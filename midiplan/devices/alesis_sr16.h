#ifndef MIDIPLAN_DEVICES_ALESIS_SR16_H
#define MIDIPLAN_DEVICES_ALESIS_SR16_H

#include <midiplan/device.h>

extern const midiplan_device_t alesis_sr16;

#define ALESIS_SR16_RANGE_INVALID (0x00)

// D = Dry
// R = Reverb
// ST = Stereo

// AMB, AMBNT = Ambience
// RM = Room
// HL = Hall
// SN, SNR = Snare
// K, KK, KIK = Kick
// TM = Tom
// FL = Floor
// MD = Medium

// KICKS

#define ALESIS_SR16_HONST_KIK_D          (0x00) // 1
#define ALESIS_SR16_HONST_RM_R_ST        (0x01) // 2
#define ALESIS_SR16_STAB_KIK_D           (0x02) // 3
#define ALESIS_SR16_STAB_RM_R_ST         (0x03) // 4
#define ALESIS_SR16_LO_HONST_D           (0x04) // 5
#define ALESIS_SR16_LO_HNST_RM_R_ST      (0x05) // 6
#define ALESIS_SR16_LO_STAB_D            (0x06) // 7
#define ALESIS_SR16_LO_STAB_RM_R_ST      (0x07) // 8
#define ALESIS_SR16_PURE_KIK_D           (0x08) // 9
#define ALESIS_SR16_OLD_WOOD_D           (0x09) // 10
#define ALESIS_SR16_LOW_WOOD_D           (0x0A) // 11
#define ALESIS_SR16_AMBNT_KIK_R_ST       (0x0B) // 12
#define ALESIS_SR16_ROOM_KIK_1_R_ST      (0x0C) // 13
#define ALESIS_SR16_LO_ROOM_K1_R_ST      (0x0D) // 14
#define ALESIS_SR16_ROOM_KIK_2_R_ST      (0x0E) // 15
#define ALESIS_SR16_LO_ROOM_K2_R_ST      (0x0F) // 16
#define ALESIS_SR16_HI_FOOT_D            (0x10) // 17
#define ALESIS_SR16_LO_FOOT_D            (0x11) // 18
#define ALESIS_SR16_HI_STOMP_D           (0x12) // 19
#define ALESIS_SR16_MD_STOMP_D           (0x13) // 20
#define ALESIS_SR16_LO_STOMP_D           (0x14) // 21
#define ALESIS_SR16_GARAGE_KK_D          (0x15) // 22
#define ALESIS_SR16_HOUSE_KIK_D          (0x16) // 23
#define ALESIS_SR16_RAP_KIK_D            (0x17) // 24
#define ALESIS_SR16_HI_RAP_KIK_D         (0x18) // 25
#define ALESIS_SR16_DBL_HEAD_D           (0x19) // 26
#define ALESIS_SR16_TIGHT_DBL_D          (0x1A) // 27
#define ALESIS_SR16_HEAD_PNCH_D          (0x1B) // 28
#define ALESIS_SR16_BRIT_RM_KK_R_ST      (0x1C) // 29
#define ALESIS_SR16_LOOSE_KIK_D          (0x1D) // 30
#define ALESIS_SR16_BLUE_FOOT_D          (0x1E) // 31
#define ALESIS_SR16_HI_ELECT_D           (0x1F) // 32
#define ALESIS_SR16_ELECTRONC_D          (0x20) // 33
#define ALESIS_SR16_AMBNT_ELC_R_ST       (0x21) // 34
#define ALESIS_SR16_LO_ELECT_D           (0x22) // 35
#define ALESIS_SR16_PUNCH_RM_R_ST        (0x23) // 36
#define ALESIS_SR16_FLABBY_RM_R_ST       (0x24) // 37
#define ALESIS_SR16_WETNFLBY_R_ST        (0x25) // 38
#define ALESIS_SR16_BRT_HALL_R_ST        (0x26) // 39
#define ALESIS_SR16_HALL_FOOT_R_ST       (0x27) // 40
#define ALESIS_SR16_LO_KIK_RM_R_ST       (0x28) // 41
#define ALESIS_SR16_LO_KIK_HL_R_ST       (0x29) // 42
#define ALESIS_SR16_BALLADKK_R_ST        (0x2A) // 43
#define ALESIS_SR16_DBL_HD_RM_R_ST       (0x2B) // 44
#define ALESIS_SR16_LO_DBL_H_RM_R_ST     (0x2C) // 45
#define ALESIS_SR16_SOLID_HL_R_ST        (0x2D) // 46
#define ALESIS_SR16_WET_FLNG_K_R         (0x2E) // 47
#define ALESIS_SR16_BRT_PUNCH_R_ST       (0x2F) // 48
#define ALESIS_SR16_FLNGE_KIK_D          (0x30) // 49

