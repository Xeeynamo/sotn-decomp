// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank25;

void func_060E78B8(Entity* self);
void func_060E8A7C(Entity* self);
void func_060E8BBC(Entity* self);
void func_060E8D50(Entity* self);
void func_060E8FD4(Entity* self);
void func_060E9144(Entity* self);
void func_060E94A0(Entity* self);
void func_060E95E8(Entity* self);

EntityEntry g_Stage15EntitySkeletonBreeder = {
    &g_Stage15SpriteBank25, func_060E78B8};
EntityEntry g_Stage15EntityEntry38 = {NULL, func_060E8A7C};
EntityEntry g_Stage15EntityEntry39 = {NULL, func_060E8BBC};
EntityEntry g_Stage15EntityEntry40 = {NULL, func_060E8D50};
EntityEntry g_Stage15EntityEntry41 = {NULL, func_060E8FD4};
EntityEntry g_Stage15EntityEntry42 = {NULL, func_060E9144};

s16 g_Stage15SkeletonBreederPositionOffsets[69][2] = {
    {0, 0},    {-16, -3}, {-16, -3}, {-16, -2}, {0, 0},    {0, 0},   {0, 0},
    {0, 0},    {0, 0},    {-12, 0},  {-12, 0},  {-13, -2}, {-12, 1}, {-13, -2},
    {-13, -3}, {-13, -1}, {2, 9},    {2, 9},    {2, 14},   {4, 15},  {13, 2},
    {-49, 9},  {-49, 9},  {-49, 9},  {-49, 9},  {-49, 9},  {0, 0},   {0, 0},
    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},   {0, 0},
    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},   {0, 10},
    {0, 0},    {0, 0},    {0, 0},    {31, -8},  {16, 0},   {16, 0},  {21, 18},
    {15, 2},   {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},   {0, 0},
    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},    {0, 0},   {0, 0},
    {0, 0},    {0, 0},    {0, 0},    {26, 3},   {26, 3},   {26, 3},
};
s16 g_Stage15SkeletonBreederHitboxSizes[69][2] = {
    {0, 0},  {13, 2}, {13, 2}, {13, 2}, {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2},
    {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2}, {13, 2},
    {13, 2}, {13, 2}, {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {13, 2}, {0, 0},  {0, 0},  {0, 0},  {6, 8},  {6, 8},  {6, 8},
    {6, 8},  {6, 8},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {2, 14}, {2, 14}, {2, 14}, {2, 14},
};

u8 g_Stage15SkeletonBreederAnimation[4] = {4, 0x53, 4, 0x54};
u32 g_Stage15SkeletonBreederAnimationPadding = 0;
s16 g_Stage15SkeletonBreederSpawnOffsets[2][2] = {{-5, 0}, {5, 0}};
u16 g_Stage15SkeletonBreederSpawnParameters[2] = {0x2038, 0x4048};
s32 g_Stage15SkeletonBreederVelocityLeft = -0x28000;
s32 g_Stage15SkeletonBreederVelocityRight = 0x28000;
s16 g_Stage15SkeletonBreederCollisionSensors[4][2] = {
    {0, 8},
    {0, 4},
    {4, -4},
    {-8, 0},
};

EntityEntry g_Stage15EntityEntry43 = {&g_Stage15SpriteBank25, func_060E94A0};
s16 g_Stage15Entity43InitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry44 = {&g_Stage15SpriteBank25, func_060E95E8};
