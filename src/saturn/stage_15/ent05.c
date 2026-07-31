// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E2F3C(Entity* self);
void func_060E30A4(Entity* self);
void func_060E320C(Entity* self);
void func_060E32F8(Entity* self);
void func_060E3464(Entity* self);

EntityEntry g_Stage15EntityEntry01 = {
    &g_SaturnSharedSpriteBank1Resource, func_060E2F3C};
EntityEntry g_Stage15EntityEntry05 = {
    &g_SaturnSharedSpriteBank5Resource, func_060E30A4};
EntityEntry g_Stage15EntityEntry18 = {NULL, func_060E320C};
EntityEntry g_Stage15EntityEntry19 = {
    &g_SaturnSharedSpriteBank1Resource, func_060E32F8};
EntityEntry g_Stage15GreyPuffEntityEntry = {
    &g_SaturnSharedSpriteBank5Resource, func_060E3464};

s32 g_Stage15ExplosionVariantYVelocities[6] = {
    0x800, 0x2800, 0x4800, 0x7000, 0xE000, 0x12000,
};

u8 g_Stage15ExplosionVariantStartFrames[4] = {1, 9, 21, 43};

u16 g_Stage15ExplosionVariantLifetimes[4] = {16, 24, 42, 47};

s32 g_Stage15GreyPuffYVelocities[6] = {
    0x400, 0x2400, 0x3C00, 0x6000, 0x7800, 0xC000,
};

s16 g_Stage15GreyPuffRotations[7] = {
    0x0C, 0x14, 0x20, 0x2C, 0x34, 0x40, 0x40,
};

s16 g_Stage15ExplosionVariantSizes[7] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
};
