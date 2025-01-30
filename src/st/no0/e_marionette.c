// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

u8 func_us_801D6254(s16 arg0[]) {
    Collider collider;
    s16 xDir;
    u8 ret = 0;
    s32 i;
    s16 posX;
    s16 posX2;
    s16 posY;
    s16 posY2;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
    posX2 = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi + *arg0++;
    posY2 = g_CurrentEntity->posY.i.hi + *arg0++;

    if (g_CurrentEntity->velocityX > 0) {
        xDir = *arg0;
    } else {
        xDir = -*arg0;
    }

    posX = posX2;
    g_api.CheckCollision(posX, posY, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk18;
        g_CurrentEntity->velocityY = 0;
        ret |= 1;
    }
    posX = posX2;
    g_api.CheckCollision(posX, posY2, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk20;
        g_CurrentEntity->velocityY = 0;
        ret |= 2;
    }

    posY2 += 2;
    for (i = 0; i < 5; i++, posY2 += 5) {
        posX = g_CurrentEntity->posX.i.hi + xDir;
        g_api.CheckCollision(posX, posY2, &collider, 0);
        if ((collider.effects & (EFFECT_SOLID | EFFECT_UNK_0002)) &&
            !(collider.effects & EFFECT_UNK_8000)) {
            ret |= 4;
            if (g_CurrentEntity->velocityX > 0) {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            }
            g_CurrentEntity->velocityX = 0;
            break;
        }
    }

    return ret;
}

void func_us_801D6474(Primitive* prim) {
    Collider collider;
    Entity* newEntity;
    s16 xVal;
    s16 yVal;

    UnkPrimHelper(prim);
    switch (prim->next->u2) {
    case 0:
        LOW(prim->next->u0) = ((Random() & 31) << 12) - FIX(1.0);
        LOW(prim->next->r1) = -(Random() & 31) << 12;
        if (LOH(prim->next->r2) + LOH(prim->next->b2) >= 48) {
            prim->next->u2 = 1;
            prim->next->x3 = 256;
        } else {
            prim->next->u2 = 2;
            prim->next->x3 = ((Random() & 15) * 4) + 8;
        }
        // fallthrough
    case 1:
        xVal = prim->next->x1;
        yVal = prim->next->y0 + 4;
        g_api.CheckCollision(xVal, yVal, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->next->y0 += collider.unk18;
            if (LOW(prim->next->r1) < 0x4000) {
                prim->next->x3 = 1;
            }
            LOW(prim->next->r1) = -LOW(prim->next->r1);
            LOW(prim->next->r1) -= LOW(prim->next->r1) / 2;
        }
        // fallthrough
    case 2:
        if (LOW(prim->next->u0) > 0) {
            HIH(prim->next->u1) -= 32;
        } else {
            HIH(prim->next->u1) += 32;
        }
        LOW(prim->next->r1) += 0x1800;
        prim->next->x3 -= 1;
        if (!prim->next->x3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->posX.i.hi = prim->next->x1;
                newEntity->posY.i.hi = prim->next->y0;
                newEntity->params = 0;
            }
            UnkPolyFunc0(prim);
        }
        break;
    }
}

extern s16 D_us_80181FE8[];
extern s16 D_us_80181FF0[];
extern s16 D_us_80182000[];
extern u8 D_us_80182008[];
extern u8 D_us_80182024[];
extern u8 D_us_8018204C[];
extern u8 D_us_80182074[];
extern u8 D_us_801820A0[];
extern u8 D_us_801820B4[];
extern u8 D_us_801820C4[];
extern u8 D_us_801820D8[];
extern u8 D_us_801820E4[];
extern u8* D_us_80182178[];
extern s16* D_us_801BA12C[];

