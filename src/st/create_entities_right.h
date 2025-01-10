// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Creates entities between the previous horizontal position and
 * the passed in x position toward the right.
 *
 * - Parameters:
 *   - posX - the new right extent
 */
static void CreateEntitiesToTheRight(s16 posX) {
    u16* layoutObjHorizontal;
    s32 expected;
    u8 flag;

    // if previously scrolling left, scan right to the
    // previous x delta and start traversal from there
    // otherwise keep going from the current position.
    if (g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheRight(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        layoutObjHorizontal = g_LayoutObjHorizontal;
        if (layoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_END ||
            posX < layoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            break;
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
        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}
