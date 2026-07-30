// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "../shared_sprite_banks.h"

extern SaturnSpriteResource g_Stage15SpriteBank16;
extern SaturnSpriteFrameHeader* g_Stage15SpriteBank16Frames[];
extern SaturnSpriteResource g_Stage15SpriteBank19;
extern SaturnSpriteResource g_Stage15SpriteBank20;
extern SaturnSpriteFrameHeader* g_Stage15SpriteBank20Frames[];
extern SaturnSpriteResource g_Stage15SpriteBank21;
extern SaturnSpriteFrameHeader* g_Stage15SpriteBank21Frames[];
extern SaturnSpriteResource g_Stage15SpriteBank22;
extern SaturnSpriteResource g_Stage15SpriteBank32;

void func_060DC040(Entity* self);
void func_060DC428(Entity* self);
void func_060DC4B8(Entity* self);
void func_060DC838(Entity* self);
void func_060DD37C(Entity* self);
void func_060DD898(Entity* self);
void func_060DDCE8(Entity* self);
void func_060DDFB0(Entity* self);
void func_060DE264(Entity* self);
void func_060DE2F4(Entity* self);
void func_060DE464(Entity* self);
void func_060DE670(Entity* self);
void func_060DE704(Entity* self);
void func_060DE964(Entity* self);
void func_060DECE0(Entity* self);
void func_060DF160(Entity* self);
void func_060DF204(Entity* self);
void func_060DF354(Entity* self);

typedef struct {
    SaturnSpriteResource* resource;
    SaturnSpriteFrameHeader** frames;
    s16* primitiveOffsets;
    u8* animation;
    u8 palette;
    u8 hitboxHeight;
    u8 explosionType;
    u8 primitiveCount;
    u16 spriteFlags;
    s16 spriteOffsetY;
} BreakableConfig;

typedef struct {
    SaturnSpriteResource* resource;
    SaturnSpriteFrameHeader** frames;
    u16 spriteFlags;
    u16 drawPriority;
    u8 drawMode;
    u8 palette;
    u8 facing;
    u8 hitboxWidth;
    u32 state;
    u32 entityFlags;
    u8* animation;
} Entity17Variant;

typedef struct {
    SaturnSpriteResource* spriteResource;
    SaturnSpriteFrameHeader** frameData;
    u16 variant;
    u16 drawPriority;
    u8* animation;
} Entity68AnimationConfig;

EntityEntry g_Stage15EntityEntry00 = {NULL, func_060DC040};
u8 g_Stage15BreakableAnimation[8] = {
    5, 0x26, 5, 0x27, 5, 0x28, 5, 0x29,
};
u16 g_Stage15BreakableAnimationPadding = 0;
s16 g_Stage15BreakablePrimitiveOffsets[4][5] = {
    {-17, -34, 26, 0, 0},
    {-16, -33, 27, 0, 0},
    {-17, -34, 26, 0, 0},
    {-15, -32, 28, 0, 0},
};
u16 g_Stage15BreakablePrimitiveOffsetsPadding = 0;
BreakableConfig g_Stage15BreakableConfigs[2] = {
    {
        &g_Stage15SpriteBank16,
        g_Stage15SpriteBank16Frames,
        g_Stage15BreakablePrimitiveOffsets[0],
        g_Stage15BreakableAnimation,
        0,
        8,
        0x70,
        3,
        0,
        -16,
    },
    {
        &g_Stage15SpriteBank16,
        g_Stage15SpriteBank16Frames,
        g_Stage15BreakablePrimitiveOffsets[0],
        g_Stage15BreakableAnimation,
        0,
        8,
        0x70,
        3,
        0,
        -16,
    },
};

EntityEntry g_Stage15EntityEntry17 = {&g_Stage15SpriteBank16, func_060DC428};
u8 g_Stage15Entity17Animations[6][4] = {
    {0x10, 0x24, 0, 0}, {0x10, 0x25, 0, 0}, {0x10, 1, 0, 0},
    {0x10, 2, 0, 0},    {0x10, 3, 0, 0},    {0x10, 1, 0, 0},
};
Entity17Variant g_Stage15Entity17Variants[6] = {
    {
        &g_Stage15SpriteBank16,
        g_Stage15SpriteBank16Frames,
        0,
        0x60,
        1,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[0],
    },
    {
        &g_Stage15SpriteBank16,
        g_Stage15SpriteBank16Frames,
        0,
        0x60,
        1,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[1],
    },
    {
        &g_Stage15SpriteBank20,
        g_Stage15SpriteBank20Frames,
        0,
        0x20,
        3,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[2],
    },
    {
        &g_Stage15SpriteBank20,
        g_Stage15SpriteBank20Frames,
        0,
        0x20,
        1,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[3],
    },
    {
        &g_Stage15SpriteBank20,
        g_Stage15SpriteBank20Frames,
        0,
        0x20,
        3,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[4],
    },
    {
        &g_Stage15SpriteBank21,
        g_Stage15SpriteBank21Frames,
        0,
        0x20,
        2,
        0,
        0,
        0,
        0,
        0,
        g_Stage15Entity17Animations[5],
    },
};

EntityEntry g_Stage15EntityEntry16 = {NULL, func_060DC4B8};
u8 g_Stage15Entity16Animation[8] = {
    7, 0x77, 7, 0x78, 6, 0x48, 2, 0x14,
};
u16 g_Stage15Entity16Parameters[6] = {0, 0x1B9, 0x200, 7, 7, 0};
s16 g_Stage15Entity16DirectionOffsets[7] = {0, 1, 2, 4, -1, -2, -4};
u16 g_Stage15Entity16Padding = 0;

