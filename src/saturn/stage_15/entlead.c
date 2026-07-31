// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank31;

void func_060EF0C0(Entity* self);
void func_060EF5E0(Entity* self);
void func_060EF6E0(Entity* self);
void func_060EFF44(Entity* self);

typedef struct {
    s8 width;
    s8 height;
    s8 offsetX;
    s8 offsetY;
} Stage15SkeletonLeaderHitbox;

EntityEntry g_Stage15EntitySkeletonLeader = {
    &g_Stage15SpriteBank31, func_060EF0C0};
EntityEntry g_Stage15EntityEntry64 = {NULL, func_060EF5E0};
EntityEntry g_Stage15EntityEntry65 = {NULL, func_060EF6E0};
EntityEntry g_Stage15EntityEntry66 = {NULL, func_060EFF44};

Stage15SkeletonLeaderHitbox g_Stage15SkeletonLeaderHitboxes[11] = {
    {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},
    {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 2, 0, -16},
    {12, 12, -44, 2}, {20, 8, -48, 22}, {16, 2, -52, 28},
};
s16 g_Stage15SkeletonLeaderAttackSensors[2][2] = {{0, 16}, {4, 0}};
s16 g_Stage15SkeletonLeaderGroundSensors[4][2] = {
    {0, 16},
    {0, 4},
    {8, -4},
    {-16, 0},
};
