#ifndef MIDIPLAN_TASKS_OUTPUT_UART_TASK_H
#define MIDIPLAN_TASKS_OUTPUT_UART_TASK_H

#include <evar.h>
#include "common.h"
#include <midiplan/device.h>

EVAR_TASK(output_uart_task);

typedef struct {

    /* initialization parameters */

    midi_out_port_t    midi_out_port;
    uint32_t           uart_base;
    uint32_t           periph_uart;
    uint32_t           uart_port_base;
    uint32_t           uart_tx_pin;
    uint32_t           uart_tx_pin_config;
    uint32_t           led_port_base;
    uint32_t           led_pin;

    /* runtime state */

    status_byte_t      running_status;   // keeps track of the previous status

    struct {
        uint8_t        bytes[3];         // up to 3 bytes of a literal data message being sent
        uint8_t        size;             // number of bytes to send
        uint8_t        offs;             // offset to the next byte to send
    } message_data; // active when sending an ad-hoc message received from the input UART

    struct {
        const uint8_t* p_next_byte;      // points to the next byte in the custom sequence being sent
        custom_sequence_parameters_t parameters; // parameters for the custom sequence being sent
        struct {
            uint8_t    roland_checksum;  // running value of a Roland-style checksum
        } variables;
        uint8_t        current_status;   // currently active status byte (can be regular or SOX)
        uint8_t        data_byte_count;  // number of data bytes expected to be ahead
    } custom_sequence; // active when sending a custom device-specific sequence

    evar_timestamp_t   delay_start;      // when in delay, the starting moment of the delay
    evar_time_delta_t  delay_usec;       // when in delay, duration of the delay > 0

} output_uart_task_data_t;

typedef struct {
    custom_sequence_id_t custom_sequence_id;
    union {
        midi_message_t midi_message;
        custom_sequence_parameters_t custom_sequence_parameters;
    };
} output_uart_task_message_t;

// this does not necessarily have to be 4 bytes, but efforts have been made
// to make it as small as possible, and that was the achieved minimum
EVAR_ASSERT(sizeof(output_uart_task_message_t) == 4, sizeof_output_uart_task_message_t);

#endif
