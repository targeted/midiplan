#ifndef MIDIPLAN_MIDI_H
#define MIDIPLAN_MIDI_H

#include <stdint.h>
#include <evar_preproc.h>

typedef unsigned char status_byte_t;
#define VALID_STATUS_BYTE(BYTE) (((BYTE) & 0x80) != 0)
#define INVALID_STATUS_BYTE (0x7F)
EVAR_ASSERT(!VALID_STATUS_BYTE(INVALID_STATUS_BYTE), invalid_status_byte);

typedef unsigned char data_byte_t;
#define VALID_DATA_BYTE(BYTE) (((BYTE) & 0x80) == 0)
#define INVALID_DATA_BYTE (0xFF)
EVAR_ASSERT(!VALID_DATA_BYTE(INVALID_DATA_BYTE), invalid_data_byte);

typedef enum {
    MIDI_MESSAGE_NOTE_OFF         = 0x80,
    MIDI_MESSAGE_NOTE_ON          = 0x90,
    MIDI_MESSAGE_KEY_PRESSURE     = 0xA0,
    MIDI_MESSAGE_CONTROL_CHANGE   = 0xB0,
    MIDI_MESSAGE_PROGRAM_CHANGE   = 0xC0,
    MIDI_MESSAGE_CHANNEL_PRESSURE = 0xD0,
    MIDI_MESSAGE_PITCH_BEND       = 0xE0,
    MIDI_MESSAGE_SPECIAL          = 0xF0
} midi_message_type_t;

#define MIDI_MESSAGE_TYPE(STATUS_BYTE) ((midi_message_type_t)((STATUS_BYTE) & 0xF0))

typedef enum {
    MIDI_CHANNEL_1     = 0,
    MIDI_CHANNEL_2     = 1,
    MIDI_CHANNEL_3     = 2,
    MIDI_CHANNEL_4     = 3,
    MIDI_CHANNEL_5     = 4,
    MIDI_CHANNEL_6     = 5,
    MIDI_CHANNEL_7     = 6,
    MIDI_CHANNEL_8     = 7,
    MIDI_CHANNEL_9     = 8,
    MIDI_CHANNEL_10    = 9,
    MIDI_CHANNEL_11    = 10,
    MIDI_CHANNEL_12    = 11,
    MIDI_CHANNEL_13    = 12,
    MIDI_CHANNEL_14    = 13,
    MIDI_CHANNEL_15    = 14,
    MIDI_CHANNEL_16    = 15,
    MIDI_CHANNEL_COUNT = 16
} midi_channel_t;

#define MIDI_MESSAGE_CHANNEL(STATUS_BYTE) ((midi_channel_t)((STATUS_BYTE) & 0x0F))

typedef uint16_t midi_channels_bitmap_t;
EVAR_ASSERT((sizeof(midi_channels_bitmap_t) * 8) >= MIDI_CHANNEL_COUNT, sizeof_midi_channels_bitmap_t);

typedef enum {

    MIDI_MESSAGE_SYSTEM_EXCLUSIVE               = 0xF0,
    MIDI_MESSAGE_COMMON_TIME_CODE_QUARTER_FRAME = 0xF1,
    MIDI_MESSAGE_COMMON_SONG_POSITION_POINTER   = 0xF2,
    MIDI_MESSAGE_COMMON_SONG_SELECT             = 0xF3,
    MIDI_MESSAGE_COMMON_UNDEFINED_F4            = 0xF4,
    MIDI_MESSAGE_DELAY                          = 0xF4, // repurposed undefined, observed by the output UART
    MIDI_MESSAGE_COMMON_UNDEFINED_F5            = 0xF5,
    MIDI_MESSAGE_COMMON_TUNE_REQUEST            = 0xF6,
    MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END           = 0xF7,

    MIDI_MESSAGE_REAL_TIME_TIMING_CLOCK         = 0xF8,
    MIDI_MESSAGE_REAL_TIME_UNDEFINED_F9         = 0xF9,
    MIDI_MESSAGE_REAL_TIME_START                = 0xFA,
    MIDI_MESSAGE_REAL_TIME_CONTINUE             = 0xFB,
    MIDI_MESSAGE_REAL_TIME_STOP                 = 0xFC,
    MIDI_MESSAGE_REAL_TIME_UNDEFINED_FD         = 0xFD,
    MIDI_MESSAGE_REAL_TIME_ACTIVE_SENSING       = 0xFE,
    MIDI_MESSAGE_REAL_TIME_SYSTEM_RESET         = 0xFF

} midi_message_type_special_t;

