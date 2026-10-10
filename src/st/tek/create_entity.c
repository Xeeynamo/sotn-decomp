// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

#include "../pfn_entity_update.h"
#include "../create_entity.h"

bool EntityIsNearPlayer(Entity* self) {
    s16 distanceX;
    s16 diffX;
    s16 distanceY;
    s16 diffY;

    diffX = PLAYER.posX.i.hi - self->posX.i.hi;
    distanceX = abs(diffX);
    if (distanceX <= 24) {
        diffY = PLAYER.posY.i.hi - self->posY.i.hi;
        distanceY = abs(diffY);
        return distanceY <= 32;
    }
    return false;
}
