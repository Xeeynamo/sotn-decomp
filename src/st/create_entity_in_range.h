// SPDX-License-Identifier: AGPL-3.0-or-later
void CreateEntityWhenInVerticalRange(LayoutEntity* obj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    posY = tilemap->scrollY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = obj->posY;
    if (posY < yClose || posY > yFar) {
        return;
    }
    switch (obj->entityId & 0xE000) {
    case 0x0:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        if (!entity->entityId) {
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0xA000:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        CreateEntityFromLayout(entity, obj);
        break;
    case 0x8000:
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* obj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    posX = tilemap->scrollX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = obj->posX;
    if (posX < xClose || posX > xFar) {
        return;
    }

    switch (obj->entityId & 0xE000) {
    case 0x0:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        if (!entity->entityId) {
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0xA000:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        CreateEntityFromLayout(entity, obj);
        break;
    case 0x8000:
        break;
    }
}