EntityEntry g_Stage15EntityEntry22 = {NULL, func_060DC838};
EntityEntry g_Stage15EntityEntry23 = {&g_Stage15SpriteBank19, func_060DD37C};
EntityEntry g_Stage15EntityEntry24 = {&g_Stage15SpriteBank19, func_060DD898};
EntityEntry g_Stage15EntityEntry25 = {&g_Stage15SpriteBank19, func_060DDCE8};
EntityEntry g_Stage15EntityEntry26 = {NULL, func_060DDFB0};
EntityEntry g_Stage15EntityEntry27 = {NULL, func_060DE264};

s32 g_Stage15Entity23InitialVelocities[4][2] = {
    {-0x68000, 0x4800},
    {-0x58000, 0x4400},
    {-0x48000, 0x4000},
    {-0x38000, 0x3C00},
};
u16 g_Stage15Entity23FrameOffsets[6] = {0, 2, 4, 6, 8, 10};
s32 g_Stage15Entity23PositionCurve[8][2] = {
    {22, -46}, {-24, -55}, {14, -62}, {-12, -45},
    {2, -74},  {-4, -52},  {9, -60},  {-6, -61},
};
u16 g_Stage15Entity23Angles[8] = {
    0, 0x100, 0x80, 0x40, 0xF00, 0xF80, 0xFC0, 0,
};
s32 g_Stage15Entity23PartVelocities[8] = {
    -0x18000, -0x1B000, -0xC000, -0x16000, -0x4000, -0x17000, -0x6000, -0x1E000,
};

EntityEntry g_Stage15EntityEntry20 = {NULL, func_060DE2F4};
EntityEntry g_Stage15EntityEntry21 = {&g_Stage15SpriteBank22, func_060DE464};
s16 g_Stage15Entity21SpawnConfigs[3][6] = {
    {0, 0, 0, 128, 0, 1},
    {0, 128, 0, 2, 0, 128},
    {0, 0, 0, 128, 0, 3},
};
s16 g_Stage15Entity21InitOffset[2] = {0, 20};
u8 g_Stage15Entity21Animation[10] = {
    0xA, 0, 0xA, 4, 0xA, 8, 0xA, 4, 0, 0,
};

EntityEntry g_Stage15EntityEntry28 = {NULL, func_060DE670};
u16 g_Stage15Entity28ModeTable[20] = {
    0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
};
EntityEntry g_Stage15EntityEntry67 = {NULL, func_060DE704};
EntityEntry g_Stage15EntityEntry68 = {&g_Stage15SpriteBank16, func_060DE964};
u8 g_Stage15Entity68Animation0[28] = {
    3, 1, 3, 2, 3, 3,   3, 4,   3, 5,   3, 6,   3,    7,
    3, 8, 3, 9, 3, 0xA, 3, 0xB, 3, 0xC, 3, 0xD, 0xFF, 0,
};
u8 g_Stage15Entity68Animation1[30] = {
    2, 1, 2, 2, 2,   3, 2,   4, 2,   5, 2,   6, 2,   7,    2,
    8, 2, 9, 2, 0xA, 2, 0xB, 2, 0xC, 2, 0xD, 2, 0xE, 0xFF, 0,
};
u16 g_Stage15Entity68AnimationPadding = 0;
Entity68AnimationConfig g_Stage15Entity68AnimationConfigs[4] = {
    {
        &g_SaturnSharedSpriteBank7Resource,
        g_SaturnSharedOpaquePuffFrames0,
        0,
        0x30,
        g_Stage15Entity68Animation0,
    },
    {
        &g_SaturnSharedSpriteBank9Resource,
        g_SaturnSharedOpaquePuffFrames1,
        0,
        0,
        g_Stage15Entity68Animation1,
    },
    {
        &g_SaturnSharedSpriteBank9Resource,
        g_SaturnSharedOpaquePuffFrames1,
        3,
        0,
        g_Stage15Entity68Animation1,
    },
    {
        &g_SaturnSharedSpriteBank7Resource,
        g_SaturnSharedOpaquePuffFrames0,
        4,
        0x30,
        g_Stage15Entity68Animation0,
    },
};

EntityEntry g_Stage15EntityEntry69 = {NULL, func_060DECE0};
EntityEntry g_Stage15EntityEntry29 = {NULL, func_060DF160};
EntityEntry g_Stage15EntityEntry30 = {&g_Stage15SpriteBank16, func_060DF204};
s16 g_Stage15Entity30SpawnPositions[4][2] = {
    {0, 200},
    {0, 280},
    {0, 190},
    {0, 240},
};
u8 g_Stage15Entity30Animation0[8] = {3, 1, 3, 2, 3, 3, 0, 0};
u8 g_Stage15Entity30Animation1[12] = {
    3, 0x13, 3, 0x14, 3, 0x15, 3, 0x16, 3, 0x17, 0xFF, 0xFF,
};
EntityEntry g_Stage15EntityEntry70 = {&g_Stage15SpriteBank32, func_060DF354};
u16 g_Stage15Entity70FrameMap[22] = {
    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
};
s16 g_Stage15Entity70PositionOffsets[6][2] = {
    {-8, 0}, {-8, 0}, {0, 0}, {8, 0}, {8, 0}, {0, 0},
};
