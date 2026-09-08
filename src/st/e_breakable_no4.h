// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitBreakable;

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->blendMode = blend_modes[breakableType];
        self->hitboxHeight = hitbox_heights[breakableType];
        self->animSet = anim_sets[breakableType];
        self->unk5A = unk5a_arr[breakableType];
        self->palette = palettes[breakableType];
        self->hitboxOffY = hitbox_y_offsets[breakableType];
    }

    AnimateEntity(anims[breakableType], self);

    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = params_arr[breakableType];
        }

        switch (breakableType) {
        case 2:
        case 3:
            break;

        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_BREAKABLE_RELIC, entity);
                entity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;

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
                entity->params = 0x29;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        }

        ReplaceBreakableWithItemDrop(self);
    }
}
