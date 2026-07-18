#ifndef MIDIPLAN_TYPES_H
#define MIDIPLAN_TYPES_H

#include <stdbool.h>
#include "midi.h"
#include "config.h"

/*
 * MIDI channel plus special values.
 */
typedef uint8_t channel_t; // midi_channel_t plus the following special value
#define INVALID_CHANNEL    (0xFF)
#define VALID_CHANNEL(CHANNEL) ((CHANNEL) < MIDI_CHANNEL_COUNT)
EVAR_ASSERT(!VALID_CHANNEL(INVALID_CHANNEL), invalid_channel);

/*
 * MIDI control plus special values.
 */
typedef uint8_t control_t; // midi_control_number_t plus the following special values
#define CONTROL_PRESSURE   (0x80)
#define CONTROL_PITCH_BEND (0x81)
#define INVALID_CONTROL    (0xFF)
#define VALID_CONTROL(CONTROL) ((CONTROL) <= CONTROL_PITCH_BEND)
EVAR_ASSERT(!VALID_CONTROL(INVALID_CONTROL), invalid_control);

/*
 * MIDI program plus special values.
 */
typedef uint8_t program_t; // midi_program_number_t plus the following special values
#define PERCUSSION_PROGRAM (0x80)
EVAR_ASSERT((PERCUSSION_PROGRAM & 0x7F) == 0, percussion_program_used_as_a_flag);
#define INVALID_PROGRAM    (0xFF)
#define VALID_PROGRAM(PROGRAM) ((PROGRAM) <= PERCUSSION_PROGRAM)
EVAR_ASSERT(!VALID_PROGRAM(INVALID_PROGRAM), invalid_program);
#define IS_MELODIC_PROGRAM(PROGRAM) ((PROGRAM) != PERCUSSION_PROGRAM)
#define IS_PERCUSSION_PROGRAM(PROGRAM) ((PROGRAM) == PERCUSSION_PROGRAM)

/*
 * MIDI note plus special values.
 */
typedef uint8_t note_t;  // midi_note_number_t plus the following special value
#define INVALID_NOTE     (0xFF)
#define VALID_NOTE(NOTE) (((NOTE) & 0x80) == 0)
EVAR_ASSERT(!VALID_NOTE(INVALID_NOTE), invalid_note);

/*
 * Logical identifier of a device-specific custom sequence.
 * The SINGLE_MIDI_MESSAGE value corresponds to a single ad-hoc
 * message, not a sequence, and is handled differently.
 */
typedef enum {
    INITIALIZATION_SEQUENCE = 0,
    PROGRAM_CHANGE_SEQUENCE = 1,
    NOTE_ON_SEQUENCE        = 2,
    NOTE_OFF_SEQUENCE       = 3,
    SINGLE_MIDI_MESSAGE     = 0xFF
} custom_sequence_id_t;

/*
 * Ordered parameters used for producing custom sequences,
 * their interpretation depends on the sequence.
 */
typedef struct { uint8_t p[3]; } custom_sequence_parameters_t; // wrapped in a struct to make it atomically assignable
EVAR_ASSERT(sizeof(custom_sequence_parameters_t) == 3, sizeof_custom_sequence_parameters_t); // see output_uart_task_message_t

#endif
