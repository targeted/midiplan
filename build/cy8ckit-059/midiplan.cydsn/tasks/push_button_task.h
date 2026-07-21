#ifndef MIDIPLAN_TASKS_PUSH_BUTTON_TASK_H
#define MIDIPLAN_TASKS_PUSH_BUTTON_TASK_H

#include <CyLib.h>
#include "common.h"

EVAR_TASK(push_button_task);

typedef uint8_t push_button_id_t;

typedef struct {

    /* initialization parameters */

    struct {
        cyisraddress interrupt_handler;
        void (*SetVector) (cyisraddress interrupt_handler);
        void (*Enable)    (void);
    } IRQ;

    evar_task_id_t   ui_task;
    push_button_id_t button_id;

} push_button_task_data_t;

void push_button_interrupt_handler(push_button_task_data_t* p_task_data);

#endif
