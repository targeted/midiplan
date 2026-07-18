#ifndef MIDIPLAN_MIDIPLAN_H
#define MIDIPLAN_MIDIPLAN_H

#include "types.h"
#include "devices.h"

/*
 * Sends a MIDI message to the specified output port.
 * The actual sending will be done asynchronously to this call,
 * when the output UART task later pulls this message from its queue.
 */
typedef void (*midiplan_callback_send_midi_message_t)(
    void* p_callback_context,
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
    void* p_callback_context,
    midi_out_port_t out_port,
    custom_sequence_id_t custom_sequence_id,
    custom_sequence_parameters_t custom_sequence_parameters
);

typedef struct {
    
    void* p_callback_context;
    
    struct {
        midiplan_callback_send_midi_message_t send_midi_message;
        midiplan_callback_send_custom_sequence_t send_custom_sequence;
    } callbacks;
    
} midiplan_context_t;

/*
 * Initializes the structures.
 */
void midiplan__initialize(void);

/*
 * Processes a MIDI message incoming from the input UART.
 */
void midiplan__handle_message(
    midiplan_context_t* p_midiplan_context,
    midi_message_t midi_message
);

#endif
