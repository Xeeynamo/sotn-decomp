// SPDX-License-Identifier: AGPL-3.0-or-later
void CreateEntityFromLayout(Entity* entity, LayoutEntity* initDesc) {
    Tilemap* tilemap;

    tilemap = &g_Tilemap;

    DestroyEntity(entity);
    entity->entityId = initDesc->entityId & 0x3FF;
#ifdef STAGE_IS_LIB
    entity->pfnUpdate = PfnEntityUpdates[entity->entityId];
#else
    entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
#endif
    entity->posX.i.hi = (s16)initDesc->posX - tilemap->scrollX.i.hi;
    entity->posY.i.hi = (s16)initDesc->posY - tilemap->scrollY.i.hi;
    entity->params = initDesc->params;
    entity->entityRoomIndex = initDesc->entityRoomIndex >> 8;
    entity->unk68 = (initDesc->entityId >> 0xA) & 7;
}
