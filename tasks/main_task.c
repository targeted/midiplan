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

#define EVAR_TASK_NAME main_task
#include <evar_task.h>

#include <tasks/main_task.h>

#include <tasks/input_uart_task.h>
#include <tasks/midi_router_task.h>
#include <tasks/output_uart_task.h>

/*
 * Input UART configuration.
 */

void input_uart_interrupt_handler(input_uart_task_data_t* input_uart_task_data);

static input_uart_task_data_t input_uart_task_data_1 = {
    .uart_base          = UART1_BASE,
    .periph_uart        = SYSCTL_PERIPH_UART1,
    .uart_port_base     = GPIO_PORTB_BASE,
    .uart_rx_pin        = GPIO_PIN_0,
    .uart_rx_pin_config = GPIO_PB0_U1RX,
    .led_port_base      = GPIO_PORTB_BASE,
    .led_pin            = GPIO_PIN_6
};

/*
 * This thunk binds the parameter to the correct UART structure.
 * Currently there is only one input UART, so there is technically
 * no need for it, but I keep it for future extensibility.
 */
static void input_uart_1_interrupt_handler(void) {
    input_uart_interrupt_handler(&input_uart_task_data_1);
}

/*
 * MIDI router configuration.
 */

static midi_router_task_data_t midi_router_task_data;

/*
 * Output UARTs configuration.
 */

output_uart_task_data_t output_uart_task_data_1 = {
    .midi_out_port      = MIDI_OUT_PORT_1,
    .uart_base          = UART2_BASE,
    .periph_uart        = SYSCTL_PERIPH_UART2,
    .uart_port_base     = GPIO_PORTD_BASE,
    .uart_tx_pin        = GPIO_PIN_7,
    .uart_tx_pin_config = GPIO_PD7_U2TX,
    .led_port_base      = GPIO_PORTB_BASE,
    .led_pin            = GPIO_PIN_2
};

output_uart_task_data_t output_uart_task_data_2 = {
    .midi_out_port      = MIDI_OUT_PORT_2,
    .uart_base          = UART3_BASE,
    .periph_uart        = SYSCTL_PERIPH_UART3,
    .uart_port_base     = GPIO_PORTC_BASE,
    .uart_tx_pin        = GPIO_PIN_7,
    .uart_tx_pin_config = GPIO_PC7_U3TX,
    .led_port_base      = GPIO_PORTB_BASE,
    .led_pin            = GPIO_PIN_3
};

output_uart_task_data_t output_uart_task_data_3 = {
    .midi_out_port      = MIDI_OUT_PORT_3,
    .uart_base          = UART4_BASE,
    .periph_uart        = SYSCTL_PERIPH_UART4,
    .uart_port_base     = GPIO_PORTC_BASE,
    .uart_tx_pin        = GPIO_PIN_5,
    .uart_tx_pin_config = GPIO_PC5_U4TX,
    .led_port_base      = GPIO_PORTB_BASE,
    .led_pin            = GPIO_PIN_4
};

output_uart_task_data_t output_uart_task_data_4 = {
    .midi_out_port      = MIDI_OUT_PORT_4,
    .uart_base          = UART5_BASE,
    .periph_uart        = SYSCTL_PERIPH_UART5,
    .uart_port_base     = GPIO_PORTE_BASE,
    .uart_tx_pin        = GPIO_PIN_5,
    .uart_tx_pin_config = GPIO_PE5_U5TX,
    .led_port_base      = GPIO_PORTB_BASE,
    .led_pin            = GPIO_PIN_5
};

void main_task__initialize(evar_task_info_t* p_task_info) {

    EVAR_UNUSED(p_task_info);

    // output UART tasks

    evar_task_id_t output_uart_task_1 = evar__create_task(output_uart_task, &output_uart_task_data_1);
    if (output_uart_task_1 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_1) failed");
    }

    evar_task_id_t output_uart_task_2 = evar__create_task(output_uart_task, &output_uart_task_data_2);
    if (output_uart_task_2 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_2) failed");
    }

    evar_task_id_t output_uart_task_3 = evar__create_task(output_uart_task, &output_uart_task_data_3);
    if (output_uart_task_3 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_3) failed");
    }

    evar_task_id_t output_uart_task_4 = evar__create_task(output_uart_task, &output_uart_task_data_4);
    if (output_uart_task_4 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_4) failed");
    }

    // MIDI router task

    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_1] = output_uart_task_1;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_2] = output_uart_task_2;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_3] = output_uart_task_3;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_4] = output_uart_task_4;

    evar_task_id_t midi_router_task_1 = evar__create_task(midi_router_task, &midi_router_task_data);
    if (midi_router_task_1 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(midi_router_task_1) failed");
    }

    // input UART task

    input_uart_task_data_1.interrupt_handler = input_uart_1_interrupt_handler;
    input_uart_task_data_1.midi_router_task  = midi_router_task_1;

    evar_task_id_t input_uart_task_1 = evar__create_task(input_uart_task, &input_uart_task_data_1);
    if (input_uart_task_1 == EVAR_INVALID_TASK_ID) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(input_uart_task_1) failed");
    }

    UARTprintf("\nMIDIplan running...\n");

    evar_task__sleep();
}

void main_task__run(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void main_task__wake_up(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void main_task__receive(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}

void main_task__cleanup(evar_task_info_t* p_task_info) {
    EVAR_UNUSED(p_task_info);
}
