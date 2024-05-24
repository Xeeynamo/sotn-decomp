/*
 * Creates entities between the previous vertical position and
 * the passed in y position going up.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
void CreateEntitiesAbove(s16 posY) {
    u8 flag;
    s32 expected;

    if (g_LayoutObjPosVertical != LAYOUT_OBJ_POSITION_FORWARD) {
        FindFirstEntityAbove(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        if (g_LayoutObjVertical->posY == LAYOUT_OBJ_END ||
            posY < g_LayoutObjVertical->posY) {
            break;
        }

        expected = 0;
        flag = (g_LayoutObjVertical->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical++;
    }
}

/*
 * Creates entities between the previous vertical position and
 * the passed in y position going down.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
void CreateEntitiesBelow(s16 posY) {
    u8 flag;
    s32 expected;

    if (posY < 0) {
        posY = 0;
    }

    if (g_LayoutObjPosVertical == LAYOUT_OBJ_POSITION_FORWARD) {
        FindFirstEntityBelow(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_BACKWARD;
    }

    while (true) {
        if (g_LayoutObjVertical->posY == LAYOUT_OBJ_START ||
            (posY > g_LayoutObjVertical->posY)) {
            break;
        }

        expected = 0;
        flag = (g_LayoutObjVertical->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical--;
    }
}
