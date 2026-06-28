// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

extern EInit g_EInitNovaSkeleton;
extern EInit D_us_801809A4;

// sensors
extern s16 D_pspeu_0925A540[] = {0, 20, 0, 4, 8, -4, -16, 0};
extern s16 D_pspeu_0925A550[] = {0, 20, 12, 0};
// animations
extern u8 D_pspeu_0925A558[] = {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0};
extern u8 D_pspeu_0925A568[] = {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0};
static u8 anim_unused1[] = {1, 1, 4, 27, 4, 28, 1, 1, 255, 0};
static u8 anim_unused2[] = {1, 1, 4, 27, 4, 28, 4, 27, 1, 1, 255, 0};
extern u8 D_pspeu_0925A578[] = {4, 1, 5, 27, 15, 28, 6, 27, 6, 1, 0};
extern u8 D_pspeu_0925A588[] = {16, 1, 3, 2, 3, 7, 3, 8, 2, 9, 2, 10, 2, 11, 2, 10, 2, 11, 2, 12, 2, 11, 2, 12, 2, 13, 2, 12, 2, 13, 2, 14, 2, 13, 2, 14, 2, 13, 2, 14, 2, 15, 2, 16, 2, 15, 2, 16, 2, 15, 2, 16, 4, 20, 4, 19, 4, 18, 4, 17, 4, 18, 4, 19, 255, 0};
extern u8 D_pspeu_0925A5D0[] = {2, 20, 96, 21, 1, 23, 1, 22, 1, 23, 1, 22, 1, 23, 2, 22, 2, 23, 2, 22, 2, 23, 3, 22, 3, 23, 3, 22, 4, 23, 5, 22, 26, 23, 3, 24, 3, 25, 3, 26, 4, 4, 4, 5, 4, 6, 255, 0};
// death_parts_rotspeeds
extern u16 D_pspeu_0925A600[] = {256, 128, 72, 32, 64, 16, 32, -32};
//deathPartLife
extern u8 D_pspeu_0925A610[] = {48, 32, 20, 12, 24, 16, 64, 48};
//death part xvel
extern s32 D_pspeu_0925A618[] = {FIX(0.75), FIX(1.75), FIX(1.5), FIX(1.0), FIX(2.0), FIX(1.75), FIX(-0.5), FIX(0.5)};
// death part yvel
extern s32 D_pspeu_0925A638[] = {FIX(-5.0), FIX(-3.0), FIX(-2.0), FIX(-3.0), FIX(-4.0), FIX(-0.875), FIX(-6.0), FIX(-4.5)};
//death_parts_xPos
extern s16 D_pspeu_0925A658[] = {-4, 0, 4, -4, -4, 4, -6, 6};
//death_parts_yPos
extern s16 D_pspeu_0925A668[] = {-16, -8, -4, -4, 9, 9, 2, -2};
// laser cooldown
extern u8 D_pspeu_0925A678[] = {128, 8, 8, 64, 240, 192, 160, 128};
static s8 unused[] = {-12, -1, 16, 0, 0, 0, -16, -1, 0, 0, -16, -1};
// vectors
extern SVECTOR D_pspeu_0925A680 = {-32, -32, 0, 0};
extern SVECTOR D_pspeu_0925A688 = {32, -32, 0, 0};
extern SVECTOR D_pspeu_0925A690 = {-32, 32, 0, 0};
extern SVECTOR D_pspeu_0925A698 = {32, 32, 0, 0};
// uv data
extern u8 D_pspeu_0925A6A0[] = {96, 127, 128, 128, 
    32, 95, 64, 128, 
    0, 31, 32, 64};

