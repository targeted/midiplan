#ifndef MIDIPLAN_DEVICES_ROLAND_GR09_H
#define MIDIPLAN_DEVICES_ROLAND_GR09_H

#include <midiplan/device.h>

extern const midiplan_device_t roland_gr09;

#define ROLAND_GR09_LOWEST_NOTE               (  0)
#define ROLAND_GR09_MIDDLE_C                  ( 60)
#define ROLAND_GR09_HIGHEST_NOTE              (127)

#define ROLAND_GR09_RANGE_INVALID             (0x00)
#define ROLAND_GR09_RANGE_DEFAULT             (0x0F)

#define ROLAND_GR09_TONE_ACOUSTIC_PIANO1          (0x00) // 1
#define ROLAND_GR09_TONE_ACOUSTIC_PIANO2          (0x01) // 2
#define ROLAND_GR09_TONE_HONKY_TONK               (0x02) // 3
#define ROLAND_GR09_TONE_ELECTRIC_PIANO1          (0x03) // 4
#define ROLAND_GR09_TONE_ELECTRIC_PIANO2          (0x04) // 5
#define ROLAND_GR09_TONE_ELECTRIC_GRAND           (0x05) // 6
#define ROLAND_GR09_TONE_POP_E_PIANO              (0x06) // 7
#define ROLAND_GR09_TONE_RHODES                   (0x07) // 8
#define ROLAND_GR09_TONE_OVER_TONE                (0x08) // 9
#define ROLAND_GR09_TONE_A_PIANO_PLUS_VIB         (0x09) // 10
#define ROLAND_GR09_TONE_A_PIANO_PLUS_VOX         (0x0A) // 11
#define ROLAND_GR09_TONE_CLAV1                    (0x0B) // 12
#define ROLAND_GR09_TONE_CLAV2                    (0x0C) // 13
#define ROLAND_GR09_TONE_VIBES                    (0x0D) // 14
#define ROLAND_GR09_TONE_VIBES2                   (0x0E) // 15
#define ROLAND_GR09_TONE_MARIMBA                  (0x0F) // 16
#define ROLAND_GR09_TONE_ORGAN1                   (0x10) // 17
#define ROLAND_GR09_TONE_ORGAN2                   (0x11) // 18
#define ROLAND_GR09_TONE_ROCK_ORGAN1              (0x12) // 19
#define ROLAND_GR09_TONE_JAZZ_ORGAN1              (0x13) // 20
#define ROLAND_GR09_TONE_JAZZ_ORGAN2              (0x14) // 21
#define ROLAND_GR09_TONE_CHEESO                   (0x15) // 22
#define ROLAND_GR09_TONE_PIPE_ORGAN1              (0x16) // 23
#define ROLAND_GR09_TONE_STEEL_GUITAR1            (0x17) // 24
#define ROLAND_GR09_TONE_NYLN_GUITAR              (0x18) // 25
#define ROLAND_GR09_TONE_12STR_GUITAR             (0x19) // 26
#define ROLAND_GR09_TONE_GTR_HARMONICS1           (0x1A) // 27
#define ROLAND_GR09_TONE_GTR_HARMONICS2           (0x1B) // 28
#define ROLAND_GR09_TONE_DISTORTION_GTR1          (0x1C) // 29
#define ROLAND_GR09_TONE_DISTORTION_GTR2          (0x1D) // 30
#define ROLAND_GR09_TONE_GUITAR_CLAV              (0x1E) // 31
#define ROLAND_GR09_TONE_GUITAR_LEAD              (0x1F) // 32
#define ROLAND_GR09_TONE_FEED_BACK1               (0x20) // 33
#define ROLAND_GR09_TONE_FEED_BACK2               (0x21) // 34
#define ROLAND_GR09_TONE_ONLY_FEEDBACK            (0x22) // 35
#define ROLAND_GR09_TONE_PEDAL_STEEL              (0x23) // 36
#define ROLAND_GR09_TONE_BANJO                    (0x24) // 37
#define ROLAND_GR09_TONE_ELECTRIC_SITAR1          (0x25) // 38
#define ROLAND_GR09_TONE_ELECTRIC_SITAR2          (0x26) // 39
#define ROLAND_GR09_TONE_ACOUSTIC_BASS1           (0x27) // 40
#define ROLAND_GR09_TONE_ACOUSTIC_BASS2           (0x28) // 41
#define ROLAND_GR09_TONE_ELECTRIC_BASS1           (0x29) // 42
#define ROLAND_GR09_TONE_PICK_BASS1               (0x2A) // 43
#define ROLAND_GR09_TONE_PICK_BASS2               (0x2B) // 44
#define ROLAND_GR09_TONE_PICK_BASS3               (0x2C) // 45
#define ROLAND_GR09_TONE_PICK_BASS4               (0x2D) // 46
#define ROLAND_GR09_TONE_SLAP_BASS1               (0x2E) // 47
#define ROLAND_GR09_TONE_SLAP_BASS2               (0x2F) // 48
#define ROLAND_GR09_TONE_DETUNED_SLAP             (0x30) // 49
#define ROLAND_GR09_TONE_FRETLESS_BASS            (0x31) // 50
#define ROLAND_GR09_TONE_FRETLESS_BASS2           (0x32) // 51
#define ROLAND_GR09_TONE_MINI_BASS1               (0x33) // 52
#define ROLAND_GR09_TONE_MINI_BASS2               (0x34) // 53
#define ROLAND_GR09_TONE_OCT_BASS1                (0x35) // 54
#define ROLAND_GR09_TONE_OCT_BASS2                (0x36) // 55
#define ROLAND_GR09_TONE_RESO_BASS1               (0x37) // 56
#define ROLAND_GR09_TONE_PEDAL_BASS               (0x38) // 57
#define ROLAND_GR09_TONE_FAST_STRINGS             (0x39) // 58
#define ROLAND_GR09_TONE_SLOW_STRINGS             (0x3A) // 59
#define ROLAND_GR09_TONE_OCT_STRINGS              (0x3B) // 60
#define ROLAND_GR09_TONE_BOWED_STRINGS            (0x3C) // 61
#define ROLAND_GR09_TONE_BRIGHT_STRINGS1          (0x3D) // 62
#define ROLAND_GR09_TONE_DARK_STRINGS             (0x3E) // 63
#define ROLAND_GR09_TONE_JP_STRINGS               (0x3F) // 64
#define ROLAND_GR09_TONE_JP_PAD1                  (0x40) // 65
#define ROLAND_GR09_TONE_OCT_JP_STRINGS           (0x41) // 66
#define ROLAND_GR09_TONE_JP_STRINGS2              (0x42) // 67
#define ROLAND_GR09_TONE_HYBRID_STRINGS           (0x43) // 68
#define ROLAND_GR09_TONE_HYBRID_STRINGS2          (0x44) // 69
#define ROLAND_GR09_TONE_HYBRID_STRINGS3          (0x45) // 70
#define ROLAND_GR09_TONE_VIOLIN                   (0x46) // 71
#define ROLAND_GR09_TONE_CELLO1                   (0x47) // 72
#define ROLAND_GR09_TONE_CONTRA_BASS              (0x48) // 73
#define ROLAND_GR09_TONE_FIDDLE                   (0x49) // 74
#define ROLAND_GR09_TONE_WIRE_STRING              (0x4A) // 75
#define ROLAND_GR09_TONE_HARP                     (0x4B) // 76
#define ROLAND_GR09_TONE_SYNTH_HARP               (0x4C) // 77
#define ROLAND_GR09_TONE_SYNTH_VOX1               (0x4D) // 78
#define ROLAND_GR09_TONE_SYNTH_VOX2               (0x4E) // 79
#define ROLAND_GR09_TONE_DOUBLE_VOX               (0x4F) // 80
#define ROLAND_GR09_TONE_VOX_LEAD1                (0x50) // 81
#define ROLAND_GR09_TONE_HAUNT_VOX                (0x51) // 82
#define ROLAND_GR09_TONE_CHIFF_PAD                (0x52) // 83
#define ROLAND_GR09_TONE_BREATH                   (0x53) // 84
#define ROLAND_GR09_TONE_WIND_VOX                 (0x54) // 85
#define ROLAND_GR09_TONE_INVERSION                (0x55) // 86
#define ROLAND_GR09_TONE_SYNTH_HARM               (0x56) // 87
#define ROLAND_GR09_TONE_ECHO_VOX                 (0x57) // 88
#define ROLAND_GR09_TONE_SCAT_VOX                 (0x58) // 89
#define ROLAND_GR09_TONE_DOUBLE_SCAT              (0x59) // 90
#define ROLAND_GR09_TONE_NYLON_SCAT               (0x5A) // 91
#define ROLAND_GR09_TONE_PLUCK_DOO                (0x5B) // 92
#define ROLAND_GR09_TONE_BRASS_SECTION            (0x5C) // 93
#define ROLAND_GR09_TONE_BRASS_SECTION2           (0x5D) // 94
#define ROLAND_GR09_TONE_BRASS_SECTION3           (0x5E) // 95
#define ROLAND_GR09_TONE_OCT_BRASS                (0x5F) // 96
#define ROLAND_GR09_TONE_SYNTH_BRASS1             (0x60) // 97
#define ROLAND_GR09_TONE_SYNTH_BRASS2             (0x61) // 98
#define ROLAND_GR09_TONE_SYNTH_BRASS3             (0x62) // 99
#define ROLAND_GR09_TONE_BRASS_BLUST              (0x63) // 100
#define ROLAND_GR09_TONE_RICH_BRASS               (0x64) // 101
#define ROLAND_GR09_TONE_TRUMPET                  (0x65) // 102
#define ROLAND_GR09_TONE_TROMBONE                 (0x66) // 103
#define ROLAND_GR09_TONE_TUBA                     (0x67) // 104
#define ROLAND_GR09_TONE_BRIGHT_TRUMPET           (0x68) // 105
#define ROLAND_GR09_TONE_MUTE_TRUMPET             (0x69) // 106
#define ROLAND_GR09_TONE_ALTO_SAX_PLUS_TP         (0x6A) // 107
#define ROLAND_GR09_TONE_TP_PLUS_TB               (0x6B) // 108
#define ROLAND_GR09_TONE_TROMBONE_PLUS_SAX        (0x6C) // 109
#define ROLAND_GR09_TONE_FRENCH_HORN              (0x6D) // 110
#define ROLAND_GR09_TONE_FLUGEL_HORN              (0x6E) // 111
#define ROLAND_GR09_TONE_DETUNED_HORN             (0x6F) // 112
#define ROLAND_GR09_TONE_VELOCITY_HORN            (0x70) // 113
#define ROLAND_GR09_TONE_DUAL_HORN                (0x71) // 114
#define ROLAND_GR09_TONE_PULSE_HORN               (0x72) // 115
#define ROLAND_GR09_TONE_SYNTH_HOM                (0x73) // 116
#define ROLAND_GR09_TONE_BREATHY_HORN             (0x74) // 117
#define ROLAND_GR09_TONE_FLUGEL_PLUS_TRUMPET      (0x75) // 118
#define ROLAND_GR09_TONE_FLUGEL_PLUS_FLUTE        (0x76) // 119
#define ROLAND_GR09_TONE_ALTO_SAX                 (0x77) // 120
#define ROLAND_GR09_TONE_TENOR_SAX                (0x78) // 121
#define ROLAND_GR09_TONE_SOPRANO_SAX              (0x79) // 122
#define ROLAND_GR09_TONE_ALTO_GROWL               (0x7A) // 123
#define ROLAND_GR09_TONE_TENOR_GROWL              (0x7B) // 124
#define ROLAND_GR09_TONE_ALTO_TENOR               (0x7C) // 125
#define ROLAND_GR09_TONE_PICCOLO                  (0x7D) // 126
#define ROLAND_GR09_TONE_FLUTE                    (0x7E) // 127
#define ROLAND_GR09_TONE_OBOE                     (0x7F) // 128
#define ROLAND_GR09_TONE_CLARINET                 (0x80) // 129
#define ROLAND_GR09_TONE_CHIFF_FLUTE              (0x81) // 130
#define ROLAND_GR09_TONE_MUTE_TP_PLUS_FLUTE       (0x82) // 131
#define ROLAND_GR09_TONE_VIBE_PLUS_FLUTE          (0x83) // 132
#define ROLAND_GR09_TONE_OCARINA                  (0x84) // 133
#define ROLAND_GR09_TONE_CALLIOPE                 (0x85) // 134
#define ROLAND_GR09_TONE_BOTTLE_BLOW              (0x86) // 135
#define ROLAND_GR09_TONE_BLOW_PIPE                (0x87) // 136
#define ROLAND_GR09_TONE_HARMONICA                (0x88) // 137
#define ROLAND_GR09_TONE_WHISTLE                  (0x89) // 138
#define ROLAND_GR09_TONE_GR300_LEAD               (0x8A) // 139
#define ROLAND_GR09_TONE_PLAIN_LEAD               (0x8B) // 140
#define ROLAND_GR09_TONE_POLY_SYNTH1              (0x8C) // 141
#define ROLAND_GR09_TONE_TWEETY                   (0x8D) // 142
#define ROLAND_GR09_TONE_SOFT_PAD                 (0x8E) // 143
#define ROLAND_GR09_TONE_METAL_PAD1               (0x8F) // 144
#define ROLAND_GR09_TONE_SQUARE_LEAD              (0x90) // 145
#define ROLAND_GR09_TONE_SYNTH_LEAD               (0x91) // 146
#define ROLAND_GR09_TONE_SYNTH_LEAD2              (0x92) // 147
#define ROLAND_GR09_TONE_SYNTH_LEAD3              (0x93) // 148
#define ROLAND_GR09_TONE_SYNTH_LEAD4              (0x94) // 149
#define ROLAND_GR09_TONE_SYNTH_LEAD5              (0x95) // 150
#define ROLAND_GR09_TONE_5TH_LEAD1                (0x96) // 151
#define ROLAND_GR09_TONE_SAW_LEAD                 (0x97) // 152
#define ROLAND_GR09_TONE_FAT_LEAD                 (0x98) // 153
#define ROLAND_GR09_TONE_SAW_PAD                  (0x99) // 154
#define ROLAND_GR09_TONE_PULSE_PAD                (0x9A) // 155
#define ROLAND_GR09_TONE_TECHNO                   (0x9B) // 156
#define ROLAND_GR09_TONE_OMINOUS                  (0x9C) // 157
#define ROLAND_GR09_TONE_HARP_PAD                 (0x9D) // 158
#define ROLAND_GR09_TONE_INVISIBLE                (0x9E) // 159
#define ROLAND_GR09_TONE_ATMOSPHERE               (0x9F) // 160
#define ROLAND_GR09_TONE_DIGITAL_PLUCK            (0xA0) // 161
#define ROLAND_GR09_TONE_PLUCK_SWEEP1             (0xA1) // 162
#define ROLAND_GR09_TONE_PLUCK_SWEEP2             (0xA2) // 163
#define ROLAND_GR09_TONE_SWEEP_PAD1               (0xA3) // 164
#define ROLAND_GR09_TONE_OCTAVE_PAD1              (0xA4) // 165
#define ROLAND_GR09_TONE_HELLOW_PAD               (0xA5) // 166
#define ROLAND_GR09_TONE_CHOIR_PAD                (0xA6) // 167
#define ROLAND_GR09_TONE_DIGITAL_BOW              (0xA7) // 168
#define ROLAND_GR09_TONE_DIGITAL_VOX1             (0xA8) // 169
#define ROLAND_GR09_TONE_SOUNDTRACK               (0xA9) // 170
#define ROLAND_GR09_TONE_BOWED_GLASS              (0xAA) // 171
#define ROLAND_GR09_TONE_HEAVEN                   (0xAB) // 172
#define ROLAND_GR09_TONE_FANTA_BELL               (0xAC) // 173
#define ROLAND_GR09_TONE_TINKLE_BELL              (0xAD) // 174
#define ROLAND_GR09_TONE_SYNTH_BELL               (0xAE) // 175
#define ROLAND_GR09_TONE_SPARKLE_BELL             (0xAF) // 176
#define ROLAND_GR09_TONE_FANTASIA                 (0xB0) // 177
#define ROLAND_GR09_TONE_FANTA_PAD                (0xB1) // 178
#define ROLAND_GR09_TONE_WHISPER                  (0xB2) // 179
#define ROLAND_GR09_TONE_STEEL_DRUM               (0xB3) // 180

