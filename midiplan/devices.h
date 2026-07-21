#ifndef MIDIPLAN_DEVICES_H
#define MIDIPLAN_DEVICES_H

#include "device.h"

/*
 * One bit per program/note to indicate what is routed to the device.
 */
typedef struct {

    // in terms of *input* program/note, this is used to filter the incoming notes before any handling

    uint32_t melodic_programs_bitmap[128 / 32]; // one bit per program, set to 1 if the program is routed to this device
    uint32_t percussion_notes_bitmap[128 / 32]; // one bit per note, set to 1 if the note is routed to this device

} midiplan_device_routing_t;

/*
 * Typical routing configurations.
 */
extern const midiplan_device_routing_t route_all;
extern const midiplan_device_routing_t route_none;
extern const midiplan_device_routing_t route_melodic;
extern const midiplan_device_routing_t route_percussion;

/*
 * This structure is used for bonding of multiple identical devices
 * playing as one, selects the 1/Nth fraction of the note space.
 */
typedef struct {

    uint8_t device_index;
    uint8_t device_count;

} midiplan_device_bonding_t;

/*
 * The global state of currently attached devices.
 */
typedef struct {

    const midiplan_device_t*  p_device;
    midiplan_device_state_t   state;

    midiplan_device_routing_t routing;
    midiplan_device_bonding_t bonding;

} attached_device_t;

extern attached_device_t devices[MIDI_OUT_PORT_COUNT];

/*
 * This is the order in which the devices will be considered to play a note on.
 * The logic behind this is as follows:
 * 1. We go "left to right", from port 1 to port 4.
 * 2. Bonded devices are treated as one logical device, therefore if identical
 *    devices are configured on ports 2 and 4, then the order will be 1-2-4-3,
 *    but if 1 and 3 were also identical, then 1-3-2-4.
 * 3. Specific (non-GM-compatible) devices consume the notes they play,
 *    GM-compatible devices are transparent, the note is propagated.
 */
typedef struct {

    midi_out_port_t out_port;
    bool            consume_note;

} device_order_t;

extern device_order_t device_order[MIDI_OUT_PORT_COUNT];

void configure_devices(void);
void initialize_devices(void);

/*
 * Returns true if the note should be routed to the device.
 * It accounts for routing table and bonding configuration.
 */
bool route_note_to_device(
    midi_out_port_t out_port,
    midi_channel_t in_channel,
    program_t in_program,
    note_t in_note
);

#endif
