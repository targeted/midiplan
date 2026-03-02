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
#include <midiplan/midiplan.h>
#include <midiplan/controller_values.h>
#include <midiplan/note_entries.h>
#include <midiplan/channels.h>
#include <midiplan/devices.h>

static midiplan_callbacks_t* p_callbacks;

void midiplan_initialize(midiplan_callbacks_t* p_callbacks_) {

    p_callbacks = p_callbacks_;

    configure_devices();

    initialize_device_states();
    initialize_controller_values();
    initialize_note_entries();
    initialize_channels();

    reset_channel_associations();
    reset_program_statistics();
}

/*
 * This sends a fully translated message to a device. This is the last step
 * before the message hits the UART. All the changes are final, all numbers
 * already absolute in device terms.
 */
static void send_message(
    void* p_context,
    midi_out_port_t out_port,
    midi_channel_t out_channel,
    midi_message_type_t message_type,
    data_byte_t data_byte_1,
    data_byte_t data_byte_2
) {

    midi_message_t midi_message = {
        .status_byte = message_type | out_channel,
        .data_byte_1 = data_byte_1,
        .data_byte_2 = data_byte_2
    };

    p_callbacks->send_message(p_context, out_port, midi_message);
}

/*
 * Sends the same message to all output ports. This is not related to any input channel,
 * or any association with any output channel, and is used for system messages only.
 * It does not apply any translation, the messages are sent verbatim.
 */
static void broadcast_message(
    void* p_context,
    midi_message_t midi_message
) {
    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
        p_callbacks->send_message(p_context, out_port, midi_message);
    }
}

/*
 * This internal utility reads the next byte from a custom sequence in a device configuration.
 * If the MSB parity of the next byte matches the expected (status vs. data), it is returned
 * as is, otherwise all the bytes of the opposite parity are interpreted as instructions on
 * how to augment the upcoming byte, using the provided parameters. After all parameter bytes
 * are processed, we get to the real byte, and the collected augmentation is or-ed into it.
 */
static uint8_t read_augmented_byte(
    const uint8_t** p_sequence,
    const uint8_t** p_parameters,
    uint8_t expected_msb
) {

    const uint8_t* sequence = *p_sequence;

    uint8_t augmented_byte = 0x00;

    uint8_t next_byte = *sequence++;

    while ((next_byte & 0x80) != expected_msb) { // this loop ends when a real sequence byte is received, after the augmentation has been collected

        // the parity of the next byte is not as expected for the MIDI message,
        // it is interpreted as a parameter, or-augmenting the upcoming real byte

        // because the most significant bit is fixed, that leaves us with 7 bits:
        // x6543210
        //  ^       "mode" switch, when 0:
        //   ^^        0 to 3, index into the parameters array to pick the parameter byte (value range 0-127)
        //     ^       0 = use the parameter as a literal value
        //             1 = use the parameter as an index to look up into the following inline table with 128 elements
        //      ^      0 = 4-bit value / 4-bit table entry size
        //             1 = 7-bit value / 8-bit table entry size, produces 7 bits
        //       ^^    when the previous bit is 0 (4-bit values), number of bits to shift value left, 0 to 3
        //             when the previous bit is 1 (8-bit values), reserved
        //  ^       when 1:
        //             reserved

        uint8_t parameter_mode  = (next_byte & 0b01000000) >> 6;
        uint8_t parameter_index = (next_byte & 0b00110000) >> 4;
        uint8_t parameter_type  = (next_byte & 0b00001000) >> 3;
        uint8_t parameter_size  = (next_byte & 0b00000100) >> 2;
        uint8_t parameter_shift = (next_byte & 0b00000011);

        if (parameter_mode == 0) {

            // pick the parameter byte by index

            uint8_t parameter_value = (*p_parameters)[parameter_index];
            evar_assert((parameter_value & 0x80) == 0);

            if (parameter_type == 0) { // literal
                if (parameter_size == 0) { // use lower 4 bits
                    parameter_value = (parameter_value & 0x0F) << parameter_shift;
                }
            }
            else { // lookup index
                if (parameter_size == 0) { // use 4-bit lookup, 128 4-bit entries numbered 0-127 left-to-right, 64 bytes
                    if ((parameter_value & 1) != 0) {
                        parameter_value = sequence[parameter_value >> 1] & 0x0F;
                    }
                    else {
                        parameter_value = sequence[parameter_value >> 1] >> 4;
                    }
                    parameter_value <<= parameter_shift;
                    sequence += 64;
                }
                else { // use 8-bit lookup, 128 8-bit entries numbered 0-127 left-to-right, 128 bytes
                    parameter_value = sequence[parameter_value];
                    sequence += 128;
                }
            }

            evar_assert((parameter_value & 0x80) == 0); // augmentation can't alter the high bit of the value
            augmented_byte |= parameter_value;

        }
        else { // reserved

        }

        next_byte = *sequence++;
    }

    *p_sequence = sequence;

    return augmented_byte | next_byte;
}

static status_byte_t read_augmented_status_byte(
    const uint8_t** p_sequence,
    const uint8_t** p_parameters
) {
    status_byte_t result = read_augmented_byte(p_sequence, p_parameters, 0x80);
    evar_assert(VALID_STATUS_BYTE(result));
    return result;
}

static data_byte_t read_augmented_data_byte(
    const uint8_t** p_sequence,
    const uint8_t** p_parameters
) {
    data_byte_t result = read_augmented_byte(p_sequence, p_parameters, 0x00);
    evar_assert(VALID_DATA_BYTE(result));
    return result;
}

/*
 * Constructs and sends sequence of parameterized MIDI messages.
 */
