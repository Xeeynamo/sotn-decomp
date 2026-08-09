// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

extern unsigned char* maria_sprites[];
void MarMain(void);
#ifdef MARIA_SFX_DEBUG
void MarSoundTest(void);
#define MARIA_MAIN MarSoundTest
#else
#define MARIA_MAIN MarMain
#endif
void MarInit(u16 initParam);
void MarUpdatePlayerEntities(void);
void MarGetPlayerSensor(Collider* col);
PlayerOvl MARIA_player = {
    MARIA_MAIN,    MarInit,       MarUpdatePlayerEntities, MarGetPlayerSensor,
    maria_sprites, maria_sprites, maria_sprites,           maria_sprites,
};
