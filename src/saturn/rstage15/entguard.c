// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage15SpriteBank28;

void func_060EB550(Entity* self);
void func_060EC174(Entity* self);
void func_060EC274(Entity* self);
void func_060EC374(Entity* self);

typedef struct {
    s8 width;
    s8 height;
    s8 offsetX;
    s8 offsetY;
} RStage15SkeletonGuardianHitbox;

EntityEntry g_RStage15EntitySkeletonGuardian = {
    &g_RStage15SpriteBank28, func_060EB550};
EntityEntry g_RStage15EntityEntry56 = {NULL, func_060EC174};
EntityEntry g_RStage15EntityEntry57 = {NULL, func_060EC274};
EntityEntry g_RStage15EntityEntry58 = {NULL, func_060EC374};

RStage15SkeletonGuardianHitbox g_RStage15SkeletonGuardianBodyHitboxes[18] = {
    {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8},
    {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8}, {4, 16, 0, 8},
    {4, 16, 0, 8}, {4, 16, 0, 8}, {4, 16, 0, 8}, {4, 16, 0, 8}, {7, 16, 0, 8},
    {7, 16, 0, 8}, {7, 16, 0, 8}, {7, 16, 0, 8},
};
RStage15SkeletonGuardianHitbox g_RStage15SkeletonGuardianWeaponHitboxes[18] = {
    {6, 6, -24, 21},   {6, 6, -28, 20},   {6, 6, -31, 18},  {6, 6, 4, -34},
    {16, 6, -20, -32}, {8, 12, -38, -14}, {6, 12, -34, 20}, {6, 8, 8, -24},
    {6, 8, 8, -24},    {6, 8, 8, -24},    {8, 8, -16, -18}, {8, 4, -32, 6},
    {8, 4, -32, 4},    {8, 4, -32, 5},    {8, 4, -40, 5},   {8, 4, -41, 3},
    {8, 4, -40, 3},    {8, 4, -32, 4},
};
RStage15SkeletonGuardianHitbox g_RStage15SkeletonGuardianShieldHitboxes[18] = {
    {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, -6, 0},   {4, 16, -6, 12}, {4, 16, -6, 12}, {4, 16, -6, 12},
    {4, 16, -6, 12}, {4, 16, -6, 12}, {5, 18, -16, 6}, {5, 18, -16, 6},
    {5, 18, -16, 6}, {4, 16, -8, 12},
};
