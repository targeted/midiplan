#ifndef MIDIPLAN_NOTE_ENTRIES_H
#define MIDIPLAN_NOTE_ENTRIES_H

#include <stdbool.h>
#include <evar.h>
#include <midiplan/types.h>
#include <midiplan/config.h>

typedef uint8_t note_entry_id_t;
EVAR_ASSERT(sizeof(note_entry_id_t) <= sizeof(uint8_t), sizeof_note_entry_id_t); // because uint8_t is used to iterate through note entries
#define INVALID_NOTE_ENTRY_ID ((note_entry_id_t)-1)
#define VALID_NOTE_ENTRY_ID(NOTE_ENTRY_ID) ((NOTE_ENTRY_ID) < (MAX_NOTE_ENTRIES))
EVAR_ASSERT(INVALID_NOTE_ENTRY_ID >= MAX_NOTE_ENTRIES, invalid_note_entry_id_1);
EVAR_ASSERT(!VALID_NOTE_ENTRY_ID(INVALID_NOTE_ENTRY_ID), invalid_note_entry_id_2);

typedef struct {
    channel_t channel;
    program_t program;
    note_t    note;
} note_route_t;

typedef struct {
    note_route_t     in;
    note_route_t     out[MIDI_OUT_PORT_COUNT];
    evar_timestamp_t timestamp;
    note_entry_id_t  prev;
    note_entry_id_t  next;
} note_entry_t;

/*
 * Publicly accessible table of notes.
 */
extern note_entry_t note_entries[MAX_NOTE_ENTRIES];

/*
 * Resets the note entries to their initial empty state.
 * This is only done once at startup.
 */
void initialize_note_entries(void);

/*
 * Returns true if there are no note entries allocated,
 * used to detect absence of active notes.
 */
bool no_allocated_note_entries(void);

/*
 * Allocates and gives out an index of an empty unused note entry.
 */
note_entry_id_t allocate_note_entry(void);

/*
 * Releases a note entry back to the pool.
 */
void deallocate_note_entry(note_entry_id_t note_entry_id);

/*
 * Enumerates all the currently active note entries in order 
 * from the earliest to the most recent.
 */
void enumerate_note_entries(
    void* p_callback_context,
    void (*callback)(
        void* p_callback_context,
        note_entry_id_t note_entry_id
    )
);

/*
 * This structure will accumulate note statistics even after they have been turned off.
 */
typedef struct {
    uint8_t note_count;          // the number of notes accounted for in the following numbers, it is a moving average and will not exceed 16
    uint16_t total_note_time_ms; // in milliseconds, assuming last 16 notes being accounted for, good for up to 4 seconds per note
    uint32_t last_note_times[2]; // 4 bits per note, measured in 150ms units, 0 meaning 0 (i.e. empty), 1 meaning <150, 2 meaning <300, ..., 14 meaning <2100, 15 meaning >=2100 ms
} program_profile_t;

extern program_profile_t program_profiles[128 + 1]; // 128 melodic + 1 for percussion

/*
 * Clears the accumulated program statistics. This can be called arbitrarily.
 */
void reset_program_statistics(void);

/*
 * This is called when an input note is officially turned off by the client. 
 * By that time, the corresponding output notes could have been long since turned off,
 * but it is only then that we know how long the input note was supposed to sound.
 */
void register_note_duration(program_t program, uint16_t note_duration_ms);

/*
 * Returns a moving average duration milliseconds of the last few notes for the given program.
 */
uint16_t get_average_note_duration(program_t program);

#endif
