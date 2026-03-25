#ifndef MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H
#define MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H

#include <evar.h>
#include "common.h"

EVAR_TASK(midi_router_task);

typedef struct {
    
    evar_task_id_t output_uart_tasks[MIDI_OUT_PORT_COUNT];
    
} midi_router_task_data_t;

typedef struct {

    midi_message_t midi_message;

} midi_router_task_message_t;

#endif
