#ifndef MIDIPLAN_DEVICES_YAMAHA_EMT1_H
#define MIDIPLAN_DEVICES_YAMAHA_EMT1_H

#include <midiplan/device.h>

extern const midiplan_device_t yamaha_emt1;

#define YAMAHA_EMT1_LOWEST_NOTE            (21)
#define YAMAHA_EMT1_MIDDLE_C               (60)
#define YAMAHA_EMT1_HIGHEST_NOTE          (108)

#define YAMAHA_EMT1_PROGRAM_BRASS          ( 0)
#define YAMAHA_EMT1_PROGRAM_TRUMPET        ( 1)
#define YAMAHA_EMT1_PROGRAM_HORN           ( 2)
#define YAMAHA_EMT1_PROGRAM_SAX            ( 3)
#define YAMAHA_EMT1_PROGRAM_CLARINET       ( 4)
#define YAMAHA_EMT1_PROGRAM_OBOE           ( 5)
#define YAMAHA_EMT1_PROGRAM_FLUTE          ( 6)
#define YAMAHA_EMT1_PROGRAM_ACCORDION      ( 7)
#define YAMAHA_EMT1_PROGRAM_STRINGS        ( 8)
#define YAMAHA_EMT1_PROGRAM_VIOLIN         ( 9)
#define YAMAHA_EMT1_PROGRAM_PIPE_ORGAN     (10)
#define YAMAHA_EMT1_PROGRAM_JAZZ_ORGAN     (11)
#define YAMAHA_EMT1_PROGRAM_PIANO          (12)
#define YAMAHA_EMT1_PROGRAM_ELECTRIC_PIANO (13)
#define YAMAHA_EMT1_PROGRAM_HARPSICHORD    (14)
#define YAMAHA_EMT1_PROGRAM_CELESTA        (15)
#define YAMAHA_EMT1_PROGRAM_VIBES          (16)
#define YAMAHA_EMT1_PROGRAM_MARIMBA        (17)
#define YAMAHA_EMT1_PROGRAM_CLAVI          (18)
#define YAMAHA_EMT1_PROGRAM_BELL           (19)
#define YAMAHA_EMT1_PROGRAM_WAH            (20)
#define YAMAHA_EMT1_PROGRAM_ALIEN          (21)
#define YAMAHA_EMT1_PROGRAM_ICE            (22)
#define YAMAHA_EMT1_PROGRAM_DRUMS          (23)
#define YAMAHA_EMT1_PROGRAM_GUITAR_1       (24)
#define YAMAHA_EMT1_PROGRAM_GUITAR_2       (25)
#define YAMAHA_EMT1_PROGRAM_GUITAR_3       (26)
#define YAMAHA_EMT1_PROGRAM_SITAR          (27)
#define YAMAHA_EMT1_PROGRAM_UPRIGHT_BASS   (28)
#define YAMAHA_EMT1_PROGRAM_ELEC_BASS      (29)
#define YAMAHA_EMT1_PROGRAM_SLAP_BASS      (30)
#define YAMAHA_EMT1_PROGRAM_SYNTH_BASS     (31)

#define YAMAHA_EMT1_RANGE_INVALID        (0x00)
#define YAMAHA_EMT1_RANGE_OCTAVE_HIGHER  (0x01)
#define YAMAHA_EMT1_RANGE_OCTAVE_LOWER   (0x02)
#define YAMAHA_EMT1_RANGE_DEFAULT        (0x0F)

#endif
