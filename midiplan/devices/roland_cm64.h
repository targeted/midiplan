#ifndef MIDIPLAN_DEVICES_ROLAND_CM64_H
#define MIDIPLAN_DEVICES_ROLAND_CM64_H

#include <midiplan/device.h>

extern const midiplan_device_t roland_cm64;

#define ROLAND_CM64_LOWEST_NOTE      (0)
#define ROLAND_CM64_MIDDLE_C        (60)
#define ROLAND_CM64_HIGHEST_NOTE   (127)

#define ROLAND_CM64_RANGE_DEFAULT (0x0E)

#endif
