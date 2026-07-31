// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E0774(Entity* self);
void func_060E127C(Entity* self);

EntityEntry g_RStage15EntityEntry04 = {
    &g_SaturnSharedSpriteBank3Resource, func_060E0774};

u16 g_RStage15Entity04Parameters[8] = {1, 5, 3, 4, 4, 4, 2, 4};

EntityEntry g_RStage15EntityEntry03 = {
    &g_SaturnSharedSpriteBank4Resource, func_060E127C};