#define IS_MIDI_SPECIAL_MESSAGE(STATUS_BYTE) (MIDI_MESSAGE_TYPE(STATUS_BYTE) == MIDI_MESSAGE_SPECIAL)
#define IS_MIDI_CHANNEL_MESSAGE(STATUS_BYTE) (!IS_MIDI_SPECIAL_MESSAGE(STATUS_BYTE))
#define IS_MIDI_EXCLUSIVE_MESSAGE(STATUS_BYTE) ((STATUS_BYTE) == MIDI_MESSAGE_SYSTEM_EXCLUSIVE || (STATUS_BYTE) == MIDI_MESSAGE_EXCLUSIVE_STOP)
#define IS_MIDI_REAL_TIME_MESSAGE(STATUS_BYTE) (((STATUS_BYTE) & 0xF8) == 0xF8)
#define IS_MIDI_UNDEFINED_MESSAGE(STATUS_BYTE) (((STATUS_BYTE) == MIDI_MESSAGE_COMMON_UNDEFINED_F4) || ((STATUS_BYTE) == MIDI_MESSAGE_COMMON_UNDEFINED_F5) || ((STATUS_BYTE) == MIDI_MESSAGE_REAL_TIME_UNDEFINED_F9) || ((STATUS_BYTE) == MIDI_MESSAGE_REAL_TIME_UNDEFINED_FD))

typedef struct {
    status_byte_t status_byte;
    data_byte_t data_byte_1;
    data_byte_t data_byte_2;
} midi_message_t;

typedef data_byte_t midi_program_number_t;

typedef data_byte_t midi_note_number_t;

