// SPDX-License-Identifier: AGPL-3.0-only
/*
 * Creates any new entities that may need to be created
 * based on a change in the scroll delta.
 */
void UpdateRoomPosition() {
    Tilemap* tilemap = &g_Tilemap;
    s16 tmp;
    if (g_ScrollDeltaX != 0) {
        tmp = tilemap->scrollX.i.hi;
        if (g_ScrollDeltaX > 0) {
            tmp += 320;
            CreateEntitiesToTheRight(tmp);
        } else {
            tmp -= 64;
            CreateEntitiesToTheLeft(tmp);
        }
    }

    if (g_ScrollDeltaY != 0) {
        tmp = tilemap->scrollY.i.hi;
        if (g_ScrollDeltaY > 0) {
            tmp += 288;
            CreateEntitiesAbove(tmp);
        } else {
            tmp -= 64;
            CreateEntitiesBelow(tmp);
        }
    }
}
