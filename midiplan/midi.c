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

#include <midiplan/midi.h>

/*
 * Returns the number of data bytes a MIDI message with this status byte expects.
 * For an undefined message returns EXPECTED_DATA_BYTES_UNKNOWN.
 */
uint8_t get_expected_data_bytes(status_byte_t status_byte) {

    switch (MIDI_MESSAGE_TYPE(status_byte)) {
        case MIDI_MESSAGE_NOTE_ON:
            return 2;
        case MIDI_MESSAGE_NOTE_OFF:
            return 2;
        case MIDI_MESSAGE_KEY_PRESSURE:
            return 2;
        case MIDI_MESSAGE_CONTROL_CHANGE:
            return 2;
        case MIDI_MESSAGE_PROGRAM_CHANGE:
            return 1;
        case MIDI_MESSAGE_CHANNEL_PRESSURE:
            return 1;
        case MIDI_MESSAGE_PITCH_BEND:
            return 2;
        case MIDI_MESSAGE_SPECIAL:
            switch (status_byte) {
                case MIDI_MESSAGE_COMMON_TIME_CODE_QUARTER_FRAME:
                    return 1;
                case MIDI_MESSAGE_COMMON_SONG_POSITION_POINTER:
                    return 2;
                case MIDI_MESSAGE_COMMON_SONG_SELECT:
                    return 1;
                case MIDI_MESSAGE_DELAY: // repurposed undefined
                    return 2;
                case MIDI_MESSAGE_COMMON_TUNE_REQUEST:
                    return 0;
                default:
                    break;
            }
        default:
            break;
    }

    return EXPECTED_DATA_BYTES_UNKNOWN;
}

/*
 * Returns the default MSB or the single-byte value for a controller.
 */
