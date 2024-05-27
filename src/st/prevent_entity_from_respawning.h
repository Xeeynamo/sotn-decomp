void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u32 value = (entity->entityRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}
