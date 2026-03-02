#ifndef MIDIPLAN_DEVICES_H
#define MIDIPLAN_DEVICES_H

#include <midiplan/types.h>
#include <midiplan/config.h>
#include <midiplan/device.h>
#include <midiplan/devices/casio_csm1.h>
#include <midiplan/devices/gm_device.h>
#include <midiplan/devices/kawai_phm.h>
#include <midiplan/devices/kawai_xs1.h>
#include <midiplan/devices/null_device.h>
#include <midiplan/devices/roland_gr09.h>
#include <midiplan/devices/yamaha_dom30.h>
#include <midiplan/devices/yamaha_emr1.h>
#include <midiplan/devices/yamaha_emt1.h>
#include <midiplan/devices/yamaha_fb01.h>
#include <midiplan/devices/yamaha_rx21.h>
#include <midiplan/devices/zoom_rt234.h>

typedef struct {
    const midiplan_device_t* p_device;
    midiplan_device_routing_t routing;
    midiplan_device_bonding_t bonding;
    midiplan_device_state_t state;
} midiplan_devices_t[MIDI_OUT_PORT_COUNT];

extern midiplan_devices_t devices;

void configure_devices(void);
void initialize_device_states(void);

#endif
