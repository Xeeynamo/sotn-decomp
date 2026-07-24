// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage02TableWithGlobeResource;
extern SaturnSpriteResource entityRedEyeBustData;
extern SaturnSpriteFrameHeader* entityRedEyeBustData2[22];
extern SaturnSpriteFrameHeader* g_Stage02TableWithGlobeFrames[19];

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
    &g_SaturnSharedSpriteBank0Resource,
    &entityRedEyeBustData,
    &g_Stage02TableWithGlobeResource,
};

SaturnSpriteFrameHeader** g_Stage02BreakableFrameData[8] = {
    g_SaturnSharedBreakableFrames,
    entityRedEyeBustData2,
    g_Stage02TableWithGlobeFrames,
};

u8 g_Stage02BreakableBlendModes[8] = {0x70, 0x70, 0x30};
