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

#define EVAR_TASK_NAME output_uart_task
#define EVAR_TASK_MESSAGE_COUNT 256
#include <evar_task.h>

#include <midiplan/devices.h>
#include <midiplan/midi_output.h>

void output_uart_task__initialize(evar_task_info_t* p_task_info) {

    output_uart_task_data_t* p_task_data = (output_uart_task_data_t*)p_task_info->p_task_data;

    // initialize the message queue for the task

    static output_uart_task_message_store_t message_stores[MIDI_OUT_PORT_COUNT];
    evar__initialize_message_store(&message_stores[p_task_data->midi_out_port]);

    // turn activity LED off

    p_task_data->LED_Write(0);

    // start the hardware output UART
    
    p_task_data->UART_Start();
    
    // initialize task data

    initialize_midi_output_state(&p_task_data->midi_output_state);
    evar_assert(!have_midi_output_bytes_to_send(&p_task_data->midi_output_state));

    p_task_data->delay_usec = 0;

    // wait for incoming messages

    evar_task__sleep();
}

/*
 * Returns true if sending delay has been requested and is still in effect.
 */
static bool sending_is_delayed(output_uart_task_data_t* p_task_data) {

    if (p_task_data->delay_usec == 0) {
        return false;
    }

    evar_timestamp_t current_timestamp;
    evar__get_current_timestamp(&current_timestamp);

    if (evar__get_time_delta(&p_task_data->delay_start, &current_timestamp) < p_task_data->delay_usec) {
        return true;
    }

    p_task_data->delay_usec = 0;
    return false;
}

/*
 * Initializes a sending delay.
 */
static void delay_sending(output_uart_task_data_t* p_task_data, evar_time_delta_t delay_usec) {

    evar_assert(!sending_is_delayed(p_task_data));
    evar_assert(delay_usec > 0 && delay_usec <= EVAR_MAX_POSITIVE_TIME_DELTA);

    p_task_data->delay_usec = delay_usec;
    evar__get_current_timestamp(&p_task_data->delay_start);
    evar_assert(sending_is_delayed(p_task_data));
}

/*
 * Pulls a message from the queue and buffers its contents for sending.
 */
static bool receive_next_message(output_uart_task_data_t* p_task_data) {

    output_uart_task_message_t output_uart_task_message;

    evar_mq_result_t mq_result = evar__receive_message(&output_uart_task_message);
    if (mq_result == EVAR_MQ_QUEUE_EMPTY) {
        return false;
    }
    else if (mq_result != EVAR_MQ_SUCCESS) {
        evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "receive_next_message: evar__receive_message failed");
    }

    // depending on its id/type, the received message will be interpreteted as
    // either a single literal MIDI message or a pointer to a parameterized sequence
    
    if (output_uart_task_message.custom_sequence_id == SINGLE_MIDI_MESSAGE) {
        load_midi_output_midi_message(
            &p_task_data->midi_output_state, 
            output_uart_task_message.midi_message
        );
    }
    else {
        load_midi_output_custom_sequence(
            &p_task_data->midi_output_state,
            devices[p_task_data->midi_out_port].p_device,
            output_uart_task_message.custom_sequence_id, 
            output_uart_task_message.custom_sequence_parameters
        );
    }

    return true;
}

/*
 * This will get invoked if there is a message in the queue or there is some buffered data to send.
 */
void output_uart_task__run(evar_task_info_t* p_task_info) {

    output_uart_task_data_t* p_task_data = p_task_info->p_task_data;

    // output UART could be in state of delay, not sending for the specified
    // amount of time, sending will continue after the timeout will have elapsed

    if (sending_is_delayed(p_task_data)) {
        return evar_task__keep_running();
    }

    // this loop exits when we run out of input messages, the output UART FIFO is full, or a delay is requested

    while (true) {

        if (p_task_data->UART_FIFO_FULL()) {
            return evar_task__keep_running(); // busy wait until output FIFO has sending capacity
        }

        if (!have_midi_output_bytes_to_send(&p_task_data->midi_output_state)) {
            if (!receive_next_message(p_task_data)) { // nothing buffered and no more messages in the queue
                return evar_task__sleep_for(100000);
            }
            evar_assert(have_midi_output_bytes_to_send(&p_task_data->midi_output_state));
        }

        uint8_t next_byte;
        evar_time_delta_t delay_usec = 0;

        if (!get_next_midi_output_byte(&p_task_data->midi_output_state, &next_byte, &delay_usec)) {
            if (delay_usec > 0) {
                delay_sending(p_task_data, delay_usec);
            }
            return evar_task__keep_running();
        }

        //DEBUG_PRINT1("> %02X\r\n", next_byte);
        
        p_task_data->UART_WriteTxData(next_byte);

        p_task_data->LED_Write(1); // turn activity LED on
    }

    return evar_task__keep_running();
}

/*
 * This will be invoked when the task has been idle for 100ms.
 */
void output_uart_task__wake_up(evar_task_info_t* p_task_info) {
    output_uart_task_data_t* p_task_data = p_task_info->p_task_data;
    p_task_data->LED_Write(0);
    evar_task__sleep();
}

void output_uart_task__receive(evar_task_info_t* p_task_info) {
    output_uart_task__run(p_task_info);
}

void output_uart_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
