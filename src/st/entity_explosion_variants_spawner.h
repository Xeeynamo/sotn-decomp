// SPDX-License-Identifier: AGPL-3.0-or-later

static u16 explosionVariantSizes[] = {
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
            newEntity->pfnUpdate = EntityExplosionVariants;
            newEntity->params = params;
            newEntity->ext.destructAnim.index = arg5 + i;
            newEntity->rotY = newEntity->rotX = explosionVariantSizes[arg5 + i];
            newEntity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