#define ROLAND_GR09_GROUP1  (0x00)
#define ROLAND_GR09_GROUP2  (0x10)
#define ROLAND_GR09_GROUP3  (0x20)
#define ROLAND_GR09_GROUP4  (0x30)
#define ROLAND_GR09_GROUP5  (0x40)
#define ROLAND_GR09_GROUP6  (0x50)
#define ROLAND_GR09_GROUP7  (0x60)
#define ROLAND_GR09_GROUP8  (0x70)

#define ROLAND_GR09_PROGRAM_ACOUSTIC_GRAND_PIANO   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ACOUSTIC_PIANO1       0x0F))
#define ROLAND_GR09_PROGRAM_BRIGHT_ACOUSTIC_PIANO  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ACOUSTIC_PIANO2       0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_GRAND_PIANO   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ELECTRIC_GRAND        0x0F))
#define ROLAND_GR09_PROGRAM_HONKY_TONK_PIANO       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_HONKY_TONK            0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_PIANO_1       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ELECTRIC_PIANO1       0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_PIANO_2       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ELECTRIC_PIANO2       0x0F))
#define ROLAND_GR09_PROGRAM_HARPSICHORD            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_CLAVI                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CLAV1                 0x0F))

#define ROLAND_GR09_PROGRAM_CELESTA                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_GLOCKENSPIEL           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_MUSIC_BOX              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_VIBRAPHONE             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_VIBES                 0x0F))
#define ROLAND_GR09_PROGRAM_MARIMBA                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_MARIMBA               0x0F))
#define ROLAND_GR09_PROGRAM_XYLOPHONE              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_TUBULAR_BELLS          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_DULCIMER               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_DRAWBAR_ORGAN          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PERCUSSIVE_ORGAN       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ROCK_ORGAN             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ROCK_ORGAN1           0x0F))
#define ROLAND_GR09_PROGRAM_CHURCH_ORGAN           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_REED_ORGAN             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ACCORDION              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_HARMONICA              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_HARMONICA             0x0F))
#define ROLAND_GR09_PROGRAM_TANGO_ACCORDION        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_ACOUSTIC_GUITAR_NYLON  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_NYLN_GUITAR           0x0F))
#define ROLAND_GR09_PROGRAM_ACOUSTIC_GUITAR_STEEL  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_STEEL_GUITAR1         0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_GUITAR_JAZZ   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_GUITAR_CLEAN  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_GUITAR_MUTED  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_OVERDRIVEN_GUITAR      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_DISTORTION_GUITAR      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_GUITAR_HARMONICS       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_GTR_HARMONICS1        0x0F))

