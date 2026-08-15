// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"

extern EInit g_EInitGorgon;
extern u8 D_pspeu_0925EEB0[];
extern u8 D_pspeu_0925EEE0[];


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

Primitive* func_pspeu_0923DD78(Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
    Point16 sp2C;
    Point16 sp28;
    Pos sp20;
    Pos sp18;
    s16 angle;

    angle = *arg2--;
    func_pspeu_0923D928(ent1, -14, angle, &sp20);
    sp2C.x = 6;
    sp2C.y = 6;
    sp28.x = 10;
    sp28.y = 8;
    prim->drawMode = 2;
    func_us_801D2424(&sp20, angle, &sp2C, ent1, angle, &sp28, prim);
    prim = prim->next;
    func_pspeu_0923D928(&sp20, 3, angle, &sp20);
    angle = *arg2--;
    func_pspeu_0923D928(&sp20, -12, angle, &sp18);
    sp2C.x = 6;
    sp2C.y = 6;
    sp28.x = 6;
    sp28.y = 6;
    func_us_801D2424(&sp18, angle, &sp2C, &sp20, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    func_pspeu_0923D928(&sp18, -4, angle, &sp18);
    angle = *arg2;
    func_pspeu_0923D928(&sp18, 5, angle, &sp18);
    func_pspeu_0923D928(&sp18, -22, angle, ent2);
    sp2C.x = 8;
    sp2C.y = 8;
    sp28.x = 10;
    sp28.y = 10;
    func_us_801D2424(ent2, angle, &sp2C, &sp18, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    return prim;
}

Primitive* func_pspeu_0923DF88(Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
    Point16 sp2C;
    Point16 sp28;
    Pos sp20;
    Pos sp18;
    s32 angle;

    angle = *arg2++;
    func_pspeu_0923D928(ent1, 22, angle, &sp20);
    sp2C.x = 8;
    sp2C.y = 8;
    sp28.x = 10;
    sp28.y = 10;
    func_us_801D2424(ent1, angle, &sp2C, &sp20, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    func_pspeu_0923D928(&sp20, -5, angle, &sp20);
    angle = *arg2++;
    func_pspeu_0923D928(&sp20, 4, angle, &sp20);
    func_pspeu_0923D928(&sp20, 12, angle, &sp18);
    sp2C.x = 6;
    sp2C.y = 6;
    sp28.x = 6;
    sp28.y = 6;
    func_us_801D2424(&sp20, angle, &sp2C, &sp18, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    angle = *arg2++;
    func_pspeu_0923D928(&sp18, -3, angle, &sp18);
    func_pspeu_0923D928(&sp18, 14, angle, ent2);
    sp2C.x = 6;
    sp2C.y = 6;
    sp28.x = 10;
    sp28.y = 8;
    func_us_801D2424(&sp18, angle, &sp2C, ent2, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    return prim;
}

Primitive* func_pspeu_0923E1A0(Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
    Point16 sp2C;
    Point16 sp28;
    Pos sp10;
    s32 angle;

    angle = *arg2++;
    func_pspeu_0923D928(ent1, 18, angle, &sp10);
    sp2C.x = 5;
    sp2C.y = 5;
    sp28.x = 5;
    sp28.y = 5;
    func_us_801D2424(ent1, angle, &sp2C, &sp10, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    func_pspeu_0923D928(&sp10, -4, angle, &sp10);
    angle = *arg2++;
    func_pspeu_0923D928(&sp10, 17, angle, ent2);
    sp2C.x = 7;
    sp2C.y = 9;
    sp28.x = 6;
    sp28.y = 10;
    func_us_801D2424(&sp10, angle, &sp2C, ent2, angle, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    return prim;
}

Primitive* func_pspeu_0923E300(Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
    Point16 sp2C;
    Point16 sp28;
    Pos sp20;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;
    
    var_s0 = ent2->x.val - ent1->x.val;
    if (g_CurrentEntity->facingLeft) {
        var_s0 = -var_s0;
    }
    var_s1 = ent2->y.val - ent1->y.val;
    *arg2 = ratan2(-var_s0, var_s1);
    var_s4 = 0xE00;
    var_s3 = 0x1100;
    var_s0 = var_s0 / 0x100;
    var_s1 = var_s1 / 0x100;
    var_s2 = SquareRoot0((var_s0 * var_s0) + (var_s1 * var_s1));
    if (var_s2 > 0x1F00) {
        var_s2 = 0x1F00;
    }
    
    var_s2 = (var_s2 * var_s4) / (var_s4 + var_s3);
    var_s3 = (var_s4 * var_s4) - (var_s2 * var_s2);
    var_s3 = SquareRoot0(var_s3);
    *arg2 += ratan2(var_s3, var_s2);
    func_pspeu_0923D928(ent1, 0x12, *arg2, &sp20);
    sp2C.x = 5;
    sp2C.y = 5;
    sp28.x = 5;
    sp28.y = 5;
    func_us_801D2424(ent1, *arg2, &sp2C, &sp20, *arg2, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    func_pspeu_0923D928(&sp20, -4, *arg2, &sp20);
    var_s0 = ent2->x.val - sp20.x.val;
    if (g_CurrentEntity->facingLeft) {
        var_s0 = -var_s0;
    }
    var_s1 = ent2->y.val - sp20.y.val;
    arg2++;
    *arg2 = ratan2(-var_s0, var_s1);
    sp2C.x = 7;
    sp2C.y = 9;
    sp28.x = 6;
    sp28.y = 0xA;
    func_us_801D2424(&sp20, *arg2, &sp2C, ent2, *arg2, &sp28, prim);
    prim->drawMode = 2;
    prim = prim->next;
    return prim;
}

#include "../step_towards.h"

s32 func_pspeu_0923E6D0(Entity* arg0, s16* arg1, Entity* arg2, s16* arg3, u16* arg4) {
    s32 var_s2;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s1;
    s16 var_s0;

    
    var_s2 = g_CurrentEntity->posX.i.hi;
    if (g_CurrentEntity->facingLeft ) {
        var_s2 = var_s2 - 2;
    } else {
        var_s2 = var_s2 + 2;
    }
    var_s4 = var_s2 - arg2->posX.i.hi;
    var_s5 = var_s2 - arg0->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s4 = -var_s4;
        var_s5 = -var_s5;
    }
    var_s3 = arg4[0];
    var_s1 = arg4[1];
    if (arg2->ext.ILLEGAL.s16[2] && (var_s3 < var_s4) && (var_s5 < -var_s3)) {
        return 1;
    }
    if (var_s4 < var_s3) {
        *arg3 += var_s1;
        var_s0 = *arg3 - 0x300;
    } else {
        var_s0 = *arg3 - 0x240;
    }
    StepTowards(arg3 + 1, var_s0 - 0x100, var_s1);
    StepTowards(arg3 + 2, var_s0 + 0x100, var_s1);
    if (-var_s3 < var_s5) {
        *arg1 -= var_s1;
        var_s0 = *arg1 - 0x240;
    } else {
        var_s0 = *arg1 - 0x300;
    }
    StepTowards(arg1 + 1, var_s0 - 0x100, var_s1);
    StepTowards(arg1 + 2, var_s0 + 0x100, var_s1);
    return 0;
}

s32 func_pspeu_0923E920(Entity* arg0, s16* arg1, Entity* arg2, s16* arg3, u16* arg4) {
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s4 = g_CurrentEntity->posX.i.hi;
    var_s2 = var_s4 - arg0->posX.i.hi;
    var_s3 = var_s4 - arg2->posX.i.hi;
    var_s0 = arg4[0];
    var_s1 = arg4[1];
    if (g_CurrentEntity->facingLeft) {
        var_s3 = -var_s3;
        var_s2 = -var_s2;
    }
    if (var_s2 < -(var_s0 + 6)) {
        if (g_CurrentEntity->facingLeft) {
            arg0->posX.i.hi += (-(var_s0 + 6) - var_s2);
        } else {
            arg0->posX.i.hi -= (-(var_s0 + 6) - var_s2);
        }
    }
    if ((arg2->ext.ILLEGAL.s16[2]) && (var_s0 < var_s3) && (var_s2 < -var_s0)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.ILLEGAL.u8[0x2E]) {                              /* irregular */
    case 0:
        StepTowards(arg3 + 1, -0x240, var_s1);
        if (StepTowards(arg3, 0x1C0, var_s1) != 0) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x2E] += 1;
        }
        break;
    case 1:
        if (StepTowards(arg3 + 1, *arg3, var_s1) != 0) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x2E] += 1;
        }
        break;
    case 2:
        if (var_s0 < var_s3) {
            *arg3 -= var_s1 / 2;
        }
        if (var_s3 < var_s0) {
            *arg3 += var_s1 / 2;
        }
        StepTowards(arg3 + 1, *arg3, var_s1);
        break;
    }
    return 0;
}

s32 func_pspeu_0923EBE8(Entity* arg0, s16* arg1, Entity* arg2, s16* arg3) {
    s32 temp_v1;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    s16 var_s0;

    var_s3 = g_CurrentEntity->posX.i.hi;
    var_s1 = var_s3 - arg2->posX.i.hi;
    var_s2 = var_s3 - arg0->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s1 = -var_s1;
        var_s2 = -var_s2;
    }
    if ((arg2->ext.ILLEGAL.s16[2]) && (var_s1 < -8) && (var_s2 > 8)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.ILLEGAL.u8[0x2E]) {                              /* irregular */
    case 0:
        if (var_s1 > -8) {
            *arg3 -= 0x10;
            var_s0 = *arg3 - 0x340;
            StepTowards(arg3 + 1, var_s0 - 0x140, 0x40);
            StepTowards(arg3 + 2, var_s0 + 0x140, 0x40);
        } else {
            g_CurrentEntity->ext.ILLEGAL.u8[0x2E] += 1;
        }
        break;
    case 1:
        if (var_s1 > -8) {
            *arg3 -= 0x10;
        } else {
            var_s0 = *arg3 - 0x240;
            StepTowards(arg3 + 1, var_s0 - 0x60, 0x20);
            StepTowards(arg3 + 2, var_s0 + 0x60, 0x20);
        }
        break;
    }
    if (var_s2 < 8) {
        *arg1 += 12;
        var_s0 = *arg1 - 0x2C0;
        StepTowards(arg1 + 1, var_s0 - 0x60, 0x14);
        StepTowards(arg1 + 2, var_s0 + 0x60, 0x14);
    } else {
        arg1[2] += 12;
    }
    return 0;
}

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
    u16 sp38[2];
    s32 primIndex;
    Entity* other7;
    Entity* other6;
    s32 var_s5;
    s16* var_s4;
    s16* var_s3;
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
            var_s4 = &self->ext.ILLEGAL.s16[2];
            other6 = self + 2;
            var_s3 = &self->ext.ILLEGAL.s16[5];
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.ILLEGAL.s16[5];
            other6 = self + 1;
            var_s3 = &self->ext.ILLEGAL.s16[2];
        }
        switch (self->step) {                          /* switch 2; irregular */
        case 17:                                    /* switch 2 */
            sp38[0] = 0xA;
            sp38[1] = 0x10;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, sp38);
            break;
        case 16:                                    /* switch 2 */
            sp38[0] = 8;
            sp38[1] = 8;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, sp38);
            break;
        case 18:                                    /* switch 2 */
            sp68 = func_pspeu_0923EBE8(other7, var_s4, other6, var_s3);
            break;
        case 20:
        case 21:
            break;
        }
        prim = self->ext.prim;
        prim = func_pspeu_0923DD78((Pos*)other7, (Pos*)self, var_s4 + 2, prim);
        func_pspeu_0923DF88((Pos*)self, (Pos*)other6, var_s3, prim);
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
            var_s4 = &self->ext.ILLEGAL.s16[2];
            other6 = self + 2;
            var_s3 = &self->ext.ILLEGAL.s16[5];
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.ILLEGAL.s16[5];
            other6 = self + 1;
            var_s3 = &self->ext.ILLEGAL.s16[2];
        }
        switch (self->step_s) {                          /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            self->ext.ILLEGAL.u8[0x2F] = 0;
            StepTowards(var_s4 + 1, -0x600, 0x30);
            StepTowards(var_s4 + 2, -0x400, 0x30);
            StepTowards(var_s3, 0x400, 0x50);
            StepTowards(var_s3 + 1, -0x300, 0x38);
            StepTowards(var_s3 + 2, -0x500, 0x38);
            prim = self->ext.prim;
            prim = (Primitive*)func_pspeu_0923DD78((Pos*)other7, (Pos*)self, var_s4 + 2, prim);
            func_pspeu_0923DF88((Pos*)self, (Pos*)other6, var_s3, prim);
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

void func_us_801D0CFC(Entity* self) {
    Point16 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    Collider sp3C;
    u16 sp38[2];
    s32 primIndex;
    Entity* other7;
    s16* var_s6;
    s32 var_s5;
    s16* var_s4;
    Entity* other3;
    u8* var_s2;
    Entity* other;
    Primitive* prim;


    self->animCurFrame = 13;
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 13;
        self->drawFlags = 4;
        self->zPriority = 0x73;
        other = self + 1;        
        CreateEntityFromEntity(0x41U, self, other);
        other->params = 0x10;
        other = self + 2;
        CreateEntityFromEntity(0x41U, self, other);
        other->params = 0x11;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        var_s2 = D_pspeu_0925EEE0;
        while(prim != NULL) {
            prim->tpage = 0x13;
            prim->clut = 0x232;
            prim->u0 = *var_s2++;
            prim->v0 = *var_s2++;
            prim->u1 = *var_s2++;
            prim->v1 = *var_s2++;
            prim->u2 = *var_s2++;
            prim->v2 = *var_s2++;
            prim->u3 = *var_s2++;
            prim->v3 = *var_s2++;
            prim->drawMode = 8;
            prim = prim->next;
        }
        self->ext.ILLEGAL.s16[2] = 0;
        self->ext.ILLEGAL.s16[3] = 0x40;
        self->step = 0x15;
        break;
    case 17:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
        if (self->ext.ILLEGAL.u8[0x2C] == 0) {
            other3 = self + 1;
            var_s4 = &self->ext.ILLEGAL.s16[2];
            other7 = self + 2;
            var_s6 = &self->ext.ILLEGAL.s16[4];
        } else {
            other3 = self + 2;
            var_s4 = &self->ext.ILLEGAL.s16[4];
            other7 = self + 1;
            var_s6 = &self->ext.ILLEGAL.s16[2];
        }
        switch (self->step) {                          /* switch 2; irregular */
        case 17:                                    /* switch 2 */
            sp38[0] = 0xA;
            sp38[1] = 0x40;
            sp68 = func_pspeu_0923E920(other3, var_s4, other7, var_s6, sp38);
            break;
        case 16:                                    /* switch 2 */
            sp38[0] = 8;
            sp38[1] = 32;
            sp68 = func_pspeu_0923E920(other3, var_s4, other7, var_s6, sp38);
            break;
        case 18:                                    /* switch 2 */
            sp68 = func_pspeu_0923EE78(other3, var_s4, other7, var_s6);
            break;
        }
        prim = self->ext.prim;
        prim = func_pspeu_0923E300((Pos*)self, (Pos*)other3, var_s4, prim);
        func_pspeu_0923E1A0((Pos*)self, (Pos*)other7, var_s6, prim);
        func_pspeu_0923F198(2);
        if (sp68 != 0) {
            self->ext.ILLEGAL.u8[0x32] = 1;
            self->ext.ILLEGAL.u8[0x2C] ^= 1;
            self->ext.ILLEGAL.u8[0x2E] = 0;
        } else {
            self->ext.ILLEGAL.u8[0x32] = 0;
        }
        self->rotate = self->ext.ILLEGAL.s16[2] / 2;
        break;
    case 20:
    case 21:
        self->ext.ILLEGAL.u8[0x2F] = 0;
        if (self->ext.ILLEGAL.u8[0x2C] == 0) {
            other3 = self + 1;
            var_s4 = &self->ext.ILLEGAL.s16[2];
            other7 = self + 2;
            var_s6 = &self->ext.ILLEGAL.s16[4];
        } else {
            other3 = self + 2;
            var_s4 = &self->ext.ILLEGAL.s16[4];
            other7 = self + 1;
            var_s6 = &self->ext.ILLEGAL.s16[2];
        }
        prim = self->ext.prim;
        if (self->step == 21) {
            prim = func_pspeu_0923E1A0((Pos*)self, (Pos*)other3, var_s4, prim);
            func_pspeu_0923E1A0((Pos*)self, (Pos*)other7, var_s6, prim);
        } else {
            prim = func_pspeu_0923E300((Pos*)self, (Pos*)other3, var_s4, prim);
            func_pspeu_0923E300((Pos*)self, (Pos*)other7, var_s6, prim);
        }
        func_pspeu_0923F198(2);
        break;
    case 19:                                        /* switch 1 */
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.ILLEGAL.u8[0x2F] = 1;
            self->animCurFrame = 0;
            for(prim = self->ext.prim; prim != NULL; prim = prim->next) {
                prim->drawMode |= 8;
            }
        }
        break;
    case 22:                                        /* switch 1 */
        switch (self->step_s) {                          /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            other3 = self + 1;
            var_s4 = &self->ext.ILLEGAL.s16[2];
            prim = self->ext.prim;
            for(var_s5 = 0; var_s5 < 2; var_s5++) {
                if(other3->ext.ILLEGAL.s16[2]){
                    prim = func_pspeu_0923E300((Pos*)self, (Pos*)other3, var_s4, prim);
                } else {
                    prim = func_pspeu_0923E1A0((Pos*)self, (Pos*)other3, var_s4, prim);
                }
                other3 = self + 2;
                var_s4 = &self->ext.ILLEGAL.s16[4];
            }
            func_pspeu_0923F198(2);
            sp64 = self->posX.i.hi;
            sp60 = self->posY.i.hi + 0x18;
            g_api.CheckCollision(sp64, sp60, &sp3C, 0);
            if (sp3C.effects & 1) {
                other = self - 3;
                other->ext.ILLEGAL.u8[0x2F] = 1;
                PlaySfxPositional(0x653);
                self->step_s += 1;
            }
            break;
        case 1:
            other = self - 4;
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
            self->ext.ILLEGAL.u8[0x2F] = 1;
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
    other = self + 5;
    other->facingLeft = self->facingLeft;
    if (!self->ext.ILLEGAL.u8[0x2F]) {
        other = self - 4;
        other->posX.i.hi = self->posX.i.hi;
        other->posY.i.hi = self->posY.i.hi;
        other = self + 5;
        other->posX.i.hi = self->posX.i.hi + 0;
        other->posY.i.hi = self->posY.i.hi - 13;
    }
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D136C);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D15C0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D1BF0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2038);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D21C8);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2264);
