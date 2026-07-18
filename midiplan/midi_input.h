#ifndef MIDIPLAN_MIDI_INPUT_H
#define MIDIPLAN_MIDI_INPUT_H

#include <stdbool.h>
#include "midi.h"
    
typedef struct {
    bool          synchronized;        // set to true after a status byte have been received which might start a message
    status_byte_t status_byte;         // the status byte of the message being received
    data_byte_t   data_bytes[2];       // a buffer for up to two data bytes of the message being received
    uint8_t       expected_data_bytes; // how many data bytes are expected for the message being received (0 to 2)
    uint8_t       received_data_bytes; // how many data bytes have been received
    status_byte_t running_status;      // the status byte of the previous message, when running status is applicable
} midi_input_state_t;

/*
 * Initializes the logical MIDI byte stream state to "unknown".
 */
void reset_midi_input_state(midi_input_state_t* p_midi_input_state);

/*
 * The purpose of this function is to coalesce a stream of input UART bytes into logical MIDI messages,
 * which always start with a status byte and have between zero and two data bytes. The moment a MIDI
 * message is completed, it is sent to the next stage of processing.
 *
 * There is one tricky case of a system exclusive message terminated not by EOX, but by the next
 * message's status byte, which is permitted. In this case, the implied EOX will be sent, but
 * the status byte will have to be not consumed, false is returned and the caller will retry.
 *
 * System exclusive messages are sent as as a sequence of single-byte wrapper "messages" and are 
 * therefore unlimited in size from this code's perspective. Any other message is sent individually
 * in full, running status is translated into explicit status bytes.
 *
 * The only filtering performed at this level is ignoring undefined messages.
 *
 * Returns true if this byte if this byte has resulted in completion and production of a MIDI message 
 * into the caller's buffer.
 */
bool handle_midi_input_byte(
    midi_input_state_t* p_midi_input_state,
    unsigned char input_byte,
    midi_message_t* p_midi_message,
    bool* p_consume_input_byte
);

#endif
