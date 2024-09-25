Entity* SearchForEntityInRange(s32 rangeIndex, s32 entityId) {
    volatile u32 pad; // fake?
    s16 start = g_EntityRanges[rangeIndex].start;
    s16 end = g_EntityRanges[rangeIndex].end;
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}