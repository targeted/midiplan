#ifndef MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H
#define MIDIPLAN_TASKS_MIDI_ROUTER_TASK_H

#include <tasks/common.h>
#include <tasks/output_uart_task.h>

EVAR_TASK(midi_router_task);

typedef struct {

    evar_task_id_t output_uart_tasks[MIDI_OUT_PORT_COUNT];
    
} midi_router_task_data_t;

#endif
