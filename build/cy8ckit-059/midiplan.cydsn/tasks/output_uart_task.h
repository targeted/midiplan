#ifndef MIDIPLAN_TASKS_OUTPUT_UART_TASK_H
#define MIDIPLAN_TASKS_OUTPUT_UART_TASK_H

#include <CyLib.h>
#include <tasks/common.h>
#include <midiplan/midi_output.h>

EVAR_TASK(output_uart_task);

typedef struct {

    /* initialization parameters */

    midi_out_port_t    midi_out_port;

    void               (*UART_Start)       (void);
    bool               (*UART_FIFO_FULL)   (void); 
    void               (*UART_WriteTxData) (uint8_t txDataByte);
    void               (*LED_Write)        (uint8_t value);
    
    /* runtime state */

    evar_timestamp_t   delay_start; // when in delay, the starting moment of the delay
    evar_time_delta_t  delay_usec;  // when in delay, duration of the delay > 0

    midi_output_state_t midi_output_state;
    
} output_uart_task_data_t;

typedef struct __packed {
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
