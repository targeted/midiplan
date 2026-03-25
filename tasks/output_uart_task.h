#ifndef MIDIPLAN_TASKS_OUTPUT_UART_TASK_H
#define MIDIPLAN_TASKS_OUTPUT_UART_TASK_H

#include <evar.h>
#include "common.h"

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

    status_byte_t     prev_status_byte;      // tracks the running status when sending

    uint8_t           message_bytes[3];      // the bytes of the message being sent
    uint8_t           message_bytes_to_send; // number of actual bytes in the above array
    uint8_t           message_bytes_sent;    // number of bytes already sent to the UART

    evar_timestamp_t  delay_start;           // when in delay, the starting moment of the delay
    evar_time_delta_t delay_usec;            // when in delay, duration of the delay > 0

} output_uart_task_data_t;

typedef struct {

    midi_message_t midi_message;
    
} output_uart_task_message_t;

#endif
