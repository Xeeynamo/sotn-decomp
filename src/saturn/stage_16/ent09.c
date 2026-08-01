// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DED28(Entity* self);
void func_060DF830(Entity* self);

EntityEntry g_Stage16EntityEntry04 = {
    &g_SaturnSharedSpriteBank3Resource, func_060DED28};

u16 g_Stage16Entity04Parameters[8] = {1, 5, 3, 4, 4, 4, 2, 4};

EntityEntry g_Stage16EntityEntry03 = {
    &g_SaturnSharedSpriteBank4Resource, func_060DF830};
