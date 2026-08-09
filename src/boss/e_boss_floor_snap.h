// SPDX-License-Identifier: AGPL-3.0-or-later

// Snaps the boss to the arena floor once it falls low enough.
#ifndef BOSS_FLOOR_Y
#define BOSS_FLOOR_Y 0xE0
#endif

bool func_us_80194338(s16* offsets) {
    s32 posY;

    offsets++;
    posY = g_CurrentEntity->posY.i.hi + *offsets + g_Tilemap.scrollY.i.hi;
    posY = BOSS_FLOOR_Y - posY;
    if (posY <= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}
