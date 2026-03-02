#ifndef MIDIPLAN_DEVICES_CASIO_CSM1_H
#define MIDIPLAN_DEVICES_CASIO_CSM1_H

#include <midiplan/device.h>

extern const midiplan_device_t casio_csm1;

#define CASIO_CSM1_LOWEST_NOTE  (36)
#define CASIO_CSM1_MIDDLE_C     (60)
#define CASIO_CSM1_HIGHEST_NOTE (96)

#define CASIO_CSM1_PROGRAM_PIANO               ( 0) // note 36–96
#define CASIO_CSM1_PROGRAM_HARPSICHORD         ( 1) // note 36–96
#define CASIO_CSM1_PROGRAM_VIB                 ( 2) // note 36–96
#define CASIO_CSM1_PROGRAM_ORGAN_1             ( 3) // note 36–96
#define CASIO_CSM1_PROGRAM_ORGAN_2             ( 4) // note 36–96
#define CASIO_CSM1_PROGRAM_BRASS_ENS           ( 5) // note 36–96
#define CASIO_CSM1_PROGRAM_FLUTE               ( 6) // note 36–96
#define CASIO_CSM1_PROGRAM_CHORUS              ( 7) // note 36–96
#define CASIO_CSM1_PROGRAM_JAZZ_GUITAR         ( 8) // note 36–96
#define CASIO_CSM1_PROGRAM_BELLS               ( 9) // note 36–96
#define CASIO_CSM1_PROGRAM_CLAVI_1             (10) // note 36–96
#define CASIO_CSM1_PROGRAM_METALLIC_SOUND      (11) // note 36–96
#define CASIO_CSM1_PROGRAM_SYNTH_ENS           (12) // note 36–96
#define CASIO_CSM1_PROGRAM_HONKY_TONK_PIANO    (15) // note 36–96
#define CASIO_CSM1_PROGRAM_E_PIANO             (16) // note 36–96
#define CASIO_CSM1_PROGRAM_MARIMBA             (17) // note 36–96
#define CASIO_CSM1_PROGRAM_ORGAN_3             (18) // note 36–96
#define CASIO_CSM1_PROGRAM_ACCORDION           (19) // note 36–96
#define CASIO_CSM1_PROGRAM_STRINGS             (20) // note 36–96
#define CASIO_CSM1_PROGRAM_OBOE                (21) // note 36–96
#define CASIO_CSM1_PROGRAM_SYNTH_1             (22) // note 36–96
#define CASIO_CSM1_PROGRAM_HARP                (23) // note 36–96
#define CASIO_CSM1_PROGRAM_SYNTH_2             (24) // note 36–96
#define CASIO_CSM1_PROGRAM_CLAVI_2             (25) // note 36–96
#define CASIO_CSM1_PROGRAM_FANTASY             (26) // note 36–96
#define CASIO_CSM1_PROGRAM_MIRACLE             (27) // note 36–96
#define CASIO_CSM1_PROGRAM_BASS                (28) // note 36–59 = wood bass, note 60–96 = slap bass

#define CASIO_CSM1_RANGE_INVALID             (0x00)
#define CASIO_CSM1_RANGE_OCTAVE_HIGHER       (0x01)
#define CASIO_CSM1_RANGE_OCTAVE_LOWER        (0x02)
#define CASIO_CSM1_RANGE_LOWER_HALF          (0x03)
#define CASIO_CSM1_RANGE_UPPER_HALF          (0x04)
#define CASIO_CSM1_RANGE_DEFAULT             (0x0F)

#define CASIO_CSM1_PERC_NOTE_RAIN            (0x60)
#define CASIO_CSM1_PERC_NOTE_WAVES           (0x7A)
#define CASIO_CSM1_PERC_NOTE_SMALL_BIRDS     (0x7B)
#define CASIO_CSM1_PERC_NOTE_GUNSHOT         (0x7C) // by the same convention this should have been 7F but a melodic program can't be translated into percussion note 7F 
#define CASIO_CSM1_PERC_NOTE_TRAFFIC         (0x7D)
#define CASIO_CSM1_PERC_NOTE_APPLAUSE        (0x7E)

