// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sword.h"

void ServantInit(InitializeMode mode);
void UpdateServantDefault(Entity* self);
void func_us_801746BC(Entity* self);
void func_us_80174B6C(Entity* self);
void func_us_801758C8(Entity* self);
void func_us_80176270(Entity* self);
void func_us_80176664(Entity* self);
void func_us_8017666C(Entity* self);
void func_us_80176674(Entity* self);
void func_us_80176BF0(Entity* self);
void func_us_80176BF8(Entity* self);
void func_us_80176F28(Entity* self);
void func_us_801773CC(Entity* self);
void UpdateServantSfxPassthrough(Entity* self);
void func_us_80177480(Entity* self);
void func_us_80177590(Entity* self);

ServantDesc sword_ServantDesc = {
    .Init = ServantInit,
    .Update = UpdateServantDefault,
    func_us_801746BC, // active target below level 70
    func_us_80174B6C, // active target above level 70
    func_us_801758C8,
    func_us_80176270,
    func_us_80176664,
    func_us_8017666C,
    func_us_80176674,
    func_us_80176BF0,
    func_us_80176BF8,
    func_us_80176F28,
    func_us_801773CC,
    UpdateServantSfxPassthrough,
    func_us_80177480,
    func_us_80177590,
};

#ifdef VERSION_PSP
void func_092EF780(void) {
    memcpy((u8*)&g_ServantDesc, (u8*)&sword_ServantDesc, sizeof(ServantDesc));
}
#endif
