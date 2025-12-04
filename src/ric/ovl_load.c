// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

void OVL_EXPORT(Load)(void) {
    memcpy(&g_PlOvl, &RIC_player, sizeof(PlayerOvl));
    func_psp_08929FA8(g_PlOvlSpritesheet, RIC_SPRITE_COUNT);
}
