/*
 * MIDIplan
 * Copyright (C) 2026 Dmitry Dvoinikov <dmitry@targeted.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "kawai_phm.h"

const midiplan_device_t kawai_phm = {

    .basic_channel = 1,

    .max_melodic_notes     = 16,
    .max_percussion_notes  = 8,
    .max_melodic_programs  = 4,
    .max_notes_per_program = 4,
    .monotimbral_channels  = 1,
    .max_notes_per_channel = 0,

    .key_pressure     = 0,
    .channel_pressure = 1,
    .pitch_bend       = 1,

    .melodic_programs = {
        /* 0x00   0  GM_PROGRAM_ACOUSTIC_GRAND_PIANO  */ {  .program = KAWAI_PHM_PROGRAM_UP_PIANO,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x01   1  GM_PROGRAM_BRIGHT_ACOUSTIC_PIANO */ {  .program = KAWAI_PHM_PROGRAM_JAZZPIANO,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x02   2  GM_PROGRAM_ELECTRIC_GRAND_PIANO  */ {  .program = KAWAI_PHM_PROGRAM_ELECTRIC_GRAND_PIANO_1,  .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x03   3  GM_PROGRAM_HONKY_TONK_PIANO      */ {  .program = KAWAI_PHM_PROGRAM_HONKY_TONK,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x04   4  GM_PROGRAM_ELECTRIC_PIANO_1      */ {  .program = KAWAI_PHM_PROGRAM_ELECTRIC_PIANO,          .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x05   5  GM_PROGRAM_ELECTRIC_PIANO_2      */ {  .program = KAWAI_PHM_PROGRAM_ELECTRIC_PIANO,          .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x06   6  GM_PROGRAM_HARPSICHORD           */ {  .program = KAWAI_PHM_PROGRAM_HARPSICHORD,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x07   7  GM_PROGRAM_CLAVI                 */ {  .program = KAWAI_PHM_PROGRAM_ORIENTBELL,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x08   8  GM_PROGRAM_CELESTA               */ {  .program = KAWAI_PHM_PROGRAM_BRITE_VIBE,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x09   9  GM_PROGRAM_GLOCKENSPIEL          */ {  .program = KAWAI_PHM_PROGRAM_OKOTO,                   .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x0A  10  GM_PROGRAM_MUSIC_BOX             */ {  .program = KAWAI_PHM_PROGRAM_ECHOPLEX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x0B  11  GM_PROGRAM_VIBRAPHONE            */ {  .program = KAWAI_PHM_PROGRAM_STEEL_DRUM,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x0C  12  GM_PROGRAM_MARIMBA               */ {  .program = KAWAI_PHM_PROGRAM_MARIMBA,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x0D  13  GM_PROGRAM_XYLOPHONE             */ {  .program = KAWAI_PHM_PROGRAM_ECHOPLEX,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x0E  14  GM_PROGRAM_TUBULAR_BELLS         */ {  .program = KAWAI_PHM_PROGRAM_BOTTLE_BELL,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x0F  15  GM_PROGRAM_DULCIMER              */ {  .program = KAWAI_PHM_PROGRAM_GLITTY_CLAV,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x10  16  GM_PROGRAM_DRAWBAR_ORGAN         */ {  .program = KAWAI_PHM_PROGRAM_PHANTOM,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x11  17  GM_PROGRAM_PERCUSSIVE_ORGAN      */ {  .program = KAWAI_PHM_PROGRAM_DA_BASS,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x12  18  GM_PROGRAM_ROCK_ORGAN            */ {  .program = KAWAI_PHM_PROGRAM_DEEP_PURPLE,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x13  19  GM_PROGRAM_CHURCH_ORGAN          */ {  .program = KAWAI_PHM_PROGRAM_SACRE_COEUR,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x14  20  GM_PROGRAM_REED_ORGAN            */ {  .program = KAWAI_PHM_PROGRAM_BLUE_MONICA,             .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER                   },
        /* 0x15  21  GM_PROGRAM_ACCORDION             */ {  .program = KAWAI_PHM_PROGRAM_ACCORDION,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x16  22  GM_PROGRAM_HARMONICA             */ {  .program = KAWAI_PHM_PROGRAM_BLUE_MONICA,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x17  23  GM_PROGRAM_TANGO_ACCORDION       */ {  .program = KAWAI_PHM_PROGRAM_ACCORDION,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x18  24  GM_PROGRAM_ACOUSTIC_GUITAR_NYLON */ {  .program = KAWAI_PHM_PROGRAM_REAL_RODES,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x19  25  GM_PROGRAM_ACOUSTIC_GUITAR_STEEL */ {  .program = KAWAI_PHM_PROGRAM_ACOUSTIC_GUITAR,         .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1A  26  GM_PROGRAM_ELECTRIC_GUITAR_JAZZ  */ {  .program = KAWAI_PHM_PROGRAM_STRATTO,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1B  27  GM_PROGRAM_ELECTRIC_GUITAR_CLEAN */ {  .program = KAWAI_PHM_PROGRAM_STRATTO,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1C  28  GM_PROGRAM_ELECTRIC_GUITAR_MUTED */ {  .program = KAWAI_PHM_PROGRAM_HARMONICS,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1D  29  GM_PROGRAM_OVERDRIVEN_GUITAR     */ {  .program = KAWAI_PHM_PROGRAM_OVERDRIVE,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1E  30  GM_PROGRAM_DISTORTION_GUITAR     */ {  .program = KAWAI_PHM_PROGRAM_DISTORTED_GUITAR,        .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x1F  31  GM_PROGRAM_GUITAR_HARMONICS      */ {  .program = KAWAI_PHM_PROGRAM_BASS_GUITAR_1,           .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x20  32  GM_PROGRAM_ACOUSTIC_BASS         */ {  .program = KAWAI_PHM_PROGRAM_BACKIN_SY_1,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x21  33  GM_PROGRAM_ELECTRIC_BASS_FINGER  */ {  .program = KAWAI_PHM_PROGRAM_PULL_BASS,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x22  34  GM_PROGRAM_ELECTRIC_BASS_PICK    */ {  .program = KAWAI_PHM_PROGRAM_KICK_BASS_1,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x23  35  GM_PROGRAM_FRETLESS_BASS         */ {  .program = KAWAI_PHM_PROGRAM_ROSIN_PUNCH,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x24  36  GM_PROGRAM_SLAP_BASS_1           */ {  .program = KAWAI_PHM_PROGRAM_KICK_BASS_1,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x25  37  GM_PROGRAM_SLAP_BASS_2           */ {  .program = KAWAI_PHM_PROGRAM_GLITTY_CLAV,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x26  38  GM_PROGRAM_SYNTH_BASS_1          */ {  .program = KAWAI_PHM_PROGRAM_BRASS_ENSEMBLE_1,        .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x27  39  GM_PROGRAM_SYNTH_BASS_2          */ {  .program = KAWAI_PHM_PROGRAM_BRASS_ENSEMBLE_2,        .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x28  40  GM_PROGRAM_VIOLIN                */ {  .program = KAWAI_PHM_PROGRAM_SOLO_VIOLIN,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x29  41  GM_PROGRAM_VIOLA                 */ {  .program = KAWAI_PHM_PROGRAM_LINE_STRINGS,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x2A  42  GM_PROGRAM_CELLO                 */ {  .program = KAWAI_PHM_PROGRAM_STRING_PAD,              .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x2B  43  GM_PROGRAM_CONTRABASS            */ {  .program = KAWAI_PHM_PROGRAM_CONTRABASS,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x2C  44  GM_PROGRAM_TREMOLO_STRINGS       */ {  .program = KAWAI_PHM_PROGRAM_SYNTH_SOLO_1,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x2D  45  GM_PROGRAM_PIZZICATO_STRINGS     */ {  .program = KAWAI_PHM_PROGRAM_OKOTO,                   .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x2E  46  GM_PROGRAM_ORCHESTRAL_HARP       */ {  .program = KAWAI_PHM_PROGRAM_HELLO,                   .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x2F  47  GM_PROGRAM_TIMPANI               */ {  .program = KAWAI_PHM_PROGRAM_TIMPANI,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x30  48  GM_PROGRAM_STRING_ENSEMBLE_1     */ {  .program = KAWAI_PHM_PROGRAM_CELLOS,                  .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x31  49  GM_PROGRAM_STRING_ENSEMBLE_2     */ {  .program = KAWAI_PHM_PROGRAM_FAT_STRINGS,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x32  50  GM_PROGRAM_SYNTHSTRINGS_1        */ {  .program = KAWAI_PHM_PROGRAM_GRAND_STRINGS,           .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x33  51  GM_PROGRAM_SYNTHSTRINGS_2        */ {  .program = KAWAI_PHM_PROGRAM_FAT_STRINGS,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x34  52  GM_PROGRAM_CHOIR_AAHS            */ {  .program = KAWAI_PHM_PROGRAM_AHH,                     .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x35  53  GM_PROGRAM_VOICE_OOHS            */ {  .program = KAWAI_PHM_PROGRAM_BREATH_ORG,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x36  54  GM_PROGRAM_SYNTH_VOICE           */ {  .program = KAWAI_PHM_PROGRAM_GLASSY,                  .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER                   },
        /* 0x37  55  GM_PROGRAM_ORCHESTRA_HIT         */ {  .program = KAWAI_PHM_PROGRAM_SINGLE_HIT,              .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x38  56  GM_PROGRAM_TRUMPET               */ {  .program = KAWAI_PHM_PROGRAM_TRUMPET,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x39  57  GM_PROGRAM_TROMBONE              */ {  .program = KAWAI_PHM_PROGRAM_NATURE_HORN,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x3A  58  GM_PROGRAM_TUBA                  */ {  .program = KAWAI_PHM_PROGRAM_NATURE_HORN,             .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER  | VOLUME_UP_6DB  },
        /* 0x3B  59  GM_PROGRAM_MUTED_TRUMPET         */ {  .program = KAWAI_PHM_PROGRAM_TRUMPET,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x3C  60  GM_PROGRAM_FRENCH_HORN           */ {  .program = KAWAI_PHM_PROGRAM_NATURE_HORN,             .flags = KAWAI_PHM_RANGE_DEFAULT       | VOLUME_UP_4DB  },
        /* 0x3D  61  GM_PROGRAM_BRASS_SECTION         */ {  .program = KAWAI_PHM_PROGRAM_BRASS_ENSEMBLE_2,        .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x3E  62  GM_PROGRAM_SYNTHBRASS_1          */ {  .program = KAWAI_PHM_PROGRAM_SYNTH_BRASS,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x3F  63  GM_PROGRAM_SYNTHBRASS_2          */ {  .program = KAWAI_PHM_PROGRAM_NASTY_BRASS,             .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x40  64  GM_PROGRAM_SOPRANO_SAX           */ {  .program = KAWAI_PHM_PROGRAM_SOLO_SAX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x41  65  GM_PROGRAM_ALTO_SAX              */ {  .program = KAWAI_PHM_PROGRAM_SOLO_SAX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x42  66  GM_PROGRAM_TENOR_SAX             */ {  .program = KAWAI_PHM_PROGRAM_SOLO_SAX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x43  67  GM_PROGRAM_BARITONE_SAX          */ {  .program = KAWAI_PHM_PROGRAM_SOLO_SAX,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x44  68  GM_PROGRAM_OBOE                  */ {  .program = KAWAI_PHM_PROGRAM_OBOE,                    .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x45  69  GM_PROGRAM_ENGLISH_HORN          */ {  .program = KAWAI_PHM_PROGRAM_ANALOG_HORN,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x46  70  GM_PROGRAM_BASSOON               */ {  .program = KAWAI_PHM_PROGRAM_ANALOG_HORN,             .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER  | VOLUME_UP_4DB  },
        /* 0x47  71  GM_PROGRAM_CLARINET              */ {  .program = KAWAI_PHM_PROGRAM_SOLO_SAX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x48  72  GM_PROGRAM_PICCOLO               */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x49  73  GM_PROGRAM_FLUTE                 */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x4A  74  GM_PROGRAM_RECORDER              */ {  .program = KAWAI_PHM_PROGRAM_WHISTLE,                 .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER                   },
        /* 0x4B  75  GM_PROGRAM_PAN_FLUTE             */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x4C  76  GM_PROGRAM_BLOWN_BOTTLE          */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x4D  77  GM_PROGRAM_SHAKUHACHI            */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x4E  78  GM_PROGRAM_WHISTLE               */ {  .program = KAWAI_PHM_PROGRAM_WHISTLE,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x4F  79  GM_PROGRAM_OCARINA               */ {  .program = KAWAI_PHM_PROGRAM_PAN_FLUTE,               .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x50  80  GM_PROGRAM_LEAD_1_SQUARE         */ {  .program = KAWAI_PHM_PROGRAM_SQUARE_LEAD,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x51  81  GM_PROGRAM_LEAD_2_SAWTOOTH       */ {  .program = KAWAI_PHM_PROGRAM_SYNTH_SOLO_1,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x52  82  GM_PROGRAM_LEAD_3_CALLIOPE       */ {  .program = KAWAI_PHM_PROGRAM_ECHOPLEX,                .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x53  83  GM_PROGRAM_LEAD_4_CHIFF          */ {  .program = KAWAI_PHM_PROGRAM_REVERB_SYNTH,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x54  84  GM_PROGRAM_LEAD_5_CHARANG        */ {  .program = KAWAI_PHM_PROGRAM_JUMP_PHM,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x55  85  GM_PROGRAM_LEAD_6_VOICE          */ {  .program = KAWAI_PHM_PROGRAM_MOONRAKER,               .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x56  86  GM_PROGRAM_LEAD_7_FIFTHS         */ {  .program = KAWAI_PHM_PROGRAM_REVERB_SYNTH,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x57  87  GM_PROGRAM_LEAD_8_BASS_LEAD      */ {  .program = KAWAI_PHM_PROGRAM_BACKIN_SY_1,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x58  88  GM_PROGRAM_PAD_1_NEW_AGE         */ {  .program = KAWAI_PHM_PROGRAM_WINE_GLASS,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x59  89  GM_PROGRAM_PAD_2_WARM            */ {  .program = KAWAI_PHM_PROGRAM_AMAZING,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5A  90  GM_PROGRAM_PAD_3_POLYSYNTH       */ {  .program = KAWAI_PHM_PROGRAM_ANALOG_SYNTH,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5B  91  GM_PROGRAM_PAD_4_CHOIR           */ {  .program = KAWAI_PHM_PROGRAM_FAL_IN_ANGEL,            .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5C  92  GM_PROGRAM_PAD_5_BOWED           */ {  .program = KAWAI_PHM_PROGRAM_SOFT_BRASS,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5D  93  GM_PROGRAM_PAD_6_METALLIC        */ {  .program = KAWAI_PHM_PROGRAM_MOONRAKER,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5E  94  GM_PROGRAM_PAD_7_HALO            */ {  .program = KAWAI_PHM_PROGRAM_STRING_PAD,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x5F  95  GM_PROGRAM_PAD_8_SWEEP           */ {  .program = KAWAI_PHM_PROGRAM_ARRANGEMENT,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x60  96  GM_PROGRAM_FX_1_RAIN             */ {  .program = KAWAI_PHM_PROGRAM_RAIN,                    .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x61  97  GM_PROGRAM_FX_2_SOUNDTRACK       */ {  .program = KAWAI_PHM_PROGRAM_ARRANGEMENT,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x62  98  GM_PROGRAM_FX_3_CRYSTAL          */ {  .program = KAWAI_PHM_PROGRAM_WINE_GLASS,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x63  99  GM_PROGRAM_FX_4_ATMOSPHERE       */ {  .program = KAWAI_PHM_PROGRAM_BRITE_VIBE,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x64 100  GM_PROGRAM_FX_5_BRIGHTNESS       */ {  .program = KAWAI_PHM_PROGRAM_GLASSY,                  .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x65 101  GM_PROGRAM_FX_6_GOBLINS          */ {  .program = KAWAI_PHM_PROGRAM_FAL_IN_ANGEL,            .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x66 102  GM_PROGRAM_FX_7_ECHOES           */ {  .program = KAWAI_PHM_PROGRAM_AHH,                     .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x67 103  GM_PROGRAM_FX_8_SCI_FI           */ {  .program = KAWAI_PHM_PROGRAM_DEEP_SPACE,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x68 104  GM_PROGRAM_SITAR                 */ {  .program = KAWAI_PHM_PROGRAM_SITAR,                   .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x69 105  GM_PROGRAM_BANJO                 */ {  .program = KAWAI_PHM_PROGRAM_BANJO,                   .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6A 106  GM_PROGRAM_SHAMISEN              */ {  .program = KAWAI_PHM_PROGRAM_BANJO,                   .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6B 107  GM_PROGRAM_KOTO                  */ {  .program = KAWAI_PHM_PROGRAM_HELLO,                   .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6C 108  GM_PROGRAM_KALIMBA               */ {  .program = KAWAI_PHM_PROGRAM_MARIMBA,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6D 109  GM_PROGRAM_BAG_PIPE              */ {  .program = KAWAI_PHM_PROGRAM_KILTBLOWER,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6E 110  GM_PROGRAM_FIDDLE                */ {  .program = KAWAI_PHM_PROGRAM_FIDDLER,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x6F 111  GM_PROGRAM_SHANAI                */ {  .program = KAWAI_PHM_PROGRAM_OBOE,                    .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x70 112  GM_PROGRAM_TINKLE_BELL           */ {  .program = KAWAI_PHM_PROGRAM_OKOTO,                   .flags = KAWAI_PHM_RANGE_OCTAVE_HIGHER                  },
        /* 0x71 113  GM_PROGRAM_AGOGO                 */ {  .program = KAWAI_PHM_PROGRAM_BRITE_VIBE,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x72 114  GM_PROGRAM_STEEL_DRUMS           */ {  .program = KAWAI_PHM_PROGRAM_STEEL_DRUM,              .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x73 115  GM_PROGRAM_WOODBLOCK             */ {  .program = KAWAI_PHM_PROGRAM_ECHOPLEX,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x74 116  GM_PROGRAM_TAIKO_DRUM            */ {  .program = KAWAI_PHM_PROGRAM_A_TOM_PLUS_HI_HAT,       .flags = KAWAI_PHM_RANGE_LOWER_HALF                     },
        /* 0x75 117  GM_PROGRAM_MELODIC_TOM           */ {  .program = KAWAI_PHM_PROGRAM_A_TOM_PLUS_HI_HAT,       .flags = KAWAI_PHM_RANGE_LOWER_HALF                     },
        /* 0x76 118  GM_PROGRAM_SYNTH_DRUM            */ {  .program = KAWAI_PHM_PROGRAM_CHRYSALIS,               .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER                   },
        /* 0x77 119  GM_PROGRAM_REVERSE_CYMBAL        */ {  .program = KAWAI_PHM_PROGRAM_SCRATCH_1,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x78 120  GM_PROGRAM_GUITAR_FRET_NOISE     */ {  .program = KAWAI_PHM_PROGRAM_AHH,                     .flags = KAWAI_PHM_RANGE_OCTAVE_LOWER                   },
        /* 0x79 121  GM_PROGRAM_BREATH_NOISE          */ {  .program = KAWAI_PHM_PROGRAM_AHH,                     .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7A 122  GM_PROGRAM_SEASHORE              */ {  .program = KAWAI_PHM_PROGRAM_RAIN,                    .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7B 123  GM_PROGRAM_BIRD_TWEET            */ {  .program = KAWAI_PHM_PROGRAM_UMI_NEKO,                .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7C 124  GM_PROGRAM_TELEPHONE_RING        */ {  .program = KAWAI_PHM_PROGRAM_GLITTY_CLAV,             .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7D 125  GM_PROGRAM_HELICOPTER            */ {  .program = KAWAI_PHM_PROGRAM_MACHINE,                 .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7E 126  GM_PROGRAM_APPLAUSE              */ {  .program = KAWAI_PHM_PROGRAM_SCRATCH_1,               .flags = KAWAI_PHM_RANGE_DEFAULT                        },
        /* 0x7F 127  GM_PROGRAM_GUNSHOT               */ {  .program = KAWAI_PHM_PROGRAM_CANNON_AND_GUN,          .flags = KAWAI_PHM_RANGE_DEFAULT                        }
    },

    .melodic_note_ranges = {
        /* 0x00 KAWAI_PHM_RANGE_INVALID       */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x01 KAWAI_PHM_RANGE_OCTAVE_HIGHER */ {  .lowest_note = KAWAI_PHM_LOWEST_NOTE,  .middle_c = KAWAI_PHM_MIDDLE_C + 12,  .highest_note = KAWAI_PHM_HIGHEST_NOTE  },
        /* 0x02 KAWAI_PHM_RANGE_OCTAVE_LOWER  */ {  .lowest_note = KAWAI_PHM_LOWEST_NOTE,  .middle_c = KAWAI_PHM_MIDDLE_C - 12,  .highest_note = KAWAI_PHM_HIGHEST_NOTE  },
        /* 0x03 KAWAI_PHM_RANGE_LOWER_HALF    */ {  .lowest_note = KAWAI_PHM_LOWEST_NOTE,  .middle_c = KAWAI_PHM_MIDDLE_C - 24,  .highest_note = KAWAI_PHM_MIDDLE_C - 1  },
        /* 0x04                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x05                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x06                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x07                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x08                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x09                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0A                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0B                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0C                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0D                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0E                               */ {  .lowest_note = INVALID_NOTE,           .middle_c = INVALID_NOTE,             .highest_note = INVALID_NOTE            },
        /* 0x0F KAWAI_PHM_RANGE_DEFAULT       */ {  .lowest_note = KAWAI_PHM_LOWEST_NOTE,  .middle_c = KAWAI_PHM_MIDDLE_C,       .highest_note = KAWAI_PHM_HIGHEST_NOTE  }
    },

    .percussion_notes = {
        /* 0x00   0  GM_PERCUSSION_UNDEFINED_00       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x01   1  GM_PERCUSSION_UNDEFINED_01       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x02   2  GM_PERCUSSION_UNDEFINED_02       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x03   3  GM_PERCUSSION_UNDEFINED_03       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x04   4  GM_PERCUSSION_UNDEFINED_04       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x05   5  GM_PERCUSSION_UNDEFINED_05       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x06   6  GM_PERCUSSION_UNDEFINED_06       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x07   7  GM_PERCUSSION_UNDEFINED_07       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x08   8  GM_PERCUSSION_UNDEFINED_08       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x09   9  GM_PERCUSSION_UNDEFINED_09       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0A  10  GM_PERCUSSION_UNDEFINED_0A       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0B  11  GM_PERCUSSION_UNDEFINED_0B       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0C  12  GM_PERCUSSION_UNDEFINED_0C       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0D  13  GM_PERCUSSION_UNDEFINED_0D       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0E  14  GM_PERCUSSION_UNDEFINED_0E       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x0F  15  GM_PERCUSSION_UNDEFINED_0F       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x10  16  GM_PERCUSSION_UNDEFINED_10       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x11  17  GM_PERCUSSION_UNDEFINED_11       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x12  18  GM_PERCUSSION_UNDEFINED_12       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x13  19  GM_PERCUSSION_UNDEFINED_13       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x14  20  GM_PERCUSSION_UNDEFINED_14       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x15  21  GM_PERCUSSION_UNDEFINED_15       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x16  22  GM_PERCUSSION_UNDEFINED_16       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x17  23  GM_PERCUSSION_UNDEFINED_17       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x18  24  GM_PERCUSSION_UNDEFINED_18       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x19  25  GM_PERCUSSION_UNDEFINED_19       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1A  26  GM_PERCUSSION_UNDEFINED_1A       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1B  27  GM_PERCUSSION_UNDEFINED_1B       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1C  28  GM_PERCUSSION_UNDEFINED_1C       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1D  29  GM_PERCUSSION_UNDEFINED_1D       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1E  30  GM_PERCUSSION_UNDEFINED_1E       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x1F  31  GM_PERCUSSION_UNDEFINED_1F       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x20  32  GM_PERCUSSION_UNDEFINED_20       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x21  33  GM_PERCUSSION_UNDEFINED_21       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x22  34  GM_PERCUSSION_UNDEFINED_22       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x23  35  GM_PERCUSSION_ACOUSTIC_BASS_DRUM */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_ACOUSTIC_BASS_DRUM   },
        /* 0x24  36  GM_PERCUSSION_BASS_DRUM_1        */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_ACOUSTIC_BASS_DRUM   },
        /* 0x25  37  GM_PERCUSSION_SIDE_STICK         */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_RIM_SHOT             },
        /* 0x26  38  GM_PERCUSSION_ACOUSTIC_SNARE     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_ACOUSTIC_SNARE_DRUM  },
        /* 0x27  39  GM_PERCUSSION_HAND_CLAP          */ {  .program = KAWAI_PHM_PROGRAM_MACHINE,       .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x28  40  GM_PERCUSSION_ELECTRIC_SNARE     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_E_SNARE_DRUM         },
        /* 0x29  41  GM_PERCUSSION_LOW_FLOOR_TOM      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_LOW_TOM              },
        /* 0x2A  42  GM_PERCUSSION_CLOSED_HI_HAT      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CLOSED_HI_HAT        },
        /* 0x2B  43  GM_PERCUSSION_HIGH_FLOOR_TOM     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x2C  44  GM_PERCUSSION_PEDAL_HI_HAT       */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CLOSED_HI_HAT        },
        /* 0x2D  45  GM_PERCUSSION_LOW_TOM            */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_LOW_TOM              },
        /* 0x2E  46  GM_PERCUSSION_OPEN_HI_HAT        */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_OPEN_HI_HAT          },
        /* 0x2F  47  GM_PERCUSSION_LOW_MID_TOM        */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_LOW_TOM              },
        /* 0x30  48  GM_PERCUSSION_HI_MID_TOM         */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x31  49  GM_PERCUSSION_CRASH_CYMBAL_1     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CRASH_CYMBAL         },
        /* 0x32  50  GM_PERCUSSION_HIGH_TOM           */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x33  51  GM_PERCUSSION_RIDE_CYMBAL_1      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_RIDE_CYMBAL          },
        /* 0x34  52  GM_PERCUSSION_CHINESE_CYMBAL     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CRASH_CYMBAL         },
        /* 0x35  53  GM_PERCUSSION_RIDE_BELL          */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_RIDE_CYMBAL          },
        /* 0x36  54  GM_PERCUSSION_TAMBOURINE         */ {  .program = KAWAI_PHM_PROGRAM_TAMBOURINE,    .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x37  55  GM_PERCUSSION_SPLASH_CYMBAL      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CRASH_CYMBAL         },
        /* 0x38  56  GM_PERCUSSION_COWBELL            */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_COWBELL              },
        /* 0x39  57  GM_PERCUSSION_CRASH_CYMBAL_2     */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CRASH_CYMBAL         },
        /* 0x3A  58  GM_PERCUSSION_VIBRASLAP          */ {  .program = KAWAI_PHM_PROGRAM_CASTANET,      .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x3B  59  GM_PERCUSSION_RIDE_CYMBAL_2      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_RIDE_CYMBAL          },
        /* 0x3C  60  GM_PERCUSSION_HI_BONGO           */ {  .program = KAWAI_PHM_PROGRAM_BONGO_COWBOY,  .note = KAWAI_PHM_MIDDLE_C - 1                    },
        /* 0x3D  61  GM_PERCUSSION_LOW_BONGO          */ {  .program = KAWAI_PHM_PROGRAM_BONGO_COWBOY,  .note = KAWAI_PHM_MIDDLE_C - 12                   },
        /* 0x3E  62  GM_PERCUSSION_MUTE_HI_CONGA      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x3F  63  GM_PERCUSSION_OPEN_HI_CONGA      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x40  64  GM_PERCUSSION_LOW_CONGA          */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_LOW_TOM              },
        /* 0x41  65  GM_PERCUSSION_HIGH_TIMBALE       */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x42  66  GM_PERCUSSION_LOW_TIMBALE        */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_HI_TOM               },
        /* 0x43  67  GM_PERCUSSION_HIGH_AGOGO         */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_AGOGO                },
        /* 0x44  68  GM_PERCUSSION_LOW_AGOGO          */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_AGOGO                },
        /* 0x45  69  GM_PERCUSSION_CABASA             */ {  .program = KAWAI_PHM_PROGRAM_SCRATCH_1,     .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x46  70  GM_PERCUSSION_MARACAS            */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_FINGER_SNAP          },
        /* 0x47  71  GM_PERCUSSION_SHORT_WHISTLE      */ {  .program = KAWAI_PHM_PROGRAM_WHISTLE,       .note = KAWAI_PHM_MIDDLE_C + 12                   },
        /* 0x48  72  GM_PERCUSSION_LONG_WHISTLE       */ {  .program = KAWAI_PHM_PROGRAM_WHISTLE,       .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x49  73  GM_PERCUSSION_SHORT_GUIRO        */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_AGOGO                },
        /* 0x4A  74  GM_PERCUSSION_LONG_GUIRO         */ {  .program = KAWAI_PHM_PROGRAM_CASTANET,      .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x4B  75  GM_PERCUSSION_CLAVES             */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_AGOGO                },
        /* 0x4C  76  GM_PERCUSSION_HI_WOOD_BLOCK      */ {  .program = KAWAI_PHM_PROGRAM_MACHINE,       .note = KAWAI_PHM_MIDDLE_C + 12                   },
        /* 0x4D  77  GM_PERCUSSION_LOW_WOOD_BLOCK     */ {  .program = KAWAI_PHM_PROGRAM_MACHINE,       .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x4E  78  GM_PERCUSSION_MUTE_CUICA         */ {  .program = KAWAI_PHM_PROGRAM_SCRATCH_1,     .note = KAWAI_PHM_MIDDLE_C + 12                   },
        /* 0x4F  79  GM_PERCUSSION_OPEN_CUICA         */ {  .program = KAWAI_PHM_PROGRAM_SCRATCH_1,     .note = KAWAI_PHM_MIDDLE_C                        },
        /* 0x50  80  GM_PERCUSSION_MUTE_TRIANGLE      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_CLOSED_HI_HAT        },
        /* 0x51  81  GM_PERCUSSION_OPEN_TRIANGLE      */ {  .program = PERCUSSION_PROGRAM,              .note = KAWAI_PHM_PERCUSSION_OPEN_HI_HAT          },
        /* 0x52  82  GM_PERCUSSION_UNDEFINED_52       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x53  83  GM_PERCUSSION_UNDEFINED_53       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x54  84  GM_PERCUSSION_UNDEFINED_54       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x55  85  GM_PERCUSSION_UNDEFINED_55       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x56  86  GM_PERCUSSION_UNDEFINED_56       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x57  87  GM_PERCUSSION_UNDEFINED_57       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x58  88  GM_PERCUSSION_UNDEFINED_58       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x59  89  GM_PERCUSSION_UNDEFINED_59       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5A  90  GM_PERCUSSION_UNDEFINED_5A       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5B  91  GM_PERCUSSION_UNDEFINED_5B       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5C  92  GM_PERCUSSION_UNDEFINED_5C       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5D  93  GM_PERCUSSION_UNDEFINED_5D       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5E  94  GM_PERCUSSION_UNDEFINED_5E       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x5F  95  GM_PERCUSSION_UNDEFINED_5F       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x60  96  GM_PERCUSSION_UNDEFINED_60       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x61  97  GM_PERCUSSION_UNDEFINED_61       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x62  98  GM_PERCUSSION_UNDEFINED_62       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x63  99  GM_PERCUSSION_UNDEFINED_63       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x64 100  GM_PERCUSSION_UNDEFINED_64       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x65 101  GM_PERCUSSION_UNDEFINED_65       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x66 102  GM_PERCUSSION_UNDEFINED_66       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x67 103  GM_PERCUSSION_UNDEFINED_67       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x68 104  GM_PERCUSSION_UNDEFINED_68       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x69 105  GM_PERCUSSION_UNDEFINED_69       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6A 106  GM_PERCUSSION_UNDEFINED_6A       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6B 107  GM_PERCUSSION_UNDEFINED_6B       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6C 108  GM_PERCUSSION_UNDEFINED_6C       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6D 109  GM_PERCUSSION_UNDEFINED_6D       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6E 110  GM_PERCUSSION_UNDEFINED_6E       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x6F 111  GM_PERCUSSION_UNDEFINED_6F       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x70 112  GM_PERCUSSION_UNDEFINED_70       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x71 113  GM_PERCUSSION_UNDEFINED_71       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x72 114  GM_PERCUSSION_UNDEFINED_72       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x73 115  GM_PERCUSSION_UNDEFINED_73       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x74 116  GM_PERCUSSION_UNDEFINED_74       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x75 117  GM_PERCUSSION_UNDEFINED_75       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x76 118  GM_PERCUSSION_UNDEFINED_76       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x77 119  GM_PERCUSSION_UNDEFINED_77       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x78 120  GM_PERCUSSION_UNDEFINED_78       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x79 121  GM_PERCUSSION_UNDEFINED_79       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7A 122  GM_PERCUSSION_UNDEFINED_7A       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7B 123  GM_PERCUSSION_UNDEFINED_7B       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7C 124  GM_PERCUSSION_UNDEFINED_7C       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7D 125  GM_PERCUSSION_UNDEFINED_7D       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7E 126  GM_PERCUSSION_UNDEFINED_7E       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              },
        /* 0x7F 127  GM_PERCUSSION_UNDEFINED_7F       */ {  .program = INVALID_PROGRAM,                 .note = INVALID_NOTE                              }
    },

    /* the following is expressed in device's terms */

    .melodic_channels_bitmaps_refs = {
        //--||--||--||--||--||--||--||--||
        0b11111111111111111111111111111111, //  15/0Fh -   0/00h
        0b11111111111111111111111111111111, //  31/1Fh -  16/10h
        0b11111111111111111111111111111111, //  47/2Fh -  32/20h
        0b11111111111111111111111111111111, //  63/3Fh -  48/30h
        0b11111111111111111111111111111111, //  79/4Fh -  64/40h
        0b11111111111111111111111111111111, //  95/5Fh -  80/50h
        0b00000000000000000000000011111111, // 111/6Fh -  96/60h
        0b00000000000000000000000000000000  // 127/7Fh - 112/70h
    },

    .melodic_channels_bitmaps = {
        0b0000000000000000, // 00
        0b0000000000000000, // 01
        0b0000000000000000, // 10
        0b0000000011110000  // 11 ** using form 28 **
    },

    .percussion_channels_bitmap = 0b0000001000000000,

    .controllers_bitmap = {

      //(1 << (MIDI_CONTROL_BANK_SELECT                  & 0x1F)) |  /* 0x00   0 */
        (1 << (MIDI_CONTROL_MODULATION_WHEEL_OR_LEVER    & 0x1F)) |  /* 0x01   1 */
      //(1 << (MIDI_CONTROL_BREATH_CONTROLLER            & 0x1F)) |  /* 0x02   2 */
      //(1 << (MIDI_CONTROL_UNDEFINED_03                 & 0x1F)) |  /* 0x03   3 */
      //(1 << (MIDI_CONTROL_FOOT_CONTROLLER              & 0x1F)) |  /* 0x04   4 */
        (1 << (MIDI_CONTROL_PORTAMENTO_TIME              & 0x1F)) |  /* 0x05   5 */
        (1 << (MIDI_CONTROL_DATA_ENTRY_MSB               & 0x1F)) |  /* 0x06   6 */
        (1 << (MIDI_CONTROL_CHANNEL_VOLUME               & 0x1F)) |  /* 0x07   7 */
      //(1 << (MIDI_CONTROL_BALANCE                      & 0x1F)) |  /* 0x08   8 */
      //(1 << (MIDI_CONTROL_UNDEFINED_09                 & 0x1F)) |  /* 0x09   9 */
        (1 << (MIDI_CONTROL_PAN                          & 0x1F)) |  /* 0x0A  10 */
        (1 << (MIDI_CONTROL_EXPRESSION_CONTROLLER        & 0x1F)) |  /* 0x0B  11 */
      //(1 << (MIDI_CONTROL_EFFECT_CONTROL_1             & 0x1F)) |  /* 0x0C  12 */
      //(1 << (MIDI_CONTROL_EFFECT_CONTROL_2             & 0x1F)) |  /* 0x0D  13 */
      //(1 << (MIDI_CONTROL_UNDEFINED_0E                 & 0x1F)) |  /* 0x0E  14 */
      //(1 << (MIDI_CONTROL_UNDEFINED_0F                 & 0x1F)) |  /* 0x0F  15 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1 & 0x1F)) |  /* 0x10  16 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2 & 0x1F)) |  /* 0x11  17 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3 & 0x1F)) |  /* 0x12  18 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4 & 0x1F)) |  /* 0x13  19 */
      //(1 << (MIDI_CONTROL_UNDEFINED_14                 & 0x1F)) |  /* 0x14  20 */
      //(1 << (MIDI_CONTROL_UNDEFINED_15                 & 0x1F)) |  /* 0x15  21 */
      //(1 << (MIDI_CONTROL_UNDEFINED_16                 & 0x1F)) |  /* 0x16  22 */
      //(1 << (MIDI_CONTROL_UNDEFINED_17                 & 0x1F)) |  /* 0x17  23 */
      //(1 << (MIDI_CONTROL_UNDEFINED_18                 & 0x1F)) |  /* 0x18  24 */
      //(1 << (MIDI_CONTROL_UNDEFINED_19                 & 0x1F)) |  /* 0x19  25 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1A                 & 0x1F)) |  /* 0x1A  26 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1B                 & 0x1F)) |  /* 0x1B  27 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1C                 & 0x1F)) |  /* 0x1C  28 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1D                 & 0x1F)) |  /* 0x1D  29 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1E                 & 0x1F)) |  /* 0x1E  30 */
      //(1 << (MIDI_CONTROL_UNDEFINED_1F                 & 0x1F)) |  /* 0x1F  31 */

        0, //---------------------------------------------------------------------

      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_00               & 0x1F)) |  /* 0x20  32 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_01               & 0x1F)) |  /* 0x21  33 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_02               & 0x1F)) |  /* 0x22  34 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_03               & 0x1F)) |  /* 0x23  35 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_04               & 0x1F)) |  /* 0x24  36 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_05               & 0x1F)) |  /* 0x25  37 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_06               & 0x1F)) |  /* 0x26  38 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_07               & 0x1F)) |  /* 0x27  39 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_08               & 0x1F)) |  /* 0x28  40 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_09               & 0x1F)) |  /* 0x29  41 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_0A               & 0x1F)) |  /* 0x2A  42 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_0B               & 0x1F)) |  /* 0x2B  43 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0C               & 0x1F)) |  /* 0x2C  44 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0D               & 0x1F)) |  /* 0x2D  45 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0E               & 0x1F)) |  /* 0x2E  46 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0F               & 0x1F)) |  /* 0x2F  47 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_10               & 0x1F)) |  /* 0x30  48 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_11               & 0x1F)) |  /* 0x31  49 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_12               & 0x1F)) |  /* 0x32  50 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_13               & 0x1F)) |  /* 0x33  51 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_14               & 0x1F)) |  /* 0x34  52 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_15               & 0x1F)) |  /* 0x35  53 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_16               & 0x1F)) |  /* 0x36  54 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_17               & 0x1F)) |  /* 0x37  55 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_18               & 0x1F)) |  /* 0x38  56 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_19               & 0x1F)) |  /* 0x39  57 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1A               & 0x1F)) |  /* 0x3A  58 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1B               & 0x1F)) |  /* 0x3B  59 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1C               & 0x1F)) |  /* 0x3C  60 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1D               & 0x1F)) |  /* 0x3D  61 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1E               & 0x1F)) |  /* 0x3E  62 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_1F               & 0x1F)) |  /* 0x3F  63 */

        0, //---------------------------------------------------------------------

        (1 << (MIDI_CONTROL_SUSTAIN                      & 0x1F)) |  /* 0x40  64 */
        (1 << (MIDI_CONTROL_PORTAMENTO_ON_OFF            & 0x1F)) |  /* 0x41  65 */
        (1 << (MIDI_CONTROL_SOSTENUTO                    & 0x1F)) |  /* 0x42  66 */
        (1 << (MIDI_CONTROL_SOFT_PEDAL                   & 0x1F)) |  /* 0x43  67 */
      //(1 << (MIDI_CONTROL_LEGATO_FOOTSWITCH            & 0x1F)) |  /* 0x44  68 */
      //(1 << (MIDI_CONTROL_HOLD_2                       & 0x1F)) |  /* 0x45  69 */
      //(1 << (MIDI_CONTROL_SOUND_VARIATION              & 0x1F)) |  /* 0x46  70 */
      //(1 << (MIDI_CONTROL_TIMBRE_HARMONIC_INTENSITY    & 0x1F)) |  /* 0x47  71 */
      //(1 << (MIDI_CONTROL_RELEASE_TIME                 & 0x1F)) |  /* 0x48  72 */
      //(1 << (MIDI_CONTROL_ATTACK_TIME                  & 0x1F)) |  /* 0x49  73 */
      //(1 << (MIDI_CONTROL_BRIGHTNESS                   & 0x1F)) |  /* 0x4A  74 */
      //(1 << (MIDI_CONTROL_DECAY_TIME                   & 0x1F)) |  /* 0x4B  75 */
      //(1 << (MIDI_CONTROL_VIBRATO_RATE                 & 0x1F)) |  /* 0x4C  76 */
      //(1 << (MIDI_CONTROL_VIBRATO_DEPTH                & 0x1F)) |  /* 0x4D  77 */
      //(1 << (MIDI_CONTROL_VIBRATO_DELAY                & 0x1F)) |  /* 0x4E  78 */
      //(1 << (MIDI_CONTROL_SOUND_CONTROLLER_10          & 0x1F)) |  /* 0x4F  79 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5 & 0x1F)) |  /* 0x50  80 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6 & 0x1F)) |  /* 0x51  81 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7 & 0x1F)) |  /* 0x52  82 */
      //(1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8 & 0x1F)) |  /* 0x53  83 */
      //(1 << (MIDI_CONTROL_PORTAMENTO_CONTROL           & 0x1F)) |  /* 0x54  84 */
      //(1 << (MIDI_CONTROL_UNDEFINED_55                 & 0x1F)) |  /* 0x55  85 */
      //(1 << (MIDI_CONTROL_UNDEFINED_56                 & 0x1F)) |  /* 0x56  86 */
      //(1 << (MIDI_CONTROL_UNDEFINED_57                 & 0x1F)) |  /* 0x57  87 */
      //(1 << (MIDI_CONTROL_UNDEFINED_58                 & 0x1F)) |  /* 0x58  88 */
      //(1 << (MIDI_CONTROL_UNDEFINED_59                 & 0x1F)) |  /* 0x59  89 */
      //(1 << (MIDI_CONTROL_UNDEFINED_5A                 & 0x1F)) |  /* 0x5A  90 */
      //(1 << (MIDI_CONTROL_REVERB_SEND_LEVEL            & 0x1F)) |  /* 0x5B  91 */
      //(1 << (MIDI_CONTROL_EFFECTS_DEPTH_2              & 0x1F)) |  /* 0x5C  92 */
      //(1 << (MIDI_CONTROL_CHORUS_SEND_LEVEL            & 0x1F)) |  /* 0x5D  93 */
      //(1 << (MIDI_CONTROL_EFFECTS_DEPTH_4              & 0x1F)) |  /* 0x5E  94 */
      //(1 << (MIDI_CONTROL_EFFECTS_DEPTH_5              & 0x1F)) |  /* 0x5F  95 */

        0, //---------------------------------------------------------------------

        (1 << (MIDI_CONTROL_DATA_INCREMENT               & 0x1F)) |  /* 0x60  96 */
        (1 << (MIDI_CONTROL_DATA_DECREMENT               & 0x1F)) |  /* 0x61  97 */
      //(1 << (MIDI_CONTROL_NON_REGISTERED_PARAMETER_LSB & 0x1F)) |  /* 0x62  98 */
      //(1 << (MIDI_CONTROL_NON_REGISTERED_PARAMETER_MSB & 0x1F)) |  /* 0x63  99 */
        (1 << (MIDI_CONTROL_REGISTERED_PARAMETER_LSB     & 0x1F)) |  /* 0x64 100 */
        (1 << (MIDI_CONTROL_REGISTERED_PARAMETER_MSB     & 0x1F)) |  /* 0x65 101 */
      //(1 << (MIDI_CONTROL_UNDEFINED_66                 & 0x1F)) |  /* 0x66 102 */
      //(1 << (MIDI_CONTROL_UNDEFINED_67                 & 0x1F)) |  /* 0x67 103 */
      //(1 << (MIDI_CONTROL_UNDEFINED_68                 & 0x1F)) |  /* 0x68 104 */
      //(1 << (MIDI_CONTROL_UNDEFINED_69                 & 0x1F)) |  /* 0x69 105 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6A                 & 0x1F)) |  /* 0x6A 106 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6B                 & 0x1F)) |  /* 0x6B 107 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6C                 & 0x1F)) |  /* 0x6C 108 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6D                 & 0x1F)) |  /* 0x6D 109 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6E                 & 0x1F)) |  /* 0x6E 110 */
      //(1 << (MIDI_CONTROL_UNDEFINED_6F                 & 0x1F)) |  /* 0x6F 111 */
      //(1 << (MIDI_CONTROL_UNDEFINED_70                 & 0x1F)) |  /* 0x70 112 */
      //(1 << (MIDI_CONTROL_UNDEFINED_71                 & 0x1F)) |  /* 0x71 113 */
      //(1 << (MIDI_CONTROL_UNDEFINED_72                 & 0x1F)) |  /* 0x72 114 */
      //(1 << (MIDI_CONTROL_UNDEFINED_73                 & 0x1F)) |  /* 0x73 115 */
      //(1 << (MIDI_CONTROL_UNDEFINED_74                 & 0x1F)) |  /* 0x74 116 */
      //(1 << (MIDI_CONTROL_UNDEFINED_75                 & 0x1F)) |  /* 0x75 117 */
      //(1 << (MIDI_CONTROL_UNDEFINED_76                 & 0x1F)) |  /* 0x76 118 */
      //(1 << (MIDI_CONTROL_UNDEFINED_77                 & 0x1F)) |  /* 0x77 119 */
      //(1 << (MIDI_CHANNEL_MODE_ALL_SOUND_OFF           & 0x1F)) |  /* 0x78 120 */
      //(1 << (MIDI_CHANNEL_MODE_RESET_ALL_CONTROLLERS   & 0x1F)) |  /* 0x79 121 */
      //(1 << (MIDI_CHANNEL_MODE_LOCAL_CONTROL_ON_OFF    & 0x1F)) |  /* 0x7A 122 */
      //(1 << (MIDI_CHANNEL_MODE_ALL_NOTES_OFF           & 0x1F)) |  /* 0x7B 123 */
      //(1 << (MIDI_CHANNEL_MODE_OMNI_OFF                & 0x1F)) |  /* 0x7C 124 */
      //(1 << (MIDI_CHANNEL_MODE_OMNI_ON                 & 0x1F)) |  /* 0x7D 125 */
      //(1 << (MIDI_CHANNEL_MODE_MONO_ON                 & 0x1F)) |  /* 0x7E 126 */
      //(1 << (MIDI_CHANNEL_MODE_POLY_ON                 & 0x1F)) |  /* 0x7F 127 */

        0, //---------------------------------------------------------------------

    },

    .initialization_sequence_offset = INVALID_SEQUENCE_OFFSET,
    .program_change_sequence_offset = 0x0000,
    .note_on_sequence_offset        = INVALID_SEQUENCE_OFFSET,
    .note_off_sequence_offset       = INVALID_SEQUENCE_OFFSET,

    .custom_sequences = {
    
        /* program change, p[0] = channel, p[1] = program */

        /* 0000 */ 0b00000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0xC0,
        /*      */ 0b10010100 /* all 7 bits of p[1] */,
        /*      */ /* over */ 0x00,

        /* delay */
        
        /* 0004 */ MIDI_MESSAGE_DELAY, 
        /*      */ 0x00, 
        /*      */ 0x1E, /* 30 ms */

        /* 0007 */ INVALID_STATUS_BYTE,
    
    }

};