// SNARES

#define ALESIS_SR16_HI_PURE_SN_D         (0x31) // 50
#define ALESIS_SR16_PURE_SNR_D           (0x32) // 51
#define ALESIS_SR16_LO_PURE_SN_D         (0x33) // 52
#define ALESIS_SR16_HI_TRUE_SN_D         (0x34) // 53
#define ALESIS_SR16_TRUE_SNR_D           (0x35) // 54
#define ALESIS_SR16_LO_TRUE_SN_D         (0x36) // 55
#define ALESIS_SR16_ROOM_SNR_R_ST        (0x37) // 56
#define ALESIS_SR16_LO_ROOM_SN_R_ST      (0x38) // 57
#define ALESIS_SR16_HALL_SNR_R_ST        (0x39) // 58
#define ALESIS_SR16_ROOM_SNR_2_R_ST      (0x3A) // 59
#define ALESIS_SR16_LO_RM_SNR_2_R_ST     (0x3B) // 60
#define ALESIS_SR16_SUPER_PIC_D          (0x3C) // 61
#define ALESIS_SR16_SPR_PIC_RM_R_ST      (0x3D) // 62
#define ALESIS_SR16_HI_PICOLO_D          (0x3E) // 63
#define ALESIS_SR16_HI_PIC_RM_R_ST       (0x3F) // 64
#define ALESIS_SR16_LO_PICOLO_D          (0x40) // 65
#define ALESIS_SR16_LO_PIC_RM_R_ST       (0x41) // 66
#define ALESIS_SR16_MED_PIC_RM_R_ST      (0x42) // 67
#define ALESIS_SR16_NASTY_SNR_R_ST       (0x43) // 68
#define ALESIS_SR16_NSTY_SN_RM_R_ST      (0x44) // 69
#define ALESIS_SR16_TRSHY_SNR_R_ST       (0x45) // 70
#define ALESIS_SR16_FRNGE_SNR_R_ST       (0x46) // 71
#define ALESIS_SR16_WET_FLNG_S_R         (0x47) // 72
#define ALESIS_SR16_FLNGE_SNR_D          (0x48) // 73
#define ALESIS_SR16_ALLOY_SNR_R_ST       (0x49) // 74
#define ALESIS_SR16_PLATE_SNR_R_ST       (0x4A) // 75
#define ALESIS_SR16_PLATE_SN_2_R_ST      (0x4B) // 76
#define ALESIS_SR16_PLATE_SN_3_R_ST      (0x4C) // 77
#define ALESIS_SR16_HAMMR_SNR_R_ST       (0x4D) // 78
#define ALESIS_SR16_RIM_2_CNTR_D         (0x4E) // 79
#define ALESIS_SR16_CNTR_2_RIM_D         (0x4F) // 80
#define ALESIS_SR16_HI_RAP_SNR_D         (0x50) // 81
#define ALESIS_SR16_RAP_SNARE_D          (0x51) // 82
#define ALESIS_SR16_LO_RAP_SNR_D         (0x52) // 83
#define ALESIS_SR16_HI_TITE_SN_D         (0x53) // 84
#define ALESIS_SR16_TIGHT_SNR_D          (0x54) // 85
#define ALESIS_SR16_LO_TITE_SN_D         (0x55) // 86
#define ALESIS_SR16_DYNO_RIM_1_D         (0x56) // 87
#define ALESIS_SR16_DYNO_RIM_2_D         (0x57) // 88
#define ALESIS_SR16_LO_DYN_SN_2_D        (0x58) // 89
#define ALESIS_SR16_HI_POP_SHT_R_ST      (0x59) // 90
#define ALESIS_SR16_POP_SHOT_R_ST        (0x5A) // 91
#define ALESIS_SR16_LO_POP_SHT_R_ST      (0x5B) // 92
#define ALESIS_SR16_TECH_GATE_R          (0x5C) // 93
#define ALESIS_SR16_POP_ROOM_R           (0x5D) // 94
#define ALESIS_SR16_BATTER_RM_R_ST       (0x5E) // 95
#define ALESIS_SR16_BRUSH_HIT_D          (0x5F) // 96
#define ALESIS_SR16_MED_BALLAD_R_ST      (0x60) // 97
#define ALESIS_SR16_BIG_BALLAD_R_ST      (0x61) // 98
#define ALESIS_SR16_CHROMESN_R_ST        (0x62) // 99
#define ALESIS_SR16_LO_CHROME_R_ST       (0x63) // 100
#define ALESIS_SR16_DYNO_HL_SN_R_ST      (0x64) // 101
#define ALESIS_SR16_SHOT_ROOM_R_ST       (0x65) // 102
#define ALESIS_SR16_BRT_PIC_RM_R_ST      (0x66) // 103
#define ALESIS_SR16_VERY_NSTY_R_ST       (0x67) // 104
#define ALESIS_SR16_SIDE_STIK_D          (0x68) // 105
#define ALESIS_SR16_WET_SIDE_R_ST        (0x69) // 106
#define ALESIS_SR16_LO_WET_SID_R_ST      (0x6A) // 107
#define ALESIS_SR16_POP_SIDE_R           (0x6B) // 108