#define ROLAND_GR09_PROGRAM_ACOUSTIC_BASS          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ACOUSTIC_BASS1        0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_BASS_FINGER   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ELECTRIC_BASS1        0x0F))
#define ROLAND_GR09_PROGRAM_ELECTRIC_BASS_PICK     (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FRETLESS_BASS          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_FRETLESS_BASS         0x0F))
#define ROLAND_GR09_PROGRAM_SLAP_BASS_1            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SLAP_BASS1            0x0F))
#define ROLAND_GR09_PROGRAM_SLAP_BASS_2            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SLAP_BASS2            0x0F))
#define ROLAND_GR09_PROGRAM_SYNTH_BASS_1           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTH_BASS_2           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_VIOLIN                 (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_VIOLIN                0x0F))
#define ROLAND_GR09_PROGRAM_VIOLA                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_CELLO                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CELLO1                0x0F))
#define ROLAND_GR09_PROGRAM_CONTRABASS             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CONTRA_BASS           0x0F))
#define ROLAND_GR09_PROGRAM_TREMOLO_STRINGS        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PIZZICATO_STRINGS      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ORCHESTRAL_HARP        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_HARP                  0x0F))
#define ROLAND_GR09_PROGRAM_TIMPANI                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_STRING_ENSEMBLE_1      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_STRING_ENSEMBLE_2      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTHSTRINGS_1         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTHSTRINGS_2         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_CHOIR_AAHS             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_VOICE_OOHS             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTH_VOICE            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_ORCHESTRA_HIT          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_TRUMPET                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_TRUMPET               0x0F))
#define ROLAND_GR09_PROGRAM_TROMBONE               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_TROMBONE              0x0F))
#define ROLAND_GR09_PROGRAM_TUBA                   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_TUBA                  0x0F))
#define ROLAND_GR09_PROGRAM_MUTED_TRUMPET          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_MUTE_TRUMPET          0x0F))
#define ROLAND_GR09_PROGRAM_FRENCH_HORN            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_FRENCH_HORN           0x0F))
#define ROLAND_GR09_PROGRAM_BRASS_SECTION          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTHBRASS_1           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTHBRASS_2           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_SOPRANO_SAX            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SOPRANO_SAX           0x0F))
#define ROLAND_GR09_PROGRAM_ALTO_SAX               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ALTO_SAX              0x0F))
#define ROLAND_GR09_PROGRAM_TENOR_SAX              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_TENOR_SAX             0x0F))
#define ROLAND_GR09_PROGRAM_BARITONE_SAX           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_OBOE                   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_OBOE                  0x0F))
#define ROLAND_GR09_PROGRAM_ENGLISH_HORN           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_BASSOON                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_CLARINET               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CLARINET              0x0F))