data_byte_t get_default_controller_value(midi_control_number_t control_number) {

    switch (control_number) {

        case MIDI_CONTROL_BANK_SELECT:
        case MIDI_CONTROL_MODULATION_WHEEL_OR_LEVER:
        case MIDI_CONTROL_BREATH_CONTROLLER:
        case MIDI_CONTROL_UNDEFINED_03:
        case MIDI_CONTROL_FOOT_CONTROLLER:
        case MIDI_CONTROL_PORTAMENTO_TIME:
        case MIDI_CONTROL_DATA_ENTRY_MSB:
            return 0;
        case MIDI_CONTROL_CHANNEL_VOLUME:
            return 64;
        case MIDI_CONTROL_BALANCE:
            return 64;
        case MIDI_CONTROL_UNDEFINED_09:
            return 0;
        case MIDI_CONTROL_PAN:
            return 64;
        case MIDI_CONTROL_EXPRESSION_CONTROLLER:
            return 127;
        case MIDI_CONTROL_EFFECT_CONTROL_1:
        case MIDI_CONTROL_EFFECT_CONTROL_2:
        case MIDI_CONTROL_UNDEFINED_0E:
        case MIDI_CONTROL_UNDEFINED_0F:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4:
        case MIDI_CONTROL_UNDEFINED_14:
        case MIDI_CONTROL_UNDEFINED_15:
        case MIDI_CONTROL_UNDEFINED_16:
        case MIDI_CONTROL_UNDEFINED_17:
        case MIDI_CONTROL_UNDEFINED_18:
        case MIDI_CONTROL_UNDEFINED_19:
        case MIDI_CONTROL_UNDEFINED_1A:
        case MIDI_CONTROL_UNDEFINED_1B:
        case MIDI_CONTROL_UNDEFINED_1C:
        case MIDI_CONTROL_UNDEFINED_1D:
        case MIDI_CONTROL_UNDEFINED_1E:
        case MIDI_CONTROL_UNDEFINED_1F:
            return 0;

        case MIDI_CONTROL_LSB_FOR_MSB_00:
        case MIDI_CONTROL_LSB_FOR_MSB_01:
        case MIDI_CONTROL_LSB_FOR_MSB_02:
        case MIDI_CONTROL_LSB_FOR_MSB_03:
        case MIDI_CONTROL_LSB_FOR_MSB_04:
        case MIDI_CONTROL_LSB_FOR_MSB_05:
        case MIDI_CONTROL_LSB_FOR_MSB_06:
        case MIDI_CONTROL_LSB_FOR_MSB_07:
        case MIDI_CONTROL_LSB_FOR_MSB_08:
        case MIDI_CONTROL_LSB_FOR_MSB_09:
        case MIDI_CONTROL_LSB_FOR_MSB_0A:
        case MIDI_CONTROL_LSB_FOR_MSB_0B:
        case MIDI_CONTROL_LSB_FOR_MSB_0C:
        case MIDI_CONTROL_LSB_FOR_MSB_0D:
        case MIDI_CONTROL_LSB_FOR_MSB_0E:
        case MIDI_CONTROL_LSB_FOR_MSB_0F:
        case MIDI_CONTROL_LSB_FOR_MSB_10:
        case MIDI_CONTROL_LSB_FOR_MSB_11:
        case MIDI_CONTROL_LSB_FOR_MSB_12:
        case MIDI_CONTROL_LSB_FOR_MSB_13:
        case MIDI_CONTROL_LSB_FOR_MSB_14:
        case MIDI_CONTROL_LSB_FOR_MSB_15:
        case MIDI_CONTROL_LSB_FOR_MSB_16:
        case MIDI_CONTROL_LSB_FOR_MSB_17:
        case MIDI_CONTROL_LSB_FOR_MSB_18:
        case MIDI_CONTROL_LSB_FOR_MSB_19:
        case MIDI_CONTROL_LSB_FOR_MSB_1A:
        case MIDI_CONTROL_LSB_FOR_MSB_1B:
        case MIDI_CONTROL_LSB_FOR_MSB_1C:
        case MIDI_CONTROL_LSB_FOR_MSB_1D:
        case MIDI_CONTROL_LSB_FOR_MSB_1E:
        case MIDI_CONTROL_LSB_FOR_MSB_1F:
            return INVALID_DATA_BYTE;

        case MIDI_CONTROL_SUSTAIN:
        case MIDI_CONTROL_PORTAMENTO_ON_OFF:
        case MIDI_CONTROL_SOSTENUTO:
        case MIDI_CONTROL_SOFT_PEDAL:
        case MIDI_CONTROL_LEGATO_FOOTSWITCH:
        case MIDI_CONTROL_HOLD_2:
        case MIDI_CONTROL_SOUND_VARIATION:
            return 0;
        case MIDI_CONTROL_TIMBRE_HARMONIC_INTENSITY:
        case MIDI_CONTROL_RELEASE_TIME:
        case MIDI_CONTROL_ATTACK_TIME:
        case MIDI_CONTROL_BRIGHTNESS:
        case MIDI_CONTROL_DECAY_TIME:
        case MIDI_CONTROL_VIBRATO_RATE:
        case MIDI_CONTROL_VIBRATO_DEPTH:
        case MIDI_CONTROL_VIBRATO_DELAY:
            return 64;
        case MIDI_CONTROL_SOUND_CONTROLLER_10:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7:
        case MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8:
        case MIDI_CONTROL_PORTAMENTO_CONTROL:
        case MIDI_CONTROL_UNDEFINED_55:
        case MIDI_CONTROL_UNDEFINED_56:
        case MIDI_CONTROL_UNDEFINED_57:
        case MIDI_CONTROL_UNDEFINED_58:
        case MIDI_CONTROL_UNDEFINED_59:
        case MIDI_CONTROL_UNDEFINED_5A:
            return 0;
        case MIDI_CONTROL_REVERB_SEND_LEVEL:
            return 40;
        case MIDI_CONTROL_EFFECTS_DEPTH_2:
        case MIDI_CONTROL_CHORUS_SEND_LEVEL:
        case MIDI_CONTROL_EFFECTS_DEPTH_4:
        case MIDI_CONTROL_EFFECTS_DEPTH_5:
        case MIDI_CONTROL_DATA_INCREMENT:
        case MIDI_CONTROL_DATA_DECREMENT:
            return 0;
        case MIDI_CONTROL_NON_REGISTERED_PARAMETER_LSB:
        case MIDI_CONTROL_NON_REGISTERED_PARAMETER_MSB:
        case MIDI_CONTROL_REGISTERED_PARAMETER_LSB:
        case MIDI_CONTROL_REGISTERED_PARAMETER_MSB:
            return 127;
        case MIDI_CONTROL_UNDEFINED_66:
        case MIDI_CONTROL_UNDEFINED_67:
        case MIDI_CONTROL_UNDEFINED_68:
        case MIDI_CONTROL_UNDEFINED_69:
        case MIDI_CONTROL_UNDEFINED_6A:
        case MIDI_CONTROL_UNDEFINED_6B:
        case MIDI_CONTROL_UNDEFINED_6C:
        case MIDI_CONTROL_UNDEFINED_6D:
        case MIDI_CONTROL_UNDEFINED_6E:
        case MIDI_CONTROL_UNDEFINED_6F:
        case MIDI_CONTROL_UNDEFINED_70:
        case MIDI_CONTROL_UNDEFINED_71:
        case MIDI_CONTROL_UNDEFINED_72:
        case MIDI_CONTROL_UNDEFINED_73:
        case MIDI_CONTROL_UNDEFINED_74:
        case MIDI_CONTROL_UNDEFINED_75:
        case MIDI_CONTROL_UNDEFINED_76:
        case MIDI_CONTROL_UNDEFINED_77:
            return 0;

        default:
            return INVALID_DATA_BYTE;
    }

}
