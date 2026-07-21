#ifndef MIDIPLAN_MIDI_OUTPUT_H
#define MIDIPLAN_MIDI_OUTPUT_H

#include "types.h"
#include "device.h"

typedef struct {

    status_byte_t      running_status;   // keeps track of the previous status

    /* if a literal MIDI message is being sent */

    struct {
        uint8_t        bytes[3];         // up to 3 bytes of a literal data message being sent
        uint8_t        size;             // number of bytes to send
        uint8_t        offs;             // offset to the next byte to send
    } message_data;

    /* if a device-specific sequence is being sent */

    struct {
        const uint8_t* p_next_byte;      // points to the raw bytes of the custom sequence being sent
        custom_sequence_parameters_t parameters; // parameters for the custom sequence being sent
        struct {
            uint8_t    roland_checksum;  // running value of a Roland-style checksum
        } variables;
        uint8_t        current_status;   // currently active status byte (can be regular or SOX)
        uint8_t        data_byte_count;  // number of data bytes expected to be ahead
    } custom_sequence;

} midi_output_state_t;

/*
 * Initializes the logical state of MIDI output to "empty".
 */
void initialize_midi_output_state(
    midi_output_state_t* p_midi_output_state
);

/*
 * Copies bytes to be sent from a message containing a single literal MIDI message
 * (or one byte of a streaming system exclusive, wrapped in a fake MIDI message).
 * These messages originate from the input UART.
 */
void load_midi_output_midi_message(
    midi_output_state_t* p_midi_output_state,
    midi_message_t midi_message
);

/*
 * Takes the bytes to be sent from a message pointing to a large device-specific buffer
 * containing potentially many separate messages. This buffer is considered to be static
 * and immutable, therefore we simply keep the pointer. The bytes in the buffer are treated
 * as parameterized mini program, augmentation is applied on the fly.
 */
void load_midi_output_custom_sequence(
    midi_output_state_t* p_midi_output_state,
    const midiplan_device_t* p_device,
    custom_sequence_id_t custom_sequence_id,
    custom_sequence_parameters_t custom_sequence_parameters
);

/*
 * Returns true if buffered data is being sent.
 */
bool have_midi_output_bytes_to_send(
    midi_output_state_t* p_midi_output_state
);

/*
 * Retrieves the next byte from the logical sequence of messages.
 * Returns true if there is a next byte, false if there is nothing
 * to send at the moment (the data may be available, but a delay
 * is being requested).
 */
bool get_next_midi_output_byte(
    midi_output_state_t* p_midi_output_state,
    uint8_t* p_next_byte,
    evar_time_delta_t* p_delay_usec
);

#endif
