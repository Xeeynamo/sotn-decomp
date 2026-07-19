// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void EntityWarpRedDoor(Entity* self);

extern struct SpriteParts* g_EntitySpriteBank03[];

EntityEntry g_WarpRedDoorEntry = {
    g_EntitySpriteBank03,
    EntityWarpRedDoor,
};

u16 g_WarpRedDoorConfig[8] = {
    1, 5, 3, 4, 4, 4, 2, 4,
};
