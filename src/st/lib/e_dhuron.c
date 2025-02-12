// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

typedef struct {
    s32 velocityX;
    s32 velocityY;
    s16 rotZ;
    s16 unkA;
} dhuronUnkStruct;

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
            self->attackElement |= 0x4000;
            self->attackElement &= 0xFFBF;
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

INCLUDE_ASM("st/lib/nonmatchings/e_dhuron", func_us_801CC984);
