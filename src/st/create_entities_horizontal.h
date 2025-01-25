// SPDX-License-Identifier: AGPL-3.0-or-later
#include "create_entities_right.h"

/*
 * Creates entities between the previous horizontal position and
 * the passed in x position.
 *
 * - Parameters:
 *   - posX - the new left extent
 */
static void CreateEntitiesToTheLeft(s16 posX) {
    u16* layoutObjHorizontal;
    s32 expected;
    u8 flag;

    if (posX < 0) {
        posX = 0;
    }

    if (!g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheLeft(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_BACKWARD;
    }
// MAD only runs once to create one entity to the left.
#if !defined(VERSION_BETA)
    while (true) {
#else
    if (true) {
#endif
        layoutObjHorizontal = g_LayoutObjHorizontal;
        if (layoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START) {
            return;
        }

        if (posX > layoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            return;
        }

        flag = (layoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8);
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInVerticalRange(
                    (LayoutEntity*)g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#endif
        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}
