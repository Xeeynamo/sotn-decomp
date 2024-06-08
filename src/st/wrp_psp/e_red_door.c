#include "../wrp/wrp.h"

bool EntityIsNearPlayer(Entity* self) {
    s16 distanceX;
    s16 diffX;
    s16 distanceY;
    s16 diffY;

    diffX = PLAYER.posX.i.hi - self->posX.i.hi;
    distanceX = abs(diffX);
    if (distanceX > 16) {
        return false;
    }

    diffY = PLAYER.posY.i.hi - self->posY.i.hi;
    distanceY = abs(diffY);
    if (distanceY > 32) {
        return false;
    }

    return true;
}

extern u8 g_eRedDoorUV[3][8];
extern u16 g_eRedDoorTiles[2][8];
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_red_door", EntityRedDoor);
