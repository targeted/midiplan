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
#define EVAR_TASK_MESSAGE_SIZE 3
#define EVAR_TASK_MESSAGE_COUNT 340
//#define EVAR_TASK_MESSAGES_CAN_BE_DROPPED
#include <evar_task.h>

#include <tasks/output_uart_task.h>

EVAR_ASSERT(EVAR_TASK_MESSAGE_SIZE == sizeof(midi_message_t), expected_message_size);

void output_uart_task__initialize(evar_task_info_t* p_task_info) {

    output_uart_task_data_t* p_task_data = (output_uart_task_data_t*)p_task_info->p_task_data;

    // allocate the message queue for the task

    static output_uart_task_message_store_t message_stores[MIDI_OUT_PORT_COUNT] = { 0 };
    p_task_info->p_message_store = &message_stores[p_task_data->midi_out_port];

    // initialize the hardware output UART

    SysCtlPeripheralEnable(p_task_data->periph_uart);
    while (!SysCtlPeripheralReady(p_task_data->periph_uart)) {}

    UARTDisable(p_task_data->uart_base);

    GPIOPinConfigure(p_task_data->uart_tx_pin_config);
    GPIOPinTypeUART(p_task_data->uart_port_base, p_task_data->uart_tx_pin);

    UARTConfigSetExpClk(p_task_data->uart_base, SysCtlClockGet(), 31250, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);

    UARTFIFOEnable(p_task_data->uart_base);

    UARTEnable(p_task_data->uart_base);

    // initialize task data

    p_task_data->prev_status_byte = INVALID_STATUS_BYTE;

    p_task_data->message_bytes_to_send = 0;
    p_task_data->message_bytes_sent = 0;

    p_task_data->delay_usec = 0;

    // wait for incoming messages

    GPIOPinTypeGPIOOutput(p_task_data->led_port_base, p_task_data->led_pin);
    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, p_task_data->led_pin);

    evar_task__sleep();
}

void output_uart_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void output_uart_task__wake_up(evar_task_info_t* p_task_info) {

    output_uart_task_data_t* p_task_data = p_task_info->p_task_data;

    // turn the LED off because there hasn't been a message in the queue for a while

    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, p_task_data->led_pin);

    evar_task__sleep();
}

void output_uart_task__receive(evar_task_info_t* p_task_info) {

    output_uart_task_data_t* p_task_data = p_task_info->p_task_data;

    // the output UART could be in state of delay, not sending for the specified amount of time

    if (p_task_data->delay_usec > 0) {
        if (evar__get_time_delta(&p_task_data->delay_start, &evar_current_timestamp) < p_task_data->delay_usec) {
            return evar_task__keep_running(); // since we did not remove the message from the queue, this will result in __receive call immediately
        }
        p_task_data->delay_usec = 0;
    }

    // otherwise we proceed as usual

    midi_message_t midi_message;

    while (true) { // this loop is restricted with the size of the output UART FIFO

        if (p_task_data->message_bytes_to_send == 0) { // time to get another message from the queue

            evar_mq_result_t mq_result = evar__receive_message(&midi_message, sizeof(midi_message_t));
            if (mq_result == EVAR_MQ_QUEUE_EMPTY) {
                break;
            }
            else if (mq_result != EVAR_MQ_SUCCESS) {
                evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "output_uart_task__receive: evar__receive_message(midi_message) failed");
            }

            // copy the received message to the internal buffer and send from there

            status_byte_t status_byte = midi_message.status_byte;
            data_byte_t data_byte_1 = midi_message.data_byte_1;
            data_byte_t data_byte_2 = midi_message.data_byte_2;

            //UARTprintf(
            //    (VALID_DATA_BYTE(data_byte_2) ? "[%d] %02X:%02X:%02X\n" : (VALID_DATA_BYTE(data_byte_1) ? "[%d] %02X:%02X\n" : "[%d] %02X\n")),
            //    p_task_data->midi_out_port + 1, status_byte, data_byte_1, data_byte_2
            //);

            // this is a re-purposed unused special message, used to delay sending, data bytes
            // contain milliseconds to delay sending for, MSB in data byte 1, LSB in data byte 2

            if (status_byte == MIDI_MESSAGE_DELAY) {
                p_task_data->delay_usec = ((data_byte_1 << 7) | data_byte_2) * 1000;
                evar_assert((p_task_data->delay_usec > 0) && (p_task_data->delay_usec <= EVAR_MAX_POSITIVE_TIME_DELTA));
                p_task_data->delay_start = evar_current_timestamp;
                return evar_task__keep_running(); // since we did not remove the message from the queue, this will result in __receive call immediately
            }

            // at this point system exclusive messages are represented as sequences 
            // of separate messages, one per byte, the following two if's reconstruct
            // them in their MIDI format

            if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {
                if (!VALID_DATA_BYTE(data_byte_1)) {
                    p_task_data->message_bytes[0] = MIDI_MESSAGE_SYSTEM_EXCLUSIVE;
                    p_task_data->message_bytes_to_send = 1;
                }
                else {
                    p_task_data->message_bytes[0] = data_byte_1;
                    p_task_data->message_bytes_to_send = 1;
                }
            }
            else if (status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {
                p_task_data->message_bytes[0] = MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;
                p_task_data->message_bytes_to_send = 1;
            }
            else { // otherwise we have a regular message to send

                // if running status can be applied, there is no need to send the status byte

                if (status_byte != p_task_data->prev_status_byte) {
                    p_task_data->message_bytes[p_task_data->message_bytes_to_send++] = status_byte;
                }

                if (IS_MIDI_CHANNEL_MESSAGE(status_byte)) { // only a channel message can become current status
                    p_task_data->prev_status_byte = status_byte;
                }
                else {
                    p_task_data->prev_status_byte = INVALID_STATUS_BYTE;
                }

                // we know how many data bytes to send from their actual values,
                // the ones that are not to be sent contain INVALID_DATA_BYTE

                if (VALID_DATA_BYTE(data_byte_1)) {
                    p_task_data->message_bytes[p_task_data->message_bytes_to_send++] = data_byte_1;
                    if (VALID_DATA_BYTE(data_byte_2)) {
                        p_task_data->message_bytes[p_task_data->message_bytes_to_send++] = data_byte_2;
                    }
                }
            }

            evar_assert(p_task_data->message_bytes_to_send > 0);
            p_task_data->message_bytes_sent = 0;
        }

        // send as many bytes of the remainder of the current message as possible

        while ((p_task_data->message_bytes_sent < p_task_data->message_bytes_to_send) && UARTSpaceAvail(p_task_data->uart_base)) {
            //UARTprintf("[%d] >> %02X\n", p_task_data->midi_out_port + 1, p_task_data->message_bytes[p_task_data->message_bytes_sent]);
            UARTCharPut(
                p_task_data->uart_base,
                p_task_data->message_bytes[p_task_data->message_bytes_sent++]
            );
        }

        if (p_task_data->message_bytes_sent < p_task_data->message_bytes_to_send) { // not all bytes have been sent, UART FIFO is full
            break;
        }

        // the current message has been sent, will pull another from the queue at the next loop pass

        p_task_data->message_bytes_to_send = 0;
        p_task_data->message_bytes_sent = 0;

    }

    // light up the LED signaling activity

    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, 0);

    evar_task__sleep_for(100000);
}

void output_uart_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
