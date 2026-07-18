#ifndef MIDIPLAN_TASKS_INPUT_UART_TASK_H
#define MIDIPLAN_TASKS_INPUT_UART_TASK_H

#include <CyLib.h>
#include <tasks/common.h>
#include <midiplan/midi_input.h>

EVAR_TASK(input_uart_task);

typedef struct {

    /* initialization parameters */

    cyisraddress       interrupt_handler;
    void               (*UART_Start)           (void);
    void               (*UART_IRQ_StartEx)     (cyisraddress interrupt_handler);
    uint8_t            (*UART_GetRxBufferSize) (void);
    uint8_t            (*UART_ReadRxData)      (void);
    void               (*LED_Write)            (uint8_t value);
    
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
