// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

extern s32 D_psp_E_UNK_3C;
extern AnimateEntityFrame* D_pspeu_09263610[];
extern u8 D_pspeu_09263638[];
extern u8 D_pspeu_09263648[];
extern u16 D_pspeu_09263658[];
extern u16 D_pspeu_09263670[];
extern u16 D_pspeu_09263688[];
extern u8 D_pspeu_092636A0[];
extern u16 D_pspeu_092636B0[];
extern EInit g_EInitBreakable;

void EntityBreakable(Entity* self) {
    Entity* entity;
    s32 breakableType;

    breakableType = ((self->params >> 0xC) & 0xFFFF) & 0xFFFF;

    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->blendMode = D_pspeu_092636A0[breakableType & 0xFFFF];
        self->hitboxHeight = D_pspeu_09263638[breakableType & 0xFFFF];
        self->animSet = D_pspeu_09263670[breakableType & 0xFFFF];
        self->unk5A = D_pspeu_09263688[breakableType & 0xFFFF];
        self->palette = D_pspeu_09263658[breakableType & 0xFFFF];
        self->hitboxOffY = D_pspeu_092636B0[breakableType & 0xFFFF];
        if (!breakableType) {
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = ROT(180);
        }
    }
    AnimateEntity(D_pspeu_09263610[breakableType & 0xFFFF], self);
    if (self->hitParams) {
        entity =
            AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = D_pspeu_09263648[breakableType & 0xFFFF];
        }
        switch (breakableType & 0xFFFF) {
        case 0:
            self->drawFlags = ENTITY_DEFAULT;
            self->rotate = 0;
            g_api.PlaySfx(SFX_CANDLE_HIT);

        case 2:
            break;

        case 3:
            break;

        case 9:
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromCurrentEntity(D_psp_E_UNK_3C, entity);
                entity->params = 0x100;
            }

            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }

            PreventEntityFromRespawning(self);
            DestroyEntity(self);

            return;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = ((self->params) & 0x1FF);
            }

            PreventEntityFromRespawning(self);
            DestroyEntity(self);

            return;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
        }

        ReplaceBreakableWithItemDrop(self);
    }
}

void func_us_801C123C_from_no4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FF7;
        self->unk5A = 0x5B;
        self->palette = 0x25D;
        self->animCurFrame = 0x15;
        self->zPriority = 0x6A;
        self->step = 0x100;
    default:
        return;
    }
}
