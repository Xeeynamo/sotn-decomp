// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    struct SpriteParts** spriteBank;
    u8* frameData;
    u16 palette;
    u8 padding;
    u8 blendMode;
    u8* animation;
} Stage02OpaquePuffConfig;

extern struct SpriteParts* g_Stage02SpriteBank07[];
extern struct SpriteParts* g_Stage02SpriteBank09[];
extern u8 g_Stage02OpaquePuffFrameData0[];
extern u8 g_Stage02OpaquePuffFrameData1[];

u8 g_Stage02OpaquePuffAnimType0[28] = {
    3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3,    7,
    3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, 0xFF, 0,
};

u8 g_Stage02OpaquePuffAnimType1[32] = {
    2, 1, 2, 2,  2, 3,  2, 4,  2, 5,  2, 6,  2,    7, 2, 8,
    2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 2, 14, 0xFF, 0, 0, 0,
};

Stage02OpaquePuffConfig g_Stage02OpaquePuffConfigs[4] = {
    {g_Stage02SpriteBank07, g_Stage02OpaquePuffFrameData0, 0, 0, 0x30,
     g_Stage02OpaquePuffAnimType0},
    {g_Stage02SpriteBank09, g_Stage02OpaquePuffFrameData1, 0, 0, 0,
     g_Stage02OpaquePuffAnimType1},
    {g_Stage02SpriteBank09, g_Stage02OpaquePuffFrameData1, 3, 0, 0,
     g_Stage02OpaquePuffAnimType1},
    {g_Stage02SpriteBank07, g_Stage02OpaquePuffFrameData0, 4, 0, 0x30,
     g_Stage02OpaquePuffAnimType0},
};
