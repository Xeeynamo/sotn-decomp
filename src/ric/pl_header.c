// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

void RicMain(void);
void RicInit(s16 arg0);
void RicUpdatePlayerEntities(void);
void RicGetPlayerSensor(Collider* col);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    RicGetPlayerSensor,
};

s32* D_8013C010[4] = {
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)],
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)]};
