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
#include <midiplan/channels.h>

input_channel_t input_channels[MIDI_CHANNEL_COUNT];
output_channel_t output_channels[MIDI_OUT_PORT_COUNT][MIDI_CHANNEL_COUNT];

/*
 * Initializes the channels structures. This is done once at startup.
 */
void initialize_channels(void) {

    // initialize the input channels

    for (midi_channel_t in_channel = MIDI_CHANNEL_1; in_channel < MIDI_CHANNEL_COUNT; ++in_channel) {
    
        input_channel_t* p_input_channel = &input_channels[in_channel];
    
        p_input_channel->in_program = (in_channel == GM_PERCUSSION_CHANNEL) ? PERCUSSION_PROGRAM : DEFAULT_MELODIC_PROGRAM;

        for (uint8_t i = 0; i < MIDI_NOTE_RANGE; ++i) {
            p_input_channel->note_entry_lookup[i] = INVALID_NOTE_ENTRY_ID;
        }
    }

    // initialize the output channels

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {

            output_channel_t* p_output_channel = &output_channels[out_port][out_channel];
        
            for (uint8_t i = 0; i < MIDI_NOTE_RANGE; ++i) {
                p_output_channel->note_entry_lookup[i] = INVALID_NOTE_ENTRY_ID;
            }
        }
    }
}

/*
 * Clears the associations between the input and output channels, 
 * this is done at startup and every time when every input note
 * has been turned off via "all notes off" command.
 */
void reset_channel_associations(void) {

    // reset the input channels associations

    for (midi_channel_t in_channel = MIDI_CHANNEL_1; in_channel < MIDI_CHANNEL_COUNT; ++in_channel) {
    
        input_channel_t* p_input_channel = &input_channels[in_channel];
        
        for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
            p_input_channel->associated_out_channels[out_port] = INVALID_CHANNEL;
        }
    }

    // reset the output channels associations

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {

        for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {

            output_channel_t* p_output_channel = &output_channels[out_port][out_channel];
        
            p_output_channel->out_program            = INVALID_PROGRAM;
            p_output_channel->associated_in_channel  = INVALID_CHANNEL;
            p_output_channel->associated_in_channels = 0;
        }
    }
}

