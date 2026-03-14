// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern u16 g_EInitInteractable;

static s32 D_us_80181A68[] = {
    FIX(-1), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3)};
static u8 D_us_80181A7C[] = {1, 9, 21, 43};
static u16 D_us_80181A80[] = {16, 24, 42, 46};

void EntityUnkId22(Entity* self) {
    if (!self->step) {
        InitializeEntity(&g_EInitInteractable);
        self->animSet = 2;
        self->animCurFrame = D_us_80181A7C[self->params & 0xF];
        self->velocityY = D_us_80181A68[self->params & 0xF];
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_NOT_AN_ENEMY |
                      FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0x10) {
            self->palette = PAL_FLAG(0x195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0x20) {
            self->blendMode = BLEND_SUB | BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->params &= 0xF;
        self->step++;
        return;
    }
    self->posY.val += self->velocityY;
    self->poseTimer++;
    if (!(self->poseTimer % 2)) {
        self->animCurFrame += 1;
    }
    if (self->poseTimer > D_us_80181A80[self->params]) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801B9FC8);

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801BA21C);

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801BAD1C);

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801BAE9C);

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801BB000);

INCLUDE_RODATA("st/rnz0/nonmatchings/e_unk1F-23", D_us_801AAD84);

INCLUDE_ASM("st/rnz0/nonmatchings/e_unk1F-23", func_us_801BB5D8);
