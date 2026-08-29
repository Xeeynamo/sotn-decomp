// SPDX-License-Identifier: AGPL-3.0-or-later
void EntityBreakable(Entity* self) {
    u16 breakableType = self->params >> 12;
    Entity* entity;
    s32 i;
    s16* debrisOffsets;

    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = 0x70;
        self->blendMode = g_RchiBreakableBlendModes[breakableType];
        self->hitboxHeight = g_RchiBreakableHitboxHeights[breakableType];
        self->animSet = g_RchiBreakableAnimSets[breakableType];
        entity = self + 1;
        CreateEntityFromEntity(E_ID(BACKGROUND_BLOCK), self, entity);
        if (breakableType) {
            entity->posY.i.hi += 0x20;
        } else {
            entity->posY.i.hi += 0x10;
        }
        entity->params = 1;
    }

    AnimateEntity(g_RchiBreakableAnimations[breakableType], self);
    if (self->hitParams) {
        g_api.PlaySfx(SFX_FIRE_SHOT);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_RchiBreakableExplosionTypes[breakableType];
            entity->params |= 0x10;
        }

        debrisOffsets = g_RchiBreakableDebrisOffsets;
        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(BREAKABLE_DEBRIS), self, entity);
                entity->posX.i.hi -= *debrisOffsets++;
                entity->posY.i.hi -= *debrisOffsets++;
                if (breakableType) {
                    entity->posY.i.hi += 0x14;
                }
                entity->params = i;
            }
        }
        if (breakableType) {
            for (i = 0; i < 3; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posX.i.hi -= *debrisOffsets++;
                    entity->posY.i.hi -= *debrisOffsets++;
                    entity->params = i + 4;
                }
            }
        }
        entity = self + 1;
        DestroyEntity(entity);
        ReplaceBreakableWithItemDrop(self);
    }
}