#define CASIO_CSM1_PERCUSSION_PROGRAM          (13)

#define CASIO_CSM1_PERCUSSION_BASS_DRUM_1      (36)
#define CASIO_CSM1_PERCUSSION_BASS_DRUM_2      (38)
#define CASIO_CSM1_PERCUSSION_SNARE_DRUM_1     (40)
#define CASIO_CSM1_PERCUSSION_SNARE_DRUM_2     (41)
#define CASIO_CSM1_PERCUSSION_GATED_SNARE_DRUM (43)
#define CASIO_CSM1_PERCUSSION_RIM_SHOT         (45)
#define CASIO_CSM1_PERCUSSION_CLOSED_HI_HAT_1  (47)
#define CASIO_CSM1_PERCUSSION_CLOSED_HI_HAT_2  (48)
#define CASIO_CSM1_PERCUSSION_OPEN_HI_HAT_1    (50)
#define CASIO_CSM1_PERCUSSION_OPEN_HI_HAT_2    (52)
#define CASIO_CSM1_PERCUSSION_CRASH_CYMBAL_1   (53)
#define CASIO_CSM1_PERCUSSION_SYNTH_CYMBAL_1   (54)
#define CASIO_CSM1_PERCUSSION_CRASH_CYMBAL_2   (55)
#define CASIO_CSM1_PERCUSSION_SYNTH_CYMBAL_2   (56)
#define CASIO_CSM1_PERCUSSION_CRASH_CYMBAL_3   (57)
#define CASIO_CSM1_PERCUSSION_SYNTH_CYMBAL_3   (58)
#define CASIO_CSM1_PERCUSSION_CRASH_CYMBAL_MIX (59)
#define CASIO_CSM1_PERCUSSION_RIDE_CYMBAL_1    (60)
#define CASIO_CSM1_PERCUSSION_GONG_1           (61)
#define CASIO_CSM1_PERCUSSION_RIDE_CYMBAL_2    (62)
#define CASIO_CSM1_PERCUSSION_GONG_2           (63)
#define CASIO_CSM1_PERCUSSION_TOM_1            (64)
#define CASIO_CSM1_PERCUSSION_TOM_2            (65)
#define CASIO_CSM1_PERCUSSION_SYNTH_TOM_1      (66)
#define CASIO_CSM1_PERCUSSION_TOM_3            (67)
#define CASIO_CSM1_PERCUSSION_SYNTH_TOM_2      (68)
#define CASIO_CSM1_PERCUSSION_TOM_4            (69)
#define CASIO_CSM1_PERCUSSION_SYNTH_TOM_3      (70)
#define CASIO_CSM1_PERCUSSION_TOM_MIX          (71)
#define CASIO_CSM1_PERCUSSION_COWBELL_1        (72)
#define CASIO_CSM1_PERCUSSION_TRIANGLE_OPEN    (73)
#define CASIO_CSM1_PERCUSSION_COWBELL_2        (74)
#define CASIO_CSM1_PERCUSSION_TRIANGLE_MUTE    (75)
#define CASIO_CSM1_PERCUSSION_HI_TIMBALE_MUTE  (76)
#define CASIO_CSM1_PERCUSSION_HI_TIMBALE       (77)
#define CASIO_CSM1_PERCUSSION_LOW_TIMBALE      (79)
#define CASIO_CSM1_PERCUSSION_HI_AGOGO         (83)
#define CASIO_CSM1_PERCUSSION_LOW_AGOGO        (84)
#define CASIO_CSM1_PERCUSSION_HI_CONGA_MUTE    (86)
#define CASIO_CSM1_PERCUSSION_HI_CONGA         (88)
#define CASIO_CSM1_PERCUSSION_MID_CONGA        (89)
#define CASIO_CSM1_PERCUSSION_LOW_CONGA        (91)
#define CASIO_CSM1_PERCUSSION_CONGA_MIX        (93)
#define CASIO_CSM1_PERCUSSION_HI_CLAVE         (95)
#define CASIO_CSM1_PERCUSSION_LOW_CLAVE        (96)

