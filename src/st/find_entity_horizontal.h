// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Scans `g_LayoutObjVertical` looking for the next element with
 * an x  position to the right of the provided argument or the end
 * of the list.
 *
 * - Parameters:
 *   - posX - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjHorizontal` will be positioned at an element with a
 *    x position larger than `posX` or the tail eleement.
 */
void FindFirstEntityToTheRight(s16 posX) {
    while (1) {
        u16* layoutEntity = g_LayoutObjHorizontal;
        if (layoutEntity[0] != LAYOUT_OBJ_START && layoutEntity[0] >= posX) {
            break;
        }

        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Scans `g_LayoutObjHorizontal` looking for the next element with an x
 * position below the provided argument or the beginning of the list.
 *
 * - Parameters:
 *   - posX - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with an
 *    x position smaller than `posX` or the head element.
 */
void FindFirstEntityToTheLeft(s16 posX) {
    while (true) {
        u16* layoutObject = g_LayoutObjHorizontal;
        if (layoutObject[0] != LAYOUT_OBJ_END &&
            (layoutObject[0] <= posX || layoutObject[0] == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}