typedef enum {
    MIDI_CONTROL_BANK_SELECT                  = 0x00,    
    MIDI_CONTROL_MODULATION_WHEEL_OR_LEVER    = 0x01,
    MIDI_CONTROL_BREATH_CONTROLLER            = 0x02,
    MIDI_CONTROL_UNDEFINED_03                 = 0x03,
    MIDI_CONTROL_FOOT_CONTROLLER              = 0x04,
    MIDI_CONTROL_PORTAMENTO_TIME              = 0x05,
    MIDI_CONTROL_DATA_ENTRY_MSB               = 0x06,
    MIDI_CONTROL_CHANNEL_VOLUME               = 0x07,
    MIDI_CONTROL_BALANCE                      = 0x08,
    MIDI_CONTROL_UNDEFINED_09                 = 0x09,
    MIDI_CONTROL_PAN                          = 0x0A,
    MIDI_CONTROL_EXPRESSION_CONTROLLER        = 0x0B,
    MIDI_CONTROL_EFFECT_CONTROL_1             = 0x0C,
    MIDI_CONTROL_EFFECT_CONTROL_2             = 0x0D,
    MIDI_CONTROL_UNDEFINED_0E                 = 0x0E,
    MIDI_CONTROL_UNDEFINED_0F                 = 0x0F,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1 = 0x10,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2 = 0x11,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3 = 0x12,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4 = 0x13,
    MIDI_CONTROL_UNDEFINED_14                 = 0x14,
    MIDI_CONTROL_UNDEFINED_15                 = 0x15,
    MIDI_CONTROL_UNDEFINED_16                 = 0x16,
    MIDI_CONTROL_UNDEFINED_17                 = 0x17,
    MIDI_CONTROL_UNDEFINED_18                 = 0x18,
    MIDI_CONTROL_UNDEFINED_19                 = 0x19,
    MIDI_CONTROL_UNDEFINED_1A                 = 0x1A,
    MIDI_CONTROL_UNDEFINED_1B                 = 0x1B,
    MIDI_CONTROL_UNDEFINED_1C                 = 0x1C,
    MIDI_CONTROL_UNDEFINED_1D                 = 0x1D,
    MIDI_CONTROL_UNDEFINED_1E                 = 0x1E,
    MIDI_CONTROL_UNDEFINED_1F                 = 0x1F,
    MIDI_CONTROL_LSB_FOR_MSB_00               = 0x20,
    MIDI_CONTROL_LSB_FOR_MSB_01               = 0x21,
    MIDI_CONTROL_LSB_FOR_MSB_02               = 0x22,
    MIDI_CONTROL_LSB_FOR_MSB_03               = 0x23,
    MIDI_CONTROL_LSB_FOR_MSB_04               = 0x24,
    MIDI_CONTROL_LSB_FOR_MSB_05               = 0x25,
    MIDI_CONTROL_LSB_FOR_MSB_06               = 0x26,
    MIDI_CONTROL_LSB_FOR_MSB_07               = 0x27,
    MIDI_CONTROL_LSB_FOR_MSB_08               = 0x28,
    MIDI_CONTROL_LSB_FOR_MSB_09               = 0x29,
    MIDI_CONTROL_LSB_FOR_MSB_0A               = 0x2A,
    MIDI_CONTROL_LSB_FOR_MSB_0B               = 0x2B,
    MIDI_CONTROL_LSB_FOR_MSB_0C               = 0x2C,
    MIDI_CONTROL_LSB_FOR_MSB_0D               = 0x2D,
    MIDI_CONTROL_LSB_FOR_MSB_0E               = 0x2E,
    MIDI_CONTROL_LSB_FOR_MSB_0F               = 0x2F,
    MIDI_CONTROL_LSB_FOR_MSB_10               = 0x30,
    MIDI_CONTROL_LSB_FOR_MSB_11               = 0x31,
    MIDI_CONTROL_LSB_FOR_MSB_12               = 0x32,
    MIDI_CONTROL_LSB_FOR_MSB_13               = 0x33,
    MIDI_CONTROL_LSB_FOR_MSB_14               = 0x34,
    MIDI_CONTROL_LSB_FOR_MSB_15               = 0x35,
    MIDI_CONTROL_LSB_FOR_MSB_16               = 0x36,
    MIDI_CONTROL_LSB_FOR_MSB_17               = 0x37,
    MIDI_CONTROL_LSB_FOR_MSB_18               = 0x38,
    MIDI_CONTROL_LSB_FOR_MSB_19               = 0x39,
    MIDI_CONTROL_LSB_FOR_MSB_1A               = 0x3A,
    MIDI_CONTROL_LSB_FOR_MSB_1B               = 0x3B,
    MIDI_CONTROL_LSB_FOR_MSB_1C               = 0x3C,
    MIDI_CONTROL_LSB_FOR_MSB_1D               = 0x3D,
    MIDI_CONTROL_LSB_FOR_MSB_1E               = 0x3E,
    MIDI_CONTROL_LSB_FOR_MSB_1F               = 0x3F,
    MIDI_CONTROL_SUSTAIN                      = 0x40,
    MIDI_CONTROL_PORTAMENTO_ON_OFF            = 0x41,
    MIDI_CONTROL_SOSTENUTO                    = 0x42,
    MIDI_CONTROL_SOFT_PEDAL                   = 0x43,
    MIDI_CONTROL_LEGATO_FOOTSWITCH            = 0x44,
    MIDI_CONTROL_HOLD_2                       = 0x45,
    MIDI_CONTROL_SOUND_VARIATION              = 0x46,
    MIDI_CONTROL_TIMBRE_HARMONIC_INTENSITY    = 0x47,
    MIDI_CONTROL_RELEASE_TIME                 = 0x48,
    MIDI_CONTROL_ATTACK_TIME                  = 0x49,
    MIDI_CONTROL_BRIGHTNESS                   = 0x4A,
    MIDI_CONTROL_DECAY_TIME                   = 0x4B,
    MIDI_CONTROL_VIBRATO_RATE                 = 0x4C,
    MIDI_CONTROL_VIBRATO_DEPTH                = 0x4D,
    MIDI_CONTROL_VIBRATO_DELAY                = 0x4E,
    MIDI_CONTROL_SOUND_CONTROLLER_10          = 0x4F,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5 = 0x50,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6 = 0x51,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7 = 0x52,
    MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8 = 0x53,
    MIDI_CONTROL_PORTAMENTO_CONTROL           = 0x54,
    MIDI_CONTROL_UNDEFINED_55                 = 0x55,
    MIDI_CONTROL_UNDEFINED_56                 = 0x56,
    MIDI_CONTROL_UNDEFINED_57                 = 0x57,
    MIDI_CONTROL_UNDEFINED_58                 = 0x58,
    MIDI_CONTROL_UNDEFINED_59                 = 0x59,
    MIDI_CONTROL_UNDEFINED_5A                 = 0x5A,
    MIDI_CONTROL_REVERB_SEND_LEVEL            = 0x5B,
    MIDI_CONTROL_EFFECTS_DEPTH_2              = 0x5C,
    MIDI_CONTROL_CHORUS_SEND_LEVEL            = 0x5D,
    MIDI_CONTROL_EFFECTS_DEPTH_4              = 0x5E,
    MIDI_CONTROL_EFFECTS_DEPTH_5              = 0x5F,
    MIDI_CONTROL_DATA_INCREMENT               = 0x60,
    MIDI_CONTROL_DATA_DECREMENT               = 0x61,
    MIDI_CONTROL_NON_REGISTERED_PARAMETER_LSB = 0x62,
    MIDI_CONTROL_NON_REGISTERED_PARAMETER_MSB = 0x63,
    MIDI_CONTROL_REGISTERED_PARAMETER_LSB     = 0x64,
    MIDI_CONTROL_REGISTERED_PARAMETER_MSB     = 0x65,
    MIDI_CONTROL_UNDEFINED_66                 = 0x66,
    MIDI_CONTROL_UNDEFINED_67                 = 0x67,
    MIDI_CONTROL_UNDEFINED_68                 = 0x68,
    MIDI_CONTROL_UNDEFINED_69                 = 0x69,
    MIDI_CONTROL_UNDEFINED_6A                 = 0x6A,
    MIDI_CONTROL_UNDEFINED_6B                 = 0x6B,
    MIDI_CONTROL_UNDEFINED_6C                 = 0x6C,
    MIDI_CONTROL_UNDEFINED_6D                 = 0x6D,
    MIDI_CONTROL_UNDEFINED_6E                 = 0x6E,
    MIDI_CONTROL_UNDEFINED_6F                 = 0x6F,
    MIDI_CONTROL_UNDEFINED_70                 = 0x70,
    MIDI_CONTROL_UNDEFINED_71                 = 0x71,
    MIDI_CONTROL_UNDEFINED_72                 = 0x72,
    MIDI_CONTROL_UNDEFINED_73                 = 0x73,
    MIDI_CONTROL_UNDEFINED_74                 = 0x74,
    MIDI_CONTROL_UNDEFINED_75                 = 0x75,
    MIDI_CONTROL_UNDEFINED_76                 = 0x76,
    MIDI_CONTROL_UNDEFINED_77                 = 0x77,
    MIDI_CHANNEL_MODE_ALL_SOUND_OFF           = 0x78,
    MIDI_CHANNEL_MODE_RESET_ALL_CONTROLLERS   = 0x79,
    MIDI_CHANNEL_MODE_LOCAL_CONTROL_ON_OFF    = 0x7A,
    MIDI_CHANNEL_MODE_ALL_NOTES_OFF           = 0x7B,
    MIDI_CHANNEL_MODE_OMNI_OFF                = 0x7C,
    MIDI_CHANNEL_MODE_OMNI_ON                 = 0x7D,
    MIDI_CHANNEL_MODE_MONO_ON                 = 0x7E,
    MIDI_CHANNEL_MODE_POLY_ON                 = 0x7F,
} midi_control_number_t;

#define IS_MIDI_CHANNEL_MODE(CONTROL_NUMBER) (((CONTROL_NUMBER) & 0x78) == 0x78)

#define GM_PERCUSSION_CHANNEL (MIDI_CHANNEL_10)
#define GM_MIDDLE_C (0x3C)

/*
 * Returns the number of data bytes a MIDI message with this status byte expects. 
 * For an undefined message returns EXPECTED_DATA_BYTES_UNKNOWN.
 */
#define EXPECTED_DATA_BYTES_UNKNOWN (0xFF)
uint8_t get_expected_data_bytes(status_byte_t status_byte);

/*
 * Returns the default MSB or the single-byte value for a controller.
 */
data_byte_t get_default_controller_value(midi_control_number_t control_number);

#endif
