// SPDX-License-Identifier: AGPL-3.0-or-later

static s16 explosionVariantSizes[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};

void EntityExplosionVariantsSpawner(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 index, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->entityId = E_ID_14;
            newEntity->pfnUpdate = EntityExplosionVariants;
            newEntity->params = params;
            newEntity->posX.i.hi = newX + i * xGap;
            newEntity->posY.i.hi = newY;
            newEntity->ext.destructAnim.index = i + index;
            newEntity->rotX = explosionVariantSizes[i + index];
            newEntity->rotY = newEntity->rotX;
            newEntity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
