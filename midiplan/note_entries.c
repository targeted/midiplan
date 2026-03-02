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

#include <evar.h>
#include <midiplan/note_entries.h>

// this table contains all the notes we could track

note_entry_t note_entries[MAX_NOTE_ENTRIES];

// this table contains runtime statistics per input program

program_profile_t program_profiles[128 + 1];

// the same pool of note entries is shared by two linked lists,
// one containing available elements and another allocated,
// initially all elements are on the first list.

static note_entry_id_t available_head;
static note_entry_id_t allocated_head;

#define NR_PREV(ENTRY_ID) note_entries[ENTRY_ID].prev
#define NR_NEXT(ENTRY_ID) note_entries[ENTRY_ID].next

/*
 * Removes the specified element from the linked list.
 */
static void remove_note_entry(note_entry_id_t* p_head, note_entry_id_t note_entry_id) {
    
    evar_assert(VALID_NOTE_ENTRY_ID(*p_head));
    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));

    note_entry_id_t prev = NR_PREV(note_entry_id);
    note_entry_id_t next = NR_NEXT(note_entry_id);

    if (next == note_entry_id) { // the only entry is being removed
    
        evar_assert(prev == note_entry_id);
        evar_assert(*p_head == note_entry_id);
    
        *p_head = INVALID_NOTE_ENTRY_ID;
    }
    else {
        
        NR_NEXT(prev) = next;
        NR_PREV(next) = prev;
        
        if (note_entry_id == *p_head) {
            *p_head = next;
        }
    }
}

/*
 * Insert the specified element at the front of the linked list.
 */
static void insert_note_entry(note_entry_id_t* p_head, note_entry_id_t note_entry_id) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));

    note_entry_id_t head = *p_head;

    if (!VALID_NOTE_ENTRY_ID(head)) {
    
        NR_NEXT(note_entry_id) = note_entry_id;
        NR_PREV(note_entry_id) = note_entry_id;
    }
    else {
    
        note_entry_id_t tail = NR_PREV(head);
    
        NR_NEXT(note_entry_id) = head;
        NR_PREV(note_entry_id) = tail;
        
        NR_PREV(head) = note_entry_id; 
        NR_NEXT(tail) = note_entry_id;
    }

    *p_head = note_entry_id;
}

/*
 * Clears a note route.
 */
static void clear_note_route(note_route_t* p_note_route) {
    p_note_route->channel = INVALID_CHANNEL;
    p_note_route->program = INVALID_PROGRAM;
    p_note_route->note    = INVALID_NOTE;  
}

/*
 * Clears a note entry to its initial state.
 */
static note_entry_t* clear_note_entry(note_entry_id_t note_entry_id) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));

    note_entry_t* p_note_entry = &note_entries[note_entry_id];

    clear_note_route(&p_note_entry->in);

    for (midi_out_port_t out_port = MIDI_OUT_PORT_1; out_port < MIDI_OUT_PORT_COUNT; ++out_port) {
        clear_note_route(&p_note_entry->out[out_port]);
    }

    p_note_entry->prev = INVALID_NOTE_ENTRY_ID;
    p_note_entry->next = INVALID_NOTE_ENTRY_ID;
    
    return p_note_entry;
}

/*
 * Returns true if there are no note entries allocated,
 * used to detect absence of active notes.
 */
bool no_allocated_note_entries(void) {
    
    return !VALID_NOTE_ENTRY_ID(allocated_head);
}

/*
 * Resets the note entries to their initial empty state.
 * This is only done once at startup.
 */
void initialize_note_entries(void) {

    for (uint8_t i = 0; i < MAX_NOTE_ENTRIES; ++i) {
        
        note_entry_t* p_note_entry = clear_note_entry(i);
        
        p_note_entry->prev = i > 0 ? i - 1 : MAX_NOTE_ENTRIES - 1;
        p_note_entry->next = i < MAX_NOTE_ENTRIES - 1 ? i + 1 : 0;
    }
    
    available_head = 0;
    allocated_head = INVALID_NOTE_ENTRY_ID;
}

