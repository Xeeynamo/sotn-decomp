// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_player.h>
#include "richter.h"

void RicGetPlayerSensor(Collider* col);
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames);
void func_8015F9F0(Entity* entity);

SaturnPlayerOvl RIC_player = {
    RicInit,
    RicMain,
    RicUpdatePlayerEntities,
    (SaturnPlayerCallback)func_060B0610,
    func_060AC2DC,
    RicGetPlayerSensor,
    DisableAfterImage,
    RicSetInvincibilityFrames,
    (SaturnPlayerCallback)func_060B0610,
    func_060AA4F4,
    RicCreateEntFactoryFromEntity,
    func_8015E484,
    func_8015F9F0,
    (SaturnPlayerCallback)func_060B0610,
    (SaturnPlayerCallback)func_060B0610,
    (u8*)g_RichterSpriteBanks,
    g_RichterPlayerGraphicsRecords,
};
