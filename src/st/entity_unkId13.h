extern u16 g_InitDataEnt13[];

void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_InitDataEnt13);
        entity->ext.ent13.parentId = entity->ext.ent13.parent->entityId;
    case 1:
        if (entity->ext.ent13.fiveFrameCounter++ >= 5) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = entity->params;
            }
            entity->ext.ent13.fiveFrameCounter = 0;
        }
        entity->posX.i.hi = entity->ext.ent13.parent->posX.i.hi;
        entity->posY.i.hi = entity->ext.ent13.parent->posY.i.hi;
        if (entity->ext.ent13.parent->entityId != entity->ext.ent13.parentId) {
            DestroyEntity(entity);
        }
        break;
    }
}
