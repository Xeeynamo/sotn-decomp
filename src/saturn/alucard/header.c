// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_player.h>

void func_060ADF3C(u16 params);
void func_060AFA20(void);
void func_060BAB00(void);
void func_060BAD84(void);
void func_060BAE70(void);
void func_060B2DE4(Collider* collider);
void func_060A7D68(s32 resetAnims, s32 arg1);
void func_060AB44C(s32 kind, s16 invincibilityFrames);
void func_060ADD74(void);
void func_060AB3A8(void);
Entity* func_060BAF44(Entity* source, u32 factoryParams, s32 arg2);
void func_060B2E40(void);
void func_060B9340(Entity* entity);
void func_060AF4A0(void);
void func_060AF654(void);
extern u8 D_060CBE94[];
extern SaturnPlayerGraphicsRecord D_060CBED8[];

SaturnPlayerOvl ALUCARD_player = {
    func_060ADF3C,
    func_060AFA20,
    func_060BAB00,
    func_060BAD84,
    func_060BAE70,
    func_060B2DE4,
    func_060A7D68,
    func_060AB44C,
    func_060ADD74,
    func_060AB3A8,
    func_060BAF44,
    func_060B2E40,
    func_060B9340,
    func_060AF4A0,
    func_060AF654,
    D_060CBE94,
    D_060CBED8,
};
