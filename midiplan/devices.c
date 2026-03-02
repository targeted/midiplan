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

#include <midiplan/devices.h>

midiplan_devices_t devices;

static void configure_bonding(void);

void configure_devices(void) {

    devices[MIDI_OUT_PORT_1].p_device = &gm_device;
    devices[MIDI_OUT_PORT_1].routing  = route_all;

    devices[MIDI_OUT_PORT_2].p_device = &null_device;
    devices[MIDI_OUT_PORT_2].routing  = route_none;

    devices[MIDI_OUT_PORT_3].p_device = &null_device;
    devices[MIDI_OUT_PORT_3].routing  = route_none;

    devices[MIDI_OUT_PORT_4].p_device = &null_device;
    devices[MIDI_OUT_PORT_4].routing  = route_none;

    configure_bonding();

}

/*
 * The current implementation of bonding is 1 out of N modulo-based,
 * across the namespace of out programs/notes. This can be calculated
 * automatically, knowing what kind of device is on which port.
 */
static void configure_bonding(void) {

    for (midi_out_port_t i = MIDI_OUT_PORT_1; i < MIDI_OUT_PORT_COUNT; ++i) {
        devices[i].bonding.device_index = 0;
        devices[i].bonding.device_count = 1;
    }
    
    for (midi_out_port_t i = MIDI_OUT_PORT_1; i < MIDI_OUT_PORT_COUNT; ++i) {
        for (midi_out_port_t j = 0; j < MIDI_OUT_PORT_COUNT; ++j) {
            if (
                (i != j) &&
                (devices[j].p_device == devices[i].p_device) &&
                (devices[j].p_device != &gm_device) && // the generic devices are segregated
                (devices[j].p_device != &null_device)  // and not automatically bonded
            ) {
                if (i < j) {
                    devices[j].bonding.device_index += 1;
                }
                devices[i].bonding.device_count += 1;
            }
        }
    }
}

void initialize_device_states(void) {

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
    
        midiplan_device_state_t* p_device_state = &devices[out_port].state;
    
        p_device_state->melodic_programs_playing = 0;
        p_device_state->melodic_notes_playing = 0;
        
        for (uint8_t i = 0; i < 128 + 1; ++i) {
            p_device_state->melodic_notes_per_program[i] = 0;
        }
        
        p_device_state->percussion_notes_playing = 0;
        
        for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {
            p_device_state->channels[out_channel].notes_playing = 0;
            p_device_state->channels[out_channel].last_note_entry_id = INVALID_NOTE_ENTRY_ID;
        }
        
        reset_device_state(p_device_state);
    }
}
