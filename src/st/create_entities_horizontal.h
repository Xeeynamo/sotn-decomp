// SPDX-License-Identifier: AGPL-3.0-or-later
#include "create_entities_right.h"

/*
 * Creates entities between the previous horizontal position and
 * the passed in x position.
 *
 * - Parameters:
 *   - posX - the new left extent
 */
void CreateEntitiesToTheLeft(s16 posX) {
    u8 flag;
    s32 expected;

    if (posX < 0) {
        posX = 0;
    }

    if (g_LayoutObjPosHorizontal == LAYOUT_OBJ_POSITION_FORWARD) {
        FindFirstEntityToTheLeft(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_BACKWARD;
    }
// MAD only runs once to create one entity to the left.
#if !defined(VERSION_BETA)
    while (true) {
#else
    if (true) {
#endif
        if (g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START ||
            posX > g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            return;
        }

        expected = 0;
        flag = (g_LayoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}
