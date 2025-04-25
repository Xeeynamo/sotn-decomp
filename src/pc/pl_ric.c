// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../../ric/ric.h"

static void (*real_player_init)(u16 params);
static void InjectPlayerInit(u16 params) {
    // fixes a bug where g_CurrentEntity is not correctly initialized at init
    g_CurrentEntity = &PLAYER;
    real_player_init(params);
}

void InitPlayerRic(void) {
    g_PlOvl.D_8013C000 = RIC_player.D_8013C000;
    g_PlOvl.D_8013C004 = InjectPlayerInit;
    g_PlOvl.D_8013C008 = RIC_player.D_8013C008;
    g_PlOvl.GetPlayerSensor = RIC_player.GetPlayerSensor;
    real_player_init = RIC_player.D_8013C004;
}
