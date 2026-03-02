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
#define EVAR_TASK_MESSAGE_SIZE 1
#define EVAR_TASK_MESSAGE_COUNT 1024
//#define EVAR_TASK_MESSAGES_CAN_BE_DROPPED
#include <evar_task.h>

#include <tasks/input_uart_task.h>

EVAR_ASSERT(EVAR_TASK_MESSAGE_SIZE == sizeof(unsigned char), expected_message_size);

/*
 * This is the universal input UART interrupt handler.
 */
void input_uart_interrupt_handler(input_uart_task_data_t* p_task_data) {

    uint32_t uart_base = p_task_data->uart_base;
    uint32_t int_status = UARTIntStatus(uart_base, true);

    // RX = (more than 1 byte of) data is available in the FIFO
    // RT = receive has stalled, a single stray byte is still in the FIFO, not enough to trigger RX (hardware quirk)

    if (int_status & (UART_INT_RX | UART_INT_RT)) {

        UARTIntClear(uart_base, UART_INT_RX | UART_INT_RT);

        while (UARTCharsAvail(uart_base)) { // drain the input UART FIFO, because there is no second chance there

            int32_t uart_char = UARTCharGet(uart_base);

            if (((uint32_t)uart_char & 0x00000F00) != 0) { // presence of high bits indicates hardware error condition, combined from UART_RXERROR_... flags
                continue;
            }

            unsigned char input_uart_byte = (unsigned char)(uart_char & 0xFF);

            evar_mq_result_t mq_result = evar__send_async_message(
                p_task_data->input_uart_task, 
                &input_uart_byte,
                sizeof(unsigned char)
            );
            if (mq_result != EVAR_MQ_SUCCESS) {
                evar__crash(CRASH_SEND_ASYNC_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_interrupt_handler: evar__send_async_message(input_uart_byte) failed");
            }

        }
    }
}

void reset_protocol_state(input_uart_task_data_t* p_task_data) {
    p_task_data->synchronized   = false;
    p_task_data->status_byte    = INVALID_STATUS_BYTE;
    p_task_data->data_bytes[0]  = INVALID_DATA_BYTE;
    p_task_data->data_bytes[1]  = INVALID_DATA_BYTE;
    p_task_data->running_status = INVALID_STATUS_BYTE;
    p_task_data->input_midi_message_pending = false;
}

void input_uart_task__initialize(evar_task_info_t* p_task_info) {

    input_uart_task_data_t* p_task_data = (input_uart_task_data_t*)p_task_info->p_task_data;

    // allocate the message queue for the task

    static input_uart_task_message_store_t message_store = { 0 };
    p_task_info->p_message_store = &message_store;

    p_task_data->input_uart_task = p_task_info->current_task;

    // clear the internal state tracking the protocol

    reset_protocol_state(p_task_data);

    // initialize the hardware input UART

    SysCtlPeripheralEnable(p_task_data->periph_uart);
    while (!SysCtlPeripheralReady(p_task_data->periph_uart)) {}

    UARTDisable(p_task_data->uart_base);

    GPIOPinConfigure(p_task_data->uart_rx_pin_config);
    GPIOPinTypeUART(p_task_data->uart_port_base, p_task_data->uart_rx_pin);

    UARTConfigSetExpClk(p_task_data->uart_base, SysCtlClockGet(), 31250, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);

    UARTIntRegister(p_task_data->uart_base, p_task_data->interrupt_handler);
    UARTIntEnable(p_task_data->uart_base, UART_INT_RX | UART_INT_RT);

    UARTFIFOEnable(p_task_data->uart_base);
    UARTFIFOLevelSet(p_task_data->uart_base, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    UARTEnable(p_task_data->uart_base);

    // wait for incoming messages

    GPIOPinTypeGPIOOutput(p_task_data->led_port_base, p_task_data->led_pin);

    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, p_task_data->led_pin);

    evar_task__sleep();
}

void input_uart_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
    input_uart_task__receive(p_task_info);
}

void input_uart_task__wake_up(evar_task_info_t* p_task_info) {

    input_uart_task_data_t* p_task_data = p_task_info->p_task_data;

    // turn the LED off because there hasn't been a message in the queue for a while

    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, p_task_data->led_pin);

    evar_task__sleep();
}

/*
 * Attempts to send the fully composed MIDI message to the router. 
 * Will be retried if it fails.
 */
