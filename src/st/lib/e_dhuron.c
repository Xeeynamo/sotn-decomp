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

    if ((self->flags & 0x100) && self->step < 8) {
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
                self->ext.ILLEGAL.u8[0xC] = self->facingLeft ^ 1;
            } else {
                self->ext.ILLEGAL.u8[0xC] = self->facingLeft;
            }
            self->step_s++;
        }
        if (self->animCurFrame == 6 || self->animCurFrame == 1) {
            self->velocityX = 0;
        }
        UnkCollisionFunc2(D_us_80182964);
        if (!AnimateEntity(D_us_8018296C, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.ILLEGAL.u8[0xC] = self->facingLeft;
            tempVar = GetDistanceToPlayerX();
            if (!self->ext.ILLEGAL.u8[0xD] && self->posY.i.hi < 0x100 && tempVar > 0x50 && (Random() & 7) == 0) {
                SetStep(5);
                break;
            }
            if (tempVar < 0x40) {
                SetStep(4);
                if (self->ext.ILLEGAL.u8[0xD]) {
                    SetStep(6);
                }
            }
        }
        if (self->ext.ILLEGAL.u8[0xC]) {
            self->velocityX = 0x28000;
        } else {
            self->velocityX = -0x28000;
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
            if (self->ext.ILLEGAL.u8[0xC]) {
                self->velocityX = 0x30000;
            } else {
                self->velocityX = -0x30000;
            }
            if (!self->animFrameDuration) {
                PlaySfxPositional(0x66D);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801829C4, self)) {
                self->ext.ILLEGAL.s16[4] = 8;
                SetSubStep(1);
            }
            break;

        case 1:
            if (!AnimateEntity(D_us_801829D4, self)) {
                self->ext.ILLEGAL.s16[4]--;
                if ((((GetSideToPlayer() & 1) == self->facingLeft)) || (GetDistanceToPlayerX() > 0x60) || !self->ext.ILLEGAL.s16[4]) {
                    SetSubStep(2);
                }
            }
            if (!self->animFrameDuration && self->animFrameIdx == 6) {
                PlaySfxPositional(0x66D);
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
                self->ext.ILLEGAL.s16[4] = 0x20;
                self->step_s++;
            }
            if (self->animFrameIdx == 10 && !self->animFrameDuration) {
                PlaySfxPositional(0x665);
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(0x35U, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    tempEntity->zPriority = self->zPriority - 1;
                    tempEntity->ext.ILLEGAL.u32[8] = (u32) self;
                }
            }
            break;

        case 1:
            if (!--self->ext.ILLEGAL.s16[4]) {
                self->ext.ILLEGAL.u8[0xD] = 1;
                (self + 1)->ext.ILLEGAL.u8[0xD] = 1;
                self->drawMode |= 0x30;
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
                CreateEntityFromEntity(0x36, self, tempEntity);
                tempEntity->params = i;
                tempEntity->facingLeft = self->facingLeft;
            } else {
                break;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(2, self, tempEntity);
            tempEntity->params = 3;
        }
        PlaySfxPositional(0x629);
        DestroyEntity(self);
        return;
    }
    if (self->ext.ILLEGAL.u8[0xD]) {
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
