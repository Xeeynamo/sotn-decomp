// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank21;

void func_060E4210(Entity* self);
void func_060E49F0(Entity* self);
void func_060E4AEC(Entity* self);

EntityEntry g_Stage16EntityEntry25 = {&g_Stage16SpriteBank21, func_060E4210};

s16 g_Stage16Entity25PositionOffsets[43][2] = {
    {-28, 15},  {-24, 13},  {-24, 12},  {-23, -1},  {-29, 2},   {-29, -1},
    {-21, -24}, {1, -38},   {35, -7},   {-36, -16}, {-36, 0},   {3, 26},
    {4, 24},    {-20, 6},   {-29, -1},  {-28, -10}, {-20, 18},  {-27, 12},
    {-16, 0},   {-16, 0},   {-29, -1},  {-21, -24}, {1, -38},   {-6, -36},
    {3, -27},   {-16, -34}, {-25, -17}, {-48, -72}, {-64, -72}, {-64, -72},
    {-15, 21},  {3, 26},    {1, 38},    {1, 46},    {1, 54},    {1, 62},
    {-25, 0},   {-23, -27}, {1, -30},   {0, -47},   {0, -54},   {0, -62},
    {0, -70},
};
s16 g_Stage16Entity25HitboxSizes[43][2] = {
    {0, 0},  {8, 4},   {8, 4},   {16, 4},  {16, 4}, {16, 4}, {8, 8},  {4, 20},
    {8, 4},  {12, 24}, {16, 24}, {4, 12},  {4, 12}, {16, 4}, {16, 4}, {16, 4},
    {8, 8},  {8, 8},   {27, 25}, {27, 25}, {16, 4}, {8, 8},  {4, 20}, {4, 20},
    {8, 8},  {12, 4},  {0, 0},   {0, 0},   {0, 0},  {0, 0},  {4, 4},  {4, 8},
    {4, 20}, {4, 28},  {4, 36},  {4, 44},  {20, 4}, {8, 8},  {4, 8},  {4, 24},
    {4, 32}, {4, 40},  {4, 48},
};

EntityEntry g_Stage16EntityEntry26 = {NULL, func_060E49F0};
s16 g_Stage16Entity26InitOffset[2] = {0, 0};
EntityEntry g_Stage16EntityEntry27 = {&g_Stage16SpriteBank21, func_060E4AEC};

u8 g_Stage16Entity25AnimationData[] = {
    6,    1,    0x20, 2,    0xA,  3,    0xFF, 0xFF, 0x16, 4,    8,    5,
    0xFF, 0xFF, 6,    4,    8,    6,    0x25, 7,    6,    6,    0xFF, 0xFF,
    6,    4,    6,    8,    6,    9,    8,    0xA,  0x1F, 0xB,  2,    0xA,
    2,    0xC,  2,    0xD,  2,    0xE,  0x31, 0xF,  0xFF, 0xFF, 6,    4,
    6,    0x10, 6,    0x11, 6,    0x12, 1,    0x15, 1,    0x16, 1,    0x15,
    1,    0x16, 1,    0x15, 1,    0x16, 1,    0x15, 1,    0x16, 1,    0x15,
    1,    0x16, 6,    0x13, 6,    0x14, 0xFF, 0xFF, 6,    4,    6,    0x17,
    6,    0x18, 4,    0x19, 4,    0x1A, 0x26, 0x1B, 3,    0x1C, 3,    0x1D,
    0x16, 0x1E, 6,    0x1F, 0xFF, 0xFF, 0x16, 0x1F, 6,    0x20, 0xFF, 0xFF,
    6,    4,    6,    0x21, 0xF,  0x22, 3,    0x23, 3,    0x24, 3,    0x25,
    0x16, 0x26, 2,    0x25, 2,    0x24, 2,    0x23, 6,    0x22, 6,    0x21,
    0xFF, 0xFF, 6,    4,    6,    0x27, 6,    0x28, 0xF,  0x29, 3,    0x2A,
    3,    0x2B, 3,    0x2C, 0x16, 0x2D, 2,    0x2C, 2,    0x2B, 2,    0x2A,
    6,    0x29, 6,    0x28, 6,    0x27, 0xFF, 0xFF, 6,    0x3E, 2,    0x3F,
    2,    0x40, 2,    0x3F, 2,    0x40, 2,    0x3F, 0x12, 0x40, 0xFF, 0xFF,
};
u8* g_Stage16Entity25Animations[] = {
    &g_Stage16Entity25AnimationData[0],   &g_Stage16Entity25AnimationData[8],
    &g_Stage16Entity25AnimationData[14],  &g_Stage16Entity25AnimationData[24],
    &g_Stage16Entity25AnimationData[46],  &g_Stage16Entity25AnimationData[80],
    &g_Stage16Entity25AnimationData[102], &g_Stage16Entity25AnimationData[108],
    &g_Stage16Entity25AnimationData[134], &g_Stage16Entity25AnimationData[164],
};
