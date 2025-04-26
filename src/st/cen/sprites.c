// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
#include "common.h"
static s16 sprites_cen_0_1[14];
static s16 sprites_cen_0_2[14];
static s16 sprites_cen_0_3[14];
static s16 sprites_cen_0_4[14];
static s16 sprites_cen_0_5[14];
static s16 sprites_cen_0_6[14];
static s16 sprites_cen_0_7[14];
static s16 sprites_cen_0_8[14];
static s16 sprites_cen_0_9[14];
static s16 sprites_cen_0_10[14];
s16* sprites_cen_0[] = {
    0,
    sprites_cen_0_1,
    sprites_cen_0_2,
    sprites_cen_0_3,
    sprites_cen_0_4,
    sprites_cen_0_5,
    sprites_cen_0_6,
    sprites_cen_0_7,
    sprites_cen_0_8,
    sprites_cen_0_9,
    sprites_cen_0_10,
    0,
};
static s16 sprites_cen_0_1[] = {
    1,
    0, -16, -12, 32, 24, 16, 60, 128, 128, 160, 152,
    0, 0
};
static s16 sprites_cen_0_2[] = {
    1,
    0, -16, -12, 32, 24, 16, 60, 160, 128, 192, 152,
    0, 0
};
static s16 sprites_cen_0_3[] = {
    1,
    0, -16, -12, 32, 24, 16, 60, 192, 128, 224, 152,
    0, 0
};
static s16 sprites_cen_0_4[] = {
    1,
    4, -16, -12, 32, 24, 16, 60, 224, 128, 256, 152,
    0, 0
};
static s16 sprites_cen_0_5[] = {
    1,
    0, -16, -12, 32, 24, 16, 60, 128, 152, 160, 176,
    0, 0
};
static s16 sprites_cen_0_6[] = {
    1,
    0, -4, -4, 8, 8, 17, 60, 160, 152, 168, 160,
    0, 0
};
static s16 sprites_cen_0_7[] = {
    1,
    0, -16, -16, 32, 32, 14, 60, 128, 176, 160, 208,
    0, 0
};
static s16 sprites_cen_0_8[] = {
    1,
    0, -16, -4, 32, 8, 14, 60, 128, 208, 160, 216,
    0, 0
};
static s16 sprites_cen_0_9[] = {
    1,
    0, -32, -24, 64, 40, 18, 60, 176, 152, 240, 192,
    0, 0
};
static s16 sprites_cen_0_10[] = {
    1,
    0, -8, -4, 16, 8, 18, 60, 160, 160, 176, 168,
    0, 0
};
static s16 sprites_cen_1_1[24];
static s16 sprites_cen_1_2[24];
static s16 sprites_cen_1_3[14];
static s16 sprites_cen_1_4[14];
static s16 sprites_cen_1_5[14];
static s16 sprites_cen_1_6[14];
static s16 sprites_cen_1_7[14];
static s16 sprites_cen_1_8[14];
static s16 sprites_cen_1_9[14];
static s16 sprites_cen_1_10[24];
static s16 sprites_cen_1_11[24];
static s16 sprites_cen_1_12[24];
static s16 sprites_cen_1_13[24];
static s16 sprites_cen_1_14[24];
static s16 sprites_cen_1_15[24];
static s16 sprites_cen_1_16[24];
static s16 sprites_cen_1_17[24];
static s16 sprites_cen_1_18[24];
static s16 sprites_cen_1_19[24];
static s16 sprites_cen_1_20[24];
static s16 sprites_cen_1_21[24];
static s16 sprites_cen_1_22[24];
static s16 sprites_cen_1_23[14];
static s16 sprites_cen_1_24[36];
static s16 sprites_cen_1_25[36];
static s16 sprites_cen_1_26[24];
static s16 sprites_cen_1_27[24];
static s16 sprites_cen_1_28[24];
static s16 sprites_cen_1_29[24];
static s16 sprites_cen_1_30[24];
static s16 sprites_cen_1_31[14];
static s16 sprites_cen_1_32[14];
static s16 sprites_cen_1_33[14];
static s16 sprites_cen_1_34[14];
static s16 sprites_cen_1_35[14];
static s16 sprites_cen_1_36[14];
static s16 sprites_cen_1_37[14];
static s16 sprites_cen_1_38[14];
static s16 sprites_cen_1_39[14];
static s16 sprites_cen_1_40[36];
static s16 sprites_cen_1_41[24];
static s16 sprites_cen_1_42[24];
s16* sprites_cen_1[] = {
    0,
    sprites_cen_1_1,
    sprites_cen_1_2,
    sprites_cen_1_3,
    sprites_cen_1_4,
    sprites_cen_1_5,
    sprites_cen_1_6,
    sprites_cen_1_7,
    sprites_cen_1_8,
    sprites_cen_1_9,
    sprites_cen_1_10,
    sprites_cen_1_11,
    sprites_cen_1_12,
    sprites_cen_1_13,
    sprites_cen_1_14,
    sprites_cen_1_15,
    sprites_cen_1_16,
    sprites_cen_1_17,
    sprites_cen_1_18,
    sprites_cen_1_19,
    sprites_cen_1_20,
    sprites_cen_1_21,
    sprites_cen_1_22,
    sprites_cen_1_23,
    sprites_cen_1_24,
    sprites_cen_1_25,
    sprites_cen_1_26,
    sprites_cen_1_27,
    sprites_cen_1_28,
    sprites_cen_1_29,
    sprites_cen_1_30,
    sprites_cen_1_31,
    sprites_cen_1_32,
    sprites_cen_1_33,
    sprites_cen_1_34,
    sprites_cen_1_35,
    sprites_cen_1_36,
    sprites_cen_1_37,
    sprites_cen_1_38,
    sprites_cen_1_39,
    sprites_cen_1_40,
    sprites_cen_1_41,
    sprites_cen_1_42,
    0,
};
static s16 sprites_cen_1_1[] = {
    2,
    16, -19, -21, 16, 16, 0, 0, 0, 88, 16, 104,
    48, -19, -14, 16, 40, 0, 0, 0, 0, 16, 40,
    0
};
static s16 sprites_cen_1_2[] = {
    2,
    16, -19, -21, 16, 16, 0, 0, 0, 104, 16, 120,
    48, -19, -14, 16, 40, 0, 0, 0, 0, 16, 40,
    0
};
static s16 sprites_cen_1_3[] = {
    1,
    32, -19, -22, 16, 48, 0, 0, 16, 0, 32, 48,
    0, 0
};
static s16 sprites_cen_1_4[] = {
    1,
    32, -18, -22, 24, 48, 0, 0, 32, 0, 56, 48,
    0, 0
};
static s16 sprites_cen_1_5[] = {
    1,
    32, -18, -22, 24, 48, 0, 0, 56, 0, 80, 48,
    0, 0
};
static s16 sprites_cen_1_6[] = {
    1,
    32, -18, -22, 24, 48, 0, 0, 80, 0, 104, 48,
    0, 0
};
static s16 sprites_cen_1_7[] = {
    1,
    36, -18, -22, 24, 48, 0, 0, 104, 0, 128, 48,
    0, 0
};
static s16 sprites_cen_1_8[] = {
    1,
    0, -18, -22, 24, 48, 0, 0, 16, 48, 40, 96,
    0, 0
};
static s16 sprites_cen_1_9[] = {
    1,
    0, -18, -22, 24, 48, 0, 0, 40, 48, 64, 96,
    0, 0
};
static s16 sprites_cen_1_10[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, -2, -14, 8, 24, 0, 0, 16, 96, 24, 120,
    0
};
static s16 sprites_cen_1_11[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, -1, -11, 8, 16, 0, 0, 24, 96, 32, 112,
    0
};
static s16 sprites_cen_1_12[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, 0, -12, 8, 16, 0, 0, 32, 96, 40, 112,
    0
};
static s16 sprites_cen_1_13[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    8, 0, -14, 8, 16, 0, 0, 24, 112, 32, 128,
    0
};
static s16 sprites_cen_1_14[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    8, 1, -17, 8, 16, 0, 0, 32, 112, 40, 128,
    0
};
static s16 sprites_cen_1_15[] = {
    2,
    8, 1, -15, 8, 8, 0, 0, 16, 120, 24, 128,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_16[] = {
    2,
    0, 1, -15, 8, 16, 0, 0, 40, 96, 48, 112,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_17[] = {
    2,
    8, 1, -15, 8, 16, 0, 0, 40, 112, 48, 128,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_18[] = {
    2,
    24, 0, -12, 8, 8, 0, 0, 0, 120, 8, 128,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_19[] = {
    2,
    8, -1, -12, 8, 8, 0, 0, 8, 120, 16, 128,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_20[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, 0, -15, 8, 16, 0, 0, 48, 104, 56, 120,
    0
};
static s16 sprites_cen_1_21[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, -3, -11, 16, 8, 0, 0, 48, 96, 64, 104,
    0
};
static s16 sprites_cen_1_22[] = {
    2,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0, -2, -11, 16, 8, 0, 0, 48, 96, 64, 104,
    0
};
static s16 sprites_cen_1_23[] = {
    1,
    0, -14, -22, 24, 48, 0, 0, 64, 48, 88, 96,
    0, 0
};
static s16 sprites_cen_1_24[] = {
    3,
    0, 3, -10, 8, 8, 0, 0, 56, 112, 64, 120,
    0, -11, -10, 8, 8, 0, 0, 56, 104, 64, 112,
    0, -9, -22, 16, 48, 0, 0, 88, 48, 104, 96,
    0, 0
};
static s16 sprites_cen_1_25[] = {
    3,
    0, 4, -11, 8, 8, 0, 0, 56, 112, 64, 120,
    0, -11, -11, 8, 8, 0, 0, 56, 104, 64, 112,
    0, -9, -22, 16, 48, 0, 0, 88, 48, 104, 96,
    0, 0
};
static s16 sprites_cen_1_26[] = {
    2,
    0, 0, -21, 8, 16, 0, 0, 64, 96, 72, 112,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_27[] = {
    2,
    8, 0, -21, 8, 16, 0, 0, 64, 112, 72, 128,
    16, -10, -22, 16, 48, 0, 0, 0, 40, 16, 88,
    0
};
static s16 sprites_cen_1_28[] = {
    2,
    32, -10, -6, 16, 32, 0, 1, 16, 0, 32, 32,
    48, -10, -22, 16, 32, 0, 1, 0, 0, 16, 32,
    0
};
static s16 sprites_cen_1_29[] = {
    2,
    32, -10, -6, 16, 32, 0, 1, 48, 0, 64, 32,
    32, -10, -22, 16, 32, 0, 1, 32, 0, 48, 32,
    0
};
static s16 sprites_cen_1_30[] = {
    2,
    8, -8, -22, 16, 32, 0, 0, 96, 96, 112, 128,
    12, -9, -6, 16, 32, 0, 0, 112, 96, 128, 128,
    0
};
static s16 sprites_cen_1_31[] = {
    1,
    4, -10, -22, 24, 48, 0, 0, 104, 48, 128, 96,
    0, 0
};
static s16 sprites_cen_1_32[] = {
    1,
    8, -10, -23, 24, 48, 0, 1, 88, 80, 112, 128,
    0, 0
};
static s16 sprites_cen_1_33[] = {
    1,
    16, -16, -23, 32, 48, 0, 1, 0, 32, 32, 80,
    0, 0
};
static s16 sprites_cen_1_34[] = {
    1,
    0, -16, -23, 32, 48, 0, 1, 32, 32, 64, 80,
    0, 0
};
static s16 sprites_cen_1_35[] = {
    1,
    0, -16, -23, 32, 48, 0, 1, 64, 32, 96, 80,
    0, 0
};
static s16 sprites_cen_1_36[] = {
    1,
    4, -16, -23, 32, 48, 0, 1, 96, 32, 128, 80,
    0, 0
};
static s16 sprites_cen_1_37[] = {
    1,
    24, -16, -23, 32, 48, 0, 1, 0, 80, 32, 128,
    0, 0
};
static s16 sprites_cen_1_38[] = {
    1,
    8, -16, -23, 32, 48, 0, 1, 32, 80, 64, 128,
    0, 0
};
static s16 sprites_cen_1_39[] = {
    1,
    8, -11, -23, 24, 48, 0, 1, 64, 80, 88, 128,
    0, 0
};
static s16 sprites_cen_1_40[] = {
    3,
    4, -3, -21, 16, 24, 0, 1, 112, 80, 128, 104,
    12, -12, -21, 16, 24, 0, 1, 112, 104, 128, 128,
    8, -11, -7, 24, 32, 0, 0, 72, 96, 96, 128,
    0, 0
};
static s16 sprites_cen_1_41[] = {
    2,
    32, -19, -21, 32, 24, 0, 1, 64, 0, 96, 24,
    8, -11, -7, 24, 32, 0, 0, 72, 96, 96, 128,
    0
};
static s16 sprites_cen_1_42[] = {
    2,
    36, -19, -21, 32, 24, 0, 1, 96, 0, 128, 24,
    8, -11, -7, 24, 32, 0, 0, 72, 96, 96, 128,
    0
};
static s16 sprites_cen_2_1[14];
static s16 sprites_cen_2_2[14];
static s16 sprites_cen_2_3[36];
static s16 sprites_cen_2_4[36];
static s16 sprites_cen_2_5[46];
static s16 sprites_cen_2_6[58];
static s16 sprites_cen_2_7[58];
static s16 sprites_cen_2_8[68];
static s16 sprites_cen_2_9[68];
static s16 sprites_cen_2_10[80];
static s16 sprites_cen_2_11[80];
static s16 sprites_cen_2_12[36];
static s16 sprites_cen_2_13[14];
static s16 sprites_cen_2_14[14];
static s16 sprites_cen_2_15[14];
s16* sprites_cen_2[] = {
    0,
    sprites_cen_2_1,
    sprites_cen_2_2,
    sprites_cen_2_3,
    sprites_cen_2_4,
    sprites_cen_2_5,
    sprites_cen_2_6,
    sprites_cen_2_7,
    sprites_cen_2_8,
    sprites_cen_2_9,
    sprites_cen_2_10,
    sprites_cen_2_11,
    sprites_cen_2_12,
    sprites_cen_2_13,
    sprites_cen_2_14,
    sprites_cen_2_15,
    0,
};
static s16 sprites_cen_2_1[] = {
    1,
    32, -8, -23, 16, 40, 0, 0, 80, 0, 96, 40,
    0, 0
};
static s16 sprites_cen_2_2[] = {
    1,
    36, -16, -16, 32, 32, 0, 0, 96, 0, 128, 32,
    0, 0
};
static s16 sprites_cen_2_3[] = {
    3,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    0, -20, -27, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_4[] = {
    3,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    0, -20, -19, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_5[] = {
    4,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, -24, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, -11, 40, 24, 0, 0, 40, 16, 80, 40,
    0
};
static s16 sprites_cen_2_6[] = {
    5,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    32, -20, -16, 40, 16, 0, 0, 40, 0, 80, 16,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, -30, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, -3, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_7[] = {
    5,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, -22, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -8, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, 5, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_8[] = {
    6,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, -28, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -14, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, 0, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, 13, 40, 24, 0, 0, 40, 16, 80, 40,
    0
};
static s16 sprites_cen_2_9[] = {
    6,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, -20, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -6, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, 8, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, 21, 40, 24, 0, 0, 40, 16, 80, 40,
    0
};
static s16 sprites_cen_2_10[] = {
    7,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, 12, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -2, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -16, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -30, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, 26, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_11[] = {
    7,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    32, -20, 14, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, 0, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -14, 40, 16, 0, 0, 40, 0, 80, 16,
    32, -20, -28, 40, 16, 0, 0, 40, 0, 80, 16,
    0, -20, 28, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_12[] = {
    3,
    16, -20, 26, 40, 16, 0, 0, 0, 64, 40, 80,
    48, -20, -35, 40, 64, 0, 0, 0, 0, 40, 64,
    0, -20, -26, 40, 24, 0, 0, 40, 16, 80, 40,
    0, 0
};
static s16 sprites_cen_2_13[] = {
    1,
    16, -17, -8, 40, 16, 0, 0, 0, 80, 40, 96,
    0, 0
};
static s16 sprites_cen_2_14[] = {
    1,
    16, -20, -12, 40, 24, 1, 0, 0, 96, 40, 120,
    0, 0
};
static s16 sprites_cen_2_15[] = {
    1,
    0, -8, -47, 16, 16, 0, 0, 40, 40, 56, 56,
    0, 0
};
