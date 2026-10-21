// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nosedevil.h"

void TT_006_ServantInit(InitializeMode);
void TT_006_UpdateServantDefault(Entity*);
void UpdateServantBasicAttack(Entity*);
void UpdateServantSpecialAttack(Entity*);
void unused_55D4(Entity*);
void unused_55DC(Entity*);
void UpdateServantPressSwitch(Entity*);
void UpdateSubentitySwitch(Entity*);
void UpdateServantAdditionalInit(Entity*);
void UpdateServantSfxPassthrough(Entity*);
void UpdateEventAttack(Entity*);
void func_us_80176374(Entity*);
void func_us_801765E8(Entity*);
void func_us_801769F0(Entity*);
void func_us_80176F84(Entity*);
void func_us_80177464(Entity*);

ServantDesc nosedevil_ServantDesc = {
    TT_006_ServantInit,
    TT_006_UpdateServantDefault,
    UpdateServantBasicAttack,
    UpdateServantSpecialAttack,
    unused_55D4,
    unused_55DC,
    UpdateServantPressSwitch,
    UpdateSubentitySwitch,
    UpdateServantAdditionalInit,
    UpdateServantSfxPassthrough,
    UpdateEventAttack,
    func_us_80176374,
    func_us_801765E8,
    func_us_801769F0,
    func_us_80176F84,
    func_us_80177464,
};

#ifdef VERSION_PSP
void func_092EF908(void) {
    memcpy(
        (u8*)&g_ServantDesc, (u8*)&nosedevil_ServantDesc, sizeof(ServantDesc));
}
#endif
