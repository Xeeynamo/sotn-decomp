// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Scans `g_LayoutObjVertical` looking for the next element with
 * a y position above the provided argument or the end of the list.
 *
 * - Parameters:
 *   - posY - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with a
 *    y position larger than `posY` or the tail eleement.
 */
void FindFirstEntityAbove(s16 posY) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (*ptr != LAYOUT_OBJ_START && *ptr >= posY) {
            break;
        }
        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Scans `g_LayoutObjVertical` looking for the next element with a y
 * position below the provided argument or the beginning of the list.
 *
 * - Parameters:
 *   - posY - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with a
 *    y position smaller than `posY` or the head element.
 */
void FindFirstEntityBelow(s16 posY) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];

        if (*ptr != LAYOUT_OBJ_END &&
            (*ptr <= posY || *ptr == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjVertical -= sizeof(LayoutEntity) / sizeof(u16);
    }
}
