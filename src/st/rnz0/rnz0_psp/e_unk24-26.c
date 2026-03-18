// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924DBD0);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924DDF0);

extern EInit g_EInitLesserDemonSpit;

extern s16 D_pspeu_092595A0[];
extern u8 D_pspeu_09259690[];
extern u8 D_pspeu_092596A0[];
extern u8 D_pspeu_092596B0[];


// EntityLesserDemonSpit

void func_us_801BCAB0(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLesserDemonSpit);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x180;
        self->scaleY = 0x180;
        break;

    case 1:
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        self->velocityY = FIX(4.0);
        self->step++;
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_pspeu_09259690, self);
        if (CheckColliderOffsets(D_pspeu_092595A0, 0)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->scaleX = 0x140;
            self->scaleY = 0x200;
            self->hitboxWidth = 8;
            self->hitboxHeight = 8;
            self->step++;
        }
        break;

    case 3:
        if (!AnimateEntity(D_pspeu_092596A0, self)) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.lesserDemon.unk7C = prim;
                prim->tpage = 0x13;
                prim->clut = 0x231;
                prim->u0 = 0x68;
                prim->v0 = 0xC8;
                prim->u1 = 0x7F;
                prim->v1 = 0xC8;
                prim->u2 = 0x68;
                prim->v2 = 0xFF;
                prim->u3 = 0x7F;
                prim->v3 = 0xFF;
                prim->x0 = self->posX.i.hi - 0x10;
                prim->x1 = prim->x0 + 0x2C;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = self->posY.i.hi - 0x30;
                prim->y1 = prim->y0;
                prim->y2 = self->posY.i.hi + 0xC;
                prim->y3 = prim->y2;
                prim->priority = self->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            } else {
                DestroyEntity(self);
                return;
            }
            self->animCurFrame = 0x25;
            self->poseTimer = 0;
            self->pose = 0;
            self->ext.lesserDemon.unk80 = 0;
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->step++;
        }
        break;

    case 4:
        prim = self->ext.lesserDemon.unk7C;
        if (self->ext.lesserDemon.unk80++ > 0x10) {
            self->step++;
            self->ext.lesserDemon.unk80 = 0x1D;
            self->hitboxHeight = 0x40;
            self->hitboxOffY -= 0x20;
        } else {
            prim->y0 -= 0x10 - self->ext.lesserDemon.unk80;
            prim->y1 = prim->y0;
        }
        break;

    case 5:
        prim = self->ext.lesserDemon.unk7C;
        if (!--self->ext.lesserDemon.unk80) {
            self->pose = 0;
            self->poseTimer = 0;
            self->hitboxState = 0;
            self->step++;
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->y0 += 4;
            prim->y1 = prim->y0;
            prim->v2 -= 2;
            prim->v3 = prim->v2;
            self->hitboxHeight = 8;
            self->hitboxOffY = -4;
        }
        break;

    case 6:
        self->scaleY -= 0x20;
        if (!AnimateEntity(D_pspeu_092596B0, self)) {
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            self->step++;
        }
        break;

    case 7:
        self->scaleY -= 0x10;
        self->opacity -= 0x10;
        if (!self->opacity) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924E7D0);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924EB18);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924EE10);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_us_801BD7D0);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924F908);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924FE10);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_09250678);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", EntityLesserDemon);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_us_801BF7B0);
