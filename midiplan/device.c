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
#include <midiplan/device.h>

midiplan_device_routing_t route_all = {
    .melodic_programs_bitmap = {
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111
    },
    .percussion_notes_bitmap = {
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111
    }
};

midiplan_device_routing_t route_none = {
    .melodic_programs_bitmap = {
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000
    },
    .percussion_notes_bitmap = {
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000
    }
};

midiplan_device_routing_t route_melodic = {
    .melodic_programs_bitmap = {
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111
    },
    .percussion_notes_bitmap = {
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000
    }
};

midiplan_device_routing_t route_percussion = {
    .melodic_programs_bitmap = {
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000,
        0b00000000000000000000000000000000
    },
    .percussion_notes_bitmap = {
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111,
        0b11111111111111111111111111111111
    }
};

/*
 * These pre-calculated lookup tables are used to turn velocity up/down when a note is translated.
 * The first three are +2dB, +4dB, +6dB, the last three are -2dB, -4dB, -6dB,
 * velocity values range from 1 to 128, hence 127 elements in each array.
 */
data_byte_t velocity_curves[6][127] = {
    {  3,   5,   6,   8,  10,  11,  13,  14,  16,  17,  18,  19,  21,  22,  23,  24,  26,  27,  28,  29,  30,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  76,  77,  78,  79,  80,  81,  82,  83,  84,  84,  85,  86,  87,  88,  89,  90,  91,  91,  92,  93,  94,  95,  96,  97,  97,  98,  99, 100, 101, 102, 103, 103, 104, 105, 106, 107, 108, 108, 109, 110, 111, 112, 112, 113, 114, 115, 116, 117, 117, 118, 119, 120, 121, 121, 122, 123, 124, 125, 125, 126, 127  },
    {  6,   9,  12,  14,  16,  19,  20,  22,  24,  26,  27,  29,  30,  32,  33,  34,  36,  37,  38,  40,  41,  42,  43,  44,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  71,  72,  73,  74,  75,  76,  77,  77,  78,  79,  80,  81,  82,  82,  83,  84,  85,  86,  86,  87,  88,  89,  90,  90,  91,  92,  93,  93,  94,  95,  96,  96,  97,  98,  99,  99, 100, 101, 101, 102, 103, 104, 104, 105, 106, 106, 107, 108, 109, 109, 110, 111, 111, 112, 113, 113, 114, 115, 115, 116, 117, 117, 118, 119, 119, 120, 121, 121, 122, 123, 123, 124, 124, 125, 126, 126, 127  },
    { 11,  16,  19,  22,  25,  28,  30,  32,  34,  36,  37,  39,  41,  42,  44,  45,  46,  48,  49,  50,  52,  53,  54,  55,  56,  57,  58,  60,  61,  62,  63,  64,  65,  66,  67,  68,  68,  69,  70,  71,  72,  73,  74,  75,  76,  76,  77,  78,  79,  80,  80,  81,  82,  83,  83,  84,  85,  86,  86,  87,  88,  89,  89,  90,  91,  91,  92,  93,  94,  94,  95,  96,  96,  97,  98,  98,  99,  99, 100, 101, 101, 102, 103, 103, 104, 104, 105, 106, 106, 107, 107, 108, 109, 109, 110, 110, 111, 112, 112, 113, 113, 114, 114, 115, 115, 116, 117, 117, 118, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124, 124, 125, 125, 126, 126, 127  },
    {  1,   1,   1,   2,   2,   3,   3,   4,   5,   5,   6,   7,   7,   8,   9,   9,  10,  11,  12,  12,  13,  14,  15,  16,  16,  17,  18,  19,  20,  21,  22,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  67,  68,  69,  70,  71,  72,  73,  74,  75,  77,  78,  79,  80,  81,  82,  83,  85,  86,  87,  88,  89,  90,  92,  93,  94,  95,  96,  98,  99, 100, 101, 102, 104, 105, 106, 107, 108, 110, 111, 112, 113, 115, 116, 117, 118, 119, 121, 122, 123, 124, 126, 127  },
    {  1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   3,   3,   3,   4,   4,   5,   5,   6,   6,   7,   7,   8,   8,   9,  10,  10,  11,  12,  12,  13,  14,  14,  15,  16,  16,  17,  18,  19,  20,  20,  21,  22,  23,  24,  25,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  51,  52,  53,  54,  55,  56,  57,  59,  60,  61,  62,  63,  65,  66,  67,  68,  70,  71,  72,  74,  75,  76,  78,  79,  80,  82,  83,  84,  86,  87,  88,  90,  91,  93,  94,  95,  97,  98, 100, 101, 103, 104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124, 125, 127  },
    {  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   3,   3,   3,   4,   4,   4,   5,   5,   5,   6,   6,   7,   7,   8,   8,   9,   9,  10,  10,  11,  11,  12,  13,  13,  14,  15,  15,  16,  17,  17,  18,  19,  20,  21,  21,  22,  23,  24,  25,  26,  27,  28,  28,  29,  30,  31,  32,  33,  34,  35,  37,  38,  39,  40,  41,  42,  43,  44,  46,  47,  48,  49,  51,  52,  53,  54,  56,  57,  58,  60,  61,  62,  64,  65,  67,  68,  70,  71,  73,  74,  76,  77,  79,  80,  82,  84,  85,  87,  89,  90,  92,  94,  95,  97,  99, 101, 102, 104, 106, 108, 110, 112, 113, 115, 117, 119, 121, 123, 125, 127  }
};

