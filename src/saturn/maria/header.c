// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_player.h>
#include "maria.h"

void RicGetPlayerSensor(Collider* collider);

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
