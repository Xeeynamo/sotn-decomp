#include "maria.h"

extern unsigned char* maria_sprites[];
void MarMain(void);
void MarInit(u16 initParam);
void MarUpdatePlayerEntities(void);
void MarGetPlayerSensor(Collider* col);
PlayerOvl MARIA_player = {
    MarMain,       MarInit,       MarUpdatePlayerEntities, MarGetPlayerSensor,
    maria_sprites, maria_sprites, maria_sprites,           maria_sprites,
};
