// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage15SpriteBank22;

void func_060E4668(Entity* self);
void func_060E519C(Entity* self);
void func_060E540C(Entity* self);

EntityEntry g_RStage15EntityEntry29 = {&g_RStage15SpriteBank22, func_060E4668};
s16 g_RStage15Entity29InitOffset[2] = {0, 25};
EntityEntry g_RStage15EntityEntry30 = {&g_RStage15SpriteBank22, func_060E519C};
s16 g_RStage15Entity30InitOffset[2] = {0, 25};
EntityEntry g_RStage15EntityEntry31 = {&g_RStage15SpriteBank22, func_060E540C};

u8 g_RStage15Entity29AnimationData[] = {
    6,    2,    6,    3,    0x40, 4,    0xFF, 0xFF, 6,    5,    8,    1,
    6,    6,    0xFF, 0xFF, 6,    7,    8,    8,    6,    9,    0xFF, 0xFF,
    0x10, 1,    2,    0xA,  2,    0xB,  0x14, 0xA,  1,    0x12, 1,    0x11,
    1,    0x10, 0xFF, 0xFF, 1,    0xD,  1,    0xE,  0xFF, 0xFF, 8,    1,
    0x16, 0xC,  1,    0xE,  1,    0xD,  1,    0xF,  1,    0x11, 1,    0x12,
    0xFF, 0xFF, 1,    0x15, 1,    0x16, 1,    0x17, 1,    0x18, 1,    0x19,
    1,    0x1A, 1,    0x1B, 1,    0x1C, 0xFF, 0xFF, 2,    0x1D, 2,    0x1E,
    2,    0x1F, 2,    0x20, 2,    0x21, 2,    0x22, 0xFF, 0xFF,
};
u16 g_RStage15Entity29AnimationsPadding = 0;
u8* g_RStage15Entity29Animations[] = {
    &g_RStage15Entity29AnimationData[0],  &g_RStage15Entity29AnimationData[8],
    &g_RStage15Entity29AnimationData[16], &g_RStage15Entity29AnimationData[24],
    &g_RStage15Entity29AnimationData[40], &g_RStage15Entity29AnimationData[46],
    &g_RStage15Entity29AnimationData[62], &g_RStage15Entity29AnimationData[80],
};
