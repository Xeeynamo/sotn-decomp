// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

extern EInit g_EInitGorgon;
extern EInit g_EInitGorgonHead;
extern EInit g_EInitGorgonAttack;

static u8 UV_data_1[][8] = {
    {121, 86, 127, 92, 111, 97, 123, 105},
    {72, 95, 81, 88, 79, 103, 87, 96},
    {85, 101, 95, 113, 70, 120, 84, 130},
    {85, 101, 95, 113, 70, 120, 84, 130},
    {72, 95, 81, 88, 79, 103, 87, 96},
    {121, 86, 127, 92, 111, 97, 123, 105}};
static u8 UV_data_2[][8] = {{69, 64, 77, 72, 56, 79, 63, 87},
                            {88, 83, 103, 83, 88, 100, 103, 100},
                            {69, 64, 77, 72, 56, 79, 63, 87},
                            {88, 83, 103, 83, 88, 100, 103, 100}};

static AnimateEntityFrame anim_turnaround[] = {
    {3, 38}, {3, 37}, {3, 37}, {3, 38}, POSE_END};

static AnimateEntityFrame anim_mouthblast[] = {
    {7, 11}, {7, 23}, {7, 24}, {1, 25}, {1, 24}, {1, 25}, POSE_END};
static AnimateEntityFrame anim_end_mouthblast[] = {
    {1, 25}, {7, 24}, {7, 23}, {7, 11}, POSE_END};
static AnimateEntityFrame anim_head_dying[] = {
    {2, 11}, {2, 23}, {2, 24}, {2, 25},
    {2, 24}, {2, 23}, {2, 11}, POSE_LOOP(0)};
static AnimateEntityFrame anim_snortpuff[] = {
    {3, 26}, {2, 27}, {2, 28}, {3, 29}, {3, 30},
    {4, 31}, {5, 32}, {4, 33}, {4, 34}, POSE_END};

// This could be a file split issue
#ifdef VERSION_US
static s32 fakepad = 0;
#endif

// These first two are copied from the Plate Lord?
static void func_pspeu_0923D928(Pos* src, s32 speed, s16 angle, Pos* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x.val += -(speed * rsin(angle) * 16);
    dst->y.val += speed * rcos(angle) * 16;
}

