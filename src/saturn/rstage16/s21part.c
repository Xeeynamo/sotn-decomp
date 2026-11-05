// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

u8 g_RStage16Entity34Anim0[16] = {
    6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0, 0, 0, 0,
};

u8 g_RStage16Entity34Anim1[16] = {
    6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0, 0, 0, 0,
};

u8 g_RStage16Entity34Anim2[24] = {
    5, 1,   5,    2,   5, 7, 6, 8, 5, 9, 5,    0xA,
    5, 0xB, 0x1F, 0xC, 4, 4, 4, 5, 4, 6, 0xFF, 0,
};

u8 g_RStage16Entity34Anim3[12] = {
    1, 1, 4, 0xD, 4, 0xE, 1, 1, 0xFF, 0, 0, 0,
};

u8 g_RStage16Entity34Anim4[12] = {
    1, 1, 4, 0xD, 6, 0xE, 4, 0xD, 1, 1, 0xFF, 0,
};

u16 g_RStage16Entity35Params[8] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x18, 0,
};

u8 g_RStage16Entity34Params[8] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x14, 0,
};

s32 g_RStage16Entity34VelocityX[7] = {
    49152, 114688, 98304, 65536, 131072, 114688, 49152,
};

s32 g_RStage16Entity34VelocityY[7] = {
    -327680, -196608, -131072, -196608, -262144, -57344, -262144,
};

s16 g_RStage16Entity34OffsetX[7] = {
    -4, 0, 4, -4, -4, 4, 0,
};

s16 g_RStage16Entity34OffsetY[7] = {
    -16, -8, -4, -4, 9, 9, 0,
};

u8 g_RStage16Entity34Data[8] = {
    0x60, 8, 8, 0x40, 0x80, 0x40, 0x20, 0x30,
};

s16 g_RStage16Entity34Sensors[4][2] = {
    {0, 20},
    {0, 4},
    {8, -4},
    {-16, 0},
};

s16 g_RStage16Entity34InitOffset[4] = {
    0,
    20,
    12,
    0,
};

s16 g_RStage16Entity34Hitbox[6] = {
    -12, 16, 0, -16, 0, -16,
};
