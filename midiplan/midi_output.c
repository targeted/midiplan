/*
 * MIDIplan
 * Copyright (C) 2026 Dmitry Dvoinikov <dmitry@targeted.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <evar_assert.h>
#include "midi_output.h"

/*
 * Initializes the logical state of MIDI output to "empty".
 */
void initialize_midi_output_state(
    midi_output_state_t* p_midi_output_state
) {
    
    p_midi_output_state->running_status = INVALID_STATUS_BYTE;
    
    p_midi_output_state->message_data.size = 0;
    p_midi_output_state->message_data.offs = 0;
    
    p_midi_output_state->custom_sequence.p_next_byte = NULL;
}

/*
 * Returns true if buffered data is being sent.
 */
bool have_midi_output_bytes_to_send(
    midi_output_state_t* p_midi_output_state
) {
    return (p_midi_output_state->custom_sequence.p_next_byte != NULL) ||
           (p_midi_output_state->message_data.offs < p_midi_output_state->message_data.size);
}

/*
 * Copies bytes to be sent from a message containing a single literal MIDI message
 * (or one byte of a streaming system exclusive, wrapped in a fake MIDI message).
 * These messages originate from the input UART.
 */
void load_midi_output_midi_message(
    midi_output_state_t* p_midi_output_state,
    midi_message_t midi_message
) {

    status_byte_t status_byte = midi_message.status_byte;
    data_byte_t   data_byte_1 = midi_message.data_byte_1;
    data_byte_t   data_byte_2 = midi_message.data_byte_2;

    p_midi_output_state->message_data.offs = 0;
    p_midi_output_state->message_data.size = 0;

    if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) { // wrapped byte of a streaming system exclusive, either SOX or a data byte

        if (!VALID_DATA_BYTE(data_byte_1)) {
            p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = MIDI_MESSAGE_SYSTEM_EXCLUSIVE;
        }
        else {
            p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = data_byte_1;
        }

        p_midi_output_state->running_status = INVALID_STATUS_BYTE; // reset running status

    }
    else if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) { // EOX terminating the streaming system exclusive

        p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;

        p_midi_output_state->running_status = INVALID_STATUS_BYTE; // reset running status

    }
    else { // a complete regular message

        evar_assert(VALID_STATUS_BYTE(status_byte));

        // if running status is applicable, we don't need to copy the status byte for sending

        if (status_byte != p_midi_output_state->running_status) {

            p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = status_byte;

            if (IS_MIDI_CHANNEL_MESSAGE(status_byte)) { // only a channel message can become running status
                p_midi_output_state->running_status = status_byte;
            }
            else {
                p_midi_output_state->running_status = INVALID_STATUS_BYTE; // reset running status
            }

        }

        // how many data bytes the message contains is determined from the actual values

        if (VALID_DATA_BYTE(data_byte_1)) {
            p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = data_byte_1;
            if (VALID_DATA_BYTE(data_byte_2)) {
                p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.size++] = data_byte_2;
            }
        }

    }

    evar_assert(p_midi_output_state->message_data.size <= 3);

    // sending custom sequence and literal message are mutually exclusive

    p_midi_output_state->custom_sequence.p_next_byte = NULL;
}

/*
 * Takes the bytes to be sent from a message pointing to a large device-specific buffer
 * containing potentially many separate messages. This buffer is considered to be static
 * and immutable, therefore we simply keep the pointer. The bytes in the buffer are treated
 * as parameterized mini program, augmentation is applied on the fly.
 */
void load_midi_output_custom_sequence(
    midi_output_state_t* p_midi_output_state,
    const midiplan_device_t* p_device,
    custom_sequence_id_t custom_sequence_id,
    custom_sequence_parameters_t custom_sequence_parameters
) {

    p_midi_output_state->custom_sequence.p_next_byte = \
        get_device_custom_sequence(p_device, custom_sequence_id);
        
    evar_assert(p_midi_output_state->custom_sequence.p_next_byte != NULL);

    p_midi_output_state->custom_sequence.current_status = INVALID_STATUS_BYTE;
    p_midi_output_state->custom_sequence.parameters = custom_sequence_parameters;

    p_midi_output_state->custom_sequence.variables.roland_checksum = 0;

    p_midi_output_state->message_data.offs = 0; // sending custom sequence and literal message are mutually exclusive
    p_midi_output_state->message_data.size = 0;

    p_midi_output_state->running_status = INVALID_STATUS_BYTE; // reset running status
}

/*
 * This internal utility reads the next byte from the custom sequence.
 * If the MSB parity of the next byte matches the expected (status vs. data), it is returned
 * as is, otherwise all the bytes of the opposite parity are interpreted as instructions on
 * how to augment the upcoming byte, using the provided parameters. After all parameter bytes
 * are processed, we get to the real byte, and the collected augmentation is or-ed into it.
 */