static void send_sequence(
    void*           p_context,
    midi_out_port_t out_port,
    const uint8_t*  sequence,
    const uint8_t   parameters[4]
) {

    while (*sequence != INVALID_STATUS_BYTE) {

        status_byte_t status_byte = read_augmented_status_byte(&sequence, &parameters);

        midi_message_t midi_message = {
            .status_byte = status_byte,
            .data_byte_1 = INVALID_DATA_BYTE,
            .data_byte_2 = INVALID_DATA_BYTE,
        };

        if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {

            p_callbacks->send_message(p_context, out_port, midi_message);

            while (*sequence != MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {
                midi_message.data_byte_1 = read_augmented_data_byte(&sequence, &parameters);
                p_callbacks->send_message(p_context, out_port, midi_message);
            }

            sequence += 1; // skip EOX

            midi_message.status_byte = MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;
            midi_message.data_byte_1 = INVALID_DATA_BYTE;

            p_callbacks->send_message(p_context, out_port, midi_message);
        }
        else {

            switch (get_expected_data_bytes(status_byte)) {
                case 2:
                    midi_message.data_byte_1 = read_augmented_data_byte(&sequence, &parameters);
                    midi_message.data_byte_2 = read_augmented_data_byte(&sequence, &parameters);
                    break;
                case 1:
                    midi_message.data_byte_1 = read_augmented_data_byte(&sequence, &parameters);
                    break;
                case 0:
                    break;
                default:
                    return;
            }

            p_callbacks->send_message(p_context, out_port, midi_message);
        }
    }
}

/*
 * Sends the specific initialization sequence to a device.
 */
static void send_initialization_sequence(
    void* p_context,
    midi_out_port_t out_port
) {

    const midiplan_device_t* p_device = devices[out_port].p_device;

    uint16_t sequence_offset = p_device->initialization_sequence_offset;
    if (sequence_offset == INVALID_SEQUENCE_OFFSET) {
        // there is no default initialization sequence
        return;
    }

    if (sequence_offset > 0) {
        evar_assert(p_device->custom_sequences[sequence_offset - 1] == INVALID_STATUS_BYTE); // buffer integrity check
    }

    const uint8_t parameters[4] = {
        p_device->basic_channel - 1,
        0x00,
        0x00,
        0x00
    };

    send_sequence(
        p_context,
        out_port,
        p_device->custom_sequences + sequence_offset,
        parameters
    );
}

/*
 * Sends the specific program change sequence to a device.
 */
static void send_program_change_sequence(
    void* p_context,
    midi_out_port_t out_port,
    channel_t out_channel,
    program_t out_program
) {

    evar_assert(VALID_CHANNEL(out_channel));
    evar_assert(VALID_PROGRAM(out_program));

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    if (p_device->monotimbral_channels) {
        evar_assert(p_device_state->channels[out_channel].notes_playing == 0);
        evar_assert(!VALID_NOTE_ENTRY_ID(p_device_state->channels[out_channel].last_note_entry_id));
    }

    uint16_t sequence_offset = p_device->program_change_sequence_offset;
    if (sequence_offset == INVALID_SEQUENCE_OFFSET) {

        // if there is no custom sequence for program change,
        // we send the default message

        send_message(
            p_context,
            out_port,
            out_channel,
            MIDI_MESSAGE_PROGRAM_CHANGE,
            out_program,
            INVALID_DATA_BYTE
        );

        return;
    }

    if (sequence_offset > 0) {
        evar_assert(p_device->custom_sequences[sequence_offset - 1] == INVALID_STATUS_BYTE); // buffer integrity check
    }

    const uint8_t parameters[4] = {
        out_channel,
        out_program,
        0x00,
        0x00
    };

    send_sequence(
        p_context,
        out_port,
        p_device->custom_sequences + sequence_offset,
        parameters
    );
}

/*
 * Sends the specific note on sequence to a device.
 */
static void send_note_on_sequence(
    void* p_context,
    midi_out_port_t out_port,
    channel_t out_channel,
    note_t out_note,
    data_byte_t out_velocity
) {

    evar_assert(VALID_CHANNEL(out_channel));
    evar_assert(VALID_NOTE(out_note));
    evar_assert(VALID_DATA_BYTE(out_velocity) && out_velocity > 0);

    const midiplan_device_t* p_device = devices[out_port].p_device;

    uint16_t sequence_offset = p_device->note_on_sequence_offset;
    if (sequence_offset == INVALID_SEQUENCE_OFFSET) {

        // if there is no custom sequence for note on,
        // we send the default message

        send_message(
            p_context,
            out_port,
            out_channel,
            MIDI_MESSAGE_NOTE_ON,
            out_note,
            out_velocity
        );

        return;
    }

    if (sequence_offset > 0) {
        evar_assert(p_device->custom_sequences[sequence_offset - 1] == INVALID_STATUS_BYTE); // buffer integrity check
    }

    const uint8_t parameters[8] = {
        out_channel,
        out_note,
        out_velocity,
        0x00
    };

    send_sequence(
        p_context,
        out_port,
        p_device->custom_sequences + sequence_offset,
        parameters
    );
}

/*
 * Sends the specific note off sequence to a device.
 */
static void send_note_off_sequence(
    void* p_context,
    midi_out_port_t out_port,
    channel_t out_channel,
    note_t out_note,
    data_byte_t out_velocity
) {

    evar_assert(VALID_CHANNEL(out_channel));
    evar_assert(VALID_NOTE(out_note));
    evar_assert(VALID_DATA_BYTE(out_velocity));

    const midiplan_device_t* p_device = devices[out_port].p_device;

    uint16_t sequence_offset = p_device->note_off_sequence_offset;
    if (sequence_offset == INVALID_SEQUENCE_OFFSET) {

        // if there is no custom sequence for note off,
        // we send the default message

        send_message(
            p_context,
            out_port,
            out_channel,
            MIDI_MESSAGE_NOTE_OFF,
            out_note,
            out_velocity
        );

        return;
    }

    if (sequence_offset > 0) {
        evar_assert(p_device->custom_sequences[sequence_offset - 1] == INVALID_STATUS_BYTE); // buffer integrity check
    }

    const uint8_t parameters[4] = {
        out_channel,
        out_note,
        out_velocity,
        0x00
    };

    send_sequence(
        p_context,
        out_port,
        p_device->custom_sequences + sequence_offset,
        parameters
    );
}

/*
 * Sends a message to change controller value on an output channel.
 * The message is sent only if that controller is supported by the device.
 */
static void send_control_change(
    void* p_context,
    midi_out_port_t out_port,
    midi_channel_t out_channel,
    control_t control,
    data_byte_t msb_or_value,
    data_byte_t lsb
) {

    const midiplan_device_t* p_device = devices[out_port].p_device;

    if (control < 0x20) { // long controller value

        if (controller_supported(p_device, control) && controller_supported(p_device, control | 0x20)) {

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CONTROL_CHANGE,
                control,
                msb_or_value
            );

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CONTROL_CHANGE,
                control | 0x20,
                lsb
            );
        }
    }
    else if (control >= 0x40 && control < 0x78) { // short controller value

        if (controller_supported(p_device, control)) {

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CONTROL_CHANGE,
                control,
                msb_or_value
            );
        }
    }
    else if (control == CONTROL_PRESSURE) { // channel pressure, one byte

        if (channel_pressure_supported(p_device)) {

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CHANNEL_PRESSURE,
                msb_or_value,
                INVALID_DATA_BYTE
            );
        }
    }
    else if (control == CONTROL_PITCH_BEND) { // channel pitch bend, two bytes

        if (pitch_bend_supported(p_device)) {

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_PITCH_BEND,
                lsb,
                msb_or_value
            );
        }
    }
}

/*
 * Sends a message to reset a controller to its default value.
 * The message is sent only if that controller is supported by the device.
 */
static void send_control_default(
    void* p_context,
    midi_out_port_t out_port,
    midi_channel_t out_channel,
    control_t control
) {

    evar_assert(VALID_CONTROL(control));

    if (control == CONTROL_PRESSURE) {
        send_control_change(p_context, out_port, out_channel, CONTROL_PRESSURE, 0, 0);
    }
    else if (control == CONTROL_PITCH_BEND) {
        send_control_change(p_context, out_port, out_channel, CONTROL_PRESSURE, 64, 0);
    }
    else {
        data_byte_t msb_or_value = get_default_controller_value(control);
        send_control_change(p_context, out_port, out_channel, control, msb_or_value, 0);
    }
}

/*
 * Returns note duration value in units being 1/8th of the note's input program
 * average note duration. Therefore a result of 0 means less that 1/8th,
 * 16 means twice the average and so forth.
 */
static uint8_t get_note_age(
    note_entry_id_t note_entry_id
) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    program_t in_program = p_note_entry->in.program;
    evar_assert(VALID_PROGRAM(in_program));

    uint16_t average_note_duration_ms = get_average_note_duration(in_program);
    if (average_note_duration_ms == 0) { // no information on that program yet
        average_note_duration_ms = 500;  // some arbitrary value
    }
    evar_assert(average_note_duration_ms <= 2250);

    evar_time_delta_t note_duration_usec = evar__get_time_delta(&p_note_entry->timestamp, &evar_current_timestamp);
    evar_assert(note_duration_usec >= 0);

    uint8_t note_age = ((note_duration_usec / 1000) * 8) / average_note_duration_ms;

    // here is one edge case, percussion notes can vary significantly in duration
    // and do not exhibit same uniformity as the melodic programs, therefore for
    // percussion notes we conservatively report the age as being half of it, so
    // that we don't evict longer percussion notes because there were shorter ones

    if (IS_PERCUSSION_PROGRAM(in_program)) {
        return note_age / 2;
    }

    return note_age;
}

/*
 * Updates note counters for a device, accounting for a note being turned off.
 * The note is expressed as a translated device-specific number.
 */
static void account_note_off(
    note_entry_id_t note_entry_id,
    midi_out_port_t out_port
) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    note_route_t* p_out_route = &note_entries[note_entry_id].out[out_port];

    channel_t out_channel = p_out_route->channel;
    evar_assert(VALID_CHANNEL(out_channel));

    program_t out_program = p_out_route->program;
    evar_assert(VALID_PROGRAM(out_program));

    note_t out_note = p_out_route->note;
    evar_assert((out_note >= MIDI_LOWEST_NOTE) && (out_note <= MIDI_HIGHEST_NOTE));

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    // percussion notes are accounted as melodic if max_percussion_notes = 0
    // and we are still having a percussion output program here

    if (USES_MELODIC_TIMBRE(p_device, out_program)) {

        // total note counter is decremented

        evar_assert(p_device_state->melodic_notes_playing > 0);
        p_device_state->melodic_notes_playing -= 1;

        // per program note counter is decremented

        uint8_t program_note_count = p_device_state->melodic_notes_per_program[out_program];
        evar_assert(program_note_count > 0);
        p_device_state->melodic_notes_per_program[out_program] = --program_note_count;

        if (program_note_count == 0) {
            evar_assert(p_device_state->melodic_programs_playing > 0);
            p_device_state->melodic_programs_playing -= 1;
        }
    }
    else {

        evar_assert(USES_PERCUSSION_TIMBRE(p_device, out_program));

        // total note counter is decremented

        evar_assert(p_device_state->percussion_notes_playing > 0);
        p_device_state->percussion_notes_playing -= 1;
    }

    // per-channel statistics is updated

    evar_assert(p_device_state->channels[out_channel].notes_playing > 0);
    p_device_state->channels[out_channel].notes_playing -= 1;

    // notice that when the last note is turned off, the previous note can
    // technically become "the last" but we don't have information on previous notes,
    // therefore (notes_playing == 1) does *not* imply VALID_NOTE_ENTRY_ID(last_note_entry_id)

    if (p_device_state->channels[out_channel].last_note_entry_id == note_entry_id) {
        p_device_state->channels[out_channel].last_note_entry_id = INVALID_NOTE_ENTRY_ID;
    }
}

/*
 * Updates note counters for a device, accounting for a note being turned on.
 * The note is expressed as a translated device-specific number.
 */
