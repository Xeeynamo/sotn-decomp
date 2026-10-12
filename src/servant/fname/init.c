// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>

void ServantInit(InitializeMode mode);
void UpdateServantDefault(Entity* self);
void UpdateBatAttackMode(Entity* self);
void func_801728D4(Entity* self);
void func_801728DC(Entity* self);
void func_801728E4(Entity* self);
void func_801728EC(Entity* self);
void func_801728F4(Entity* self);
void func_801728FC(Entity* self);
void func_80172904(Entity* self);
void UpdateBatBlueTrailEntities(Entity* self);
void func_80173144(Entity* self);
void func_8017314C(Entity* self);
void func_80173154(Entity* self);
void func_8017315C(Entity* self);
void func_80173164(Entity* self);

ServantDesc fname_ServantDesc = {
    ServantInit,
    UpdateServantDefault,
    UpdateBatAttackMode,
    func_801728D4,
    func_801728DC,
    func_801728E4,
    func_801728EC,
    func_801728F4,
    func_801728FC,
    func_80172904,
    UpdateBatBlueTrailEntities,
    func_80173144,
    func_8017314C,
    func_80173154,
    func_8017315C,
    func_80173164,
};