void EntityMarionette(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16* dataPtr;
    s16 posX, posY;
    s32 primIndex;
    u8 flag;
    s16 clut;

    if ((self->flags & FLAG_DEAD) && self->step < 10) {
        self->hitboxState = 0;
        self->palette = self->hitEffect = g_EInitSlinger[5] + 1;
        SetStep(10);
        PlaySfxPositional(0x726);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMarionette);
        self->animCurFrame = 0x22;
        self->facingLeft = self->params & 1;
        break;

    case 1:
        self->animCurFrame = 0x22;
        UnkCollisionFunc3(D_us_80181FF0);
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            PlaySfxPositional(SFX_MARIONETTE_RATTLE);
            self->velocityX = 0;
            self->velocityY = 0;
            switch (self->animCurFrame) {
            case 8:
                self->ext.et_marionette.unk80 = D_us_80182024;
                break;
            case 25:
                self->ext.et_marionette.unk80 = D_us_8018204C;
                break;
            case 34:
                self->ext.et_marionette.unk80 = D_us_80182074;
                break;
            }
            self->step_s++;
        }
        if (!AnimateEntity(self->ext.et_marionette.unk80, self)) {
            if (Random() & 1) {
                SetStep(4);
            } else {
                SetStep(8);
            }
        }
        func_us_801D6254(D_us_80181FE8);
        self->velocityY += FIX(0.5 / 16);
        if (self->animFrameIdx == 10 && !self->animFrameDuration) {
            self->velocityY = FIX(-1.0);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->ext.et_marionette.unk84 = D_us_80182000[Random() & 3];
            self->step_s++;
        }
        flag = AnimateEntity(D_us_80182008, self);
        if (!flag) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        flag = func_us_801D6254(D_us_80181FE8);
        if (flag & 4) {
            self->facingLeft ^= 1;
        }
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        self->velocityY += 0x400;
        if (!--self->ext.et_marionette.unk84) {
            if (Random() & 1) {
                SetStep(6);
            } else {
                SetStep(5);
            }

            if (GetDistanceToPlayerX() > 0x60) {
                SetStep(5);
            }
        }
        break;

    case 5:
        flag = func_us_801D6254(D_us_80181FE8);
        self->velocityY += FIX(1.0 / 16);
        switch (self->step_s) {
        case 0:
            if (flag & 1) {
                self->step_s++;
            }
            break;

        case 1:
            flag = 0;
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 0x1C;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_UNK_8000) {
                SetStep(8);
            } else {
                posY -= 4;
                posX += 0x18;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    if (self->facingLeft) {
                        self->facingLeft ^= 1;
                    }
                    flag = 1;
                }
                posX -= 0x30;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    if (flag) {
                        SetStep(8);
                        break;
                    }
                    if (!self->facingLeft) {
                        self->facingLeft ^= 1;
                    }
                    flag = 1;
                }
                self->ext.et_marionette.unk80 =
                    *(&D_us_80182178[flag] + (Random() & 1));
                self->velocityX = 0;
                self->velocityY = FIX(-1.0);
                if (self->animFrameIdx > 0) {
                    self->velocityY = 0;
                }
                self->step_s++;
                PlaySfxPositional(SFX_MARIONETTE_RATTLE);
                self->ext.et_marionette.unk84 = 0x30;
            }
            break;
        case 2:
            if (!AnimateEntity(self->ext.et_marionette.unk80, self)) {
                if (GetDistanceToPlayerX() < 0x100) {
                    self->ext.et_marionette.unk84--;
                }
                if (!self->ext.et_marionette.unk84) {
                    SetStep(3);
                }
                if (GetDistanceToPlayerX() < 0x60) {
                    SetStep(3);
                }
                break;
            }
            break;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            posX = GetDistanceToPlayerX();
            if (posX < 0x20) {
                posX = 0x20;
            }
            if (posX > 0xA0) {
                posX = 0xA0;
            }
            self->velocityX = -posX * 0x200;
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = FIX(-2.0);
            self->step_s++;
            break;

        case 1:
            if (!AnimateEntity(D_us_801820C4, self)) {
                SetSubStep(2);
            }
            flag = func_us_801D6254(D_us_80181FE8);
            if (flag & 4) {
                self->velocityX = 0;
            }
            self->velocityY += FIX(0.5 / 16);
            self->ext.et_marionette.unk84 = 0x10;
            break;

        case 2:
            AnimateEntity(D_us_801820D8, self);
            flag = func_us_801D6254(D_us_80181FE8);
            if (flag & 4) {
                self->velocityX = 0;
            }
            self->velocityY += FIX(1.0 / 16);
            posX = GetDistanceToPlayerX();
            if (posX < 0x20) {
                posX = 0x20;
            }
            if (posX > 0xA0) {
                posX = 0xA0;
            }
            self->velocityX = -posX * 0x280;
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            if (self->ext.et_marionette.unk84 &&
                !--self->ext.et_marionette.unk84 && (Random() & 1) == 0) {
                SetStep(9);
            } else if (flag & 1) {
                self->velocityX = 0;
                self->velocityY = 0;
                SetSubStep(3);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_801820E4, self)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(5);
                    self->animFrameIdx = 10;
                }
            }
            break;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->velocityY = 0;
            self->velocityX = FIX(-0.75);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->step_s++;
            if ((Random() & 1) == 0) {
                SetStep(7);
            }
            break;

        case 1:
            flag = func_us_801D6254(D_us_80181FE8);
            if (flag & 4) {
                self->velocityX = 0;
            }
            if (!AnimateEntity(D_us_801820C4, self)) {
                SetSubStep(2);
                self->velocityX = FIX(-1.125);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->ext.et_marionette.unk84 = 0x80;
            }
            break;

        case 2:
            AnimateEntity(D_us_801820D8, self);
            flag = func_us_801D6254(D_us_80181FE8);
            if (flag & 4) {
                self->velocityX = 0;
            }
            if (!--self->ext.et_marionette.unk84 || flag & 4) {
                self->velocityX = 0;
                self->velocityY = 0;
                SetSubStep(3);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_801820E4, self)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(5);
                    self->animFrameIdx = 10;
                }
            }
            break;
        }
        break;

    case 8:
        func_us_801D6254(D_us_80181FE8);
        self->velocityY += FIX(0.5 / 16);
        switch (self->step_s) {
        case 0:
            self->ext.et_marionette.unk84 = 0x80;
            PlaySfxPositional(0x725);
            self->step_s++;
            break;

        case 1:
            AnimateEntity(D_us_801820B4, self);
            if (!--self->ext.et_marionette.unk84) {
                SetSubStep(2);
                self->animFrameIdx = 5;
                self->animFrameDuration = 0;
            }
            if (GetDistanceToPlayerX() < 0x40) {
                SetSubStep(3);
                self->animFrameIdx = 5;
                self->animFrameDuration = 0;
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_801820B4, self)) {
                SetStep(4);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_801820B4, self)) {
                SetStep(6);
            }
            break;
        }
        break;

    case 9:
        func_us_801D6254(D_us_80181FE8);
        self->velocityX -= self->velocityX / 24;
        self->velocityY -= self->velocityY / 24;
        if (!AnimateEntity(D_us_801820A0, self)) {
            SetStep(4);
        }
        break;

    case 10:
        switch (self->step_s) {
        case 0:
            dataPtr = (s16*)g_EInitMarionette;
            clut = *(dataPtr + 11);
            dataPtr = D_us_801BA12C[self->animCurFrame];
            primIndex = g_api.AllocPrimitives(PRIM_GT4, *dataPtr * 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.et_marionette.unk7C = prim;
                dataPtr += 2;

                posX = self->unk5A & 1;
                posX = posX * 0x7F;
                posY = (self->unk5A & 2) >> 1;
                posY = posY * 0x7F;
                while (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->x1 = self->posX.i.hi;
                    if (self->facingLeft) {
                        prim->next->x1 -= *dataPtr++;
                    } else {
                        prim->next->x1 += *dataPtr++;
                    }
                    prim->next->y0 = self->posY.i.hi + *dataPtr++;
                    LOH(prim->next->r2) = *dataPtr++;
                    if (self->facingLeft) {
                        prim->next->x1 -= LOH(prim->next->r2) / 2;
                    } else {
                        prim->next->x1 += LOH(prim->next->r2) / 2;
                    }
                    LOH(prim->next->b2) = *dataPtr++;
                    prim->next->y0 += LOH(prim->next->b2) / 2;
                    dataPtr += 2;
                    if (self->facingLeft) {
                        prim->u1 = prim->u3 = posX + *dataPtr++;
                        prim->v0 = prim->v1 = posY + *dataPtr++;
                        prim->u0 = prim->u2 = posX + *dataPtr++;
                        prim->v2 = prim->v3 = posY + *dataPtr++;
                    } else {
                        prim->u0 = prim->u2 = posX + *dataPtr++;
                        prim->v0 = prim->v1 = posY + *dataPtr++;
                        prim->u1 = prim->u3 = posX + *dataPtr++;
                        prim->v2 = prim->v3 = posY + *dataPtr++;
                    }
                    prim->tpage = 0x12;
                    prim->clut = clut;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode = DRAW_UNK02;
                    dataPtr++;
                    prim = prim->next;
                    prim = prim->next;
                }
            } else {
                DestroyEntity(self);
                return;
            }
            self->animCurFrame = 0;
            self->step_s++;
            break;

        case 1:
            flag = false;
            prim = self->ext.et_marionette.unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_us_801D6474(prim);
                    flag = true;
                }
                prim = prim->next;
                prim = prim->next;
            }
            if (!flag) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    flag = self->animCurFrame;
    if (flag > 7 && flag < 14) {
        flag = 0;
    }
    if (flag > 24 && flag < 32) {
        flag = 0;
    }
    if (flag > 33 && flag < 38) {
        flag = 0;
    }
    if (!flag) {
        self->hitboxOffX = 1;
        self->hitboxOffY = 16;
        self->hitboxWidth = 3;
        self->hitboxHeight = 11;
    } else {
        self->hitboxOffX = 1;
        self->hitboxOffY = 5;
        self->hitboxWidth = 3;
        self->hitboxHeight = 18;
    }
}
