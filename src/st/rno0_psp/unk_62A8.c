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

s32 func_pspeu_0923EE78(Entity* arg0, s16* arg1, Entity* arg2, s16* arg3) {
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s1 = g_CurrentEntity->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s1 += 2;
    } else {
        var_s1 -= 2;
    }
    var_s2 = var_s1 - arg0->posX.i.hi;
    var_s0 = var_s1 - arg2->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s0 = -var_s0;
        var_s2 = -var_s2;
    }
    if (arg2->ext.ILLEGAL.s16[2] && (var_s0 < -8) && (var_s2 > 8)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.ILLEGAL.u8[0x2E]) {                              /* irregular */
    case 0:
        StepTowards(arg3 + 1, -0x280, 0x20);
        if (StepTowards(arg3, -0xC0, 0x18)) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x2E] += 1;
        }
        break;
    case 1:
        if (StepTowards(arg3 + 1, *arg3, 0x20)) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x2E] += 1;
        }
        break;
    case 2:
        if (var_s0 < -8) {
            *arg3 += 0x14;
        }
        if (var_s0 > -8) {
            *arg3 -= 0x14;
        }
        StepTowards(arg3 + 1, *arg3, 0x20);
        break;
    }
    return 0;
}

s32 func_pspeu_0923F088(Entity* self, s32 arg1) {
    Collider sp2C;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;

    var_s3 = self->posX.i.hi;
    if (arg1 ^ g_CurrentEntity->facingLeft) {
        var_s3 += 0x38;
    } else {
        var_s3 -= 0x38;
    }
    var_s2 = self->posY.i.hi + 4;
    var_s1 = 0;
    for(var_s0 = 0; var_s0 < 2; var_s0++){
        g_api.CheckCollision(var_s3, var_s2, &sp2C, 0);
        if (var_s0 != 0) {
            if (!(sp2C.effects & 1)) {
                var_s1 |= 2;
            }
        } else if (sp2C.effects & 1) {
            var_s1 |= 1;
        }
        var_s2 += 4;
    }
    return var_s1;
}

void func_pspeu_0923F198(s32 count) {
    s32 i;
    Primitive* prim;

    prim = g_CurrentEntity->ext.prim;
    for(i = 0; i < count; i++) {
        if (g_CurrentEntity->ext.ILLEGAL.u8[0x2C] == 0) {
            prim->clut = 0x232;
            prim->priority = 0x72;
        } else {
            prim->clut = 0x233;
            prim->priority = 0x6E;
        }
        if (g_CurrentEntity->palette & 0x8000) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        }
        prim = prim->next;
    }
    for(i = 0; i < count; i++) {
        if (g_CurrentEntity->ext.ILLEGAL.u8[0x2C] == 0) {
            prim->clut = 0x233;
            prim->priority = 0x6E;
        } else {
            prim->clut = 0x232;
            prim->priority = 0x72;
        }
        if (g_CurrentEntity->palette & 0x8000) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        }
        prim = prim->next;
    }
}

static void func_pspeu_0923F300(s32 newStep) {
    Entity* ent;
    s32 i;

    for(ent = g_CurrentEntity, i = 0; i < 10; i++, ent++){
        ent->step = newStep;
        ent->step_s = 0;
        ent->ext.ILLEGAL.u8[0x2E] = 0;
    }
}

extern u8 D_pspeu_0925EF00;

