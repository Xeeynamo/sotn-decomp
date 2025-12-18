// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

void OVL_EXPORT(ServantInit)(InitializeMode mode);
void OVL_EXPORT(UpdateServantDefault)(Entity* self);
void UpdateServantUseLifeApple(Entity* self);
void UpdateServantUseHammer(Entity* self);
void UpdateServantUseUncurse(Entity* self);
void UpdateServantUseAntivenom(Entity* self);
void UpdateServantUseElementalResist(Entity* self);
void UpdateServantUsePotion(Entity* self);
void UpdateServantAdditionalInit(Entity* self);
void UpdateSubEntityWings(Entity* self);
void UpdateServantSitOnShoulder(Entity* self);
void UpdateServantOfferHint(Entity* self);
void UpdateEntitySetRoomSpecialState(Entity* self);
void UpdateSubEntityUseLifeApple(Entity* self);
void UpdateServantSfxPassthrough(Entity* self);
void UpdateSubEntityUseItem(Entity* self);

ServantDesc faerie_ServantDesc = {
    OVL_EXPORT(ServantInit),         OVL_EXPORT(UpdateServantDefault),
    UpdateServantUseLifeApple,       UpdateServantUseHammer,
    UpdateServantUseUncurse,         UpdateServantUseAntivenom,
    UpdateServantUseElementalResist, UpdateServantUsePotion,
    UpdateServantAdditionalInit,     UpdateSubEntityWings,
    UpdateServantSitOnShoulder,      UpdateServantOfferHint,
    UpdateEntitySetRoomSpecialState, UpdateSubEntityUseLifeApple,
    UpdateServantSfxPassthrough,     UpdateSubEntityUseItem,
};

#ifdef VERSION_PSP
void func_092EF290(void) {
    memcpy((u8*)&g_ServantDesc, (u8*)&faerie_ServantDesc, sizeof(ServantDesc));
}
#endif
