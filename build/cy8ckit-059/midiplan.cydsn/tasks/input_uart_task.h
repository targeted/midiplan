#ifndef MIDIPLAN_TASKS_INPUT_UART_TASK_H
#define MIDIPLAN_TASKS_INPUT_UART_TASK_H

#include <CyLib.h>
#include "common.h"
#include <midiplan/midi_input.h>

EVAR_TASK(input_uart_task);

typedef struct {

    /* initialization parameters */

    struct {
        cyisraddress   interrupt_handler;
        void           (*Start)           (void);
        void           (*IRQ_StartEx)     (cyisraddress interrupt_handler);
        uint8_t        (*GetRxBufferSize) (void);
        uint8_t        (*ReadRxData)      (void);
    } UART;

    struct {
        void           (*Write)           (uint8_t value);
    } LED;

    evar_task_id_t     midi_router_task;

    /* runtime state */

    evar_task_id_t     input_uart_task;
    midi_input_state_t midi_input_state;

} input_uart_task_data_t;

typedef struct __packed {

    uint8_t input_uart_byte;

} input_uart_task_message_t;

void input_uart_interrupt_handler(input_uart_task_data_t* p_task_data);

#endif
