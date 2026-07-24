// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DD038(Entity* self);
void func_060DD894(Entity* self);
void EntityWarpRelicOrb(Entity* self);
void EntityWarpHeartDrop(Entity* self);
void EntityWarpMessageBox(Entity* self);

EntityEntry g_WarpPrizeDropEntry = {
    &g_SaturnSharedSpriteBank0Resource,
    func_060DD038,
};

EntityEntry g_WarpEquipItemDropEntry = {
    &g_SaturnSharedSpriteBank0Resource,
    func_060DD894,
};

EntityEntry g_WarpRelicOrbEntry = {
    &g_SaturnSharedSpriteBank0Resource,
    EntityWarpRelicOrb,
};

EntityEntry g_WarpHeartDropEntry = {
    &g_SaturnSharedSpriteBank0Resource,
    EntityWarpHeartDrop,
};

EntityEntry g_WarpMessageBoxEntry = {
    NULL,
    EntityWarpMessageBox,
};
