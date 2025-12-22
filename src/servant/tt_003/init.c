// SPDX-License-Identifier: AGPL-3.0-or-later
#include "demon.h"

void OVL_EXPORT(ServantInit)(InitializeMode);
void OVL_EXPORT(UpdateServantDefault)(Entity*);
void UpdateServantBasicAttack(Entity*);
void UpdateServantSpecialAttack(Entity*);
void unused_5800(Entity*);
void unused_5808(Entity*);
void UpdateServantPressSwitch(Entity*);
void UpdateSubentitySwitch(Entity*);
void UpdateServantAdditionalInit(Entity*);
void UpdateServantSfxPassthrough(Entity*);
void UpdateEventAttack(Entity*);
void func_us_801765A0(Entity*);
void func_us_80176814(Entity*);
void func_us_80176C1C(Entity*);
void func_us_801771B0(Entity*);
void func_us_80177690(Entity*);

ServantDesc demon_ServantDesc = {
    OVL_EXPORT(ServantInit),
    OVL_EXPORT(UpdateServantDefault),
    UpdateServantBasicAttack,
    UpdateServantSpecialAttack,
    unused_5800,
    unused_5808,
    UpdateServantPressSwitch,
    UpdateSubentitySwitch,
    UpdateServantAdditionalInit,
    UpdateServantSfxPassthrough,
    UpdateEventAttack,
    func_us_801765A0,
    func_us_80176814,
    func_us_80176C1C,
    func_us_801771B0,
    func_us_80177690,
};

#ifdef VERSION_PSP
void func_092EF908(void) {
    memcpy((u8*)&g_ServantDesc, (u8*)&demon_ServantDesc, sizeof(ServantDesc));
}
#endif
