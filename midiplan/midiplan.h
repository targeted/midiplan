#ifndef MIDIPLAN_MIDIPLAN_H
#define MIDIPLAN_MIDIPLAN_H

#include <midiplan/types.h>
#include <midiplan/config.h>

/*
 * Sends a MIDI message to the specified output port.
 * The actual sending will be done asynchronously to this call,
 * when the output UART task later pulls this message from its queue.
 */
typedef void (*midiplan_callback_send_midi_message_t)(
    void* p_context, 
    midi_out_port_t out_port,
    status_byte_t status_byte,
    data_byte_t data_byte_1,
    data_byte_t data_byte_2
);

/*
 * Sends a custom device-specific sequence to the specified output port.
 * The actual sending will be done asynchronously to this call,
 * when the output UART task later pulls this message from its queue.
 */
typedef void (*midiplan_callback_send_custom_sequence_t)(
    void* p_context, 
    midi_out_port_t out_port,
    custom_sequence_id_t custom_sequence_id,
    custom_sequence_parameters_t custom_sequence_parameters
);

typedef struct {
    midiplan_callback_send_midi_message_t send_midi_message;
    midiplan_callback_send_custom_sequence_t send_custom_sequence;
} midiplan_callbacks_t;

/*
 * Initializes the module.
 */
void midiplan_initialize(midiplan_callbacks_t* p_callbacks);

/*
 * Processes a MIDI message incoming from the input UART.
 */
void midiplan_handle_message(
    void* p_context, 
    midi_message_t midi_message
);

#endif
