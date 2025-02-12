// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

typedef struct {
    s32 velocityX;
    s32 velocityY;
    s16 rotZ;
    s16 unkA;
} dhuronUnkStruct;

extern u16 g_EInitInteractable[];
extern u16 D_us_8018089C[];
extern u16 D_us_801808A8[];
extern u16 D_us_801808B4[];

extern s16 D_us_80182954[];
extern s16 D_us_80182964[];
extern u8 D_us_8018296C[];
extern u8 D_us_80182984[];
extern u8 D_us_801829A4[];
extern u8 D_us_801829C4[];
extern u8 D_us_801829D4[];
extern u8 D_us_801829F0[];
extern s8 D_us_801829FC[][4];
extern u8 D_us_80182A14[];
extern s8 D_us_80182A30[][4];
extern u8 D_us_80182A48[];
extern dhuronUnkStruct D_us_80182A64[];
extern u8 D_us_80182ACC[];

// Dhuron
void func_us_801CC054(Entity* self) {
    Entity* tempEntity;
    s32 tempVar;
    s32 i;
    s8* hitboxPtr;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018089C);
        tempEntity = self + 1;
        CreateEntityFromEntity(E_ID_34, self, tempEntity);
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182954) & 1) {
            SetStep(2);
        }
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (GetDistanceToPlayerX() < 0x50) {
                self->ext.dhuron.unk88 = self->facingLeft ^ 1;
            } else {
                self->ext.dhuron.unk88 = self->facingLeft;
            }
            self->step_s++;
        }
        if (self->animCurFrame == 6 || self->animCurFrame == 1) {
            self->velocityX = 0;
        }
        UnkCollisionFunc2(D_us_80182964);
        if (!AnimateEntity(D_us_8018296C, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.dhuron.unk88 = self->facingLeft;
            tempVar = GetDistanceToPlayerX();
            if (!self->ext.dhuron.unk89 && self->posY.i.hi < 0x100 &&
                tempVar > 0x50 && (Random() & 7) == 0) {
                SetStep(5);
                break;
            }
            if (tempVar < 0x40) {
                SetStep(4);
                if (self->ext.dhuron.unk89) {
                    SetStep(6);
                }
            }
        }
        if (self->ext.dhuron.unk88) {
            self->velocityX = FIX(2.5);
        } else {
            self->velocityX = FIX(-2.5);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->velocityX = 0;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182984, self)) {
            SetStep(3);
            self->animFrameIdx = 6;
        }
        UnkCollisionFunc2(D_us_80182964);
        self->velocityX -= self->velocityX / 16;
        if (self->animFrameIdx == 5) {
            if (self->ext.dhuron.unk88) {
                self->velocityX = FIX(3.0);
            } else {
                self->velocityX = FIX(-3.0);
            }
            if (!self->animFrameDuration) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801829C4, self)) {
                self->ext.dhuron.unk84 = 8;
                SetSubStep(1);
            }
            break;

        case 1:
            if (!AnimateEntity(D_us_801829D4, self)) {
                self->ext.dhuron.unk84--;
                if (((GetSideToPlayer() & 1) == self->facingLeft) ||
                    (GetDistanceToPlayerX() > 0x60) ||
                    !self->ext.dhuron.unk84) {
                    SetSubStep(2);
                }
            }
            if (!self->animFrameDuration && self->animFrameIdx == 6) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_801829F0, self)) {
                SetStep(3);
            }
            break;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801829A4, self)) {
                self->ext.dhuron.unk84 = 0x20;
                self->step_s++;
            }
            if (self->animFrameIdx == 10 && !self->animFrameDuration) {
                PlaySfxPositional(SFX_THUNDER_B);
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_35, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    tempEntity->zPriority = self->zPriority - 1;
                    tempEntity->ext.dhuron.unk9C = self;
                }
            }
            break;

        case 1:
            if (!--self->ext.dhuron.unk84) {
                self->ext.dhuron.unk89 = 1;
                (self + 1)->ext.dhuron.unk89 = 1;
                self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
                SetStep(3);
            }
            break;
        }
        break;

    case 8:
        self->hitboxState = 0;
        for (i = 0; i < 7; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID_36, self, tempEntity);
                tempEntity->params = i;
                tempEntity->facingLeft = self->facingLeft;
            } else {
                break;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 3;
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_A);
        DestroyEntity(self);
        return;
    }
    if (self->ext.dhuron.unk89) {
        if (g_Timer & 2) {
            self->palette = 0x201;
        } else {
            self->palette = 0x202;
        }
    }
    hitboxPtr = D_us_801829FC[0];
    tempVar = D_us_80182A14[self->animCurFrame];
    hitboxPtr += tempVar * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

// Dhuron death parts
void func_us_801CC6B0(Entity* self) {
    s8* hitboxPtr;
    Entity* tempEntity;
    s32 tempVar;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808A8);
        break;

    case 1:
        tempEntity = self - 1;
        self->facingLeft = tempEntity->facingLeft;
        self->posX.i.hi = tempEntity->posX.i.hi;
        self->posY.i.hi = tempEntity->posY.i.hi;
        hitboxPtr = D_us_80182A30[0];
        tempVar = D_us_80182A48[tempEntity->animCurFrame];
        hitboxPtr += tempVar * 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr++;
        if (self->ext.dhuron.unk89) {
            self->attackElement |= ELEMENT_THUNDER;
            self->attackElement &= ~ELEMENT_CUT;
            self->attack *= 2;
            self->ext.dhuron.unk89 = 0;
        }
        if (tempEntity->entityId != E_ID_33) {
            DestroyEntity(self);
        }
        break;
    }
}

