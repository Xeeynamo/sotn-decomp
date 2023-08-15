void UpdateStageEntities(void) {
    Entity* entity;
    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            if (!(entity->flags & FLAG_UNK_10000))
                continue;
            if (entity->flags & 0xF) {
                entity->palette =
                    UNK_Invincibility0[entity->nFramesInvincibility << 1 |
                                       LOH(entity->flags) & 1];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->hitEffect;
                    entity->hitEffect = 0;
                }
            }
        }

        g_CurrentEntity = entity;
        entity->pfnUpdate(entity);
        entity->unk44 = 0;
        entity->hitFlags = 0;
    }
}
