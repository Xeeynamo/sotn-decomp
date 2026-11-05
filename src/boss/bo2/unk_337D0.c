// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

/**
 * Restricts the current entity's horizontal position to the boss arena.
 *
 * Accounts for horizontal velocity and tilemap scrolling when checking
 * the arena boundaries.
 */
void func_us_801B37D0(void) {
    s16 scrollX = g_Tilemap.scrollX.i.hi;
    s32 x = g_CurrentEntity->posX.i.hi + scrollX;

    if (g_CurrentEntity->velocityX > 0) {
        x += 8;

        if (x >= 0x1B1) {
            g_CurrentEntity->posX.i.hi = 0x1A8 - scrollX;
        }
    }

    if (g_CurrentEntity->velocityX < 0) {
        x -= 8;

        if (x < 0x50) {
            g_CurrentEntity->posX.i.hi = 0x58 - (u16)g_Tilemap.scrollX.i.hi;
        }
    }
}

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", func_us_801B385C);

#include "e_werewolf_attack_hitbox.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", func_us_801B503C);

#include "e_werewolf_after_image.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", func_us_801B52FC);

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", EntityWerewolfDeathFlames);