// HI HATS

#define ALESIS_SR16_CLOSD_HAT_D          (0x6C) // 109
#define ALESIS_SR16_HARD_HAT_D           (0x6D) // 110
#define ALESIS_SR16_EDGE_HAT_D           (0x6E) // 111
#define ALESIS_SR16_THIN_HAT_D           (0x6F) // 112
#define ALESIS_SR16_TIGHT_HAT_D          (0x70) // 113
#define ALESIS_SR16_SMALL_HAT_D          (0x71) // 114
#define ALESIS_SR16_VARI_HAT_D           (0x72) // 115
#define ALESIS_SR16_WET_HAT_1_R_ST       (0x73) // 116
#define ALESIS_SR16_WET_HAT_2_R_ST       (0x74) // 117
#define ALESIS_SR16_RANDM_HAT_D          (0x75) // 118
#define ALESIS_SR16_WET_RANDM_R_ST       (0x76) // 119
#define ALESIS_SR16_SWEET_HAT_D          (0x77) // 120
#define ALESIS_SR16_OPEN_HAT_D           (0x78) // 121
#define ALESIS_SR16_HALF_HAT_D           (0x79) // 122
#define ALESIS_SR16_OPEN_HAT_2_D         (0x7A) // 123
#define ALESIS_SR16_BAKWRDZ_D            (0x7B) // 124
#define ALESIS_SR16_ST_BKWRDZ_D_ST       (0x7C) // 125
#define ALESIS_SR16_LO_BKWRDZ_D          (0x7D) // 126
#define ALESIS_SR16_BACK_N_4TH_D         (0x7E) // 127

// CYMBALS

#define ALESIS_SR16_SOFT_RIDE_D          (0x7F) // 128
#define ALESIS_SR16_HARD_RIDE_D          (0x80) // 129
#define ALESIS_SR16_LIVE_RIDE_D          (0x81) // 130
#define ALESIS_SR16_LIVE_RID_2_D         (0x82) // 131
#define ALESIS_SR16_RIDE_BELL_D          (0x83) // 132
#define ALESIS_SR16_FLNG_RIDE_D          (0x84) // 133
#define ALESIS_SR16_HI_CRASH_1_D         (0x85) // 134
#define ALESIS_SR16_MD_CRASH_2_D         (0x86) // 135
#define ALESIS_SR16_LO_CRASH_3_D         (0x87) // 136
#define ALESIS_SR16_CMBO_CRSH_D          (0x88) // 137
#define ALESIS_SR16_TRSH_CRSH_D          (0x89) // 138
#define ALESIS_SR16_FLNG_CRSH_D          (0x8A) // 139

