// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ghost.h"

void OVL_EXPORT(ServantInit)(InitializeMode mode);
void OVL_EXPORT(UpdateServantDefault)(Entity* self);
void unused_20A4(Entity* self);
void unused_20AC(Entity* self);
void unused_20B4(Entity* self);
void unused_20BC(Entity* self);
void unused_20C4(Entity* self);
void unused_20CC(Entity* self);
void unused_20D4(Entity* self);
void unused_20DC(Entity* self);
void UpdateAttackEntities(Entity* self);
void UpdateConfusedEntities(Entity* self);
void unused_28EC(Entity* self);
void unused_28F4(Entity* self);
void unused_28FC(Entity* self);
void OVL_EXPORT(DestroyServantEntity)(Entity* self);

ServantDesc ghost_ServantDesc = {
    OVL_EXPORT(ServantInit),          OVL_EXPORT(UpdateServantDefault), unused_20A4,
    unused_20AC,          unused_20B4,          unused_20BC,
    unused_20C4,          unused_20CC,          unused_20D4,
    unused_20DC,          UpdateAttackEntities, UpdateConfusedEntities,
    unused_28EC,          unused_28F4,          unused_28FC,
    OVL_EXPORT(DestroyServantEntity),
};

#ifdef VERSION_PSP
void func_092EA620(void) {
    memcpy((u8*)&g_ServantDesc, (u8*)&ghost_ServantDesc, sizeof(ServantDesc));
}
#endif
