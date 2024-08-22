// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Creates entities between the previous horizontal position and
 * the passed in x position toward the right.
 *
 * - Parameters:
 *   - posX - the new right extent
 */
void CreateEntitiesToTheRight(s16 posX) {
    s32 expected;
    u8 flag;

    // if previously scrolling left, scan right to the
    // previous x delta and start traversal from there
    // otherwise keep going from the current position.
    if (g_LayoutObjPosHorizontal != LAYOUT_OBJ_POSITION_FORWARD) {
        FindFirstEntityToTheRight(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        if (g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_END ||
            posX < g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            break;
        }

        expected = 0;
        flag = (g_LayoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}
