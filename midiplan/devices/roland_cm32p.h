#ifndef MIDIPLAN_DEVICES_ROLAND_CM32P_H
#define MIDIPLAN_DEVICES_ROLAND_CM32P_H

#include <midiplan/device.h>

extern const midiplan_device_t roland_cm32p;

#define ROLAND_CM32P_LOWEST_NOTE      (0)
#define ROLAND_CM32P_MIDDLE_C        (60)
#define ROLAND_CM32P_HIGHEST_NOTE   (127)

#define ROLAND_CM32P_RANGE_INVALID       (0x00)
#define ROLAND_CM32P_RANGE_PROG_66       (0x01)
#define ROLAND_CM32P_RANGE_HARM_66       (0x02)
#define ROLAND_CM32P_RANGE_PROG_61       (0x03)
#define ROLAND_CM32P_RANGE_HARM_61       (0x04)
#define ROLAND_CM32P_RANGE_PROG_73       (0x05)
#define ROLAND_CM32P_RANGE_HARM_73       (0x06)
#define ROLAND_CM32P_RANGE_PROG_87       (0x07)
#define ROLAND_CM32P_RANGE_HARM_87       (0x08)
#define ROLAND_CM32P_RANGE_OCTAVE_HIGHER (0x09)
#define ROLAND_CM32P_RANGE_OCTAVE_LOWER  (0x0A)
#define ROLAND_CM32P_RANGE_DEFAULT       (0x0F)

#define ROLAND_CM32P_A_PIANO_1     (0x00) // 01
#define ROLAND_CM32P_A_PIANO_2     (0x01) // 02
#define ROLAND_CM32P_A_PIANO_3     (0x02) // 03
#define ROLAND_CM32P_A_PIANO_4     (0x03) // 04
#define ROLAND_CM32P_A_PIANO_5     (0x04) // 05
#define ROLAND_CM32P_A_PIANO_7     (0x05) // 06
#define ROLAND_CM32P_A_PIANO_9     (0x06) // 07
#define ROLAND_CM32P_E_PIANO_1     (0x07) // 08
#define ROLAND_CM32P_E_PIANO_3     (0x08) // 09
#define ROLAND_CM32P_E_PIANO_5     (0x09) // 10
#define ROLAND_CM32P_A_GUITAR_1    (0x0A) // 11
#define ROLAND_CM32P_A_GUITAR_3    (0x0B) // 12
#define ROLAND_CM32P_A_GUITAR_4    (0x0C) // 13
#define ROLAND_CM32P_E_GUITAR_1    (0x0D) // 14 V-SW, ignored
#define ROLAND_CM32P_E_GUITAR_2    (0x0E) // 15
#define ROLAND_CM32P_SLAP_3        (0x0F) // 16 harmonics after >= 66
#define ROLAND_CM32P_SLAP_4        (0x10) // 17 harmonics after >= 66
#define ROLAND_CM32P_SLAP_5        (0x11) // 18 V-SW, ignored
#define ROLAND_CM32P_SLAP_6        (0x12) // 19 V-SW, ignored
#define ROLAND_CM32P_SLAP_9        (0x13) // 20 harmonics after >= 61
#define ROLAND_CM32P_SLAP_10       (0x14) // 21 harmonics after >= 61
#define ROLAND_CM32P_SLAP_11       (0x15) // 22 V-SW, ignored
#define ROLAND_CM32P_SLAP_12       (0x16) // 23 V-SW, ignored
#define ROLAND_CM32P_FINGERED_1    (0x17) // 24 harmonics after >= 73
#define ROLAND_CM32P_FINGERED_2    (0x18) // 25 harmonics after >= 73
#define ROLAND_CM32P_PICKED_1      (0x19) // 26
#define ROLAND_CM32P_PICKED_2      (0x1A) // 27
#define ROLAND_CM32P_FRETLESS_1    (0x1B) // 28 harmonics after >= 87
#define ROLAND_CM32P_AC_BASS       (0x1C) // 29
#define ROLAND_CM32P_CHOIR_1       (0x1D) // 30
#define ROLAND_CM32P_CHOIR_2       (0x1E) // 31
#define ROLAND_CM32P_CHOIR_3       (0x1F) // 32
#define ROLAND_CM32P_CHOIR_4       (0x20) // 33
#define ROLAND_CM32P_STRINGS_1     (0x21) // 34
#define ROLAND_CM32P_STRINGS_2     (0x22) // 35
#define ROLAND_CM32P_STRINGS_3     (0x23) // 36
#define ROLAND_CM32P_STRINGS_4     (0x24) // 37
#define ROLAND_CM32P_E_ORGAN_2     (0x25) // 38
#define ROLAND_CM32P_E_ORGAN_4     (0x26) // 39
#define ROLAND_CM32P_E_ORGAN_6     (0x27) // 40
#define ROLAND_CM32P_E_ORGAN_8     (0x28) // 41
#define ROLAND_CM32P_E_ORGAN_9     (0x29) // 42
#define ROLAND_CM32P_E_ORGAN_10    (0x2A) // 43
#define ROLAND_CM32P_E_ORGAN_11    (0x2B) // 44
#define ROLAND_CM32P_E_ORGAN_12    (0x2C) // 45
#define ROLAND_CM32P_E_ORGAN_13    (0x2D) // 46
#define ROLAND_CM32P_SOFT_TP_1     (0x2E) // 47
#define ROLAND_CM32P_SOFT_TP_3     (0x2F) // 48
#define ROLAND_CM32P_TP_TRB_1      (0x30) // 49
#define ROLAND_CM32P_TP_TRB_2      (0x31) // 50
#define ROLAND_CM32P_TP_TRB_3      (0x32) // 51
#define ROLAND_CM32P_TP_TRB_4      (0x33) // 52
#define ROLAND_CM32P_TP_TRB_5      (0x34) // 53
#define ROLAND_CM32P_TP_TRB_6      (0x35) // 54
#define ROLAND_CM32P_SAX_1         (0x36) // 55
#define ROLAND_CM32P_SAX_2         (0x37) // 56
#define ROLAND_CM32P_SAX_3         (0x38) // 57
#define ROLAND_CM32P_SAX_5         (0x39) // 58
#define ROLAND_CM32P_BRASS_1       (0x3A) // 59
#define ROLAND_CM32P_BRASS_2       (0x3B) // 60
#define ROLAND_CM32P_BRASS_3       (0x3C) // 61
#define ROLAND_CM32P_BRASS_4       (0x3D) // 62
#define ROLAND_CM32P_BRASS_5       (0x3E) // 63
#define ROLAND_CM32P_ORCHE_HIT     (0x3F) // 64

#endif
