#ifndef MIDIPLAN_CONFIG_H
#define MIDIPLAN_CONFIG_H

#include <evar_preproc.h>

typedef enum {
    MIDI_OUT_PORT_1     = 0,
    MIDI_OUT_PORT_2     = 1,
    MIDI_OUT_PORT_3     = 2,
    MIDI_OUT_PORT_4     = 3,
    MIDI_OUT_PORT_COUNT = 4
} midi_out_port_t;

#define DEFAULT_MELODIC_PROGRAM (0x00) // GM_PROGRAM_ACOUSTIC_GRAND_PIANO

#define MIDI_LOWEST_NOTE (0x10)
#define MIDI_HIGHEST_NOTE (0x6F)
#define MIDI_NOTE_RANGE (MIDI_HIGHEST_NOTE - MIDI_LOWEST_NOTE + 1)

#define MAX_CONTROLLER_VALUES (128)
#define MAX_NOTE_ENTRIES (128)

#define MIN_REPLACEABLE_NOTE_AGE (7) // in eights of the program's average duration

//#define SYSTEM_EXCLUSIVE_PASSTHROUGH // define to allow passing incoming system exclusive messages

#endif