/*
 * Allocates and gives out an index of an empty unused note entry.
 */
note_entry_id_t allocate_note_entry(void) {

    if (!VALID_NOTE_ENTRY_ID(available_head)) {
        return INVALID_NOTE_ENTRY_ID;
    }

    note_entry_id_t result = available_head;
    remove_note_entry(&available_head, result);
    insert_note_entry(&allocated_head, result);

    return result;
}

/*
 * Releases a note entry back to the pool.
 */
void deallocate_note_entry(note_entry_id_t note_entry_id) {

    evar_assert(VALID_NOTE_ENTRY_ID(note_entry_id));
    
    remove_note_entry(&allocated_head, note_entry_id);
    insert_note_entry(&available_head, note_entry_id);
}

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
) {

    if (!VALID_NOTE_ENTRY_ID(allocated_head)) {
        return;
    }

    // we enumerate from the earliest entries i.e. from the tail
    
    note_entry_id_t scan = allocated_head;
    do {
        scan = NR_PREV(scan);
        callback(p_callback_context, scan);
    } 
    while (scan != allocated_head);
}

/*
 * Clears the accumulated program statistics. This can be called arbitrarily.
 */
void reset_program_statistics(void) {
    
    for (uint8_t i = 0; i < 128 + 1; ++i) {
        program_profiles[i].note_count = 0;
        program_profiles[i].total_note_time_ms = 0;
        program_profiles[i].last_note_times[0] = 0;
        program_profiles[i].last_note_times[1] = 0;
    }
}

/*
 * This is called when an input note is officially turned off by the client. 
 * By that time, the corresponding output notes could have been long since turned off,
 * but it is only then that we know how long the input note was supposed to sound.
 */
void register_note_duration(
    program_t program, 
    uint16_t note_duration_ms
) {

    evar_assert(VALID_PROGRAM(program));
    evar_assert(note_duration_ms > 0);

    // convert the milliseconds into range 1-15 (1 being <=150ms, 14 being <=2100ms, 15 being over 2100, registered as 2250ms)

    uint8_t note_time;
    if (note_duration_ms <= 2100) {
        note_time = (note_duration_ms + 149) / 150; 
    }
    else {
        note_time = 15;
    }

    evar_assert(note_time > 0);
    note_duration_ms = note_time * 150;
    evar_assert(note_duration_ms <= 2250);
    
    // this is the range index of the first registered note
    
    uint8_t first_note_time = program_profiles[program].last_note_times[0] >> 28;
    
    // shift in the 4 bits for the new note
    
    program_profiles[program].last_note_times[0] = (program_profiles[program].last_note_times[0] << 4) | (program_profiles[program].last_note_times[1] >> 28);
    program_profiles[program].last_note_times[1] = (program_profiles[program].last_note_times[1] << 4) | (note_time & 0x0f);
    
    // subtract the oldest note, add the new note
    
    uint16_t first_note_duration_ms = first_note_time * 150;
    
    evar_assert(program_profiles[program].total_note_time_ms >= first_note_duration_ms);
    program_profiles[program].total_note_time_ms -= first_note_duration_ms;
    program_profiles[program].total_note_time_ms += note_duration_ms;
    evar_assert(program_profiles[program].total_note_time_ms <= 36000);
    
    // the counter goes up to 16 and stays there
    
    if (program_profiles[program].note_count < 16) {
        program_profiles[program].note_count += 1;
    }
}

/*
 * Returns a moving average duration milliseconds of the last few notes for the given program.
 */
uint16_t get_average_note_duration(
    program_t program
) {
    
    evar_assert(VALID_PROGRAM(program));

    if (program_profiles[program].note_count == 0) { // no information yet
        return 0;
    }
    else if (program_profiles[program].note_count == 16) {
        return program_profiles[program].total_note_time_ms >> 4; // to avoid division when possible
    }
    else {
        return program_profiles[program].total_note_time_ms / program_profiles[program].note_count;
    }
}