static uint8_t get_augmented_byte(
    midi_output_state_t* p_midi_output_state,
    uint8_t expected_msb
) {

    const uint8_t* p_next_byte = p_midi_output_state->custom_sequence.p_next_byte;

    uint8_t augmented_byte = 0x00;

    uint8_t next_byte = *p_next_byte++;

    while ((next_byte & 0x80) != expected_msb) { // this loop ends when a real sequence byte is received, after the augmentation has been collected

        // the parity of the next byte is not as expected for the MIDI message,
        // it is interpreted as a parameter, or-augmenting the upcoming real byte

        // because the most significant bit is fixed, that leaves us with 7 bits:
        // x6543210
        //  ^       when 0:
        //   ^^        0 to 2, reference into the parameters struct to pick the parameter byte (value range 0-127), value 3 unused/reserved
        //     ^       0 = use the parameter as a literal value
        //             1 = use the parameter as an index to look up into the following inline table with 128 elements
        //      ^      0 = 4-bit value / 4-bit table entry size
        //             1 = 7-bit value / 8-bit table entry size, produces 7 bits
        //       ^^    when the previous bit is 0 (4-bit values)
        //               00 = verbatim
        //               01 = bits 2-0 of the value are shifted to bits 6-4, bit 3 is ignored
        //               10 = reserved
        //               11 = reserved
        //             when the previous bit is 1 (8-bit values)
        //               00 = verbatim
        //               01 = bit 6 of the value is set to 0, reducing value to 6 bits
        //               10 = reserved
        //               11 = reserved
        //  ^       when 1:
        //   ^^^^^^    000000 = reset the Roland-style checksum to 0, marking the first byte of a checksummed part of the sequence
        //             000001 = paste the current value of the Roland-checksum
        //             ...... = reserved
        //             111111 = invalid value

        uint8_t parameter_mode  = (next_byte & 0b01000000) >> 6;

        if (parameter_mode == 0) { // parameter-derived value

            uint8_t parameter_index = (next_byte & 0b00110000) >> 4;
            uint8_t parameter_type  = (next_byte & 0b00001000) >> 3;
            uint8_t parameter_size  = (next_byte & 0b00000100) >> 2;
            uint8_t parameter_op    = (next_byte & 0b00000011);

            // pick the parameter byte by index

            evar_assert(parameter_index < sizeof(p_midi_output_state->custom_sequence.parameters.p));
            uint8_t parameter_value = p_midi_output_state->custom_sequence.parameters.p[parameter_index];
            evar_assert((parameter_value & 0x80) == 0);

            if (parameter_type == 0) { // literal
                if (parameter_size == 0) { // use lower 4 bits
                    parameter_value &= 0x0F;
                    switch (parameter_op) {
                        case 0b00: // verbatim
                            break;
                        case 0b01: // bits 2-0 are put to bits 6-4
                            parameter_value = (parameter_value & 0b111) << 4;
                            break;
                        case 0b10: // reserved
                            break;
                        case 0b11: // reserved
                            break;
                        default:
                            break;
                    }
                }
                else { // use lower 7 bits
                    switch (parameter_op) {
                        case 0b00: // verbatim
                            break;
                        case 0b01: // reduce to 6 bits
                            parameter_value &= 0b00111111;
                            break;
                        case 0b10: // reserved
                            break;
                        case 0b11: // reserved
                            break;
                        default:
                            break;
                    }
                }
            }
            else { // lookup index
                if (parameter_size == 0) { // use 4-bit lookup, 128 4-bit entries numbered 0-127 left-to-right, 64 bytes
                    if ((parameter_value & 1) != 0) {
                        parameter_value = p_next_byte[parameter_value >> 1] & 0x0F;
                    }
                    else {
                        parameter_value = p_next_byte[parameter_value >> 1] >> 4;
                    }
                    switch (parameter_op) {
                        case 0b00: // verbatim
                            break;
                        case 0b01: // bits 2-0 are put to bits 6-4
                            parameter_value = (parameter_value & 0b111) << 4;
                            break;
                        case 0b10: // reserved
                            break;
                        case 0b11: // reserved
                            break;
                        default:
                            break;
                    }
                    p_next_byte += 64;
                }
                else { // use 8-bit lookup, 128 8-bit entries numbered 0-127 left-to-right, 128 bytes
                    parameter_value = p_next_byte[parameter_value];
                    switch (parameter_op) {
                        case 0b00: // verbatim
                            break;
                        case 0b01: // reduce to 6 bits
                            parameter_value &= 0b00111111;
                            break;
                        case 0b10: // reserved
                            break;
                        case 0b11: // reserved
                            break;
                        default:
                            break;
                    }
                    p_next_byte += 128;
                }
            }

            augmented_byte |= parameter_value;
        }
        else { // assorted operations

            switch (next_byte & 0b00111111) {
                case 0b000000: // reset the Roland-style checksum
                    p_midi_output_state->custom_sequence.variables.roland_checksum = 0;
                    break;
                case 0b000001: // paste the value of the Roland-style checksum
                    augmented_byte |= (0x80 - (p_midi_output_state->custom_sequence.variables.roland_checksum & 0x7F)) & 0x7F;
                    break;
                default: // reserved
                    break;
            }
        }

        next_byte = *p_next_byte++;
    }

    uint8_t actual_byte = augmented_byte | next_byte;

    // update running value of the Roland-style checksum

    p_midi_output_state->custom_sequence.variables.roland_checksum += actual_byte;

    // put the advanced pointer back

    p_midi_output_state->custom_sequence.p_next_byte = p_next_byte;

    return actual_byte;
}

