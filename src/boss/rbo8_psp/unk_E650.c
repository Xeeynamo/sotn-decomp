// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo8/rbo8.h"

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_E650", func_us_8019953C);

extern EInit g_EInitBreakable;
extern AnimationFrame* D_us_80180BBC[];
extern u8 D_us_80180BDC[];
extern u16 D_us_80180BEC[];
extern u8 D_us_80180BE4[];
extern u8 D_us_80180BFC[];

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (self->step) {
        AnimateEntity(D_us_80180BBC[breakableType], self);
        if (self->hitParams) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = D_us_80180BE4[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->blendMode = D_us_80180BFC[breakableType];
        self->hitboxHeight = D_us_80180BDC[breakableType];
        self->animSet = D_us_80180BEC[breakableType];
    }
}

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_E650", func_us_801955A0);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_E650", func_us_801955F8);

void func_801CE1E8(s32 step) {
    s32 i;

    g_CurrentEntity->step = (u16)step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB4[i] = 0;
    }
}

void func_801CE228(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB4[i] = 0;
    }
}

void polarPlacePartsList(s16* offsets) {
    Entity* entity;

    while (*offsets) {
        entity = g_CurrentEntity + *offsets;
        if (!entity->ext.GH_Props.unkA8) {
            polarPlacePart(entity);
        }
        offsets++;
    }
}