void EntityGorgon(Entity* self) {
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 i;
    Entity* other_s0;
    Entity* other_s1;

    if ((self->flags & 0x100) && (self->step < 0x16)) {
        for(other_s0 = self, i = 0; i < 10; i++, other_s0++){
            other_s0->hitboxState = 0;
        }
        if ((self->step) != 0x13) {
            func_pspeu_0923F300(0x15);
            self->step = 0x16;
        }
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitGorgon);
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        self->zPriority = 0x70;
        self->animCurFrame = 0xA;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0xC;
        other_s1 = self + 1;
        CreateEntityFromEntity(0x3FU, self, other_s1);
        other_s1 = self + 4;
        CreateEntityFromEntity(0x40U, self, other_s1);
        other_s1 = self + 7;
        CreateEntityFromEntity(0x42U, self, other_s1);
        other_s1 = self + 9;
        CreateEntityFromEntity(0x43U, self, other_s1);
        other_s1 = self + 8;
        CreateEntityFromEntity(0x44U, self, other_s1);
        self->ext.ILLEGAL.s16[0x14] = 2;
        break;
    case 1:                                         /* switch 1 */
        if (!--self->ext.ILLEGAL.s16[0x14]) {
            for(other_s0 = self, i = 0; i < 9; i++, other_s0++){
                other_s0->parent = self;
                other_s0->nextPart = other_s0 + 1;
            }
            other_s0->parent = self;
            other_s0->nextPart = self;
            self->parent = NULL;
            func_pspeu_0923F300(0x10);
        }
        break;
    case 17:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[0x14] = 0x40;
            self->step_s++;
        }
        other_s1 = self + 4;
        if (other_s1->ext.ILLEGAL.u8[0x2C] == 0) {
            other_s1 = other_s1 + 1;
        } else {
            other_s1 = other_s1 + 2;
        }
        var_s4 = func_pspeu_0923F088(other_s1, 0);
        if (var_s4 != 0) {
            if (self->ext.ILLEGAL.s16[0x14]) {
                self->ext.ILLEGAL.u8[0x2D] = 0x13;
                func_pspeu_0923F300(0x15);
            }
            self->ext.ILLEGAL.s16[0x14] = 0x20;
        }
        if (self->ext.ILLEGAL.s16[0x14]) {
            self->ext.ILLEGAL.s16[0x14]--;
            break;
        } else if (GetDistanceToPlayerY() < 0x40) {
            other_s0 = &PLAYER;
            var_s3 = self->posX.i.hi - other_s0->posX.i.hi;
            if (self->facingLeft) {
                var_s3 = -var_s3;
            }
            if ((u16)var_s3 > 0xFFB0) {
                var_s4 = 1;
                self->ext.ILLEGAL.s16[0x14] = 0x10;
            }
            if ((var_s4 == 0) && (var_s3 > 0x60) && (self->step != 0x11)) {
                func_pspeu_0923F300(0x11);
            }
            if (!self->ext.ILLEGAL.s16[0x12]) {
                if (var_s3 < 0x50U) {
                    self->ext.ILLEGAL.s16[0x12] = 0x80;
                    SetStep(0x14U);
                    break;
                }
            } else {
                if (self->ext.ILLEGAL.s16[0x12] < 0) {
                    self->ext.ILLEGAL.s16[0x12] = 0x80;
                } else {
                    self->ext.ILLEGAL.s16[0x12]--;
                }
            }
        }
        if (var_s4 != 0) {
            self->ext.ILLEGAL.s16[0x14] = 0x20;
            self->ext.ILLEGAL.u8[0x2D] = 0x13;
            func_pspeu_0923F300(0x15);
        }
        if (self->hitParams) {
            self->ext.ILLEGAL.s16[0x14] = 0x40;
            func_pspeu_0923F300(0x12);
        }
        
        break;
    case 18:                                        /* switch 1 */
        other_s1 = self + 1;
        if (other_s1->ext.ILLEGAL.u8[0x2C] == 0) {
            other_s1 = other_s1 + 1;
        } else {
            other_s1 = other_s1 + 2;
        }
        var_s4 = func_pspeu_0923F088(other_s1, 1);
        if (!--self->ext.ILLEGAL.s16[0x14]) {
            var_s4 = 1;
        }
        if (var_s4 != 0) {
            self->ext.ILLEGAL.s16[0x14] = 0x18;
            self->ext.ILLEGAL.u8[0x2D] = 0x10;
            func_pspeu_0923F300(0x15);
        }
        break;
    case 19:                                        /* switch 1 */
        switch (self->step_s) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            other_s1 = self + 1;
            if (other_s1->ext.ILLEGAL.u8[0x2C] == 0) {
                other_s1 = other_s1 + 1;
            } else {
                other_s1 = other_s1 + 2;
            }
            self->posY.i.hi = other_s1->posY.i.hi - 0x16;
            if (self->facingLeft) {
                self->posX.i.hi -= 0xC;
            } else {
                self->posX.i.hi += 0xC;
            }
            self->ext.ILLEGAL.u8[0x2F] = 1;
            self->poseTimer = 0;
            self->pose = 0;
            self->step_s++;
            /* fallthrough */
        case 1:                                     /* switch 2 */
            if (AnimateEntity(&D_pspeu_0925EF00, self) == 0) {
                self->step_s++;
            }
            if (((self->pose) == 2) && (!self->poseTimer)) {
                self->facingLeft ^= 1;
                if (self->facingLeft) {
                    self->posX.i.hi -= 0xC;
                } else {
                    self->posX.i.hi += 0xC;
                }
            }
            break;
        case 2:                                     /* switch 2 */
            self->animCurFrame = 0xA;
            other_s1 = self + 1;
            if (other_s1->ext.ILLEGAL.u8[0x2C] == 0) {
                other_s1 = other_s1 + 1;
            } else {
                other_s1 = other_s1 + 2;
            }
            other_s1->posX.i.hi = self->posX.i.hi;
            self->ext.ILLEGAL.u8[0x2F] = 0;
            self->ext.ILLEGAL.s16[0x14] = 0x20;
            self->ext.ILLEGAL.u8[0x2D] = 0x10;
            func_pspeu_0923F300(0x15);
            break;
        }
        break;
    case 20:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            other_s0 = self + 4;
            if (other_s0->ext.ILLEGAL.u8[0x32]) {
                other_s0->step = 0x14;
                func_pspeu_0923F300(0x14);
                self->step_s = 1;
            }
            break;
        case 1:                                     /* switch 3 */
            other_s0 = self + 7;
            if (other_s0->step != 0x14) {
                other_s0 = &PLAYER;
                var_s3 = self->posX.i.hi - other_s0->posX.i.hi;
                if (var_s3 < 0x50U) {
                    func_pspeu_0923F300(0x14);
                } else {
                    func_pspeu_0923F300(0x10);
                }
            }
            break;
        }
        break;
    case 21:                                        /* switch 1 */
        if (!--self->ext.ILLEGAL.s16[0x14]) {
            if (self->ext.ILLEGAL.u8[0x2D]) {
                func_pspeu_0923F300(self->ext.ILLEGAL.u8[0x2D]);
            } else {
                func_pspeu_0923F300(0x10);
            }
        }
        break;
    case 22:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 4 */
        case 0:                                     /* switch 4 */
            other_s0 = self + 7;
            other_s0->step = 0x16;
            self->ext.ILLEGAL.s16[0x14] = 0x40;
            self->step_s++;
            /* fallthrough */
        case 1:                                     /* switch 4 */
            if (!(self->ext.ILLEGAL.s16[0x14] & 7)) {
                PlaySfxPositional(0x655);
                var_s3 = self->posX.i.hi;
                var_s5 = self->posY.i.hi;
                if (PLAYER.facingLeft) {
                    var_s3 -= ((Random() & 0x3F) - 0x10);
                } else {
                    var_s3 += ((Random() & 0x3F) - 0x10);
                }
                var_s5 += ((Random() & 0x1F) - 0x10);
                other_s1 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other_s1 != NULL) {
                    CreateEntityFromCurrentEntity(2, other_s1);
                    other_s1->params = 1;
                    other_s1->zPriority = ((self->zPriority) + 2);
                    other_s1->posX.i.hi = var_s3;
                    other_s1->posY.i.hi = var_s5;
                }
            }
            if (!--self->ext.ILLEGAL.s16[0x14]) {
                func_pspeu_0923F300(0x16);
                self->step_s = 2;
            }
            break;
        case 2:                                     /* switch 4 */
            other_s0 = self + 7;
            if (!other_s0->entityId) {
                self->step_s++;
            }
            break;
        case 3:                                     /* switch 4 */
            PlaySfxPositional(0x693);
            self->ext.ILLEGAL.u8[0x30] = 1;
            self->step_s++;
            break;
        case 4:                                     /* switch 4 */
            other_s1 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other_s1 != NULL) {
                CreateEntityFromEntity(2U, self, other_s1);
                other_s1->params = 3;
                other_s1->zPriority = self->zPriority;
            }
            self->ext.ILLEGAL.s16[0x14] = 8;
            self->step_s++;
            break;
        case 5:                                     /* switch 4 */
            if (!--self->ext.ILLEGAL.s16[0x14]) {
                self->animCurFrame = 0;
                for(other_s0 = self, i = 0; i < 9; i++, other_s0++){
                    DestroyEntity(other_s0);
                }
            }
            break;
        }
        break;
    }
    other_s1 = self + 1;
    other_s1->facingLeft = self->facingLeft;
    other_s1 = self + 4;
    other_s1->facingLeft = self->facingLeft;
    if (self->ext.ILLEGAL.u8[0x2F]) {
        1;
    }

}

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

