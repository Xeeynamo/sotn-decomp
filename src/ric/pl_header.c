// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

void RicMain(void);
void RicInit(s16 arg0);
void RicUpdatePlayerEntities(void);
void func_8015E7B4(Collider* col);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    func_8015E7B4,
};

s32* D_8013C010[4] = {
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)],
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)]};
