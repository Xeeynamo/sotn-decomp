#include "nz0.h"

s32 func_801C7CF0(Entity* e) { // EntityMagicallySealedDoor
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 25) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

// sealed door that displays "Magically Sealed" prompt
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/47CF0", EntityMagicallySealedDoor);



