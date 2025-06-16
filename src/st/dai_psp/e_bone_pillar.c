// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dai/dai.h"

extern s32 D_pspeu_0925CAC0;
extern s32 D_pspeu_0925CAD0;
extern s16 D_pspeu_0925CAD8;
extern s16 D_pspeu_0925CAE8[];
extern s16 D_pspeu_0925CAF0;
extern s32 D_pspeu_0925CAF8;
extern s32 D_pspeu_0925CB30;
extern s32 D_pspeu_0925CB68;
extern s16 D_pspeu_0925CB80[];
extern s16* D_pspeu_0925F008[];
extern u16 D_pspeu_09263196;

extern const char D_pspeu_0925CB90;

void func_us_801D1D00(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s16 temp_v1;
    s16* ptr;
    s32 posX, posY;
    s32 i;
    s32 var_s6;

    if ((self->flags & 0x100) && (self->step < 8)) {
        SetStep(8);
    }
    if (self->ext.et_801D2444.unk85) {
        self->ext.et_801D2444.unk85 = 0;
        SetStep(0xA);
    }
    switch (self->step) { // irregular
    case 0x0:
        InitializeEntity(D_us_801809F8);
        self->palette = D_pspeu_09263196 + 1;
        self->animCurFrame = 1;
        self->flags |= 0x20000000;
        if (self->params & 0xFF) {
            self->hitboxOffX = -1;
            self->hitboxOffY = -0xE;
            self->animCurFrame = 9;
            SetStep(2);
            break;
        }
        self->hitboxOffX = -3;
        self->hitboxOffY = 0xD;
    case 0x1:
        if (UnkCollisionFunc3(&D_pspeu_0925CAC0) & 1) {
            if (self->params & 0x100) {
                newEntity = self + 1;
                CreateEntityFromCurrentEntity(0x2C, newEntity);
                newEntity->posX.i.hi = self->posX.i.hi + 8;
                newEntity->posY.i.hi = self->posY.i.hi - 8;
                self->params = 0;
            } else {
                newEntity = self + 1;
                CreateEntityFromCurrentEntity(0x29, newEntity);
                newEntity->params = 1;
                newEntity->posX.i.hi = self->posX.i.hi;
                newEntity->posY.i.hi = self->posY.i.hi;
            }
            SetStep(2);
        }
        break;
    case 0x2:
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(3);
        }
        break;
    case 0x3:
        if (!self->step_s) {
            self->ext.et_801D2444.unk80 =
                D_pspeu_0925CB80[self->ext.et_801D2444.unk84];
            self->ext.et_801D2444.unk84++;
            self->ext.et_801D2444.unk84 &= 7;
            self->step_s++;
        }
        if (self->params) {
            self->animCurFrame = 9;
        } else {
            self->animCurFrame = 1;
        }
        if (self->params == ((GetSideToPlayer() & 1) ^ 1)) {
            if (!--self->ext.et_801D2444.unk80) {
                SetStep(4);
            }
        }
        if (GetDistanceToPlayerX() > 0x80) {
            SetStep(3);
        }
        break;
    case 0x4:
        if (g_Timer & 2) {
            self->palette = D_pspeu_09263196;
        } else {
            self->palette = D_pspeu_09263196 + 1;
        }
        if (self->params) {
            var_s6 = AnimateEntity(&D_pspeu_0925CB30, self);
        } else {
            var_s6 = AnimateEntity(&D_pspeu_0925CAF8, self);
        }
        if (!var_s6) {
            self->palette = D_pspeu_09263196 + 1;
            SetStep(3);
        }
        if ((self->pose == 0x11) && (var_s6 & 0x80)) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2A, self, newEntity);
                newEntity->facingLeft = self->params;
                if (self->params) {
                    newEntity->posY.i.hi -= 0xE;
                    break;
                }
                newEntity->posY.i.hi += 8;
            }
        }
        break;
    case 0x8:
        ptr = &D_pspeu_0925CAD8;
        var_s6 = 0;
        if (!self->params) {
            ptr += 4;
            var_s6 = 2;
        }
        for (i = 0; i < 2; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2B, self, newEntity);
                newEntity->params = i + var_s6;
                newEntity->posX.i.hi += *ptr++;
                newEntity->posY.i.hi += *ptr++;
            }
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->params = 2;
        }
        if ((!self->params) &&
            ((newEntity = self + 1, (newEntity->entityId) == 0x29) ||
             ((newEntity->entityId) == 0x2C))) {
            newEntity->ext.et_801D2444.unk85 = 1;
        }
        PlaySfxPositional(0x683);
        DestroyEntity(self);
        break;
    case 0xA:
        switch (self->step_s) { // switch 1; irregular
        case 0:
            self->animCurFrame = 0x18;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->drawFlags |= 4;
            self->velocityX = -0xC000;
            self->velocityY = -0x10000;
            self->flags &= 0xDFFFFFFF;
            self->flags |= 0x02000000;
            self->step_s++;
            // fallthrough
        case 1:
            self->rotate -= 0x20;
            MoveEntity();
            self->velocityY += 0x3000;
            for (ptr = &D_pspeu_0925CAF0, i = 0; i < 4; i++, ptr++) {
                posX = self->posX.i.hi;
                posY = self->posY.i.hi;
                temp_v1 = self->rotate + *ptr;
                posX += ((rcos(temp_v1) * 0xE) >> 0xC);
                posY += ((rsin(temp_v1) * 0xE) >> 0xC);
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & 1) {
                    PlaySfxPositional(0x6A6);
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = -self->velocityY;
                    self->velocityY -= self->velocityY / 2;
                    break;
                }
            }
            if (self->flags & 0x100) {
                PlaySfxPositional(0x683);
                self->hitboxState = 0;
                self->drawFlags = 0;
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 1;
            }
        }
        break;
    case 0xFF:
        FntPrint(&D_pspeu_0925CB90, self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

void func_us_801D2444(Entity* self) {
    Collider collider;
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 posY;

    if (self->flags & 0x100) {
        PlaySfxPositional(0x683);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->params = 3;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A1C);
        self->animCurFrame = 0x16;
        self->hitboxWidth = 0xD;
        self->hitboxHeight = 0xD;
        self->flags |= 0x02000000;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        prim->tpage = self->unk5A / 4;
        if (self->unk5A & 1) {
            posX = 0x80;
        } else {
            posX = 0;
        }
        if (self->unk5A & 2) {
            posY = 0x80;
        } else {
            posY = 0;
        }
        prim->clut = D_us_80180A1C[3] + 2;
        prim->u0 = prim->u2 = posX + 0x50;
        prim->u1 = prim->u3 = posX + 0x70;
        prim->v0 = prim->v1 = posY + 0x30;
        prim->v2 = prim->v3 = posY + 0x50;
        prim->priority = self->zPriority - 1;
        prim->drawMode = 2;
    case 1:
        if (self->ext.et_801D2444.unk85) {
            self->drawFlags = 4;
            self->hitPoints = 0x7FFF;
            self->hitboxState = 1;
            self->velocityX = -0xC000;
            self->velocityY = -0x10000;
            self->step++;
            newEntity = AllocEntity(&g_Entities[32], &g_Entities[47]);
            if (newEntity != NULL) {
                DestroyEntity(newEntity);
                newEntity->entityId = 0x43;
                newEntity->pfnUpdate = func_us_801D2444;
                newEntity->attack = self->attack;
                newEntity->hitboxWidth = self->hitboxWidth;
                newEntity->hitboxHeight = self->hitboxHeight;
                newEntity->hitboxState = 2;
                newEntity->attackElement = 0x8000;
                newEntity->nFramesInvincibility = 0x10;
                newEntity->stunFrames = 4;
                newEntity->hitEffect = 1;
                newEntity->ext.et_801D2444.unkB0.i.hi = 0;
                newEntity->flags = 0x0C000000;
                g_api.func_80118894(newEntity);
                newEntity->step = 4;
                newEntity->ext.et_801D2444.unkEntity = self;
                self->ext.et_801D2444.unkEntity = newEntity;
            }
        }
        break;
    case 2:
        MoveEntity();
        self->rotate -= 0x40;
        self->velocityY += 0x4000;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & 1) {
            if (!self->ext.et_801D2444.unk86) {
                self->ext.et_801D2444.unk86 = 1;
                PlaySfxPositional(0x761);
            } else {
                PlaySfxPositional(0x60E);
            }
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            self->velocityY -= self->velocityY / 2;

            if (abs(self->velocityY) < 0x8000) {
                self->step++;
            }
        }
        break;
    case 3:
        UnkCollisionFunc2(&D_pspeu_0925CAD0);
        self->rotate -= 0x80;
        self->velocityX = -0x1C000;
        break;
    case 4:
        newEntity = self->ext.et_801D2444.unkEntity;
        self->posX.i.hi = newEntity->posX.i.hi;
        self->posY.i.hi = newEntity->posY.i.hi;
        if (newEntity->entityId != 0x2C) {
            DestroyEntity(self);
        }
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - 0xF;
    prim->y0 = prim->y1 = self->posY.i.hi - 0x10;
    prim->x1 = prim->x3 = prim->x0 + 0x20;
    prim->y2 = prim->y3 = prim->y0 + 0x20;
    if (self->ext.et_801D2444.unk85) {
        if (g_Timer & 2) {
            self->palette = D_us_80180A1C[3];
            prim->clut = D_us_80180A1C[3] + 2;
        } else {
            self->palette = D_us_80180A1C[3] + 1;
            prim->clut = D_us_80180A1C[3] + 3;
        }
    }
}

