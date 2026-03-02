#ifndef MIDIPLAN_MIDIPLAN_H
#define MIDIPLAN_MIDIPLAN_H

#include <midiplan/types.h>
#include <midiplan/config.h>

/*
 * Sends a MIDI message to the specified output port. The message will be
 * sent directly to the output UART, with no further processing of any kind.
 */
typedef void (*midiplan_callback_send_message_t)(
    void* p_context, 
    midi_out_port_t out_port,
    midi_message_t midi_message
);

typedef struct {
    midiplan_callback_send_message_t send_message;
} midiplan_callbacks_t;

void midiplan_initialize(midiplan_callbacks_t* p_callbacks);

/*
 * Processes a MIDI message incoming from the input UART.
 */
void midiplan_handle_message(
    void* p_context, 
    midi_message_t midi_message
);

#endif