static void func_us_801D2424(Pos* arg0, s16 arg1, Point16* arg2, Pos* arg3,
                             s16 arg4, Point16* arg5, Primitive* prim) {
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

static Primitive* func_pspeu_0923DD78(
    Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
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
    prim->drawMode = DRAW_UNK02;
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
    prim->drawMode = DRAW_UNK02;
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
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    return prim;
}

static Primitive* func_pspeu_0923DF88(
    Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
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
    prim->drawMode = DRAW_UNK02;
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
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    angle = *arg2++;
    func_pspeu_0923D928(&sp18, -3, angle, &sp18);
    func_pspeu_0923D928(&sp18, 14, angle, ent2);
    sp2C.x = 6;
    sp2C.y = 6;
    sp28.x = 10;
    sp28.y = 8;
    func_us_801D2424(&sp18, angle, &sp2C, ent2, angle, &sp28, prim);
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    return prim;
}

static Primitive* func_pspeu_0923E1A0(
    Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
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
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    func_pspeu_0923D928(&sp10, -4, angle, &sp10);
    angle = *arg2++;
    func_pspeu_0923D928(&sp10, 17, angle, ent2);
    sp2C.x = 7;
    sp2C.y = 9;
    sp28.x = 6;
    sp28.y = 10;
    func_us_801D2424(&sp10, angle, &sp2C, ent2, angle, &sp28, prim);
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    return prim;
}

static Primitive* func_pspeu_0923E300(
    Pos* ent1, Pos* ent2, s16* arg2, Primitive* prim) {
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
    prim->drawMode = DRAW_UNK02;
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
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;
    return prim;
}

#include "../step_towards.h"

static s32 func_pspeu_0923E6D0(
    Entity* arg0, s16* arg1, Entity* arg2, s16* arg3, u16* arg4) {
    s32 var_s2;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s1;
    s16 var_s0;

    var_s2 = g_CurrentEntity->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
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
    if (arg2->ext.gorgon.unk80 && (var_s3 < var_s4) && (var_s5 < -var_s3)) {
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

static s32 func_pspeu_0923E920(
    Entity* arg0, s16* arg1, Entity* arg2, s16* arg3, u16* arg4) {
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
    if ((arg2->ext.gorgon.unk80) && (var_s0 < var_s3) && (var_s2 < -var_s0)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.gorgon.unkAA) {
    case 0:
        StepTowards(arg3 + 1, -0x240, var_s1);
        if (StepTowards(arg3, 0x1C0, var_s1) != 0) {
            g_CurrentEntity->ext.gorgon.unkAA += 1;
        }
        break;
    case 1:
        if (StepTowards(arg3 + 1, *arg3, var_s1) != 0) {
            g_CurrentEntity->ext.gorgon.unkAA += 1;
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

static s32 func_pspeu_0923EBE8(
    Entity* arg0, s16* arg1, Entity* arg2, s16* arg3) {
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
    if ((arg2->ext.gorgon.unk80) && (var_s1 < -8) && (var_s2 > 8)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.gorgon.unkAA) {
    case 0:
        if (var_s1 > -8) {
            *arg3 -= 0x10;
            var_s0 = *arg3 - 0x340;
            StepTowards(arg3 + 1, var_s0 - 0x140, 0x40);
            StepTowards(arg3 + 2, var_s0 + 0x140, 0x40);
        } else {
            g_CurrentEntity->ext.gorgon.unkAA += 1;
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

static s32 func_pspeu_0923EE78(
    Entity* arg0, s16* arg1, Entity* arg2, s16* arg3) {
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
    if (arg2->ext.gorgon.unk80 && (var_s0 < -8) && (var_s2 > 8)) {
        return 1;
    }
    switch (g_CurrentEntity->ext.gorgon.unkAA) {
    case 0:
        StepTowards(arg3 + 1, -0x280, 0x20);
        if (StepTowards(arg3, -0xC0, 0x18)) {
            g_CurrentEntity->ext.gorgon.unkAA += 1;
        }
        break;
    case 1:
        if (StepTowards(arg3 + 1, *arg3, 0x20)) {
            g_CurrentEntity->ext.gorgon.unkAA += 1;
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

static s32 func_pspeu_0923F088(Entity* self, s32 arg1) {
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
    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        g_api.CheckCollision(var_s3, var_s2, &sp2C, 0);
        if (var_s0 != 0) {
            if (!(sp2C.effects & EFFECT_SOLID)) {
                var_s1 |= 2;
            }
        } else if (sp2C.effects & EFFECT_SOLID) {
            var_s1 |= 1;
        }
        var_s2 += 4;
    }
    return var_s1;
}

static void func_pspeu_0923F198(s32 count) {
    s32 i;
    Primitive* prim;

    prim = g_CurrentEntity->ext.gorgon.prim;
    for (i = 0; i < count; i++) {
        if (g_CurrentEntity->ext.gorgon.unkA8 == 0) {
            prim->clut = 0x232;
            prim->priority = 0x72;
        } else {
            prim->clut = 0x233;
            prim->priority = 0x6E;
        }
        if (g_CurrentEntity->palette & PAL_UNK_FLAG) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        }
        prim = prim->next;
    }
    for (i = 0; i < count; i++) {
        if (g_CurrentEntity->ext.gorgon.unkA8 == 0) {
            prim->clut = 0x233;
            prim->priority = 0x6E;
        } else {
            prim->clut = 0x232;
            prim->priority = 0x72;
        }
        if (g_CurrentEntity->palette & PAL_UNK_FLAG) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        }
        prim = prim->next;
    }
}

static void func_pspeu_0923F300(s32 newStep) {
    Entity* ent;
    s32 i;

    for (ent = g_CurrentEntity, i = 0; i < 10; i++, ent++) {
        ent->step = newStep;
        ent->step_s = 0;
        ent->ext.gorgon.unkAA = 0;
    }
}

void EntityGorgon(Entity* self) {
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 i;
    Entity* other_s0;
    Entity* other_s1;
    s32 stackpad[6];

    if ((self->flags & FLAG_DEAD) && (self->step < 0x16)) {
        for (other_s0 = self, i = 0; i < 10; i++, other_s0++) {
            other_s0->hitboxState = 0;
        }
        if ((self->step) != 0x13) {
            func_pspeu_0923F300(0x15);
            self->step = 0x16;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        self->zPriority = 0x70;
        self->animCurFrame = 10;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        other_s1 = self + 1;
        CreateEntityFromEntity(E_GORGON_FRONT, self, other_s1);
        other_s1 = self + 4;
        CreateEntityFromEntity(E_GORGON_REAR, self, other_s1);
        other_s1 = self + 7;
        CreateEntityFromEntity(E_GORGON_HEAD, self, other_s1);
        other_s1 = self + 9;
        CreateEntityFromEntity(E_GORGON_SADDLE, self, other_s1);
        other_s1 = self + 8;
        CreateEntityFromEntity(E_GORGON_TAIL, self, other_s1);
        self->ext.gorgon.unkA4 = 2;
        break;
    case 1:
        if (!--self->ext.gorgon.unkA4) {
            for (other_s0 = self, i = 0; i < 9; i++, other_s0++) {
                other_s0->parent = self;
                other_s0->nextPart = other_s0 + 1;
            }
            other_s0->parent = self;
            other_s0->nextPart = self;
            self->parent = NULL;
            func_pspeu_0923F300(0x10);
        }
        break;
    case 17:
    case 16:
        if (!self->step_s) {
            self->ext.gorgon.unkA4 = 0x40;
            self->step_s++;
        }
        other_s1 = self + 4;
        if (other_s1->ext.gorgon.unkA8 == 0) {
            other_s1 = other_s1 + 1;
        } else {
            other_s1 = other_s1 + 2;
        }
        var_s4 = func_pspeu_0923F088(other_s1, 0);
        if (var_s4 != 0) {
            if (self->ext.gorgon.unkA4) {
                self->ext.gorgon.unkA9 = 0x13;
                func_pspeu_0923F300(0x15);
            }
            self->ext.gorgon.unkA4 = 0x20;
        }
        if (self->ext.gorgon.unkA4) {
            self->ext.gorgon.unkA4--;
            break;
        } else if (GetDistanceToPlayerY() < 0x40) {
            other_s0 = &PLAYER;
            var_s3 = self->posX.i.hi - other_s0->posX.i.hi;
            if (self->facingLeft) {
                var_s3 = -var_s3;
            }
            if ((u16)var_s3 > 0xFFB0) {
                var_s4 = 1;
                self->ext.gorgon.unkA4 = 0x10;
            }
            if ((var_s4 == 0) && (var_s3 > 0x60) && (self->step != 0x11)) {
                func_pspeu_0923F300(0x11);
            }
            if (!self->ext.gorgon.unkA0) {
                if (var_s3 < 0x50U) {
                    self->ext.gorgon.unkA0 = 0x80;
                    SetStep(0x14U);
                    break;
                }
            } else {
                if (self->ext.gorgon.unkA0 < 0) {
                    self->ext.gorgon.unkA0 = 0x80;
                } else {
                    self->ext.gorgon.unkA0--;
                }
            }
        }
        if (var_s4 != 0) {
            self->ext.gorgon.unkA4 = 0x20;
            self->ext.gorgon.unkA9 = 0x13;
            func_pspeu_0923F300(0x15);
        }
        if (self->hitParams) {
            self->ext.gorgon.unkA4 = 0x40;
            func_pspeu_0923F300(0x12);
        }

        break;
    case 18:
        other_s1 = self + 1;
        if (other_s1->ext.gorgon.unkA8 == 0) {
            other_s1 = other_s1 + 1;
        } else {
            other_s1 = other_s1 + 2;
        }
        var_s4 = func_pspeu_0923F088(other_s1, 1);
        if (!--self->ext.gorgon.unkA4) {
            var_s4 = 1;
        }
        if (var_s4 != 0) {
            self->ext.gorgon.unkA4 = 0x18;
            self->ext.gorgon.unkA9 = 0x10;
            func_pspeu_0923F300(0x15);
        }
        break;
    case 19:
        switch (self->step_s) {
        case 0:
            other_s1 = self + 1;
            if (other_s1->ext.gorgon.unkA8 == 0) {
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
            self->ext.gorgon.unkAB = 1;
            self->poseTimer = 0;
            self->pose = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_turnaround, self) == 0) {
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
        case 2:
            self->animCurFrame = 10;
            other_s1 = self + 1;
            if (other_s1->ext.gorgon.unkA8 == 0) {
                other_s1 = other_s1 + 1;
            } else {
                other_s1 = other_s1 + 2;
            }
            other_s1->posX.i.hi = self->posX.i.hi;
            self->ext.gorgon.unkAB = 0;
            self->ext.gorgon.unkA4 = 0x20;
            self->ext.gorgon.unkA9 = 0x10;
            func_pspeu_0923F300(0x15);
            break;
        }
        break;
    case 20:
        switch (self->step_s) {
        case 0:
            other_s0 = self + 4;
            if (other_s0->ext.gorgon.unkAE) {
                other_s0->step = 0x14;
                func_pspeu_0923F300(0x14);
                self->step_s = 1;
            }
            break;
        case 1:
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
    case 21:
        if (!--self->ext.gorgon.unkA4) {
            if (self->ext.gorgon.unkA9) {
                func_pspeu_0923F300(self->ext.gorgon.unkA9);
            } else {
                func_pspeu_0923F300(0x10);
            }
        }
        break;
    case 22:
        switch (self->step_s) {
        case 0:
            other_s0 = self + 7;
            other_s0->step = 0x16;
            self->ext.gorgon.unkA4 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!(self->ext.gorgon.unkA4 & 7)) {
                PlaySfxPositional(SFX_EXPLODE_B);
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
                    CreateEntityFromCurrentEntity(E_EXPLOSION, other_s1);
                    other_s1->params = 1;
                    other_s1->zPriority = ((self->zPriority) + 2);
                    other_s1->posX.i.hi = var_s3;
                    other_s1->posY.i.hi = var_s5;
                }
            }
            if (!--self->ext.gorgon.unkA4) {
                func_pspeu_0923F300(0x16);
                self->step_s = 2;
            }
            break;
        case 2:
            other_s0 = self + 7;
            if (!other_s0->entityId) {
                self->step_s++;
            }
            break;
        case 3:
            PlaySfxPositional(SFX_STUTTER_EXPLODE_LOW);
            self->ext.gorgon.unkAC = 1;
            self->step_s++;
            break;
        case 4:
            other_s1 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other_s1 != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other_s1);
                other_s1->params = 3;
                other_s1->zPriority = self->zPriority;
            }
            self->ext.gorgon.unkA4 = 8;
            self->step_s++;
            break;
        case 5:
            if (!--self->ext.gorgon.unkA4) {
                self->animCurFrame = 0;
                for (other_s0 = self, i = 0; i < 9; i++, other_s0++) {
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
    if (self->ext.gorgon.unkAB) {
        1;
    }
}

void EntityGorgonFront(Entity* self) {
    s16 sp6E;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    Collider sp3C;
    s32 stackpad[2];
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
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 9;
        self->zPriority = 0x70;
        self->zPriority += ((self->params) * 4);
        self->hitboxWidth = 8;
        self->hitboxHeight = 10;
        self->hitboxOffX = -8;
        self->hitboxOffY = 8;
        other = self + 1;
        CreateEntityFromEntity(E_GORGON_FOOT, self, other);
        other->params = 0;
        other = self + 2;
        CreateEntityFromEntity(E_GORGON_FOOT, self, other);
        other->params = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.gorgon.prim = prim;
        var_s2 = (u8*)UV_data_1;
        for (var_s5 = 0; var_s5 < 6; var_s5++) {
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
        self->ext.gorgon.unk80 = 0x180;
        self->ext.gorgon.unk82 = -0x80;
        self->ext.gorgon.unk84 = 0x100;
        self->ext.gorgon.unk86 = 0x180;
        self->ext.gorgon.unk88 = -0x80U;
        self->ext.gorgon.unk8A = 0x100;
        self->step = 0x15;
        break;
    case 17:
    case 16:
    case 18:
    case 21:
    case 20:
        self->ext.gorgon.unkAB = 0;
        if (self->ext.gorgon.unkA8 == 0) {
            other7 = self + 1;
            var_s4 = &self->ext.gorgon.unk80;
            other6 = self + 2;
            var_s3 = &self->ext.gorgon.unk86;
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.gorgon.unk86;
            other6 = self + 1;
            var_s3 = &self->ext.gorgon.unk80;
        }
        switch (self->step) {
        case 17:
            sp38[0] = 0xA;
            sp38[1] = 0x10;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, sp38);
            break;
        case 16:
            sp38[0] = 8;
            sp38[1] = 8;
            sp68 = func_pspeu_0923E6D0(other7, var_s4, other6, var_s3, sp38);
            break;
        case 18:
            sp68 = func_pspeu_0923EBE8(other7, var_s4, other6, var_s3);
            break;
        case 20:
        case 21:
            break;
        }
        prim = self->ext.gorgon.prim;
        prim = func_pspeu_0923DD78((Pos*)other7, (Pos*)self, var_s4 + 2, prim);
        func_pspeu_0923DF88((Pos*)self, (Pos*)other6, var_s3, prim);
        func_pspeu_0923F198(3);
        if (sp68 != 0) {
            self->ext.gorgon.unkAE = 1;
            self->ext.gorgon.unkAA = 0;
            self->ext.gorgon.unkA8 ^= 1;
        } else {
            self->ext.gorgon.unkAE = 0;
        }
        break;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.gorgon.unkAB = 1;
            for (prim = self->ext.gorgon.prim, self->animCurFrame = 0;
                 prim != NULL; prim = prim->next) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        break;
    case 22:
        if (self->ext.gorgon.unkA8 == 0) {
            other7 = self + 1;
            var_s4 = &self->ext.gorgon.unk80;
            other6 = self + 2;
            var_s3 = &self->ext.gorgon.unk86;
        } else {
            other7 = self + 2;
            var_s4 = &self->ext.gorgon.unk86;
            other6 = self + 1;
            var_s3 = &self->ext.gorgon.unk80;
        }
        switch (self->step_s) {
        case 0:
            self->ext.gorgon.unkAB = 0;
            StepTowards(var_s4 + 1, -0x600, 0x30);
            StepTowards(var_s4 + 2, -0x400, 0x30);
            StepTowards(var_s3, 0x400, 0x50);
            StepTowards(var_s3 + 1, -0x300, 0x38);
            StepTowards(var_s3 + 2, -0x500, 0x38);
            prim = self->ext.gorgon.prim;
            prim = (Primitive*)func_pspeu_0923DD78(
                (Pos*)other7, (Pos*)self, var_s4 + 2, prim);
            func_pspeu_0923DF88((Pos*)self, (Pos*)other6, var_s3, prim);
            func_pspeu_0923F198(3);
            sp64 = self->posX.i.hi;
            sp60 = self->posY.i.hi + 0x18;
            g_api.CheckCollision(sp64, sp60, &sp3C, 0);
            if (sp3C.effects & EFFECT_SOLID) {
                g_api.func_80102CD8(1);
                PlaySfxPositional(SFX_EXPLODE_A);
                self->step_s += 1;
            }
            break;
        case 1:
            other = self - 1;
            if (other->ext.gorgon.unkAC) {
                self->ext.gorgon.unkAC = 1;
                self->step_s += 1;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 3;
                other->zPriority = self->zPriority;
            }
            self->step_s += 1;
            break;
        case 3:
            for (prim = self->ext.gorgon.prim; prim != NULL;) {
                if (prim->drawMode & DRAW_HIDE) {
                    prim = prim->next;
                } else {
                    other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
                    if (other != NULL) {
                        CreateEntityFromCurrentEntity(E_EXPLOSION, other);
                        other->posX.i.hi = prim->x0;
                        other->posY.i.hi = prim->y0;
                        other->params = 1;
                    }
                    prim->drawMode = DRAW_HIDE;
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
    if (!self->ext.gorgon.unkAB) {
        if ((self->step == 0x10) || (self->step == 0x11)) {
            sp6E = 0x360;
        } else {
            sp6E = 0x330;
        }
        other = self + 3;
        func_pspeu_0923D928((Pos*)self, 0x22, sp6E, (Pos*)other);
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

void EntityGorgonRear(Entity* self) {
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
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 13;
        self->drawFlags = ENTITY_ROTATE;
        self->zPriority = 0x73;
        other = self + 1;
        CreateEntityFromEntity(E_GORGON_FOOT, self, other);
        other->params = 0x10;
        other = self + 2;
        CreateEntityFromEntity(E_GORGON_FOOT, self, other);
        other->params = 0x11;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.gorgon.prim = prim;
        var_s2 = (u8*)UV_data_2;
        while (prim != NULL) {
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
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.gorgon.unk80 = 0;
        self->ext.gorgon.unk82 = 0x40;
        self->step = 0x15;
        break;
    case 17:
    case 16:
    case 18:
        if (self->ext.gorgon.unkA8 == 0) {
            other3 = self + 1;
            var_s4 = &self->ext.gorgon.unk80;
            other7 = self + 2;
            var_s6 = &self->ext.gorgon.unk84;
        } else {
            other3 = self + 2;
            var_s4 = &self->ext.gorgon.unk84;
            other7 = self + 1;
            var_s6 = &self->ext.gorgon.unk80;
        }
        switch (self->step) {
        case 17:
            sp38[0] = 0xA;
            sp38[1] = 0x40;
            sp68 = func_pspeu_0923E920(other3, var_s4, other7, var_s6, sp38);
            break;
        case 16:
            sp38[0] = 8;
            sp38[1] = 32;
            sp68 = func_pspeu_0923E920(other3, var_s4, other7, var_s6, sp38);
            break;
        case 18:
            sp68 = func_pspeu_0923EE78(other3, var_s4, other7, var_s6);
            break;
        }
        prim = self->ext.gorgon.prim;
        prim = func_pspeu_0923E300((Pos*)self, (Pos*)other3, var_s4, prim);
        func_pspeu_0923E1A0((Pos*)self, (Pos*)other7, var_s6, prim);
        func_pspeu_0923F198(2);
        if (sp68 != 0) {
            self->ext.gorgon.unkAE = 1;
            self->ext.gorgon.unkA8 ^= 1;
            self->ext.gorgon.unkAA = 0;
        } else {
            self->ext.gorgon.unkAE = 0;
        }
        self->rotate = self->ext.gorgon.unk80 / 2;
        break;
    case 20:
    case 21:
        self->ext.gorgon.unkAB = 0;
        if (self->ext.gorgon.unkA8 == 0) {
            other3 = self + 1;
            var_s4 = &self->ext.gorgon.unk80;
            other7 = self + 2;
            var_s6 = &self->ext.gorgon.unk84;
        } else {
            other3 = self + 2;
            var_s4 = &self->ext.gorgon.unk84;
            other7 = self + 1;
            var_s6 = &self->ext.gorgon.unk80;
        }
        prim = self->ext.gorgon.prim;
        if (self->step == 21) {
            prim = func_pspeu_0923E1A0((Pos*)self, (Pos*)other3, var_s4, prim);
            func_pspeu_0923E1A0((Pos*)self, (Pos*)other7, var_s6, prim);
        } else {
            prim = func_pspeu_0923E300((Pos*)self, (Pos*)other3, var_s4, prim);
            func_pspeu_0923E300((Pos*)self, (Pos*)other7, var_s6, prim);
        }
        func_pspeu_0923F198(2);
        break;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.gorgon.unkAB = 1;
            self->animCurFrame = 0;
            for (prim = self->ext.gorgon.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        break;
    case 22:
        switch (self->step_s) {
        case 0:
            other3 = self + 1;
            var_s4 = &self->ext.gorgon.unk80;
            prim = self->ext.gorgon.prim;
            for (var_s5 = 0; var_s5 < 2; var_s5++) {
                if (other3->ext.gorgon.unk80) {
                    prim = func_pspeu_0923E300(
                        (Pos*)self, (Pos*)other3, var_s4, prim);
                } else {
                    prim = func_pspeu_0923E1A0(
                        (Pos*)self, (Pos*)other3, var_s4, prim);
                }
                other3 = self + 2;
                var_s4 = &self->ext.gorgon.unk84;
            }
            func_pspeu_0923F198(2);
            sp64 = self->posX.i.hi;
            sp60 = self->posY.i.hi + 0x18;
            g_api.CheckCollision(sp64, sp60, &sp3C, 0);
            if (sp3C.effects & EFFECT_SOLID) {
                other = self - 3;
                other->ext.gorgon.unkAB = 1;
                PlaySfxPositional(SFX_EXPLODE_FAST_B);
                self->step_s += 1;
            }
            break;
        case 1:
            other = self - 4;
            if (other->ext.gorgon.unkAC) {
                self->ext.gorgon.unkAC = 1;
                self->step_s += 1;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 3;
                other->zPriority = self->zPriority;
            }
            self->ext.gorgon.unkAB = 1;
            self->step_s += 1;
            break;
        case 3:
            for (prim = self->ext.gorgon.prim; prim != NULL;) {
                if (prim->drawMode & DRAW_HIDE) {
                    prim = prim->next;
                } else {
                    other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
                    if (other != NULL) {
                        CreateEntityFromCurrentEntity(E_EXPLOSION, other);
                        other->posX.i.hi = prim->x0;
                        other->posY.i.hi = prim->y0;
                        other->params = 1;
                    }
                    prim->drawMode = DRAW_HIDE;
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
    if (!self->ext.gorgon.unkAB) {
        other = self - 4;
        other->posX.i.hi = self->posX.i.hi;
        other->posY.i.hi = self->posY.i.hi;
        other = self + 5;
        other->posX.i.hi = self->posX.i.hi + 0;
        other->posY.i.hi = self->posY.i.hi - 13;
    }
}

void EntityGorgonFoot(Entity* self) {
    Collider sp1C;
    Entity* other;
    s32 xVar, yVar;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 16;
        if (self->params & 1) {
            self->zPriority = 0x6D;
            self->palette = PAL_FLAG(0x234);
        } else {
            self->zPriority = 0x71;
        }
        self->hitboxWidth = 4;
        self->hitboxHeight = 6;
        return;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
            return;
        }
        self->animCurFrame = 0;
        return;
    case 22:
        switch (self->step_s) {
        case 1:
            other = self - 1;
            if (other->ext.gorgon.unkAC) {
                self->ext.gorgon.unkAC = 1;
                self->step_s += 1;
            }
            break;
        case 2:
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
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
        case 3:
            break;
        }
    }
    if (!self->step_s) {
        if (self->params & 1) {
            self->zPriority = 0x6D;
            self->animCurFrame = 4;
        } else {
            self->zPriority = 0x71;
            self->animCurFrame = 16;
        }
        self->step_s += 1;
    }
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi + 6;
    g_api.CheckCollision(xVar, yVar, &sp1C, 0);
    if (sp1C.effects & EFFECT_SOLID) {
        self->posY.i.hi += sp1C.unk18;
        self->rotate = 0;
        self->ext.gorgon.unk80 = 1;
        if (!self->ext.gorgon.unkAD) {
            PlaySfxPositional(SFX_STOMP_HARD_B);
            self->ext.gorgon.unkAD = 1;
        }
    } else {
        self->rotate = ROT(-22.5);
        self->ext.gorgon.unk80 = 0;
        self->ext.gorgon.unkAD = 0;
    }
}

void EntityGorgonHead(Entity* self) {
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

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgonHead);
        self->animCurFrame = 11;
        self->zPriority = 0x70;
        self->hitboxWidth = 7;
        self->hitboxHeight = 7;
        self->hitboxOffX = -3;
        self->drawFlags |= ENTITY_ROTATE;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.gorgon.prim = prim;
        prim->tpage = 0x13;
        prim->clut = 0x232;
        prim->u0 = prim->u1 = 0x80;
        prim->u2 = prim->u3 = 0x60;
        prim->v0 = prim->v2 = 0x68;
        prim->v1 = prim->v3 = 0x80;
        prim->priority = 0x6F;
        prim->drawMode = DRAW_UNK02;
        self->ext.gorgon.unk80 = 0x400;
        break;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
        } else {
            self->ext.gorgon.unkAB = 1;
            self->animCurFrame = 0;
            prim = self->ext.gorgon.prim;
            prim->drawMode |= DRAW_HIDE;
        }
        break;
    case 20:
        switch (self->step_s) {
        case 0:
            temp_s2 = StepTowards(&self->ext.gorgon.unk80, 0x600, 0x10);
            temp_s2 += StepTowards(&self->rotate, 0x300, 0x20);
            if (temp_s2 == 2) {
                self->step_s += 1;
            }
            break;
        case 1:
            temp_s2 = StepTowards(&self->ext.gorgon.unk80, 0x500, 0x18);
            temp_s2 = temp_s2 + StepTowards(&self->rotate, 0x100, 0x30);
            if ((AnimateEntity(anim_mouthblast, self) == 0) && (temp_s2 == 2)) {
                self->ext.gorgon.unkA4 = 0x40;
                PlaySfxPositional(SFX_GORGON_ATTACK);
                self->step_s += 1;
            }
            break;
        case 2:
            if (!(g_Timer & 3)) {
                other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_GORGON_ATTACK, self, other);
                    other->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        other->posX.i.hi += 0xC;
                    } else {
                        other->posX.i.hi -= 0xC;
                    }
                    other->posY.i.hi += 2;
                }
            }
            if (!--self->ext.gorgon.unkA4) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s += 1;
            }
            break;
        case 3:
            temp_s2 = StepTowards(&self->ext.gorgon.unk80, 0x400, 0x10);
            temp_s2 = temp_s2 + StepTowards(&self->rotate, 0, 0x20);
            if ((AnimateEntity(anim_end_mouthblast, self) == 0) &&
                (temp_s2 == 2)) {
                self->step = 0x15;
            }
            break;
        }
        break;
    case 17:
    case 16:
    case 18:
        switch (self->step_s) {
        case 0:
            if (StepTowards(&self->ext.gorgon.unk80, 0x500, 8) != 0) {
                self->step_s += 1;
            }
            break;
        default:
            if (StepTowards(&self->ext.gorgon.unk80, 0x400, 8) != 0) {
                self->step_s = 0;
            }
        }
    default:
        self->ext.gorgon.unkAB = 0;
        self->animCurFrame = 11;
        if (!(g_Timer & 0x7F)) {
            other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
            if (other != NULL) {
                PlaySfxPositional(SFX_GORGON_SNORT);
                CreateEntityFromEntity(E_GORGON_SNORT, self, other);
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
    case 22:
        switch (self->step_s) {
        case 0:
            StepTowards(&self->ext.gorgon.unk80, 0x400, 8);
            StepTowards(&self->rotate, 0x200, 0x10);
            AnimateEntity(anim_head_dying, self);
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi + 8;
            g_api.CheckCollision(xVar, yVar, &sp48, 0);
            if (sp48.effects & EFFECT_SOLID) {
                self->ext.gorgon.unkAB = 1;
                PlaySfxPositional(SFX_EXPLODE_FAST_B);
                self->step_s += 1;
            }
            break;
        case 1:
            other = AllocEntity(&g_Entities[0xE0], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 3;
            }
            DestroyEntity(self);
            return;
        }
        break;
    }
    other4 = self - 7;
    self->facingLeft = other4->facingLeft;
    if (!self->ext.gorgon.unkAB) {
        sp40.x.val = other4->posX.val;
        sp40.y.val = other4->posY.val;
        if (self->facingLeft) {
            sp40.x.i.hi += 0x10;
        } else {
            sp40.x.i.hi -= 0x10;
        }
        var_s3 = self->ext.gorgon.unk80;
        func_pspeu_0923D928(&sp40, -0xC, var_s3, &sp40);
        func_pspeu_0923D928(&sp40, 0x18, var_s3, &sp38);
        sp6C.x = 0xC;
        sp6C.y = 0xC;
        prim = self->ext.gorgon.prim;
        func_us_801D2424(&sp40, var_s3, &sp6C, &sp38, var_s3, &sp6C, prim);
        if (self->palette & PAL_UNK_FLAG) {
            prim->clut = self->palette & 0xFFF;
        } else {
            prim->clut = 0x232;
        }
        prim->drawMode = DRAW_UNK02;
        func_pspeu_0923D928(&sp40, 0x16, (var_s3 - 0x100), (Pos*)self);
    }
}

// This has a bunch of weird manipulation of prim fields using the LOW and
// similar macros. This indicates it may be yet another Primitive variant.
// Worthy of further research.
void EntityGorgonTail(Entity* self) {
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

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->animCurFrame = 20;
        self->zPriority = 0x6F;
        sp3C = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (sp3C == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = sp3C;
        prim = &g_PrimBuf[sp3C];
        self->ext.gorgon.prim = prim;
        for (var_s6 = 0; var_s6 < 4; var_s6++) {
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
            prim->drawMode = DRAW_UNK02;
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
        prim->drawMode = DRAW_UNK02;
        // please konami, you're returning, there is no reason to increment the
        // prim
        prim = prim->next;
        prim = prim->next;
        return;
    case 19:
        if (!self->step_s) {
            self->step_s += 1;
            return;
        }
        self->animCurFrame = 0;
        for (prim = self->ext.gorgon.prim; prim != NULL; prim = prim->next) {
            prim->drawMode |= DRAW_HIDE;
        }
        return;
    case 22:
        sp34 = self - 8;
        if (sp34->ext.gorgon.unkAC) {
            sp34 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (sp34 != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, sp34);
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
        prim = self->ext.gorgon.prim;
        for (var_s6 = 0; var_s6 < 5; var_s6++) {
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
            if (self->palette & PAL_UNK_FLAG) {
                prim->clut = self->palette & 0xFFF;
            } else {
                prim->clut = 0x232;
            }
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            prim = prim->next;
        }
        return;
    }
}

// Uses the ext struct weird, I'm doing f32 casts for now until we understand
// this whole gorgon file better.
void EntityGorgonSaddle(Entity* self) {
    Collider sp1C;
    s32 xVar, yVar;
    Entity* player;

    switch (self->step) {
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
        self->velocityY = FIX(1.0);
        MoveEntity();
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 6;
        g_api.CheckCollision(xVar, yVar, &sp1C, 0);
        if (sp1C.effects & EFFECT_SOLID) {
            DestroyEntity(self);
            return;
        }
    default:
        self->animCurFrame = 0xC;
        if (GetPlayerCollisionWith(self, 0x10, 8, 4U) != 0) {
            xVar = (g_Tilemap.scrollX.val + self->posX.val) -
                   F(self->ext.gorgon.unk80).val;
            // unused but let's calculate it just for fun
            yVar = (g_Tilemap.scrollY.val + self->posY.val) -
                   F(self->ext.gorgon.unk84).val;
            player = &PLAYER;
            player->posX.val += xVar;
            player->posY.i.hi += 1;
        }
        break;
    }
    F(self->ext.gorgon.unk80).val = g_Tilemap.scrollX.val + self->posX.val;
    F(self->ext.gorgon.unk84).val = g_Tilemap.scrollY.val + self->posY.val;
}

void EntityGorgonSnort(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgon);
        self->zPriority = 0x72;
        self->palette = PAL_FLAG(0x235);
        self->velocityY = FIX(-0.75);
        break;
    case 1:
        MoveEntity();
        if (AnimateEntity(anim_snortpuff, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityGorgonAttack(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGorgonAttack);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->velocityX = FIX(-1.5);
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = (s32)primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.gorgon.prim = prim;
        UnkPolyFunc2(prim);
        // This is the DRA tpage that includes "Now loading", numbers, and
        // status texts like "Stone", "Guard", and "Critical".
        // There is a circular blur at the listed UV coordinates
        prim->tpage = 0x1A;
        prim->clut = 0x19C;

        prim->u0 = prim->u2 = 0xE0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x5F;
        LOH(prim->next->r2) = 0x20;
        LOH(prim->next->b2) = 0x20;
        prim->next->b3 = 0xE0;
        LOH(prim->next->u1) = 0;
        prim->p3 |= 0x10;
        prim->next->x2 = prim->next->y2 = 0x300;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
    case 1:
        MoveEntity();
        prim = self->ext.gorgon.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        prim->next->x2 += 0x60;
        prim->next->y2 = prim->next->x2;
        prim->next->b3 -= 6;
        LOH(prim->next->tpage) += 0x20;
        if (prim->next->b3 < 0x40) {
            prim->next->b3 = 0x40;
        }
        UnkPrimHelper(prim);
        if (prim->next->x2 > 0xE00) {
            DestroyEntity(self);
        }
    }
}
