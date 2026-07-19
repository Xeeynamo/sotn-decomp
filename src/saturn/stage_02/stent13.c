// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060EAFAC(Entity* self);
void func_060EB5C4(Entity* self);
void func_060EB6E4(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank31[];

EntityEntry g_Stage02EntityEntry42 = {
    g_Stage02SpriteBank31, func_060EAFAC};
EntityEntry g_Stage02EntityEntry44 = {
    g_Stage02SpriteBank31, func_060EB5C4};

u16 g_Stage02BloodSplatterAnimations[26] = {
    0,     0,     0x226, 0x227, 0x228, 0x229, 0x22A, 0,
    0x22B, 0x22C, 0x22D, 0x22E, 0x22F, 0x230, 0,     0,
    0x420, 0x42B, 0x42C, 0,     0x421, 0x422, 0x423, 0x424,
    0x425, 0,
};

EntityEntry g_Stage02EntityEntry43 = {
    g_Stage02SpriteBank31, func_060EB6E4};

u32 g_Stage02BloodDripsState = 0;

s16 g_Stage02BloodDripsColliderOffsets[2][2] = {
    {0, 0},
    {0xFF, 0},
};
