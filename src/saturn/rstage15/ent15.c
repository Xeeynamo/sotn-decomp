// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_EntitySpriteBank14;

void func_060E2A90(Entity* self);

typedef struct {
    s8 spriteOffsetX;
    s8 spriteOffsetY;
    u8 hitboxWidth;
    u8 hitboxHeight;
} Entity15FrameGeometry;

EntityEntry g_RStage15EntityEntry15 = {&g_EntitySpriteBank14, func_060E2A90};

s16 g_RStage15Entity15CollisionSensors[6][2] = {
    {0, 25}, {0, 4}, {8, -4}, {-16, 0}, {0, 25}, {12, 0},
};

u8 g_RStage15Entity15Animation0[8] = {
    6, 2, 6, 3, 0x40, 4, 0xFF, 0,
};
u8 g_RStage15Entity15Animation1[8] = {
    4, 5, 6, 1, 4, 6, 0xFF, 0,
};
u8 g_RStage15Entity15Animation2[8] = {
    6, 7, 8, 8, 6, 9, 0xFF, 0,
};
u8 g_RStage15Entity15Animation3[16] = {
    0x10, 1, 2, 0xA, 2, 0xB, 0x14, 0xA, 1, 0x12, 1, 0x11, 1, 0x10, 0xFF, 0,
};
u8 g_RStage15Entity15Animation4[4] = {1, 0xD, 1, 0xE};
u32 g_RStage15Entity15Animation4Padding = 0;
u8 g_RStage15Entity15Animation5[16] = {
    8, 1, 0x16, 0xC, 1, 0xE, 1, 0xD, 1, 0xF, 1, 0x11, 1, 0x12, 0xFF, 0,
};

u8 g_RStage15Entity15Animation6[20] = {
    1, 0x15, 1, 0x16, 1, 0x17, 1, 0x18, 1,    0x19,
    1, 0x1A, 1, 0x1B, 1, 0x1C, 1, 0,    0xFF, 0,
};
u8 g_RStage15Entity15Animation7[12] = {
    2, 0x1D, 2, 0x1E, 2, 0x1F, 2, 0x20, 2, 0x21, 2, 0x22,
};
u32 g_RStage15Entity15AnimationPadding = 0;

Entity15FrameGeometry g_RStage15Entity15FrameGeometry[5] = {
    {0, 0, 0, 0}, {1, 7, 4, 18}, {1, 3, 7, 14}, {4, 0, 4, 24}, {0, 5, 5, 20},
};
u8 g_RStage15Entity15FrameGeometryIndices[22] = {
    0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 2, 0,
};
s16 g_RStage15Entity15SpawnOffset[2] = {0, 25};
u16 g_RStage15Entity15DataPadding = 0;
