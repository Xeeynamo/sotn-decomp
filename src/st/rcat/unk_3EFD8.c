// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

extern EInit D_us_8018103C;
extern EInit D_us_80181048;
extern EInit D_us_80181054;
extern EInit D_us_80181060;
extern EInit g_EInitParticle;

extern EInit g_EInitFrozenHalf;
extern u8 D_us_80182080[];
extern u8 D_us_80182094[];
extern u8 D_us_801820A0[];
extern u8 D_us_801820AC[];
extern u8 D_us_801820BC[];
extern u8 D_us_801820CC[];
extern u8 D_us_801820DC[];

#ifndef NON_MATCHING
INCLUDE_ASM("st/rcat/nonmatchings/unk_3EFD8", func_us_801BEFD8);
#else
void func_us_801BEFD8(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s32 i;
    s32 j;
    s32 allDone;
    s32 velX;
    s32 fixedX;
    s16 posX;
    s16 posY;
    s8 vLow;
    s8 vHigh;
    s32 yOff;
    u8 uVal;

    if (g_Timer & 1) {
        self->palette = 0x200;
    } else {
        self->palette = 0x201;
    }
    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if ((self->step & 1) && (self->hitFlags & 3)) {
        SetStep(0xA);
    }
    if ((self->flags & FLAG_DEAD) && (u16)self->step < 0x10U) {
        PlaySfxPositional(SFX_FROZEN_HALF_DEATH);
        newEntity = (Entity*)self->ext.ILLEGAL.u32[3];
        if (newEntity != NULL) {
            DestroyEntity(newEntity);
        }
        SetStep(0x10);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalf);
        self->blendMode = DRAW_TPAGE2 | DRAW_TPAGE;
        CreateEntityFromEntity(E_UNK_23, self, self + 1);
        SetStep(3);
        return;

    case 3:
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(5);
            return;
        }
        break;

    case 5:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        self->facingLeft = GetSideToPlayer() & 1;
        {
            s32 vel;
            s32 maskedAngle;
            self->ext.ILLEGAL.u16[3] += 0x20;
            maskedAngle = self->ext.ILLEGAL.u16[3] & 0xFFF;
            vel = rsin(maskedAngle) * 0x10;
            self->velocityY = vel;
            if (self->ext.ILLEGAL.u8[11]) {
                vel += 0x2000;
            } else {
                vel -= 0x2000;
            }
            self->velocityY = vel;
            AnimateEntity(D_us_80182080, self);
            if (maskedAngle < 0x601) {
                self->pose = 0;
                self->poseTimer = 0;
                self->animCurFrame = 1;
            }
        }
        if (!(self->ext.ILLEGAL.u16[3] & 0x3FF)) {
            if (GetDistanceToPlayerX() < 0x68) {
                if (PLAYER.facingLeft != self->facingLeft) {
                    self->ext.ILLEGAL.u8[8] = 1;
                    SetStep(7);
                }
            }
            if (GetDistanceToPlayerX() >= 0x51) {
                if (PLAYER.facingLeft == self->facingLeft) {
                    self->ext.ILLEGAL.u8[8] = 0;
                    SetStep(7);
                }
            }
        }
        if (self->ext.ILLEGAL.u16[3] & 0xFFF) {
            break;
        }
        if (self->posY.i.hi < 0x60) {
            self->ext.ILLEGAL.u8[11] = 1;
        } else {
            self->ext.ILLEGAL.u8[11] = 0;
        }
        return;

    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0;
            self->ext.ILLEGAL.u16[2] = 0x40;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->ext.ILLEGAL.u8[8]) {
                self->animCurFrame = 0xB;
            } else {
                self->animCurFrame = 9;
            }
            if (self->facingLeft != self->ext.ILLEGAL.u8[8]) {
                self->velocityX -= FIX(0.0625);
                if (self->velocityX <= (s32)0xFFFF0000) {
                    self->velocityX = FIX(-1.0);
                }
            } else {
                self->velocityX += FIX(0.0625);
                if (self->velocityX > 0xFFFF) {
                    self->velocityX = FIX(1.0);
                }
            }
            if (!self->ext.ILLEGAL.u8[8]) {
                if (GetDistanceToPlayerX() < 0x48) {
                    SetSubStep(2);
                }
            }
            if (self->ext.ILLEGAL.u8[8]) {
                if (GetDistanceToPlayerX() >= 0x71) {
                    SetSubStep(2);
                }
            }
            {
                u16 timer = self->ext.ILLEGAL.u16[2] - 1;
                self->ext.ILLEGAL.u16[2] = timer;
                if (timer << 16) {
                    break;
                }
            }
            SetSubStep(3);
            return;

        case 2: {
            u8* anim;
            s32 origVel;
            MoveEntity();
            origVel = self->velocityX;
            velX = origVel;
            if (origVel < 0) {
                velX = origVel + 7;
            }
            anim = D_us_801820A0;
            self->velocityX = origVel - (velX >> 3);
            if (self->ext.ILLEGAL.u8[8]) {
                anim = D_us_801820BC;
            }
            if (AnimateEntity(anim, self)) {
                break;
            }
            self->ext.ILLEGAL.u8[8] ^= 1;
            SetSubStep(1);
            return;
        }

        case 3: {
            u8* anim;
            s32 nextStep;
            s32 origVel;
            MoveEntity();
            origVel = self->velocityX;
            velX = origVel;
            if (origVel < 0) {
                velX = origVel + 0xF;
            }
            anim = D_us_80182094;
            self->velocityX = origVel - (velX >> 4);
            if (self->ext.ILLEGAL.u8[8]) {
                anim = D_us_801820AC;
            }
            if (AnimateEntity(anim, self)) {
                break;
            }
            if (self->ext.ILLEGAL.u8[9]) {
                nextStep = 8;
                if (self->posX.i.hi & 0xFF00) {
                    nextStep = 7;
                }
            } else {
                nextStep = 6;
            }
            SetStep(nextStep);
            self->ext.ILLEGAL.u8[9] ^= 1;
            return;
        }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity == NULL) {
                self->ext.ILLEGAL.u32[3] = 0;
                SetStep(5);
                return;
            }
            PlaySfxPositional(SFX_GLASS_SHARDS);
            CreateEntityFromEntity(E_UNK_24, self, newEntity);
            if (self->facingLeft) {
                newEntity->posX.i.hi += 0x10;
            } else {
                newEntity->posX.i.hi -= 0x10;
            }
            newEntity->posY.i.hi -= 0x10;
            newEntity->facingLeft = self->facingLeft;
            self->ext.ILLEGAL.u32[3] = (u32)newEntity;
            self->animCurFrame = 0xD;
            self->step_s++;
            return;

        case 1:
            newEntity = (Entity*)self->ext.ILLEGAL.u32[3];
            if (newEntity->flags & FLAG_DEAD) {
                self->ext.ILLEGAL.u32[3] = 0;
                SetStep(5);
                return;
            }
            if (newEntity->drawFlags & ENTITY_SCALEX) {
                break;
            }
            PlaySfxPositional(SFX_FROZEN_HALF_ATTACK);
            PlaySfxPositional(SFX_GLASS_SHARDS);
            self->ext.ILLEGAL.u32[3] = 0;
            self->ext.ILLEGAL.u16[2] = 0x20;
            self->step_s++;
            return;

        case 2: {
            u16 timer;
            self->animCurFrame = 0xE;
            timer = self->ext.ILLEGAL.u16[2] - 1;
            self->ext.ILLEGAL.u16[2] = timer;
            if (!(timer << 16)) {
                SetStep(5);
                return;
            }
            return;
        }
        }
        break;

    case 8:
        if (self->step_s >= 6U) {
            break;
        }
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 1;
            if (self->posY.i.hi < 0x60) {
                self->step_s++;
                return;
            }
            self->posY.i.hi--;
            return;

        case 1:
            if (AnimateEntity(D_us_801820CC, self)) {
                break;
            }
            PlaySfxPositional(SFX_FROZEN_HALF_MAXIMUM_POWER);
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            self->ext.ILLEGAL.u16[2] = 0x40;
            self->step_s++;
            return;

        case 2:
            if (g_Timer & 2) {
                newEntity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_UNK_27, self, newEntity);
                    newEntity->params = (u16)g_Timer & 1;
                    newEntity->posY.i.hi -= 0x20;
                    if (!newEntity->params) {
                        newEntity->velocityX = (Random() * 2) - 0x8000;
                    } else {
                        newEntity->velocityX = Random() - 0x4000;
                    }
                }
            }
            {
                u16 timer = self->ext.ILLEGAL.u16[2] - 1;
                self->ext.ILLEGAL.u16[2] = timer;
                if (!(timer << 16)) {
                    self->step_s++;
                    return;
                }
            }
            return;

        case 3:
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity == NULL) {
                goto step8_attack_done;
            }
            CreateEntityFromEntity(E_UNK_25, self, newEntity);
            newEntity->posY.i.hi -= 0x28;
            newEntity->facingLeft = self->facingLeft;
            newEntity->zPriority = self->zPriority - 1;
            self->ext.ILLEGAL.u32[3] = (u32)newEntity;
            self->step_s++;
            PlaySfxPositional(SFX_TRANSFORM_3X);
            /* fallthrough */
        case 4:
            newEntity = (Entity*)self->ext.ILLEGAL.u32[3];
            if (newEntity->entityId == E_UNK_25) {
                break;
            }
        step8_attack_done:
            self->ext.ILLEGAL.u32[3] = 0;
            SetSubStep(5);
            return;

        case 5:
            if (!AnimateEntity(D_us_801820DC, self)) {
                SetStep(5);
                return;
            }
            return;
        }
        break;

    case 0xA:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (!self->facingLeft) {
                self->velocityX = FIX(-1.0);
            } else {
                self->velocityX = FIX(1.0);
            }
            self->ext.ILLEGAL.u16[2] = 0x10;
            self->velocityY = 0;
            self->animCurFrame = 0xC;
            self->step_s++;
            /* fallthrough */
        case 1: {
            s32 origVel;
            u16 timer;
            MoveEntity();
            origVel = self->velocityX;
            velX = origVel;
            if (origVel < 0) {
                velX = origVel + 0x1F;
            }
            self->velocityX = origVel - (velX >> 5);
            timer = self->ext.ILLEGAL.u16[2] - 1;
            self->ext.ILLEGAL.u16[2] = timer;
            if (timer << 16) {
                break;
            }
            SetStep(5);
            return;
        }
        }
        break;

    case 0x10:
        if (self->step_s >= 5U) {
            break;
        }
        switch (self->step_s) {
        case 0:
            self[1].step = 0x10;
            self->hitboxState = 0;
            self[1].flags |= FLAG_UNK_2000;
            if (!self->facingLeft) {
                self->velocityX = FIX(-1.0);
            } else {
                self->velocityX = FIX(1.0);
            }
            self->ext.ILLEGAL.u16[2] = 0x10;
            self->velocityY = 0;
            self->animCurFrame = 0xC;
            self->step_s++;
            /* fallthrough */
        case 1: {
            s32 origVel;
            u16 timer;
            MoveEntity();
            origVel = self->velocityX;
            velX = origVel;
            if (origVel < 0) {
                velX = origVel + 0x1F;
            }
            self->velocityX = origVel - (velX >> 5);
            timer = self->ext.ILLEGAL.u16[2] - 1;
            self->ext.ILLEGAL.u16[2] = timer;
            if (!(timer << 16)) {
                self->step_s++;
                return;
            }
            return;
        }

        case 2: {
            s32 primIdx;
            Primitive* firstPrim;
            s32 outerCount;
            s32 xOff;
            s32 innerIdx;
            s8 uOuter;
            s8 uInner;

            primIdx = g_api.AllocPrimitives(PRIM_GT4, 0x200);
            if (primIdx == -1) {
                DestroyEntity(self);
                return;
            }
            firstPrim = &g_PrimBuf[primIdx];
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            self->primIndex = primIdx;
            self->ext.ILLEGAL.u32[0] = (u32)firstPrim;
            self->flags |= FLAG_HAS_PRIMS;
            firstPrim->tpage = 0x12;
            firstPrim->clut = 0x200;
            if (self->facingLeft) {
                firstPrim->u2 = 0xA0;
                firstPrim->u0 = 0xA0;
                uVal = 0x80;
            } else {
                firstPrim->u2 = 0x80;
                firstPrim->u0 = 0x80;
                uVal = 0xA0;
            }
            firstPrim->u3 = uVal;
            firstPrim->u1 = uVal;
            {
                s16 xLeft = posX - 0xF;
                s16 xRight = posX + 0x11;
                s16 yTop = posY - 0x15;
                s16 yBottom = posY + 0x1B;
                firstPrim->v1 = 0;
                firstPrim->v0 = 0;
                firstPrim->v3 = 0x30;
                firstPrim->v2 = 0x30;
                firstPrim->x2 = xLeft;
                firstPrim->x0 = xLeft;
                firstPrim->x3 = xRight;
                firstPrim->x1 = xRight;
                firstPrim->y1 = yTop;
                firstPrim->y0 = yTop;
                firstPrim->y3 = yBottom;
                firstPrim->y2 = yBottom;
            }
            firstPrim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            firstPrim->priority = self->zPriority;
            prim = firstPrim->next;
            yOff = -0x1B;
            vHigh = 0x30;
            vLow = 0x2E;
            for (outerCount = 0; outerCount < 0x18; outerCount++) {
                s16 particleY = posY - yOff;
                s16 particleY2 = particleY - 2;
                xOff = -0xF;
                innerIdx = 0;
                uOuter = -0x7E;
                uInner = -0x80;
                while (xOff < 0x11) {
                    prim->tpage = 0x12;
                    prim->clut = 0x200;
                    if (self->facingLeft) {
                        s8 temp1 = -0x60 - innerIdx;
                        s8 temp2 = -0x62 - innerIdx;
                        prim->u2 = temp1;
                        prim->u0 = temp1;
                        prim->u3 = temp2;
                        prim->u1 = temp2;
                    } else {
                        prim->u2 = uInner;
                        prim->u0 = uInner;
                        prim->u3 = uOuter;
                        prim->u1 = uOuter;
                    }
                    {
                        s16 pxLeft = posX + xOff;
                        s16 pxRight = pxLeft + 2;
                        xOff += 2;
                        innerIdx += 2;
                        uOuter += 2;
                        prim->b0 = 0x60;
                        prim->g0 = 0x60;
                        prim->r0 = 0x60;
                        prim->v1 = vLow;
                        prim->v0 = vLow;
                        prim->v3 = vHigh;
                        prim->v2 = vHigh;
                        prim->x2 = pxLeft;
                        prim->x0 = pxLeft;
                        prim->x3 = pxRight;
                        prim->x1 = pxRight;
                        prim->y1 = particleY2;
                        prim->y0 = particleY2;
                        prim->y3 = particleY;
                        prim->y2 = particleY;
                        LOWU(prim->r1) = LOWU(prim->r0);
                        LOWU(prim->r2) = LOWU(prim->r0);
                        LOWU(prim->r3) = LOWU(prim->r0);
                        prim->p3 = 0x50;
                        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                        prim->priority = self->zPriority + 1;
                    }
                    prim = prim->next;
                    uInner += 2;
                }
                yOff += 2;
                vHigh -= 2;
                vLow -= 2;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->animCurFrame = 0;
            self->ext.ILLEGAL.u16[2] = 1;
            self->ext.ILLEGAL.s32[4] = 0;
            PlaySfxPositional(SFX_GLASS_SHARDS);
            self->step_s++;
            return;
        }

        case 3: {
            Primitive* firstPrim2;
            u16 timer;
            timer = self->ext.ILLEGAL.u16[2] - 1;
            self->ext.ILLEGAL.u16[2] = timer;
            allDone = 1;
            if (!(timer << 16)) {
                firstPrim2 = (Primitive*)self->ext.ILLEGAL.u32[0];
                self->ext.ILLEGAL.u16[2] = 6;
                firstPrim2->v3 -= 2;
                firstPrim2->v2 = firstPrim2->v3;
                firstPrim2->y3 -= 2;
                firstPrim2->y2 = firstPrim2->y3;
                self->ext.ILLEGAL.s32[4]++;
                if (self->ext.ILLEGAL.s32[4] >= 0x17) {
                    self->step_s++;
                }
            }
            /* fallthrough */
        }
        case 4:
            allDone = 1;
            prim = ((Primitive*)self->ext.ILLEGAL.u32[0])->next;
            for (i = 0; i < self->ext.ILLEGAL.s32[4] * 0x10; i++) {
                if (!prim->r0) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    allDone = 0;
                    fixedX = (prim->x0 << 8) + prim->p2;
                    if (self->facingLeft) {
                        fixedX -= (prim->u0 - 0x90) * 0x18;
                    } else {
                        fixedX += (prim->u0 - 0x90) * 0x18;
                    }
                    prim->x0 = fixedX >> 8;
                    prim->p2 = (u8)fixedX;
                    prim->y0 = (s16)((s32)((prim->y0 << 8) - 0x400 +
                                           (prim->p3 * 0x10)) >>
                                     8);
                    if (prim->p3) {
                        prim->p3 -= 2;
                    }
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    {
                        s16 newX = (u16)prim->x0 + 2;
                        s16 newY = (u16)prim->y0 + 2;
                        u8 fade = prim->r0 - 2;
                        prim->r0 = fade;
                        prim->x2 = prim->x0;
                        prim->x3 = newX;
                        prim->x1 = newX;
                        prim->y1 = prim->y0;
                        prim->y3 = newY;
                        prim->y2 = newY;
                        prim->b0 = fade;
                        prim->g0 = fade;
                        prim->b3 = fade;
                        prim->g3 = fade;
                        prim->r3 = fade;
                        prim->b2 = fade;
                        prim->g2 = fade;
                        prim->r2 = fade;
                        prim->b1 = fade;
                        prim->g1 = fade;
                        prim->r1 = fade;
                    }
                }
                prim = prim->next;
            }
            if (!allDone) {
                break;
            }
            DestroyEntity(self);
            return;
        }
        break;

    case 0xFF:
        FntPrint("charal %x\n", (u16)self->animCurFrame);
        if (g_pads[1].pressed & 0x80) {
            if (self->params) {
                break;
            }
            self->animCurFrame = (s16)((u16)self->animCurFrame + 1);
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & 0x20) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame = (s16)((u16)self->animCurFrame - 1);
            self->step_s |= 1;
            return;
        }
        self->step_s = 0;
        break;
    }
}
#endif