#define ROLAND_GR09_PROGRAM_PICCOLO                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_PICCOLO               0x0F))
#define ROLAND_GR09_PROGRAM_FLUTE                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_FLUTE                 0x0F))
#define ROLAND_GR09_PROGRAM_RECORDER               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PAN_FLUTE              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_BLOWN_BOTTLE           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_BOTTLE_BLOW           0x0F))
#define ROLAND_GR09_PROGRAM_SHAKUHACHI             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_WHISTLE                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_WHISTLE               0x0F))
#define ROLAND_GR09_PROGRAM_OCARINA                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_OCARINA               0x0F))

#define ROLAND_GR09_PROGRAM_LEAD_1_SQUARE          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SQUARE_LEAD           0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_2_SAWTOOTH        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SAW_LEAD              0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_3_CALLIOPE        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CALLIOPE              0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_4_CHIFF           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_5_CHARANG         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_6_VOICE           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_7_FIFTHS          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_LEAD_8_BASS_LEAD       (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_PAD_1_NEW_AGE          (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PAD_2_WARM             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PAD_3_POLYSYNTH        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_POLY_SYNTH1           0x0F))
#define ROLAND_GR09_PROGRAM_PAD_4_CHOIR            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_CHOIR_PAD             0x0F))
#define ROLAND_GR09_PROGRAM_PAD_5_BOWED            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PAD_6_METALLIC         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_METAL_PAD1            0x0F))
#define ROLAND_GR09_PROGRAM_PAD_7_HALO             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_PAD_8_SWEEP            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))




