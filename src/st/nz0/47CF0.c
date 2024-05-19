/*
 * Overlay: NZ0
 * Entity: Magically Sealed Door
 */

#include "nz0.h"

// Another dupe of EntityIsNearPlayer but needs separate definition in nz0
s32 EntityIsNearPlayer2(Entity* e) {
    s16 diff = PLAYER.posX.i.hi - e->posX.i.hi;

    diff = abs(diff);

    if (diff >= 25) {
        return 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = abs(diff);
        if (diff < 33) {
            return 1;
        } else {
            return 0;
        }
    }
    return diff;
}

// sealed door that displays "Magically Sealed" prompt
INCLUDE_ASM("st/nz0/nonmatchings/47CF0", EntityMagicallySealedDoor);
