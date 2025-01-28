// SPDX-License-Identifier: AGPL-3.0-or-later
Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->entityId == E_NONE) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}
