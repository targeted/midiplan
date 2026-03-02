#ifndef MIDIPLAN_TASKS_OUTPUT_UART_TASK_H
#define MIDIPLAN_TASKS_OUTPUT_UART_TASK_H

#include <tasks/common.h>

EVAR_TASK(output_uart_task);

typedef struct {

    midi_out_port_t   midi_out_port;
    uint32_t          uart_base;
    uint32_t          periph_uart;
    uint32_t          uart_port_base;
    uint32_t          uart_tx_pin;
    uint32_t          uart_tx_pin_config;
    uint32_t          led_port_base;
    uint32_t          led_pin;

    status_byte_t     prev_status_byte;      // used to track the running status

    uint8_t           message_bytes[3];      // the bytes of the message being sent
    uint8_t           message_bytes_to_send; // number of actual bytes in the above array
    uint8_t           message_bytes_sent;    // number of bytes already sent to the UART

    evar_timestamp_t  delay_start;
    evar_time_delta_t delay_usec;

} output_uart_task_data_t;

#endif
