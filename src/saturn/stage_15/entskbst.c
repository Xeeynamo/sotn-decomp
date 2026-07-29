// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank23;

void func_060E65CC(Entity* self);
void func_060E6B30(Entity* self);
void func_060E6CB8(Entity* self);

EntityEntry g_Stage15EntitySkeletonBeast = {
    &g_Stage15SpriteBank23, func_060E65CC};
EntityEntry g_Stage15EntityEntry33 = {NULL, func_060E6B30};
s16 g_Stage15SkeletonBeastRiderInitOffsets[4][2] = {0};
EntityEntry g_Stage15EntityEntry32 = {NULL, func_060E6CB8};
s16 g_Stage15SkeletonBeastBoneInitOffsets[4][2] = {0};

u8 g_Stage15SkeletonBeastAnimationData[] = {
    /* Idle */
    6,
    1,
    4,
    1,
    4,
    2,
    6,
    3,
    5,
    4,
    5,
    5,
    0xFF,
    0xFF,
    /* Walk */
    6,
    1,
    4,
    2,
    4,
    3,
    6,
    4,
    5,
    5,
    5,
    6,
    0xFF,
    0xFF,
    /* Walk back */
    6,
    1,
    5,
    6,
    5,
    5,
    6,
    4,
    4,
    3,
    4,
    2,
    0xFF,
    0xFF,
    /* Attack */
    5,
    7,
    6,
    8,
    5,
    9,
    5,
    0xA,
    5,
    0xB,
    5,
    0xC,
    0xFF,
    0xFF,
    /* Jump */
    1,
    1,
    4,
    0xD,
    4,
    0xE,
    1,
    1,
    0xFF,
    0xFF,
    /* Land */
    1,
    1,
    4,
    0xD,
    6,
    0xE,
    4,
    0xD,
    1,
    1,
    0xFF,
    0xFF,
};
u16 g_Stage15SkeletonBeastAnimationsPadding = 0;
u8* g_Stage15SkeletonBeastAnimations[] = {
    &g_Stage15SkeletonBeastAnimationData[0],
    &g_Stage15SkeletonBeastAnimationData[14],
    &g_Stage15SkeletonBeastAnimationData[28],
    &g_Stage15SkeletonBeastAnimationData[42],
    &g_Stage15SkeletonBeastAnimationData[56],
    &g_Stage15SkeletonBeastAnimationData[66],
};
