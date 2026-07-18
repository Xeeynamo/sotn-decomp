// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

static s16 D_pspeu_09277C50[4];
static s16 D_pspeu_09277C58[4];
static s16 D_pspeu_09277C60[4];
static s16 D_pspeu_09277C68[4];
static s16 D_pspeu_09277C70[4];
static s16 D_pspeu_09277C78[4];
static s16 D_pspeu_09277C80[4];
static s16 D_pspeu_09277C88[4];
static s16 D_pspeu_09277C90[4];
static s16 D_pspeu_09277C98[4];
static s16 D_pspeu_09277CA0[4];
static s16 D_pspeu_09277CA8[4];
static s16 D_pspeu_09277CB0[4];
static s16 D_pspeu_09277CB8[4];
static s16 D_pspeu_09277CC0[4];
static s16 D_pspeu_09277CC8[4];
static s16 D_pspeu_09277CD0[4];
static s16 D_pspeu_09277CD8[4];
static s16 D_pspeu_09277CE0[4];
static s16 D_pspeu_09277CE8[4];
static s16 D_pspeu_09277CF0[4];
static s16 D_pspeu_09277CF8[4];
static s16 D_pspeu_09277D00[4];
static s16 D_pspeu_09277D08[4];
static s16 D_pspeu_09277D10[4];
static s16 D_pspeu_09277D18[4];
static s16 D_pspeu_09277D20[4];
static s16 D_pspeu_09277D28[4];
static s16 D_pspeu_09277D30[4];
static s16 D_pspeu_09277D38[4];
static s16 D_pspeu_09277D40[4];
static s16 D_pspeu_09277D48[4];
static s16 D_pspeu_09277D50[4];
static s16 D_pspeu_09277D58[4];
static s16 D_pspeu_09277D60[4];
static s16 D_pspeu_09277D68[4];
static s16 D_pspeu_09277D70[4];
static s16 D_pspeu_09277D78[4];
static s16 D_pspeu_09277D80[4];
static s16 D_pspeu_09277D88[4];
static s16 D_pspeu_09277D90[4];
static s16 D_pspeu_09277D98[4];
static s16 D_pspeu_09277DA0[4];
static s16 D_pspeu_09277DA8[4];
static s16 D_pspeu_09277DB0[4];
static s16 D_pspeu_09277DB8[4];
static s16 D_pspeu_09277DC0[4];
static s16 D_pspeu_09277DC8[4];
static s16 D_pspeu_09277DD0[4];
static s16 D_pspeu_09277DD8[4];
static s16 D_pspeu_09277DE0[4];
static s16 D_pspeu_09277DE8[4];
static s16 D_pspeu_09277DF0[4];
static s16 D_pspeu_09277DF8[4];
static s16 D_pspeu_09277E00[4];
static s16 D_pspeu_09277E08[4];
static s16 D_pspeu_09277E10[4];
static s16 D_pspeu_09277E18[4];
static s16 D_pspeu_09277E20[4];
static s16 D_pspeu_09277E28[4];
static s16 D_pspeu_09277E30[4];
static s16 D_pspeu_09277E38[4];
static s16 D_pspeu_09277E40[4];
static s16 D_pspeu_09277E48[4];
static s16 D_pspeu_09277E50[4];
static s16 D_pspeu_09277E58[4];
static s16 D_pspeu_09277E60[4];
static s16 D_pspeu_09277E68[4];
static s16 D_pspeu_09277E70[4];
static s16 D_pspeu_09277E78[4];
static s16 D_pspeu_09277E80[4];
static s16 D_pspeu_09277E88[4];
static s16 D_pspeu_09277E90[4];
static s16 D_pspeu_09277E98[4];
static s16 D_pspeu_09277EA0[4];
static s16 D_pspeu_09277EA8[4];
static s16 D_pspeu_09277EB0[4];
static s16 D_pspeu_09277EB8[4];
static s16 D_pspeu_09277EC0[4];
static s16 D_pspeu_09277EC8[4];
static s16 D_pspeu_09277ED0[4];
static s16 D_pspeu_09277ED8[4];
static s16 D_pspeu_09277EE0[4];
static s16 D_pspeu_09277EE8[4];
static s16 D_pspeu_09277EF0[4];
static s16 D_pspeu_09277EF8[4];
static s16 D_pspeu_09277F00[4];
static s16 D_pspeu_09277F08[4];
static s16 D_pspeu_09277F10[4];
static s16 D_pspeu_09277F18[4];
static s16 D_pspeu_09277F20[4];
static s16 D_pspeu_09277F28[4];
static s16 D_pspeu_09277F30[4];
static s16 D_pspeu_09277F38[4];
static s16 D_pspeu_09277F40[4];
static s16 D_pspeu_09277F48[4];
static s16 D_pspeu_09277F50[4];
static s16 D_pspeu_09277F58[4];
static s16 D_pspeu_09277F60[4];
static s16 D_pspeu_09277F68[4];
static s16 D_pspeu_09277F70[4];
static s16 D_pspeu_09277F78[4];
static s16 D_pspeu_09277F80[4];
static s16 D_pspeu_09277F88[4];
static s16 D_pspeu_09277F90[4];
static s16 D_pspeu_09277F98[4];
static s16 D_pspeu_09277FA0[4];
static s16 D_pspeu_09277FA8[4];
static s16 D_pspeu_09277FB0[4];
static s16 D_pspeu_09277FB8[4];
static s16 D_pspeu_09277FC0[4];
static s16 D_pspeu_09277FC8[4];
static s16 D_pspeu_09277FD0[4];
static s16 D_pspeu_09277FD8[4];
static s16 D_pspeu_09277FE0[4];
static s16 D_pspeu_09277FE8[4];
static s16 D_pspeu_09277FF0[4];
static s16 D_pspeu_09277FF8[4];
static s16 D_pspeu_09278000[4];
static s16 D_pspeu_09278008[4];
static s16 D_pspeu_09278010[4];
static s16 D_pspeu_09278018[4];
static s16 D_pspeu_09278020[4];
s16* maria_spr[] = {
    NULL,
    D_pspeu_09277C50,
    D_pspeu_09277C58,
    D_pspeu_09277C60,
    D_pspeu_09277C68,
    D_pspeu_09277C70,
    D_pspeu_09277C78,
    D_pspeu_09277C80,
    D_pspeu_09277C88,
    D_pspeu_09277C90,
    D_pspeu_09277C98,
    D_pspeu_09277CA0,
    D_pspeu_09277CA8,
    D_pspeu_09277CB0,
    D_pspeu_09277CB8,
    D_pspeu_09277CC0,
    D_pspeu_09277CC8,
    D_pspeu_09277CD0,
    D_pspeu_09277CD8,
    D_pspeu_09277CE0,
    D_pspeu_09277CE8,
    D_pspeu_09277CF0,
    D_pspeu_09277CF8,
    D_pspeu_09277D00,
    D_pspeu_09277D08,
    D_pspeu_09277D10,
    D_pspeu_09277D18,
    D_pspeu_09277D20,
    D_pspeu_09277D28,
    D_pspeu_09277D30,
    D_pspeu_09277D38,
    D_pspeu_09277D40,
    D_pspeu_09277D48,
    D_pspeu_09277D50,
    D_pspeu_09277D58,
    D_pspeu_09277D60,
    D_pspeu_09277D68,
    D_pspeu_09277D70,
    D_pspeu_09277D78,
    D_pspeu_09277D80,
    D_pspeu_09277D88,
    D_pspeu_09277D90,
    D_pspeu_09277D98,
    D_pspeu_09277DA0,
    D_pspeu_09277DA8,
    D_pspeu_09277DB0,
    D_pspeu_09277DB8,
    D_pspeu_09277DC0,
    D_pspeu_09277DC8,
    D_pspeu_09277DD0,
    D_pspeu_09277DD8,
    D_pspeu_09277DE0,
    D_pspeu_09277DE8,
    D_pspeu_09277DF0,
    D_pspeu_09277DF8,
    D_pspeu_09277E00,
    D_pspeu_09277E08,
    D_pspeu_09277E10,
    D_pspeu_09277E18,
    D_pspeu_09277E20,
    D_pspeu_09277E28,
    D_pspeu_09277E30,
    D_pspeu_09277E38,
    D_pspeu_09277E40,
    D_pspeu_09277E48,
    D_pspeu_09277E50,
    D_pspeu_09277E58,
    D_pspeu_09277E60,
    D_pspeu_09277E68,
    D_pspeu_09277E70,
    D_pspeu_09277E78,
    D_pspeu_09277E80,
    D_pspeu_09277E88,
    D_pspeu_09277E90,
    D_pspeu_09277E98,
    D_pspeu_09277EA0,
    D_pspeu_09277EA8,
    D_pspeu_09277EB0,
    D_pspeu_09277EB8,
    D_pspeu_09277EC0,
    D_pspeu_09277EC8,
    D_pspeu_09277ED0,
    D_pspeu_09277ED8,
    D_pspeu_09277EE0,
    D_pspeu_09277EE8,
    D_pspeu_09277EF0,
    D_pspeu_09277EF8,
    D_pspeu_09277F00,
    D_pspeu_09277F08,
    D_pspeu_09277F10,
    D_pspeu_09277F18,
    D_pspeu_09277F20,
    D_pspeu_09277F28,
    D_pspeu_09277F30,
    D_pspeu_09277F38,
    D_pspeu_09277F40,
    D_pspeu_09277F48,
    D_pspeu_09277F50,
    D_pspeu_09277F58,
    D_pspeu_09277F60,
    D_pspeu_09277F68,
    D_pspeu_09277F70,
    D_pspeu_09277F78,
    D_pspeu_09277F80,
    D_pspeu_09277F88,
    D_pspeu_09277F90,
    D_pspeu_09277F98,
    D_pspeu_09277FA0,
    D_pspeu_09277FA8,
    D_pspeu_09277FB0,
    D_pspeu_09277FB8,
    D_pspeu_09277FC0,
    D_pspeu_09277FC8,
    D_pspeu_09277FD0,
    D_pspeu_09277FD8,
    D_pspeu_09277FE0,
    D_pspeu_09277FE8,
    D_pspeu_09277FF0,
    D_pspeu_09277FF8,
    D_pspeu_09278000,
    D_pspeu_09278008,
    D_pspeu_09278010,
    D_pspeu_09278018,
    D_pspeu_09278020,
    NULL};

