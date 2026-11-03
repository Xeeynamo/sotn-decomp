// SPDX-License-Identifier: AGPL-3.0-or-later
void SetEntityCollisionTiles(Entity* self) {
    Tilemap* map;
    s32 w, h;
    s32 index;
    s32 i;
    s32 x, y;

    map = &g_Tilemap;
    for (i = 0; i < 4; i++) {
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        w = (x + map->scrollX.i.hi) * 4 / 5;
        h = (y - 0x18 + i * 0x10 + map->scrollY.i.hi);
        index = (w >> 4) + ((h >> 4) * map->hSize * 0x10);
        DAT_0608FFF8[index] = self->animCurFrame != 0 ? 3 : 0;
    }
}