// TOMS

#define ALESIS_SR16_HI_TOM_DRY_D         (0x8B) // 140
#define ALESIS_SR16_MD_TOM_DRY_D         (0x8C) // 141
#define ALESIS_SR16_LO_TOM_DRY_D         (0x8D) // 142
#define ALESIS_SR16_FLR_TOM_DRY_D        (0x8E) // 143
#define ALESIS_SR16_LO_FLR_DRY_D         (0x8F) // 144
#define ALESIS_SR16_HI_AMB_TOM_R_ST      (0x90) // 145
#define ALESIS_SR16_MD_AMB_TOM_R_ST      (0x91) // 146
#define ALESIS_SR16_LO_AMB_TOM_R_ST      (0x92) // 147
#define ALESIS_SR16_FLR_AMB_TM_R_ST      (0x93) // 148
#define ALESIS_SR16_LO_AMB_FLR_R_ST      (0x94) // 149
#define ALESIS_SR16_HI_ROOM_TM_R_ST      (0x95) // 150
#define ALESIS_SR16_MD_ROOM_TM_R_ST      (0x96) // 151
#define ALESIS_SR16_LO_ROOM_TM_R_ST      (0x97) // 152
#define ALESIS_SR16_FLR_RM_TOM_R_ST      (0x98) // 153
#define ALESIS_SR16_LO_FLR_RM_R_ST       (0x99) // 154
#define ALESIS_SR16_HI_HALL_TM_R_ST      (0x9A) // 155
#define ALESIS_SR16_MD_HALL_TM_R_ST      (0x9B) // 156
#define ALESIS_SR16_LO_HALL_TM_R_ST      (0x9C) // 157
#define ALESIS_SR16_FLR_HL_TOM_R_ST      (0x9D) // 158
#define ALESIS_SR16_LO_FLR_HL_R_ST       (0x9E) // 159
#define ALESIS_SR16_HI_BIG_HL_R_ST       (0x9F) // 160
#define ALESIS_SR16_MD_BIG_HL_R_ST       (0xA0) // 161
#define ALESIS_SR16_LO_BIG_HL_R_ST       (0xA1) // 162
#define ALESIS_SR16_FLR_BIG_HL_R_ST      (0xA2) // 163
#define ALESIS_SR16_LO_FLRBHL_R_ST       (0xA3) // 164
#define ALESIS_SR16_HI_CANNON_D          (0xA4) // 165
#define ALESIS_SR16_MD_CANNON_D          (0xA5) // 166
#define ALESIS_SR16_LO_CANNON_D          (0xA6) // 167
#define ALESIS_SR16_XLO_CANON_D          (0xA7) // 168
#define ALESIS_SR16_HI_CAN_HL_R_ST       (0xA8) // 169
#define ALESIS_SR16_MD_CAN_HL_R_ST       (0xA9) // 170
#define ALESIS_SR16_LO_CAN_HL_R_ST       (0xAA) // 171
#define ALESIS_SR16_XLO_CAN_HL_R_ST      (0xAB) // 172
#define ALESIS_SR16_HI_ELEC_TM_D         (0xAC) // 173
#define ALESIS_SR16_MD_ELEC_TM_D         (0xAD) // 174
#define ALESIS_SR16_LO_ELEC_TM_D         (0xAE) // 175
#define ALESIS_SR16_HI_SUPR_TM_R_ST      (0xAF) // 176
#define ALESIS_SR16_MD_SUPR_TM_R_ST      (0xB0) // 177
#define ALESIS_SR16_LO_SUPR_TM_R_ST      (0xB1) // 178
#define ALESIS_SR16_XL_SUPR_TM_R_ST      (0xB2) // 179
#define ALESIS_SR16_HI_FLAT_TM_D         (0xB3) // 180
#define ALESIS_SR16_MD_FLAT_TM_D         (0xB4) // 181
#define ALESIS_SR16_LO_FLAT_TM_D         (0xB5) // 182
#define ALESIS_SR16_HI_FLAT_RM_R_ST      (0xB6) // 183
#define ALESIS_SR16_MD_FLAT_RM_R_ST      (0xB7) // 184
#define ALESIS_SR16_LO_FLAT_RM_R_ST      (0xB8) // 185
#define ALESIS_SR16_HI_FLAT_HL_R_ST      (0xB9) // 186
#define ALESIS_SR16_MD_FLAT_HL_R_ST      (0xBA) // 187
#define ALESIS_SR16_LO_FLAT_HL_R_ST      (0xBB) // 188
#define ALESIS_SR16_HI_FLNG_TM_D         (0xBC) // 189
#define ALESIS_SR16_MD_FLNG_TM_D         (0xBD) // 190
#define ALESIS_SR16_LO_FLNG_TM_D         (0xBE) // 191