#define ROLAND_GR09_PROGRAM_FX_1_RAIN              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FX_2_SOUNDTRACK        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_SOUNDTRACK            0x0F))
#define ROLAND_GR09_PROGRAM_FX_3_CRYSTAL           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FX_4_ATMOSPHERE        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ATMOSPHERE            0x0F))
#define ROLAND_GR09_PROGRAM_FX_5_BRIGHTNESS        (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FX_6_GOBLINS           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FX_7_ECHOES            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FX_8_SCI_FI            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_SITAR                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_ELECTRIC_SITAR1       0x0F))
#define ROLAND_GR09_PROGRAM_BANJO                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_BANJO                 0x0F))
#define ROLAND_GR09_PROGRAM_SHAMISEN               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_KOTO                   (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_KALIMBA                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_BAG_PIPE               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_FIDDLE                 (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_FIDDLE                0x0F))
#define ROLAND_GR09_PROGRAM_SHANAI                 (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_TINKLE_BELL            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_AGOGO                  (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_STEEL_DRUMS            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_STEEL_DRUM            0x0F))
#define ROLAND_GR09_PROGRAM_WOODBLOCK              (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_TAIKO_DRUM             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_MELODIC_TOM            (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_SYNTH_DRUM             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_REVERSE_CYMBAL         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