void func_us_801D136C(Entity* self) {
    Collider sp1C;
    Entity* other;
    s32 xVar, yVar;

    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitGorgon);
        self->drawFlags = 4;
        self->animCurFrame = 0x10;
        if (self->params & 1) {
            self->zPriority = 0x6D;
            self->palette = 0x8234;
        } else {
            self->zPriority = 0x71;
        }
        self->hitboxWidth = 4;
        self->hitboxHeight = 6;
        return;
    case 19:                                        /* switch 1 */
        if (!self->step_s) {
            self->step_s += 1;
            return;
        }
        self->animCurFrame = 0;
        return;
    case 22:                                        /* switch 1 */
        switch (self->step_s) {                          /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            other = self - 1;
            if (other->ext.ILLEGAL.u8[0x30]) {
                self->ext.ILLEGAL.u8[0x30] = 1;
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 2 */
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(2U, self, other);
                other->params = 1;
                if (self->params & 1) {
                    other->zPriority = 0x75;
                } else {
                    other->zPriority = 0x71;
                }
            }
            self->animCurFrame = 0;
            self->step_s += 1;
            break;
        case 3:                                     /* switch 2 */
            break;
        }
    }
    if (!self->step_s) {
        if (self->params & 1) {
            self->zPriority = 0x6D;
            self->animCurFrame = 4;
        } else {
            self->zPriority = 0x71;
            self->animCurFrame = 0x10;
        }
        self->step_s += 1;
    }
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi + 6;
    g_api.CheckCollision(xVar, yVar, &sp1C, 0);
    if (sp1C.effects & 1) {
        self->posY.i.hi += sp1C.unk18;
        self->rotate = 0;
        self->ext.ILLEGAL.u16[2] = 1;
        if (!self->ext.ILLEGAL.u8[0x31]) {
            PlaySfxPositional(0x647);
            self->ext.ILLEGAL.u8[0x31] = 1;
        }
    } else {
        self->rotate = -0x100;
        self->ext.ILLEGAL.u16[2] = 0;
        self->ext.ILLEGAL.u8[0x31] = 0;
    }
}

