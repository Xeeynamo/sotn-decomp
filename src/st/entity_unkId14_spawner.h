// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_eUnk14SpawnRots[];

void EntityUnkId14Spawner(
    Entity* self, u8 count, u8 params, s32 x, s32 y, u8 arg5, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->posX.i.hi = newX + xGap * i;
            newEntity->posY.i.hi = newY;
            newEntity->entityId = E_ID_14;
            newEntity->pfnUpdate = EntityUnkId14;
            newEntity->params = params;
            newEntity->ext.generic.unk94 = arg5 + i;
            newEntity->rotY = newEntity->rotX = g_eUnk14SpawnRots[arg5 + i];
            newEntity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
