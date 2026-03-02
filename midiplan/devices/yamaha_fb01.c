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

#include "yamaha_fb01.h"

const midiplan_device_t yamaha_fb01 = {

    .basic_channel = 1,

    .max_melodic_notes     = 8,
    .max_percussion_notes  = 0,
    .max_melodic_programs  = 8,
    .max_notes_per_program = 8,
    .monotimbral_channels  = 1,
    .max_notes_per_channel = 1,

    .key_pressure     = 0,
    .channel_pressure = 1,
    .pitch_bend       = 1,

    .melodic_programs = {
        /* 0x00   1  GM_PROGRAM_ACOUSTIC_GRAND_PIANO  */ {  .program = YAMAHA_FB01_PROGRAM_ACOUSTIC_GRAND_PIANO,   .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x01   2  GM_PROGRAM_BRIGHT_ACOUSTIC_PIANO */ {  .program = YAMAHA_FB01_PROGRAM_BRIGHT_ACOUSTIC_PIANO,  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x02   3  GM_PROGRAM_ELECTRIC_GRAND_PIANO  */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_GRAND_PIANO,   .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x03   4  GM_PROGRAM_HONKY_TONK_PIANO      */ {  .program = YAMAHA_FB01_PROGRAM_HONKY_TONK_PIANO,       .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x04   5  GM_PROGRAM_ELECTRIC_PIANO_1      */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_PIANO_1,       .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_4DB    },
        /* 0x05   6  GM_PROGRAM_ELECTRIC_PIANO_2      */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_PIANO_2,       .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_4DB    },
        /* 0x06   7  GM_PROGRAM_HARPSICHORD           */ {  .program = YAMAHA_FB01_PROGRAM_HARPSICHORD,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x07   8  GM_PROGRAM_CLAVI                 */ {  .program = YAMAHA_FB01_PROGRAM_CLAVI,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x08   9  GM_PROGRAM_CELESTA               */ {  .program = YAMAHA_FB01_PROGRAM_CELESTA,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x09  10  GM_PROGRAM_GLOCKENSPIEL          */ {  .program = YAMAHA_FB01_PROGRAM_GLOCKENSPIEL,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x0A  11  GM_PROGRAM_MUSIC_BOX             */ {  .program = YAMAHA_FB01_PROGRAM_MUSIC_BOX,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x0B  12  GM_PROGRAM_VIBRAPHONE            */ {  .program = YAMAHA_FB01_PROGRAM_VIBRAPHONE,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x0C  13  GM_PROGRAM_MARIMBA               */ {  .program = YAMAHA_FB01_PROGRAM_MARIMBA,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x0D  14  GM_PROGRAM_XYLOPHONE             */ {  .program = YAMAHA_FB01_PROGRAM_XYLOPHONE,              .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_6DB    },
        /* 0x0E  15  GM_PROGRAM_TUBULAR_BELLS         */ {  .program = YAMAHA_FB01_PROGRAM_TUBULAR_BELLS,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x0F  16  GM_PROGRAM_DULCIMER              */ {  .program = YAMAHA_FB01_PROGRAM_DULCIMER,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x10  17  GM_PROGRAM_DRAWBAR_ORGAN         */ {  .program = YAMAHA_FB01_PROGRAM_DRAWBAR_ORGAN,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x11  18  GM_PROGRAM_PERCUSSIVE_ORGAN      */ {  .program = YAMAHA_FB01_PROGRAM_PERCUSSIVE_ORGAN,       .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x12  19  GM_PROGRAM_ROCK_ORGAN            */ {  .program = YAMAHA_FB01_PROGRAM_ROCK_ORGAN,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x13  20  GM_PROGRAM_CHURCH_ORGAN          */ {  .program = YAMAHA_FB01_PROGRAM_CHURCH_ORGAN,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x14  21  GM_PROGRAM_REED_ORGAN            */ {  .program = YAMAHA_FB01_PROGRAM_REED_ORGAN,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x15  22  GM_PROGRAM_ACCORDION             */ {  .program = YAMAHA_FB01_PROGRAM_ACCORDION,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x16  23  GM_PROGRAM_HARMONICA             */ {  .program = YAMAHA_FB01_PROGRAM_HARMONICA,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x17  24  GM_PROGRAM_TANGO_ACCORDION       */ {  .program = YAMAHA_FB01_PROGRAM_TANGO_ACCORDION,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x18  25  GM_PROGRAM_ACOUSTIC_GUITAR_NYLON */ {  .program = YAMAHA_FB01_PROGRAM_ACOUSTIC_GUITAR_NYLON,  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x19  26  GM_PROGRAM_ACOUSTIC_GUITAR_STEEL */ {  .program = YAMAHA_FB01_PROGRAM_ACOUSTIC_GUITAR_STEEL,  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x1A  27  GM_PROGRAM_ELECTRIC_GUITAR_JAZZ  */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_GUITAR_JAZZ,   .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_4DB    },
        /* 0x1B  28  GM_PROGRAM_ELECTRIC_GUITAR_CLEAN */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_GUITAR_CLEAN,  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x1C  29  GM_PROGRAM_ELECTRIC_GUITAR_MUTED */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_GUITAR_MUTED,  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x1D  30  GM_PROGRAM_OVERDRIVEN_GUITAR     */ {  .program = YAMAHA_FB01_PROGRAM_OVERDRIVEN_GUITAR,      .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x1E  31  GM_PROGRAM_DISTORTION_GUITAR     */ {  .program = YAMAHA_FB01_PROGRAM_DISTORTION_GUITAR,      .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x1F  32  GM_PROGRAM_GUITAR_HARMONICS      */ {  .program = YAMAHA_FB01_PROGRAM_GUITAR_HARMONICS,       .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x20  33  GM_PROGRAM_ACOUSTIC_BASS         */ {  .program = YAMAHA_FB01_PROGRAM_ACOUSTIC_BASS,          .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x21  34  GM_PROGRAM_ELECTRIC_BASS_FINGER  */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_BASS_FINGER,   .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x22  35  GM_PROGRAM_ELECTRIC_BASS_PICK    */ {  .program = YAMAHA_FB01_PROGRAM_ELECTRIC_BASS_PICK,     .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x23  36  GM_PROGRAM_FRETLESS_BASS         */ {  .program = YAMAHA_FB01_PROGRAM_FRETLESS_BASS,          .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x24  37  GM_PROGRAM_SLAP_BASS_1           */ {  .program = YAMAHA_FB01_PROGRAM_SLAP_BASS_1,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x25  38  GM_PROGRAM_SLAP_BASS_2           */ {  .program = YAMAHA_FB01_PROGRAM_SLAP_BASS_2,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x26  39  GM_PROGRAM_SYNTH_BASS_1          */ {  .program = YAMAHA_FB01_PROGRAM_SYNTH_BASS_1,           .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x27  40  GM_PROGRAM_SYNTH_BASS_2          */ {  .program = YAMAHA_FB01_PROGRAM_SYNTH_BASS_2,           .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x28  41  GM_PROGRAM_VIOLIN                */ {  .program = YAMAHA_FB01_PROGRAM_VIOLIN,                 .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x29  42  GM_PROGRAM_VIOLA                 */ {  .program = YAMAHA_FB01_PROGRAM_VIOLA,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x2A  43  GM_PROGRAM_CELLO                 */ {  .program = YAMAHA_FB01_PROGRAM_CELLO,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x2B  44  GM_PROGRAM_CONTRABASS            */ {  .program = YAMAHA_FB01_PROGRAM_CONTRABASS,             .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER   | VOLUME_UP_4DB    },
        /* 0x2C  45  GM_PROGRAM_TREMOLO_STRINGS       */ {  .program = YAMAHA_FB01_PROGRAM_TREMOLO_STRINGS,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x2D  46  GM_PROGRAM_PIZZICATO_STRINGS     */ {  .program = YAMAHA_FB01_PROGRAM_PIZZICATO_STRINGS,      .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x2E  47  GM_PROGRAM_ORCHESTRAL_HARP       */ {  .program = YAMAHA_FB01_PROGRAM_ORCHESTRAL_HARP,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x2F  48  GM_PROGRAM_TIMPANI               */ {  .program = YAMAHA_FB01_PROGRAM_TIMPANI,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x30  49  GM_PROGRAM_STRING_ENSEMBLE_1     */ {  .program = YAMAHA_FB01_PROGRAM_STRING_ENSEMBLE_1,      .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_2DB    },
        /* 0x31  50  GM_PROGRAM_STRING_ENSEMBLE_2     */ {  .program = YAMAHA_FB01_PROGRAM_STRING_ENSEMBLE_2,      .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x32  51  GM_PROGRAM_SYNTHSTRINGS_1        */ {  .program = YAMAHA_FB01_PROGRAM_SYNTHSTRINGS_1,         .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_2DB    },
        /* 0x33  52  GM_PROGRAM_SYNTHSTRINGS_2        */ {  .program = YAMAHA_FB01_PROGRAM_SYNTHSTRINGS_2,         .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x34  53  GM_PROGRAM_CHOIR_AAHS            */ {  .program = YAMAHA_FB01_PROGRAM_CHOIR_AAHS,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x35  54  GM_PROGRAM_VOICE_OOHS            */ {  .program = YAMAHA_FB01_PROGRAM_VOICE_OOHS,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x36  55  GM_PROGRAM_SYNTH_VOICE           */ {  .program = YAMAHA_FB01_PROGRAM_SYNTH_VOICE,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x37  56  GM_PROGRAM_ORCHESTRA_HIT         */ {  .program = YAMAHA_FB01_PROGRAM_ORCHESTRA_HIT,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x38  57  GM_PROGRAM_TRUMPET               */ {  .program = YAMAHA_FB01_PROGRAM_TRUMPET,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x39  58  GM_PROGRAM_TROMBONE              */ {  .program = YAMAHA_FB01_PROGRAM_TROMBONE,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x3A  59  GM_PROGRAM_TUBA                  */ {  .program = YAMAHA_FB01_PROGRAM_TUBA,                   .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x3B  60  GM_PROGRAM_MUTED_TRUMPET         */ {  .program = YAMAHA_FB01_PROGRAM_MUTED_TRUMPET,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x3C  61  GM_PROGRAM_FRENCH_HORN           */ {  .program = YAMAHA_FB01_PROGRAM_FRENCH_HORN,            .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x3D  62  GM_PROGRAM_BRASS_SECTION         */ {  .program = YAMAHA_FB01_PROGRAM_BRASS_SECTION,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x3E  63  GM_PROGRAM_SYNTHBRASS_1          */ {  .program = YAMAHA_FB01_PROGRAM_SYNTHBRASS_1,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x3F  64  GM_PROGRAM_SYNTHBRASS_2          */ {  .program = YAMAHA_FB01_PROGRAM_SYNTHBRASS_2,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x40  65  GM_PROGRAM_SOPRANO_SAX           */ {  .program = YAMAHA_FB01_PROGRAM_SOPRANO_SAX,            .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x41  66  GM_PROGRAM_ALTO_SAX              */ {  .program = YAMAHA_FB01_PROGRAM_ALTO_SAX,               .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x42  67  GM_PROGRAM_TENOR_SAX             */ {  .program = YAMAHA_FB01_PROGRAM_TENOR_SAX,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x43  68  GM_PROGRAM_BARITONE_SAX          */ {  .program = YAMAHA_FB01_PROGRAM_BARITONE_SAX,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x44  69  GM_PROGRAM_OBOE                  */ {  .program = YAMAHA_FB01_PROGRAM_OBOE,                   .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x45  70  GM_PROGRAM_ENGLISH_HORN          */ {  .program = YAMAHA_FB01_PROGRAM_HORN,                   .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x46  71  GM_PROGRAM_BASSOON               */ {  .program = YAMAHA_FB01_PROGRAM_BASSOON,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x47  72  GM_PROGRAM_CLARINET              */ {  .program = YAMAHA_FB01_PROGRAM_CLARINET,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x48  73  GM_PROGRAM_PICCOLO               */ {  .program = YAMAHA_FB01_PROGRAM_PICCOLO,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x49  74  GM_PROGRAM_FLUTE                 */ {  .program = YAMAHA_FB01_PROGRAM_FLUTE,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4A  75  GM_PROGRAM_RECORDER              */ {  .program = YAMAHA_FB01_PROGRAM_RECORDER,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4B  76  GM_PROGRAM_PAN_FLUTE             */ {  .program = YAMAHA_FB01_PROGRAM_PAN_FLUTE,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4C  77  GM_PROGRAM_BLOWN_BOTTLE          */ {  .program = YAMAHA_FB01_PROGRAM_BLOWN_BOTTLE,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4D  78  GM_PROGRAM_SHAKUHACHI            */ {  .program = YAMAHA_FB01_PROGRAM_SHAKUHACHI,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4E  79  GM_PROGRAM_WHISTLE               */ {  .program = YAMAHA_FB01_PROGRAM_WHISTLE,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x4F  80  GM_PROGRAM_OCARINA               */ {  .program = YAMAHA_FB01_PROGRAM_OCARINA,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x50  81  GM_PROGRAM_LEAD_1_SQUARE         */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_1_SQUARE,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x51  82  GM_PROGRAM_LEAD_2_SAWTOOTH       */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_2_SAWTOOTH,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x52  83  GM_PROGRAM_LEAD_3_CALLIOPE       */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_3_CALLIOPE,        .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_UP_4DB    },
        /* 0x53  84  GM_PROGRAM_LEAD_4_CHIFF          */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_4_CHIFF,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x54  85  GM_PROGRAM_LEAD_5_CHARANG        */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_5_CHARANG,         .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x55  86  GM_PROGRAM_LEAD_6_VOICE          */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_6_VOICE,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x56  87  GM_PROGRAM_LEAD_7_FIFTHS         */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_7_FIFTHS,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x57  88  GM_PROGRAM_LEAD_8_BASS_LEAD      */ {  .program = YAMAHA_FB01_PROGRAM_LEAD_8_BASS_LEAD,       .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x58  89  GM_PROGRAM_PAD_1_NEW_AGE         */ {  .program = YAMAHA_FB01_PROGRAM_PAD_1_NEW_AGE,          .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x59  90  GM_PROGRAM_PAD_2_WARM            */ {  .program = YAMAHA_FB01_PROGRAM_PAD_2_WARM,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x5A  91  GM_PROGRAM_PAD_3_POLYSYNTH       */ {  .program = YAMAHA_FB01_PROGRAM_PAD_3_POLYSYNTH,        .flags = YAMAHA_FB01_RANGE_DEFAULT         | VOLUME_DOWN_2DB  },
        /* 0x5B  92  GM_PROGRAM_PAD_4_CHOIR           */ {  .program = YAMAHA_FB01_PROGRAM_PAD_4_CHOIR,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x5C  93  GM_PROGRAM_PAD_5_BOWED           */ {  .program = YAMAHA_FB01_PROGRAM_PAD_5_BOWED,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x5D  94  GM_PROGRAM_PAD_6_METALLIC        */ {  .program = YAMAHA_FB01_PROGRAM_PAD_6_METALLIC,         .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x5E  95  GM_PROGRAM_PAD_7_HALO            */ {  .program = YAMAHA_FB01_PROGRAM_PAD_7_HALO,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x5F  96  GM_PROGRAM_PAD_8_SWEEP           */ {  .program = YAMAHA_FB01_PROGRAM_PAD_8_SWEEP,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x60  97  GM_PROGRAM_FX_1_RAIN             */ {  .program = YAMAHA_FB01_PROGRAM_FX_1_RAIN,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x61  98  GM_PROGRAM_FX_2_SOUNDTRACK       */ {  .program = YAMAHA_FB01_PROGRAM_FX_2_SOUNDTRACK,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x62  99  GM_PROGRAM_FX_3_CRYSTAL          */ {  .program = YAMAHA_FB01_PROGRAM_FX_3_CRYSTAL,           .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x63 100  GM_PROGRAM_FX_4_ATMOSPHERE       */ {  .program = YAMAHA_FB01_PROGRAM_FX_4_ATMOSPHERE,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x64 101  GM_PROGRAM_FX_5_BRIGHTNESS       */ {  .program = YAMAHA_FB01_PROGRAM_FX_5_BRIGHTNESS,        .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x65 102  GM_PROGRAM_FX_6_GOBLINS          */ {  .program = YAMAHA_FB01_PROGRAM_FX_6_GOBLINS,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x66 103  GM_PROGRAM_FX_7_ECHOES           */ {  .program = YAMAHA_FB01_PROGRAM_FX_7_ECHOES,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x67 104  GM_PROGRAM_FX_8_SCI_FI           */ {  .program = YAMAHA_FB01_PROGRAM_FX_8_SCI_FI,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x68 105  GM_PROGRAM_SITAR                 */ {  .program = YAMAHA_FB01_PROGRAM_SITAR,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x69 106  GM_PROGRAM_BANJO                 */ {  .program = YAMAHA_FB01_PROGRAM_BANJO,                  .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6A 107  GM_PROGRAM_SHAMISEN              */ {  .program = YAMAHA_FB01_PROGRAM_SHAMISEN,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6B 108  GM_PROGRAM_KOTO                  */ {  .program = YAMAHA_FB01_PROGRAM_KOTO,                   .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6C 109  GM_PROGRAM_KALIMBA               */ {  .program = YAMAHA_FB01_PROGRAM_KALIMBA,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6D 110  GM_PROGRAM_BAG_PIPE              */ {  .program = YAMAHA_FB01_PROGRAM_BAG_PIPE,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6E 111  GM_PROGRAM_FIDDLE                */ {  .program = YAMAHA_FB01_PROGRAM_FIDDLE,                 .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x6F 112  GM_PROGRAM_SHANAI                */ {  .program = YAMAHA_FB01_PROGRAM_SHANAI,                 .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x70 113  GM_PROGRAM_TINKLE_BELL           */ {  .program = YAMAHA_FB01_PROGRAM_TINKLE_BELL,            .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x71 114  GM_PROGRAM_AGOGO                 */ {  .program = YAMAHA_FB01_PROGRAM_AGOGO,                  .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x72 115  GM_PROGRAM_STEEL_DRUMS           */ {  .program = YAMAHA_FB01_PROGRAM_STEEL_DRUMS,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x73 116  GM_PROGRAM_WOODBLOCK             */ {  .program = YAMAHA_FB01_PROGRAM_WOODBLOCK,              .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x74 117  GM_PROGRAM_TAIKO_DRUM            */ {  .program = YAMAHA_FB01_PROGRAM_TAIKO_DRUM,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x75 118  GM_PROGRAM_MELODIC_TOM           */ {  .program = YAMAHA_FB01_PROGRAM_MELODIC_TOM,            .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x76 119  GM_PROGRAM_SYNTH_DRUM            */ {  .program = YAMAHA_FB01_PROGRAM_SYNTH_DRUM,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x77 120  GM_PROGRAM_REVERSE_CYMBAL        */ {  .program = YAMAHA_FB01_PROGRAM_REVERSE_CYMBAL,         .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x78 121  GM_PROGRAM_GUITAR_FRET_NOISE     */ {  .program = YAMAHA_FB01_PROGRAM_GUITAR_FRET_NOISE,      .flags = YAMAHA_FB01_RANGE_OCTAVE_LOWER    | VOLUME_DOWN_4DB  },
        /* 0x79 122  GM_PROGRAM_BREATH_NOISE          */ {  .program = YAMAHA_FB01_PROGRAM_BREATH_NOISE,           .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x7A 123  GM_PROGRAM_SEASHORE              */ {  .program = YAMAHA_FB01_PROGRAM_SEASHORE,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x7B 124  GM_PROGRAM_BIRD_TWEET            */ {  .program = YAMAHA_FB01_PROGRAM_BIRD_TWEET,             .flags = YAMAHA_FB01_RANGE_OCTAVE_HIGHER                      },
        /* 0x7C 125  GM_PROGRAM_TELEPHONE_RING        */ {  .program = YAMAHA_FB01_PROGRAM_TELEPHONE_RING,         .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x7D 126  GM_PROGRAM_HELICOPTER            */ {  .program = YAMAHA_FB01_PROGRAM_HELICOPTER,             .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x7E 127  GM_PROGRAM_APPLAUSE              */ {  .program = YAMAHA_FB01_PROGRAM_APPLAUSE,               .flags = YAMAHA_FB01_RANGE_DEFAULT                            },
        /* 0x7F 128  GM_PROGRAM_GUNSHOT               */ {  .program = YAMAHA_FB01_PROGRAM_GUNSHOT,                .flags = YAMAHA_FB01_RANGE_DEFAULT                            }
    },

    .melodic_note_ranges = {
        /* 0x00 YAMAHA_FB01_RANGE_INVALID       */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x01 YAMAHA_FB01_RANGE_OCTAVE_HIGHER */ {  .lowest_note = YAMAHA_FB01_LOWEST_NOTE,  .middle_c = YAMAHA_FB01_MIDDLE_C + 12,  .highest_note = YAMAHA_FB01_HIGHEST_NOTE  },
        /* 0x02 YAMAHA_FB01_RANGE_OCTAVE_LOWER  */ {  .lowest_note = YAMAHA_FB01_LOWEST_NOTE,  .middle_c = YAMAHA_FB01_MIDDLE_C - 12,  .highest_note = YAMAHA_FB01_HIGHEST_NOTE  },
        /* 0x03                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x04                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x05                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x06                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x07                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x08                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x09                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0A                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0B                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0C                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0D                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0E                                 */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x0F YAMAHA_FB01_RANGE_DEFAULT       */ {  .lowest_note = YAMAHA_FB01_LOWEST_NOTE,  .middle_c = YAMAHA_FB01_MIDDLE_C,       .highest_note = YAMAHA_FB01_HIGHEST_NOTE  }
    },

    .percussion_notes = {
        /* 0x00   1  GM_PERCUSSION_UNDEFINED_00       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x01   2  GM_PERCUSSION_UNDEFINED_01       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x02   3  GM_PERCUSSION_UNDEFINED_02       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x03   4  GM_PERCUSSION_UNDEFINED_03       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x04   5  GM_PERCUSSION_UNDEFINED_04       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x05   6  GM_PERCUSSION_UNDEFINED_05       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x06   7  GM_PERCUSSION_UNDEFINED_06       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x07   8  GM_PERCUSSION_UNDEFINED_07       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x08   9  GM_PERCUSSION_UNDEFINED_08       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x09  10  GM_PERCUSSION_UNDEFINED_09       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0A  11  GM_PERCUSSION_UNDEFINED_0A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0B  12  GM_PERCUSSION_UNDEFINED_0B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0C  13  GM_PERCUSSION_UNDEFINED_0C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0D  14  GM_PERCUSSION_UNDEFINED_0D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0E  15  GM_PERCUSSION_UNDEFINED_0E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0F  16  GM_PERCUSSION_UNDEFINED_0F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x10  17  GM_PERCUSSION_UNDEFINED_10       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x11  18  GM_PERCUSSION_UNDEFINED_11       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x12  19  GM_PERCUSSION_UNDEFINED_12       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x13  20  GM_PERCUSSION_UNDEFINED_13       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x14  21  GM_PERCUSSION_UNDEFINED_14       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x15  22  GM_PERCUSSION_UNDEFINED_15       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x16  23  GM_PERCUSSION_UNDEFINED_16       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x17  24  GM_PERCUSSION_UNDEFINED_17       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x18  25  GM_PERCUSSION_UNDEFINED_18       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x19  26  GM_PERCUSSION_UNDEFINED_19       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1A  27  GM_PERCUSSION_UNDEFINED_1A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1B  28  GM_PERCUSSION_UNDEFINED_1B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1C  29  GM_PERCUSSION_UNDEFINED_1C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1D  30  GM_PERCUSSION_UNDEFINED_1D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1E  31  GM_PERCUSSION_UNDEFINED_1E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1F  32  GM_PERCUSSION_UNDEFINED_1F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x20  33  GM_PERCUSSION_UNDEFINED_20       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x21  34  GM_PERCUSSION_UNDEFINED_21       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x22  35  GM_PERCUSSION_UNDEFINED_22       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x23  36  GM_PERCUSSION_ACOUSTIC_BASS_DRUM */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x24  37  GM_PERCUSSION_BASS_DRUM_1        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x25  38  GM_PERCUSSION_SIDE_STICK         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x26  39  GM_PERCUSSION_ACOUSTIC_SNARE     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x27  40  GM_PERCUSSION_HAND_CLAP          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x28  41  GM_PERCUSSION_ELECTRIC_SNARE     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x29  42  GM_PERCUSSION_LOW_FLOOR_TOM      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2A  43  GM_PERCUSSION_CLOSED_HI_HAT      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2B  44  GM_PERCUSSION_HIGH_FLOOR_TOM     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2C  45  GM_PERCUSSION_PEDAL_HI_HAT       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2D  46  GM_PERCUSSION_LOW_TOM            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2E  47  GM_PERCUSSION_OPEN_HI_HAT        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2F  48  GM_PERCUSSION_LOW_MID_TOM        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x30  49  GM_PERCUSSION_HI_MID_TOM         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x31  50  GM_PERCUSSION_CRASH_CYMBAL_1     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x32  51  GM_PERCUSSION_HIGH_TOM           */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x33  52  GM_PERCUSSION_RIDE_CYMBAL_1      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x34  53  GM_PERCUSSION_CHINESE_CYMBAL     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x35  54  GM_PERCUSSION_RIDE_BELL          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x36  55  GM_PERCUSSION_TAMBOURINE         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x37  56  GM_PERCUSSION_SPLASH_CYMBAL      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x38  57  GM_PERCUSSION_COWBELL            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x39  58  GM_PERCUSSION_CRASH_CYMBAL_2     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3A  59  GM_PERCUSSION_VIBRASLAP          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3B  60  GM_PERCUSSION_RIDE_CYMBAL_2      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3C  61  GM_PERCUSSION_HI_BONGO           */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3D  62  GM_PERCUSSION_LOW_BONGO          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3E  63  GM_PERCUSSION_MUTE_HI_CONGA      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3F  64  GM_PERCUSSION_OPEN_HI_CONGA      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x40  65  GM_PERCUSSION_LOW_CONGA          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x41  66  GM_PERCUSSION_HIGH_TIMBALE       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x42  67  GM_PERCUSSION_LOW_TIMBALE        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x43  68  GM_PERCUSSION_HIGH_AGOGO         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x44  69  GM_PERCUSSION_LOW_AGOGO          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x45  70  GM_PERCUSSION_CABASA             */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x46  71  GM_PERCUSSION_MARACAS            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x47  72  GM_PERCUSSION_SHORT_WHISTLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x48  73  GM_PERCUSSION_LONG_WHISTLE       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x49  74  GM_PERCUSSION_SHORT_GUIRO        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4A  75  GM_PERCUSSION_LONG_GUIRO         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4B  76  GM_PERCUSSION_CLAVES             */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4C  77  GM_PERCUSSION_HI_WOOD_BLOCK      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4D  78  GM_PERCUSSION_LOW_WOOD_BLOCK     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4E  79  GM_PERCUSSION_MUTE_CUICA         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4F  80  GM_PERCUSSION_OPEN_CUICA         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x50  81  GM_PERCUSSION_MUTE_TRIANGLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x51  82  GM_PERCUSSION_OPEN_TRIANGLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x52  83  GM_PERCUSSION_UNDEFINED_52       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x53  84  GM_PERCUSSION_UNDEFINED_53       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x54  85  GM_PERCUSSION_UNDEFINED_54       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x55  86  GM_PERCUSSION_UNDEFINED_55       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x56  87  GM_PERCUSSION_UNDEFINED_56       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x57  88  GM_PERCUSSION_UNDEFINED_57       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x58  89  GM_PERCUSSION_UNDEFINED_58       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x59  90  GM_PERCUSSION_UNDEFINED_59       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5A  91  GM_PERCUSSION_UNDEFINED_5A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5B  92  GM_PERCUSSION_UNDEFINED_5B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5C  93  GM_PERCUSSION_UNDEFINED_5C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5D  94  GM_PERCUSSION_UNDEFINED_5D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5E  95  GM_PERCUSSION_UNDEFINED_5E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5F  96  GM_PERCUSSION_UNDEFINED_5F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x60  97  GM_PERCUSSION_UNDEFINED_60       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x61  98  GM_PERCUSSION_UNDEFINED_61       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x62  99  GM_PERCUSSION_UNDEFINED_62       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x63 100  GM_PERCUSSION_UNDEFINED_63       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x64 101  GM_PERCUSSION_UNDEFINED_64       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x65 102  GM_PERCUSSION_UNDEFINED_65       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x66 103  GM_PERCUSSION_UNDEFINED_66       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x67 104  GM_PERCUSSION_UNDEFINED_67       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x68 105  GM_PERCUSSION_UNDEFINED_68       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x69 106  GM_PERCUSSION_UNDEFINED_69       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6A 107  GM_PERCUSSION_UNDEFINED_6A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6B 108  GM_PERCUSSION_UNDEFINED_6B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6C 109  GM_PERCUSSION_UNDEFINED_6C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6D 110  GM_PERCUSSION_UNDEFINED_6D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6E 111  GM_PERCUSSION_UNDEFINED_6E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6F 112  GM_PERCUSSION_UNDEFINED_6F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x70 113  GM_PERCUSSION_UNDEFINED_70       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x71 114  GM_PERCUSSION_UNDEFINED_71       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x72 115  GM_PERCUSSION_UNDEFINED_72       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x73 116  GM_PERCUSSION_UNDEFINED_73       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x74 117  GM_PERCUSSION_UNDEFINED_74       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x75 118  GM_PERCUSSION_UNDEFINED_75       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x76 119  GM_PERCUSSION_UNDEFINED_76       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x77 120  GM_PERCUSSION_UNDEFINED_77       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x78 121  GM_PERCUSSION_UNDEFINED_78       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x79 122  GM_PERCUSSION_UNDEFINED_79       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7A 123  GM_PERCUSSION_UNDEFINED_7A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7B 124  GM_PERCUSSION_UNDEFINED_7B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7C 125  GM_PERCUSSION_UNDEFINED_7C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7D 126  GM_PERCUSSION_UNDEFINED_7D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7E 127  GM_PERCUSSION_UNDEFINED_7E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7F 128  GM_PERCUSSION_UNDEFINED_7F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  }
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
        0b11111111111111111111111111111111, // 111/6Fh -  96/60h
        0b11111111111111111111111111111111  // 127/7Fh - 112/70h
    },

    .melodic_channels_bitmaps = {
        0b0000000000000000, // 00
        0b0000000000000000, // 01
        0b0000000000000000, // 10
        0b0000000011111111  // 11
    },

    .percussion_channels_bitmap = 0b0000000000000000,

    .controllers_bitmap = {

      //(1 << (MIDI_CONTROL_BANK_SELECT                  & 0x1F)) |  /* 0x00   0 */
        (1 << (MIDI_CONTROL_MODULATION_WHEEL_OR_LEVER    & 0x1F)) |  /* 0x01   1 */
        (1 << (MIDI_CONTROL_BREATH_CONTROLLER            & 0x1F)) |  /* 0x02   2 */
      //(1 << (MIDI_CONTROL_UNDEFINED_03                 & 0x1F)) |  /* 0x03   3 */
        (1 << (MIDI_CONTROL_FOOT_CONTROLLER              & 0x1F)) |  /* 0x04   4 */
        (1 << (MIDI_CONTROL_PORTAMENTO_TIME              & 0x1F)) |  /* 0x05   5 */
      //(1 << (MIDI_CONTROL_DATA_ENTRY_MSB               & 0x1F)) |  /* 0x06   6 */
        (1 << (MIDI_CONTROL_CHANNEL_VOLUME               & 0x1F)) |  /* 0x07   7 */
      //(1 << (MIDI_CONTROL_BALANCE                      & 0x1F)) |  /* 0x08   8 */
      //(1 << (MIDI_CONTROL_UNDEFINED_09                 & 0x1F)) |  /* 0x09   9 */
        (1 << (MIDI_CONTROL_PAN                          & 0x1F)) |  /* 0x0A  10 */
      //(1 << (MIDI_CONTROL_EXPRESSION_CONTROLLER        & 0x1F)) |  /* 0x0B  11 */
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
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_02               & 0x1F)) |  /* 0x22  34 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_03               & 0x1F)) |  /* 0x23  35 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_04               & 0x1F)) |  /* 0x24  36 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_05               & 0x1F)) |  /* 0x25  37 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_06               & 0x1F)) |  /* 0x26  38 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_07               & 0x1F)) |  /* 0x27  39 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_08               & 0x1F)) |  /* 0x28  40 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_09               & 0x1F)) |  /* 0x29  41 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_0A               & 0x1F)) |  /* 0x2A  42 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0B               & 0x1F)) |  /* 0x2B  43 */
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
      //(1 << (MIDI_CONTROL_SOFT_PEDAL                   & 0x1F)) |  /* 0x43  67 */
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

      //(1 << (MIDI_CONTROL_DATA_INCREMENT               & 0x1F)) |  /* 0x60  96 */
      //(1 << (MIDI_CONTROL_DATA_DECREMENT               & 0x1F)) |  /* 0x61  97 */
      //(1 << (MIDI_CONTROL_NON_REGISTERED_PARAMETER_LSB & 0x1F)) |  /* 0x62  98 */
      //(1 << (MIDI_CONTROL_NON_REGISTERED_PARAMETER_MSB & 0x1F)) |  /* 0x63  99 */
      //(1 << (MIDI_CONTROL_REGISTERED_PARAMETER_LSB     & 0x1F)) |  /* 0x64 100 */
      //(1 << (MIDI_CONTROL_REGISTERED_PARAMETER_MSB     & 0x1F)) |  /* 0x65 101 */
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

    .initialization_sequence_offset = 0x0000,
    .program_change_sequence_offset = 0x00DC,
    .note_on_sequence_offset        = INVALID_SEQUENCE_OFFSET,
    .note_off_sequence_offset       = INVALID_SEQUENCE_OFFSET,

    .custom_sequences = {

        /* initialization, p[0] = system channel */

        /* switch instruments 1-8 to MIDI channels 1-8 */

        /* 0000 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x00, /* instrument: 1 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x00, /* midi channel 1 */
        /*      */ 0xF7,

        /* 0009 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x01, /* instrument: 2 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x01, /* midi channel 2 */
        /*      */ 0xF7,

        /* 0012 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x02, /* instrument: 3 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x02, /* midi channel 3 */
        /*      */ 0xF7,

        /* 001B */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x03, /* instrument: 4 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x03, /* midi channel 4 */
        /*      */ 0xF7,

        /* 0024 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x04, /* instrument: 5 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x04, /* midi channel 5 */
        /*      */ 0xF7,

        /* 002D */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x05, /* instrument: 6 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x05, /* midi channel 6 */
        /*      */ 0xF7,

        /* 0036 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x06, /* instrument: 7 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x06, /* midi channel 7 */
        /*      */ 0xF7,

        /* 003F */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x07, /* instrument: 8 */
        /*      */ 0x01, /* parameter: midi channel */
        /*      */ 0x07, /* midi channel 8 */
        /*      */ 0xF7,

        /* set number of notes for instruments 1-8 to 0 (because setting it directly to 1 may not always be possible) */

        /* 0048 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x00, /* instrument: 1 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 0051 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x01, /* instrument: 2 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 005A */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x02, /* instrument: 3 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 0063 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x03, /* instrument: 4 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 006C */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x04, /* instrument: 5 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 0075 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x05, /* instrument: 6 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 007E */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x06, /* instrument: 7 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* 0087 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x07, /* instrument: 8 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x00, /* value: 0 */
        /*      */ 0xF7,

        /* set number of notes for instruments 1-8 to 1 (now it is possible) */

        /* 0090 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x00, /* instrument: 1 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 0099 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x01, /* instrument: 2 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00A2 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x02, /* instrument: 3 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00AB */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x03, /* instrument: 4 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00B4 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x04, /* instrument: 5 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00BD */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x05, /* instrument: 6 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00C6 */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x06, /* instrument: 7 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00CF */ 0xF0, 0x43, 0x75, /* change parameter by instrument number */
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x00,
        /*      */ 0x18 | 0x07, /* instrument: 8 */
        /*      */ 0x00, /* parameter: # of notes */
        /*      */ 0x01, /* value: 1 */
        /*      */ 0xF7,

        /* 00D8 */ MIDI_MESSAGE_DELAY, 
        /*      */ 0x00, 
        /*      */ 0x64, /* 100 ms */

        /* 00DB */ INVALID_STATUS_BYTE,

        /* program change, p[0] = channel, p[1] = program */

        /* bank switch */

        /* 00DC */ 0xF0,
        /*      */ 0x43,
        /*      */ 0b10000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0x10,
        /*      */ 0x15,
        /*      */ 0x04,
        /*      */ 0b10011000 /* 4-bit lookup in the following 64-byte table using p[1] as the index */,
                    /*          program to device bank mapping                                       */
                    /*   01    23    45    67    89    AB    CD    EF                                */
        /*      0_ */  0x33, 0x23, 0x33, 0x23, 0x32, 0x52, 0x22, 0x56,
        /*      1_ */  0x66, 0x66, 0x63, 0x24, 0x66, 0x26, 0x66, 0x26,
        /*      2_ */  0x22, 0x25, 0x55, 0x55, 0x44, 0x45, 0x54, 0x22,
        /*      3_ */  0x44, 0x44, 0x26, 0x65, 0x24, 0x24, 0x24, 0x44,
        /*      4_ */  0x44, 0x44, 0x22, 0x42, 0x22, 0x44, 0x54, 0x26,
        /*      5_ */  0x56, 0x35, 0x52, 0x55, 0x56, 0x55, 0x42, 0x45,
        /*      6_ */  0x63, 0x66, 0x66, 0x26, 0x66, 0x62, 0x66, 0x44,
        /*      7_ */  0x52, 0x55, 0x52, 0x56, 0x46, 0x62, 0x66, 0x66,
        /*      */ /* over */ 0x00,
        /*      */ 0xF7,

        /* program change */

        /* 0125 */ 0b00000000 /* low 4 bits of p[0] */,
        /*      */ /* over */ 0xC0,
        /*      */ 0b10011100 /* 8-bit lookup in the following 128-byte table using p[1] as the index                   */,
                    /*                             program to bank-specific program mapping                             */
                    /*   _0    _1    _2    _3    _4    _5    _6    _7    _8    _9    _A    _B    _C    _D    _E    _F   */
        /*      0_ */  0x07, 0x00, 0x07, 0x0D, 0x14, 0x15, 0x19, 0x21, 0x2E, 0x13, 0x21, 0x14, 0x28, 0x15, 0x24, 0x1A,
        /*      1_ */  0x07, 0x03, 0x05, 0x09, 0x06, 0x2F, 0x1D, 0x2C, 0x0F, 0x10, 0x08, 0x12, 0x11, 0x13, 0x25, 0x18,
        /*      2_ */  0x0A, 0x09, 0x29, 0x14, 0x12, 0x11, 0x17, 0x1D, 0x13, 0x12, 0x18, 0x13, 0x0D, 0x20, 0x1B, 0x1F,
        /*      3_ */  0x16, 0x14, 0x17, 0x15, 0x27, 0x21, 0x20, 0x2B, 0x02, 0x04, 0x21, 0x03, 0x21, 0x0A, 0x07, 0x0B,
        /*      4_ */  0x2E, 0x2F, 0x2E, 0x2F, 0x11, 0x01, 0x28, 0x12, 0x10, 0x0F, 0x25, 0x24, 0x0A, 0x22, 0x22, 0x1E,
        /*      5_ */  0x05, 0x14, 0x2D, 0x07, 0x1C, 0x1C, 0x09, 0x08, 0x0C, 0x1F, 0x04, 0x06, 0x19, 0x24, 0x1D, 0x00,
        /*      6_ */  0x24, 0x27, 0x29, 0x0D, 0x1D, 0x26, 0x2D, 0x28, 0x1C, 0x16, 0x1B, 0x16, 0x17, 0x0B, 0x13, 0x27,
        /*      7_ */  0x25, 0x1E, 0x28, 0x2D, 0x2A, 0x2C, 0x29, 0x24, 0x10, 0x27, 0x27, 0x23, 0x2D, 0x2E, 0x27, 0x2C,
        /*      */ /* over */ 0x00,

        /* delay */
        
        /* 016A */ MIDI_MESSAGE_DELAY, 
        /*      */ 0x00, 
        /*      */ 0x14, /* 20 ms */

        /* 016D */ INVALID_STATUS_BYTE,

    }

};