static void account_note_on(
    note_entry_id_t note_entry_id,
    midi_out_port_t out_port
) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    note_route_t* p_out_route = &note_entries[note_entry_id].out[out_port];

    channel_t out_channel = p_out_route->channel;
    evar_assert(VALID_CHANNEL(out_channel));

    program_t out_program = p_out_route->program;
    evar_assert(VALID_PROGRAM(out_program));

    note_t out_note = p_out_route->note;
    evar_assert((out_note >= MIDI_LOWEST_NOTE) && (out_note <= MIDI_HIGHEST_NOTE));

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    // percussion notes are accounted as melodic if max_percussion_notes = 0
    // and we are still having a percussion output program here

    if (USES_MELODIC_TIMBRE(p_device, out_program)) {

        // total note counter is incremented

        evar_assert(p_device_state->melodic_notes_playing < p_device->max_melodic_notes);
        p_device_state->melodic_notes_playing += 1;

        // per program note counter is incremented

        uint8_t program_note_count = p_device_state->melodic_notes_per_program[out_program];
        evar_assert(program_note_count < p_device->max_notes_per_program);
        p_device_state->melodic_notes_per_program[out_program] = ++program_note_count;

        // if this is the first note on that program, the program counter is incremented,
        // except when it is a percussion note and percussion is a separate resource

        if (program_note_count == 1) {
            evar_assert(p_device_state->melodic_programs_playing < p_device->max_melodic_programs);
            p_device_state->melodic_programs_playing += 1;
        }
    }
    else {

        evar_assert(USES_PERCUSSION_TIMBRE(p_device, out_program));

        // total note counter is incremented

        evar_assert(p_device_state->percussion_notes_playing < p_device->max_percussion_notes);
        p_device_state->percussion_notes_playing += 1;
    }

    // per-channel statistics is updated

    p_device_state->channels[out_channel].notes_playing += 1;
    p_device_state->channels[out_channel].last_note_entry_id = note_entry_id;

}

/*
 * Turns a note off at a single output device, the note entry
 * is still kept and the other output channels are not affected.
 */
static void out_note_off(
    void* p_context,
    note_entry_id_t note_entry_id,
    midi_out_port_t out_port,
    data_byte_t velocity
) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    // while the note entry for this device is still intact, account for the note being turned off

    account_note_off(note_entry_id, out_port);

    // erase the note reference from the output side of the entry

    note_route_t* p_out_route = &p_note_entry->out[out_port];

    channel_t out_channel = p_out_route->channel;
    evar_assert(VALID_CHANNEL(out_channel));
    p_out_route->channel = INVALID_CHANNEL;

    program_t out_program = p_out_route->program;
    evar_assert(VALID_PROGRAM(out_program));
    p_out_route->program = INVALID_PROGRAM;

    note_t out_note = p_out_route->note;
    evar_assert((out_note >= MIDI_LOWEST_NOTE) && (out_note <= MIDI_HIGHEST_NOTE));
    uint8_t out_note_index = out_note - MIDI_LOWEST_NOTE;
    p_out_route->note = INVALID_NOTE;

    output_channel_t* p_output_channel = &output_channels[out_port][out_channel];
    evar_assert(p_output_channel->note_entry_lookup[out_note_index] == note_entry_id);
    p_output_channel->note_entry_lookup[out_note_index] = INVALID_NOTE_ENTRY_ID;

    // send "note off" to the device

    send_note_off_sequence(
        p_context,
        out_port,
        out_channel,
        out_note,
        velocity
    );
}

/*
 * This structure contains contextual parameters passed
 * to the evict_note_callback below.
 */
typedef struct {
    void*            p_context;
    midi_out_port_t  out_port;
    program_t        out_program;
    bool             polyphony_exceeded;
    bool             notes_per_program_exceeded;
    bool             multitimbrality_exceeded;
    note_entry_id_t  candidate_note_entry_id;
    uint8_t          candidate_note_age;
} evict_note_context_t;

/*
 * The purpose of this callback is to find an existing note, which could
 * be turned off on one output channel, to accomodate another note on that
 * one device.
 */
static void evict_note_callback(
    void* p_callback_context,
    note_entry_id_t note_entry_id
) {

    evict_note_context_t* p_evict_note_context = (evict_note_context_t*)p_callback_context;
    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    // we only consider notes that are playing on this device at all

    midi_out_port_t out_port = p_evict_note_context->out_port;
    note_route_t* p_out_route = &p_note_entry->out[out_port];

    if (!VALID_CHANNEL(p_out_route->channel)) {
        return; // iteration continues, this note is not even playing on this device
    }

    program_t out_program = p_out_route->program; // this is the *current* program on which a note is playing
    evar_assert(VALID_PROGRAM(out_program));

    // for the next node to be considered as a candidate for replacement,
    // it must be old enough and also older than the current best candidate

    uint8_t candidate_note_age = get_note_age(note_entry_id);

    if (candidate_note_age < MIN_REPLACEABLE_NOTE_AGE) {
        return; // iteration continues, this node has not sounded long enough
    }

    if (candidate_note_age <= p_evict_note_context->candidate_note_age) {
        return; // iteration continues, this note is a worse candidate than what we already have
    }

    // will evicting this note solve our issue ?

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    // notice that if we evict any note, exceeded polyphony, even it was happening, would also be solved

    if (p_evict_note_context->multitimbrality_exceeded) {

        // this could be remedied if the evicted note is the only one playing on some other program

        evar_assert(!p_evict_note_context->notes_per_program_exceeded); // notes per program cannot be exceeded here, because the program note count must be 0
        evar_assert(p_evict_note_context->out_program != out_program);

        evar_assert(USES_MELODIC_TIMBRE(p_device, p_evict_note_context->out_program));

        if (USES_MELODIC_TIMBRE(p_device, out_program)) {
            if (p_device_state->melodic_notes_per_program[out_program] == 1) {
                p_evict_note_context->candidate_note_entry_id = note_entry_id;
                p_evict_note_context->candidate_note_age = candidate_note_age;
            }
        }
    }
    else if (p_evict_note_context->notes_per_program_exceeded) {

        // this could be remedied if the evicted note is playing on the same program

        evar_assert(!p_evict_note_context->multitimbrality_exceeded); // multitimbrality cannot be exceeded here, because the program note count must be > 0

        if (p_evict_note_context->out_program == out_program) {
            p_evict_note_context->candidate_note_entry_id = note_entry_id;
            p_evict_note_context->candidate_note_age = candidate_note_age;
        }
    }
    else if (p_evict_note_context->polyphony_exceeded) {

        // this could be remedied by evicting any compatible note

        if (
            (USES_MELODIC_TIMBRE(p_device, p_evict_note_context->out_program) && USES_MELODIC_TIMBRE(p_device, out_program)) ||
            (USES_PERCUSSION_TIMBRE(p_device, p_evict_note_context->out_program) && USES_PERCUSSION_TIMBRE(p_device, out_program))
        ) {
            p_evict_note_context->candidate_note_entry_id = note_entry_id;
            p_evict_note_context->candidate_note_age = candidate_note_age;
        }
    }

    // iteration continues, we could still find a better candidate to evict
}

/*
 * Returns true if another note can be accepted on a device.
 * The note's program is expressed as a translated device-specific number.
 * If the new note exceeds device limits, an attempt is made to evict
 * and shut down one of the currently playing notes. If eviction succeeds,
 * the new note is accepted.
 */
static bool note_can_be_accepted(
    void* p_context,
    midi_out_port_t out_port,
    program_t out_program
) {

    evar_assert(VALID_PROGRAM(out_program));

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    bool polyphony_exceeded;
    bool notes_per_program_exceeded;
    bool multitimbrality_exceeded;

    if (USES_MELODIC_TIMBRE(p_device, out_program)) {

        uint8_t program_note_count = p_device_state->melodic_notes_per_program[out_program];

        polyphony_exceeded         = (p_device_state->melodic_notes_playing == p_device->max_melodic_notes);
        notes_per_program_exceeded = (program_note_count == p_device->max_notes_per_program);
        multitimbrality_exceeded   = (program_note_count == 0) && (p_device_state->melodic_programs_playing == p_device->max_melodic_programs);
    }
    else {

        evar_assert(USES_PERCUSSION_TIMBRE(p_device, out_program));

        polyphony_exceeded         = (p_device_state->percussion_notes_playing == p_device->max_percussion_notes);
        notes_per_program_exceeded = (p_device_state->percussion_notes_playing == p_device->max_notes_per_program);
        multitimbrality_exceeded   = false;
    }

    if (polyphony_exceeded || notes_per_program_exceeded || multitimbrality_exceeded) {

        // see if an existing note can be dropped and replaced with
        // the incoming one, and we are still under the limits

        evict_note_context_t evict_note_context = {
            .p_context                  = p_context,
            .out_port                   = out_port,
            .out_program                = out_program,
            .polyphony_exceeded         = polyphony_exceeded,
            .notes_per_program_exceeded = notes_per_program_exceeded,
            .multitimbrality_exceeded   = multitimbrality_exceeded,
            .candidate_note_entry_id    = INVALID_NOTE_ENTRY_ID,
            .candidate_note_age         = 0
        };

        // we are looking for a single note among all the existing ones

        enumerate_note_entries(&evict_note_context, evict_note_callback);

        note_entry_id_t evicted_note_entry_id = evict_note_context.candidate_note_entry_id;
        if (!VALID_NOTE_ENTRY_ID(evicted_note_entry_id)) {
            return false; // did not find a note to evict
        }

        evar_assert(evict_note_context.candidate_note_age > 0);

        program_t evicted_program = note_entries[evicted_note_entry_id].out[out_port].program;
        evar_assert(VALID_PROGRAM(evicted_program));

        evar_assert(
            (USES_MELODIC_TIMBRE(p_device, evicted_program) && USES_MELODIC_TIMBRE(p_device, out_program)) ||
            (USES_PERCUSSION_TIMBRE(p_device, evicted_program) && USES_PERCUSSION_TIMBRE(p_device, out_program))
        );

        // this is the output note we decided to evict, we turn it off, but the note entry still remains

        out_note_off(p_context, evicted_note_entry_id, out_port, 0);

        // now we have capacity for the new note

    }

    return true;
}

