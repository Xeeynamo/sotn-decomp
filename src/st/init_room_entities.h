// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId) {
    u16* pObjLayoutStart = OBJ_LAYOUT_HORIZONTAL[objLayoutId];
    Tilemap* tilemap = &g_Tilemap;
    s16 temp_s0;
    s16 arg0;
    s16 i;
    u16* temp_v1;

    g_LayoutObjHorizontal = pObjLayoutStart;
    g_LayoutObjVertical = OBJ_LAYOUT_VERTICAL[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        g_LayoutObjHorizontal = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp_v1 = g_LayoutObjHorizontal;
            g_LayoutObjHorizontal = temp_v1 + 1;
            arg0 -= temp_v1[0];
            if (arg0 < 0) {
                break;
            }
            g_LayoutObjHorizontal = temp_v1 + 3;
        }
        g_LayoutObjHorizontal = (temp_v1[2] << 0x10) + temp_v1[1];
        g_LayoutObjVertical += i * 2 + 2;
        g_LayoutObjVertical = (g_LayoutObjVertical[LAYOUT_OBJ_POS_Y] << 0x10) +
                              g_LayoutObjVertical[LAYOUT_OBJ_POS_X];
    }
    arg0 = tilemap->scrollX.i.hi;
    temp_s0 = arg0 + 320;
    i = arg0 - 64;
    if (i < 0) {
        i = 0;
    }

    g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    FindFirstEntityToTheRight(i);
    CreateEntitiesToTheRight(temp_s0);
    FindFirstEntityAbove(tilemap->scrollY.i.hi + 288);
}