static bool submit_pending_input_midi_message(input_uart_task_data_t* p_task_data) {

    evar_mq_result_t mq_result = evar__send_message(
        p_task_data->midi_router_task,
        &p_task_data->input_midi_message,
        sizeof(midi_message_t)
    );
    if (mq_result == EVAR_MQ_SUCCESS) {
        p_task_data->input_midi_message_pending = false;
        return true;
    }
    else if (mq_result != EVAR_MQ_QUEUE_FULL) {
        evar__crash(CRASH_SEND_MESSAGE_FAILED | (unsigned short)mq_result, "submit_pending_input_midi_message: evar__send_message(input_midi_message) failed");
    }

    return false;
}

/*
 * Initiates the attempts to deliver the fully composed MIDI message to the router.
 */
static void submit_input_midi_message(
    input_uart_task_data_t* p_task_data,
    status_byte_t status_byte,
    data_byte_t data_byte_1,
    data_byte_t data_byte_2
) {

    p_task_data->input_midi_message.status_byte = status_byte;
    p_task_data->input_midi_message.data_byte_1 = data_byte_1;
    p_task_data->input_midi_message.data_byte_2 = data_byte_2;

    p_task_data->input_midi_message_pending = true;

    // this is the first attempt to send the MIDI message in for processing,
    // if it succeeds right away, the pending flag is reset

    submit_pending_input_midi_message(p_task_data);
}

/*
 * The purpose of this function is to coalesce a stream of received bytes into logical MIDI messages,
 * which always start with a status byte and have between zero and two data bytes. The moment a MIDI
 * message is completed, it is sent to the next stage of processing.
 *
 * There are two caveats here.
 *
 * One is that an attempt to send the complete MIDI message may fail, because the receiver's queue
 * gets full, then the message becomes "pending" and all this task will be doing then is to keep
 * trying to send it again.
 *
 * Another one is a tricky case of a system exclusive message terminated not by EOX, but by the next
 * message's status byte, which is permitted. In this case, the system exclusive message will be sent,
 * but the status byte will have to be not consumed, false is returned and the caller will retry.
 *
 * System exclusive messages are sent as as a sequence of single-byte "messages" and are therefore
 * unlimited in size from this code's perspective. Any other message is sent in its canonical format.
 *
 * The only filtering performed at this level is ignoring the undefined messages.
 */
