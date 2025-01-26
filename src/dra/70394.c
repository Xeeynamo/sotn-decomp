// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"


s16 D_800ACF6C[] = {0, -8, -16, -22};

s16 func_80110394(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    // Values that are set once and never again (but not const for some reason)
    s32 xpos = PLAYER.posX.i.hi;
    s32 xp4 = xpos + 4;
    s32 xm4 = xpos - 4;
    s32 coll_flags = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;

    for (i = 0; i < 4; i++) {
        yvar = PLAYER.posY.i.hi + D_800ACF6C[i];
        CheckCollision(xpos, yvar, &collider, 0);
        collisions = 0;
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xp4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xm4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}