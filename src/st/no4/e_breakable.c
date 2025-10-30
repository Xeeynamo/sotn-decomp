// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

static u8 D_us_80180DDC[] = {0x04, 0x01, 0x04, 0x02, 0x00};
static u8 D_us_80180DE4[] = {0x04, 0x00, 0x04, 0x00, 0x00};
static u8 D_us_80180DEC[] = {
    0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0x00};
static u8 D_us_80180DF8[] = {
    0x05, 0x05, 0x05, 0x06, 0x05, 0x07, 0x05, 0x08, 0x00};
static u8 D_us_80180E04[] = {0x00, 0x00, 0x00, 0x00};
static u8 D_us_80180E08[] = {
    0x05, 0x0D, 0x05, 0x0E, 0x05, 0x0F, 0x05, 0x10, 0x00};
static u8 D_us_80180E14[] = {0x05, 0x11, 0x05, 0x12, 0x05, 0x13, 0x00};
static u8 D_us_80180E1C[] = {0x05, 0x17, 0x00, 0x00};
static u8 D_us_80180E20[] = {0x05, 0x16, 0x00, 0x00};
static u8 D_us_80180E24[] = {
    0x05, 0x14, 0xFF, 0xFF, 0x05, 0x15, 0x05, 0x15, 0xFF, 0x00, 0x00, 0x00};
static u8* anims[] = {
    D_us_80180DDC, D_us_80180DE4, D_us_80180DEC, D_us_80180DF8, D_us_80180E04,
    D_us_80180E08, D_us_80180E14, D_us_80180E1C, D_us_80180E20, D_us_80180E24};

static u8 hitbox_heights[] = {
    0x08, 0x08, 0x28, 0x18, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00};
static u8 params_arr[] = {
    0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00};
static u16 palettes[] = {
    PAL_UNK_000, PAL_UNK_000, PAL_UNK_228, PAL_UNK_228, PAL_UNK_228,
    PAL_UNK_228, PAL_UNK_228, PAL_UNK_228, PAL_UNK_228, PAL_UNK_228};
static u16 anim_sets[] = {
    ANIMSET_DRA(0x3), ANIMSET_DRA(0x3), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB),
    ANIMSET_OVL(0xB), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB),
    ANIMSET_OVL(0xB), ANIMSET_OVL(0xB)};
static u16 unk5a_arr[] = {0x0000, 0x007C, 0x005B, 0x005B, 0x005B,
                          0x005B, 0x005B, 0x005B, 0x005B, 0x005B};
static u8 draw_modes[] = {
    DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE};
static u16 hitbox_y_offsets[] = {0x0000, 0x0000, 0xFFE8, 0xFFF0, 0x0000,
                                 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

#ifdef VERSION_PSP
extern s32 D_psp_E_ID_35;
#endif

void EntityBreakable(Entity* self) {
    Entity* tempEntity;
    u16 params;

    params = self->params >> 0xC;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = draw_modes[params];
        self->hitboxHeight = hitbox_heights[params];
        self->animSet = anim_sets[params];
        self->unk5A = unk5a_arr[params];
        self->palette = palettes[params];
        self->hitboxOffY = hitbox_y_offsets[params];
    }
    AnimateEntity(anims[params], self);
    if (self->hitParams) {
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
            tempEntity->params = params_arr[params];
        }
        switch (params) {
        case 2:
        case 3:
            break;

        case 9:
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(ID_35), tempEntity);
                tempEntity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;

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
                tempEntity->params = 0x29;
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

void func_us_801C123C(Entity* self) {
    u32 pad[10];
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(0xB);
        self->unk5A = 0x5B;
        self->palette = PAL_UNK_228;
        self->animCurFrame = 0x15;
        self->zPriority = 0x6A;
        self->step = 0x100;
        break;
    }
}
