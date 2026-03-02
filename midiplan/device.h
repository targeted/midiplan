#ifndef MIDIPLAN_DEVICE_H
#define MIDIPLAN_DEVICE_H

#include <stdbool.h>
#include <midiplan/types.h>
#include <midiplan/config.h>
#include <midiplan/note_entries.h>

/*
 * This is a read-only configuration structure that contains all kinds of maps describing the device.
 */
typedef struct {

    midi_channel_t basic_channel;

    /* the following affect the viability of a note being played */

    uint8_t max_melodic_notes;     // how many notes can be playing on melodic programs at the same time, including percussion if max_percussion_notes = 0
    uint8_t max_percussion_notes;  // how many notes can be playing on percussion program at the same time, if 0 then percussion notes are accounted as melodic
    uint8_t max_melodic_programs;  // how many melodic programs can be playing at the same time, including percussion program if max_percussion_notes = 0
    uint8_t max_notes_per_program; // how many notes can be played at the same time for any given melodic program, including percussion if max_percussion_notes = 0
    
    /* the following affect the channel association process */
    
    uint8_t monotimbral_channels;  // 0 or 1, 1 if there can't be more than one program playing over one channel concurrently, 0 if many programs can play over one channel concurrently
    uint8_t max_notes_per_channel; // how many notes can be played on one channel at the same time (on one program or different programs), 0 if there is no restriction

#define USES_MELODIC_TIMBRE(DEVICE, PROGRAM) (IS_MELODIC_PROGRAM(PROGRAM) || ((DEVICE)->max_percussion_notes == 0))
#define USES_PERCUSSION_TIMBRE(DEVICE, PROGRAM) (IS_PERCUSSION_PROGRAM(PROGRAM) && ((DEVICE)->max_percussion_notes != 0))

    /* supported controller-like messages */

    uint8_t key_pressure;          // 0 or 1
    uint8_t channel_pressure;      // 0 or 1
    uint8_t pitch_bend;            // 0 or 1

    /* melodic programs mapping */

    struct {

        uint8_t program;           // maps a GM melodic program 0-127 to a device melodic program N 0-127 (if the high bit is clear in N)
                                   // or to a percussion note N 0-127 when the high bit is set in N (i.e. or-ed with PERCUSSION_PROGRAM)

        uint8_t flags;             // bits ....xxxx contain 0x00-0x0F as an index 0-15 into the following melodic_note_ranges array
                                   // bits .xxx.... contain 0 for no volume change, 7 for silence or 1-6 as an index 0-5 into global velocity_curves translation tabless

#define MELODIC_PROGRAM_RANGE(flags)    (((flags) & 0x0F)     )
#define MELODIC_PROGRAM_VELOCITY(flags) (((flags) & 0x70) >> 4)

    } melodic_programs[128];

    struct {
        note_t lowest_note;        // changing lowest and highest notes allows for split keyboard configuration
        note_t middle_c;           // the received middle C would be shifted to this note, this allows arbitrary transposition
        note_t highest_note;
    } melodic_note_ranges[16];

    /* percussion notes mapping */

    struct {

        program_t program;         // normally PERCUSSION_PROGRAM but some devices would re-route percussion back to melodic effects
        note_t note;
        uint8_t flags;             // bits .xxx.... contain 0 for no volume change, 7 for silence or 1-6 as an index 0-5 into global velocity_curves translation tabless

#define PERCUSSION_NOTE_VELOCITY(flags) (((flags) & 0x70) >> 4)

    } percussion_notes[128];

    /* after a GM program/note has been translated into a device-specific program/note, the following are expressed in device terms */

    uint32_t melodic_channels_bitmaps_refs[128 / 16];    // two bits per device program, as 0-3 index into the following array
    midi_channels_bitmap_t melodic_channels_bitmaps[4];  // of bitmaps of channels on which such program can be accepted

    midi_channels_bitmap_t percussion_channels_bitmap;   // the bitmap of channels on which percussion notes can be accepted

    /* controllers mapping */

    uint32_t controllers_bitmap[128 / 32];               // one bit per controller number, set to 1 if supported by the device

    /* offsets of parameterized sequences into the following array of messages */

    uint16_t initialization_sequence_offset;
    uint16_t program_change_sequence_offset;
    uint16_t note_on_sequence_offset;
    uint16_t note_off_sequence_offset;
    
#define INVALID_SEQUENCE_OFFSET (0xFFFF)
    
    /* variable-sized buffer containing device-specific sequences of parameterized messages */
    
    uint8_t custom_sequences[];

} midiplan_device_t;

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
extern midiplan_device_routing_t route_all;
extern midiplan_device_routing_t route_none;
extern midiplan_device_routing_t route_melodic;
extern midiplan_device_routing_t route_percussion;

