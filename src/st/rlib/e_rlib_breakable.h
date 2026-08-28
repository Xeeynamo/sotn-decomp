// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitBreakable;
extern AnimationFrame* g_RlibBreakableAnimations[];
extern u8 g_RlibBreakableHitboxHeights[];
extern u8 g_RlibBreakableExplosionTypes[];
extern u16 g_RlibBreakablePalettes[];
extern u16 g_RlibBreakableAnimSets[];
extern u8 g_RlibBreakableBlendModes[];
extern u16 g_RlibBreakableUnk5A[];
extern u16 g_RlibBreakableHitboxOffsetsY[];

#ifdef VERSION_PSP
extern s32 E_ID(UNK_1B);
extern s32 E_ID(UNK_28);
#endif

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        if (breakableType < 5) {
            entity = self + 1;
            CreateEntityFromEntity(E_ID(UNK_1B), self, entity);
            entity->params = breakableType;
            entity->zPriority = self->zPriority;
        }
        self->blendMode = g_RlibBreakableBlendModes[breakableType];
        self->hitboxHeight = g_RlibBreakableHitboxHeights[breakableType];
        self->animSet = g_RlibBreakableAnimSets[breakableType];
        self->unk5A = g_RlibBreakableUnk5A[breakableType];
        self->palette = g_RlibBreakablePalettes[breakableType];
        self->hitboxOffY = g_RlibBreakableHitboxOffsetsY[breakableType];
    }
    AnimateEntity(g_RlibBreakableAnimations[breakableType], self);
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_RlibBreakableExplosionTypes[breakableType];
        }
        switch (breakableType) {
        case 2:
        case 3:
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            break;
        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(UNK_28), entity);
                entity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = 3;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        default:
            g_api.PlaySfx(SFX_GLASS_BREAK_C);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}