extern EInit D_us_80180BDC;

extern AnimateEntityFrame D_pspeu_0925EF10;
extern AnimateEntityFrame D_pspeu_0925EF20;
extern AnimateEntityFrame D_pspeu_0925EF30;

void func_us_801D15C0(Entity* self) {
    Point16 sp6C;
    Collider sp48;
    Pos sp40;
    Pos sp38;
    Entity* other4;
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s16 var_s3;
    s32 temp_s2;

    s32 xVar, yVar;

    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_80180BDC);
        self->animCurFrame = 0xB;
        self->zPriority = 0x70;
        self->hitboxWidth = 7;
        self->hitboxHeight = 7;
        self->hitboxOffX = -3;
        self->drawFlags |= 4;
        primIndex = g_api_AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->tpage = 0x13;
        prim->clut = 0x232;
        prim->u0 = prim->u1 = 0x80;
        prim->u2 = prim->u3 = 0x60;
        prim->v0 = prim->v2 = 0x68;
        prim->v1 = prim->v3 = 0x80;
        prim->priority = 0x6F;
        prim->drawMode = 2;
        self->ext.ILLEGAL.u16[2] = 0x400;    
        break;
    case 19:                                        /* switch 1 */
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.ILLEGAL.u8[0x2F] = 1;
            self->animCurFrame = 0;
            prim = self->ext.prim;
            prim->drawMode |= 8;
        }
        break;
    case 20:                                        /* switch 1 */
        switch (self->step_s) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            temp_s2 = StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x600, 0x10);
            temp_s2 += StepTowards(&self->rotate, 0x300, 0x20);
            if (temp_s2 == 2) {
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            temp_s2 = StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x500, 0x18);
            temp_s2 = temp_s2 + StepTowards(&self->rotate, 0x100, 0x30);
            if ((AnimateEntity(&D_pspeu_0925EF10, self) == 0) && (temp_s2 == 2)) {
                self->ext.ILLEGAL.u16[0x14] = 0x40;
                PlaySfxPositional(0x77B);
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 2 */
            if (!(g_Timer & 3)) {
                other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (other != NULL) {
                    CreateEntityFromEntity(0x45U, self, other);
                    other->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        other->posX.i.hi += 0xC;
                    } else {
                        other->posX.i.hi -= 0xC;
                    }
                    other->posY.i.hi += 2;
                }
            }
            if (!--self->ext.ILLEGAL.s16[0x14]) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s += 1;
            }
            break;
        case 3:                                     /* switch 2 */
            temp_s2 = StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x400, 0x10);
            temp_s2 = temp_s2 + StepTowards(&self->rotate, 0, 0x20);
            if ((AnimateEntity(&D_pspeu_0925EF20, self) == 0) && (temp_s2 == 2)) {
                self->step = 0x15;
            }
            break;
        }
        break;
    case 17:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
        switch(self->step_s){
            case 0:
            if (StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x500, 8) != 0) {
                self->step_s += 1;
            }
            break;
            default:
                if (StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x400, 8) != 0) {
                self->step_s = 0;
            }
        }
    default:                                        /* switch 1 */
        self->ext.ILLEGAL.u8[0x2F] = 0;
        self->animCurFrame = 0xB;
        if (!(g_Timer & 0x7F)) {
            other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
            if (other != NULL) {
                PlaySfxPositional(0x77A);
                CreateEntityFromEntity(0x46U, self, other);
                other->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    other->posX.i.hi += 0x14;
                } else {
                    other->posX.i.hi -= 0x14;
                }
                other->posY.i.hi += 0x14;
            }
        }
        break;
    case 22:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            StepTowards((s16* ) &self->ext.ILLEGAL.u8[4], 0x400, 8);
            StepTowards(&self->rotate, 0x200, 0x10);
            AnimateEntity(&D_pspeu_0925EF30, self);
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi + 8;
            g_api.CheckCollision(xVar, yVar, &sp48, 0);
            if (sp48.effects & 1) {
                self->ext.ILLEGAL.u8[0x2F] = 1;
                PlaySfxPositional(0x653);
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 3 */
            other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
            if (other != NULL) {
                CreateEntityFromEntity(2U, self, other);
                other->params = 3;
            }
            DestroyEntity(self);
            return;
        }
        break;
    }
    other4 = self - 7;
    self->facingLeft = other4->facingLeft;
    if (!self->ext.ILLEGAL.u8[0x2F]) {
        sp40.x.val = other4->posX.val;
        sp40.y.val = other4->posY.val;
        if (self->facingLeft) {
            sp40.x.i.hi += 0x10;
        } else {
            sp40.x.i.hi -= 0x10;
        }
        var_s3 = self->ext.ILLEGAL.s16[2];
        func_pspeu_0923D928(&sp40, -0xC, var_s3, &sp40);
        func_pspeu_0923D928(&sp40, 0x18, var_s3, &sp38);
        sp6C.x = 0xC;
        sp6C.y = 0xC;
        prim = self->ext.prim;
        func_us_801D2424(&sp40, var_s3, &sp6C, &sp38, var_s3, &sp6C, prim);
        if (self->palette & 0x8000) {
            prim->clut = self->palette & 0xFFF;
        } else {
            prim->clut = 0x232;
        }
        prim->drawMode = 2;
        func_pspeu_0923D928(&sp40, 0x16, (var_s3 - 0x100), (Pos*)self);
    }
}

