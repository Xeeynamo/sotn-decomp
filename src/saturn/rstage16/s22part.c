// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

s16 g_RStage16Entity37Sensors[4][2] = {
    {0, 20},
    {0, 4},
    {8, -4},
    {-16, 0},
};

s16 g_RStage16Entity37InitOffset[4] = {
    0,
    20,
    12,
    0,
};

u8 g_RStage16Entity37Anim0[16] = {
    6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0, 0, 0, 0,
};

u8 g_RStage16Entity37Anim1[16] = {
    6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0, 0, 0, 0,
};

u8 g_RStage16Entity37Anim2[12] = {
    4, 1, 5, 0x1B, 0xF, 0x1C, 6, 0x1B, 6, 1, 0, 0,
};

u8 g_RStage16Entity37Anim3[68] = {
    0x10, 1,    3, 2,    3, 7,    3, 8,    2,    9,    2, 0xA,  2, 0xB,
    2,    0xA,  2, 0xB,  2, 0xC,  2, 0xB,  2,    0xC,  2, 0xD,  2, 0xC,
    2,    0xD,  2, 0xE,  2, 0xD,  2, 0xE,  2,    0xD,  2, 0xE,  2, 0xF,
    2,    0x10, 2, 0xF,  2, 0x10, 2, 0xF,  2,    0x10, 4, 0x14, 4, 0x13,
    4,    0x12, 4, 0x11, 4, 0x12, 4, 0x13, 0xFF, 0,    0, 0,
};

u8 g_RStage16Entity37Anim4[48] = {
    2, 0x14, 0x60, 0x15, 1, 0x17, 1, 0x16, 1,    0x17, 1,    0x16,
    1, 0x17, 2,    0x16, 2, 0x17, 2, 0x16, 2,    0x17, 3,    0x16,
    3, 0x17, 3,    0x16, 4, 0x17, 5, 0x16, 0x1A, 0x17, 3,    0x18,
    3, 0x19, 3,    0x1A, 4, 4,    4, 5,    4,    6,    0xFF, 0,
};

u16 g_RStage16Entity38Params[8] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x20, 0xFFE0,
};

u8 g_RStage16Entity37Params[8] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x40, 0x30,
};

s32 g_RStage16Entity37VelocityX[8] = {
    49152, 114688, 98304, 65536, 131072, 114688, -32768, 32768,
};

s32 g_RStage16Entity37VelocityY[8] = {
    -327680, -196608, -131072, -196608, -262144, -57344, -393216, -294912,
};

s16 g_RStage16Entity37OffsetX[8] = {
    -4, 0, 4, -4, -4, 4, -6, 6,
};

s16 g_RStage16Entity37OffsetY[8] = {
    -16, -8, -4, -4, 9, 9, 2, -2,
};

u8 g_RStage16Entity37Data[8] = {
    0x80, 8, 8, 0x40, 0xF0, 0xC0, 0xA0, 0x80,
};

s32 g_RStage16Entity36Corners[4][3] = {
    {-0x200000, -0x200000, 0},
    {0x200000, -0x200000, 0},
    {0x200000, 0x200000, 0},
    {-0x200000, 0x200000, 0},
};

u8 g_RStage16Entity36Colors[12] = {
    0x60, 0x7F, 0x80, 0x80, 0x20, 0x5F, 0x40, 0x80, 0, 0x1F, 0x20, 0x40,
};