/*
 * Sends the same controller change message to all output
 * channels *currently* associated with this input channel.
 */
static void propagate_control_change(
    void* p_context,
    midi_channel_t in_channel,
    control_t control,
    data_byte_t msb_or_value,
    data_byte_t lsb
) {

    input_channel_t* p_input_channel = &input_channels[in_channel];

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        channel_t out_channel = p_input_channel->associated_out_channels[out_port];
        if (!VALID_CHANNEL(out_channel)) {
            continue;
        }

        send_control_change(
            p_context,
            out_port,
            out_channel,
            control,
            msb_or_value,
            lsb
        );
    }
}

/*
 * This is called to turn an input note off. After this call returns,
 * all the output notes have been turned off and the note entry
 * is cleared but not deallocated. This is the moment when a note
 * is officially not sounding any more. The output notes could have been
 * shut off already, but from the client perspective the sound was still
 * supposed to be playing.
 */
static void in_note_off(
    void* p_context,
    note_entry_id_t note_entry_id,
    data_byte_t velocity
) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    // turn off each output note individually

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
        if (VALID_CHANNEL(p_note_entry->out[out_port].channel)) {
            out_note_off(p_context, note_entry_id, out_port, velocity);
        }
    }

    // clear the input side of the note entry

    channel_t in_channel = p_note_entry->in.channel;
    evar_assert(VALID_CHANNEL(in_channel));
    p_note_entry->in.channel = INVALID_CHANNEL;

    program_t in_program = p_note_entry->in.program;
    evar_assert(VALID_PROGRAM(in_program));
    p_note_entry->in.program = INVALID_PROGRAM;

    note_t in_note = p_note_entry->in.note;
    evar_assert((in_note >= MIDI_LOWEST_NOTE) && (in_note <= MIDI_HIGHEST_NOTE));
    uint8_t in_note_index = in_note - MIDI_LOWEST_NOTE;
    p_note_entry->in.note = INVALID_NOTE;

    input_channel_t* p_input_channel = &input_channels[in_channel];
    evar_assert(p_input_channel->note_entry_lookup[in_note_index] == note_entry_id);
    p_input_channel->note_entry_lookup[in_note_index] = INVALID_NOTE_ENTRY_ID;

    // now that we are sure the note is officially not sounding any more,
    // update the program statistics with the note's actual duration

    evar_time_delta_t note_duration_usec = evar__get_time_delta(&p_note_entry->timestamp, &evar_current_timestamp);
    evar_assert(note_duration_usec >= 0);

    if (note_duration_usec > 0) {
        uint16_t note_duration_ms = (note_duration_usec < 10000000) ? ((note_duration_usec + 999) / 1000) : 10000;
        register_note_duration(in_program, note_duration_ms);
    }
}

/*
 * This is called to turn a note off. The note may or may not be playing.
 * After this call returns, the note entry is cleared and deallocated.
 */
static void handle_note_off(
    void* p_context,
    midi_channel_t in_channel,
    midi_note_number_t note_number,
    data_byte_t velocity
) {

    if ((note_number < MIDI_LOWEST_NOTE) || (note_number > MIDI_HIGHEST_NOTE)) {
        return;
    }

    // the note being turned off is specified in terms of its input route,
    // i.e. the input channel and the original note number

    note_t in_note = note_number;
    uint8_t in_note_index = in_note - MIDI_LOWEST_NOTE;

    // we find the note in the input channel index, where it had to be put by the note on before

    input_channel_t* p_input_channel = &input_channels[in_channel];

    note_entry_id_t note_entry_id = p_input_channel->note_entry_lookup[in_note_index];
    if (!VALID_NOTE_ENTRY_ID(note_entry_id)) {
        return;
    }

    in_note_off(p_context, note_entry_id, velocity);

    // release the now empty entry back to the pool

    deallocate_note_entry(note_entry_id);
}

/*
 * This structure contains one bit per channel controller.
 */
typedef struct {
    uint32_t controllers[128 / 32];
    bool pressure;
    bool pitch_bend;
} assigned_controllers_t;

/*
 * This structure contains contextual parameters passed
 * to the collect_controllers_callback below.
 */
typedef struct {
    program_t in_program;
    assigned_controllers_t assigned_controllers;
} collect_controllers_context_t;

/*
 * This callback accumulates information on which controllers
 * have been assigned on a program on a channel.
 */
static void collect_controllers_callback(
    void* p_callback_context,
    midi_channel_t in_channel,
    program_t in_program,
    control_t control,
    controller_value_t* p_controller_value
) {

    EVAR_UNUSED(in_channel);
    EVAR_UNUSED(p_controller_value);

    collect_controllers_context_t* p_collect_controllers_context = (collect_controllers_context_t*)p_callback_context;

    if (VALID_PROGRAM(p_collect_controllers_context->in_program) && in_program != p_collect_controllers_context->in_program) {
        return;
    }

    if (control == CONTROL_PRESSURE) {
        p_collect_controllers_context->assigned_controllers.pressure = true;
    }
    else if (control == CONTROL_PITCH_BEND) {
        p_collect_controllers_context->assigned_controllers.pitch_bend = true;
    }
    else {
        p_collect_controllers_context->assigned_controllers.controllers[control >> 5] |= (1 << (control & 0x1F));
    }
}

/*
 * This structure contains contextual parameters passed
 * to the restore_program_controllers_callback below.
 */
typedef struct {
    void* p_context;
    program_t in_program;
    midi_out_port_t out_port;
    midi_channel_t out_channel;
} restore_program_controllers_context_t;

/*
 * This callback sends a program's controller value to the device.
 */
static void restore_program_controllers_callback(
    void* p_callback_context,
    midi_channel_t in_channel,
    program_t in_program,
    control_t control,
    controller_value_t* p_controller_value
) {

    EVAR_UNUSED(in_channel);
    EVAR_UNUSED(p_controller_value);

    restore_program_controllers_context_t* p_restore_program_controllers_context = (restore_program_controllers_context_t*)p_callback_context;

    evar_assert(VALID_PROGRAM(p_restore_program_controllers_context->in_program));

    if (in_program != p_restore_program_controllers_context->in_program) {
        return;
    }

    data_byte_t msb_or_value = p_controller_value->msb;
    if (VALID_DATA_BYTE(msb_or_value)) {

        send_control_change(
            p_restore_program_controllers_context->p_context,
            p_restore_program_controllers_context->out_port,
            p_restore_program_controllers_context->out_channel,
            control,
            msb_or_value,
            p_controller_value->lsb
        );
    }
}

static void associate_channels(
    void* p_context,
    midi_channel_t in_channel,
    program_t in_program,
    midi_out_port_t out_port,
    midi_channel_t out_channel,
    program_t out_program
) {

    evar_assert(VALID_PROGRAM(in_program));

    input_channel_t* p_input_channel = &input_channels[in_channel];
    output_channel_t* p_output_channel = &output_channels[out_port][out_channel];

    // if the output channel has been previously associated with some input channel
    // (the same one, or a different one) its inherited controllers must be reset

    channel_t prev_in_channel = p_output_channel->associated_in_channel;
    if (VALID_CHANNEL(prev_in_channel)) {

        // the previously associated input channel must be disassociated

        if (
            prev_in_channel != in_channel &&
            input_channels[prev_in_channel].associated_out_channels[out_port] == out_channel
        ) {
            input_channels[prev_in_channel].associated_out_channels[out_port] = INVALID_CHANNEL;
        }

        // collect controllers that have been assigned at the old input channel for all programs

        collect_controllers_context_t collect_channel_controllers_context = {
            .in_program           = INVALID_PROGRAM,
            .assigned_controllers = {
                .controllers      = { 0 },
                .pressure         = false,
                .pitch_bend       = false
            }
        };

        enumerate_controller_values(
            prev_in_channel, // collect on the previously associated input channel
            &collect_channel_controllers_context,
            collect_controllers_callback
        );

        // collect controller values assigned on the program to which we are switching to

        collect_controllers_context_t collect_program_controllers_context = {
            .in_program           = in_program,
            .assigned_controllers = {
                .controllers      = { 0 },
                .pressure         = false,
                .pitch_bend       = false
            }
        };

        enumerate_controller_values(
            in_channel, // collect on the input channel to be associated
            &collect_program_controllers_context,
            collect_controllers_callback
        );

        // subtract the program controllers from the channel controllers,
        // because there is no need to reset controllers that are going
        // to be immediately assigned with their new values

        assigned_controllers_t* p_channel_controllers = &collect_channel_controllers_context.assigned_controllers;
        assigned_controllers_t* p_program_controllers = &collect_program_controllers_context.assigned_controllers;

        for (uint8_t i = 0; i < (128 / 32); ++i) {
            p_channel_controllers->controllers[i] &= ~p_program_controllers->controllers[i];
        }

        if (p_program_controllers->pressure) {
            p_channel_controllers->pressure = false;
        }

        if (p_program_controllers->pitch_bend) {
            p_channel_controllers->pitch_bend = false;
        }

        // what's left in channel controllers needs to be reset to default
        // by explicitly sending the default value for each

        for (uint8_t i = 0; i < (128 / 32); ++i) {

            uint32_t bitmap = p_channel_controllers->controllers[i];
            if (bitmap == 0) {
                continue;
            }

            for (uint8_t j = 0; j < 32; ++j) {
                if ((bitmap & (1 << j)) != 0) {
                    midi_control_number_t control_number = (i * 32) + j;
                    evar_assert(control_number < 128);
                    send_control_default(p_context, out_port, out_channel, control_number);
                }
            }
        }

        if (p_channel_controllers->pressure) {
            send_control_default(p_context, out_port, out_channel, CONTROL_PRESSURE);
        }

        if (p_channel_controllers->pitch_bend) {
            send_control_default(p_context, out_port, out_channel, CONTROL_PITCH_BEND);
        }
    }

    // a change to a different program may be required on the output channel

    if (p_output_channel->out_program != out_program) {

        if (IS_MELODIC_PROGRAM(out_program)) { // no need to explicitly switch to a percussion program
            send_program_change_sequence(
                p_context,
                out_port,
                out_channel,
                out_program
            );
        }

        p_output_channel->out_program = out_program;
    }

    // now that the program is coherent, restore the controller values expected for this program at this channel,
    // this is expected to go through exactly the same controllers as collected in collect_program_controllers_context

    restore_program_controllers_context_t restore_program_controllers_context = {
        .p_context   = p_context,
        .in_program  = in_program,
        .out_port    = out_port,
        .out_channel = out_channel
    };

    enumerate_controller_values(
        in_channel,
        &restore_program_controllers_context,
        restore_program_controllers_callback
    );

    // establish the association between the input and the output channels

    p_output_channel->associated_in_channel = in_channel;
    p_output_channel->associated_in_channels |= (1 << in_channel); // this bit will never be cleared, tracking history rather than current state

    p_input_channel->associated_out_channels[out_port] = out_channel;

    // and we are done
}

