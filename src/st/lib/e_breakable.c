// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

static u8 D_us_80180B58[] = {3, 4, 3, 5, 0, 0};
static u8 D_us_80180B60[] = {3, 6, 3, 7, 0, 0};
static u8 D_us_80180B68[] = {6, 8, 6, 9, 6, 10, 6, 11, 6, 12, 0, 0};
static u8 D_us_80180B74[] = {5, 9, 5, 10, 5, 11, 5, 12, 0, 0};
static u8 D_us_80180B80[] = {5, 13, 5, 14, 5, 15, 5, 16, 0, 0};
static u8 D_us_80180B8C[] = {5, 17, 5, 18, 5, 19, 0, 0};
static u8 D_us_80180B94[] = {5, 23, 0, 0};
static u8 D_us_80180B98[] = {5, 22, 0, 0};
static u8 D_us_80180B9C[] = {5, 20, -1, -1, 5, 21, 5, 21, -1, 0};
static u8* D_us_80180BA8[] = {
    D_us_80180B68, D_us_80180B68, D_us_80180B58, D_us_80180B60, D_us_80180B74,
    D_us_80180B80, D_us_80180B8C, D_us_80180B94, D_us_80180B98, D_us_80180B9C};
static u8 D_us_80180BD0[] = {8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8};
static u8 D_us_80180BDC[] = {2, 2, 0, 0, 2, 2, 2, 2, 2, 2};
static u16 D_us_80180BE8[] = {
    PAL_DRA(0x000), PAL_DRA(0x000), PAL_DRA(0x000), PAL_DRA(0x000),
    PAL_DRA(0x26C), PAL_DRA(0x26C), PAL_DRA(0x26C), PAL_DRA(0x26C),
    PAL_DRA(0x26C), PAL_DRA(0x26C)};
static u16 D_us_80180BFC[] = {
    ANIMSET_OVL(0x1), ANIMSET_OVL(0x1), ANIMSET_OVL(0x1), ANIMSET_OVL(0x1),
    ANIMSET_OVL(0xC), ANIMSET_OVL(0xC), ANIMSET_OVL(0xC), ANIMSET_OVL(0xC),
    ANIMSET_OVL(0xC), ANIMSET_OVL(0xC)};
static u8 D_us_80180C10[] = {
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE};
static u16 D_us_80180C1C[] = {
    0x00, 0x00, 0x00, 0x00, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B};
static u16 D_us_80180C30[12] = {0};

void EntityBreakable(Entity* self) {
    Entity* tempEntity;
    u16 params;

    params = self->params >> 0xC;
    if (!self->step) {
        InitializeEntity(D_us_80180800);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        if (params < 5) {
            tempEntity = self + 1;
            CreateEntityFromEntity(E_ID_3F, self, tempEntity);
            tempEntity->params = params;
            tempEntity->zPriority = self->zPriority;
        }
        self->drawMode = D_us_80180C10[params];
        self->hitboxHeight = D_us_80180BD0[params];
        self->animSet = D_us_80180BFC[params];
        self->unk5A = D_us_80180C1C[params];
        self->palette = D_us_80180BE8[params];
        self->hitboxOffY = D_us_80180C30[params];
    }
    AnimateEntity(D_us_80180BA8[params], self);
    if (self->hitParams) {
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
            tempEntity->params = D_us_80180BDC[params];
        }
        switch (params) {
        case 0:
            PlaySfxPositional(SFX_GLASS_BREAK_D);
            break;

        case 2:
        case 3:
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            break;

        case 9:
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_47, tempEntity);
                tempEntity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, tempEntity);
                tempEntity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, tempEntity);
                tempEntity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, tempEntity);
                tempEntity->params = 3;
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

void func_us_801AE7AC(Entity* self) {
    Entity* tempEntity;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->animSet = ANIMSET_OVL(0x1);
    }
    if (!self->params) {
        AnimateEntity(D_us_80180B58, self);
    } else {
        AnimateEntity(D_us_80180B60, self);
    }
    tempEntity = self - 1;
    if (tempEntity->entityId != 1) {
        if (!self->params) {
            self->animCurFrame = 13;
        } else {
            self->animCurFrame = 14;
        }
    }
}

void func_us_801AE84C(Entity* self) {
    u32 pad[10];
    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(0xC);
            self->unk5A = 0x5B;
            self->palette = PAL_DRA(0x26C);
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 256;
        } else {
            InitializeEntity(g_EInitParticle);
        }
        break;

    case 1:
        break;
    }
}
