// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void EntityWarpExplosion(Entity* self);
void EntityWarpIntenseExplosion(Entity* self);
void EntityWarpUnkId13(Entity* self);
void EntityWarpExplosionVariants(Entity* self);
void EntityWarpGreyPuff(Entity* self);
void EntityWarpSoulStealOrb(Entity* self);
void EntityWarpEnemyBlood(Entity* self);

u16 g_WarpEInitExplosion[5] = {1, 2, 4, 5, 1};

EntityEntry g_WarpExplosionEntry = {
    &g_SaturnSharedSpriteBank1Resource,
    EntityWarpExplosion,
};

EntityEntry g_WarpIntenseExplosionEntry = {
    &g_SaturnSharedSpriteBank5Resource,
    EntityWarpIntenseExplosion,
};

EntityEntry g_WarpUnkId13Entry = {
    NULL,
    EntityWarpUnkId13,
};

EntityEntry g_WarpExplosionVariantsEntry = {
    &g_SaturnSharedSpriteBank1Resource,
    EntityWarpExplosionVariants,
};

EntityEntry g_WarpGreyPuffEntry = {
    &g_SaturnSharedSpriteBank5Resource,
    EntityWarpGreyPuff,
};

s32 g_WarpExplosionVariantYVelocities[6] = {
    0x800, 0x2800, 0x4800, 0x7000, 0xE000, 0x12000,
};

u8 g_WarpExplosionVariantStartFrames[4] = {1, 9, 21, 43};

u16 g_WarpExplosionVariantLifetimes[4] = {16, 24, 42, 47};

s32 g_WarpGreyPuffYVelocities[6] = {
    0x400, 0x2400, 0x3C00, 0x6000, 0x7800, 0xC000,
};

s16 g_WarpGreyPuffRotations[7] = {
    0x0C, 0x14, 0x20, 0x2C, 0x34, 0x40, 0x40,
};

s16 g_WarpExplosionVariantSizes[7] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
};

EntityEntry g_WarpSoulStealOrbEntry = {
    &g_SaturnSharedSpriteBank6Resource,
    EntityWarpSoulStealOrb,
};

EntityEntry g_WarpEnemyBloodEntry = {
    NULL,
    EntityWarpEnemyBlood,
};
