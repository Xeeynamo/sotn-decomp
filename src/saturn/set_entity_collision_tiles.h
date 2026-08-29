// SPDX-License-Identifier: AGPL-3.0-or-later
void SetEntityCollisionTiles(Entity* arg0) {
    Tilemap* map;
    u8* dest;
    s16 scroll_y;
    s32 index;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;

    map = &g_Tilemap;
    i = 0;
    dest = DAT_0608FFF8;
    offset = -0x18;
    do {
        x = arg0->posX.i.hi;
        y = arg0->posY.i.hi;
        index = ((x + map->scrollX.i.hi) << 2) / 5;
        scroll_y = map->scrollY.i.hi;
        index =
            (index >> 4) + (((y + offset + scroll_y) >> 4) * map->hSize * 0x10);
        dest[index] = arg0->animCurFrame != 0 ? 3 : 0;
        i += 1;
        offset += 0x10;
    } while (i <= 3);
}
