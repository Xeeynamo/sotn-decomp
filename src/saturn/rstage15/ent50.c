// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage15SpriteBank26;

void func_060EA138(Entity* self);

EntityEntry g_RStage15EntityEntry50 = {&g_RStage15SpriteBank26, func_060EA138};

u8 g_RStage15Entity50AnimationData[] = {
    5, 1,    6,   2,    4,    3,    4, 4,    5,    5,    5,    6,
    4, 7,    5,   8,    5,    9,    6, 0xA,  0xFF, 0xFF, 4,    0xB,
    4, 0xC,  5,   0xD,  4,    0xE,  3, 0xF,  3,    0x10, 2,    0x11,
    3, 0x12, 2,   0x13, 2,    0x14, 2, 0x15, 1,    0x16, 1,    0x17,
    2, 0x18, 0xD, 0x19, 0xFF, 0xFF, 7, 0x1A, 7,    0x1B, 7,    0x1C,
    7, 0x1D, 7,   0x1E, 7,    0x1F, 7, 0x20, 0x1D, 0x21, 0xFF, 0xFF,
    2, 1,    2,   2,    2,    3,    2, 4,    2,    5,    2,    6,
    2, 7,    2,   8,    2,    9,    2, 0xA,  0xFF, 0xFF,
};
u16 g_RStage15Entity50AnimationsPadding = 0;
u8* g_RStage15Entity50Animations[] = {
    &g_RStage15Entity50AnimationData[0],
    &g_RStage15Entity50AnimationData[22],
    &g_RStage15Entity50AnimationData[54],
    &g_RStage15Entity50AnimationData[72],
};
