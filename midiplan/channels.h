#ifndef MIDIPLAN_CHANNELS_H
#define MIDIPLAN_CHANNELS_H

#include <midiplan/types.h>
#include <midiplan/config.h>
#include <midiplan/note_entries.h>

/*
 * This is an index referencing note entries from note numbers.
 */
typedef note_entry_id_t note_entry_lookup_t[MIDI_NOTE_RANGE];

/*
 * This structure contains the running state of an input MIDI channel.
 */
typedef struct {
    program_t           in_program;                                   // currently active GM program
    channel_t           associated_out_channels[MIDI_OUT_PORT_COUNT]; // the channel on each output device to which this input channel is currently associated
    note_entry_lookup_t note_entry_lookup;                            // for each active input note references the corresponding note entry
} input_channel_t;

extern input_channel_t input_channels[MIDI_CHANNEL_COUNT];

/*
 * This structure contains the running state of an output MIDI channel.
 */
typedef struct {
    program_t              out_program;             // currently active device-specific program
    channel_t              associated_in_channel;   // the input channel to which this output channel has been last associated
    midi_channels_bitmap_t associated_in_channels;  // cumulative bitmap of input channels, to which this output channel has ever been associated
    note_entry_lookup_t    note_entry_lookup;       // for each active output note references the corresponding note entry
} output_channel_t;

extern output_channel_t output_channels[MIDI_OUT_PORT_COUNT][MIDI_CHANNEL_COUNT];

/*
 * Initializes the channels structures. This is done once at startup.
 */
void initialize_channels(void);

/*
 * Clears the associations between the input and output channels, 
 * this is done at startup and every time when every input note
 * has been turned off via "all notes off" command.
 */
void reset_channel_associations(void);

#endif
