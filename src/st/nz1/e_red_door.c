// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern u16 PLAYER_posX_i_hi;
extern u16 PLAYER_posY_i_hi;

static bool EntityIsNearPlayer(Entity* self) {
    s16 distanceX;
    s16 diffX;
    s16 distanceY;
    s16 diffY;

    diffX = PLAYER.posX.i.hi - self->posX.i.hi;
    distanceX = abs(diffX);
#ifdef STAGE_IS_NO1
    if (distanceX > 24) {
#else
    if (distanceX > 16) {
#endif
        return false;
    }

    diffY = PLAYER.posY.i.hi - self->posY.i.hi;
    distanceY = abs(diffY);
    if (distanceY > 32) {
        return false;
    }

    return true;
}

INCLUDE_ASM("st/nz1/nonmatchings/e_red_door", NZ1_EntityRedDoor);
