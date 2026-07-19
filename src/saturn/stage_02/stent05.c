// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060E5AE4(Entity* self);
void func_060E5C4C(Entity* self);
void func_060E5DB4(Entity* self);
void func_060E5EA0(Entity* self);
void func_060E600C(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank01[];
extern struct SpriteParts* g_Stage02SpriteBank05[];

EntityEntry g_Stage02EntityEntry01 = {
    g_Stage02SpriteBank01, func_060E5AE4};
EntityEntry g_Stage02EntityEntry05 = {
    g_Stage02SpriteBank05, func_060E5C4C};
EntityEntry g_Stage02EntityEntry18 = {NULL, func_060E5DB4};
EntityEntry g_Stage02EntityEntry19 = {
    g_Stage02SpriteBank01, func_060E5EA0};
EntityEntry g_Stage02EntityEntry20 = {
    g_Stage02SpriteBank05, func_060E600C};

s32 g_Stage02ExplosionVariantYVelocities[6] = {
    0x800, 0x2800, 0x4800, 0x7000, 0xE000, 0x12000,
};

u8 g_Stage02ExplosionVariantStartFrames[4] = {1, 9, 21, 43};

u16 g_Stage02ExplosionVariantLifetimes[4] = {16, 24, 42, 47};

s32 g_Stage02GreyPuffYVelocities[6] = {
    0x400, 0x2400, 0x3C00, 0x6000, 0x7800, 0xC000,
};

s16 g_Stage02GreyPuffRotations[7] = {
    0x0C, 0x14, 0x20, 0x2C, 0x34, 0x40, 0x40,
};

s16 g_Stage02ExplosionVariantSizes[7] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
};
