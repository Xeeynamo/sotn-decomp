// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank22;

void func_060E4CF4(Entity* self);
void func_060E5258(Entity* self);
void func_060E53E0(Entity* self);

EntityEntry g_Stage16EntitySkeletonBeast = {
    &g_Stage16SpriteBank22, func_060E4CF4};
EntityEntry g_Stage16EntityEntry30 = {NULL, func_060E5258};
s16 g_Stage16SkeletonBeastRiderInitOffsets[4][2] = {0};
EntityEntry g_Stage16EntityEntry29 = {NULL, func_060E53E0};
s16 g_Stage16SkeletonBeastBoneInitOffsets[4][2] = {0};

u8 g_Stage16SkeletonBeastAnimationData[] = {
    6,    1,    4,    1,    4,   2, 6,   3,   5,   4,   5,   5,    0xFF,
    0xFF, 6,    1,    4,    2,   4, 3,   6,   4,   5,   5,   5,    6,
    0xFF, 0xFF, 6,    1,    5,   6, 5,   5,   6,   4,   4,   3,    4,
    2,    0xFF, 0xFF, 5,    7,   6, 8,   5,   9,   5,   0xA, 5,    0xB,
    5,    0xC,  0xFF, 0xFF, 1,   1, 4,   0xD, 4,   0xE, 1,   1,    0xFF,
    0xFF, 1,    1,    4,    0xD, 6, 0xE, 4,   0xD, 1,   1,   0xFF, 0xFF,
};
u16 g_Stage16SkeletonBeastAnimationsPadding = 0;
u8* g_Stage16SkeletonBeastAnimations[] = {
    &g_Stage16SkeletonBeastAnimationData[0],
    &g_Stage16SkeletonBeastAnimationData[14],
    &g_Stage16SkeletonBeastAnimationData[28],
    &g_Stage16SkeletonBeastAnimationData[42],
    &g_Stage16SkeletonBeastAnimationData[56],
    &g_Stage16SkeletonBeastAnimationData[66],
};
