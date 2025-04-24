// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

extern u8* RIC_sprites;
void RicMain(void);
void RicInit(u16 params);
void RicUpdatePlayerEntities(void);
void RicGetPlayerSensor(Collider* col);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    RicGetPlayerSensor,
#if defined(VERSION_PSP)
    &RIC_sprites,
    &RIC_sprites,
    &RIC_sprites,
    &RIC_sprites,
#else
    (u8**)((u8*)&RIC_player + sizeof(PlayerOvl)),
    (u8**)((u8*)&RIC_player + sizeof(PlayerOvl)),
    (u8**)((u8*)&RIC_player + sizeof(PlayerOvl)),
    (u8**)((u8*)&RIC_player + sizeof(PlayerOvl)),
#endif
};
