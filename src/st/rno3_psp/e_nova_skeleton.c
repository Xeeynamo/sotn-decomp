// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern s16 D_pspeu_0925A550[];

void func_pspeu_0924EB18(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(&D_pspeu_0925A550);
    // if cooldown has expired...
    if (!g_CurrentEntity->ext.ILLEGAL.u8[5]) {
        if (GetDistanceToPlayerX() >= 0x80){
            return;
        }
        if((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
            SetStep(6);
        }
    } else {
        g_CurrentEntity->ext.ILLEGAL.u8[5]--;
    }
}

extern SVECTOR D_pspeu_0925A680;
extern SVECTOR D_pspeu_0925A688;
extern SVECTOR D_pspeu_0925A690;
extern SVECTOR D_pspeu_0925A698;

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
        prim->drawMode = 0x37;
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
    RotTransPers4(&D_pspeu_0925A680, &D_pspeu_0925A688, &D_pspeu_0925A690, &D_pspeu_0925A698, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                      (long*)&prim->x3, (long*)&p, (long*)&flag);
}


extern s32 D_pspeu_0925A540;
extern s32 D_pspeu_0925A558;
extern s32 D_pspeu_0925A568;
extern s32 D_pspeu_0925A578;
extern s32 D_pspeu_0925A588;
extern s32 D_pspeu_0925A5D0;
extern u8 D_pspeu_0925A610[];
extern s32 D_pspeu_0925A618[];
extern s32 D_pspeu_0925A638[];
extern s16 D_pspeu_0925A658[];
extern s16 D_pspeu_0925A668[];
extern u8 D_pspeu_0925A678[];
extern u16 g_EInitNovaSkeleton;
extern Entity g_Entities_224;

void EntityNovaSkeleton(Entity* self) {
    s32 var_s4;
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    if (self->flags & 0x100) {
        SetStep(8U);
    }
    switch (self->step) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        InitializeEntity(&g_EInitNovaSkeleton);
        self->ext.ILLEGAL.u8[5] = 0x50;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
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
        prim->drawMode = 8;
        break;
    case 1:                                         /* switch 1 */
        if (UnkCollisionFunc3(&D_pspeu_0925A540) == 0) {
            break;
        }
        SetStep(2U);
        break;
    case 2:                                         /* switch 1 */
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(&D_pspeu_0925A578, self);
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(4U);
        }
        break;
    case 3:                                         /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A558, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = 0x8000;
        } else {
            self->velocityX = -0x8000;
        }
        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = 4;
        }
        func_pspeu_0924EB18();
        break;
    case 4:                                         /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A568, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft ^ 1;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = 0x8000;
        } else {
            self->velocityX = -0x8000;
        }
        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = 3;
        }
        func_pspeu_0924EB18();
        break;
    case 6:                                         /* switch 1 */
        if (AnimateEntity(&D_pspeu_0925A588, self) == 0) {
            self->ext.ILLEGAL.u8[0xC] = 0;
            SetStep(7U);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            PlaySfxPositional(0x614);
        }
        break;
    case 7:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            other = self + 1;
            CreateEntityFromEntity(0x28U, self, other);
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
            prim->drawMode = 8;
            var_s4 = ++self->ext.ILLEGAL.u8[6] & 7;
            self->ext.ILLEGAL.u8[5] = D_pspeu_0925A678[var_s4];
            SetStep(4U);
        }
        break;
    case 8:                                         /* switch 1 */
        for(i = 0; i < 6; i++){
            other = AllocEntity(&g_Entities_224, (Entity* ) &D_80097C98);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(0x2A, other);
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
        PlaySfxPositional(0x62A);
        DestroyEntity(self);
        break;
    }
}

extern u16 death_parts_rotspeeds[];
extern u16 g_EInitNovaSkeleton;

void EntityBladeSoldierDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.ILLEGAL.u8[7]) {
            self->rotate += death_parts_rotspeeds[self->params];
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
    InitializeEntity(&g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |= 0xC0202000;
    self->animCurFrame = self->params + 0x1D;
    self->drawFlags = 4;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C2FF0);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C34A0);