static s16 D_pspeu_09277C50[] = {0x00 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277C58[] = {0x01 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277C60[] = {0x02 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277C68[] = {0x03 | 0x8000, -12, -24, 0};
static s16 D_pspeu_09277C70[] = {0x04 | 0x8000, -12, -15, 0};
static s16 D_pspeu_09277C78[] = {0x05 | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277C80[] = {0x06 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277C88[] = {0x07 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277C90[] = {0x08 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277C98[] = {0x09 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277CA0[] = {0x09 | 0x8000, -11, -23, 0};
static s16 D_pspeu_09277CA8[] = {0x0A | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CB0[] = {0x0B | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CB8[] = {0x0C | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CC0[] = {0x0D | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CC8[] = {0x0E | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CD0[] = {0x0F | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CD8[] = {0x10 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CE0[] = {0x11 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CE8[] = {0x12 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CF0[] = {0x13 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277CF8[] = {0x14 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277D00[] = {0x15 | 0x8000, -11, -23, 0};
static s16 D_pspeu_09277D08[] = {0x16 | 0x8000, -11, -23, 0};
static s16 D_pspeu_09277D10[] = {0x17 | 0x8000, -11, -23, 0};
static s16 D_pspeu_09277D18[] = {0x18 | 0x8000, -10, -23, 0};
static s16 D_pspeu_09277D20[] = {0x19 | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277D28[] = {0x1A | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277D30[] = {0x1B | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277D38[] = {0x1C | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277D40[] = {0x1D | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277D48[] = {0x1E | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277D50[] = {0x1F | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277D58[] = {0x20 | 0x8000, -10, -23, 0};
static s16 D_pspeu_09277D60[] = {0x21 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277D68[] = {0x22 | 0x8000, -10, -23, 0};
static s16 D_pspeu_09277D70[] = {0x23 | 0x8000, -10, -23, 0};
static s16 D_pspeu_09277D78[] = {0x24 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277D80[] = {0x25 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277D88[] = {0x26 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277D90[] = {0x27 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277D98[] = {0x28 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277DA0[] = {0x29 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277DA8[] = {0x2A | 0x8000, -24, -33, 0};
static s16 D_pspeu_09277DB0[] = {0x2B | 0x8000, -24, -33, 0};
static s16 D_pspeu_09277DB8[] = {0x2C | 0x8000, -13, -37, 0};
static s16 D_pspeu_09277DC0[] = {0x2D | 0x8000, -13, -37, 0};
static s16 D_pspeu_09277DC8[] = {0x2E | 0x8000, -13, -37, 0};
static s16 D_pspeu_09277DD0[] = {0x2F | 0x8000, -13, -37, 0};
static s16 D_pspeu_09277DD8[] = {0x30 | 0x8000, -19, -17, 0};
static s16 D_pspeu_09277DE0[] = {0x31 | 0x8000, -19, -17, 0};
static s16 D_pspeu_09277DE8[] = {0x32 | 0x8000, -19, -17, 0};
static s16 D_pspeu_09277DF0[] = {0x33 | 0x8000, -19, -17, 0};
static s16 D_pspeu_09277DF8[] = {0x34 | 0x8000, -28, -6, 0};
static s16 D_pspeu_09277E00[] = {0x35 | 0x8000, -27, -6, 0};
static s16 D_pspeu_09277E08[] = {0x36 | 0x8000, -19, -24, 0};
static s16 D_pspeu_09277E10[] = {0x37 | 0x8000, -24, -23, 0};
static s16 D_pspeu_09277E18[] = {0x38 | 0x8000, -24, -22, 0};
static s16 D_pspeu_09277E20[] = {0x39 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277E28[] = {0x3A | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277E30[] = {0x3B | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277E38[] = {0x3C | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277E40[] = {0x3D | 0x8000, -21, -19, 0};
static s16 D_pspeu_09277E48[] = {0x3E | 0x8000, -21, -27, 0};
static s16 D_pspeu_09277E50[] = {0x3F | 0x8000, -20, -27, 0};
static s16 D_pspeu_09277E58[] = {0x40 | 0x8000, -21, -27, 0};
static s16 D_pspeu_09277E60[] = {0x40 | 0x8000, -22, -27, 0};
static s16 D_pspeu_09277E68[] = {0x41 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E70[] = {0x42 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E78[] = {0x43 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E80[] = {0x44 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E88[] = {0x45 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E90[] = {0x46 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277E98[] = {0x47 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277EA0[] = {0x48 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277EA8[] = {0x49 | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277EB0[] = {0x4A | 0x8000, -12, -23, 0};
static s16 D_pspeu_09277EB8[] = {0x4B | 0x8000, -14, -21, 0};
static s16 D_pspeu_09277EC0[] = {0x4C | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277EC8[] = {0x4D | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277ED0[] = {0x4E | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277ED8[] = {0x4F | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277EE0[] = {0x50 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277EE8[] = {0x51 | 0x8000, -24, -24, 0};
static s16 D_pspeu_09277EF0[] = {0x52 | 0x8000, -17, -9, 0};
static s16 D_pspeu_09277EF8[] = {0x53 | 0x8000, -17, -9, 0};
static s16 D_pspeu_09277F00[] = {0x54 | 0x8000, -16, -9, 0};
static s16 D_pspeu_09277F08[] = {0x55 | 0x8000, -17, -9, 0};
static s16 D_pspeu_09277F10[] = {0x55 | 0x8000, -18, -9, 0};
static s16 D_pspeu_09277F18[] = {0x56 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277F20[] = {0x57 | 0x8000, -15, -24, 0};
static s16 D_pspeu_09277F28[] = {0x58 | 0x8000, -21, -37, 0};
static s16 D_pspeu_09277F30[] = {0x58 | 0x8000, -20, -37, 0};
static s16 D_pspeu_09277F38[] = {0x59 | 0x8000, -8, -24, 0};
static s16 D_pspeu_09277F40[] = {0x5A | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277F48[] = {0x5B | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277F50[] = {0x5C | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277F58[] = {0x5D | 0x8000, -21, -19, 0};
static s16 D_pspeu_09277F60[] = {0x5E | 0x8000, -21, -19, 0};
static s16 D_pspeu_09277F68[] = {0x5F | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F70[] = {0x60 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F78[] = {0x61 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F80[] = {0x62 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F88[] = {0x63 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F90[] = {0x64 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277F98[] = {0x65 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277FA0[] = {0x66 | 0x8000, -20, -21, 0};
static s16 D_pspeu_09277FA8[] = {0x04 | 0x8000, -12, -15, 0};
static s16 D_pspeu_09277FB0[] = {0x67 | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277FB8[] = {0x68 | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277FC0[] = {0x05 | 0x8000, -12, -7, 0};
static s16 D_pspeu_09277FC8[] = {0x57 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277FD0[] = {0x69 | 0x8000, -16, -24, 0};
static s16 D_pspeu_09277FD8[] = {0x6A | 0x8000, -16, -19, 0};
static s16 D_pspeu_09277FE0[] = {0x6B | 0x8000, -25, -22, 0};
static s16 D_pspeu_09277FE8[] = {0x6C | 0x8000, -16, -23, 0};
static s16 D_pspeu_09277FF0[] = {0x6D | 0x8000, -24, -23, 0};
static s16 D_pspeu_09277FF8[] = {0x6E | 0x8000, -24, -23, 0};
static s16 D_pspeu_09278000[] = {0x6F | 0x8000, -12, -45, 0};
static s16 D_pspeu_09278008[] = {0x70 | 0x8000, -12, -45, 0};
static s16 D_pspeu_09278010[] = {0x71 | 0x8000, -12, -45, 0};
static s16 D_pspeu_09278018[] = {0x72 | 0x8000, -12, -45, 0};
static s16 D_pspeu_09278020[] = {0x73 | 0x8000, -12, -45, 0};
