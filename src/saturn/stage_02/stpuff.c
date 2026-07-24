// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

typedef struct {
    void* spriteBank;
    SaturnSpriteFrameHeader** frameData;
    u16 palette;
    u8 padding;
    u8 blendMode;
    u8* animation;
} Stage02OpaquePuffConfig;

u8 g_Stage02OpaquePuffAnimType0[28] = {
    3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3,    7,
    3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, 0xFF, 0,
};

u8 g_Stage02OpaquePuffAnimType1[32] = {
    2, 1, 2, 2,  2, 3,  2, 4,  2, 5,  2, 6,  2,    7, 2, 8,
    2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 2, 14, 0xFF, 0, 0, 0,
};

Stage02OpaquePuffConfig g_Stage02OpaquePuffConfigs[4] = {
    {&g_SaturnSharedSpriteBank7Resource, g_SaturnSharedOpaquePuffFrames0, 0, 0,
     0x30, g_Stage02OpaquePuffAnimType0},
    {&g_SaturnSharedSpriteBank9Resource, g_SaturnSharedOpaquePuffFrames1, 0, 0,
     0, g_Stage02OpaquePuffAnimType1},
    {&g_SaturnSharedSpriteBank9Resource, g_SaturnSharedOpaquePuffFrames1, 3, 0,
     0, g_Stage02OpaquePuffAnimType1},
    {&g_SaturnSharedSpriteBank7Resource, g_SaturnSharedOpaquePuffFrames0, 4, 0,
     0x30, g_Stage02OpaquePuffAnimType0},
};
