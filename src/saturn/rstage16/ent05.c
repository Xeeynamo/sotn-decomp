// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "shared_sprite_banks.h"
#include "rstage16.h"

EntityEntry g_RStage16EntityEntry01 = {
    &g_SaturnSharedSpriteBank1Resource, func_060DF8AC};

EntityEntry g_RStage16EntityEntry05 = {
    &g_SaturnSharedSpriteBank5Resource, func_060DFA14};

EntityEntry g_RStage16EntityEntryUnused = {NULL, func_060DFB7C};

EntityEntry g_RStage16EntityEntry18 = {
    &g_SaturnSharedSpriteBank1Resource, EntityDestructAnim};

EntityEntry g_RStage16EntityEntry19 = {
    &g_SaturnSharedSpriteBank5Resource, func_060DFDD4};

s32 g_RStage16ExplosionVariantYVelocities[6] = {
    2048, 10240, 18432, 28672, 57344, 73728,
};

u8 g_RStage16ExplosionVariantStartFrames[4] = {
    1,
    9,
    0x15,
    0x2B,
};

u16 g_RStage16ExplosionVariantLifetimes[4] = {
    0x10,
    0x18,
    0x2A,
    0x2F,
};

s32 g_RStage16GreyPuffYVelocities[6] = {
    1024, 9216, 15360, 24576, 30720, 49152,
};

u8 g_RStage16GreyPuffScales[14] = {
    0, 0x0C, 0, 0x14, 0, 0x20, 0, 0x2C, 0, 0x34, 0, 0x40, 0, 0x40,
};

s16 g_ExplosionVariantSizes[7] = {
    16, 32, 48, 64, 80, 96, 112,
};
