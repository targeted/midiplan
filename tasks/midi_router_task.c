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
#define EVAR_TASK_MESSAGE_SIZE 3
#define EVAR_TASK_MESSAGE_COUNT 256
//#define EVAR_TASK_MESSAGES_CAN_BE_DROPPED
#include <evar_task.h>

#include <tasks/midi_router_task.h>

EVAR_ASSERT(EVAR_TASK_MESSAGE_SIZE == sizeof(midi_message_t), expected_message_size);

/*
 * Sends a MIDI message to the specified output port.
 */
static void send_message(
    void* p_context, 
    midi_out_port_t out_port,
    midi_message_t midi_message
) {

    midi_router_task_data_t* p_task_data = (midi_router_task_data_t*)p_context;
    
    evar_mq_result_t mq_result = evar__send_message(
        p_task_data->output_uart_tasks[out_port],
        &midi_message,
        sizeof(midi_message_t)
    );
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "send_message: evar__send_message(midi_message) failed");
    }
}

static midiplan_callbacks_t midiplan_callbacks = {
    .send_message = send_message
};

void midi_router_task__initialize(evar_task_info_t* p_task_info) {
    
    // allocate the message queue for the task

    static midi_router_task_message_store_t message_store = { 0 };
    p_task_info->p_message_store = &message_store;

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

    do {

        midi_message_t input_midi_message;

        evar_mq_result_t mq_result = evar__receive_message(&input_midi_message, sizeof(midi_message_t));
        if (mq_result == EVAR_MQ_QUEUE_EMPTY) {
            break;
        }
        else if (mq_result != EVAR_MQ_SUCCESS) {
            evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "midi_router_task__receive: evar__receive_message(input_midi_message) failed");
        }

        midiplan_handle_message(p_task_info->p_task_data, input_midi_message);

    } 
    while (false); // the router receives and dispatches one message at a time

    evar_task__sleep();
}

void midi_router_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
