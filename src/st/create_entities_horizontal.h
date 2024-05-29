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

    while (true) {
        if (g_LayoutObjHorizontal[0] == LAYOUT_OBJ_START ||
            posX > g_LayoutObjHorizontal[0]) {
            break;
        }

        expected = 0;
        flag = (g_LayoutObjHorizontal[3] >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal -= 5;
    }
}
