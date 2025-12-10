// SPDX-License-Identifier: AGPL-3.0-or-later
Entity* SearchForEntityInRange(s32 rangeIndex, s32 entityId) {
    s32 start = g_EntityRanges[rangeIndex * 2 + 0];
    s32 end = g_EntityRanges[rangeIndex * 2 + 1];
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; i <= end; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}
