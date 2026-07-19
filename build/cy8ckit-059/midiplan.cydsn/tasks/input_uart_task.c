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

#define EVAR_TASK_NAME input_uart_task
#define EVAR_TASK_MESSAGE_COUNT 1024 /* this controls how many input bytes could be buffered */
#include <evar_task.h>

#include <midiplan/midi_input.h>
#include "midi_router_task.h"

/*
 * This is the input UART RX interrupt handler. Buffer size is expected to be set to 4,
 * which causes the interrupt to be generated with respect to the hardware buffer only.
 */
void input_uart_interrupt_handler(input_uart_task_data_t* p_task_data) {

    while (p_task_data->UART.GetRxBufferSize() > 0) {
        
        input_uart_task_message_t input_uart_task_message = {
            .input_uart_byte = p_task_data->UART.ReadRxData()
        };
        
        evar_mq_result_t mq_result = evar__send_async_message(
            p_task_data->input_uart_task,
            &input_uart_task_message,
            sizeof(input_uart_task_message_t)
        );
        if (mq_result != EVAR_MQ_SUCCESS) {
            evar__crash(CRASH_SEND_ASYNC_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_interrupt_handler: evar__send_async_message() failed");
        }
    }
}

void input_uart_task__initialize(evar_task_info_t* p_task_info) {

    input_uart_task_data_t* p_task_data = (input_uart_task_data_t*)p_task_info->p_task_data;

    // initialize the message queue for the task

    static input_uart_task_message_store_t message_store;
    evar__initialize_message_store(&message_store);

    // initialize the runtime state

    p_task_data->input_uart_task = p_task_info->current_task; // keep a reference to the current task for the interrupt handler
    reset_midi_input_state(&p_task_data->midi_input_state);

    // turn activity LED off

    p_task_data->LED.Write(0);

    // start the hardware input UART
    
    p_task_data->UART.IRQ_StartEx(p_task_data->UART.interrupt_handler);
    p_task_data->UART.Start();

    // wait for incoming messages

    evar_task__sleep();
}

void input_uart_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
    input_uart_task__receive(p_task_info);
}

/*
 * This will be invoked when the task has been idle for 100ms.
 */
void input_uart_task__wake_up(evar_task_info_t* p_task_info) {
    input_uart_task_data_t* p_task_data = p_task_info->p_task_data;
    p_task_data->LED.Write(0);
    evar_task__sleep();
}

void input_uart_task__receive(evar_task_info_t* p_task_info) {

    input_uart_task_data_t* p_task_data = (input_uart_task_data_t*)p_task_info->p_task_data;

    // the bytes incoming from the input UART are accumulated in this task's message queue,
    // one byte per message, the most economical way possible, therefore we let them stay
    // there while we process them one by one

    // each received byte can complete a MIDI message, and for it to be submitted
    // we need the router task's message queue to have free space, lest we find out
    // later that it is full and there is nothing to do but to crash then

    if (evar__message_queue_full(p_task_data->midi_router_task) != EVAR_MQ_QUEUE_NOT_FULL) {
        return evar_task__keep_running(); // since we did not remove the message from the queue, this will result in the same __receive call immediately
    }

    // now that we know that we can produce a MIDI message, we will read as many input bytes as needed

    while (true) { // 1 to 3 bytes will be read

        input_uart_task_message_t input_uart_task_message;

        // the incoming byte cannot always be consumed, because of the tricky case of an
        // exclusive message terminated not by EOX, but by the next message's status byte

        evar_mq_result_t mq_result = evar__preview_message(&input_uart_task_message);
        if (mq_result == EVAR_MQ_QUEUE_EMPTY) {
            break;
        }
        else if (mq_result != EVAR_MQ_SUCCESS) {
            evar__crash(CRASH_PREVIEW_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_task__receive: evar__preview_message failed");
        }

        //DEBUG_PRINT1("< %02X\r\n", input_uart_task_message.input_uart_byte);

        // the following call will handle the incoming byte and possibly produce the completed MIDI message

        midi_router_task_message_t midi_router_task_message = {
            .type = MIDI_ROUTER_HANDLE_MESSAGE
        };

        bool consume_input_byte;
        bool midi_message_produced = handle_midi_input_byte(
                &p_task_data->midi_input_state,
                input_uart_task_message.input_uart_byte,
                &midi_router_task_message.midi_message,
                &consume_input_byte
        );
             
        if (consume_input_byte) {
            if (evar__receive_message(NULL) != EVAR_MQ_SUCCESS) { // the processed message is dropped by "receiving" it to NULL
                evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_task__receive: evar__receive_message failed");
            }
        }

        if (midi_message_produced) {
            evar_mq_result_t mq_result = evar__send_message(
                p_task_data->midi_router_task,
                &midi_router_task_message,
                sizeof(midi_router_task_message_t)
            );
            if (mq_result != EVAR_MQ_SUCCESS) {
                evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "submit_midi_message: evar__send_message failed");
            }
            break;
        }
    }

    p_task_data->LED.Write(1); // turn activity LED on

    evar_task__sleep_for(100000); // if this timeout expires before another message, wake_up is called and the LED is turned off
}

void input_uart_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
