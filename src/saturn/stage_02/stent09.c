// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E4908(Entity* self);
void func_060E5410(Entity* self);

EntityEntry g_Stage02EntityEntry04 = {
    &g_SaturnSharedSpriteBank3Resource, func_060E4908};

u16 g_Stage02Entity04Parameters[8] = {1, 5, 3, 4, 4, 4, 2, 4};

EntityEntry g_Stage02EntityEntry03 = {
    &g_SaturnSharedSpriteBank4Resource, func_060E5410};