/*
 * Selects one channel from the set. The choice does not have to be truly random,
 * important is only that it changes every time. Returns the selected channel.
 */
static midi_channel_t select_random_channel(midi_channels_bitmap_t channels_bitmap) {

    static midi_channel_t last_channel = MIDI_CHANNEL_1;
    midi_channel_t selected_channel = INVALID_CHANNEL;

    for (uint8_t i = 0; i < MIDI_CHANNEL_COUNT; ++i) {

        if ((channels_bitmap & (1 << last_channel)) != 0) {
            selected_channel = last_channel;
        }

        if (++last_channel == MIDI_CHANNEL_COUNT) {
            last_channel = MIDI_CHANNEL_1;
        }

        if (VALID_CHANNEL(selected_channel)) {
            break;
        }
    }

    return selected_channel;
}

/*
 * This function picks one of the output channels of a device to be used to send the next note to.
 * For the course of sending a note, the channels will be associated to have coherent program and
 * controller values. The three major problems here are
 * (1) there could be fewer output channels that input, therefore the output channels must be reused
 * (2) the program and the controller values assumed by the input channel must be restored
 * (3) a note with the same number can already be playing on the selected output channel
 */
static channel_t associate_out_channel(
    void* p_context,
    midi_channel_t in_channel,
    program_t in_program,
    midi_out_port_t out_port,
    midi_channels_bitmap_t out_channels_bitmap,
    program_t out_program,
    note_t out_note
) {

    evar_assert(VALID_PROGRAM(in_program));
    evar_assert(out_channels_bitmap != 0);
    evar_assert(VALID_PROGRAM(out_program));

    evar_assert((out_note >= MIDI_LOWEST_NOTE) && (out_note <= MIDI_HIGHEST_NOTE));
    uint8_t out_note_index = out_note - MIDI_LOWEST_NOTE;

    input_channel_t* p_input_channel = &input_channels[in_channel];

    const midiplan_device_t* p_device = devices[out_port].p_device;
    midiplan_device_state_t* p_device_state = &devices[out_port].state;

    // our best chance is that this input channel is already associated with an output channel
    // on the required program, this way nothing needs to be done at all, and it is the typical
    // situation when there is no shortage of output channels (e.g. 15+1 to 15+1 mapping)

    channel_t associated_out_channel = p_input_channel->associated_out_channels[out_port];
    if (VALID_CHANNEL(associated_out_channel)) {

        output_channel_t* p_associated_output_channel = &output_channels[out_port][associated_out_channel];
        evar_assert(p_associated_output_channel->associated_in_channel == in_channel);

        // there are three possibilities when such happy reassociation is not possible:
        // 1. if a program change is initiated by a percussion note
        // 2. if the same note is already playing on that channel
        // 3. we hit the limit of notes playing per channel
        // either way we must then go through full channel search

        if (
            (p_associated_output_channel->out_program == out_program) &&                             // otherwise a program change has been requested
            !VALID_NOTE_ENTRY_ID(p_associated_output_channel->note_entry_lookup[out_note_index]) &&  // otherwise the same note already plays
            ((p_device->max_notes_per_channel == 0) || p_device_state->channels[associated_out_channel].notes_playing < p_device->max_notes_per_channel) // otherwise the channel is full
        ) {
            return associated_out_channel;
        }

        associated_out_channel = INVALID_CHANNEL;
    }

    evar_assert(!VALID_CHANNEL(associated_out_channel));

    // at this point we have ensured that the device is capable of playing another note,
    // but whether or we have a channel to send this note over is not guaranteed, and
    // if we can't find a suitable channel, the note will still not be played

    // cycle through all and pick one output channel

    channel_t exclusive_out_channel         = INVALID_CHANNEL;    // an output channel that was only ever associated with this input channel
    midi_channels_bitmap_t in_channel_mask  = (1 << in_channel);

    channel_t pristine_out_channel          = INVALID_CHANNEL;    // an output channel which was never associated with any input channel

    midi_channels_bitmap_t same_program_without_note = 0;         // multiple channels on which the required program is currently selected and the required note is not playing
    channel_t same_program_with_note        = INVALID_CHANNEL;    // an output channel on which the required program is currently selected and the required note is playing
    uint8_t same_program_note_age           = 0;                  // if the same note is playing, then how old it is

    midi_channels_bitmap_t diff_program_without_note = 0;         // multiple channels on which a different program is currently selected and the required note is not playing
    channel_t diff_program_with_note        = INVALID_CHANNEL;    // an output channel on which a different program is currently selected and the required note is playing
    uint8_t diff_program_note_age           = 0;                  // if the same note is playing, then how old it is

    bool in_channel_was_associated          = false;              // whether this input channel was ever associated with any output channel before

    for (uint8_t i = 0; i < MIDI_CHANNEL_COUNT; ++i) {            // this loop will go through all the channels looking for the best match, starting from
                                                                  // the same channel as the input, this helps keeping channel numbers the same if possible
        channel_t out_channel = (in_channel + i) % MIDI_CHANNEL_COUNT;
        midi_channels_bitmap_t out_channel_mask = (1 << out_channel);

        if ((out_channels_bitmap & out_channel_mask) == 0) { // choose only from the allowed channels
            continue;
        }

        output_channel_t* p_output_channel = &output_channels[out_port][out_channel];

        // if the device can play only one program per channel (and/or switching
        // a program causes hiccups or glitches) we only consider a channel with
        // a different program when there is at most one note playing there, and
        // if there is one, it is playing long enough to be evicted

        if (p_device->monotimbral_channels && (p_output_channel->out_program != out_program)) {

            note_entry_id_t last_note_entry_id = p_device_state->channels[out_channel].last_note_entry_id;

            switch (p_device_state->channels[out_channel].notes_playing) {
                case 1:
                    if (VALID_NOTE_ENTRY_ID(last_note_entry_id)) {
                        if (get_note_age(last_note_entry_id) >= MIN_REPLACEABLE_NOTE_AGE) {
                            break; // the existing note will be evicted
                        }
                        else {
                            continue; // the already playing note may not yet be evicted
                        }
                    }
                    else {
                        continue; // we know there is just one one playing, but which note it is we no longer do
                    }
                case 0:
                    break;
                default:
                    continue;
            }
        }

        // if the device can't play more than N notes on the same channel, similar logic applies,
        // only now the last note can be turned off regardless of whether there are more before it,
        // ideally we would want to turn off the oldest note, but doing so would require an expensive
        // note enumeration

        if (
            (p_device->max_notes_per_channel > 0) &&
            (p_device_state->channels[out_channel].notes_playing == p_device->max_notes_per_channel)
        ) {
            note_entry_id_t last_note_entry_id = p_device_state->channels[out_channel].last_note_entry_id;
            if (
                !VALID_NOTE_ENTRY_ID(last_note_entry_id) ||
                (get_note_age(last_note_entry_id) < MIN_REPLACEABLE_NOTE_AGE)
            ) {
                continue;
            }
        }

        // see if a note with the same number is already playing on that channel, and if yes, then whether it can be replaced

        note_entry_id_t same_note_entry_id = p_output_channel->note_entry_lookup[out_note_index];
        uint8_t same_note_age = 0;

        if (VALID_NOTE_ENTRY_ID(same_note_entry_id)) {
            same_note_age = get_note_age(same_note_entry_id);
            if ((same_note_age < MIN_REPLACEABLE_NOTE_AGE) && IS_MELODIC_PROGRAM(out_program)) { // percussion notes can re-attack at will
                continue;
            }
        }

        // this output channel was never associated with any input channel

        if (!VALID_CHANNEL(pristine_out_channel) && (p_output_channel->associated_in_channels == 0)) {
            pristine_out_channel = out_channel;
        }

        // this output channel has only ever been associated with this input channel

        if (!VALID_CHANNEL(exclusive_out_channel)) {
            if (p_output_channel->associated_in_channels == in_channel_mask) {
                exclusive_out_channel = out_channel;
                break; // can't get better than that, stop searching
            }
        }

        // this output channel was at some point associated with this input channel

        if ((p_output_channel->associated_in_channels & in_channel_mask) != 0) {
            in_channel_was_associated = true;
        }

        // now differentiate between the cases when the output channel is set to the required program or to a different one

        if (p_output_channel->out_program == out_program) { // same program, no program change would be necessary if we pick this channel
            if (VALID_NOTE_ENTRY_ID(same_note_entry_id)) {
                if (same_note_age > same_program_note_age) { // find the channel with the oldest note
                    same_program_with_note = out_channel;
                    same_program_note_age = same_note_age;
                }
            }
            else {
                same_program_without_note |= out_channel_mask;
            }
        }
        else { // a different program, program change would be necessary if we pick this channel
            if (VALID_NOTE_ENTRY_ID(same_note_entry_id)) {
                if (same_note_age > diff_program_note_age) { // find the channel with the oldest note
                    diff_program_with_note = out_channel;
                    diff_program_note_age = same_note_age;
                }
            }
            else {
                diff_program_without_note |= out_channel_mask;
            }
        }

    } // for

    // now we pick the best output channel using all the information that we have collected in the loop

    // in order of preference

    if (VALID_CHANNEL(exclusive_out_channel)) { // the channel which was only ever associated with the same input channel

        associated_out_channel = exclusive_out_channel;
    }
    else if (VALID_CHANNEL(pristine_out_channel) && !in_channel_was_associated) { // a previously unused output channel for a previously unused input channel

        associated_out_channel = pristine_out_channel;
    }
    else if (same_program_without_note != 0) { // one of the channels on the same program where the same note is not playing

        associated_out_channel = select_random_channel(same_program_without_note);
    }
    else if (diff_program_without_note != 0) { // one of the channels on a different program where the same note is not playing

        associated_out_channel = select_random_channel(diff_program_without_note);
    }
    else if (VALID_CHANNEL(same_program_with_note)) { // the channel on the same program where the same note has been playing for the longest time

        associated_out_channel = same_program_with_note;
    }
    else if (VALID_CHANNEL(diff_program_with_note)) { // the channel on a different program where the same note has been playing for the longest time

        associated_out_channel = diff_program_with_note;
    }
    else { // sadly, it could so happen that we find no suitable channel

        return INVALID_CHANNEL;
    }

    evar_assert(VALID_CHANNEL(associated_out_channel));

    output_channel_t* p_associated_output_channel = &output_channels[out_port][associated_out_channel];

    // if there is a note with the same number playing on the selected channel, it has to be turned off

    note_entry_id_t same_note_entry_id = p_associated_output_channel->note_entry_lookup[out_note_index];

    if (VALID_NOTE_ENTRY_ID(same_note_entry_id)) {
        out_note_off(p_context, same_note_entry_id, out_port, 0);
    }

    // if the device can play only one program per channel and there already is
    // (exactly one) note playing there on a different program, we turn it off

    if (p_device->monotimbral_channels && (p_associated_output_channel->out_program != out_program)) {

        evar_assert(p_device_state->channels[associated_out_channel].notes_playing <= 1);

        if (p_device_state->channels[associated_out_channel].notes_playing == 1) {
            note_entry_id_t last_note_entry_id = p_device_state->channels[associated_out_channel].last_note_entry_id;
            evar_assert(get_note_age(last_note_entry_id) >= MIN_REPLACEABLE_NOTE_AGE);
            out_note_off(p_context, last_note_entry_id, out_port, 0);
        }
    }

    // if the device can't play more than N notes on the same channel, and we are
    // already at the limit, the last note on the selected channel is turned off

    if (
        (p_device->max_notes_per_channel > 0) &&
        (p_device_state->channels[associated_out_channel].notes_playing == p_device->max_notes_per_channel)
    ) {
        note_entry_id_t last_note_entry_id = p_device_state->channels[associated_out_channel].last_note_entry_id;
        evar_assert(VALID_NOTE_ENTRY_ID(last_note_entry_id));
        out_note_off(p_context, last_note_entry_id, out_port, 0);
    }

    // finally, all the preparatory work is done and we can associate
    // the channels (which requires a lot of additional work by itself)

    associate_channels(
        p_context,
        in_channel,
        in_program,
        out_port,
        associated_out_channel,
        out_program
    );

    // now, that was easy, wasn't it ?

    return associated_out_channel;
}

