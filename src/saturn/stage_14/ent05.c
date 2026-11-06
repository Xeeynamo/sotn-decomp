// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include "stage_14.h"

EntityEntry g_Stage14EntityEntry01 = {
    &g_SaturnSharedSpriteBank1Resource, func_060E1E64};
EntityEntry g_Stage14EntityEntry05 = {
    &g_SaturnSharedSpriteBank5Resource, func_060E1FCC};
EntityEntry g_Stage14EntityEntry18 = {NULL, func_060E2134};
EntityEntry g_Stage14EntityEntry19 = {
    &g_SaturnSharedSpriteBank1Resource, EntityDestructAnim};
EntityEntry g_Stage14EntityEntry20 = {
    &g_SaturnSharedSpriteBank5Resource, func_060E238C};

s32 g_Stage14ExplosionVariantYVelocities[6] = {
    0x800, 0x2800, 0x4800, 0x7000, 0xE000, 0x12000,
};

u8 g_Stage14ExplosionVariantStartFrames[4] = {1, 9, 21, 43};

u16 g_Stage14ExplosionVariantLifetimes[4] = {16, 24, 42, 47};

s32 g_Stage14GreyPuffYVelocities[6] = {
    0x400, 0x2400, 0x3C00, 0x6000, 0x7800, 0xC000,
};

u8 g_Stage14GreyPuffScales[14] = {
    0, 0x0C, 0, 0x14, 0, 0x20, 0, 0x2C, 0, 0x34, 0, 0x40, 0, 0x40,
};

s16 g_ExplosionVariantSizes[7] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
};