static status_byte_t get_augmented_status_byte(
    midi_output_state_t* p_midi_output_state
) {
    status_byte_t status_byte = get_augmented_byte(p_midi_output_state, STATUS_BYTE_MSB);
    evar_assert(VALID_STATUS_BYTE(status_byte));
    return status_byte;
}

static data_byte_t get_augmented_data_byte(
    midi_output_state_t* p_midi_output_state
) {
    data_byte_t data_byte = get_augmented_byte(p_midi_output_state, DATA_BYTE_MSB);
    evar_assert(VALID_DATA_BYTE(data_byte));
    return data_byte;
}

/*
 * For a custom sequence, the bytes are interpreted as a parameterized mini-program.
 */
static bool get_next_custom_sequence_byte(
    midi_output_state_t* p_midi_output_state,
    uint8_t* p_next_byte,
    evar_time_delta_t* p_delay_usec
) {

    evar_assert(p_midi_output_state->custom_sequence.p_next_byte != NULL);

    if (p_midi_output_state->custom_sequence.current_status == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) { // reading data bytes of a sysex

        // sysex is terminated with EOX (F7), technically a status byte, which should be
        // interpreted as augmentation prefix for the upcoming data byte, but working around
        // that edge case would make the custom sequences look unnaturally complicated

        // therefore we allow literal EOX to appear as it is and terminate the sysex

        if (*p_midi_output_state->custom_sequence.p_next_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {

            p_midi_output_state->custom_sequence.current_status = INVALID_STATUS_BYTE;

            *p_next_byte = MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;
            p_midi_output_state->custom_sequence.p_next_byte += 1;

        }
        else { // anything else is expected to be a possibly augmented data byte

            *p_next_byte = get_augmented_data_byte(p_midi_output_state);

        }

        return true;
    }
    else if (VALID_STATUS_BYTE(p_midi_output_state->custom_sequence.current_status)) { // reading data bytes of a regular message

        evar_assert(p_midi_output_state->custom_sequence.data_byte_count > 0);

        *p_next_byte = get_augmented_data_byte(p_midi_output_state);

        if (--p_midi_output_state->custom_sequence.data_byte_count == 0) { // this was the last data byte of a regular message
            p_midi_output_state->custom_sequence.current_status = INVALID_STATUS_BYTE;
        }

        return true;
    }
    else { // reading a status byte

        // just like as with the EOX above, here we accept literal INVALID_STATUS_BYTE
        // as a sequence terminator even though it should be an augmentation prefix

        if (*p_midi_output_state->custom_sequence.p_next_byte == INVALID_STATUS_BYTE) { // note: need literal comparison, not !VALID_STATUS_BYTE
            p_midi_output_state->custom_sequence.p_next_byte = NULL;
            return false; // nothing is returned, end of sequence is reached
        }

        status_byte_t status_byte = get_augmented_status_byte(p_midi_output_state);

        if (status_byte == MIDI_MESSAGE_DELAY) { // undefined message repurposed as flow control to cause a delay

            data_byte_t data_byte_1 = get_augmented_data_byte(p_midi_output_state);
            data_byte_t data_byte_2 = get_augmented_data_byte(p_midi_output_state);

            *p_delay_usec = ((data_byte_1 << 7) | data_byte_2) * 1000;

            return false; // nothing is returned, UART goes into delay
        }

        if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {
            p_midi_output_state->custom_sequence.current_status = status_byte;
        }
        else {
            p_midi_output_state->custom_sequence.data_byte_count = get_expected_data_bytes(status_byte);
            if (p_midi_output_state->custom_sequence.data_byte_count > 0) {
                p_midi_output_state->custom_sequence.current_status = status_byte;
            }
        }

        *p_next_byte = status_byte;

        return true;
    }
}

/*
 * For an ad-hoc message coming from the input UART we simply take the next byte from the buffer.
 */
static bool get_next_midi_message_byte(
    midi_output_state_t* p_midi_output_state,
    uint8_t* p_next_byte
) {
    evar_assert(p_midi_output_state->message_data.offs < p_midi_output_state->message_data.size);
    evar_assert(p_midi_output_state->message_data.size <= 3);
    *p_next_byte = p_midi_output_state->message_data.bytes[p_midi_output_state->message_data.offs++];
    return true;
}

/*
 * Retrieves the next byte from the logical sequence of messages.
 * Returns true if there is a next byte, false if there is nothing
 * to send at the moment (the data may be available, but a delay
 * is being requested).
 */
bool get_next_midi_output_byte(
    midi_output_state_t* p_midi_output_state,
    uint8_t* p_next_byte,
    evar_time_delta_t* p_delay_usec
) {
    if (p_midi_output_state->custom_sequence.p_next_byte != NULL) {
        return get_next_custom_sequence_byte(p_midi_output_state, p_next_byte, p_delay_usec);
    }
    else {
        return get_next_midi_message_byte(p_midi_output_state, p_next_byte);
    }
}
