#ifndef MIDIPLAN_TYPES_H
#define MIDIPLAN_TYPES_H

#include <stddef.h>
#include <midiplan/midi.h>
#include <midiplan/config.h>

typedef uint8_t channel_t; // midi_channel_t plus the following special value
#define INVALID_CHANNEL    (0xFF)
#define VALID_CHANNEL(CHANNEL) ((CHANNEL) < MIDI_CHANNEL_COUNT)
EVAR_ASSERT(!VALID_CHANNEL(INVALID_CHANNEL), invalid_channel);

typedef uint8_t control_t; // midi_control_number_t plus the following special values
#define CONTROL_PRESSURE   (0x80)
#define CONTROL_PITCH_BEND (0x81)
#define INVALID_CONTROL    (0xFF)
#define VALID_CONTROL(CONTROL) ((CONTROL) <= CONTROL_PITCH_BEND)
EVAR_ASSERT(!VALID_CONTROL(INVALID_CONTROL), invalid_control);

typedef uint8_t program_t; // midi_program_number_t plus the following special values
#define PERCUSSION_PROGRAM (0x80)
EVAR_ASSERT((PERCUSSION_PROGRAM & 0x7F) == 0, percussion_program_used_as_a_flag);
#define INVALID_PROGRAM    (0xFF)
#define VALID_PROGRAM(PROGRAM) ((PROGRAM) <= PERCUSSION_PROGRAM)
EVAR_ASSERT(!VALID_PROGRAM(INVALID_PROGRAM), invalid_program);
#define IS_MELODIC_PROGRAM(PROGRAM) ((PROGRAM) != PERCUSSION_PROGRAM)
#define IS_PERCUSSION_PROGRAM(PROGRAM) ((PROGRAM) == PERCUSSION_PROGRAM)

typedef uint8_t note_t;    // midi_note_number_t plus the following special value
#define INVALID_NOTE       (0xFF)
#define VALID_NOTE(NOTE)   (((NOTE) & 0x80) == 0)
EVAR_ASSERT(!VALID_NOTE(INVALID_NOTE), invalid_note);

#endif