// This has a bunch of weird manipulation of prim fields using the LOW and
// similar macros. This indicates it may be yet another Primitive variant.
// Worthy of further research.
void func_us_801D1BF0(Entity* self) {
    s32 sp3C;
    s32 sp38;
    Entity* sp34;
    Primitive* prim;
    s16 angle;
    s32 temp_s2;
    s32 temp_s1;
    u32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    u32 var_s3;

    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 0x14;
        self->zPriority = 0x6F;
        sp3C = g_api_AllocPrimitives(PRIM_GT4, 10);
        if (sp3C == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = sp3C;
        prim = &g_PrimBuf[sp3C];
        self->ext.prim = prim;
        for(var_s6 = 0; var_s6 < 4; var_s6++){
            UnkPolyFunc2(prim);
            prim->tpage = 0x13;
            prim->clut = 0x232;
            prim->u0 = 0x1E;
            prim->v0 = 0x52;
            prim->u1 = 0x24;
            prim->v1 = 0x4E;
            prim->u2 = 0x22;
            prim->v2 = 0x58;
            prim->u3 = 0x28;
            prim->v3 = 0x54;
            LOH(prim->next->r2) = 6;
            LOH(prim->next->b2) = 6;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            prim->priority = 0x6F;
            prim->drawMode = 2;
            prim = prim->next;
            prim = prim->next;
        }
        UnkPolyFunc2(prim);
        prim->tpage = 0x13;
        prim->clut = 0x232;
        prim->u0 = 4;
        prim->v0 = 0x2B;
        prim->u1 = 0xB;
        prim->v1 = 0x2B;
        prim->u2 = 4;
        prim->v2 = 0x34;
        prim->u3 = 0xB;
        prim->v3 = 0x34;
        LOH(prim->next->r2) = 9;
        LOH(prim->next->b2) = 10;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        prim->priority = 0x6F;
        prim->drawMode = 2;
        // please konami, you're returning, there is no reason to increment the prim
        prim = prim->next;
        prim = prim->next;
        return;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
            return;
        }
        self->animCurFrame = 0;
        for(prim = self->ext.prim; prim != NULL; prim = prim->next) {
            prim->drawMode |= 8;
        }
        return;
    case 22:
        sp34 = self - 8;
        if (sp34->ext.ILLEGAL.u8[0x30]) {
            sp34 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (sp34 != NULL) {
                CreateEntityFromEntity(2U, self, sp34);
                sp34->params = 1;
                sp34->zPriority = self->zPriority;
            }
            DestroyEntity(self);
            return;
        }
    default:
        if (!self->step_s) {
            self->animCurFrame = 0x14;
            self->step_s += 1;
        }
        var_s4 = self->posX.val;
        if (self->facingLeft) {
            var_s4 -= FIX(4);
        } else {
            var_s4 += FIX(4);
        }
        var_s7 = self->posY.val;
        prim = self->ext.prim;
        for(var_s6 = 0; var_s6 < 5; var_s6++){
            var_s3 = prim->next->x1;
            var_s3 <<= 0x10;
            var_s3 += (u16)(prim->next->y1);
            var_s5 = LOW(prim->next->x0);
            var_s5 += FIX(1.5);
            temp_s2 = var_s3 - var_s4;
            temp_s1 = var_s5 - var_s7;
            angle = ratan2(-temp_s2, temp_s1);
            temp_s2 = temp_s2 >> 0x10;
            temp_s1 = temp_s1 >> 0x10;
            sp38 = (temp_s2 * temp_s2) + (temp_s1 * temp_s1);
            if (sp38 > 0x10) {
                temp_s2 = -(rsin(angle) * 4) << 4;
                temp_s1 = rcos(angle) * 4 << 4;
                var_s3 = var_s4 + temp_s2;
                var_s5 = var_s7 + temp_s1;
            }
            var_s4 = var_s3;
            var_s7 = var_s5;
            prim->next->x1 = (var_s4 >> 0x10);
            prim->next->y1 = var_s4 & 0xFFFF;
            LOW(prim->next->x0) = var_s7;
            UnkPrimHelper(prim);
            if (self->palette & 0x8000) {
                prim->clut = self->palette & 0xFFF;
            } else {
                prim->clut = 0x232;
            }
            prim->drawMode = 2;
            prim = prim->next;
            prim = prim->next;
        }
        return;
    }
}

