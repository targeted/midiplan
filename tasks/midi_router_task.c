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

#define EVAR_TASK_NAME midi_router_task
#define EVAR_TASK_MESSAGE_COUNT 64
#include <evar_task.h>

#include <midiplan/midiplan.h>
#include "output_uart_task.h"
#include <midiplan/device.h>

/*
 * Sends a MIDI message to the specified output port.
 * The actual sending will be done asynchronously to this call,
 * when the output UART task later pulls this message from its queue.
 */
static void send_midi_message(
    void* p_context, 
    midi_out_port_t out_port,
    status_byte_t status_byte,
    data_byte_t data_byte_1,
    data_byte_t data_byte_2
) {

    midi_router_task_data_t* p_task_data = (midi_router_task_data_t*)p_context;
    
    output_uart_task_message_t output_uart_task_message = {
        .custom_sequence_id = SINGLE_MIDI_MESSAGE,
        .midi_message = {
            .status_byte = status_byte,
            .data_byte_1 = data_byte_1,
            .data_byte_2 = data_byte_2
        }
    };
    
    evar_mq_result_t mq_result = evar__send_message(
        p_task_data->output_uart_tasks[out_port],
        &output_uart_task_message,
        sizeof(output_uart_task_message_t)
    );
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "send_midi_message: evar__send_message(output_uart_task_message) failed");
    }
}

/*
 * Sends a custom device-specific sequence to the specified output port.
 * The actual sending will be done asynchronously to this call,
 * when the output UART task later pulls this message from its queue.
 */
static void send_custom_sequence(
    void* p_context, 
    midi_out_port_t out_port,
    custom_sequence_id_t custom_sequence_id,
    custom_sequence_parameters_t custom_sequence_parameters
) {

    midi_router_task_data_t* p_task_data = (midi_router_task_data_t*)p_context;
    
    evar_assert(custom_sequence_id != SINGLE_MIDI_MESSAGE);
    
    output_uart_task_message_t output_uart_task_message = {
        .custom_sequence_id = custom_sequence_id,
        .custom_sequence_parameters = custom_sequence_parameters
    };
    
    evar_mq_result_t mq_result = evar__send_message(
        p_task_data->output_uart_tasks[out_port],
        &output_uart_task_message,
        sizeof(output_uart_task_message_t)
    );
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "send_midi_message: evar__send_message(output_uart_task_message) failed");
    }
}

static midiplan_callbacks_t midiplan_callbacks = {
    .send_midi_message = send_midi_message,
    .send_custom_sequence = send_custom_sequence
};

static midi_router_task_message_store_t message_store;

/*
 * Initializes the module.
 */
void midi_router_task__initialize(evar_task_info_t* p_task_info) {
    
    EVAR_UNUSED(p_task_info);
    
    // initialize the message queue for the task

    evar__initialize_message_store(&message_store);

    // initialize the router's structures
    
    midiplan_initialize(&midiplan_callbacks);
    
    // wait for incoming messages
    
    evar_task__sleep();
}

void midi_router_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void midi_router_task__wake_up(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void midi_router_task__receive(evar_task_info_t* p_task_info) {

    midi_router_task_message_t midi_router_task_message;

    // we handle one message at a time
    
    evar_mq_result_t mq_result = evar__receive_message(&midi_router_task_message);
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "midi_router_task__receive: evar__receive_message failed");
    }
    
    //UARTprintf(
    //    (VALID_DATA_BYTE(midi_router_task_message.midi_message.data_byte_2) ? "= %02X:%02X:%02X\n" : (VALID_DATA_BYTE(midi_router_task_message.midi_message.data_byte_1) ? "= %02X:%02X\n" : "= %02X\n")),
    //    midi_router_task_message.midi_message.status_byte, midi_router_task_message.midi_message.data_byte_1, midi_router_task_message.midi_message.data_byte_2
    //);
    
    // and the actual handling is done in a separate module

    midiplan_handle_message(p_task_info->p_task_data, midi_router_task_message.midi_message);

    evar_task__sleep();
}

void midi_router_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
