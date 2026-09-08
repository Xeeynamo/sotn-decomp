// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "stage_16.h"

typedef struct {
    u8* animation;
    s32 velocityX;
    s32 velocityY;
} Entity15Attack;

EntityEntry g_Stage16EntityEntry15 = {&g_EntitySpriteBank14, func_060E1928};

s16 g_Stage16Entity15CollisionSensors[8][2] = {
    {0, 16}, {0, 4}, {8, -4}, {-16, 0}, {0, 16}, {12, 0}, {-12, 16}, {0, -16},
};

u8 g_Stage16Entity15Animation0[8] = {8, 0xB, 7, 0xC, 8, 0xD, 7, 0xC};
u32 g_Stage16Entity15Animation0Padding = 0;
u8 g_Stage16Entity15Animation1[8] = {
    5, 0xD, 5, 0xC, 5, 0xB, 0xFF, 0,
};
u8 g_Stage16Entity15Animation2[8] = {
    5, 0xE, 5, 0xD, 5, 1, 0xFF, 0,
};
u8 g_Stage16Entity15Animation3[44] = {
    0x20, 1, 1,   2,   1, 3, 1, 4, 0x11, 5, 0x1C, 6, 1,    7,    1,
    8,    1, 7,   1,   8, 1, 7, 2, 8,    2, 7,    3, 8,    0x20, 7,
    8,    9, 0xC, 0xA, 7, 5, 4, 4, 4,    3, 0x10, 2, 0xFF, 0,
};
u8 g_Stage16Entity15Animation4[36] = {
    0x11, 1,    0x1C, 0xF,  1, 0x10, 1, 0x11, 1,    0x10, 1,    0x11,
    1,    0x10, 2,    0x11, 2, 0x10, 3, 0x11, 0x20, 0x10, 8,    9,
    0xC,  0xA,  7,    5,    4, 4,    4, 3,    0x10, 2,    0xFF, 0,
};
u8 g_Stage16Entity15Animation5[24] = {
    0xC, 0xA,  0x20, 0x12, 0x1C, 0x13, 1, 0x14, 1, 0x15, 1,    0x14,
    1,   0x15, 1,    0x14, 2,    0x15, 2, 0x14, 3, 0x15, 0x10, 0x14,
};
u8 g_Stage16Entity15Animation6[44] = {
    0x10, 1, 1,   2,   1, 3, 1, 4, 0x10, 5, 0x1C, 6, 1,    7,    1,
    8,    1, 7,   1,   8, 1, 7, 2, 8,    2, 7,    3, 8,    0x20, 7,
    8,    9, 0xC, 0xA, 7, 5, 4, 4, 4,    3, 0x10, 2, 0xFF, 0,
};
u8 g_Stage16Entity15Animation7[42] = {
    0x1C, 0xB,  1,    0x21, 1,    0x22, 0x10, 0x23, 0x1C, 0x24, 1,
    0x25, 1,    0x26, 1,    0x25, 1,    0x26, 1,    0x25, 2,    0x26,
    2,    0x25, 3,    0x26, 0x20, 0x25, 8,    0x27, 0xC,  0x28, 3,
    0x23, 3,    0x22, 3,    0x21, 0x10, 0xB,  0xFF, 0,
};
u16 g_Stage16Entity15AnimationPadding = 0;

Entity15Attack g_Stage16Entity15Attacks[4] = {
    {g_Stage16Entity15Animation3, 0x0600000A, (s32)0xFFFE0000},
    {g_Stage16Entity15Animation4, 0x0F00000A, 0x00020000},
    {g_Stage16Entity15Animation7, 0x24000008, (s32)0xFFF10000},
    {g_Stage16Entity15Animation5, 0x1306000A, 0x00020000},
};

s32 g_Stage16Entity15PartVelocityX[8] = {
    0x0000C000, 0x0001C000, 0x00018000, 0x00010000,
    0x00020000, 0x0001C000, 0x0000C000, 0x00018000,
};
s32 g_Stage16Entity15PartVelocityY[8] = {
    -0x50000, -0x30000, -0x20000, -0x30000,
    -0x40000, -0xE000,  -0x40000, -0x20000,
};
u8 g_Stage16Entity15PartFrames[8] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x14, 0x28,
};
