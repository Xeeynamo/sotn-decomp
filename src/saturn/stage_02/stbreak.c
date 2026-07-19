// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern struct SpriteParts* g_Stage02SpriteBank00[];
extern struct SpriteParts* g_Stage02SpriteBank18[];
extern SaturnSpriteResource g_Stage02SharedBreakableResource;
extern SaturnSpriteFrameHeader* g_Stage02SharedBreakableFrames[22];

extern u8 g_Stage02BreakableFrameData0[];
extern u8 g_Stage02BreakableFrameData2[];

u8 g_Stage02BreakableAnimType0[8] = {4, 1, 4, 2, 0, 0};
u8 g_Stage02BreakableAnimType1[12] = {4, 4, 4, 5, 4, 6, 4, 5, 0, 0};
u8 g_Stage02BreakableAnimType2[10] = {
    4, 14, 4, 15, 4, 16, 4, 17, 0, 0,
};

s16 g_Stage02BreakablePrimitiveOffsets[7] = {
    -15, -16, -17, -15, -13, -14, 0,
};

u8* g_Stage02BreakableAnimations[8] = {
    g_Stage02BreakableAnimType0,
    g_Stage02BreakableAnimType1,
    g_Stage02BreakableAnimType2,
};

u8 g_Stage02BreakableHitboxHeights[8] = {8, 8, 8};
u8 g_Stage02BreakableExplosionTypes[8] = {0};

void* g_Stage02BreakableSpriteBanks[8] = {
    g_Stage02SpriteBank00,
    &g_Stage02SharedBreakableResource,
    g_Stage02SpriteBank18,
};

void* g_Stage02BreakableFrameData[8] = {
    g_Stage02BreakableFrameData0,
    g_Stage02SharedBreakableFrames,
    g_Stage02BreakableFrameData2,
};

u8 g_Stage02BreakableBlendModes[8] = {0x70, 0x70, 0x30};