/*
 * This is called in response to an incoming "note on" message and does all the heavy lifting.
 */
static void handle_note_on(
    void* p_context,
    midi_channel_t in_channel,
    midi_note_number_t note_number,
    data_byte_t velocity
) {

    if ((note_number < MIDI_LOWEST_NOTE) || (note_number > MIDI_HIGHEST_NOTE)) {
        return;
    }

    // if the same note has been previously initiated by the same channel,
    // it is turned off completely before proceeding, as if "note off"
    // was received before it

    handle_note_off(p_context, in_channel, note_number, 0); // if there was no such note, nothing happens

    if (velocity == 0) { // if this was a disguised request to turn
        return;          // the note off, nothing else is to be done
    }

    // we proceed to initiate a new note

    input_channel_t* p_input_channel = &input_channels[in_channel];

    // reserve a new entry in the note entry table

    note_entry_id_t note_entry_id = allocate_note_entry();
    if (!VALID_NOTE_ENTRY_ID(note_entry_id)) {
        return; // note entry table is full, maximum number of notes has been reached
    }

    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    // register the time at which the note has been received, this will be used
    // to track durations and used to decide whether a note has sounded long enough

    p_note_entry->timestamp = evar_current_timestamp;

    // put the input channel reference to the note entry, this in unconditional
    // by the fact that the note with that number has been received from that channel

    // every note will be also imprinted with the original program
    // of the input channel at the moment of its reception

    program_t in_program = p_input_channel->in_program;
    evar_assert(VALID_PROGRAM(in_program));

    note_t in_note = note_number;

    // the input route of the note will not change from these for its entire duration

    p_note_entry->in.channel = in_channel;
    p_note_entry->in.program = in_program;
    p_note_entry->in.note    = in_note;

    // put the note reference to the input channel index

    uint8_t in_note_index = in_note - MIDI_LOWEST_NOTE;

    evar_assert(!VALID_NOTE_ENTRY_ID(p_input_channel->note_entry_lookup[in_note_index]));
    p_input_channel->note_entry_lookup[in_note_index] = note_entry_id;

    // every note will possibly be routed to each of the output devices

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        // is the note routed through this device at all (this is expressed in terms of the original input GM program/note)

        midiplan_device_routing_t* p_device_routing = &devices[out_port].routing;

        if (IS_MELODIC_PROGRAM(in_program)) {
            if ((p_device_routing->melodic_programs_bitmap[in_program >> 5] & (1 << (in_program & 0x1F))) == 0) {
                continue;
            }
        }
        else if (IS_PERCUSSION_PROGRAM(in_program)) {
            if ((p_device_routing->percussion_notes_bitmap[in_note >> 5] & (1 << (in_note & 0x1F))) == 0) {
                continue;
            }
        }

        // what happens to the note after that is defined by the device capabilities and its current state

        const midiplan_device_t* p_device = devices[out_port].p_device;

        // translate the original program/note pair into a device-specific pair

        program_t out_program;
        note_t out_note;
        data_byte_t out_velocity;

        if (!translate_note(p_device, in_program, in_note, velocity, &out_program, &out_note, &out_velocity)) {
            continue; // the device does not support such note
        }

        evar_assert(VALID_PROGRAM(out_program) && VALID_NOTE(out_note) && VALID_DATA_BYTE(out_velocity) && (out_velocity > 0));

        if ((out_note < MIDI_LOWEST_NOTE) || (out_note > MIDI_HIGHEST_NOTE)) {
            continue; // the translated note is so low or so high that we can't use it
        }

        uint8_t out_note_index = out_note - MIDI_LOWEST_NOTE;

        // in case there are several identical devices playing, each
        // could take only a fraction of the programs / percussion notes

        midiplan_device_bonding_t* p_device_bonding = &devices[out_port].bonding;

        if (p_device_bonding->device_count > 1) {

            // the problem that we are trying to solve here is that the same program can be
            // invoked on different input channels, and we would like to have them spread
            // across different bonded devices, thus increasing polyphony and multitimbrality

            // two things to notice here:
            // 1. it often happens that the same input program is played on several input
            //    channels in parallel and we could route those notes to different devices
            // 2. what causes multitimbrality collisions are the *output* programs, because
            //    typically there are multiple input programs mapped to the same output program

            uint8_t bonding_key;

            if (IS_MELODIC_PROGRAM(out_program)) {
                // therefore we use a randomizing function of the input channel and
                // the output program, both are deterministic and fixed for the note
                bonding_key = device_bonding_hash(in_channel, out_program);
            }
            else {
                evar_assert(IS_PERCUSSION_PROGRAM(out_program));
                // percussion notes will use simple note number modulo distribution
                bonding_key = out_note;
            }

            if ((bonding_key % p_device_bonding->device_count) != p_device_bonding->device_index) {
                continue;
            }
        }

        // we are considering actually sending a note to a device, this is the moment
        // when we cue in the initialization sequence for the device

        midiplan_device_state_t* p_device_state = &devices[out_port].state;

        if (p_device_state->initialization_pending) {
            send_initialization_sequence(p_context, out_port);
            p_device_state->initialization_pending = false;
        }

        // check that the device still has capacity to play another note on this program

        if (!note_can_be_accepted(p_context, out_port, out_program)) {
            continue; // the device has exceeded its limits and will not be able to play this note without hiccup
        }

        // this is the set of output channels on which this note can be played

        midi_channels_bitmap_t out_channels_bitmap = get_note_channels(p_device, out_program, out_note);
        if (out_channels_bitmap == 0) {
            continue;
        }

        // associate the input channel with one of the output channels capable of playing this note

        channel_t out_channel = associate_out_channel(
            p_context,
            in_channel,
            in_program,
            out_port,
            out_channels_bitmap,
            out_program,
            out_note
        );

        if (!VALID_CHANNEL(out_channel)) { // could not find an output channel to associate
            continue;
        }

        output_channel_t* p_output_channel = &output_channels[out_port][out_channel];

        // expecting the associated output channel to be associated

        evar_assert(p_output_channel->out_program == out_program);
        evar_assert(p_output_channel->associated_in_channel == in_channel);

        // expecting no same note playing on the selected channel already,
        // that is how channel association logic should have worked

        evar_assert(!VALID_NOTE_ENTRY_ID(p_output_channel->note_entry_lookup[out_note_index]));

        // the translated output route will be kept to avoid having to translate it again

        note_route_t* p_out_route = &p_note_entry->out[out_port];

        p_out_route->channel = out_channel;
        p_out_route->program = out_program;
        p_out_route->note    = out_note;

        // put the new note reference to the lookup index for the output channel

        p_output_channel->note_entry_lookup[out_note_index] = note_entry_id;

        // the note route has been fully updated for this device, account for the note being turned on

        account_note_on(note_entry_id, out_port);

        // send "note on" to the device

        send_note_on_sequence(
            p_context,
            out_port,
            out_channel,
            out_note,
            out_velocity
        );
    }
}

