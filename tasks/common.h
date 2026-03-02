#ifndef MIDIPLAN_TASKS_COMMON_H
#define MIDIPLAN_TASKS_COMMON_H

#include <evar.h>
#include <midiplan/midiplan.h>

#define CRASH_CREATE_TASK_FAILED        (0x0100)
#define CRASH_RECEIVE_MESSAGE_FAILED    (0x0200)
#define CRASH_PREVIEW_MESSAGE_FAILED    (0x0300)
#define CRASH_SEND_ASYNC_MESSAGE_FAILED (0x0400)
#define CRASH_SEND_MESSAGE_FAILED       (0x0500)
#define CRASH_MESSAGE_TOO_LARGE         (0x0600)

#endif
