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
#include <midiplan/controller_values.h>

typedef uint8_t cv_index_t;
#define INVALID_CV_INDEX ((cv_index_t)-1)
EVAR_ASSERT(INVALID_CV_INDEX >= MAX_CONTROLLER_VALUES, invalid_cv_index);
#define VALID_CV_INDEX(INDEX) ((INDEX) != INVALID_CV_INDEX)
EVAR_ASSERT(!VALID_CV_INDEX(INVALID_CV_INDEX), valid_cv_index);

/*
 * Every tracked controller value will be stored in such structure. It is also 
 * an element in a channel's linked list, with "next" pointing to its successor.
 */
typedef struct {
    channel_t in_channel;
    program_t in_program;
    control_t control;
    controller_value_t controller_value;
    cv_index_t next;
} cv_list_element_t;

/*
 * All the tracked controller values in a large flat table.
 */
static cv_list_element_t cv_table[MAX_CONTROLLER_VALUES];

/*
 * These arrays contain the indexes of the first and the last elements of per-channel lists.
 */
static cv_index_t cv_heads[MIDI_CHANNEL_COUNT];
static cv_index_t cv_tails[MIDI_CHANNEL_COUNT];

/*
 * The rolling index into the table of the next element to be (re)used.
 */
static cv_index_t next_cv_index;

/*
 * Syntax shortcuts.
 */
#define CV(cv_index)         (cv_table[cv_index])
#define CV_CHANNEL(cv_index) (CV(cv_index).in_channel)
#define CV_PROGRAM(cv_index) (CV(cv_index).in_program)
#define CV_CONTROL(cv_index) (CV(cv_index).control)
#define CV_VALUE(cv_index)   (CV(cv_index).controller_value)
#define CV_NEXT(cv_index)    (CV(cv_index).next)

static void clear_controller_value(cv_index_t cv_index) {

    CV_CHANNEL(cv_index) = INVALID_CHANNEL;
    CV_PROGRAM(cv_index) = INVALID_PROGRAM;
    CV_CONTROL(cv_index) = INVALID_CONTROL;
    CV_VALUE(cv_index).msb = INVALID_DATA_BYTE;
    CV_VALUE(cv_index).lsb = INVALID_DATA_BYTE;

    evar_assert(!VALID_DATA_BYTE(CV_VALUE(cv_index).value));
    CV_NEXT(cv_index) = INVALID_CV_INDEX;
}

/*
 * Initializes the controller values structures.
 * This is done once at startup.
 */
void initialize_controller_values(void) {

    for (midi_channel_t channel = MIDI_CHANNEL_1; channel < MIDI_CHANNEL_COUNT; ++channel) {
        cv_heads[channel] = INVALID_CV_INDEX;
        cv_tails[channel] = INVALID_CV_INDEX;
    }

    for (cv_index_t cv_index = 0; cv_index < MAX_CONTROLLER_VALUES; ++cv_index) {
        clear_controller_value(cv_index);
    }

    next_cv_index = 0;
}

/*
 * Finds the specified controller value in the table. Allocates and reuses the elements
 * if necessary. The oldest controller value may be discarded, but this call never fails.
 */
controller_value_t* get_controller_value(
    midi_channel_t in_channel, 
    program_t in_program, 
    control_t control
) {

    evar_assert(VALID_PROGRAM(in_program));

    // first, we attempt to find a matching element in the channel's list

    cv_index_t scan = cv_heads[in_channel];
    while (VALID_CV_INDEX(scan)) {
        evar_assert(CV_CHANNEL(scan) == in_channel);
        if (CV_PROGRAM(scan) == in_program && CV_CONTROL(scan) == control) {
            return &CV_VALUE(scan);
        }
        scan = CV_NEXT(scan);
    }

    // there was no matching element, we will need to allocate one at the current
    // next_cv_index, possibly evicting and reusing the value that is currently there
    
    channel_t evicted_channel = CV_CHANNEL(next_cv_index);
    if (VALID_CHANNEL(evicted_channel)) {

        // by nature of the algorithm, the element being evicted has to be the head of its channel's list

        cv_index_t evicted_head = cv_heads[evicted_channel];
        evar_assert(evicted_head == next_cv_index);
        
        // advance the evicted head by one, and if it was the only element, reset its tail as well
        
        if (!VALID_CV_INDEX(cv_heads[evicted_channel] = CV_NEXT(evicted_head))) {
            cv_tails[evicted_channel] = INVALID_CV_INDEX;
        }
    }

    // initialize the newly allocated value, possibly overwriting what was evicted
    
    CV_CHANNEL(next_cv_index) = in_channel;
    CV_PROGRAM(next_cv_index) = in_program;
    CV_CONTROL(next_cv_index) = control;
    CV_VALUE(next_cv_index).msb = INVALID_DATA_BYTE;
    CV_VALUE(next_cv_index).lsb = INVALID_DATA_BYTE;
    evar_assert(!VALID_DATA_BYTE(CV_VALUE(next_cv_index).value));
    CV_NEXT(next_cv_index) = INVALID_CV_INDEX; // this will become the last element on its channel's list

    // put the newly allocated value at the end of its channel's list
    
    cv_index_t channel_tail = cv_tails[in_channel];
    if (VALID_CV_INDEX(channel_tail)) {
        CV_NEXT(channel_tail) = next_cv_index;
    }
    else {
        cv_heads[in_channel] = next_cv_index;
    }

    cv_tails[in_channel] = next_cv_index;
    
    // advance the next element index
    
    if (++next_cv_index == MAX_CONTROLLER_VALUES) {
        next_cv_index = 0;    
    }
    
    // return the newly allocated value

    return &CV_VALUE(cv_tails[in_channel]);
}

/*
 * Deletes all tracked values for one input channel.
 */
void delete_controller_values(
    midi_channel_t in_channel
) {

    cv_index_t scan = cv_heads[in_channel];
    
    while (VALID_CV_INDEX(scan)) {
        cv_index_t next = CV_NEXT(scan);
        clear_controller_value(scan);
        scan = next;
    }
    
    cv_heads[in_channel] = INVALID_CV_INDEX;
    cv_tails[in_channel] = INVALID_CV_INDEX;
}

/*
 * Enumerates all tracked controller values on an input channel.
 */
void enumerate_controller_values(
    midi_channel_t in_channel,
    void* p_callback_context,
    void (*callback)(
        void* p_callback_context,
        midi_channel_t in_channel,
        program_t in_program,
        control_t control, 
        controller_value_t* p_controller_value
    )
) {

    cv_index_t scan = cv_heads[in_channel];

    while (VALID_CV_INDEX(scan)) {
        evar_assert(VALID_PROGRAM(CV_PROGRAM(scan)));
        evar_assert(VALID_CONTROL(CV_CONTROL(scan)));
        callback(p_callback_context, in_channel, CV_PROGRAM(scan), CV_CONTROL(scan), &CV_VALUE(scan));
        scan = CV_NEXT(scan);
    }
}
