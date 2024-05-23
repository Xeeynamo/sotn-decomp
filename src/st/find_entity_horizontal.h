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
    while (true) {
        if (g_LayoutObjHorizontal->posX != LAYOUT_OBJ_START &&
            g_LayoutObjHorizontal->posX >= posX) {
            break;
        }

        g_LayoutObjHorizontal++;
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
        if (g_LayoutObjHorizontal->posX != LAYOUT_OBJ_END &&
            (posX >= g_LayoutObjHorizontal->posX ||
             g_LayoutObjHorizontal->posX == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjHorizontal--;
    }
}
