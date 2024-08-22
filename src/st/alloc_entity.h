// SPDX-License-Identifier: AGPL-3.0-only
Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (!current->entityId) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}
