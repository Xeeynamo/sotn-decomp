// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId) {
    Tilemap* tilemap = &g_Tilemap;
    s16 rightEdge;
    s16 temp;
    s16 i;

    g_LayoutObjHorizontal = (u16*)OBJ_LAYOUT_HORIZONTAL[objLayoutId];
    g_LayoutObjVertical = (u16*)OBJ_LAYOUT_VERTICAL[objLayoutId];

    if (*g_LayoutObjHorizontal != LAYOUT_OBJ_START) {
        g_LayoutObjHorizontal++;
        temp = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp -= *g_LayoutObjHorizontal++;
            if (temp < 0) {
                g_LayoutObjHorizontal =
                    (u16*)((g_LayoutObjHorizontal[LAYOUT_OBJ_POS_Y] << 16) +
                           g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X]);
                break;
            }
            g_LayoutObjHorizontal += 2;
        }
        g_LayoutObjVertical += i * 2 + 2;
        g_LayoutObjVertical =
            (u16*)((g_LayoutObjVertical[LAYOUT_OBJ_POS_Y] << 0x10) +
                   g_LayoutObjVertical[LAYOUT_OBJ_POS_X]);
    }
    temp = tilemap->scrollX.i.hi;
    i = temp - 64;
    rightEdge = temp + 320;

    if (i < 0) {
        i = 0;
    }

    g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    FindFirstEntityToTheRight(i);
    CreateEntitiesToTheRight(rightEdge);
    temp = tilemap->scrollY.i.hi;
    i = temp + 288;
    FindFirstEntityAbove(i);
}
