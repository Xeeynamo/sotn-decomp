#include "../wrp/wrp.h"

bool EntityIsNearPlayer(Entity* self) {
    s16 posX;
    s16 diffX;
    s16 posY;
    s16 diffY;

    diffX = PLAYER.posX.i.hi - self->posX.i.hi;
    posX = abs(diffX);

    if (posX > 16) {
        return 0;
    }

    diffY = PLAYER.posY.i.hi - self->posY.i.hi;
    posY = abs(diffY);

    if (posY > 32) {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_red_door", EntityRedDoor);

// TODO move this function to the next file
// but only when the func Update is matching
s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return (g_randomNext >> 0x18) & 0xFF;
}
