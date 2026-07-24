// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void EntityWarpRedDoor(Entity* self);

EntityEntry g_WarpRedDoorEntry = {
    &g_SaturnSharedSpriteBank3Resource,
    EntityWarpRedDoor,
};

u16 g_WarpRedDoorConfig[8] = {
    1, 5, 3, 4, 4, 4, 2, 4,
};
