// SPDX-License-Identifier: AGPL-3.0-or-later
void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
#ifdef STAGE_IS_LIB
    entity->pfnUpdate = PfnEntityUpdates[entityId];
#else
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
#endif
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
#ifdef STAGE_IS_LIB
    entity->pfnUpdate = PfnEntityUpdates[entityId];
#else
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
#endif
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}
