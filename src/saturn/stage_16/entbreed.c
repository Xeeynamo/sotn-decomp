// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank25;

void func_060E6DDC(Entity* self);
void func_060E72FC(Entity* self);
void func_060E73FC(Entity* self);
void func_060E7C60(Entity* self);

typedef struct {
    s8 width;
    s8 height;
    s8 offsetX;
    s8 offsetY;
} Stage16SkeletonBreederHitbox;

EntityEntry g_Stage16EntitySkeletonBreeder = {
    &g_Stage16SpriteBank25, func_060E6DDC};
EntityEntry g_Stage16EntityEntry36 = {NULL, func_060E72FC};
EntityEntry g_Stage16EntityEntry37 = {NULL, func_060E73FC};
EntityEntry g_Stage16EntityEntry38 = {NULL, func_060E7C60};

Stage16SkeletonBreederHitbox g_Stage16SkeletonBreederHitboxes[11] = {
    {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},
    {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 3, 0, -16},  {16, 2, 0, -16},
    {12, 12, -44, 2}, {20, 8, -48, 22}, {16, 2, -52, 28},
};

s16 g_Stage16SkeletonBreederAttackSensors[2][2] = {
    {0, 16},
    {4, 0},
};
s16 g_Stage16SkeletonBreederGroundSensors[4][2] = {
    {0, 16},
    {0, 4},
    {8, -4},
    {-16, 0},
};
