// SPDX-License-Identifier: AGPL-3.0-or-later
void SpawnDestructAnim(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 variant, s16 xStep) {
    s32 i;
    s16 initialX;
    s32 currentX;
    s16 currentY;
    s16* clut;
    SaturnSpriteResource* resource;
    Entity* entity;
    SpriteObject* sprite;

    i = 0;
    initialX = x + self->posX.i.hi;
    currentY = y + self->posY.i.hi;
    if (i < count) {
        resource = &g_EntitySpriteBank01;
        currentX = initialX;
        do {
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity != NULL) {
                entity->entityId = SPAWN_DESTRUCT_ANIM_ID;
                entity->pfnUpdate = EntityDestructAnim;
                entity->params = params;
                entity->posX.i.hi = currentX;
                entity->posY.i.hi = currentY;
                entity->ext.destructAnim.index = variant + i;
                entity->drawFlags = 3;
                entity->scaleY = entity->scaleX =
                    g_ExplosionVariantSizes[variant + i];
                clut = &DAT_06045FA8;
                sprite = CreateSpriteObject(
                    (u16)*clut, (u16)(s16)resource->flags, resource->images, 5);
                entity->unk0 = sprite;
                if (self->unk0 != NULL) {
                    sprite->zPriority = self->unk0->zPriority + 1;
                }
            }
            currentX += xStep;
            i++;
        } while (i < count);
    }
}
#undef SPAWN_DESTRUCT_ANIM_ID
