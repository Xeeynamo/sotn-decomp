// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_player.h>

void func_060A5208(u16 params);
void func_060A5BE8(void);
void func_060AC604(void);
s32 func_060B09C0(void);
void func_060AC850(void);
void RicGetPlayerSensor(Collider* collider);
void func_060AA8AC(s32 resetAnims, s32 arg1);
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames);
void func_060AA9EC(void);
void func_060AA974(void);
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2);
void func_060AB088(void);
void func_8015F9F0(Entity* entity);
extern void* g_MariaSpriteBanks[18];
extern SaturnPlayerGraphicsRecord g_MariaPlayerGraphicsRecords[346];

SaturnPlayerOvl MARIA_player = {
    func_060A5208,
    func_060A5BE8,
    func_060AC604,
    (SaturnPlayerCallback)func_060B09C0,
    func_060AC850,
    RicGetPlayerSensor,
    func_060AA8AC,
    RicSetInvincibilityFrames,
    func_060AA9EC,
    func_060AA974,
    RicCreateEntFactoryFromEntity,
    func_060AB088,
    func_8015F9F0,
    (SaturnPlayerCallback)func_060B09C0,
    (SaturnPlayerCallback)func_060B09C0,
    (u8*)g_MariaSpriteBanks,
    g_MariaPlayerGraphicsRecords,
};