/*
 * "Key pressure" is an aftertouch message, it references a note that
 * has been turned on before, and presumably still sounds. This message
 * is propagated to the note output channels but does not change any state.
 * Notice that the output channels could have already been dissociated
 * from the originating input channel, but the note will still be adjusted.
 */
static void handle_key_pressure(
    void* p_context,
    midi_channel_t in_channel,
    midi_note_number_t note_number,
    data_byte_t pressure
) {

    if ((note_number < MIDI_LOWEST_NOTE) || (note_number > MIDI_HIGHEST_NOTE)) {
        return;
    }

    input_channel_t* p_input_channel = &input_channels[in_channel];

    // the note being adjusted is specified in terms of its input route,
    // i.e. the input channel and the original note number

    note_entry_id_t note_entry_id = p_input_channel->note_entry_lookup[note_number - MIDI_LOWEST_NOTE];
    if (!VALID_NOTE_ENTRY_ID(note_entry_id)) {
        return;
    }

    note_entry_t* p_note_entry = &note_entries[note_entry_id];
    evar_assert(p_note_entry->in.note == note_number && p_note_entry->in.channel == in_channel);

    // the message is propagated to every output channel with which the input channel is currently associated

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        channel_t out_channel = p_note_entry->out[out_port].channel;
        if (!VALID_CHANNEL(out_channel)) {
            continue;
        }

        const midiplan_device_t* p_device = devices[out_port].p_device;
        if (!key_pressure_supported(p_device)) {
            continue;
        }

        send_message(
            p_context,
            out_port,
            out_channel,
            MIDI_MESSAGE_KEY_PRESSURE,
            p_note_entry->out[out_port].note,
            pressure
        );
    }
}

/*
 * This is called in response to "all sound off" channel mode message.
 * The same message is propagated to every output channel with which we
 * have associated, the notes remain active, the program and the state
 * of controllers also remain unchanged. If the device decides to ignore this,
 * the notes will still be sounding just as before, which is in line with the
 * specification:
 * > This message is not a replacement for the All Notes Off message,
 * > Note-Off messages, Hold Off, or Master Volume Off. The correct
 * > procedure of sending a Note-Off for each and every Note-On must
 * > still be followed.
 */
static void handle_all_sound_off(
    void* p_context,
    midi_channel_t in_channel
) {

    midi_channels_bitmap_t in_channel_mask = (1 << in_channel);

    // iterate over every channel on every output port

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {

            output_channel_t* p_output_channel = &output_channels[out_port][out_channel];

            // propagate the message to all output channels that have ever been associated with this input channel

            if ((p_output_channel->associated_in_channels & in_channel_mask) == 0) {
                 continue;
            }

            // send "all sound off" to the device

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CONTROL_CHANGE,
                MIDI_CHANNEL_MODE_ALL_SOUND_OFF,
                0
            );
        }
    }
}

/*
 * This is called in response to "reset all controllers" channel mode message.
 * The same message is propagated to every output channel with which we have
 * associated, the tracked controller state is deleted. The notes still sound,
 * the programs and the channel associations also remain intact.
 */
static void handle_reset_all_controllers(
    void* p_context,
    midi_channel_t in_channel
) {

    midi_channels_bitmap_t in_channel_mask = (1 << in_channel);

    // iterate over every channel on every output port

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {

            output_channel_t* p_output_channel = &output_channels[out_port][out_channel];

            // propagate reset message to all output channels that have ever been associated with this input channel

            if ((p_output_channel->associated_in_channels & in_channel_mask) == 0) {
                 continue;
            }

            // send "reset all controllers" to the device

            send_message(
                p_context,
                out_port,
                out_channel,
                MIDI_MESSAGE_CONTROL_CHANGE,
                MIDI_CHANNEL_MODE_RESET_ALL_CONTROLLERS,
                0
            );

        }
    }

    // delete the tracked controller values for that channel

    delete_controller_values(in_channel);
}

/*
 * This structure contains contextual parameters passed
 * to the all_notes_off_callback below.
 */
typedef struct {
    void* p_context;
    midi_channel_t in_channel;
    note_entry_id_t note_entry_ids[MAX_NOTE_ENTRIES];
    uint8_t note_entry_ids_count;
} all_notes_off_context_t;

/*
 * This callback is called for each active note being turned off
 * during processing the "all notes off" command.
 */
static void all_notes_off_callback(
    void* p_callback_context,
    note_entry_id_t note_entry_id
) {

    all_notes_off_context_t* p_all_notes_off_context = (all_notes_off_context_t*)p_callback_context;
    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    evar_assert(VALID_CHANNEL(p_note_entry->in.channel));
    evar_assert(VALID_NOTE(p_note_entry->in.note));

    if (p_note_entry->in.channel != p_all_notes_off_context->in_channel) {
        return;
    }

    in_note_off(p_all_notes_off_context->p_context, note_entry_id, 0);

    // notice that the note entry can't be deallocated here, as it would break the enumeration,
    // instead we collect the turned off entries in the context, and the caller will deallocate
    // them after enumeration returns

    evar_assert(p_all_notes_off_context->note_entry_ids_count < MAX_NOTE_ENTRIES);
    p_all_notes_off_context->note_entry_ids[p_all_notes_off_context->note_entry_ids_count++] = note_entry_id;
}

/*
 * This is called in response to "all notes off" channel mode message.
 * Every note currently active on that input channel is turned off as if
 * a "note off" message is received for it. The state of controllers
 * and the programs remain unchanged.
 */
static void handle_all_notes_off(
    void* p_context,
    midi_channel_t in_channel
) {

    all_notes_off_context_t all_notes_off_context = {
        .p_context            = p_context,
        .in_channel           = in_channel,
        .note_entry_ids       = { INVALID_NOTE_ENTRY_ID },
        .note_entry_ids_count = 0
    };

    enumerate_note_entries(&all_notes_off_context, all_notes_off_callback);

    // the callback used in_note_off call, therefore the note entries
    // are all blank but still allocated, here we deallocate them

    evar_assert(all_notes_off_context.note_entry_ids_count <= MAX_NOTE_ENTRIES);

    for (uint8_t i = 0; i < all_notes_off_context.note_entry_ids_count; ++i) {

        deallocate_note_entry(all_notes_off_context.note_entry_ids[i]);
    }

    // assuming that between the tracks the client software is sending a stream
    // of "all notes off" messages on all channels, when all notes are turned off
    // that way, it is the moment we reset all the statistics and associations

    if (no_allocated_note_entries()) {

        reset_channel_associations();
        reset_program_statistics();

        for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

            midiplan_device_state_t* p_device_state = &devices[out_port].state;
            reset_device_state(p_device_state);
        }
    }
}

