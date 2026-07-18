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
#include "midi_input.h"

/*
 * Initializes the logical MIDI byte stream state to "unknown".
 */
void reset_midi_input_state(midi_input_state_t* p_midi_input_state) {
    p_midi_input_state->synchronized        = false;
    p_midi_input_state->status_byte         = INVALID_STATUS_BYTE;
    p_midi_input_state->data_bytes[0]       = INVALID_DATA_BYTE;
    p_midi_input_state->data_bytes[1]       = INVALID_DATA_BYTE;
    p_midi_input_state->running_status      = INVALID_STATUS_BYTE;
    p_midi_input_state->expected_data_bytes = 0;
    p_midi_input_state->received_data_bytes = 0;
}

/*
 * The purpose of this function is to coalesce a stream of input UART bytes into logical MIDI messages,
 * which always start with a status byte and have between zero and two data bytes. The moment a MIDI
 * message is completed, it is sent to the next stage of processing.
 *
 * There is one tricky case of a system exclusive message terminated not by EOX, but by the next
 * message's status byte, which is permitted. In this case, the implied EOX will be sent, but
 * the status byte will have to be not consumed, false is returned and the caller will retry.
 *
 * System exclusive messages are sent as as a sequence of single-byte wrapper "messages" and are 
 * therefore unlimited in size from this code's perspective. Any other message is sent individually
 * in full, running status is translated into explicit status bytes.
 *
 * The only filtering performed at this level is ignoring undefined messages.
 *
 * Returns true if this byte if this byte has resulted in completion and production of a MIDI message 
 * into the caller's buffer.
 */
bool handle_midi_input_byte(
    midi_input_state_t* p_midi_input_state,
    unsigned char input_byte,
    midi_message_t* p_midi_message,
    bool* p_consume_input_byte
) {

    p_midi_message->data_byte_1 = INVALID_DATA_BYTE;
    p_midi_message->data_byte_2 = INVALID_DATA_BYTE;
    
    *p_consume_input_byte = true;

    // real time messages are single bytes which are recognized separately and sent out of band,
    // even before synchronization or in the middle of another message being transmitted

    if (IS_MIDI_REAL_TIME_MESSAGE(input_byte)) {
        if (IS_MIDI_UNDEFINED_MESSAGE(input_byte)) { // real time undefined are easy to ignore because they are always one byte
            return false;
        }
        p_midi_message->status_byte = input_byte;
        return true;
    }

    // after a reset, data bytes and EOX are skipped before the first real status byte is received

    if (!p_midi_input_state->synchronized) {
        if (!VALID_STATUS_BYTE(input_byte) || input_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {
            return false; // skip this byte, keep waiting for a status byte that begins a new message
        }
        p_midi_input_state->synchronized = true;
    }

    // receiving a system exclusive is done differently from any other message,
    // because its size is not known and is theoretically unbounded

    if (p_midi_input_state->status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {

        if (VALID_DATA_BYTE(input_byte)) { // received another data byte in the system exclusive message being streamed
            
            p_midi_message->status_byte = MIDI_MESSAGE_SYSTEM_EXCLUSIVE;
            p_midi_message->data_byte_1 = input_byte;
        }
        else {

            // a system exclusive message can be terminated by any status byte,
            // either by its own EOX or a status byte of the next message

            p_midi_message->status_byte = MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END; // either way we send an honest EOX

            // from the receiver's point of view, the system exclusive message is now over

            p_midi_input_state->status_byte = INVALID_STATUS_BYTE;
            p_midi_input_state->running_status = INVALID_STATUS_BYTE;

            // if a system exclusive was terminated by a status byte of the next message,
            // that status byte will be handled again and consumed at the next pass,
            // but if it was EOX that terminated it, it is consumed right away

            *p_consume_input_byte = input_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;
        }

        return true; // every byte of a system exclusive results in a separate MIDI message being produced
    }

    // now we are in the territory of a regular MIDI message being received
    
    if (VALID_STATUS_BYTE(input_byte)) {

        if (VALID_STATUS_BYTE(p_midi_input_state->status_byte)) { // status byte received in the middle of the previous message
            reset_midi_input_state(p_midi_input_state);           // force resync
            return false;
        }

        p_midi_input_state->status_byte = input_byte;

        // if we received a SOX, send it in a separate message, just like as any following system exclusive byte would

        if (input_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {
            p_midi_message->status_byte = MIDI_MESSAGE_SYSTEM_EXCLUSIVE;
            return true;
        }

        // otherwise we are receiving a regular message, determine 
        // the number of data bytes that are expected for its kind

        uint8_t expected_data_bytes = get_expected_data_bytes(p_midi_input_state->status_byte);
        if (expected_data_bytes == EXPECTED_DATA_BYTES_UNKNOWN) { // and if it is an undefined message
            reset_midi_input_state(p_midi_input_state);           // force resync
            return false;
        }

        p_midi_input_state->expected_data_bytes = expected_data_bytes;
        p_midi_input_state->received_data_bytes = 0;
        
    }
    else if (VALID_DATA_BYTE(input_byte)) {

        if (!VALID_STATUS_BYTE(p_midi_input_state->status_byte)) { // status byte was not received explicitly, but perhaps running status is present

            if (!VALID_STATUS_BYTE(p_midi_input_state->running_status)) { // no running status
                reset_midi_input_state(p_midi_input_state);               // force resync
                return false;
            }

            // inherit the running status as if it was received explicitly,
            // no need to check for validity this time, because an undefined
            // message could not have become a running status

            p_midi_input_state->status_byte = p_midi_input_state->running_status;
            p_midi_input_state->expected_data_bytes = get_expected_data_bytes(p_midi_input_state->status_byte);
            p_midi_input_state->received_data_bytes = 0;
        }

        // the data byte is buffered
        
        p_midi_input_state->data_bytes[p_midi_input_state->received_data_bytes++] = input_byte;
    }

    // check to see if all the data bytes expected for this message have been received (possibly zero)

    if (p_midi_input_state->received_data_bytes < p_midi_input_state->expected_data_bytes) { // keep waiting for more data bytes
        return false;
    }

    p_midi_message->status_byte = p_midi_input_state->status_byte;
    if (VALID_DATA_BYTE(p_midi_input_state->data_bytes[0])) {
        p_midi_message->data_byte_1 = p_midi_input_state->data_bytes[0];
        if (VALID_DATA_BYTE(p_midi_input_state->data_bytes[1])) {
            p_midi_message->data_byte_2 = p_midi_input_state->data_bytes[1];
        }
    }

    // check to see if a message of this kind can become a running status (only a channel message can)
    
    if (IS_MIDI_CHANNEL_MESSAGE(p_midi_input_state->status_byte)) {
        p_midi_input_state->running_status = p_midi_input_state->status_byte;
    }
    else {
        p_midi_input_state->running_status = INVALID_STATUS_BYTE;
    }

    p_midi_input_state->status_byte = INVALID_STATUS_BYTE; // we have reached the end of a message

    return true;
}