void func_pspeu_0924EB18(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(&D_pspeu_0925A550);
    // if cooldown has expired...
    if (!g_CurrentEntity->ext.ILLEGAL.u8[5]) {
        if (GetDistanceToPlayerX() >= 0x80) {
            return;
        }
        if ((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
            SetStep(6);
        }
    } else {
        g_CurrentEntity->ext.ILLEGAL.u8[5]--;
    }
}



void func_pspeu_0924EBC8(void) {
    s32 p;
    s32 flag;
    SVECTOR sp60;
    VECTOR sp50;
    MATRIX sp30;
    SVECTOR sp28 = {0};
    s32 yVar;
    s32 xVar;
    Primitive* prim;

    switch (g_CurrentEntity->ext.ILLEGAL.u8[0xC]) {
    case 0:
        g_CurrentEntity->ext.ILLEGAL.s16[8] = 0;
        prim = g_CurrentEntity->ext.prim;
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        g_CurrentEntity->ext.ILLEGAL.u8[0xC] = 1;
        break;
    case 1:
        g_CurrentEntity->ext.ILLEGAL.s16[9] += 0x100;
        g_CurrentEntity->ext.ILLEGAL.s16[8] += 0x200;
        break;
    }
    SetGeomScreen(0x200);
    xVar = g_CurrentEntity->posX.i.hi;
    yVar = g_CurrentEntity->posY.i.hi;
    if (g_CurrentEntity->facingLeft) {
        xVar += 10;
    } else {
        xVar -= 10;
    }
    yVar -= 2;
    SetGeomOffset(xVar, yVar);
    sp60.vx = 0;
    if (g_CurrentEntity->facingLeft) {
        sp60.vy = -0x2E0;
    } else {
        sp60.vy = 0x2E0;
    }
    sp60.vz = g_CurrentEntity->ext.ILLEGAL.s16[9];
    RotMatrix(&sp28, &sp30);
    RotMatrixZ(sp60.vz, &sp30);
    RotMatrixY(sp60.vy, &sp30);
    sp50.vx = 0;
    sp50.vy = 0;
    sp50.vz = 0x200;
    TransMatrix(&sp30, &sp50);
    sp50.vx = g_CurrentEntity->ext.ILLEGAL.s16[8];
    sp50.vy = g_CurrentEntity->ext.ILLEGAL.s16[8];
    sp50.vz = 0x1000;
    ScaleMatrix(&sp30, &sp50);
    SetRotMatrix(&sp30);
    SetTransMatrix(&sp30);
    prim = g_CurrentEntity->ext.prim;
    RotTransPers4(&D_pspeu_0925A680, &D_pspeu_0925A688, &D_pspeu_0925A690,
                  &D_pspeu_0925A698, (long*)&prim->x0, (long*)&prim->x1,
                  (long*)&prim->x2, (long*)&prim->x3, (long*)&p, (long*)&flag);
}

void EntityNovaSkeleton(Entity* self) {
    s32 var_s4;
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        SetStep(8U);
    }
    switch (self->step) { /* switch 1 */
    case 0:               /* switch 1 */
        InitializeEntity(g_EInitNovaSkeleton);
        self->ext.ILLEGAL.u8[5] = 0x50;
        // what. why does psp need to allocate an extra prim.
        #if defined(VERSION_PSP)
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        #else
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        #endif
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x216;
        prim->u0 = prim->u2 = 0xC0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x40;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_HIDE;
        break;
    case 1: /* switch 1 */
        if (UnkCollisionFunc3(D_pspeu_0925A540) == 0) {
            break;
        }
        SetStep(2U);
        break;
    case 2: /* switch 1 */
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(&D_pspeu_0925A578, self);
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(4U);
        }
        break;
    case 3: /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A558, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = 4;
        }
        func_pspeu_0924EB18();
        break;
    case 4: /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A568, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft ^ 1;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = 3;
        }
        func_pspeu_0924EB18();
        break;
    case 6: /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A588, self) == 0) {
            self->ext.ILLEGAL.u8[0xC] = 0;
            SetStep(7U);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            PlaySfxPositional(SFX_ELECTRICITY);
        }
        break;
    case 7:                     /* switch 1 */
        switch (self->step_s) { /* switch 2; irregular */
        case 0:                 /* switch 2 */
            other = self + 1;
            CreateEntityFromEntity(E_UNK_28, self, other);
            if (self->facingLeft) {
                other->posX.i.hi += 0xA;
            } else {
                other->posX.i.hi -= 0xA;
            }
            other->posY.i.hi -= 4;
            other->facingLeft = self->facingLeft;
            self->step_s += 1;
            break;
        case 1:
            prim = self->ext.prim;
            PrimDecreaseBrightness(prim, 5);
            break;
        }
        func_pspeu_0924EBC8();
        if (!AnimateEntity(&D_pspeu_0925A5D0, self)) {
            prim = self->ext.prim;
            prim->drawMode = DRAW_HIDE;
            var_s4 = ++self->ext.ILLEGAL.u8[6] & 7;
            self->ext.ILLEGAL.u8[5] = D_pspeu_0925A678[var_s4];
            SetStep(4U);
        }
        break;
    case 8: /* switch 1 */
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_BLADE_SOLDIER_DEATH_PARTS, other);
            other->facingLeft = self->facingLeft;
            other->params = i;
            other->ext.ILLEGAL.u8[7] = D_pspeu_0925A610[i];
            if (self->facingLeft) {
                other->posX.i.hi -= D_pspeu_0925A658[i];
            } else {
                other->posX.i.hi += D_pspeu_0925A658[i];
            }
            other->posY.i.hi += D_pspeu_0925A668[i];
            other->velocityX = D_pspeu_0925A618[i];
            other->velocityY = D_pspeu_0925A638[i];
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBladeSoldierDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.ILLEGAL.u8[7]) {
            self->rotate += D_pspeu_0925A600[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = 2;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 0x1D;
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void func_us_801C2FF0(Entity* self) {
    s32 var_s7;
    s32 primIndex;
    s32 var_s5;
    Entity* other;
    s32 var_s3;
    s32 var_s2;
    u8* var_s1;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809A4);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        var_s1 = &D_pspeu_0925A6A0[0];
        for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
            prim->tpage = 0x12;
            prim->clut = 0x216;
            prim->u0 = prim->u2 = *var_s1++ + 0x80;
            prim->u1 = prim->u3 = *var_s1++ + 0x80;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x5F;
            prim->r0 = prim->g0 = prim->b0 = *var_s1++;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = *var_s1++;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.ILLEGAL.s16[5] = 0x60;
        self->ext.ILLEGAL.s16[0xA] = 0;
    case 1:
        self->ext.ILLEGAL.s16[0xB] = 0x10;
        if (self->ext.ILLEGAL.s16[0xA] < 0x80) {
            self->ext.ILLEGAL.s16[0xA] += 0x10;
        } else {
            self->ext.ILLEGAL.s16[0xA] = 0x80;
            self->hitboxState = 1;
            self->step += 1;
        }
    case 2:
        if (!(self->ext.ILLEGAL.s16[5] & 3)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_29, self, other);
                other->zPriority = self->zPriority - 1;
                other->ext.ILLEGAL.s16[0xA] = self->ext.ILLEGAL.s16[0xA];
                other->facingLeft = self->facingLeft;
            }
        }
        if (!(self->ext.ILLEGAL.s16[5] & 0xF)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
        }
        if (self->ext.ILLEGAL.s16[5] < 0x10) {
            PlaySfxPositional(SFX_BAT_ECHO_D);
            self->step += 1;
        }
    case 3:
        if (Random() & 1) {
            if (self->ext.ILLEGAL.s16[0xA] < 0x88) {
                self->ext.ILLEGAL.s16[0xA]++;
            } else if (self->ext.ILLEGAL.s16[0xA] > 0x78) {
                self->ext.ILLEGAL.s16[0xA]--;
            }
        }
        self->hitboxWidth = self->ext.ILLEGAL.s16[0xA] / 2 + 0x10;
        self->hitboxOffX = -self->ext.ILLEGAL.s16[0xA] / 2 - 0x10;
        self->hitboxHeight = 8;
        other = self - 1;
        if (other->entityId != 0x27) {
            self->ext.ILLEGAL.s16[5] = 1;
        }
        if (!--self->ext.ILLEGAL.s16[5]) {
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 4:
        self->ext.ILLEGAL.s16[0xB]--;
        if (!self->ext.ILLEGAL.s16[0xB]) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    var_s7 = self->posX.i.hi;
    var_s5 = self->posY.i.hi;
    prim = self->ext.prim;
    for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
        prim->y0 = prim->y1 = var_s5 - self->ext.ILLEGAL.s16[0xB];
        prim->y2 = prim->y3 = var_s5 + self->ext.ILLEGAL.s16[0xB];
        if (g_Timer & 1) {
            prim->clut = 0x216;
        } else {
            prim->clut = 0x217;
        }
    }
    prim = self->ext.prim;
    var_s3 = var_s7;
    if (self->facingLeft) {
        var_s3 -= 0x10;
    } else {
        var_s3 += 0x10;
    }

    prim->x1 = prim->x3 = var_s3;
    if (self->facingLeft) {
        var_s3 += 0x20;
    } else {
        var_s3 -= 0x20;
    }

    prim->x0 = prim->x2 = var_s3;
    prim = prim->next;
    prim->x1 = prim->x3 = var_s3;
    if (self->facingLeft) {
        var_s3 += self->ext.ILLEGAL.s16[0xA];
    } else {
        var_s3 -= self->ext.ILLEGAL.s16[0xA];
    }

    prim->x0 = prim->x2 = var_s3;
    prim = prim->next;
    prim->x1 = prim->x3 = var_s3;
    if (self->facingLeft) {
        var_s3 += 0x20;
    } else {
        var_s3 -= 0x20;
    }
    prim->x0 = prim->x2 = var_s3;
    prim = prim->next;
}

void func_us_801C34A0(Entity* self) {
    s32 temp_s0;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809A4);
        self->hitboxState = 0;
        self->animCurFrame = 0x24;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x10;
        if (self->facingLeft) {
            self->velocityX = FIX(8.0);
        } else {
            self->velocityX = FIX(-8.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->ext.ILLEGAL.u32[6] += abs(self->velocityX);
        self->scaleX = self->scaleY += 0x40;
        if (self->scaleX < 0x100) {
            return;
        }
        self->step++;
        return;
    case 2:
        MoveEntity();
        self->ext.ILLEGAL.u32[6] += abs(self->velocityX);
        temp_s0 = (self->ext.ILLEGAL.s16[0xA] + 0x20) << 0x10;
        temp_s0 -= self->ext.ILLEGAL.u32[6];
        if (temp_s0 < 0) {
            DestroyEntity(self);
            return;
        }
        // okay now let's just play with this number. we're not going to use
        // it but math is fun, I guess? Everyone likes some nice bit shifts.
        temp_s0 >>= 0x10;
        temp_s0 <<= 3;
        if (temp_s0 > 0x100) {
            temp_s0 = 0x100;
        }
        break;
    }
}