void EntityBonePillarFireBreath(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;
    s16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A10);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            break;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D2444.prim = prim;
        prim->tpage = 0x13;
        prim->clut = 0x221;
        prim->priority = self->zPriority;
        prim->drawMode = 2;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        self->hitboxWidth = 0x15;
        self->hitboxHeight = 0x18;
        if (self->facingLeft) {
            prim->x0 = posX + 0x30;
            prim->x1 = posX - 4;
            prim->x2 = posX + 0x40;
            prim->x3 = posX + 4;
            prim->y0 = posY - 0x60;
            prim->y1 = posY - 8;
            prim->y2 = posY - 0x20;
            prim->y3 = posY + 8;
            self->hitboxOffX = -0x20;
            self->hitboxOffY = -0x18;
        } else {
            prim->x0 = posX - 0x40;
            prim->x1 = posX - 4;
            prim->x2 = posX - 0x30;
            prim->x3 = posX + 4;
            prim->y0 = posY;
            prim->y1 = posY - 8;
            prim->y2 = posY + 0x40;
            prim->y3 = posY + 8;
            self->hitboxOffX = -0x20;
            self->hitboxOffY = 0x1E;
        }
        PlaySfxPositional(0x660);
    case 1:
        if (!AnimateEntity(&D_pspeu_0925CB68, self)) {
            self->hitboxState = 0;
            self->step += 1;
            break;
        }
        prim = self->ext.et_801D2444.prim;
        ptr = D_pspeu_0925F008[self->animCurFrame];
        ptr += 0x8;
        prim->u0 = prim->u2 = *ptr++;
        prim->v0 = prim->v1 = *ptr++;
        prim->u1 = prim->u3 = *ptr++;
        prim->v2 = prim->v3 = *ptr++;
        break;
    case 2:
        for (prim = self->ext.et_801D2444.prim; prim != NULL;
             prim = prim->next) {
            prim->type = 1;
            if (self->facingLeft) {
                posX = (Random() & 0x1F) + 0x10;
            } else {
                posX = -(Random() & 0x1F) - 0x10;
            }
            prim->x0 = self->posX.i.hi + posX;
            posY = self->posY.i.hi - posX;
            prim->y0 = posY - (Random() & 0x1F) + 8;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->r0 = 0xE0;
            prim->b0 = 0x88;
            prim->g0 = 0xA0;
            prim->p2 = (Random() & 7) + 1;
            prim->priority = self->zPriority + 1;
            prim->drawMode = 0x33;
        }
        self->ext.et_801D2444.unk80 = 0x30;
        self->step++;
        // fallthrough
    case 3:
        for (prim = self->ext.et_801D2444.prim; prim != NULL;
             prim = prim->next) {
            if (!(g_Timer % prim->p2)) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
        }
        if (!--self->ext.et_801D2444.unk80) {
            DestroyEntity(self);
        }
    }
}

void func_us_801D2CFC(Entity* self) {
    Collider collider;
    s32 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A04);
        self->hitboxState = 0;
        self->animCurFrame = (self->params & 0xF) + 0x12;
        self->zPriority += self->params & 0xF;
        if (self->params & 1) {
            self->ext.et_801D2444.unk80 = 0x18;
            break;
        }
        self->ext.et_801D2444.unk80 = 0xC;
        break;
    case 1:
        if (!--self->ext.et_801D2444.unk80) {
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += 0x2800;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + D_pspeu_0925CAE8[self->params];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & 1) {
            self->posY.i.hi += collider.unk18;
            self->ext.et_801D2444.unk80 = 0xE;
            self->step++;
        }
        break;
    case 3:
        if (!--self->ext.et_801D2444.unk80) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
        }
    }
}
