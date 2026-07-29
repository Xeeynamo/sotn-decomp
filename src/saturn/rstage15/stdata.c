// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage15SpriteBank16;
extern SaturnSpriteFrameHeader* g_RStage15SpriteBank16Frames[];
extern SaturnSpriteResource g_RStage15SpriteBank18;
extern SaturnSpriteResource g_RStage15SpriteBank19;
extern SaturnSpriteFrameHeader* g_RStage15SpriteBank19Frames[];
extern SaturnSpriteResource g_RStage15SpriteBank20;
extern SaturnSpriteFrameHeader* g_RStage15SpriteBank20Frames[];
extern SaturnSpriteResource g_RStage15SpriteBank21;

void func_060DC040(Entity* self);
void func_060DC3A4(Entity* self);
void func_060DC434(Entity* self);
void func_060DC580(Entity* self);
void func_060DCD58(Entity* self);
void func_060DD488(Entity* self);
void func_060DD988(Entity* self);
void func_060DDD10(Entity* self);
void func_060DDFD4(Entity* self);
void func_060DE268(Entity* self);
void func_060DE40C(Entity* self);
void func_060DE654(Entity* self);

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

EntityEntry g_RStage15EntityEntry00 = {NULL, func_060DC040};
u8 g_RStage15BreakableAnimation[8] = {
    5, 0x26, 5, 0x27, 5, 0x28, 5, 0x29,
};
u16 g_RStage15BreakableAnimationPadding = 0;
s16 g_RStage15BreakablePrimitiveOffsets[4][5] = {
    {-23, 6, 26, 0, 0},
    {-16, 7, 27, 0, 0},
    {-23, 6, 26, 0, 0},
    {-17, 8, 28, 0, 0},
};
BreakableConfig g_RStage15BreakableConfig = {
    &g_RStage15SpriteBank16,
    g_RStage15SpriteBank16Frames,
    g_RStage15BreakablePrimitiveOffsets[0],
    g_RStage15BreakableAnimation,
    0,
    8,
    0x70,
    3,
    0,
    -16,
};

EntityEntry g_RStage15EntityEntry17 = {&g_RStage15SpriteBank16, func_060DC3A4};
u8 g_RStage15Entity17Animations[6][4] = {
    {0x10, 0x24, 0, 0}, {0x10, 0x25, 0, 0}, {0x10, 1, 0, 0},
    {0x10, 2, 0, 0},    {0x10, 3, 0, 0},    {0x10, 1, 0, 0},
};
Entity17Variant g_RStage15Entity17Variants[6] = {
    {
        &g_RStage15SpriteBank16,
        g_RStage15SpriteBank16Frames,
        0,
        0x60,
        1,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[0],
    },
    {
        &g_RStage15SpriteBank16,
        g_RStage15SpriteBank16Frames,
        0,
        0x60,
        1,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[1],
    },
    {
        &g_RStage15SpriteBank19,
        g_RStage15SpriteBank19Frames,
        0,
        0x20,
        3,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[2],
    },
    {
        &g_RStage15SpriteBank19,
        g_RStage15SpriteBank19Frames,
        0,
        0x20,
        1,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[3],
    },
    {
        &g_RStage15SpriteBank19,
        g_RStage15SpriteBank19Frames,
        0,
        0x20,
        3,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[4],
    },
    {
        &g_RStage15SpriteBank20,
        g_RStage15SpriteBank20Frames,
        0,
        0x20,
        2,
        0,
        0,
        0,
        0,
        0,
        g_RStage15Entity17Animations[5],
    },
};

EntityEntry g_RStage15EntityEntry16 = {NULL, func_060DC434};
u8 g_RStage15Entity16Animation[8] = {
    7, 0x77, 7, 0x78, 6, 0x48, 2, 0x14,
};
u16 g_RStage15Entity16Parameters[6] = {0, 0x1B9, 0x200, 7, 7, 0};
s16 g_RStage15Entity16DirectionOffsets[7] = {0, 1, 2, 4, -1, -2, -4};
u16 g_RStage15Entity16Padding = 0;

EntityEntry g_RStage15EntityEntry22 = {NULL, func_060DC580};
EntityEntry g_RStage15EntityEntry23 = {&g_RStage15SpriteBank18, func_060DCD58};
EntityEntry g_RStage15EntityEntry24 = {&g_RStage15SpriteBank18, func_060DD488};
EntityEntry g_RStage15EntityEntry25 = {&g_RStage15SpriteBank18, func_060DD988};
EntityEntry g_RStage15EntityEntry26 = {NULL, func_060DDD10};
EntityEntry g_RStage15EntityEntry27 = {NULL, func_060DDFD4};

s32 g_RStage15Entity23InitialVelocities[4][2] = {
    {-0x68000, 0x4800},
    {-0x58000, 0x4400},
    {-0x48000, 0x4000},
    {-0x38000, 0x3C00},
};
u16 g_RStage15Entity23FrameOffsets[6] = {0, 2, 4, 6, 8, 10};
s32 g_RStage15Entity23PositionCurve[8][2] = {
    {22, -46}, {-24, -55}, {14, -62}, {-12, -45},
    {2, -74},  {-4, -52},  {9, -60},  {-6, -61},
};
u16 g_RStage15Entity23Angles[8] = {
    0, 0x100, 0x80, 0x40, 0xF00, 0xF80, 0xFC0, 0,
};
s32 g_RStage15Entity23PartVelocities[8] = {
    -0x18000, -0x1B000, -0xC000, -0x16000, -0x4000, -0x17000, -0x6000, -0x1E000,
};

EntityEntry g_RStage15EntityEntry20 = {NULL, func_060DE268};
EntityEntry g_RStage15EntityEntry21 = {&g_RStage15SpriteBank21, func_060DE40C};
s16 g_RStage15Entity21SpawnConfigs[3][6] = {
    {0, 0, 0, 128, 0, 1},
    {0, 128, 0, 2, 0, 128},
    {0, 0, 0, 128, 0, 3},
};
s16 g_RStage15Entity21InitOffset[2] = {0, 20};
u8 g_RStage15Entity21Animation[10] = {
    0xA, 0, 0xA, 4, 0xA, 8, 0xA, 4, 0, 0,
};
EntityEntry g_RStage15EntityEntry28 = {NULL, func_060DE654};
