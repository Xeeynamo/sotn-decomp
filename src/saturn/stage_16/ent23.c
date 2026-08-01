// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank20;

void func_060E34CC(Entity* self);
void func_060E3D00(Entity* self);

EntityEntry g_Stage16EntityEntry23 = {&g_Stage16SpriteBank20, func_060E34CC};
s16 g_Stage16Entity23InitOffset[2] = {0, -16};
EntityEntry g_Stage16EntityEntry24 = {&g_Stage16SpriteBank20, func_060E3D00};

u8 g_Stage16Entity23AnimationData[] = {
    8,    0xB,  7,    0xC,  8,    0xD,  7,    0xC,  0xFF, 0xFF, 0x31, 1,
    1,    2,    1,    3,    1,    4,    0x11, 5,    0x1C, 6,    1,    7,
    1,    8,    1,    7,    1,    8,    1,    7,    2,    8,    2,    7,
    3,    8,    0x30, 7,    8,    9,    0xC,  0xA,  7,    5,    4,    4,
    4,    3,    0x10, 2,    0xFF, 0xFF, 0x11, 1,    0x1C, 0xF,  1,    0x10,
    1,    0x11, 1,    0x10, 1,    0x11, 1,    0x10, 2,    0x11, 2,    0x10,
    3,    0x11, 0x30, 0x10, 8,    9,    0xC,  0xA,  7,    5,    4,    4,
    4,    3,    0x10, 2,    0xFF, 0xFF, 0x30, 0x12, 0x18, 0x13, 1,    0x14,
    1,    0x15, 1,    0x14, 1,    0x15, 1,    0x14, 2,    0x15, 2,    0x14,
    3,    0x15, 0x10, 0x14, 0x10, 1,    1,    2,    1,    3,    1,    4,
    0x10, 5,    0x1C, 6,    1,    7,    1,    8,    1,    7,    1,    8,
    1,    7,    2,    8,    2,    7,    3,    8,    0x30, 7,    8,    9,
    0xC,  0xA,  7,    5,    4,    4,    4,    3,    0x10, 2,    0xFF, 0xFF,
    0x1C, 0xB,  1,    0x21, 1,    0x22, 0x10, 0x23, 0x1C, 0x24, 1,    0x25,
    1,    0x26, 1,    0x25, 1,    0x26, 1,    0x25, 2,    0x26, 2,    0x25,
    3,    0x26, 0x20, 0x25, 8,    0x27, 0xC,  0x28, 3,    0x23, 3,    0x22,
    3,    0x21, 0x10, 0xB,  0xFF, 0xFF,
};
u16 g_Stage16Entity23AnimationsPadding = 0;
u8* g_Stage16Entity23Animations[] = {
    &g_Stage16Entity23AnimationData[0],   &g_Stage16Entity23AnimationData[10],
    &g_Stage16Entity23AnimationData[54],  &g_Stage16Entity23AnimationData[90],
    &g_Stage16Entity23AnimationData[156],
};