/*
 * Used to produce deterministic "random" numbers to pick a device from a bonding set.
 */
uint8_t device_bonding_hash(midi_channel_t channel, program_t program) {

    uint32_t h = (channel << 8) | program;
    h ^= h >> 7;
    h *= 0x9E3779B1;
    h ^= h >> 11;

    return h & 0xff;
}

/*
 * This is called at startup and during handling of "all notes off" after a device has become idle.
 */
void reset_device_state(midiplan_device_state_t* p_device_state) {

    evar_assert(p_device_state->melodic_programs_playing == 0);
    evar_assert(p_device_state->melodic_notes_playing == 0);
    
    for (uint8_t i = 0; i < 128 + 1; ++i) {
        evar_assert(p_device_state->melodic_notes_per_program[i] == 0);
    }
    
    evar_assert(p_device_state->percussion_notes_playing == 0);

    for (midi_channel_t out_channel = MIDI_CHANNEL_1; out_channel < MIDI_CHANNEL_COUNT; ++out_channel) {
        evar_assert(p_device_state->channels[out_channel].notes_playing == 0);
        evar_assert(!VALID_NOTE_ENTRY_ID(p_device_state->channels[out_channel].last_note_entry_id));
    }

    // schedule delayed initialization for the device,
    // the actual transmission will happen at the next note

    p_device_state->initialization_pending = true;
}

/*
 * Returns the set of channels on which this device program/note can be played.
 * This is expressed in device-specific terms.
 */
midi_channels_bitmap_t get_note_channels(
    const midiplan_device_t* p_device,
    program_t                out_program,
    note_t                   out_note
) {

    evar_assert(VALID_PROGRAM(out_program));
    evar_assert(VALID_NOTE(out_note));

    if (IS_PERCUSSION_PROGRAM(out_program)) {
        return p_device->percussion_channels_bitmap;
    }

    uint8_t melodic_channels_bitmap_index = (p_device->melodic_channels_bitmaps_refs[out_program >> 4] >> ((out_program & 0x0f) << 1)) & 0x03;
    return p_device->melodic_channels_bitmaps[melodic_channels_bitmap_index];
}

/*
 * Translates/filters a note on parameters for the particular device.
 * It is crucial that note numbers are translated the same for all note
 * messages, on, off and key pressure, and for certain controllers.
 */
