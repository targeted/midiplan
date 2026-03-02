#ifndef MIDIPLAN_DEVICES_KAWAI_XS1_H
#define MIDIPLAN_DEVICES_KAWAI_XS1_H

#include <midiplan/device.h>

extern const midiplan_device_t kawai_xs1;

#define KAWAI_XS1_LOWEST_NOTE  ( 12)
#define KAWAI_XS1_MIDDLE_C     ( 60)
#define KAWAI_XS1_HIGHEST_NOTE (120)

#define KAWAI_XS1_PROGRAM_PIANO_1             ( 0) // 111
#define KAWAI_XS1_PROGRAM_LOW_PIANO           ( 1) // 112
#define KAWAI_XS1_PROGRAM_BRIGHT_PIANO        ( 2) // 113
#define KAWAI_XS1_PROGRAM_PIANO_2             ( 3) // 114
#define KAWAI_XS1_PROGRAM_SYN_BRASS           ( 4) // 115
#define KAWAI_XS1_PROGRAM_AC_BRASS            ( 5) // 116
#define KAWAI_XS1_PROGRAM_OCT_BRASS           ( 6) // 117
#define KAWAI_XS1_PROGRAM_LIPS                ( 7) // 118
#define KAWAI_XS1_PROGRAM_CONDENSER           ( 8) // 121
#define KAWAI_XS1_PROGRAM_RHODOS              ( 9) // 122
#define KAWAI_XS1_PROGRAM_WURL_EP             (10) // 123
#define KAWAI_XS1_PROGRAM_DC_EP               (11) // 124
#define KAWAI_XS1_PROGRAM_PALLAS              (12) // 125
#define KAWAI_XS1_PROGRAM_E_ORGAN             (13) // 126
#define KAWAI_XS1_PROGRAM_BEE_52              (14) // 127
#define KAWAI_XS1_PROGRAM_CHURCH_ORGAN        (15) // 128
#define KAWAI_XS1_PROGRAM_SPINETT             (16) // 131
#define KAWAI_XS1_PROGRAM_CLAVI               (17) // 132
#define KAWAI_XS1_PROGRAM_FLUTE               (18) // 133
#define KAWAI_XS1_PROGRAM_RECORDER            (19) // 134
#define KAWAI_XS1_PROGRAM_TIN_WHISTLE         (20) // 135
#define KAWAI_XS1_PROGRAM_ALTO                (21) // 136
#define KAWAI_XS1_PROGRAM_OBOE                (22) // 137
#define KAWAI_XS1_PROGRAM_TENOR_SAX           (23) // 138
#define KAWAI_XS1_PROGRAM_BELLS               (24) // 141
#define KAWAI_XS1_PROGRAM_SPIELUHR            (25) // 142
#define KAWAI_XS1_PROGRAM_WATER_BELL          (26) // 143
#define KAWAI_XS1_PROGRAM_MALLET              (27) // 144
#define KAWAI_XS1_PROGRAM_VIBRAPHONE          (28) // 145
#define KAWAI_XS1_PROGRAM_SQR_LEAD            (29) // 146
#define KAWAI_XS1_PROGRAM_SAW_LEAD_1          (30) // 147
#define KAWAI_XS1_PROGRAM_HARMONICA           (31) // 148
#define KAWAI_XS1_PROGRAM_SYN_BASS            (32) // 151
#define KAWAI_XS1_PROGRAM_CONTRABASS          (33) // 152
#define KAWAI_XS1_PROGRAM_FRETLESS            (34) // 153
#define KAWAI_XS1_PROGRAM_SHARP_BASS          (35) // 154
#define KAWAI_XS1_PROGRAM_DC_BASS             (36) // 155
#define KAWAI_XS1_PROGRAM_PULL_BASS           (37) // 156
#define KAWAI_XS1_PROGRAM_NORM_VOICE          (38) // 157
#define KAWAI_XS1_PROGRAM_CHA_CHA             (39) // 158
#define KAWAI_XS1_PROGRAM_FAT_STRINGS         (40) // 161
#define KAWAI_XS1_PROGRAM_NORM_STRING         (41) // 162
#define KAWAI_XS1_PROGRAM_SPACE_STRINGS       (42) // 163
#define KAWAI_XS1_PROGRAM_FAST_STRINGS        (43) // 164
#define KAWAI_XS1_PROGRAM_OCT_STRINGS         (44) // 165
#define KAWAI_XS1_PROGRAM_W_BASS_VIBE         (45) // 166
#define KAWAI_XS1_PROGRAM_STRINGS_BRASS       (46) // 167
#define KAWAI_XS1_PROGRAM_E_BASS_E_PIANO      (47) // 168
#define KAWAI_XS1_PROGRAM_NYLON               (48) // 171
#define KAWAI_XS1_PROGRAM_DIST                (49) // 172
#define KAWAI_XS1_PROGRAM_BANJO               (50) // 173
#define KAWAI_XS1_PROGRAM_WATER_DANCE         (51) // 174
#define KAWAI_XS1_PROGRAM_STEELY_GTR          (52) // 175
#define KAWAI_XS1_PROGRAM_SYN_BASS_STRINGS    (53) // 176
#define KAWAI_XS1_PROGRAM_E_BASS_CLAVI        (54) // 177
#define KAWAI_XS1_PROGRAM_SYN_BASS_VOICE      (55) // 178
#define KAWAI_XS1_PROGRAM_ACCORDION           (56) // 181
#define KAWAI_XS1_PROGRAM_SITAR               (57) // 182
#define KAWAI_XS1_PROGRAM_WATER_DREAM         (58) // 183
#define KAWAI_XS1_PROGRAM_LUCY                (59) // 184
#define KAWAI_XS1_PROGRAM_PIANO_STRING        (60) // 185
#define KAWAI_XS1_PROGRAM_STRING_VOICE        (61) // 186
#define KAWAI_XS1_PROGRAM_BRASS_VOICE         (62) // 187
#define KAWAI_XS1_PROGRAM_11_CC               (63) // 188

