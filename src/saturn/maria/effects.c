// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u8 count;
    u8 red;
    u8 green;
    u8 blue;
    u8 width;
    u8 height;
    s16 priority;
    s16 drawMode;
    s16 effectType;
    u32 flags;
} MariaHitEffectDef;

s16 g_MariaSmokePuffPosX[] = {0, -4, -8, -12, -16, -20};

s32 g_MariaSmokePuffVelocityY[] = {
    -0x3000, -0x4000, -0x6000, -0x8000, -0xA000, -0xC000,
};

s16 g_MariaSmokePuffScale[] = {0x30, 0x40, 0x50, 0x60, 0x70, 0x80};

AnimationFrame g_MariaAnimSmokePuff[] = {
    POSE(1, 0x01, 0), POSE(1, 0x02, 0), POSE(1, 0x03, 0),
    POSE(1, 0x04, 0), POSE(1, 0x05, 0), POSE(1, 0x06, 0),
    POSE(1, 0x07, 0), POSE(1, 0x08, 0), POSE(1, 0x09, 0),
    POSE(1, 0x0A, 0), POSE(1, 0x0B, 0), POSE(1, 0x0C, 0),
    POSE(1, 0x0D, 0), POSE(1, 0x0E, 0), POSE(1, 0x0F, 0),
    POSE(1, 0x10, 0), POSE(1, 0x11, 0), POSE(1, 0x12, 0),
    POSE(1, 0x13, 0), POSE(1, 0x14, 0), POSE(1, 0x15, 0),
    POSE(1, 0x16, 0), POSE(1, 0x17, 0), POSE(1, 0x18, 0), POSE_END,
};

u8 g_MariaSmokePuffWallSensorsWide[] = {
    2, 9, 3, 10, 1, 8, 4, 11, 0, 7, 5, 12, 6, 13,
};
u16 g_MariaSmokePuffWallSensorsWidePadding = 0;

u8 g_MariaSmokePuffWallSensorsNarrow[] = {2, 9, 3, 10, 4, 11, 5, 12, 6, 13};
u16 g_MariaSmokePuffWallSensorsNarrowPadding = 0;

MariaHitEffectDef g_MariaHitEffectDefs[] = {
    {8, 0xC0, 0x60, 0x00, 1, 1, 4, 0x33, 3, 0x08800000},
    {16, 0xC0, 0xC0, 0xC0, 1, 1, 2, 0x33, 1, 0x0C800000},
    {8, 0x7F, 0x7F, 0x7F, 2, 2, 2, 0x33, 0, 0x08800000},
    {6, 0x7F, 0xFF, 0xFF, 1, 1, 4, 0x73, 3, 0x08800000},
    {12, 0xC0, 0x60, 0x00, 1, 1, 4, 0x33, 3, 0x08800000},
    {12, 0x7F, 0x00, 0x00, 3, 3, 2, 0x02, 4, 0x0C800000},
    {8, 0x1F, 0x1F, 0x7F, 1, 1, 4, 0x33, 6, 0x0C800000},
    {20, 0x7F, 0x7F, 0xC0, 1, 1, -2, 0x33, 7, 0x0C800000},
    {6, 0xC0, 0xC0, 0xC0, 2, 2, 2, 0x7B, 8, 0x08800000},
    {16, 0x7F, 0x7F, 0x7F, 1, 1, 2, 0x33, 9, 0x08800000},
    {16, 0x80, 0x80, 0xFF, 1, 1, 2, 0x33, 10, 0x08800000},
};

MariaHitEffectDef* g_MariaHitEffectDefsByVariant[] = {
    &g_MariaHitEffectDefs[0],  &g_MariaHitEffectDefs[1],
    &g_MariaHitEffectDefs[2],  &g_MariaHitEffectDefs[3],
    &g_MariaHitEffectDefs[4],  &g_MariaHitEffectDefs[5],
    &g_MariaHitEffectDefs[6],  &g_MariaHitEffectDefs[7],
    &g_MariaHitEffectDefs[8],  &g_MariaHitEffectDefs[9],
    &g_MariaHitEffectDefs[10],
};

AnimationFrame g_MariaAnimMultipleEmbersA[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 5, 0), POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0), POSE(1, 6, 0),
    POSE(1, 7, 0), POSE(1, 8, 0), POSE_END,
};

AnimationFrame g_MariaAnimMultipleEmbersB[] = {
    POSE(1, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE(2, 15, 0), POSE(2, 16, 0),
    POSE(2, 17, 0), POSE(2, 18, 0), POSE(3, 19, 0), POSE(4, 20, 0),
    POSE_END,
};

AnimationFrame g_MariaAnimRisingEmber[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 5, 0), POSE(2, 6, 0), POSE(2, 7, 0), POSE(2, 8, 0),
    POSE_END,
};
