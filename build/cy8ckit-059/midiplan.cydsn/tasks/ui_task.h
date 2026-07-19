#ifndef MIDIPLAN_TASKS_UI_TASK_H
#define MIDIPLAN_TASKS_UI_TASK_H

#include <CyLib.h>
#include "common.h"
#include "push_button_task.h"

EVAR_TASK(ui_task);

typedef struct {

    /* initialization parameters */

    evar_task_id_t midi_router_task;

} ui_task_data_t;

typedef struct __packed {

    push_button_id_t button_id;

} ui_task_message_t;

#define INIT_BUTTON_ID ((push_button_id_t)1)

#endif