extern u8 D_us_801820EC[];
extern u8 D_us_801820F8[];
extern u8 D_us_80182108[];
extern u8 D_us_80182100[];
extern u8 D_us_80182140[];
extern u8 D_us_80182174[];
extern u16 D_us_80182110[];
extern s16 D_us_80182120[];
extern s16 D_us_80182128[];
extern s16 D_us_80182130[];
extern s16 D_us_80182138[];

void func_us_801BFF94(Entity* self) {
    s16 angle;
    s16 new_var2;
    Entity* new_var;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018103C);
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_801820EC, self);
        self->ext.ILLEGAL.u16[3] += 0x40;
        new_var = self - 1;
        if (new_var->entityId != 0x22) {
            DestroyEntity(self);
            break;
        }
        angle = self->ext.ILLEGAL.u16[3];
        posX = new_var->posX.val;
        posY = new_var->posY.val;
        posX += rcos(angle) << 9;
        posY += rsin(angle / 2) << 7;
        self->posX.val = posX;
        self->posY.val = posY;
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleY = 0x100;
            self->scaleX = 0x100;
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            AnimateEntity(D_us_801820F8, self);
            new_var2 = (self->scaleY -= 0x10);
            self->scaleX = self->scaleY;
            if (!(s16)new_var2) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

