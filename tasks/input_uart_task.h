#ifndef MIDIPLAN_TASKS_INPUT_UART_TASK_H
#define MIDIPLAN_TASKS_INPUT_UART_TASK_H

#include <evar.h>
#include <common.h>

EVAR_TASK(input_uart_task);

typedef struct {

    uint32_t       uart_base;
    evar_task_id_t midi_router_task;
    uint32_t       periph_uart;
    uint32_t       uart_port_base;
    uint32_t       uart_rx_pin;
    uint32_t       uart_rx_pin_config;
    void           (*interrupt_handler)(void);
    uint32_t       led_port_base;
    uint32_t       led_pin;

    evar_task_id_t input_uart_task;

    bool           synchronized;
    status_byte_t  status_byte;
    data_byte_t    data_bytes[2];
    uint8_t        expected_data_bytes;
    uint8_t        received_data_bytes;
    status_byte_t  running_status;

} input_uart_task_data_t;

typedef struct {

    unsigned char input_uart_byte;

} input_uart_task_message_t;

#endif
