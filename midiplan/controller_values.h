#ifndef MIDIPLAN_CONTROLLER_VALUES_H
#define MIDIPLAN_CONTROLLER_VALUES_H

#include <midiplan/types.h>
#include <midiplan/config.h>

/*
 * This structure contains a currently tracked value of a controller,
 * being either a pair of data bytes or a single data byte.
 */
typedef struct {
    union {
        struct {
            data_byte_t msb;
            data_byte_t lsb;
        };
        data_byte_t value;
    };
} controller_value_t;

/*
 * Initializes the controller values structures.
 * This is done once at startup.
 */
void initialize_controller_values(void);

/*
 * Finds the specified controller value in the table. Allocates and reuses the elements
 * if necessary. The oldest controller value may be discarded, but this call never fails.
 */
controller_value_t* get_controller_value(
    midi_channel_t in_channel, 
    program_t in_program, 
    control_t control
);

/*
 * Deletes all tracked controller values for all programs on an input channel.
 */
void delete_controller_values(
    midi_channel_t in_channel
);

/*
 * Enumerates all tracked values on an input channel.
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
);

#endif