void func_us_801C0118(Entity* self) {
    s16 new_var;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181048);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleY = 0;
        self->scaleX = 0;
        self->drawFlags |= ENTITY_ROTATE;
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_80182108, self);
        self->scaleX += 8;
        new_var = self->scaleX;
        self->rotate += 0x10;
        self->scaleY = new_var;
        if ((s16)self->scaleX >= 0x100) {
            self->drawFlags = ENTITY_ROTATE;
            self->palette = 0x815F;
            self->step++;
            break;
        }
        break;
    case 2:
        self->palette = 0x200;
        angle = GetAngleBetweenEntities(self, &PLAYER);
        self->velocityX = rcos(angle) * 5 << 3;
        self->velocityY = rsin(angle) * 5 << 3;
        if (self->facingLeft) {
            if (self->velocityX > 0) {
                self->velocityX = FIX(-0.625);
            }
        } else {
            if (self->velocityX < 0) {
                self->velocityX = FIX(0.625);
            }
        }
        self->step++;
        break;
    case 3:
        AnimateEntity(D_us_80182108, self);
        MoveEntity();
        self->rotate += 0x40;
        break;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("st/rcat/nonmatchings/unk_3EFD8", func_us_801C02C4);
#else
void func_us_801C02C4(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s32 offset;
    s32 primIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181054);
        self->scaleY = 0;
        self->scaleX = 0;
        self->animCurFrame = 0;
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 0x41);
        if (primIdx == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIdx];
        self->primIndex = primIdx;
        self->flags |= FLAG_HAS_PRIMS;
        self->ext.ILLEGAL.u32[0] = (u32)prim;
        prim->tpage = 0x12;
        prim->clut = 0x202;
        prim->u3 = 0x40;
        prim->u1 = 0x40;
        prim->v1 = 0x80;
        prim->v0 = 0x80;
        prim->u2 = 0;
        prim->u0 = 0;
        prim->v3 = 0xC0;
        prim->v2 = 0xC0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        /* fallthrough */
    case 1:
        switch (self->step_s) {
        case 0:
            self->scaleX += 0x80;
            self->scaleY = self->scaleX;
            primIdx = (s16)self->scaleX;
            self->rotate += 0x40;
            if (primIdx >= 0x2000) {
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY -= FIX(0.25);
            self->rotate += 0x80;
            self->scaleX += 0x200;
            if ((s16)self->posY.i.hi < -0x60) {
                SetStep(2);
            }
            break;
        }
        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, 0x80);
        {
            SVECTOR rotation;
            VECTOR translation;
            MATRIX mtx;
            rotation.vx = 0;
            rotation.vy = self->rotate;
            rotation.vz = 0;
            RotMatrixYXZ(&rotation, &mtx);
            translation.vx = 0;
            translation.vy = self->posY.i.hi - 0x80;
            translation.vz = 0x100;
            TransMatrix(&mtx, &translation);
            translation.vx = self->scaleX;
            translation.vy = self->scaleX;
            translation.vz = self->scaleX;
            ScaleMatrix(&mtx, &translation);
            SetRotMatrix(&mtx);
            SetTransMatrix(&mtx);
        }
        {
            Primitive* prim2;
            prim = (Primitive*)self->ext.ILLEGAL.u32[0];
            prim2 = prim->next;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim2 = UnkRecursivePrimFunc1(
                D_us_80182120, D_us_80182128, D_us_80182130, D_us_80182138,
                prim, 2, prim2, (u8*)0x1F800000);
            prim->drawMode = DRAW_HIDE;
            if (prim2) {
                do {
                    prim2->drawMode = DRAW_HIDE;
                    prim2 = prim2->next;
                } while (prim2);
            }
        }
        break;
    case 2:
        prim = (Primitive*)self->ext.ILLEGAL.u32[0];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.ILLEGAL.u16[2] = 0x200;
        self->step++;
        break;
    case 3:
        if (PLAYER.velocityX > 0) {
            offset = -0x40;
        } else {
            offset = -0x80;
        }
        if (PLAYER.velocityX < 0) {
            offset -= 0x40;
        }
        if (!(self->ext.ILLEGAL.u16[2] & 0xF)) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_26, newEntity);
                newEntity->posY.i.hi = -0x20;
                newEntity->posX.i.hi = D_us_80182110[self->ext.ILLEGAL.u8[10]];
                newEntity->params = 0;
            }
            self->ext.ILLEGAL.u8[10] = (self->ext.ILLEGAL.u8[10] + 1) & 7;
        }
        newEntity = AllocEntity(
            &g_Entities[STAGE_ENTITY_START], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_26, newEntity);
            newEntity->posY.i.hi = -0x10;
            newEntity->posX.i.hi = (Random() << 1) + offset;
            newEntity->params = 1;
        }
        if (!(self->ext.ILLEGAL.u16[2] & 0x1F)) {
            g_api.PlaySfx(SFX_FROZEN_HALF_BLIZZARD);
        }
        {
            u16 timer = self->ext.ILLEGAL.u16[2] - 1;
            self->ext.ILLEGAL.u16[2] = timer;
            if (!(timer << 16)) {
                DestroyEntity(self);
            }
        }
        break;
    }
}
#endif

