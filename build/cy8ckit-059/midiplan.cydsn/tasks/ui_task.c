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

#define EVAR_TASK_NAME ui_task
#define EVAR_TASK_MESSAGE_COUNT 20
#include <evar_task.h>

#include "midi_router_task.h"

void ui_task__initialize(evar_task_info_t* p_task_info) {
    
    EVAR_UNUSED(p_task_info);

    // initialize the message queue for the task

    static ui_task_message_store_t message_store;
    evar__initialize_message_store(&message_store);
    
    evar_task__sleep();
}

void ui_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void ui_task__wake_up(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

static void init_button_pressed(ui_task_data_t* p_task_data) {

    midi_router_task_message_t midi_router_task_message = {
        .type = MIDI_ROUTER_INITIALIZE_DEVICES
    };

    evar_mq_result_t mq_result = evar__send_message(
        p_task_data->midi_router_task,
        &midi_router_task_message,
        sizeof(midi_router_task_message_t)
    );
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "init_button_pressed: evar__send_message(midi_router_task_message) failed");
    }
}

void ui_task__receive(evar_task_info_t* p_task_info) {

    ui_task_data_t* p_task_data = (ui_task_data_t*)p_task_info->p_task_data;

    ui_task_message_t ui_task_message;
    evar_mq_result_t mq_result = evar__receive_message(&ui_task_message);
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "ui_task__receive: evar__receive_message failed");
    }

    switch (ui_task_message.button_id) {
        case INIT_BUTTON_ID:
            init_button_pressed(p_task_data);
            break;
        default:
            evar_assert(false);
            break;
    }

    evar_task__sleep();
}

void ui_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