static bool consume_input_uart_byte(
    input_uart_task_data_t* p_task_data,
    unsigned char input_uart_byte
) {

    // real time messages are single bytes which are recognized separately and sent out of band,
    // even before synchronization or in the middle of another message being transmitted

    if (IS_MIDI_REAL_TIME_MESSAGE(input_uart_byte)) {
        if (!IS_MIDI_UNDEFINED_MESSAGE(input_uart_byte)) { // real time undefined are easy to ignore because they are always one byte
            submit_input_midi_message(
                p_task_data, 
                input_uart_byte,
                INVALID_DATA_BYTE,
                INVALID_DATA_BYTE
            );
        }
        return true;
    }

    // after a reset, data bytes and EOX are skipped before the first real status byte is received

    if (!p_task_data->synchronized) {
        if (!VALID_STATUS_BYTE(input_uart_byte) || input_uart_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END) {
            return true; // skip this byte, keep waiting
        }
        p_task_data->synchronized = true;
    }

    // receiving a system exclusive is done differently from any other message,
    // because its size is not known and is theoretically unbounded

    if (p_task_data->status_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {

        if (VALID_DATA_BYTE(input_uart_byte)) { // received one more data byte for the current system exclusive message
            submit_input_midi_message(
                p_task_data,
                MIDI_MESSAGE_SYSTEM_EXCLUSIVE,
                input_uart_byte,
                INVALID_DATA_BYTE
            );
            return true;
        }

        // a system exclusive message can be terminated by any status byte (of which EOX is also one)

        submit_input_midi_message(
            p_task_data, 
            MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END, 
            INVALID_DATA_BYTE, 
            INVALID_DATA_BYTE
        );

        // from the receiver's point of view, the system exclusive message is now over

        p_task_data->status_byte = INVALID_STATUS_BYTE;
        p_task_data->running_status = INVALID_STATUS_BYTE;

        // if a system exclusive was terminated by a status byte of the next message,
        // that status byte will be handled again and consumed at the next pass,
        // and if it was terminated by EOX, it is consumed right away

        return input_uart_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE_END;
    }

    if (VALID_STATUS_BYTE(input_uart_byte)) {

        if (VALID_STATUS_BYTE(p_task_data->status_byte)) { // status byte received in the middle of the previous message
            reset_protocol_state(p_task_data);
            return true;
        }

        p_task_data->status_byte = input_uart_byte;

        // if we received a SOX, switch to receiving a system exclusive message

        if (input_uart_byte == MIDI_MESSAGE_SYSTEM_EXCLUSIVE) {
            submit_input_midi_message(
                p_task_data, 
                MIDI_MESSAGE_SYSTEM_EXCLUSIVE, 
                INVALID_DATA_BYTE, 
                INVALID_DATA_BYTE
            );
            return true;
        }

        // otherwise we are receiving a regular message, determine the number of data bytes
        // that are expected for its kind, and if it is an undefined message, we disconnect

        uint8_t expected_data_bytes = get_expected_data_bytes(p_task_data->status_byte);
        if (expected_data_bytes == EXPECTED_DATA_BYTES_UNKNOWN) {
            reset_protocol_state(p_task_data);
            return true;
        }

        p_task_data->expected_data_bytes = expected_data_bytes;
        p_task_data->received_data_bytes = 0;

    }
    else if (VALID_DATA_BYTE(input_uart_byte)) {

        if (!VALID_STATUS_BYTE(p_task_data->status_byte)) { // status byte was not received explicitly, but perhaps running status is present

            if (!VALID_STATUS_BYTE(p_task_data->running_status)) { // no running status either
                reset_protocol_state(p_task_data);
                return true;
            }

            // inherit the running status as if it was received explicitly,
            // no need to check for validity this time, because an undefined
            // message could not have become a running status

            p_task_data->status_byte = p_task_data->running_status;
            p_task_data->expected_data_bytes = get_expected_data_bytes(p_task_data->status_byte);
            p_task_data->received_data_bytes = 0;
        }

        p_task_data->data_bytes[p_task_data->received_data_bytes++] = input_uart_byte;
    }

    // check to see if all the data bytes expected for this message have been received (possibly zero)

    if (p_task_data->received_data_bytes == p_task_data->expected_data_bytes) {

        submit_input_midi_message(
            p_task_data, 
            p_task_data->status_byte, 
            p_task_data->data_bytes[0], 
            p_task_data->data_bytes[1]
        );

        if (IS_MIDI_CHANNEL_MESSAGE(p_task_data->status_byte)) { // only a channel message can become current status
            p_task_data->running_status = p_task_data->status_byte;
        }
        else {
            p_task_data->running_status = INVALID_STATUS_BYTE;
        }

        p_task_data->status_byte = INVALID_STATUS_BYTE;
        p_task_data->data_bytes[0] = INVALID_DATA_BYTE;
        p_task_data->data_bytes[1] = INVALID_DATA_BYTE;
    }

    return true;
}

void input_uart_task__receive(evar_task_info_t* p_task_info) {

    input_uart_task_data_t* p_task_data = (input_uart_task_data_t*)p_task_info->p_task_data;

    // if the previous attempt to send the complete MIDI message to the router has failed,
    // keep retrying to send it, before consuming more bytes from the UART queue

    if (p_task_data->input_midi_message_pending) {

        if (!submit_pending_input_midi_message(p_task_data)) {
            return evar_task__keep_running();
        }

        // unblocked, proceed to reading the UART messages
    }

    unsigned char input_uart_byte;

    for (int byte_count = 0; byte_count < 3; ++byte_count) { // this 3 byte limit is artificial, to yield to other tasks occasionally

        // the incoming byte cannot be consumed right away, because of the tricky case of
        // an exclusive message terminated not by EOX, but by the next message's status byte

        evar_mq_result_t mq_result = evar__preview_message(&input_uart_byte, sizeof(input_uart_byte));
        if (mq_result == EVAR_MQ_QUEUE_EMPTY) {
            break;
        }
        else if (mq_result != EVAR_MQ_SUCCESS) {
            evar__crash(CRASH_PREVIEW_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_task__receive: evar__preview_message(input_uart_byte) failed");
        }

        //UARTprintf("<< %02X\n", input_uart_byte);

        if (consume_input_uart_byte(p_task_data, input_uart_byte)) { // this call will decide whether the byte should be consumed
            if (evar__receive_message(&input_uart_byte, sizeof(input_uart_byte)) != EVAR_MQ_SUCCESS) {
                evar__crash(CRASH_RECEIVE_MESSAGE_FAILED | (unsigned short)mq_result, "input_uart_task__receive: evar__receive_message(input_uart_byte) failed");
            }
        }

        // if the received byte completed a message, but it failed
        // to be delivered to the router, switch to retries

        if (p_task_data->input_midi_message_pending) {
            return evar_task__keep_running();
        }
    }

    // light up the LED signaling activity

    GPIOPinWrite(p_task_data->led_port_base, p_task_data->led_pin, 0);

    evar_task__sleep_for(100000);
}

void input_uart_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
