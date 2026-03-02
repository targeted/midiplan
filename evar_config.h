#ifndef EVAR_CONFIG_H
#define EVAR_CONFIG_H

// uncomment to enable internal asserts
#define EVAR_DEBUG

#define EVAR_MAX_TASKS (8)
#define EVAR_TIMER_FREQUENCY (976)
#define EVAR_USEC_TO_TICKS(usec) ((usec) >> 10)
#define EVAR_TICKS_TO_USEC(ticks) ((ticks) << 10)

#endif