// PERCUSSION

#define ALESIS_SR16_TAMBORNE_D           (0xBF) // 192
#define ALESIS_SR16_SHAKER_D             (0xC0) // 193
#define ALESIS_SR16_DYN_CONGA_D          (0xC1) // 194
#define ALESIS_SR16_LO_DYN_CGA_D         (0xC2) // 195
#define ALESIS_SR16_HI_CONGA_D           (0xC3) // 196
#define ALESIS_SR16_LO_CONGA_D           (0xC4) // 197
#define ALESIS_SR16_HI_CGA_SLP_D         (0xC5) // 198
#define ALESIS_SR16_LO_CGA_SLP_D         (0xC6) // 199
#define ALESIS_SR16_HI_TIMBLI_D          (0xC7) // 200
#define ALESIS_SR16_MD_TIMBLI_D          (0xC8) // 201
#define ALESIS_SR16_LO_TIMBLI_D          (0xC9) // 202
#define ALESIS_SR16_HI_AGOGO_D           (0xCA) // 203
#define ALESIS_SR16_LO_AGOGO_D           (0xCB) // 204
#define ALESIS_SR16_HI_CLAVE_D           (0xCC) // 205
#define ALESIS_SR16_LO_CLAVE_D           (0xCD) // 206
#define ALESIS_SR16_WET_CLAVE_R_ST       (0xCE) // 207
#define ALESIS_SR16_HI_COW_BEL_D         (0xCF) // 208
#define ALESIS_SR16_MD_COW_BEL_D         (0xD0) // 209
#define ALESIS_SR16_LO_COW_BEL_D         (0xD1) // 210
#define ALESIS_SR16_HI_RAP_COW_D         (0xD2) // 211
#define ALESIS_SR16_MD_RAP_COW_D         (0xD3) // 212
#define ALESIS_SR16_LO_RAP_COW_D         (0xD4) // 213
#define ALESIS_SR16_HI_BLOCK_D           (0xD5) // 214
#define ALESIS_SR16_MD_BLOCK_D           (0xD6) // 215
#define ALESIS_SR16_LO_BLOCK_D           (0xD7) // 216
#define ALESIS_SR16_FNGR_SNAP_D          (0xD8) // 217
#define ALESIS_SR16_WIDE_FNGR_D_ST       (0xD9) // 218
#define ALESIS_SR16_FISH_STIK_D          (0xDA) // 219
#define ALESIS_SR16_LO_FISH_D            (0xDB) // 220
#define ALESIS_SR16_FROG_FISH_D_ST       (0xDC) // 221
#define ALESIS_SR16_HI_CLAPS_R           (0xDD) // 222
#define ALESIS_SR16_LO_CLAPS_R           (0xDE) // 223
#define ALESIS_SR16_TRIANGLE_D           (0xDF) // 224
#define ALESIS_SR16_CABASA_D             (0xE0) // 225
#define ALESIS_SR16_HI_STICKS_D          (0xE1) // 226
#define ALESIS_SR16_LO_STICKS_D          (0xE2) // 227
#define ALESIS_SR16_BAMBOO_D             (0xE3) // 228
#define ALESIS_SR16_BMBO_CMBO_D_ST       (0xE4) // 229
#define ALESIS_SR16_COLD_BLOK_R          (0xE5) // 230
#define ALESIS_SR16_SMPL_N_HLD_D_ST      (0xE6) // 231
#define ALESIS_SR16_FIRE_CRKR_R_ST       (0xE7) // 232
#define ALESIS_SR16_IMPACT_R_ST          (0xE8) // 233

#endif
