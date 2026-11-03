// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rstage16.h"
#include "sattypes.h"
#include <saturn_sprite.h>

EntityEntry g_RStage16EntityGargoyle = {
    &g_RStage16SpriteBankGargoyle, func_060E5F48};

s32 g_RStage16GargoyleAttackVelocities[2] = {
    131072,
    131072,
};

s16 g_RStage16Entity32Offset[2] = {
    0,
    0,
};

EntityEntry g_RStage16EntityEntry32 = {
    &g_RStage16SpriteBankGargoyle, func_060E660C};

u16 g_RStage16Entity32Params[2] = {
    0,
    2,
};

s16 g_RStage16Entity33Offset[2] = {
    0,
    0,
};

EntityEntry g_RStage16EntityEntry33 = {
    &g_RStage16SpriteBankGargoyle, func_060E6828};

u8 g_RStage16GargoyleAnimationData[102] = {
    0x62, 1,    0x62, 0x3A, 0x62, 0x3B, 0xFF, 0xFF, 3,    2,    1,    3,
    1,    2,    1,    3,    1,    4,    1,    3,    0x2B, 4,    6,    5,
    6,    6,    6,    7,    6,    8,    0x29, 4,    7,    9,    0x1A, 0xA,
    2,    0xB,  3,    0xC,  3,    0xD,  4,    0xE,  0xFF, 0xFF, 6,    0x10,
    4,    0x11, 7,    0x12, 2,    0x13, 5,    0x14, 0,    0,    0xB,  0x15,
    0x13, 0x16, 2,    0x17, 2,    0x18, 5,    0x19, 0xB,  0x1A, 9,    0x1B,
    7,    0x1C, 8,    0x1D, 0xA,  0x1E, 0xFF, 0xFF, 7,    0x1F, 7,    0x20,
    7,    0x21, 7,    0x22, 7,    0x23, 7,    0x24, 7,    0x25, 7,    0x26,
    7,    0x27, 7,    0x28, 0xFF, 0xFF,
};

u16 g_RStage16GargoyleAnimPadding = 0;

u8* g_RStage16GargoyleAnimations[5] = {
    g_RStage16GargoyleAnimationData,      &g_RStage16GargoyleAnimationData[8],
    &g_RStage16GargoyleAnimationData[46], &g_RStage16GargoyleAnimationData[58],
    &g_RStage16GargoyleAnimationData[80],
};