#define CASIO_CSM1_EFFECT_COMPUTER_GAME_SOUND1 (78)
#define CASIO_CSM1_EFFECT_COMPUTER_GAME_SOUND2 (80)
#define CASIO_CSM1_EFFECT_COMPUTER_GAME_SOUND3 (81)

#define CASIO_CSM1_EFFECTS_PROGRAM_14          (14)

#define CASIO_CSM1_EFFECT_SMALL_BIRDS_1        (43)
#define CASIO_CSM1_EFFECT_SMALL_BIRDS_2        (45)
#define CASIO_CSM1_EFFECT_SMALL_BIRDS_3        (47)

#define CASIO_CSM1_EFFECT_WAVES_1              (48)
#define CASIO_CSM1_EFFECT_WAVES_2              (50)
#define CASIO_CSM1_EFFECT_WAVES_3              (52)
#define CASIO_CSM1_EFFECT_WAVES_4              (53)
#define CASIO_CSM1_EFFECT_WAVES_5              (55)
#define CASIO_CSM1_EFFECT_WAVES_6              (57)
#define CASIO_CSM1_EFFECT_WAVES_7              (59)

#define CASIO_CSM1_EFFECT_TRAFFIC_1            (61)
#define CASIO_CSM1_EFFECT_TRAFFIC_2            (63)
#define CASIO_CSM1_EFFECT_TRAFFIC_3            (66)
#define CASIO_CSM1_EFFECT_TRAFFIC_4            (68)
#define CASIO_CSM1_EFFECT_TRAFFIC_5            (70)

#define CASIO_CSM1_EFFECTS_PROGRAM_29          (29)

#define CASIO_CSM1_EFFECT_WHISTLE_1            (61)
#define CASIO_CSM1_EFFECT_WHISTLE_2            (63)
#define CASIO_CSM1_EFFECT_WHISTLE_3            (66)
#define CASIO_CSM1_EFFECT_WHISTLE_4            (68)
#define CASIO_CSM1_EFFECT_WHISTLE_5            (70)

#define CASIO_CSM1_EFFECT_GUNSHOTS_1           (72)
#define CASIO_CSM1_EFFECT_GUNSHOTS_2           (74)
#define CASIO_CSM1_EFFECT_GUNSHOTS_3           (76)
#define CASIO_CSM1_EFFECT_GUNSHOTS_4           (77)
#define CASIO_CSM1_EFFECT_GUNSHOTS_5           (79)
#define CASIO_CSM1_EFFECT_GUNSHOTS_6           (81)
#define CASIO_CSM1_EFFECT_GUNSHOTS_7           (83)
#define CASIO_CSM1_EFFECT_GUNSHOTS_8           (84)

#define CASIO_CSM1_EFFECT_RAIN_1               (36)
#define CASIO_CSM1_EFFECT_RAIN_2               (37)
#define CASIO_CSM1_EFFECT_RAIN_3               (38)
#define CASIO_CSM1_EFFECT_RAIN_4               (39)
#define CASIO_CSM1_EFFECT_RAIN_5               (40)
#define CASIO_CSM1_EFFECT_RAIN_6               (41)
#define CASIO_CSM1_EFFECT_RAIN_7               (42)
#define CASIO_CSM1_EFFECT_RAIN_8               (43)
#define CASIO_CSM1_EFFECT_RAIN_9               (44)
#define CASIO_CSM1_EFFECT_RAIN_10              (45)
#define CASIO_CSM1_EFFECT_RAIN_11              (46)
#define CASIO_CSM1_EFFECT_RAIN_12              (47)

#define CASIO_CSM1_EFFECT_APPLAUSE_1           (60)
#define CASIO_CSM1_EFFECT_APPLAUSE_2           (62)
#define CASIO_CSM1_EFFECT_APPLAUSE_3           (64)
#define CASIO_CSM1_EFFECT_APPLAUSE_4           (65)
#define CASIO_CSM1_EFFECT_APPLAUSE_5           (67)
#define CASIO_CSM1_EFFECT_APPLAUSE_6           (69)
#define CASIO_CSM1_EFFECT_APPLAUSE_7           (71)

#endif
