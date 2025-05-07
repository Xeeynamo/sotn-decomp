// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

static s16 D_pspeu_092C6078[4];
static s16 D_pspeu_092C6080[4];
static s16 D_pspeu_092C6088[4];
static s16 D_pspeu_092C6090[4];
static s16 D_pspeu_092C6098[4];
static s16 D_pspeu_092C60A0[4];
static s16 D_pspeu_092C60A8[4];
static s16 D_pspeu_092C60B0[4];
static s16 D_pspeu_092C60B8[4];
static s16 D_pspeu_092C60C0[4];
static s16 D_pspeu_092C60C8[4];
static s16 D_pspeu_092C60D0[4];
static s16 D_pspeu_092C60D8[4];
static s16 D_pspeu_092C60E0[4];
static s16 D_pspeu_092C60E8[4];
static s16 D_pspeu_092C60F0[4];
static s16 D_pspeu_092C60F8[4];
static s16 D_pspeu_092C6100[4];
static s16 D_pspeu_092C6108[4];
static s16 D_pspeu_092C6110[4];
static s16 D_pspeu_092C6118[4];
static s16 D_pspeu_092C6120[4];
static s16 D_pspeu_092C6128[4];
static s16 D_pspeu_092C6130[4];
static s16 D_pspeu_092C6138[4];
static s16 D_pspeu_092C6140[4];
static s16 D_pspeu_092C6148[4];
static s16 D_pspeu_092C6150[4];
static s16 D_pspeu_092C6158[4];
static s16 D_pspeu_092C6160[4];
static s16 D_pspeu_092C6168[4];
static s16 D_pspeu_092C6170[4];
static s16 D_pspeu_092C6178[4];
static s16 D_pspeu_092C6180[4];
static s16 D_pspeu_092C6188[4];
static s16 D_pspeu_092C6190[4];
static s16 D_pspeu_092C6198[4];
static s16 D_pspeu_092C61A0[4];
static s16 D_pspeu_092C61A8[4];
static s16 D_pspeu_092C61B0[4];
static s16 D_pspeu_092C61B8[4];
static s16 D_pspeu_092C61C0[4];
static s16 D_pspeu_092C61C8[4];
static s16 D_pspeu_092C61D0[4];
static s16 D_pspeu_092C61D8[4];
static s16 D_pspeu_092C61E0[4];
static s16 D_pspeu_092C61E8[4];
static s16 D_pspeu_092C61F0[4];
static s16 D_pspeu_092C61F8[4];
static s16 D_pspeu_092C6200[4];
static s16 D_pspeu_092C6208[4];
static s16 D_pspeu_092C6210[4];
static s16 D_pspeu_092C6218[4];
static s16 D_pspeu_092C6220[4];
static s16 D_pspeu_092C6228[4];
static s16 D_pspeu_092C6230[4];
static s16 D_pspeu_092C6238[4];
static s16 D_pspeu_092C6240[4];
static s16 D_pspeu_092C6248[4];
static s16 D_pspeu_092C6250[4];
static s16 D_pspeu_092C6258[4];
static s16 D_pspeu_092C6260[4];
static s16 D_pspeu_092C6268[4];
static s16 D_pspeu_092C6270[4];
static s16 D_pspeu_092C6278[4];
static s16 D_pspeu_092C6280[4];
static s16 D_pspeu_092C6288[4];
static s16 D_pspeu_092C6290[4];
static s16 D_pspeu_092C6298[4];
static s16 D_pspeu_092C62A0[4];
static s16 D_pspeu_092C62A8[4];
static s16 D_pspeu_092C62B0[4];
static s16 D_pspeu_092C62B8[4];
static s16 D_pspeu_092C62C0[4];
static s16 D_pspeu_092C62C8[4];
static s16 D_pspeu_092C62D0[4];
static s16 D_pspeu_092C62D8[4];
static s16 D_pspeu_092C62E0[4];
static s16 D_pspeu_092C62E8[4];
static s16 D_pspeu_092C62F0[4];
static s16 D_pspeu_092C62F8[4];
static s16 D_pspeu_092C6300[4];
static s16 D_pspeu_092C6308[4];
static s16 D_pspeu_092C6310[4];
static s16 D_pspeu_092C6318[4];
static s16 D_pspeu_092C6320[4];
static s16 D_pspeu_092C6328[4];
static s16 D_pspeu_092C6330[4];
static s16 D_pspeu_092C6338[4];
static s16 D_pspeu_092C6340[4];
static s16 D_pspeu_092C6348[4];
static s16 D_pspeu_092C6350[4];
static s16 D_pspeu_092C6358[4];
static s16 D_pspeu_092C6360[4];
static s16 D_pspeu_092C6368[4];
static s16 D_pspeu_092C6370[4];
static s16 D_pspeu_092C6378[4];
static s16 D_pspeu_092C6380[4];
static s16 D_pspeu_092C6388[4];
static s16 D_pspeu_092C6390[4];
static s16 D_pspeu_092C6398[4];
static s16 D_pspeu_092C63A0[4];
static s16 D_pspeu_092C63A8[4];
static s16 D_pspeu_092C63B0[4];
static s16 D_pspeu_092C63B8[4];
static s16 D_pspeu_092C63C0[4];
static s16 D_pspeu_092C63C8[4];
static s16 D_pspeu_092C63D0[4];
static s16 D_pspeu_092C63D8[4];
static s16 D_pspeu_092C63E0[4];
static s16 D_pspeu_092C63E8[4];
static s16 D_pspeu_092C63F0[4];
static s16 D_pspeu_092C63F8[4];
static s16 D_pspeu_092C6400[4];
static s16 D_pspeu_092C6408[4];
static s16 D_pspeu_092C6410[4];
static s16 D_pspeu_092C6418[4];
static s16 D_pspeu_092C6420[4];
static s16 D_pspeu_092C6428[4];
static s16 D_pspeu_092C6430[4];
static s16 D_pspeu_092C6438[4];
static s16 D_pspeu_092C6440[4];
static s16 D_pspeu_092C6448[4];
s16* mar_801530AC[] = {
    NULL,
    D_pspeu_092C6078,
    D_pspeu_092C6080,
    D_pspeu_092C6088,
    D_pspeu_092C6090,
    D_pspeu_092C6098,
    D_pspeu_092C60A0,
    D_pspeu_092C60A8,
    D_pspeu_092C60B0,
    D_pspeu_092C60B8,
    D_pspeu_092C60C0,
    D_pspeu_092C60C8,
    D_pspeu_092C60D0,
    D_pspeu_092C60D8,
    D_pspeu_092C60E0,
    D_pspeu_092C60E8,
    D_pspeu_092C60F0,
    D_pspeu_092C60F8,
    D_pspeu_092C6100,
    D_pspeu_092C6108,
    D_pspeu_092C6110,
    D_pspeu_092C6118,
    D_pspeu_092C6120,
    D_pspeu_092C6128,
    D_pspeu_092C6130,
    D_pspeu_092C6138,
    D_pspeu_092C6140,
    D_pspeu_092C6148,
    D_pspeu_092C6150,
    D_pspeu_092C6158,
    D_pspeu_092C6160,
    D_pspeu_092C6168,
    D_pspeu_092C6170,
    D_pspeu_092C6178,
    D_pspeu_092C6180,
    D_pspeu_092C6188,
    D_pspeu_092C6190,
    D_pspeu_092C6198,
    D_pspeu_092C61A0,
    D_pspeu_092C61A8,
    D_pspeu_092C61B0,
    D_pspeu_092C61B8,
    D_pspeu_092C61C0,
    D_pspeu_092C61C8,
    D_pspeu_092C61D0,
    D_pspeu_092C61D8,
    D_pspeu_092C61E0,
    D_pspeu_092C61E8,
    D_pspeu_092C61F0,
    D_pspeu_092C61F8,
    D_pspeu_092C6200,
    D_pspeu_092C6208,
    D_pspeu_092C6210,
    D_pspeu_092C6218,
    D_pspeu_092C6220,
    D_pspeu_092C6228,
    D_pspeu_092C6230,
    D_pspeu_092C6238,
    D_pspeu_092C6240,
    D_pspeu_092C6248,
    D_pspeu_092C6250,
    D_pspeu_092C6258,
    D_pspeu_092C6260,
    D_pspeu_092C6268,
    D_pspeu_092C6270,
    D_pspeu_092C6278,
    D_pspeu_092C6280,
    D_pspeu_092C6288,
    D_pspeu_092C6290,
    D_pspeu_092C6298,
    D_pspeu_092C62A0,
    D_pspeu_092C62A8,
    D_pspeu_092C62B0,
    D_pspeu_092C62B8,
    D_pspeu_092C62C0,
    D_pspeu_092C62C8,
    D_pspeu_092C62D0,
    D_pspeu_092C62D8,
    D_pspeu_092C62E0,
    D_pspeu_092C62E8,
    D_pspeu_092C62F0,
    D_pspeu_092C62F8,
    D_pspeu_092C6300,
    D_pspeu_092C6308,
    D_pspeu_092C6310,
    D_pspeu_092C6318,
    D_pspeu_092C6320,
    D_pspeu_092C6328,
    D_pspeu_092C6330,
    D_pspeu_092C6338,
    D_pspeu_092C6340,
    D_pspeu_092C6348,
    D_pspeu_092C6350,
    D_pspeu_092C6358,
    D_pspeu_092C6360,
    D_pspeu_092C6368,
    D_pspeu_092C6370,
    D_pspeu_092C6378,
    D_pspeu_092C6380,
    D_pspeu_092C6388,
    D_pspeu_092C6390,
    D_pspeu_092C6398,
    D_pspeu_092C63A0,
    D_pspeu_092C63A8,
    D_pspeu_092C63B0,
    D_pspeu_092C63B8,
    D_pspeu_092C63C0,
    D_pspeu_092C63C8,
    D_pspeu_092C63D0,
    D_pspeu_092C63D8,
    D_pspeu_092C63E0,
    D_pspeu_092C63E8,
    D_pspeu_092C63F0,
    D_pspeu_092C63F8,
    D_pspeu_092C6400,
    D_pspeu_092C6408,
    D_pspeu_092C6410,
    D_pspeu_092C6418,
    D_pspeu_092C6420,
    D_pspeu_092C6428,
    D_pspeu_092C6430,
    D_pspeu_092C6438,
    D_pspeu_092C6440,
    D_pspeu_092C6448,
    NULL};

