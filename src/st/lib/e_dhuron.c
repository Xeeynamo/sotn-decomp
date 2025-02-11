// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern u16 D_us_8018089C[];
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
INCLUDE_ASM("st/lib/nonmatchings/e_dhuron", func_us_801CC6B0);

// Dhuron death
INCLUDE_ASM("st/lib/nonmatchings/e_dhuron", func_us_801CC7BC);