#define KAWAI_XS1_PROGRAM_E_PIANO_1           (64) // 211
#define KAWAI_XS1_PROGRAM_E_PIANO_2           (65) // 212
#define KAWAI_XS1_PROGRAM_NAIL_BOX            (66) // 213
#define KAWAI_XS1_PROGRAM_SLAP_BASS           (67) // 214
#define KAWAI_XS1_PROGRAM_WARM_BASS           (68) // 215
#define KAWAI_XS1_PROGRAM_MUTE_RELEASE        (69) // 216
#define KAWAI_XS1_PROGRAM_SE_BELL             (70) // 217
#define KAWAI_XS1_PROGRAM_SYNTH_SE            (71) // 218
#define KAWAI_XS1_PROGRAM_POP_LEAD            (72) // 221
#define KAWAI_XS1_PROGRAM_SAW_LEAD_2          (73) // 222
#define KAWAI_XS1_PROGRAM_PAN_FLUTE           (74) // 223
#define KAWAI_XS1_PROGRAM_VIOLIN              (75) // 224
#define KAWAI_XS1_PROGRAM_SAW_LEAD_3          (76) // 225
#define KAWAI_XS1_PROGRAM_E_ORGAN_2           (77) // 226
#define KAWAI_XS1_PROGRAM_CLARINET            (78) // 227
#define KAWAI_XS1_PROGRAM_SPACE_VOX           (79) // 228
#define KAWAI_XS1_PROGRAM_FLAGIOLET           (80) // 231
#define KAWAI_XS1_PROGRAM_FUZZ_GT             (81) // 232
#define KAWAI_XS1_PROGRAM_TIN_DRUM            (82) // 233
#define KAWAI_XS1_PROGRAM_XYLOPHONE           (83) // 234
#define KAWAI_XS1_PROGRAM_BELL                (84) // 235
#define KAWAI_XS1_PROGRAM_SEQ_PLUCK_1         (85) // 236
#define KAWAI_XS1_PROGRAM_STEEL_DRUM          (86) // 237
#define KAWAI_XS1_PROGRAM_SEQ_PLUCK_2         (87) // 238
#define KAWAI_XS1_PROGRAM_BRASS_STRINGS       (88) // 241
#define KAWAI_XS1_PROGRAM_SAW_PAD             (89) // 242
#define KAWAI_XS1_PROGRAM_SE_VOICE            (90) // 243
#define KAWAI_XS1_PROGRAM_PIANO_BRASS_2       (91) // 244
#define KAWAI_XS1_PROGRAM_BD_AND_TOM          (92) // 245
#define KAWAI_XS1_PROGRAM_HAT                 (93) // 246
#define KAWAI_XS1_PROGRAM_COWBELL             (94) // 247
#define KAWAI_XS1_PROGRAM_SNARE               (95) // 248