/*
 * "Channel mode" is a separate family of channel and/or system-wide
 * messages that are borrowing namespace from control change messages.
 */
static void handle_channel_mode(
    void* p_context,
    midi_channel_t in_channel,
    midi_control_number_t channel_mode
) {
    switch (channel_mode) {
        case MIDI_CHANNEL_MODE_ALL_SOUND_OFF:
            handle_all_sound_off(p_context, in_channel);
            break;
        case MIDI_CHANNEL_MODE_RESET_ALL_CONTROLLERS:
            handle_reset_all_controllers(p_context, in_channel);
            break;
        case MIDI_CHANNEL_MODE_LOCAL_CONTROL_ON_OFF:
            break;
        case MIDI_CHANNEL_MODE_ALL_NOTES_OFF:
            handle_all_notes_off(p_context, in_channel);
            break;
        case MIDI_CHANNEL_MODE_OMNI_OFF:
        case MIDI_CHANNEL_MODE_OMNI_ON:
        case MIDI_CHANNEL_MODE_MONO_ON:
        case MIDI_CHANNEL_MODE_POLY_ON:
            break;
        default:
            break;
    }
}

/*
 * Controller changes are propagated to every associated output channel
 * and after that the internally tracked state of the controller is updated.
 */
static void handle_control_change(
    void* p_context,
    midi_channel_t in_channel,
    midi_control_number_t control_number,
    data_byte_t control_value
) {

    // mode channel messages are not control messages and are handled separately

    if (IS_MIDI_CHANNEL_MODE(control_number)) {
        handle_channel_mode(p_context, in_channel, control_number);
        return;
    }

    // ignore bank select

    if ((control_number == MIDI_CONTROL_BANK_SELECT) || (control_number == MIDI_CONTROL_LSB_FOR_MSB_00)) {
        return;
    }

    // update the current state of program controllers and send it to all associated channels

    input_channel_t* p_input_channel = &input_channels[in_channel];

    controller_value_t* p_controller_value;

    if (control_number < 0x20) {

        p_controller_value = get_controller_value(in_channel, p_input_channel->in_program, control_number);
        p_controller_value->msb = control_value;
        p_controller_value->lsb = 0;

        propagate_control_change(
            p_context,
            in_channel,
            control_number,
            p_controller_value->msb,
            p_controller_value->lsb
        );
    }
    else if (control_number < 0x40) {

        p_controller_value = get_controller_value(in_channel, p_input_channel->in_program, control_number & 0x1F);
        p_controller_value->lsb = control_value;

        if (VALID_DATA_BYTE(p_controller_value->msb)) {
            propagate_control_change(
                p_context,
                in_channel,
                control_number,
                p_controller_value->msb,
                p_controller_value->lsb
            );
        }
    }
    else if (control_number < 0x78) {

        p_controller_value = get_controller_value(in_channel, p_input_channel->in_program, control_number);
        p_controller_value->value = control_value;

        propagate_control_change(
            p_context,
            in_channel,
            control_number,
            p_controller_value->value,
            INVALID_DATA_BYTE
        );
    }
}

/*
 * "Program change" has a different logic from any other controller change.
 * No messages are sent, only the program on the channel is changed and
 * all the channel associations are broken.
 */
static void handle_program_change(
    void* p_context,
    midi_channel_t in_channel,
    midi_program_number_t program_number
) {

    EVAR_UNUSED(p_context);

    // attempt to change a program on the percussion channel is ignored

    if (in_channel == GM_PERCUSSION_CHANNEL) {
        return;
    }

    input_channel_t* p_input_channel = &input_channels[in_channel];
    evar_assert(VALID_PROGRAM(p_input_channel->in_program)); // there is always some program active

    // attempt to change to the same program is ignored

    if (program_number == p_input_channel->in_program) {
        return;
    }

    // update the channel program

    p_input_channel->in_program = program_number;

    // break all associations from the input channel side, will be reassociated upon the next note,
    // the currently associated output channels still keep their references to this input channel,
    // and possibly are reassociated later

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
        p_input_channel->associated_out_channels[out_port] = INVALID_CHANNEL;
    }
}

/*
 * "Channel pressure" has the same logic as any other channel controller change.
 */
static void handle_channel_pressure(
    void* p_context,
    midi_channel_t in_channel,
    data_byte_t pressure
) {

    // update the current state of per-program controllers

    input_channel_t* p_input_channel = &input_channels[in_channel];

    evar_assert(VALID_PROGRAM(p_input_channel->in_program));

    controller_value_t* p_pressure =
        get_controller_value(in_channel, p_input_channel->in_program, CONTROL_PRESSURE);

    p_pressure->value = pressure;

    // send the same message to all associated channels

    propagate_control_change(
        p_context,
        in_channel,
        CONTROL_PRESSURE,
        p_pressure->value,
        INVALID_DATA_BYTE
    );
}

/*
 * "Pitch bend" has the same logic as any other channel controller change.
 */
static void handle_pitch_bend(
    void* p_context,
    midi_channel_t in_channel,
    data_byte_t pitch_bend_lsb,
    data_byte_t pitch_bend_msb
) {

    // update the current state of per-program controllers

    input_channel_t* p_input_channel = &input_channels[in_channel];

    evar_assert(VALID_PROGRAM(p_input_channel->in_program));

    controller_value_t* p_pitch_bend =
        get_controller_value(in_channel, p_input_channel->in_program, CONTROL_PITCH_BEND);

    p_pitch_bend->msb = pitch_bend_msb;
    p_pitch_bend->lsb = pitch_bend_lsb;

    // send the same message to all associated channels

    propagate_control_change(
        p_context,
        in_channel,
        CONTROL_PITCH_BEND,
        p_pitch_bend->msb,
        p_pitch_bend->lsb
    );
}

/*
 * Special messages are broadcast to all output ports. System exclusive messages are
 * at this point still represented as a sequence of separate single byte "messages",
 * it is the output UART which will reassemble them into a stream of bytes.
 */
static void handle_special(
    void* p_context,
    status_byte_t status_byte,
    data_byte_t data_byte_1
) {

// this is a quick and dirty fix to disable incoming
// system exclusive messages and will be reworked
#ifndef SYSTEM_EXCLUSIVE_PASSTHROUGH
    EVAR_UNUSED(data_byte_1);
#endif

    midi_message_t midi_message = {
        .status_byte = status_byte,
        .data_byte_1 = INVALID_DATA_BYTE,
        .data_byte_2 = INVALID_DATA_BYTE
    };

    if (IS_MIDI_REAL_TIME_MESSAGE(status_byte)) {
        broadcast_message(p_context, midi_message);
    }
    else if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {
#ifdef SYSTEM_EXCLUSIVE_PASSTHROUGH
        midi_message.data_byte_1 = data_byte_1;
        broadcast_message(p_context, midi_message);
#endif
    }
    else if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {
#ifdef SYSTEM_EXCLUSIVE_PASSTHROUGH    
        broadcast_message(p_context, midi_message);
#endif
    }
    else {
        // all the other special messages are ignored
    }
}

/*
 * Processes a MIDI message incoming from the input UART.
 */
void midiplan_handle_message(
    void* p_context,
    midi_message_t midi_message
) {

    midi_channel_t in_channel = MIDI_MESSAGE_CHANNEL(midi_message.status_byte);

    switch (MIDI_MESSAGE_TYPE(midi_message.status_byte)) {
        case MIDI_MESSAGE_NOTE_OFF:
            return handle_note_off(p_context, in_channel, midi_message.data_byte_1, midi_message.data_byte_2);
        case MIDI_MESSAGE_NOTE_ON:
            return handle_note_on(p_context, in_channel, midi_message.data_byte_1, midi_message.data_byte_2);
        case MIDI_MESSAGE_KEY_PRESSURE:
            return handle_key_pressure(p_context, in_channel, midi_message.data_byte_1, midi_message.data_byte_2);
        case MIDI_MESSAGE_CONTROL_CHANGE:
            return handle_control_change(p_context, in_channel, midi_message.data_byte_1, midi_message.data_byte_2);
        case MIDI_MESSAGE_PROGRAM_CHANGE:
            return handle_program_change(p_context, in_channel, midi_message.data_byte_1);
        case MIDI_MESSAGE_CHANNEL_PRESSURE:
            return handle_channel_pressure(p_context, in_channel, midi_message.data_byte_1);
        case MIDI_MESSAGE_PITCH_BEND:
            return handle_pitch_bend(p_context, in_channel, midi_message.data_byte_1, midi_message.data_byte_2);
        case MIDI_MESSAGE_SPECIAL:
            return handle_special(p_context, midi_message.status_byte, midi_message.data_byte_1);
    }
}
