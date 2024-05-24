/*
 * Creates any new entities that may need to be created
 * based on a change in the scroll delta.
 */
void UpdateRoomPosition() {
    Tilemap* tilemap = &g_Tilemap;

    if (g_ScrollDeltaX != 0) {
        s16 tmp = tilemap->scrollX.i.hi;
        if (g_ScrollDeltaX > 0)
            CreateEntitiesToTheRight(tmp + 320);
        else
            CreateEntitiesToTheLeft(tmp - 64);
    }

    if (g_ScrollDeltaY != 0) {
        s16 tmp = tilemap->scrollY.i.hi;
        if (g_ScrollDeltaY > 0)
            CreateEntitiesAbove(tmp + 288);
        else
            CreateEntitiesBelow(tmp - 64);
    }
}