#define ROLAND_GR09_PROGRAM_GUITAR_FRET_NOISE      (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_BREATH_NOISE           (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_BREATH                0x0F))
#define ROLAND_GR09_PROGRAM_SEASHORE               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_BIRD_TWEET             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_TELEPHONE_RING         (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_HELICOPTER             (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_APPLAUSE               (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))
#define ROLAND_GR09_PROGRAM_GUNSHOT                (ROLAND_GR09_GROUP  | (ROLAND_GR09_TONE_                      0x0F))

/*
Groups A and B (A11 to 84, B11 to 84) contain the 64 Preset Patches. (p. 77)
Groups C and D (C11 to 84, D11 to 84) provide 64 empty storage positions 
where you can write new Patches (User Patches). 

A11-A14 =  1- 4      C11-C14 =  65- 68
A21-A24 =  5- 8      C21-C24 =  69- 72
A31-A34 =  9-12      C31-C34 =  73- 76
A41-A44 = 13-16      C41-C44 =  77- 80
A51-A54 = 17-20      C51-C54 =  81- 84
A61-A64 = 21-24      C61-C64 =  85- 88
A71-A74 = 25-28      C71-C74 =  89- 92
AB1-AB4 = 29-32      C81-C84 =  93- 96
B11-B14 = 33-36      D11-D14 =  97-100
B21-B24 = 37-40      D21-D24 = 101-104
B31-B34 = 41-44      D31-D34 = 105-108
B41-B44 = 45-48      D41-D44 = 109-112
B51-B54 = 49-52      D51-D54 = 113-116
B61-B64 = 53-56      D61-D64 = 117-120
B71-B74 = 57-60      D71-D74 = 121-124
B81-B84 = 61-64      D81-D84 = 125-128

patch A11 = 01 00 00
patch D84 = 01 7F 00
*/

#endif
