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

#include "roland_gr09.h"
#include "gm_device.h"

const midiplan_device_t roland_gr09 = {

    .basic_channel = MIDI_CHANNEL_1,

    .max_melodic_notes     = 6,
    .max_percussion_notes  = 0,
    .max_melodic_programs  = 1,
    .max_notes_per_program = 6,
    .monotimbral_channels  = 1,
    .max_notes_per_channel = 6,

    .key_pressure     = 0,
    .channel_pressure = 0,
    .pitch_bend       = 1,

    .melodic_programs = {
        /* 0x00   0  GM_PROGRAM_ACOUSTIC_GRAND_PIANO  */ {  .program = GM_PROGRAM_ACOUSTIC_GRAND_PIANO,   .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x01   1  GM_PROGRAM_BRIGHT_ACOUSTIC_PIANO */ {  .program = GM_PROGRAM_BRIGHT_ACOUSTIC_PIANO,  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x02   2  GM_PROGRAM_ELECTRIC_GRAND_PIANO  */ {  .program = GM_PROGRAM_ELECTRIC_GRAND_PIANO,   .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x03   3  GM_PROGRAM_HONKY_TONK_PIANO      */ {  .program = GM_PROGRAM_HONKY_TONK_PIANO,       .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x04   4  GM_PROGRAM_ELECTRIC_PIANO_1      */ {  .program = GM_PROGRAM_ELECTRIC_PIANO_1,       .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x05   5  GM_PROGRAM_ELECTRIC_PIANO_2      */ {  .program = GM_PROGRAM_ELECTRIC_PIANO_2,       .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x06   6  GM_PROGRAM_HARPSICHORD           */ {  .program = GM_PROGRAM_HARPSICHORD,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x07   7  GM_PROGRAM_CLAVI                 */ {  .program = GM_PROGRAM_CLAVI,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x08   8  GM_PROGRAM_CELESTA               */ {  .program = GM_PROGRAM_CELESTA,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x09   9  GM_PROGRAM_GLOCKENSPIEL          */ {  .program = GM_PROGRAM_GLOCKENSPIEL,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0A  10  GM_PROGRAM_MUSIC_BOX             */ {  .program = GM_PROGRAM_MUSIC_BOX,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0B  11  GM_PROGRAM_VIBRAPHONE            */ {  .program = GM_PROGRAM_VIBRAPHONE,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0C  12  GM_PROGRAM_MARIMBA               */ {  .program = GM_PROGRAM_MARIMBA,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0D  13  GM_PROGRAM_XYLOPHONE             */ {  .program = GM_PROGRAM_XYLOPHONE,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0E  14  GM_PROGRAM_TUBULAR_BELLS         */ {  .program = GM_PROGRAM_TUBULAR_BELLS,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x0F  15  GM_PROGRAM_DULCIMER              */ {  .program = GM_PROGRAM_DULCIMER,               .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x10  16  GM_PROGRAM_DRAWBAR_ORGAN         */ {  .program = GM_PROGRAM_DRAWBAR_ORGAN,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x11  17  GM_PROGRAM_PERCUSSIVE_ORGAN      */ {  .program = GM_PROGRAM_PERCUSSIVE_ORGAN,       .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x12  18  GM_PROGRAM_ROCK_ORGAN            */ {  .program = GM_PROGRAM_ROCK_ORGAN,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x13  19  GM_PROGRAM_CHURCH_ORGAN          */ {  .program = GM_PROGRAM_CHURCH_ORGAN,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x14  20  GM_PROGRAM_REED_ORGAN            */ {  .program = GM_PROGRAM_REED_ORGAN,             .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER | VOLUME_UP_2DB    },
        /* 0x15  21  GM_PROGRAM_ACCORDION             */ {  .program = GM_PROGRAM_ACCORDION,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x16  22  GM_PROGRAM_HARMONICA             */ {  .program = GM_PROGRAM_HARMONICA,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x17  23  GM_PROGRAM_TANGO_ACCORDION       */ {  .program = GM_PROGRAM_TANGO_ACCORDION,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x18  24  GM_PROGRAM_ACOUSTIC_GUITAR_NYLON */ {  .program = GM_PROGRAM_ACOUSTIC_GUITAR_NYLON,  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x19  25  GM_PROGRAM_ACOUSTIC_GUITAR_STEEL */ {  .program = GM_PROGRAM_ACOUSTIC_GUITAR_STEEL,  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x1A  26  GM_PROGRAM_ELECTRIC_GUITAR_JAZZ  */ {  .program = GM_PROGRAM_ELECTRIC_GUITAR_JAZZ,   .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x1B  27  GM_PROGRAM_ELECTRIC_GUITAR_CLEAN */ {  .program = GM_PROGRAM_ELECTRIC_GUITAR_CLEAN,  .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x1C  28  GM_PROGRAM_ELECTRIC_GUITAR_MUTED */ {  .program = GM_PROGRAM_ELECTRIC_GUITAR_MUTED,  .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x1D  29  GM_PROGRAM_OVERDRIVEN_GUITAR     */ {  .program = GM_PROGRAM_OVERDRIVEN_GUITAR,      .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x1E  30  GM_PROGRAM_DISTORTION_GUITAR     */ {  .program = GM_PROGRAM_DISTORTION_GUITAR,      .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x1F  31  GM_PROGRAM_GUITAR_HARMONICS      */ {  .program = GM_PROGRAM_GUITAR_HARMONICS,       .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x20  32  GM_PROGRAM_ACOUSTIC_BASS         */ {  .program = GM_PROGRAM_ACOUSTIC_BASS,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x21  33  GM_PROGRAM_ELECTRIC_BASS_FINGER  */ {  .program = GM_PROGRAM_ELECTRIC_BASS_FINGER,   .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x22  34  GM_PROGRAM_ELECTRIC_BASS_PICK    */ {  .program = GM_PROGRAM_ELECTRIC_BASS_PICK,     .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x23  35  GM_PROGRAM_FRETLESS_BASS         */ {  .program = GM_PROGRAM_FRETLESS_BASS,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x24  36  GM_PROGRAM_SLAP_BASS_1           */ {  .program = GM_PROGRAM_SLAP_BASS_1,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x25  37  GM_PROGRAM_SLAP_BASS_2           */ {  .program = GM_PROGRAM_SLAP_BASS_2,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x26  38  GM_PROGRAM_SYNTH_BASS_1          */ {  .program = GM_PROGRAM_SYNTH_BASS_1,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x27  39  GM_PROGRAM_SYNTH_BASS_2          */ {  .program = GM_PROGRAM_SYNTH_BASS_2,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x28  40  GM_PROGRAM_VIOLIN                */ {  .program = GM_PROGRAM_VIOLIN,                 .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x29  41  GM_PROGRAM_VIOLA                 */ {  .program = GM_PROGRAM_VIOLA,                  .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x2A  42  GM_PROGRAM_CELLO                 */ {  .program = GM_PROGRAM_CELLO,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x2B  43  GM_PROGRAM_CONTRABASS            */ {  .program = GM_PROGRAM_CONTRABASS,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x2C  44  GM_PROGRAM_TREMOLO_STRINGS       */ {  .program = GM_PROGRAM_TREMOLO_STRINGS,        .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x2D  45  GM_PROGRAM_PIZZICATO_STRINGS     */ {  .program = GM_PROGRAM_PIZZICATO_STRINGS,      .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x2E  46  GM_PROGRAM_ORCHESTRAL_HARP       */ {  .program = GM_PROGRAM_ORCHESTRAL_HARP,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x2F  47  GM_PROGRAM_TIMPANI               */ {  .program = GM_PROGRAM_TIMPANI,                .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x30  48  GM_PROGRAM_STRING_ENSEMBLE_1     */ {  .program = GM_PROGRAM_STRING_ENSEMBLE_1,      .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x31  49  GM_PROGRAM_STRING_ENSEMBLE_2     */ {  .program = GM_PROGRAM_STRING_ENSEMBLE_2,      .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x32  50  GM_PROGRAM_SYNTHSTRINGS_1        */ {  .program = GM_PROGRAM_SYNTHSTRINGS_1,         .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x33  51  GM_PROGRAM_SYNTHSTRINGS_2        */ {  .program = GM_PROGRAM_SYNTHSTRINGS_2,         .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x34  52  GM_PROGRAM_CHOIR_AAHS            */ {  .program = GM_PROGRAM_CHOIR_AAHS,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x35  53  GM_PROGRAM_VOICE_OOHS            */ {  .program = GM_PROGRAM_VOICE_OOHS,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x36  54  GM_PROGRAM_SYNTH_VOICE           */ {  .program = GM_PROGRAM_SYNTH_VOICE,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x37  55  GM_PROGRAM_ORCHESTRA_HIT         */ {  .program = GM_PROGRAM_ORCHESTRA_HIT,          .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x38  56  GM_PROGRAM_TRUMPET               */ {  .program = GM_PROGRAM_TRUMPET,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x39  57  GM_PROGRAM_TROMBONE              */ {  .program = GM_PROGRAM_TROMBONE,               .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3A  58  GM_PROGRAM_TUBA                  */ {  .program = GM_PROGRAM_TUBA,                   .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3B  59  GM_PROGRAM_MUTED_TRUMPET         */ {  .program = GM_PROGRAM_MUTED_TRUMPET,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3C  60  GM_PROGRAM_FRENCH_HORN           */ {  .program = GM_PROGRAM_FRENCH_HORN,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3D  61  GM_PROGRAM_BRASS_SECTION         */ {  .program = GM_PROGRAM_BRASS_SECTION,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3E  62  GM_PROGRAM_SYNTHBRASS_1          */ {  .program = GM_PROGRAM_SYNTHBRASS_1,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x3F  63  GM_PROGRAM_SYNTHBRASS_2          */ {  .program = GM_PROGRAM_SYNTHBRASS_2,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x40  64  GM_PROGRAM_SOPRANO_SAX           */ {  .program = GM_PROGRAM_SOPRANO_SAX,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x41  65  GM_PROGRAM_ALTO_SAX              */ {  .program = GM_PROGRAM_ALTO_SAX,               .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x42  66  GM_PROGRAM_TENOR_SAX             */ {  .program = GM_PROGRAM_TENOR_SAX,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x43  67  GM_PROGRAM_BARITONE_SAX          */ {  .program = GM_PROGRAM_BARITONE_SAX,           .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x44  68  GM_PROGRAM_OBOE                  */ {  .program = GM_PROGRAM_OBOE,                   .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x45  69  GM_PROGRAM_ENGLISH_HORN          */ {  .program = GM_PROGRAM_ENGLISH_HORN,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x46  70  GM_PROGRAM_BASSOON               */ {  .program = GM_PROGRAM_BASSOON,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x47  71  GM_PROGRAM_CLARINET              */ {  .program = GM_PROGRAM_CLARINET,               .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x48  72  GM_PROGRAM_PICCOLO               */ {  .program = GM_PROGRAM_PICCOLO,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x49  73  GM_PROGRAM_FLUTE                 */ {  .program = GM_PROGRAM_FLUTE,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4A  74  GM_PROGRAM_RECORDER              */ {  .program = GM_PROGRAM_RECORDER,               .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4B  75  GM_PROGRAM_PAN_FLUTE             */ {  .program = GM_PROGRAM_PAN_FLUTE,              .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4C  76  GM_PROGRAM_BLOWN_BOTTLE          */ {  .program = GM_PROGRAM_BLOWN_BOTTLE,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4D  77  GM_PROGRAM_SHAKUHACHI            */ {  .program = GM_PROGRAM_SHAKUHACHI,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4E  78  GM_PROGRAM_WHISTLE               */ {  .program = GM_PROGRAM_WHISTLE,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x4F  79  GM_PROGRAM_OCARINA               */ {  .program = GM_PROGRAM_OCARINA,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x50  80  GM_PROGRAM_LEAD_1_SQUARE         */ {  .program = GM_PROGRAM_LEAD_1_SQUARE,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x51  81  GM_PROGRAM_LEAD_2_SAWTOOTH       */ {  .program = GM_PROGRAM_LEAD_2_SAWTOOTH,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x52  82  GM_PROGRAM_LEAD_3_CALLIOPE       */ {  .program = GM_PROGRAM_LEAD_3_CALLIOPE,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x53  83  GM_PROGRAM_LEAD_4_CHIFF          */ {  .program = GM_PROGRAM_LEAD_4_CHIFF,           .flags = ROLAND_GR09_RANGE_DEFAULT       | VOLUME_UP_4DB    },
        /* 0x54  84  GM_PROGRAM_LEAD_5_CHARANG        */ {  .program = GM_PROGRAM_LEAD_5_CHARANG,         .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x55  85  GM_PROGRAM_LEAD_6_VOICE          */ {  .program = GM_PROGRAM_LEAD_6_VOICE,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x56  86  GM_PROGRAM_LEAD_7_FIFTHS         */ {  .program = GM_PROGRAM_LEAD_7_FIFTHS,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x57  87  GM_PROGRAM_LEAD_8_BASS_LEAD      */ {  .program = GM_PROGRAM_LEAD_8_BASS_LEAD,       .flags = ROLAND_GR09_RANGE_DEFAULT       | VOLUME_DOWN_2DB  },
        /* 0x58  88  GM_PROGRAM_PAD_1_NEW_AGE         */ {  .program = GM_PROGRAM_PAD_1_NEW_AGE,          .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x59  89  GM_PROGRAM_PAD_2_WARM            */ {  .program = GM_PROGRAM_PAD_2_WARM,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5A  90  GM_PROGRAM_PAD_3_POLYSYNTH       */ {  .program = GM_PROGRAM_PAD_3_POLYSYNTH,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5B  91  GM_PROGRAM_PAD_4_CHOIR           */ {  .program = GM_PROGRAM_PAD_4_CHOIR,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5C  92  GM_PROGRAM_PAD_5_BOWED           */ {  .program = GM_PROGRAM_PAD_5_BOWED,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5D  93  GM_PROGRAM_PAD_6_METALLIC        */ {  .program = GM_PROGRAM_PAD_6_METALLIC,         .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5E  94  GM_PROGRAM_PAD_7_HALO            */ {  .program = GM_PROGRAM_PAD_7_HALO,             .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x5F  95  GM_PROGRAM_PAD_8_SWEEP           */ {  .program = GM_PROGRAM_PAD_8_SWEEP,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x60  96  GM_PROGRAM_FX_1_RAIN             */ {  .program = GM_PROGRAM_FX_1_RAIN,              .flags = ROLAND_GR09_RANGE_DEFAULT       | VOLUME_UP_4DB    },
        /* 0x61  97  GM_PROGRAM_FX_2_SOUNDTRACK       */ {  .program = GM_PROGRAM_FX_2_SOUNDTRACK,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x62  98  GM_PROGRAM_FX_3_CRYSTAL          */ {  .program = GM_PROGRAM_FX_3_CRYSTAL,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x63  99  GM_PROGRAM_FX_4_ATMOSPHERE       */ {  .program = GM_PROGRAM_FX_4_ATMOSPHERE,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x64 100  GM_PROGRAM_FX_5_BRIGHTNESS       */ {  .program = GM_PROGRAM_FX_5_BRIGHTNESS,        .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x65 101  GM_PROGRAM_FX_6_GOBLINS          */ {  .program = GM_PROGRAM_FX_6_GOBLINS,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x66 102  GM_PROGRAM_FX_7_ECHOES           */ {  .program = GM_PROGRAM_FX_7_ECHOES,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x67 103  GM_PROGRAM_FX_8_SCI_FI           */ {  .program = GM_PROGRAM_FX_8_SCI_FI,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x68 104  GM_PROGRAM_SITAR                 */ {  .program = GM_PROGRAM_SITAR,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x69 105  GM_PROGRAM_BANJO                 */ {  .program = GM_PROGRAM_BANJO,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x6A 106  GM_PROGRAM_SHAMISEN              */ {  .program = GM_PROGRAM_SHAMISEN,               .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x6B 107  GM_PROGRAM_KOTO                  */ {  .program = GM_PROGRAM_KOTO,                   .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x6C 108  GM_PROGRAM_KALIMBA               */ {  .program = GM_PROGRAM_KALIMBA,                .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x6D 109  GM_PROGRAM_BAG_PIPE              */ {  .program = GM_PROGRAM_BAG_PIPE,               .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x6E 110  GM_PROGRAM_FIDDLE                */ {  .program = GM_PROGRAM_FIDDLE,                 .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x6F 111  GM_PROGRAM_SHANAI                */ {  .program = GM_PROGRAM_SHANAI,                 .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x70 112  GM_PROGRAM_TINKLE_BELL           */ {  .program = GM_PROGRAM_TINKLE_BELL,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x71 113  GM_PROGRAM_AGOGO                 */ {  .program = GM_PROGRAM_AGOGO,                  .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x72 114  GM_PROGRAM_STEEL_DRUMS           */ {  .program = GM_PROGRAM_STEEL_DRUMS,            .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x73 115  GM_PROGRAM_WOODBLOCK             */ {  .program = GM_PROGRAM_WOODBLOCK,              .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x74 116  GM_PROGRAM_TAIKO_DRUM            */ {  .program = GM_PROGRAM_TAIKO_DRUM,             .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x75 117  GM_PROGRAM_MELODIC_TOM           */ {  .program = GM_PROGRAM_MELODIC_TOM,            .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER  | VOLUME_UP_6DB    },
        /* 0x76 118  GM_PROGRAM_SYNTH_DRUM            */ {  .program = GM_PROGRAM_SYNTH_DRUM,             .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x77 119  GM_PROGRAM_REVERSE_CYMBAL        */ {  .program = GM_PROGRAM_REVERSE_CYMBAL,         .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER | VOLUME_UP_6DB    },
        /* 0x78 120  GM_PROGRAM_GUITAR_FRET_NOISE     */ {  .program = GM_PROGRAM_GUITAR_FRET_NOISE,      .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x79 121  GM_PROGRAM_BREATH_NOISE          */ {  .program = GM_PROGRAM_BREATH_NOISE,           .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x7A 122  GM_PROGRAM_SEASHORE              */ {  .program = GM_PROGRAM_SEASHORE,               .flags = ROLAND_GR09_RANGE_DEFAULT       | VOLUME_UP_4DB    },
        /* 0x7B 123  GM_PROGRAM_BIRD_TWEET            */ {  .program = GM_PROGRAM_BIRD_TWEET,             .flags = ROLAND_GR09_RANGE_OCTAVE_HIGHER                    },
        /* 0x7C 124  GM_PROGRAM_TELEPHONE_RING        */ {  .program = GM_PROGRAM_TELEPHONE_RING,         .flags = ROLAND_GR09_RANGE_DEFAULT                          },
        /* 0x7D 125  GM_PROGRAM_HELICOPTER            */ {  .program = GM_PROGRAM_HELICOPTER,             .flags = ROLAND_GR09_RANGE_OCTAVE_LOWER                     },
        /* 0x7E 126  GM_PROGRAM_APPLAUSE              */ {  .program = GM_PROGRAM_APPLAUSE,               .flags = ROLAND_GR09_RANGE_DEFAULT       | VOLUME_UP_6DB    },
        /* 0x7F 127  GM_PROGRAM_GUNSHOT               */ {  .program = GM_PROGRAM_GUNSHOT,                .flags = ROLAND_GR09_RANGE_DEFAULT                          }
    },

    .melodic_note_ranges = {
        /* 0x00 ROLAND_GR09_RANGE_INVALID       */ {  .lowest_note = INVALID_NOTE,             .middle_c = INVALID_NOTE,               .highest_note = INVALID_NOTE              },
        /* 0x01 ROLAND_GR09_RANGE_OCTAVE_HIGHER */ {  .lowest_note = ROLAND_GR09_LOWEST_NOTE,  .middle_c = ROLAND_GR09_MIDDLE_C + 12,  .highest_note = ROLAND_GR09_HIGHEST_NOTE  },
        /* 0x02 ROLAND_GR09_RANGE_OCTAVE_LOWER  */ {  .lowest_note = ROLAND_GR09_LOWEST_NOTE,  .middle_c = ROLAND_GR09_MIDDLE_C - 12,  .highest_note = ROLAND_GR09_HIGHEST_NOTE  },
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
        /* 0x0F ROLAND_GR09_RANGE_DEFAULT       */ {  .lowest_note = ROLAND_GR09_LOWEST_NOTE,  .middle_c = ROLAND_GR09_MIDDLE_C,       .highest_note = ROLAND_GR09_HIGHEST_NOTE  }
    },

    .percussion_notes = {
        /* 0x00   0  GM_PERCUSSION_UNDEFINED_00       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x01   1  GM_PERCUSSION_UNDEFINED_01       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x02   2  GM_PERCUSSION_UNDEFINED_02       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x03   3  GM_PERCUSSION_UNDEFINED_03       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x04   4  GM_PERCUSSION_UNDEFINED_04       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x05   5  GM_PERCUSSION_UNDEFINED_05       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x06   6  GM_PERCUSSION_UNDEFINED_06       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x07   7  GM_PERCUSSION_UNDEFINED_07       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x08   8  GM_PERCUSSION_UNDEFINED_08       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x09   9  GM_PERCUSSION_UNDEFINED_09       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0A  10  GM_PERCUSSION_UNDEFINED_0A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0B  11  GM_PERCUSSION_UNDEFINED_0B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0C  12  GM_PERCUSSION_UNDEFINED_0C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0D  13  GM_PERCUSSION_UNDEFINED_0D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0E  14  GM_PERCUSSION_UNDEFINED_0E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x0F  15  GM_PERCUSSION_UNDEFINED_0F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x10  16  GM_PERCUSSION_UNDEFINED_10       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x11  17  GM_PERCUSSION_UNDEFINED_11       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x12  18  GM_PERCUSSION_UNDEFINED_12       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x13  19  GM_PERCUSSION_UNDEFINED_13       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x14  20  GM_PERCUSSION_UNDEFINED_14       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x15  21  GM_PERCUSSION_UNDEFINED_15       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x16  22  GM_PERCUSSION_UNDEFINED_16       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x17  23  GM_PERCUSSION_UNDEFINED_17       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x18  24  GM_PERCUSSION_UNDEFINED_18       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x19  25  GM_PERCUSSION_UNDEFINED_19       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1A  26  GM_PERCUSSION_UNDEFINED_1A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1B  27  GM_PERCUSSION_UNDEFINED_1B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1C  28  GM_PERCUSSION_UNDEFINED_1C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1D  29  GM_PERCUSSION_UNDEFINED_1D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1E  30  GM_PERCUSSION_UNDEFINED_1E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x1F  31  GM_PERCUSSION_UNDEFINED_1F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x20  32  GM_PERCUSSION_UNDEFINED_20       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x21  33  GM_PERCUSSION_UNDEFINED_21       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x22  34  GM_PERCUSSION_UNDEFINED_22       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x23  35  GM_PERCUSSION_ACOUSTIC_BASS_DRUM */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x24  36  GM_PERCUSSION_BASS_DRUM_1        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x25  37  GM_PERCUSSION_SIDE_STICK         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x26  38  GM_PERCUSSION_ACOUSTIC_SNARE     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x27  39  GM_PERCUSSION_HAND_CLAP          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x28  40  GM_PERCUSSION_ELECTRIC_SNARE     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x29  41  GM_PERCUSSION_LOW_FLOOR_TOM      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2A  42  GM_PERCUSSION_CLOSED_HI_HAT      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2B  43  GM_PERCUSSION_HIGH_FLOOR_TOM     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2C  44  GM_PERCUSSION_PEDAL_HI_HAT       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2D  45  GM_PERCUSSION_LOW_TOM            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2E  46  GM_PERCUSSION_OPEN_HI_HAT        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x2F  47  GM_PERCUSSION_LOW_MID_TOM        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x30  48  GM_PERCUSSION_HI_MID_TOM         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x31  49  GM_PERCUSSION_CRASH_CYMBAL_1     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x32  50  GM_PERCUSSION_HIGH_TOM           */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x33  51  GM_PERCUSSION_RIDE_CYMBAL_1      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x34  52  GM_PERCUSSION_CHINESE_CYMBAL     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x35  53  GM_PERCUSSION_RIDE_BELL          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x36  54  GM_PERCUSSION_TAMBOURINE         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x37  55  GM_PERCUSSION_SPLASH_CYMBAL      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x38  56  GM_PERCUSSION_COWBELL            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x39  57  GM_PERCUSSION_CRASH_CYMBAL_2     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3A  58  GM_PERCUSSION_VIBRASLAP          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3B  59  GM_PERCUSSION_RIDE_CYMBAL_2      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3C  60  GM_PERCUSSION_HI_BONGO           */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3D  61  GM_PERCUSSION_LOW_BONGO          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3E  62  GM_PERCUSSION_MUTE_HI_CONGA      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x3F  63  GM_PERCUSSION_OPEN_HI_CONGA      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x40  64  GM_PERCUSSION_LOW_CONGA          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x41  65  GM_PERCUSSION_HIGH_TIMBALE       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x42  66  GM_PERCUSSION_LOW_TIMBALE        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x43  67  GM_PERCUSSION_HIGH_AGOGO         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x44  68  GM_PERCUSSION_LOW_AGOGO          */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x45  69  GM_PERCUSSION_CABASA             */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x46  70  GM_PERCUSSION_MARACAS            */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x47  71  GM_PERCUSSION_SHORT_WHISTLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x48  72  GM_PERCUSSION_LONG_WHISTLE       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x49  73  GM_PERCUSSION_SHORT_GUIRO        */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4A  74  GM_PERCUSSION_LONG_GUIRO         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4B  75  GM_PERCUSSION_CLAVES             */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4C  76  GM_PERCUSSION_HI_WOOD_BLOCK      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4D  77  GM_PERCUSSION_LOW_WOOD_BLOCK     */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4E  78  GM_PERCUSSION_MUTE_CUICA         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x4F  79  GM_PERCUSSION_OPEN_CUICA         */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x50  80  GM_PERCUSSION_MUTE_TRIANGLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x51  81  GM_PERCUSSION_OPEN_TRIANGLE      */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x52  82  GM_PERCUSSION_UNDEFINED_52       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x53  83  GM_PERCUSSION_UNDEFINED_53       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x54  84  GM_PERCUSSION_UNDEFINED_54       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x55  85  GM_PERCUSSION_UNDEFINED_55       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x56  86  GM_PERCUSSION_UNDEFINED_56       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x57  87  GM_PERCUSSION_UNDEFINED_57       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x58  88  GM_PERCUSSION_UNDEFINED_58       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x59  89  GM_PERCUSSION_UNDEFINED_59       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5A  90  GM_PERCUSSION_UNDEFINED_5A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5B  91  GM_PERCUSSION_UNDEFINED_5B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5C  92  GM_PERCUSSION_UNDEFINED_5C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5D  93  GM_PERCUSSION_UNDEFINED_5D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5E  94  GM_PERCUSSION_UNDEFINED_5E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x5F  95  GM_PERCUSSION_UNDEFINED_5F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x60  96  GM_PERCUSSION_UNDEFINED_60       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x61  97  GM_PERCUSSION_UNDEFINED_61       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x62  98  GM_PERCUSSION_UNDEFINED_62       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x63  99  GM_PERCUSSION_UNDEFINED_63       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x64 100  GM_PERCUSSION_UNDEFINED_64       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x65 101  GM_PERCUSSION_UNDEFINED_65       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x66 102  GM_PERCUSSION_UNDEFINED_66       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x67 103  GM_PERCUSSION_UNDEFINED_67       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x68 104  GM_PERCUSSION_UNDEFINED_68       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x69 105  GM_PERCUSSION_UNDEFINED_69       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6A 106  GM_PERCUSSION_UNDEFINED_6A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6B 107  GM_PERCUSSION_UNDEFINED_6B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6C 108  GM_PERCUSSION_UNDEFINED_6C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6D 109  GM_PERCUSSION_UNDEFINED_6D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6E 110  GM_PERCUSSION_UNDEFINED_6E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x6F 111  GM_PERCUSSION_UNDEFINED_6F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x70 112  GM_PERCUSSION_UNDEFINED_70       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x71 113  GM_PERCUSSION_UNDEFINED_71       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x72 114  GM_PERCUSSION_UNDEFINED_72       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x73 115  GM_PERCUSSION_UNDEFINED_73       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x74 116  GM_PERCUSSION_UNDEFINED_74       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x75 117  GM_PERCUSSION_UNDEFINED_75       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x76 118  GM_PERCUSSION_UNDEFINED_76       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x77 119  GM_PERCUSSION_UNDEFINED_77       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x78 120  GM_PERCUSSION_UNDEFINED_78       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x79 121  GM_PERCUSSION_UNDEFINED_79       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7A 122  GM_PERCUSSION_UNDEFINED_7A       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7B 123  GM_PERCUSSION_UNDEFINED_7B       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7C 124  GM_PERCUSSION_UNDEFINED_7C       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7D 125  GM_PERCUSSION_UNDEFINED_7D       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7E 126  GM_PERCUSSION_UNDEFINED_7E       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  },
        /* 0x7F 127  GM_PERCUSSION_UNDEFINED_7F       */ {  .program = INVALID_PROGRAM,  .note = INVALID_NOTE  }
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
        0b0000000000000001  // 11
    },

    .percussion_channels_bitmap = 0b0000000000000000,

    .controllers_bitmap = {

      //(1 << (MIDI_CONTROL_BANK_SELECT                  & 0x1F)) |  /* 0x00   0 */
        (1 << (MIDI_CONTROL_MODULATION_WHEEL_OR_LEVER    & 0x1F)) |  /* 0x01   1 */
      //(1 << (MIDI_CONTROL_BREATH_CONTROLLER            & 0x1F)) |  /* 0x02   2 */
      //(1 << (MIDI_CONTROL_UNDEFINED_03                 & 0x1F)) |  /* 0x03   3 */
      //(1 << (MIDI_CONTROL_FOOT_CONTROLLER              & 0x1F)) |  /* 0x04   4 */
      //(1 << (MIDI_CONTROL_PORTAMENTO_TIME              & 0x1F)) |  /* 0x05   5 */
      //(1 << (MIDI_CONTROL_DATA_ENTRY_MSB               & 0x1F)) |  /* 0x06   6 */
        (1 << (MIDI_CONTROL_CHANNEL_VOLUME               & 0x1F)) |  /* 0x07   7 */
      //(1 << (MIDI_CONTROL_BALANCE                      & 0x1F)) |  /* 0x08   8 */
      //(1 << (MIDI_CONTROL_UNDEFINED_09                 & 0x1F)) |  /* 0x09   9 */
      //(1 << (MIDI_CONTROL_PAN                          & 0x1F)) |  /* 0x0A  10 */
      //(1 << (MIDI_CONTROL_EXPRESSION_CONTROLLER        & 0x1F)) |  /* 0x0B  11 */
      //(1 << (MIDI_CONTROL_EFFECT_CONTROL_1             & 0x1F)) |  /* 0x0C  12 */
      //(1 << (MIDI_CONTROL_EFFECT_CONTROL_2             & 0x1F)) |  /* 0x0D  13 */
      //(1 << (MIDI_CONTROL_UNDEFINED_0E                 & 0x1F)) |  /* 0x0E  14 */
      //(1 << (MIDI_CONTROL_UNDEFINED_0F                 & 0x1F)) |  /* 0x0F  15 */
        (1 << (MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1 & 0x1F)) |  /* 0x10  16 */
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
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_05               & 0x1F)) |  /* 0x25  37 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_06               & 0x1F)) |  /* 0x26  38 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_07               & 0x1F)) |  /* 0x27  39 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_08               & 0x1F)) |  /* 0x28  40 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_09               & 0x1F)) |  /* 0x29  41 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0A               & 0x1F)) |  /* 0x2A  42 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0B               & 0x1F)) |  /* 0x2B  43 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0C               & 0x1F)) |  /* 0x2C  44 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0D               & 0x1F)) |  /* 0x2D  45 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0E               & 0x1F)) |  /* 0x2E  46 */
      //(1 << (MIDI_CONTROL_LSB_FOR_MSB_0F               & 0x1F)) |  /* 0x2F  47 */
        (1 << (MIDI_CONTROL_LSB_FOR_MSB_10               & 0x1F)) |  /* 0x30  48 */
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
      //(1 << (MIDI_CONTROL_PORTAMENTO_ON_OFF            & 0x1F)) |  /* 0x41  65 */
      //(1 << (MIDI_CONTROL_SOSTENUTO                    & 0x1F)) |  /* 0x42  66 */
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

    .initialization_sequence_offset = INVALID_SEQUENCE_OFFSET,
    .program_change_sequence_offset = 0x0000,
    .note_on_sequence_offset        = INVALID_SEQUENCE_OFFSET,
    .note_off_sequence_offset       = INVALID_SEQUENCE_OFFSET,

    .custom_sequences = {

        /* program change, p[0] = channel, p[1] = program */

        /* 0000 */ 0xF0, 0x41, 0x10, 0x67, 0x12, /* "set data" sysex */
        /*      */ /* 01 00 00 = patch main tone A11 */
        /*      */ 0b11000000 /* reset Roland checksum */,
        /*      */ /* over */ 0x01,
        /*      */ 0x00,
        /*      */ 0x00,
        /*      */ 0b10011100 /* 8-bit lookup in the following 128-byte table using p[1] as the index                   */,
                    /*                               program to tone number LSB mapping                                 */
                    /*   _0    _1    _2    _3    _4    _5    _6    _7    _8    _9    _A    _B    _C    _D    _E    _F   */
        /*      0_ */  0x00, 0x01, 0x05, 0x02, 0x03, 0x04, 0x4A, 0x0C, 0x2F, 0x0E, 0x31, 0x0D, 0x0F, 0x2E, 0x1D, 0x1E,
        /*      1_ */  0x10, 0x11, 0x12, 0x16, 0x1C, 0x56, 0x08, 0x56, 0x18, 0x17, 0x31, 0x2E, 0x2F, 0x20, 0x1D, 0x1A,
        /*      2_ */  0x27, 0x29, 0x2D, 0x31, 0x2E, 0x2F, 0x34, 0x37, 0x46, 0x46, 0x47, 0x48, 0x15, 0x36, 0x4B, 0x28,
        /*      3_ */  0x3B, 0x39, 0x38, 0x3C, 0x4D, 0x4E, 0x28, 0x5F, 0x65, 0x66, 0x67, 0x69, 0x6D, 0x5C, 0x60, 0x62,
        /*      4_ */  0x79, 0x77, 0x78, 0x78, 0x7F, 0x6E, 0x6B, 0x00, 0x7D, 0x7E, 0x7D, 0x01, 0x06, 0x07, 0x09, 0x04,
        /*      5_ */  0x10, 0x0A, 0x05, 0x52, 0x37, 0x50, 0x16, 0x35, 0x51, 0x0E, 0x0C, 0x26, 0x38, 0x0F, 0x25, 0x23,
        /*      6_ */  0x55, 0x29, 0x23, 0x1F, 0x19, 0x32, 0x57, 0x27, 0x25, 0x24, 0x4A, 0x26, 0x5B, 0x08, 0x49, 0x69,
        /*      7_ */  0x2D, 0x2E, 0x33, 0x0D, 0x06, 0x1D, 0x2E, 0x55, 0x1B, 0x53, 0x55, 0x69, 0x63, 0x7A, 0x55, 0x59,
        /*      */ /* over */ 0x00,
        /*      */ 0b10011000 /* 4-bit lookup in the following 64-byte table using p[1] as the index */,
                    /*       program to tone number MSB mapping                                      */
                    /*   01    23    45    67    89    AB    CD    EF                                */
        /*      0_ */  0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x01, 0x10,
        /*      1_ */  0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
        /*      2_ */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        /*      3_ */  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
        /*      4_ */  0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x11, 0x11,
        /*      5_ */  0x11, 0x10, 0x00, 0x10, 0x01, 0x11, 0x01, 0x11,
        /*      6_ */  0x01, 0x01, 0x11, 0x01, 0x00, 0x00, 0x01, 0x00,
        /*      7_ */  0x11, 0x11, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00,
        /*      */ /* over */ 0x00,
        /*      */ 0b11000001 /* insert Roland checksum */,
        /*      */ /* over */ 0x00,
        /*      */ 0xF7, /* end of sysex */

        /*      */ MIDI_MESSAGE_DELAY,
        /*      */ 0x00,
        /*      */ 0x14, /* 20 ms */

        /*      */ 0xC0, 0x7F, /* switch to some other program */
        /*      */ 0xC0, 0x00, /* switch back to A11 */

        /*      */ INVALID_STATUS_BYTE

    }

};

/*
The above lookup tables are script-generated from the following mapping:

GM_PROGRAM_ACOUSTIC_GRAND_PIANO   ROLAND_GR09_TONE_ACOUSTIC_PIANO1
GM_PROGRAM_BRIGHT_ACOUSTIC_PIANO  ROLAND_GR09_TONE_ACOUSTIC_PIANO2
GM_PROGRAM_ELECTRIC_GRAND_PIANO   ROLAND_GR09_TONE_ELECTRIC_GRAND
GM_PROGRAM_HONKY_TONK_PIANO       ROLAND_GR09_TONE_HONKY_TONK
GM_PROGRAM_ELECTRIC_PIANO_1       ROLAND_GR09_TONE_ELECTRIC_PIANO1
GM_PROGRAM_ELECTRIC_PIANO_2       ROLAND_GR09_TONE_ELECTRIC_PIANO2
GM_PROGRAM_HARPSICHORD            ROLAND_GR09_TONE_WIRE_STRING
GM_PROGRAM_CLAVI                  ROLAND_GR09_TONE_CLAV2
GM_PROGRAM_CELESTA                ROLAND_GR09_TONE_SPARKLE_BELL
GM_PROGRAM_GLOCKENSPIEL           ROLAND_GR09_TONE_VIBES2
GM_PROGRAM_MUSIC_BOX              ROLAND_GR09_TONE_FANTA_PAD
GM_PROGRAM_VIBRAPHONE             ROLAND_GR09_TONE_VIBES
GM_PROGRAM_MARIMBA                ROLAND_GR09_TONE_MARIMBA
GM_PROGRAM_XYLOPHONE              ROLAND_GR09_TONE_SYNTH_BELL
GM_PROGRAM_TUBULAR_BELLS          ROLAND_GR09_TONE_HARP_PAD
GM_PROGRAM_DULCIMER               ROLAND_GR09_TONE_GUITAR_CLAV
GM_PROGRAM_DRAWBAR_ORGAN          ROLAND_GR09_TONE_ORGAN1
GM_PROGRAM_PERCUSSIVE_ORGAN       ROLAND_GR09_TONE_ORGAN2
GM_PROGRAM_ROCK_ORGAN             ROLAND_GR09_TONE_ROCK_ORGAN1
GM_PROGRAM_CHURCH_ORGAN           ROLAND_GR09_TONE_PIPE_ORGAN1
GM_PROGRAM_REED_ORGAN             ROLAND_GR09_TONE_OMINOUS
GM_PROGRAM_ACCORDION              ROLAND_GR09_TONE_SYNTH_HARM
GM_PROGRAM_HARMONICA              ROLAND_GR09_TONE_HARMONICA
GM_PROGRAM_TANGO_ACCORDION        ROLAND_GR09_TONE_SYNTH_HARM
GM_PROGRAM_ACOUSTIC_GUITAR_NYLON  ROLAND_GR09_TONE_NYLN_GUITAR
GM_PROGRAM_ACOUSTIC_GUITAR_STEEL  ROLAND_GR09_TONE_STEEL_GUITAR1
GM_PROGRAM_ELECTRIC_GUITAR_JAZZ   ROLAND_GR09_TONE_FRETLESS_BASS
GM_PROGRAM_ELECTRIC_GUITAR_CLEAN  ROLAND_GR09_TONE_SLAP_BASS1
GM_PROGRAM_ELECTRIC_GUITAR_MUTED  ROLAND_GR09_TONE_SLAP_BASS2
GM_PROGRAM_OVERDRIVEN_GUITAR      ROLAND_GR09_TONE_FEED_BACK1
GM_PROGRAM_DISTORTION_GUITAR      ROLAND_GR09_TONE_DISTORTION_GTR2
GM_PROGRAM_GUITAR_HARMONICS       ROLAND_GR09_TONE_GTR_HARMONICS1
GM_PROGRAM_ACOUSTIC_BASS          ROLAND_GR09_TONE_ACOUSTIC_BASS1
GM_PROGRAM_ELECTRIC_BASS_FINGER   ROLAND_GR09_TONE_ELECTRIC_BASS1
GM_PROGRAM_ELECTRIC_BASS_PICK     ROLAND_GR09_TONE_PICK_BASS4
GM_PROGRAM_FRETLESS_BASS          ROLAND_GR09_TONE_FRETLESS_BASS
GM_PROGRAM_SLAP_BASS_1            ROLAND_GR09_TONE_SLAP_BASS1
GM_PROGRAM_SLAP_BASS_2            ROLAND_GR09_TONE_SLAP_BASS2
GM_PROGRAM_SYNTH_BASS_1           ROLAND_GR09_TONE_MINI_BASS2
GM_PROGRAM_SYNTH_BASS_2           ROLAND_GR09_TONE_RESO_BASS1
GM_PROGRAM_VIOLIN                 ROLAND_GR09_TONE_VIOLIN
GM_PROGRAM_VIOLA                  ROLAND_GR09_TONE_VIOLIN
GM_PROGRAM_CELLO                  ROLAND_GR09_TONE_CELLO1
GM_PROGRAM_CONTRABASS             ROLAND_GR09_TONE_CONTRA_BASS
GM_PROGRAM_TREMOLO_STRINGS        ROLAND_GR09_TONE_CHEESO
GM_PROGRAM_PIZZICATO_STRINGS      ROLAND_GR09_TONE_OCT_BASS2
GM_PROGRAM_ORCHESTRAL_HARP        ROLAND_GR09_TONE_HARP
GM_PROGRAM_TIMPANI                ROLAND_GR09_TONE_ACOUSTIC_BASS2
GM_PROGRAM_STRING_ENSEMBLE_1      ROLAND_GR09_TONE_OCT_STRINGS
GM_PROGRAM_STRING_ENSEMBLE_2      ROLAND_GR09_TONE_FAST_STRINGS
GM_PROGRAM_SYNTHSTRINGS_1         ROLAND_GR09_TONE_PEDAL_BASS
GM_PROGRAM_SYNTHSTRINGS_2         ROLAND_GR09_TONE_BOWED_STRINGS
GM_PROGRAM_CHOIR_AAHS             ROLAND_GR09_TONE_SYNTH_VOX1
GM_PROGRAM_VOICE_OOHS             ROLAND_GR09_TONE_SYNTH_VOX2
GM_PROGRAM_SYNTH_VOICE            ROLAND_GR09_TONE_DIGITAL_VOX1
GM_PROGRAM_ORCHESTRA_HIT          ROLAND_GR09_TONE_OCT_BRASS
GM_PROGRAM_TRUMPET                ROLAND_GR09_TONE_TRUMPET
GM_PROGRAM_TROMBONE               ROLAND_GR09_TONE_TROMBONE
GM_PROGRAM_TUBA                   ROLAND_GR09_TONE_TUBA
GM_PROGRAM_MUTED_TRUMPET          ROLAND_GR09_TONE_MUTE_TRUMPET
GM_PROGRAM_FRENCH_HORN            ROLAND_GR09_TONE_FRENCH_HORN
GM_PROGRAM_BRASS_SECTION          ROLAND_GR09_TONE_BRASS_SECTION
GM_PROGRAM_SYNTHBRASS_1           ROLAND_GR09_TONE_SYNTH_BRASS1
GM_PROGRAM_SYNTHBRASS_2           ROLAND_GR09_TONE_SYNTH_BRASS3
GM_PROGRAM_SOPRANO_SAX            ROLAND_GR09_TONE_SOPRANO_SAX
GM_PROGRAM_ALTO_SAX               ROLAND_GR09_TONE_ALTO_SAX
GM_PROGRAM_TENOR_SAX              ROLAND_GR09_TONE_TENOR_SAX
GM_PROGRAM_BARITONE_SAX           ROLAND_GR09_TONE_TENOR_SAX
GM_PROGRAM_OBOE                   ROLAND_GR09_TONE_OBOE
GM_PROGRAM_ENGLISH_HORN           ROLAND_GR09_TONE_FLUGEL_HORN
GM_PROGRAM_BASSOON                ROLAND_GR09_TONE_TP_PLUS_TB
GM_PROGRAM_CLARINET               ROLAND_GR09_TONE_CLARINET
GM_PROGRAM_PICCOLO                ROLAND_GR09_TONE_PICCOLO
GM_PROGRAM_FLUTE                  ROLAND_GR09_TONE_FLUTE
GM_PROGRAM_RECORDER               ROLAND_GR09_TONE_PICCOLO
GM_PROGRAM_PAN_FLUTE              ROLAND_GR09_TONE_CHIFF_FLUTE
GM_PROGRAM_BLOWN_BOTTLE           ROLAND_GR09_TONE_BOTTLE_BLOW
GM_PROGRAM_SHAKUHACHI             ROLAND_GR09_TONE_BLOW_PIPE
GM_PROGRAM_WHISTLE                ROLAND_GR09_TONE_WHISTLE
GM_PROGRAM_OCARINA                ROLAND_GR09_TONE_OCARINA
GM_PROGRAM_LEAD_1_SQUARE          ROLAND_GR09_TONE_SQUARE_LEAD
GM_PROGRAM_LEAD_2_SAWTOOTH        ROLAND_GR09_TONE_GR300_LEAD
GM_PROGRAM_LEAD_3_CALLIOPE        ROLAND_GR09_TONE_CALLIOPE
GM_PROGRAM_LEAD_4_CHIFF           ROLAND_GR09_TONE_CHIFF_PAD
GM_PROGRAM_LEAD_5_CHARANG         ROLAND_GR09_TONE_RESO_BASS1
GM_PROGRAM_LEAD_6_VOICE           ROLAND_GR09_TONE_VOX_LEAD1
GM_PROGRAM_LEAD_7_FIFTHS          ROLAND_GR09_TONE_5TH_LEAD1
GM_PROGRAM_LEAD_8_BASS_LEAD       ROLAND_GR09_TONE_OCT_BASS1
GM_PROGRAM_PAD_1_NEW_AGE          ROLAND_GR09_TONE_HAUNT_VOX
GM_PROGRAM_PAD_2_WARM             ROLAND_GR09_TONE_SOFT_PAD
GM_PROGRAM_PAD_3_POLYSYNTH        ROLAND_GR09_TONE_POLY_SYNTH1
GM_PROGRAM_PAD_4_CHOIR            ROLAND_GR09_TONE_CHOIR_PAD
GM_PROGRAM_PAD_5_BOWED            ROLAND_GR09_TONE_PEDAL_BASS
GM_PROGRAM_PAD_6_METALLIC         ROLAND_GR09_TONE_METAL_PAD1
GM_PROGRAM_PAD_7_HALO             ROLAND_GR09_TONE_HELLOW_PAD
GM_PROGRAM_PAD_8_SWEEP            ROLAND_GR09_TONE_SWEEP_PAD1
GM_PROGRAM_FX_1_RAIN              ROLAND_GR09_TONE_INVERSION
GM_PROGRAM_FX_2_SOUNDTRACK        ROLAND_GR09_TONE_SOUNDTRACK
GM_PROGRAM_FX_3_CRYSTAL           ROLAND_GR09_TONE_PEDAL_STEEL
GM_PROGRAM_FX_4_ATMOSPHERE        ROLAND_GR09_TONE_ATMOSPHERE
GM_PROGRAM_FX_5_BRIGHTNESS        ROLAND_GR09_TONE_SAW_PAD
GM_PROGRAM_FX_6_GOBLINS           ROLAND_GR09_TONE_WHISPER
GM_PROGRAM_FX_7_ECHOES            ROLAND_GR09_TONE_ECHO_VOX
GM_PROGRAM_FX_8_SCI_FI            ROLAND_GR09_TONE_DIGITAL_BOW
GM_PROGRAM_SITAR                  ROLAND_GR09_TONE_ELECTRIC_SITAR1
GM_PROGRAM_BANJO                  ROLAND_GR09_TONE_BANJO
GM_PROGRAM_SHAMISEN               ROLAND_GR09_TONE_WIRE_STRING
GM_PROGRAM_KOTO                   ROLAND_GR09_TONE_ELECTRIC_SITAR2
GM_PROGRAM_KALIMBA                ROLAND_GR09_TONE_PLUCK_DOO
GM_PROGRAM_BAG_PIPE               ROLAND_GR09_TONE_HARMONICA
GM_PROGRAM_FIDDLE                 ROLAND_GR09_TONE_FIDDLE
GM_PROGRAM_SHANAI                 ROLAND_GR09_TONE_MUTE_TRUMPET
GM_PROGRAM_TINKLE_BELL            ROLAND_GR09_TONE_TINKLE_BELL
GM_PROGRAM_AGOGO                  ROLAND_GR09_TONE_SYNTH_BELL
GM_PROGRAM_STEEL_DRUMS            ROLAND_GR09_TONE_STEEL_DRUM
GM_PROGRAM_WOODBLOCK              ROLAND_GR09_TONE_TWEETY
GM_PROGRAM_TAIKO_DRUM             ROLAND_GR09_TONE_POP_E_PIANO
GM_PROGRAM_MELODIC_TOM            ROLAND_GR09_TONE_HARP_PAD
GM_PROGRAM_SYNTH_DRUM             ROLAND_GR09_TONE_SYNTH_BELL
GM_PROGRAM_REVERSE_CYMBAL         ROLAND_GR09_TONE_INVERSION
GM_PROGRAM_GUITAR_FRET_NOISE      ROLAND_GR09_TONE_GTR_HARMONICS2
GM_PROGRAM_BREATH_NOISE           ROLAND_GR09_TONE_BREATH
GM_PROGRAM_SEASHORE               ROLAND_GR09_TONE_INVERSION
GM_PROGRAM_BIRD_TWEET             ROLAND_GR09_TONE_MUTE_TRUMPET
GM_PROGRAM_TELEPHONE_RING         ROLAND_GR09_TONE_BRASS_BLUST
GM_PROGRAM_HELICOPTER             ROLAND_GR09_TONE_ALTO_GROWL
GM_PROGRAM_APPLAUSE               ROLAND_GR09_TONE_INVERSION
GM_PROGRAM_GUNSHOT                ROLAND_GR09_TONE_DOUBLE_SCAT
*/
