#ifndef MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H
#define MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H

#include "common.h"
#include <midiplan/midiplan.h>

EVAR_TASK(midi_router_task);

typedef struct {

    /* runtime state */

    evar_task_id_t     output_uart_tasks[MIDI_OUT_PORT_COUNT];
    midiplan_context_t midiplan_context;

} midi_router_task_data_t;

typedef enum {

    MIDI_ROUTER_HANDLE_MESSAGE     = 1,
    MIDI_ROUTER_INITIALIZE_DEVICES = 2

} midi_router_task_message_type_t;

typedef struct __packed {

    midi_router_task_message_type_t type;

    union {
        midi_message_t midi_message;
    };

} midi_router_task_message_t;

#endif
