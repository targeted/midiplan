#ifndef MIDIPLAN_DEVICES_ZOOM_RT234_H
#define MIDIPLAN_DEVICES_ZOOM_RT234_H

#include <midiplan/device.h>

extern const midiplan_device_t zoom_rt234;

#define ZOOM_RT234_LOWEST_NOTE  (0)
#define ZOOM_RT234_MIDDLE_C     (60)
#define ZOOM_RT234_HIGHEST_NOTE (127)

#define ZOOM_RT234_PROGRAM_LIVE_BASS                    ( 0)
#define ZOOM_RT234_PROGRAM_STUDIO_BASS                  ( 1)
#define ZOOM_RT234_PROGRAM_EPIC_BASS                    ( 2)
#define ZOOM_RT234_PROGRAM_FUNC_BASS                    ( 3)
#define ZOOM_RT234_PROGRAM_BALLAD_BASS                  ( 4)
#define ZOOM_RT234_PROGRAM_ACOUSTIC_BASS                ( 5)
#define ZOOM_RT234_PROGRAM_MODERN_BASS                  ( 6)
#define ZOOM_RT234_PROGRAM_SYNTH_BASS                   ( 7)
#define ZOOM_RT234_PROGRAM_TECHNO_BASS                  ( 8)
#define ZOOM_RT234_PROGRAM_BIG_BOTTOM_BASS              ( 9)
#define ZOOM_RT234_PROGRAM_SUBSLAP_BASS                 (10)
#define ZOOM_RT234_PROGRAM_DIGITAL_ACOUSTIC             (11)
#define ZOOM_RT234_PROGRAM_BASS_HARMONICS               (12)
#define ZOOM_RT234_PROGRAM_NO_FRETS                     (13)
#define ZOOM_RT234_PROGRAM_ACOUSTIC_JAZZ                (14)
#define ZOOM_RT234_PROGRAM_DIGITAL_PICK                 (15)
#define ZOOM_RT234_PROGRAM_TECHNO_ANALOG                (16)
#define ZOOM_RT234_PROGRAM_TABLA_BASS_TONES             (17)
#define ZOOM_RT234_PROGRAM_TIGHT_ANALOG                 (18)
#define ZOOM_RT234_PROGRAM_ANALOG_FIFTHS                (19)
#define ZOOM_RT234_PROGRAM_TEMPLE_TONES                 (20)
#define ZOOM_RT234_PROGRAM_QUADRA_BASS                  (21)
#define ZOOM_RT234_PROGRAM_ANALOG_TOUCH                 (22)
#define ZOOM_RT234_PROGRAM_PICKED_ACOUSTIC              (23)
#define ZOOM_RT234_PROGRAM_BASS_DIVE                    (24)
#define ZOOM_RT234_PROGRAM_ANALOG_OCTAVES               (25)
#define ZOOM_RT234_PROGRAM_SYNTH_TOM_BASS               (26)
#define ZOOM_RT234_PROGRAM_LO_SINE                      (27)
#define ZOOM_RT234_PROGRAM_DIGI_SLAP_BASS               (28)
#define ZOOM_RT234_PROGRAM_TUMBA_TONES                  (29)
#define ZOOM_RT234_PROGRAM_CONGA_KEYS                   (30)
#define ZOOM_RT234_PROGRAM_POWER_TOM_BASS               (31)
#define ZOOM_RT234_PROGRAM_BECOMING_BASS                (40) // 32
#define ZOOM_RT234_PROGRAM_HARMONICS_BASS               (41) // 33 
#define ZOOM_RT234_PROGRAM_BASS_WITH_HARMONICS          (42) // 34
#define ZOOM_RT234_PROGRAM_PICKED_FUNC_BASS             (43) // 35
#define ZOOM_RT234_PROGRAM_PICKED_JAZZ                  (44) // 36 
#define ZOOM_RT234_PROGRAM_PICKED_TECHNO                (45) // 37 
#define ZOOM_RT234_PROGRAM_ACOUSTIC_TECHNO              (46) // 38
#define ZOOM_RT234_PROGRAM_POWER_FUNC                   (47) // 39 
#define ZOOM_RT234_PROGRAM_POPS_PULLS_SPLIT             (48) // 40 
#define ZOOM_RT234_PROGRAM_EPIC_BASS_JAM_1              (49) // 41 
#define ZOOM_RT234_PROGRAM_TRIBAL_BASS_JAM_2            (50) // 42 
#define ZOOM_RT234_PROGRAM_WOODEN_BASS                  (51) // 43
#define ZOOM_RT234_PROGRAM_JAZZ_BASS                    (33) // 44 
#define ZOOM_RT234_PROGRAM_FUNC_POPS                    (36) // 45 
#define ZOOM_RT234_PROGRAM_FUNC_PULLS                   (54) // 46 
#define ZOOM_RT234_PROGRAM_PICKED_BASS                  (55) // 47
#define ZOOM_RT234_PROGRAM_ANALOG_BASS                  (56) // 48
#define ZOOM_RT234_PROGRAM_DIGI_BASS                    (57) // 49

#define ZOOM_RT234_RANGE_INVALID                      (0x00)
#define ZOOM_RT234_RANGE_DEFAULT                      (0x0F)

#endif
