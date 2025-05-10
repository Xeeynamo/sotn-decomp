// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

extern u8* richter_sprites[RIC_SPRITE_COUNT];
void RicMain(void);
void RicInit(u16 params);
void RicUpdatePlayerEntities(void);
void RicGetPlayerSensor(Collider* col);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    RicGetPlayerSensor,
    richter_sprites,
    richter_sprites,
    richter_sprites,
    richter_sprites,
};

#if !defined(VERSION_PSP)
#include "gen/richter.h"
#endif
