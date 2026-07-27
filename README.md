### Description:

MIDIplan is an MCU-based MIDI sequencer that converts General MIDI 
sequence into device-specific on the fly.

The purpose of this is to play GM music (i.e. DOS retro games) on
older non-GM-compatible sound modules. Depending on the capabilities
of the device, results may vary.

You could plug in several identical devices at the same time and automatically
have increased polyphony/multitimbrality, as each device will only play its
share of notes.

Or you could plug several different devices and route some instruments here
and some instruments there. This proves particularly useful when a module does
not support percussion at all, then you have to to pair it with a dedicated
percussion module to play drums. And can also be used to combine dedicated
synths of various kinds.

### Technical description

The firmware currently runs on CY8CKIT-059 development board containing
Cypress CY8C5888LTI-LP097 MCU. To build it you would need PSoC Creator 4.4.

The application is built on top of a task scheduler, which you can find
in the sister repository at https://github.com/targeted/evar

Then you would have one General MIDI-in and 4 MIDI-outs, configurable at build
time to connect to any of the supported devices.

### Currently supported devices:

1. Alesis SR-16 (drum)
2. Casio CSM-1
3. Kawai PHm
4. Kawai XS-1
5. Korg PSS60
6. Roland CM-32P
7. Roland CM-64
8. Roland GR-09
9. Roland MT-32
10. Yamaha DOM-30
11. Yamaha EMR-1 (drum)
12. Yamaha EMT-1
13. Yamaha FB-01
14. Zoom RT-234 (drum + bass)

### Demo recordings: 

https://www.youtube.com/@MIDIplan/playlists
