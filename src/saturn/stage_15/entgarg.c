// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank24;

void func_060E6EA0(Entity* self);
void func_060E7564(Entity* self);
void func_060E7780(Entity* self);

EntityEntry g_Stage15EntityRedGargoyle = {
    &g_Stage15SpriteBank24, func_060E6EA0};

/* Working velocities used while the gargoyle emits its attack entities. */
s32 g_Stage15RedGargoyleAttackVelocities[3] = {FIX(2), FIX(2), 0};

EntityEntry g_Stage15EntityEntry35 = {&g_Stage15SpriteBank24, func_060E7564};
s32 g_Stage15RedGargoyleAttackEntityParams[2] = {2, 0};

EntityEntry g_Stage15EntityEntry36 = {&g_Stage15SpriteBank24, func_060E7780};

u8 g_Stage15RedGargoyleAnimationData[] = {
    /* Idle */
    0x62,
    1,
    0x62,
    0x3A,
    0x62,
    0x3B,
    0xFF,
    0xFF,
    /* Wake */
    3,
    2,
    1,
    3,
    1,
    2,
    1,
    3,
    1,
    4,
    1,
    3,
    0x2B,
    4,
    6,
    5,
    6,
    6,
    6,
    7,
    6,
    8,
    0x29,
    4,
    7,
    9,
    0x1A,
    0xA,
    2,
    0xB,
    3,
    0xC,
    3,
    0xD,
    4,
    0xE,
    0xFF,
    0xFF,
    /* Attack */
    6,
    0x10,
    4,
    0x11,
    7,
    0x12,
    2,
    0x13,
    5,
    0x14,
    0,
    0,
    /* Recover */
    0xB,
    0x15,
    0x13,
    0x16,
    2,
    0x17,
    2,
    0x18,
    5,
    0x19,
    0xB,
    0x1A,
    9,
    0x1B,
    7,
    0x1C,
    8,
    0x1D,
    0xA,
    0x1E,
    0xFF,
    0xFF,
    /* Death */
    7,
    0x1F,
    7,
    0x20,
    7,
    0x21,
    7,
    0x22,
    7,
    0x23,
    7,
    0x24,
    7,
    0x25,
    7,
    0x26,
    7,
    0x27,
    7,
    0x28,
    0xFF,
    0xFF,
};
u16 g_Stage15RedGargoyleAnimationsPadding = 0;
u8* g_Stage15RedGargoyleAnimations[] = {
    &g_Stage15RedGargoyleAnimationData[0],
    &g_Stage15RedGargoyleAnimationData[8],
    &g_Stage15RedGargoyleAnimationData[46],
    &g_Stage15RedGargoyleAnimationData[58],
    &g_Stage15RedGargoyleAnimationData[80],
};