void func_us_801D2038(Entity* self) {
    Collider sp1C;
    s32 xVar, yVar;
    Entity* player;

    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 0xC;
        self->zPriority = 0x73;
        break;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->animCurFrame = 0;
        }
        break;
    case 22:
        self->velocityY = 0x10000;
        MoveEntity();
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 6;
        g_api.CheckCollision(xVar, yVar, &sp1C, 0);
        if (sp1C.effects & 1) {
            DestroyEntity(self);
            return;
        }
    default:
        self->animCurFrame = 0xC;
        if (GetPlayerCollisionWith(self, 0x10U, 8U, 4U) != 0) {
            xVar = (g_Tilemap.scrollX.val + self->posX.val) - self->ext.ILLEGAL.u32[1];
            // unused but let's calculate it just for fun
            yVar = (g_Tilemap.scrollY.val + self->posY.val) - self->ext.ILLEGAL.u32[2];
            player = &PLAYER;
            player->posX.val += xVar;
            player->posY.i.hi += 1;
        }
        break;
    }
    self->ext.ILLEGAL.u32[1] = g_Tilemap.scrollX.val + self->posX.val;
    self->ext.ILLEGAL.u32[2] = g_Tilemap.scrollY.val + self->posY.val;
}

extern AnimateEntityFrame D_pspeu_0925EF40[];

void func_us_801D21C8(Entity* self) {
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->zPriority = 0x72;
        self->palette = 0x8235;
        self->velocityY = -0xC000;
        break;
    case 1:
        MoveEntity();
        if (AnimateEntity(D_pspeu_0925EF40, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2264);