static s16 D_pspeu_092C6078[] = {0x00 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C6080[] = {0x01 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6088[] = {0x02 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6090[] = {0x03 | 0x8000, -12, -24, 0};
static s16 D_pspeu_092C6098[] = {0x04 | 0x8000, -12, -15, 0};
static s16 D_pspeu_092C60A0[] = {0x05 | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C60A8[] = {0x06 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C60B0[] = {0x07 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C60B8[] = {0x08 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C60C0[] = {0x09 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C60C8[] = {0x09 | 0x8000, -11, -23, 0};
static s16 D_pspeu_092C60D0[] = {0x0A | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C60D8[] = {0x0B | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C60E0[] = {0x0C | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C60E8[] = {0x0D | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C60F0[] = {0x0E | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C60F8[] = {0x0F | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6100[] = {0x10 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6108[] = {0x11 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6110[] = {0x12 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6118[] = {0x13 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6120[] = {0x14 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6128[] = {0x15 | 0x8000, -11, -23, 0};
static s16 D_pspeu_092C6130[] = {0x16 | 0x8000, -11, -23, 0};
static s16 D_pspeu_092C6138[] = {0x17 | 0x8000, -11, -23, 0};
static s16 D_pspeu_092C6140[] = {0x18 | 0x8000, -10, -23, 0};
static s16 D_pspeu_092C6148[] = {0x19 | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6150[] = {0x1A | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C6158[] = {0x1B | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6160[] = {0x1C | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6168[] = {0x1D | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C6170[] = {0x1E | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6178[] = {0x1F | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6180[] = {0x20 | 0x8000, -10, -23, 0};
static s16 D_pspeu_092C6188[] = {0x21 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6190[] = {0x22 | 0x8000, -10, -23, 0};
static s16 D_pspeu_092C6198[] = {0x23 | 0x8000, -10, -23, 0};
static s16 D_pspeu_092C61A0[] = {0x24 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C61A8[] = {0x25 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C61B0[] = {0x26 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C61B8[] = {0x27 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C61C0[] = {0x28 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C61C8[] = {0x29 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C61D0[] = {0x2A | 0x8000, -24, -33, 0};
static s16 D_pspeu_092C61D8[] = {0x2B | 0x8000, -24, -33, 0};
static s16 D_pspeu_092C61E0[] = {0x2C | 0x8000, -13, -37, 0};
static s16 D_pspeu_092C61E8[] = {0x2D | 0x8000, -13, -37, 0};
static s16 D_pspeu_092C61F0[] = {0x2E | 0x8000, -13, -37, 0};
static s16 D_pspeu_092C61F8[] = {0x2F | 0x8000, -13, -37, 0};
static s16 D_pspeu_092C6200[] = {0x30 | 0x8000, -19, -17, 0};
static s16 D_pspeu_092C6208[] = {0x31 | 0x8000, -19, -17, 0};
static s16 D_pspeu_092C6210[] = {0x32 | 0x8000, -19, -17, 0};
static s16 D_pspeu_092C6218[] = {0x33 | 0x8000, -19, -17, 0};
static s16 D_pspeu_092C6220[] = {0x34 | 0x8000, -28, -6, 0};
static s16 D_pspeu_092C6228[] = {0x35 | 0x8000, -27, -6, 0};
static s16 D_pspeu_092C6230[] = {0x36 | 0x8000, -19, -24, 0};
static s16 D_pspeu_092C6238[] = {0x37 | 0x8000, -24, -23, 0};
static s16 D_pspeu_092C6240[] = {0x38 | 0x8000, -24, -22, 0};
static s16 D_pspeu_092C6248[] = {0x39 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6250[] = {0x3A | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6258[] = {0x3B | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6260[] = {0x3C | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6268[] = {0x3D | 0x8000, -21, -19, 0};
static s16 D_pspeu_092C6270[] = {0x3E | 0x8000, -21, -27, 0};
static s16 D_pspeu_092C6278[] = {0x3F | 0x8000, -20, -27, 0};
static s16 D_pspeu_092C6280[] = {0x40 | 0x8000, -21, -27, 0};
static s16 D_pspeu_092C6288[] = {0x40 | 0x8000, -22, -27, 0};
static s16 D_pspeu_092C6290[] = {0x41 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C6298[] = {0x42 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62A0[] = {0x43 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62A8[] = {0x44 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62B0[] = {0x45 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62B8[] = {0x46 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62C0[] = {0x47 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62C8[] = {0x48 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62D0[] = {0x49 | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62D8[] = {0x4A | 0x8000, -12, -23, 0};
static s16 D_pspeu_092C62E0[] = {0x4B | 0x8000, -14, -21, 0};
static s16 D_pspeu_092C62E8[] = {0x4C | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C62F0[] = {0x4D | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C62F8[] = {0x4E | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C6300[] = {0x4F | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C6308[] = {0x50 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C6310[] = {0x51 | 0x8000, -24, -24, 0};
static s16 D_pspeu_092C6318[] = {0x52 | 0x8000, -17, -9, 0};
static s16 D_pspeu_092C6320[] = {0x53 | 0x8000, -17, -9, 0};
static s16 D_pspeu_092C6328[] = {0x54 | 0x8000, -16, -9, 0};
static s16 D_pspeu_092C6330[] = {0x55 | 0x8000, -17, -9, 0};
static s16 D_pspeu_092C6338[] = {0x55 | 0x8000, -18, -9, 0};
static s16 D_pspeu_092C6340[] = {0x56 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6348[] = {0x57 | 0x8000, -15, -24, 0};
static s16 D_pspeu_092C6350[] = {0x58 | 0x8000, -21, -37, 0};
static s16 D_pspeu_092C6358[] = {0x58 | 0x8000, -20, -37, 0};
static s16 D_pspeu_092C6360[] = {0x59 | 0x8000, -8, -24, 0};
static s16 D_pspeu_092C6368[] = {0x5A | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6370[] = {0x5B | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6378[] = {0x5C | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6380[] = {0x5D | 0x8000, -21, -19, 0};
static s16 D_pspeu_092C6388[] = {0x5E | 0x8000, -21, -19, 0};
static s16 D_pspeu_092C6390[] = {0x5F | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C6398[] = {0x60 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63A0[] = {0x61 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63A8[] = {0x62 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63B0[] = {0x63 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63B8[] = {0x64 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63C0[] = {0x65 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63C8[] = {0x66 | 0x8000, -20, -21, 0};
static s16 D_pspeu_092C63D0[] = {0x04 | 0x8000, -12, -15, 0};
static s16 D_pspeu_092C63D8[] = {0x67 | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C63E0[] = {0x68 | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C63E8[] = {0x05 | 0x8000, -12, -7, 0};
static s16 D_pspeu_092C63F0[] = {0x57 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C63F8[] = {0x69 | 0x8000, -16, -24, 0};
static s16 D_pspeu_092C6400[] = {0x6A | 0x8000, -16, -19, 0};
static s16 D_pspeu_092C6408[] = {0x6B | 0x8000, -25, -22, 0};
static s16 D_pspeu_092C6410[] = {0x6C | 0x8000, -16, -23, 0};
static s16 D_pspeu_092C6418[] = {0x6D | 0x8000, -24, -23, 0};
static s16 D_pspeu_092C6420[] = {0x6E | 0x8000, -24, -23, 0};
static s16 D_pspeu_092C6428[] = {0x6F | 0x8000, -12, -45, 0};
static s16 D_pspeu_092C6430[] = {0x70 | 0x8000, -12, -45, 0};
static s16 D_pspeu_092C6438[] = {0x71 | 0x8000, -12, -45, 0};
static s16 D_pspeu_092C6440[] = {0x72 | 0x8000, -12, -45, 0};
static s16 D_pspeu_092C6448[] = {0x73 | 0x8000, -12, -45, 0};