void func_us_801C0718(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181060);
        if (self->params) {
            self->animCurFrame = 0x16;
            self->blendMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
            self->step = 2;
            self->velocityX = FIX(0.75);
            self->hitboxState = 0;
            self->velocityY = FIX(5.0);
            break;
        }
        self->drawFlags = ENTITY_ROTATE;
        self->velocityX = FIX(0.5);
        self->velocityY = FIX(4.0);
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182100, self);
        self->velocityY += FIX(0.0625);
        self->rotate += 0x20;
        if ((s16)self->posY.i.hi >= 0x101) {
            DestroyEntity(self);
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        if ((s16)self->posY.i.hi >= 0x101) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801C0844(Entity* self) {
    Entity* new_var;
    u8* anim;
    s32 ret;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        if (!self->params) {
            self->animSet = 0xE;
            self->unk5A = 0x5C;
            self->velocityY = FIX(1.0);
        } else {
            self->animSet = 5;
            self->velocityY = FIX(1.25);
        }
        self->blendMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->palette = 0x8202;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x80;
        /* fallthrough */
    case 1:
        MoveEntity();
        ret = self->velocityY;
        self->velocityY -= ret / 64;
        self->velocityX += self->velocityX / 32;
        ret = !self->params;
        do {
            anim = D_us_80182140;
            new_var = self;
            if (ret) {
                anim = D_us_80182174;
            }
            ret = AnimateEntity(anim, new_var);
        } while (0);
        self->opacity += -1;
        if (!self->opacity) {
            ret = 0;
        }
        if (!ret) {
            DestroyEntity(self);
        }
        break;
    }
}
