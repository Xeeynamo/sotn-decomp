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
    while (1) {
        if (g_LayoutObjVertical->posY != LAYOUT_OBJ_START &&
            g_LayoutObjVertical->posY >= posY) {
            break;
        }

        g_LayoutObjVertical++;
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
        if (g_LayoutObjVertical->posY != LAYOUT_OBJ_END &&
            (posY >= g_LayoutObjVertical->posY ||
             g_LayoutObjVertical->posY == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjVertical--;
    }
}
