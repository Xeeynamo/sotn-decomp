// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"

const int RicSpriteCount = 0xC5;
void func_pspeu_092C8D48(void) {
    memcpy((u8*)&g_PlOvl, (u8*)&RIC_player, sizeof(PlayerOvl));
    func_8929FA8(g_PlOvlSpritesheet, RicSpriteCount);
}
