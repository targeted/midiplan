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

#define EVAR_TASK_NAME push_button_task
#include <evar_task.h>
#include "ui_task.h"

void push_button_interrupt_handler(push_button_task_data_t* p_task_data) {

    ui_task_message_t ui_task_message = {
        .button_id = p_task_data->button_id
    };
    
    evar_mq_result_t mq_result = evar__send_async_message(
        p_task_data->ui_task,
        &ui_task_message,
        sizeof(ui_task_message_t)
    );
    if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_SEND_ASYNC_MESSAGE_FAILED | (unsigned short)mq_result, "push_button_interrupt_handler: evar__send_async_message(ui_task_message) failed");
    }
}

void push_button_task__initialize(evar_task_info_t* p_task_info) {

    push_button_task_data_t* p_task_data = (push_button_task_data_t*)p_task_info->p_task_data;
    p_task_data->IRQ.SetVector(p_task_data->IRQ.interrupt_handler);
    p_task_data->IRQ.Enable();
}

void push_button_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void push_button_task__wake_up(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void push_button_task__receive(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void push_button_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
