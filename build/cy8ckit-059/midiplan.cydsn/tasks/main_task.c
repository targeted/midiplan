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

#include "input_uart_task.h"
#include "midi_router_task.h"
#include "output_uart_task.h"
#include "ui_task.h"
#include "push_button_task.h"
#include <midiplan/devices.h>
#include <midiplan/config.h>

/*
 * Input UART configuration.
 */

static void INPUT_UART_1_interrupt_handler(void);

static input_uart_task_data_t input_uart_task_data_1 = {
    .UART = {
        .interrupt_handler = INPUT_UART_1_interrupt_handler,
        .Start             = INPUT_UART_1_Start,
        .IRQ_StartEx       = INPUT_UART_1_IRQ_StartEx,
        .GetRxBufferSize   = INPUT_UART_1_GetRxBufferSize,
        .ReadRxData        = INPUT_UART_1_ReadRxData
    },
    .LED = {
        .Write             = INPUT_UART_1_LED_Write
    }
};

static void INPUT_UART_1_interrupt_handler(void) {
    input_uart_interrupt_handler(&input_uart_task_data_1);
}

/*
 * MIDI router configuration.
 */

static midi_router_task_data_t midi_router_task_data;

/*
 * Output UARTs configuration.
 */

static bool OUTPUT_UART_1_FIFO_FULL(void) { // these thunks are needed because the TX_STS_FIFO_FULL flag is not constant
    return (OUTPUT_UART_1_ReadTxStatus() & OUTPUT_UART_1_TX_STS_FIFO_FULL) != 0;
}

static output_uart_task_data_t output_uart_task_data_1 = {
    .midi_out_port     = MIDI_OUT_PORT_1,
    .UART_Start        = OUTPUT_UART_1_Start,
    .UART_FIFO_FULL    = OUTPUT_UART_1_FIFO_FULL,
    .UART_WriteTxData  = OUTPUT_UART_1_WriteTxData,
    .LED_Write         = OUTPUT_UART_1_LED_Write
};

static bool OUTPUT_UART_2_FIFO_FULL(void) {
    return (OUTPUT_UART_2_ReadTxStatus() & OUTPUT_UART_2_TX_STS_FIFO_FULL) != 0;
}

static output_uart_task_data_t output_uart_task_data_2 = {
    .midi_out_port     = MIDI_OUT_PORT_2,
    .UART_Start        = OUTPUT_UART_2_Start,
    .UART_FIFO_FULL    = OUTPUT_UART_2_FIFO_FULL,
    .UART_WriteTxData  = OUTPUT_UART_2_WriteTxData,
    .LED_Write         = OUTPUT_UART_2_LED_Write
};

static bool OUTPUT_UART_3_FIFO_FULL(void) {
    return (OUTPUT_UART_3_ReadTxStatus() & OUTPUT_UART_3_TX_STS_FIFO_FULL) != 0;
}

static output_uart_task_data_t output_uart_task_data_3 = {
    .midi_out_port     = MIDI_OUT_PORT_3,
    .UART_Start        = OUTPUT_UART_3_Start,
    .UART_FIFO_FULL    = OUTPUT_UART_3_FIFO_FULL,
    .UART_WriteTxData  = OUTPUT_UART_3_WriteTxData,
    .LED_Write         = OUTPUT_UART_3_LED_Write
};

static bool OUTPUT_UART_4_FIFO_FULL(void) {
    return (OUTPUT_UART_4_ReadTxStatus() & OUTPUT_UART_4_TX_STS_FIFO_FULL) != 0;
}

static output_uart_task_data_t output_uart_task_data_4 = {
    .midi_out_port     = MIDI_OUT_PORT_4,
    .UART_Start        = OUTPUT_UART_4_Start,
    .UART_FIFO_FULL    = OUTPUT_UART_4_FIFO_FULL,
    .UART_WriteTxData  = OUTPUT_UART_4_WriteTxData,
    .LED_Write         = OUTPUT_UART_4_LED_Write
};

/*
 * UI mediator task.
 */
static ui_task_data_t ui_task_data_1 = {
};

/*
 * Push buttons.
 */

static void init_button_interrupt_handler(void);

static push_button_task_data_t init_button_task_data = {
    .IRQ = {
        .interrupt_handler = init_button_interrupt_handler,
        .SetVector         = INIT_BUTTON_IRQ_SetVector,
        .Enable            = INIT_BUTTON_IRQ_Enable
    },
    .button_id = INIT_BUTTON_ID
};

static void init_button_interrupt_handler(void) {
    push_button_interrupt_handler(&init_button_task_data);
}

void main_task__initialize(evar_task_info_t* p_task_info) {

    EVAR_UNUSED(p_task_info);
    
    // initialize chip/board resources
    
    EEPROM_Start();
        
    DEBUG_UART_Start();
    
    // load configuration from EEPROM
    
    // create output UART tasks

    evar_task_id_t output_uart_task_1 = evar__create_task(output_uart_task, &output_uart_task_data_1);
    if (!VALID_TASK_ID(output_uart_task_1)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_1) failed");
    }

    evar_task_id_t output_uart_task_2 = evar__create_task(output_uart_task, &output_uart_task_data_2);
    if (!VALID_TASK_ID(output_uart_task_2)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_2) failed");
    }

    evar_task_id_t output_uart_task_3 = evar__create_task(output_uart_task, &output_uart_task_data_3);
    if (!VALID_TASK_ID(output_uart_task_3)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_3) failed");
    }

    evar_task_id_t output_uart_task_4 = evar__create_task(output_uart_task, &output_uart_task_data_4);
    if (!VALID_TASK_ID(output_uart_task_4)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(output_uart_task_4) failed");
    }

    // create MIDI router task

    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_1] = output_uart_task_1;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_2] = output_uart_task_2;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_3] = output_uart_task_3;
    midi_router_task_data.output_uart_tasks[MIDI_OUT_PORT_4] = output_uart_task_4;

    evar_task_id_t midi_router_task_1 = evar__create_task(midi_router_task, &midi_router_task_data);
    if (!VALID_TASK_ID(midi_router_task_1)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(midi_router_task_1) failed");
    }

    // create input UART task

    input_uart_task_data_1.midi_router_task = midi_router_task_1;

    evar_task_id_t input_uart_task_1 = evar__create_task(input_uart_task, &input_uart_task_data_1);
    if (!VALID_TASK_ID(input_uart_task_1)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(input_uart_task_1) failed");
    }
    
    // create UI task

    ui_task_data_1.midi_router_task = midi_router_task_1;
    
    evar_task_id_t ui_task_1 = evar__create_task(ui_task, &ui_task_data_1);
    if (!VALID_TASK_ID(ui_task_1)) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(ui_task_1) failed");
    }

    // create push button tasks

    init_button_task_data.ui_task = ui_task_1;
    
    evar_task_id_t init_button_task_1 = evar__create_task(push_button_task, &init_button_task_data);
    if (init_button_task_1 != EVAR_TASK_INITIALIZED) {
        evar__crash(CRASH_CREATE_TASK_FAILED, "main_task__initialize: evar__create_task(init_button_task_1) failed");
    }

    DEBUG_PRINT("MIDIplan running\r\n");

    // this task will now exit
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