/*
 * These pre-calculated lookup tables are used to turn volume up/down when a note is translated.
 * The first three are +2dB, +4dB, +6dB, the last three are -2dB, -4dB, -6dB
 */
extern data_byte_t velocity_curves[6][127];

/*
 * These are not direct indexes into the above table, but all possible
 * values of 3 bits in device configuration flags for note volume control.
 */
#define VELOCITY_DEFAULT   (0x0) // note velocity is not changed
#define VELOCITY_UP_2DB    (0x1) // -> velocity curve [0] = +2dB
#define VELOCITY_UP_4DB    (0x2) // -> velocity curve [1] = +4dB
#define VELOCITY_UP_6DB    (0x3) // -> velocity curve [2] = +6dB
#define VELOCITY_DOWN_2DB  (0x4) // -> velocity curve [3] = -2dB
#define VELOCITY_DOWN_4DB  (0x5) // -> velocity curve [4] = -4dB
#define VELOCITY_DOWN_6DB  (0x6) // -> velocity curve [5] = -6dB
#define VELOCITY_SILENCE   (0x7) // the note is not played at all

/*
 * These versions are to be used in device flags configuration, 
 * putting the bits in place.
 */
#define VOLUME_DEFAULT     ((VELOCITY_DEFAULT)  << 4)
#define VOLUME_UP_2DB      ((VELOCITY_UP_2DB)   << 4)
#define VOLUME_UP_4DB      ((VELOCITY_UP_4DB)   << 4)
#define VOLUME_UP_6DB      ((VELOCITY_UP_6DB)   << 4)
#define VOLUME_DOWN_2DB    ((VELOCITY_DOWN_2DB) << 4)
#define VOLUME_DOWN_4DB    ((VELOCITY_DOWN_4DB) << 4)
#define VOLUME_DOWN_6DB    ((VELOCITY_DOWN_6DB) << 4)
#define VOLUME_SILENCE     ((VELOCITY_SILENCE)  << 4)

/*
 * This structure describes bonding of multiple identical devices playing as one.
 */
typedef struct {

    // in terms of *output* program/note, this is the 1/Nth fraction
    // of the namespace which this device will handle

    uint8_t device_index;
    uint8_t device_count;

} midiplan_device_bonding_t;

/*
 * Used to produce deterministic "random" numbers to pick a device from a bonding set.
 */
uint8_t device_bonding_hash(midi_channel_t channel, program_t program);

/*
 * This is the runtime state of the device, expressed in output terms.
 */
typedef struct {

    uint8_t melodic_programs_playing;              // how many different *output* programs are currently playing
    uint8_t melodic_notes_playing;                 // how many notes are currently playing on all *output* melodic programs together (sum of melodic_notes_per_program)
    uint8_t melodic_notes_per_program[128 + 1];    // number of notes playing on that *output* program (128 melodic +1 for percussion)
    uint8_t percussion_notes_playing;              // how many notes are currently playing on the percussion program

    struct {
        uint8_t         notes_playing;             // how many notes (on any program) are playing on this channel, including percussion
        note_entry_id_t last_note_entry_id;        // the last note initiated on this channel (erased when that note is turned off)
    } channels[MIDI_CHANNEL_COUNT]; 
    
    bool initialization_pending;                   // true if the device's initialization sequence is pending to be transmitted

} midiplan_device_state_t;

/*
 * This is called at startup and during handling of "all notes off" after a device has become idle.
 */
void reset_device_state(midiplan_device_state_t* p_device_state);

/*
 * Returns the set of channels on which this device program/note can be played.
 */
midi_channels_bitmap_t get_note_channels(
    const midiplan_device_t* p_device,
    program_t                out_program,
    note_t                   out_note
);

/*
 * Translates/filters a note on parameters for the particular device.
 * It is crucial that note numbers are translated the same for all note
 * messages, on, off and key pressure, and for certain controllers.
 */
bool translate_note(
    const midiplan_device_t* p_device,
    program_t                in_program,
    note_t                   in_note,
    data_byte_t              in_velocity,
    program_t*               p_out_program,
    note_t*                  p_out_note,
    data_byte_t*             p_out_velocity
);

/*
 * Filters controller change messages for the particular device.
 */
bool controller_supported(
    const midiplan_device_t* p_device,
    midi_control_number_t control_number
);

/*
 * Filters key pressure messages for the particular device.
 */
bool key_pressure_supported(
    const midiplan_device_t* p_device
);

/*
 * Filters channel pressure messages for the particular device.
 */
bool channel_pressure_supported(
    const midiplan_device_t* p_device
);

/*
 * Filters pitch bend messages for the particular device.
 */
bool pitch_bend_supported(
    const midiplan_device_t* p_device
);

#endif
