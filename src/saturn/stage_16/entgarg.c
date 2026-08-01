// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank24;

void func_060E63A8(Entity* self);
void func_060E6A6C(Entity* self);
void func_060E6C88(Entity* self);

EntityEntry g_Stage16EntityGargoyle = {&g_Stage16SpriteBank24, func_060E63A8};

/* Working velocities used while the gargoyle emits its attack entities. */
s32 g_Stage16GargoyleAttackVelocities[3] = {FIX(2), FIX(2), 0};

EntityEntry g_Stage16EntityEntry33 = {&g_Stage16SpriteBank24, func_060E6A6C};
s32 g_Stage16GargoyleAttackEntityParams[2] = {2, 0};

EntityEntry g_Stage16EntityEntry34 = {&g_Stage16SpriteBank24, func_060E6C88};

u8 g_Stage16GargoyleAnimationData[] = {
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
u16 g_Stage16GargoyleAnimationsPadding = 0;
u8* g_Stage16GargoyleAnimations[] = {
    &g_Stage16GargoyleAnimationData[0],  &g_Stage16GargoyleAnimationData[8],
    &g_Stage16GargoyleAnimationData[46], &g_Stage16GargoyleAnimationData[58],
    &g_Stage16GargoyleAnimationData[80],
};
