#ifndef HARD_LINK
void DestroyEntitiesFromIndex(s16 index) {
    Entity* entity = &g_Entities[index];

    while (entity < &g_Entities[TOTAL_ENTITY_COUNT - 1]) {
        DestroyEntity(entity);
        entity++;
    }
}
#endif