// Dhuron death
void func_us_801CC7BC(Entity* self) {
    Collider collider;
    dhuronUnkStruct* ptr;
    s32 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808B4);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = self->params + 0x1B;
        self->zPriority += self->params;
        ptr = &D_us_80182A64[self->params];
        if (self->facingLeft) {
            self->velocityX = ptr->velocityX;
        } else {
            self->velocityX = -ptr->velocityX;
        }
        self->velocityY = ptr->velocityY;
        self->ext.dhuron.unk84 = ptr->unkA;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(2.5 / 16);
        ptr = &D_us_80182A64[self->params];
        self->rotZ += ptr->rotZ;
        if (!--self->ext.dhuron.unk84) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->step = 0;
            self->entityId = E_EXPLOSION;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        }
        if (self->params == 6) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 4;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects != EFFECT_NONE) {
                PlaySfxPositional(SFX_SKULL_KNOCK_A);
                self->posY.i.hi += collider.unk18;
                self->velocityY = -self->velocityY;
                self->velocityY -= self->velocityY / 4;
            }
        }
        break;
    }
}

void func_us_801CC984(Entity* self) {
    Primitive* prim;
    Primitive* prim2;
    s32 i;
    u8 condition;
    s16 angle, angle2;
    Entity* tempEntity;
    s32 primIndex;
    s32 multiplier;
    s16 temp;
    s32 posX, posY;

    switch (self->step) {
    case 0:
        self->posY.i.hi = 0;
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.dhuron.unk7C = prim;
        self->ext.dhuron.unk80 = prim;
        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            prim->r0 = prim->g0 = prim->b0 = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            i++;
            if (i > 5) {
                i = 0;
            }
        }
        prim = self->ext.dhuron.unk7C;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.dhuron.unk80 = prim;
        self->ext.dhuron.unk84 = 0xC00;
        LOH(self->ext.dhuron.unk88) = 0;
        break;

    case 1:
        prim = self->ext.dhuron.unk80;
        angle2 = self->ext.dhuron.unk84;
        tempEntity = self->ext.dhuron.unk9C;
        posX = tempEntity->posX.i.hi;
        if (tempEntity->facingLeft) {
            posX -= 7;
        } else {
            posX += 7;
        }
        posY = tempEntity->posY.i.hi - 0x30;
        posX -= prim->x2;
        posY -= prim->y2;
        if (abs(posX) < 8 && abs(posY) < 8) {
            self->step = 2;
            return;
        }
        if (abs(posX) < 0x40 && abs(posY) < 0x40) {
            condition = true;
        } else {
            condition = false;
        }
        if (!LOH(self->ext.dhuron.unk88)) {
            LOH(self->ext.dhuron.unk88) = 4;
            if (condition) {
                LOH(self->ext.dhuron.unk88) = 2;
            }
            temp = ratan2(-posY, posX);
            angle = temp - angle2;
            if (angle > 0x800) {
                angle = 0x1000 - angle;
            }
            if (angle < -0x800) {
                angle = angle + 0x1000;
            }
            if (!condition) {
                angle /= 4;
            } else {
                angle /= 2;
            }
            self->ext.dhuron.unk86 = angle;
        }
        angle2 += self->ext.dhuron.unk86;
        if (!condition) {
            angle2 += 0x180 - ((Random() & 3) << 8);
        }
        angle2 &= 0xFFF;
        prim2 = prim->next;
        if (prim2 == NULL) {
            self->step = 2;
            return;
        }
        LOW(prim2->x0) = LOW(prim->x2);
        LOW(prim2->x1) = LOW(prim->x3);
        self->ext.dhuron.unk84 = angle2;
        self->ext.dhuron.unk80 = prim2;
        posX = (rcos(angle2) * 0xC) >> 0xC;
        posY = -((rsin(angle2) * 0xC) >> 0xC);
        prim2->x2 = prim2->x0 + posX;
        prim2->y2 = prim2->y0 + posY;
        angle = angle2 - 0x400;
        multiplier = 0x10;
        posX = (rcos(angle) * multiplier) >> 0xC;
        posY = -((rsin(angle) * multiplier) >> 0xC);
        prim2->x3 = prim2->x2 + posX;
        prim2->y3 = prim2->y2 + posY;
        prim2->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        LOH(self->ext.dhuron.unk88)--;
        break;

    case 2:
        prim = self->ext.dhuron.unk7C;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        tempEntity = self->ext.dhuron.unk9C;
        tempEntity->ext.dhuron.unk89 = 1;
        posY = tempEntity->posY.i.hi;
        posX = tempEntity->posX.i.hi;
        self->posY.i.hi = posY + 0x18;
        self->posX.i.hi = posX;
        self->drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY;
        self->rotY = 0x180;
        self->unk6C = 0x80;
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->palette = PAL_OVL(0x15B);
        self->unk5A = 0x4E;
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = 0;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->step = 3;
        break;

    case 3:
        if (!AnimateEntity(D_us_80182ACC, self)) {
            self->step = 4;
        }
        break;

    case 4:
        self->posY.val -= FIX(0.25);
        self->unk6C -= 8;
        if (!self->unk6C) {
            DestroyEntity(self);
        }
        break;
    }

    tempEntity = self->ext.dhuron.unk9C;
#ifdef VERSION_PSP
    if (tempEntity != NULL && tempEntity->entityId != E_ID_33) {
#else
    if (tempEntity->entityId != E_ID_33) {
#endif
        DestroyEntity(self);
        return;
    }
}
