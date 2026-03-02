#ifndef MIDIPLAN_TASKS_INPUT_UART_TASK_H
#define MIDIPLAN_TASKS_INPUT_UART_TASK_H

#include <tasks/common.h>
#include <tasks/midi_router_task.h>

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

    bool           synchronized;
    status_byte_t  status_byte;
    data_byte_t    data_bytes[2];
    uint8_t        expected_data_bytes;
    uint8_t        received_data_bytes;
    status_byte_t  running_status;

    bool           input_midi_message_pending;
    midi_message_t input_midi_message;
    
    evar_task_id_t input_uart_task;
    
} input_uart_task_data_t;

#endif
