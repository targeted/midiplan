#ifndef MIDIPLAN_DEVICE_H
#define MIDIPLAN_DEVICE_H

#include "types.h"
#include "config.h"
#include "note_entries.h"

/*
 * This is an immutable read-only configuration structure
 * that contains all kinds of maps describing the device.
 */
typedef struct {

    char* model_name;              // NULL-terminated printable ASCII "Manufacturer Model"

    /* the following affect the viability of a note being played */

    uint8_t max_melodic_notes;     // how many notes can be playing on all melodic programs at the same time, including percussion if max_percussion_notes = 0
    uint8_t max_percussion_notes;  // how many notes can be playing on the percussion program at the same time, if 0 then percussion notes are accounted as melodic
    uint8_t max_melodic_programs;  // how many melodic programs can be playing at the same time, including percussion program if max_percussion_notes = 0
    uint8_t max_notes_per_program; // how many notes can be played at the same time for any given melodic program, including percussion if max_percussion_notes = 0

    /* the following affect the channel association process */

    uint8_t monotimbral_channels;  // 0 or 1, 1 if there can't be more than one program playing over one channel concurrently, 0 if many programs can play over one channel concurrently
    uint8_t max_notes_per_channel[MIDI_CHANNEL_COUNT]; // how many notes can be played on each channel at the same time (on one program or different programs), 0 if there is no restriction

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

    /* pointers to optional variable-sized arrays of messages, used instead of the standard MIDI sequences */

    const uint8_t* initialization_sequence;
    const uint8_t* program_change_sequence;
    const uint8_t* note_on_sequence;
    const uint8_t* note_off_sequence;
    const uint8_t* synchronization_sequence;

} midiplan_device_t;

/*
 * These are the 3 bits in device configuration flags for note volume control.
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
 * Translates note parameters (program/note/velocity) for the device.
 * This is an idempotent call, basing its decisions only on the device
 * configuration and the input note parameters. In particular, the output
 * note that we return, the device might not be able to play *at the moment*
 * because it is overloaded, but that check will be done later.
 * Similarly, the note may be supported by the device, but routing may be
 * configured so that it is not sent to this device, also a separate concern.
 * It is crucial that notes are translated the same for all note messages -
 * on, off, key pressure, and for controllers that are related to notes.
 */
bool translate_note_to_device(
    const midiplan_device_t* p_device,
    program_t in_program,
    note_t in_note,
    data_byte_t in_velocity,
    program_t* p_out_program,
    note_t* p_out_note,
    data_byte_t* p_out_velocity,
    midi_channels_bitmap_t* p_out_channels_bitmap
);

/*
 * Filters controller change messages for the particular device.
 */
bool device_supports_controller(
    const midiplan_device_t* p_device,
    midi_control_number_t control_number
);

/*
 * Filters key pressure messages for the particular device.
 */
bool device_supports_key_pressure(
    const midiplan_device_t* p_device
);

/*
 * Filters channel pressure messages for the particular device.
 */
bool device_supports_channel_pressure(
    const midiplan_device_t* p_device
);

/*
 * Filters pitch bend messages for the particular device.
 */
bool device_supports_pitch_bend(
    const midiplan_device_t* p_device
);

/*
 * Returns true if this device has custom sequence of the specified type.
 */
bool device_has_custom_sequence(
    const midiplan_device_t* p_device,
    custom_sequence_id_t custom_sequence_id
);

/*
 * Returns a pointer to the specified initialization sequence for the device.
 * The reason we use lookup by id instead of simply passing pointers around
 * is that a pointer would take 4 bytes per message in the queue, whereas id
 * requires just one byte.
 */
const uint8_t* get_device_custom_sequence(
    const midiplan_device_t* p_device,
    custom_sequence_id_t custom_sequence_id
);

/*
 * This is the runtime state of the device, expressed in output terms.
 * Used to account for device restrictions.
 */
typedef struct {

    uint8_t melodic_programs_playing;           // how many different *output* programs are currently playing on all channels
    uint8_t melodic_notes_per_program[128 + 1]; // how many notes are playing on that *output* program (128 melodic plus 1 for percussion *when it uses a melodic timbre*)
    uint8_t melodic_notes_playing;              // how many notes are currently playing on all *output* melodic programs together (sum of melodic_notes_per_program)
    uint8_t percussion_notes_playing;           // how many notes are currently playing on the percussion program *when it uses a percussion timbre*

    struct {
        uint8_t notes_playing;                  // how many notes (on any program) are playing on this channel, including percussion
        note_entry_id_t last_note_entry_id;     // the last note initiated on this channel (erased when that note is turned off)
    } channels[MIDI_CHANNEL_COUNT];

    bool all_notes_off;                         // no notes are playing *because "all notes off" has been received and acted upon*

} midiplan_device_state_t;

/*
 * This is called once at startup.
 */
void initialize_device_state(
    midiplan_device_state_t* p_device_state
);

#endif
