// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"

extern EInit g_EInitGorgon;
extern u8 D_pspeu_0925EEB0[];


// These first two are copied from the Plate Lord?
static void func_pspeu_0923D928(Pos* src, s32 speed, s16 angle, Pos* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x.val += -(speed * rsin(angle) * 16);
    dst->y.val += speed * rcos(angle) * 16;
}

static void func_us_801D2424(Pos* arg0, s16 arg1, Point16* arg2, Pos* arg3, s16 arg4,
                             Point16* arg5, Primitive* prim) {
    prim->x0 = prim->x1 = arg0->x.i.hi;
    prim->y0 = prim->y1 = arg0->y.i.hi;
    prim->x2 = prim->x3 = arg3->x.i.hi;
    prim->y2 = prim->y3 = arg3->y.i.hi;
    if (g_CurrentEntity->facingLeft) {
        prim->x0 += FLT_TO_I(arg2->x * rcos(arg1));
        prim->x1 -= FLT_TO_I(arg2->y * rcos(arg1));
        prim->x2 += FLT_TO_I(arg5->x * rcos(arg4));
        prim->x3 -= FLT_TO_I(arg5->y * rcos(arg4));
    } else {
        prim->x0 -= FLT_TO_I(arg2->x * rcos(arg1));
        prim->x1 += FLT_TO_I(arg2->y * rcos(arg1));
        prim->x2 -= FLT_TO_I(arg5->x * rcos(arg4));
        prim->x3 += FLT_TO_I(arg5->y * rcos(arg4));
    }
    prim->y0 -= FLT_TO_I(arg2->x * rsin(arg1));
    prim->y1 += FLT_TO_I(arg2->y * rsin(arg1));
    prim->y2 -= FLT_TO_I(arg5->x * rsin(arg4));
    prim->y3 += FLT_TO_I(arg5->y * rsin(arg4));
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923DD78);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923DF88);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E1A0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E300);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", StepTowards);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E6D0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E920);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923EBE8);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923EE78);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F088);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F198);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F300);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", EntityGorgon);

