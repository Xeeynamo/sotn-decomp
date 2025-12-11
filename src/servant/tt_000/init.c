// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bat.h"

void OVL_EXPORT(ServantInit)(InitializeMode mode);
void OVL_EXPORT(UpdateServantDefault)(Entity* self);
void UpdateBatAttackMode(Entity* self);
void unused_339C(Entity* self);
void unused_33A4(Entity* self);
void unused_33AC(Entity* self);
void unused_33B4(Entity* self);
void unused_33BC(Entity* self);
void unused_33C4(Entity* self);
void unused_33CC(Entity* self);
void UpdateBatBlueTrailEntities(Entity* self);
void unused_3C0C(Entity* self);
void unused_3C14(Entity* self);
void unused_3C1C(Entity* self);
void unused_3C24(Entity* self);
void OVL_EXPORT(DestroyServantEntity)(Entity* self);

ServantDesc bat_ServantDesc = {
    OVL_EXPORT(ServantInit),
    OVL_EXPORT(UpdateServantDefault),
    UpdateBatAttackMode,
    unused_339C,
    unused_33A4,
    unused_33AC,
    unused_33B4,
    unused_33BC,
    unused_33C4,
    unused_33CC,
    UpdateBatBlueTrailEntities,
    unused_3C0C,
    unused_3C14,
    unused_3C1C,
    unused_3C24,
    OVL_EXPORT(DestroyServantEntity),
};

#ifdef VERSION_PSP
void func_092EC220(void) {
    memcpy((u8*)&g_ServantDesc, (u8*)&bat_ServantDesc, sizeof(ServantDesc));
}
#endif