bool translate_note(
    const midiplan_device_t* p_device,
    program_t                in_program,
    note_t                   in_note,
    data_byte_t              in_velocity,
    program_t*               p_out_program,
    note_t*                  p_out_note,
    data_byte_t*             p_out_velocity
) {

    evar_assert(VALID_PROGRAM(in_program));
    evar_assert(VALID_NOTE(in_note));
    evar_assert(VALID_DATA_BYTE(in_velocity) && (in_velocity > 0));

    program_t out_program = INVALID_PROGRAM;
    note_t out_note = INVALID_NOTE;
    data_byte_t out_velocity = INVALID_DATA_BYTE;

    if (IS_MELODIC_PROGRAM(in_program)) {

        // some melodic programs, such as effects, can only be translated into a single percussion note

        uint8_t program_or_note = p_device->melodic_programs[in_program].program;
        if (program_or_note == INVALID_PROGRAM) {
            return false;
        }

        if ((program_or_note & PERCUSSION_PROGRAM) != 0) { // proceed as if it was a percussion note being translated

            // notice that since INVALID_PROGRAM = FF is not allowed here,
            // a melodic program cannot be translated into percussion note 7F

            note_t percussion_note = program_or_note & ~PERCUSSION_PROGRAM;
            evar_assert(VALID_NOTE(percussion_note));

            // notice that this percussion note is still in input terms,
            // it will be translated once again, and may even become melodic then

            out_program = p_device->percussion_notes[percussion_note].program;
            if (!VALID_PROGRAM(out_program)) {
                return false;
            }

            out_note = p_device->percussion_notes[percussion_note].note;
            if (!VALID_NOTE(out_note)) {
                return false;
            }

            // translate note velocity by mapping the original velocity into a lookup table

            uint8_t percussion_note_flags = p_device->percussion_notes[percussion_note].flags;

            uint8_t percussion_note_velocity = PERCUSSION_NOTE_VELOCITY(percussion_note_flags);
            if (percussion_note_velocity == VELOCITY_DEFAULT) {
                out_velocity = in_velocity;
            }
            else if (percussion_note_velocity == VELOCITY_SILENCE) {
                return false;
            }
            else {
                out_velocity = velocity_curves[percussion_note_velocity - 1][in_velocity - 1];
            }
        }
        else { // translate a melodic note by applying a transposing range

            out_program = program_or_note;
            if (!VALID_PROGRAM(out_program)) {
                return false;
            }

            uint8_t melodic_program_flags = p_device->melodic_programs[in_program].flags;

            // translate note velocity by mapping the original velocity into a lookup table

            uint8_t melodic_program_velocity = MELODIC_PROGRAM_VELOCITY(melodic_program_flags);

            if (melodic_program_velocity == VELOCITY_DEFAULT) {
                out_velocity = in_velocity;
            }
            else if (melodic_program_velocity == VELOCITY_SILENCE) {
                return false;
            }
            else {
                out_velocity = velocity_curves[melodic_program_velocity - 1][in_velocity - 1];
            }

            // translate the note number by mapping the original note number into a range

            uint8_t melodic_program_range = MELODIC_PROGRAM_RANGE(melodic_program_flags);

            note_t lowest_note = p_device->melodic_note_ranges[melodic_program_range].lowest_note;
            if (!VALID_NOTE(lowest_note)) {
                return false;
            }

            note_t middle_c = p_device->melodic_note_ranges[melodic_program_range].middle_c;
            if (!VALID_NOTE(middle_c)) {
                return false;
            }

            note_t highest_note = p_device->melodic_note_ranges[melodic_program_range].highest_note;
            if (!VALID_NOTE(highest_note)) {
                return false;
            }

            if (highest_note < lowest_note) {
                return false;
            }

            // transpose according to the middle C position

            if (in_note >= GM_MIDDLE_C) {
                out_note = middle_c + (in_note - GM_MIDDLE_C);
            }
            else {
                out_note = middle_c - (GM_MIDDLE_C - in_note);
            }

            // interestingly enough, middle C could fall outside of
            // the lowest-highest range, but the translated note can't

            if (out_note < lowest_note || out_note > highest_note) {
                return false;
            }
        }
    }
    else { // translating a percussion note

        out_program = p_device->percussion_notes[in_note].program;
        if (!VALID_PROGRAM(out_program)) {
            return false;
        }

        out_note = p_device->percussion_notes[in_note].note;
        if (!VALID_NOTE(out_note)) {
            return false;
        }

        // translate note velocity by mapping the original velocity into a lookup table

        uint8_t percussion_note_flags = p_device->percussion_notes[in_note].flags;

        uint8_t percussion_note_velocity = PERCUSSION_NOTE_VELOCITY(percussion_note_flags);
        if (percussion_note_velocity == VELOCITY_DEFAULT) {
            out_velocity = in_velocity;
        }
        else if (percussion_note_velocity == VELOCITY_SILENCE) {
            return false;
        }
        else {
            out_velocity = velocity_curves[percussion_note_velocity - 1][in_velocity - 1];
        }
    }

    evar_assert(VALID_PROGRAM(out_program));
    evar_assert(VALID_NOTE(out_note));
    evar_assert(VALID_DATA_BYTE(out_velocity) && (out_velocity > 0));

    //UARTprintf("NOTE %d %d %d -> %d %d %d\n", in_program, in_note, in_velocity, out_program, out_note, out_velocity);

    *p_out_program = out_program;
    *p_out_note = out_note;
    *p_out_velocity = out_velocity;

    return true;
}

/*
 * Filters controller change messages for the particular device.
 */
bool controller_supported(
    const midiplan_device_t* p_device,
    midi_control_number_t control_number
) {
    return (p_device->controllers_bitmap[control_number >> 5] & (1 << (control_number & 0x1F))) != 0;
}

/*
 * Filters key pressure messages for the particular device.
 */
bool key_pressure_supported(
    const midiplan_device_t* p_device
) {
    return p_device->key_pressure != 0;
}

/*
 * Filters channel pressure messages for the particular device.
 */
bool channel_pressure_supported(
    const midiplan_device_t* p_device
) {
    return p_device->channel_pressure != 0;
}

/*
 * Filters pitch bend messages for the particular device.
 */
bool pitch_bend_supported(
    const midiplan_device_t* p_device
) {
    return p_device->pitch_bend != 0;
}
