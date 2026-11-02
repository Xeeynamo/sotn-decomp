// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

s32 g_RStage16ExplosionYVelocities[5] = {
    -65536, -98304, -98304, -98304, -196608,
};

u8 g_RStage16ExplosionAnimSmall[20] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 0, 0, 0, 0,
};

u8 g_RStage16ExplosionAnimFireball[28] = {
    1, 9,    2, 0xA,  2, 0xB,  2, 0xC,  2, 0xD,  2, 0xE, 2, 0xF,
    2, 0x10, 2, 0x11, 2, 0x12, 3, 0x13, 4, 0x14, 0, 0,   0, 0,
};

u8 g_RStage16ExplosionAnimSmallMultiple[48] = {
    2, 0x15, 2, 0x16, 2, 0x17, 2, 0x18, 2, 0x19, 2, 0x1A, 2, 0x1B, 2, 0x1C,
    2, 0x1D, 2, 0x1E, 2, 0x1F, 2, 0x20, 2, 0x21, 2, 0x22, 2, 0x23, 2, 0x24,
    2, 0x25, 2, 0x26, 2, 0x27, 2, 0x28, 2, 0x29, 2, 0x2A, 0, 0,    0, 0,
};

u8 g_RStage16ExplosionAnimBig[52] = {
    2, 0x2B, 2, 0x2C, 2, 0x2D, 2, 0x2E, 2, 0x2F, 2, 0x30, 2, 0x31,
    2, 0x32, 2, 0x33, 2, 0x34, 2, 0x35, 2, 0x36, 2, 0x37, 2, 0x38,
    2, 0x39, 2, 0x3A, 2, 0x3B, 2, 0x3C, 2, 0x3D, 2, 0x3E, 2, 0x3F,
    2, 0x40, 2, 0x41, 2, 0x42, 0, 0,    0, 0,
};

u8 g_RStage16ExplosionAnimUnused[4] = {
    1,
    0x43,
    0,
    0,
};

u8* g_RStage16ExplosionAnimations[5] = {
    g_RStage16ExplosionAnimSmall,         g_RStage16ExplosionAnimFireball,
    g_RStage16ExplosionAnimSmallMultiple, g_RStage16ExplosionAnimBig,
    g_RStage16ExplosionAnimUnused,
};

u16 g_RStage16ExplosionInit[5] = {
    1, 2, 4, 5, 1,
};

u16 g_RStage16ExplosionInitPadding = 0;
