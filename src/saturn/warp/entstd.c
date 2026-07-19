// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060DD038(Entity* self);
void func_060DD894(Entity* self);
void EntityWarpRelicOrb(Entity* self);
void EntityWarpHeartDrop(Entity* self);
void EntityWarpMessageBox(Entity* self);

extern struct SpriteParts* g_EntitySpriteBank00[];

EntityEntry g_WarpPrizeDropEntry = {
    g_EntitySpriteBank00,
    func_060DD038,
};

EntityEntry g_WarpEquipItemDropEntry = {
    g_EntitySpriteBank00,
    func_060DD894,
};

EntityEntry g_WarpRelicOrbEntry = {
    g_EntitySpriteBank00,
    EntityWarpRelicOrb,
};

EntityEntry g_WarpHeartDropEntry = {
    g_EntitySpriteBank00,
    EntityWarpHeartDrop,
};

EntityEntry g_WarpMessageBoxEntry = {
    NULL,
    EntityWarpMessageBox,
};
