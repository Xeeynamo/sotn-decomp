// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Creates entities between the previous vertical position and
 * the passed in y position going up.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
static void CreateEntitiesAbove(s16 posY) {
    u16* layout;
    s32 expected;
    u8 flag;

    if (g_LayoutObjPosVertical) {
        FindFirstEntityAbove(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        layout = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];

        if (layout[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_END ||
            posY < layout[LAYOUT_OBJ_POS_X]) {
            break;
        }

        flag = layout[LAYOUT_OBJ_ID] >> 8;
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#endif
        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Creates entities between the previous vertical position and
 * the passed in y position going down.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
static void CreateEntitiesBelow(s16 posY) {
    u16* layout;
    s32 expected;
    u8 flag;

    if (posY < 0) {
        posY = 0;
    }

    if (!g_LayoutObjPosVertical) {
        FindFirstEntityBelow(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_BACKWARD;
    }

    while (true) {
        layout = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (layout[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START ||
            (posY > layout[LAYOUT_OBJ_POS_X])) {
            break;
        }
        flag = layout[LAYOUT_OBJ_ID] >> 8;
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#endif
        g_LayoutObjVertical -= sizeof(LayoutEntity) / sizeof(u16);
    }
}