void func_us_801D068C(Entity* self) {
    Point16 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    Collider sp3C;
    Point16 sp38;
    s32 primIndex;
    Entity* other7;
    Entity* other6;
    s32 var_s5;
    u8* var_s4;
    u8* var_s3;
    u8* var_s2;
    Entity* other;
    Primitive* prim;


    self->animCurFrame = 9;
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 9;
        self->zPriority = 0x70;
        self->zPriority += ((self->params) * 4);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0xA;
        self->hitboxOffX = -8;
        self->hitboxOffY = 8;
        other = self + 1;
        CreateEntityFromEntity(0x41U, self, other);
        other->params = 0;
        other = self + 2;
        CreateEntityFromEntity(0x41U, self, other);
        other->params = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        var_s2 = D_pspeu_0925EEB0;
        for(var_s5 = 0; var_s5 < 6; var_s5++) {
            prim->tpage = 0x13;
            prim->clut = 0x232;
            prim->priority = 0x72;
            prim->u0 = *var_s2++;
            prim->v0 = *var_s2++;
            prim->u1 = *var_s2++;
            prim->v1 = *var_s2++;
            prim->u2 = *var_s2++;
            prim->v2 = *var_s2++;
            prim->u3 = *var_s2++;
            prim->v3 = *var_s2++;
            prim = prim->next;
        }
        self->ext.ILLEGAL.s16[2] = 0x180;
        self->ext.ILLEGAL.s16[3] = -0x80;
        self->ext.ILLEGAL.s16[4] = 0x100;
        self->ext.ILLEGAL.s16[5] = 0x180;
        self->ext.ILLEGAL.s16[6] = -0x80U;
        self->ext.ILLEGAL.s16[7] = 0x100;
        self->step = 0x15;
        break;
    case 17:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
    case 21:                                        /* switch 1 */
    case 20:                                        /* switch 1 */
        self->ext.ILLEGAL.u8[0x2F] = 0;
        if (self->ext.ILLEGAL.u8[0x2C] == 0) {
            other7 = self + 1;
            var_s4 = &self->ext.ILLEGAL.u8[4];
            other6 = self + 2;
            var_s3 = &self->ext.ILLEGAL.u8[0xA];
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.ILLEGAL.u8[0xA];
            other6 = self + 1;
            var_s3 = &self->ext.ILLEGAL.u8[4];
        }
        switch (self->step) {                          /* switch 2; irregular */
        case 17:                                    /* switch 2 */
            sp38.x = 0xA;
            sp38.y = 0x10;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, &sp38);
            break;
        case 16:                                    /* switch 2 */
            sp38.x = 8;
            sp38.y = 8;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, &sp38);
            break;
        case 18:                                    /* switch 2 */
            sp68 = func_pspeu_0923EBE8(other7, var_s4, other6, var_s3);
            break;
        case 20:
        case 21:
            break;
        }
        prim = self->ext.prim;
        prim = (Primitive*)func_pspeu_0923DD78(other7, self, var_s4 + 4, prim);
        func_pspeu_0923DF88(self, other6, var_s3, prim);
        func_pspeu_0923F198(3);
        if (sp68 != 0) {
            self->ext.ILLEGAL.u8[0x32] = 1;
            self->ext.ILLEGAL.u8[0x2E] = 0;
            self->ext.ILLEGAL.u8[0x2C] ^= 1;
        } else {
            self->ext.ILLEGAL.u8[0x32] = 0;
        }
        break;
    case 19:                                        /* switch 1 */
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.ILLEGAL.u8[0x2F] = 1;
            for(prim = self->ext.prim, self->animCurFrame = 0; prim != NULL; prim = prim->next) {
                prim->drawMode |= 8;
            }
        }
        break;
    case 22:                                        /* switch 1 */
        if (self->ext.ILLEGAL.u8[0x2C] == 0) {
            other7 = self + 1;
            var_s4 = &self->ext.ILLEGAL.u8[4];
            other6 = self + 2;
            var_s3 = &self->ext.ILLEGAL.u8[0xA];
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.ILLEGAL.u8[0xA];
            other6 = self + 1;
            var_s3 = &self->ext.ILLEGAL.u8[4];
        }
        switch (self->step_s) {                          /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            self->ext.ILLEGAL.u8[0x2F] = 0;
            StepTowards(var_s4 + 2, -0x600, 0x30);
            StepTowards(var_s4 + 4, -0x400, 0x30);
            StepTowards(var_s3, 0x400, 0x50);
            StepTowards(var_s3 + 2, -0x300, 0x38);
            StepTowards(var_s3 + 4, -0x500, 0x38);
            prim = self->ext.prim;
            prim = (Primitive*)func_pspeu_0923DD78(other7, self, var_s4 + 4, prim);
            func_pspeu_0923DF88(self, other6, var_s3, prim);
            func_pspeu_0923F198(3);
            sp64 = self->posX.i.hi;
            sp60 = self->posY.i.hi + 0x18;
            g_api.CheckCollision(sp64, sp60, &sp3C, 0);
            if (sp3C.effects & 1) {
                g_api.func_80102CD8(1);
                PlaySfxPositional(0x654);
                self->step_s += 1;
            }
            break;
        case 1:
            other = self - 1;
            if (other->ext.ILLEGAL.u8[0x30]) {
                self->ext.ILLEGAL.u8[0x30] = 1;
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 3 */
            self->animCurFrame = 0;
            other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
            if (other != NULL) {
                CreateEntityFromEntity(2U, self, other);
                other->params = 3;
                other->zPriority = self->zPriority;
            }
            self->step_s += 1;
            break;
        case 3:                                     /* switch 3 */
            for(prim = self->ext.prim; prim != NULL; ) {
                if (prim->drawMode & 8) {
                    prim = prim->next;
                } else {
                    other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
                    if (other != NULL) {
                        CreateEntityFromCurrentEntity(2, other);
                        other->posX.i.hi = prim->x0;
                        other->posY.i.hi = prim->y0;
                        other->params = 1;
                    }
                    prim->drawMode = 8;
                    prim = prim->next;
                }
            }
            if (prim == NULL) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    }
    other = self + 1;
    other->facingLeft = self->facingLeft;
    other = self + 2;
    other->facingLeft = self->facingLeft;
    other = self + 7;
    other->facingLeft = self->facingLeft;
    if (!self->ext.ILLEGAL.u8[0x2F]) {
        if ((self->step == 0x10) || (self->step == 0x11)) {
            sp6C.y = 0x360;
        } else {
            sp6C.y = 0x330;
        }
        other = self + 3;
        func_pspeu_0923D928((Pos*)self, 0x22, sp6C.y, (Pos*)other);
        other = self + 7;
        other->posX.i.hi = self->posX.i.hi;
        if (self->facingLeft) {
            other->posX.i.hi -= 1;
        } else {
            other->posX.i.hi += 1;
        }
        other->posY.i.hi = self->posY.i.hi + 6;
    }
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D0CFC);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D136C);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D15C0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D1BF0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2038);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D21C8);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2264);