#define KAWAI_XS1_PERCUSSION_BASS_DRUM        (36)
#define KAWAI_XS1_PERCUSSION_RIM_SHOT         (37)
#define KAWAI_XS1_PERCUSSION_SNARE_DRUM_1     (38)
#define KAWAI_XS1_PERCUSSION_HAND_CLAP        (39)
#define KAWAI_XS1_PERCUSSION_SNARE_DRUM_2     (40)
#define KAWAI_XS1_PERCUSSION_LOW_TOM_1        (41)
#define KAWAI_XS1_PERCUSSION_CLOSED_HI_HAT_1  (42)
#define KAWAI_XS1_PERCUSSION_LOW_TOM_2        (43)
#define KAWAI_XS1_PERCUSSION_CLOSED_HI_HAT_2  (44)
#define KAWAI_XS1_PERCUSSION_MID_TOM_1        (45)
#define KAWAI_XS1_PERCUSSION_OPEN_HI_HAT      (46)
#define KAWAI_XS1_PERCUSSION_MID_TOM_2        (47)
#define KAWAI_XS1_PERCUSSION_HIGH_TOM_1       (48)
#define KAWAI_XS1_PERCUSSION_SIDE_CYMBAL_1    (49)
#define KAWAI_XS1_PERCUSSION_HIGH_TOM_2       (50)
#define KAWAI_XS1_PERCUSSION_TOP_CYMBAL       (51)
#define KAWAI_XS1_PERCUSSION_SIDE_CYMBAL_2    (52)
#define KAWAI_XS1_PERCUSSION_AFRICAN_BELL     (53)
#define KAWAI_XS1_PERCUSSION_TAMBOURINE       (54)
#define KAWAI_XS1_PERCUSSION_SPLASH           (55)
#define KAWAI_XS1_PERCUSSION_HIGH_COWBELL     (56)
#define KAWAI_XS1_PERCUSSION_SIDE_CYMBAL_3    (57)
#define KAWAI_XS1_PERCUSSION_LOW_COWBELL      (58)
#define KAWAI_XS1_PERCUSSION_AGOGO            (59)
#define KAWAI_XS1_PERCUSSION_HIGH_BONGO       (60)
#define KAWAI_XS1_PERCUSSION_LOW_BONGO        (61)
#define KAWAI_XS1_PERCUSSION_SHAKER           (62)
#define KAWAI_XS1_PERCUSSION_HIGH_CONGA       (63)
#define KAWAI_XS1_PERCUSSION_LOW_CONGA        (64)
#define KAWAI_XS1_PERCUSSION_HIGH_TIMBALE     (65)
#define KAWAI_XS1_PERCUSSION_LOW_TIMBALE      (66)
#define KAWAI_XS1_PERCUSSION_CLAVE            (67)

#define KAWAI_XS1_RANGE_INVALID               (0x00)
#define KAWAI_XS1_RANGE_OCTAVE_HIGHER         (0x01)
#define KAWAI_XS1_RANGE_OCTAVE_LOWER          (0x02)
#define KAWAI_XS1_RANGE_LOWER_HALF            (0x03)
#define KAWAI_XS1_RANGE_UPPER_HALF            (0x05)
#define KAWAI_XS1_RANGE_DEFAULT               (0x0F)

#endif
