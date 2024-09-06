// SPDX-License-Identifier: AGPL-3.0-or-later
void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u16 index = entity->entityRoomIndex - 1 >> 5;
        g_unkGraphicsStruct.D_80097428[index] |=
            1 << ((entity->entityRoomIndex - 1) & 0x1F);
    }
}
