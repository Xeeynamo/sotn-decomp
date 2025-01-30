// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

typedef struct {
    u8* animation;
    u8 frameA;
    u8 frameB;
    s16 xOffset;
    s16 yOffset;
    s16 pad;
} unk_801D0598; /* size=0xC */

static s16 D_us_80182BD8[] = {0, 16, 0, 4, 8, -4, -16, 0};
static s16 D_us_80182BE8[] = {0, 16, 12, 0};
static u16 D_us_80182BF0[] = {-12, 16, 0, -16};
static u8 D_us_80182BF8[] = {8, 11, 7, 12, 8, 13, 7, 12, 0, 0, 0, 0};
static u8 D_us_80182C04[] = {5, 13, 5, 12, 5, 11, -1, 0};
static u8 D_us_80182C0C[] = {5, 14, 5, 13, 5, 1, -1, 0};
static u8 D_us_80182C14[] = {
    32, 1, 1, 2, 1, 3, 1,  4, 17, 5, 28, 6,  1, 7, 1, 8, 1, 7, 1,  8, 1,  7,
    2,  8, 2, 7, 3, 8, 32, 7, 8,  9, 12, 10, 7, 5, 4, 4, 4, 3, 16, 2, -1, 0};
static u8 D_us_80182C40[] = {
    17, 1,  28, 15, 1, 16, 1,  17, 1, 16, 1, 17, 1, 16, 2,  17, 2,  16,
    3,  17, 32, 16, 8, 9,  12, 10, 7, 5,  4, 4,  4, 3,  16, 2,  -1, 0};
static u8 D_us_80182C64[] = {
    12, 10, 32, 18, 28, 19, 1,  20, 1, 21, 1, 20, 1, 21, 1, 20, 2,
    21, 2,  20, 3,  21, 16, 20, 16, 1, 1,  2, 1,  3, 1,  4, 16, 5,
    28, 6,  1,  7,  1,  8,  1,  7,  1, 8,  1, 7,  2, 8,  2, 7,  3,
    8,  32, 7,  8,  9,  12, 10, 7,  5, 4,  4, 4,  3, 16, 2, -1, 0};
static u8 D_us_80182CA8[] = {
    28, 11, 1,  33, 1,  34, 16, 35, 28, 36, 1,  37, 1,  38, 1,
    37, 1,  38, 1,  37, 2,  38, 2,  37, 3,  38, 32, 37, 8,  39,
    12, 40, 3,  35, 3,  34, 3,  33, 16, 11, -1, 0,  0,  0};
static unk_801D0598 D_us_80182CD4[] = {
    {.animation = D_us_80182C14,
     .frameA = 6,
     .frameB = 0,
     .xOffset = 10,
     .yOffset = -2},
    {.animation = D_us_80182C40,
     .frameA = 15,
     .frameB = 0,
     .xOffset = 10,
     .yOffset = 2},
    {.animation = D_us_80182CA8,
     .frameA = 36,
     .frameB = 0,
     .xOffset = 8,
     .yOffset = -15},
    {.animation = D_us_80182C64,
     .frameA = 19,
     .frameB = 6,
     .xOffset = 10,
     .yOffset = 2}};
static s32 D_us_80182D04[] = {FIX(0.75), FIX(1.75), FIX(1.5),  FIX(1.0),
                              FIX(2.0),  FIX(1.75), FIX(0.75), FIX(1.5)};
static s32 D_us_80182D24[] = {FIX(-5.0), FIX(-3.0),   FIX(-2.0), FIX(-3.0),
                              FIX(-4.0), FIX(-0.875), FIX(-4.0), FIX(-2.0)};
static u8 D_80182D44[] = {48, 32, 20, 12, 24, 16, 20, 40};

void EntityBoneArcher(Entity* self) {
    unk_801D0598* var_s2;
    Entity* tempEntity;
    s32 step;
    s32 i;
    u8* anim;
    s32 tempVar;
    u8 unused;

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        SetStep(11);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArcher);
        if (self->params) {
            self->hitboxState = 0;
            self->animCurFrame = self->params + 0x18;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->step = 12;
        } else {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182BD8) & 1) {
            self->step = 2;
        }
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->ext.boneArcher.unk84 = 0x40;
            self->step_s++;
        }
        self->animCurFrame = 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(13);
        }
        if (!--self->ext.boneArcher.unk84) {
            step = self->ext.boneArcher.unk8C;
            step += 7;
            SetStep(step);
            if (++self->ext.boneArcher.unk8C > 2) {
                self->ext.boneArcher.unk8C = 0;
            }
        }
        break;

    case 13:
        if (!AnimateEntity(D_us_80182C04, self)) {
            SetStep(5);
        }
        break;

    case 14:
        if (!AnimateEntity(D_us_80182C0C, self)) {
            SetStep(3);
        }
        break;

    case 4:
    case 5:
        if (!self->step_s) {
            self->ext.boneArcher.unk86 = 0x40;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182BF8, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        step = 0;
        tempVar = UnkCollisionFunc2(D_us_80182BE8);
        if (self->facingLeft) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }
        if (self->step == 5) {
            self->velocityX = -self->velocityX;
        }
        switch (self->step) {
        case 4:
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(5);
            }
            if (tempVar & 0x80) {
                tempVar = UnkCollisionFunc(D_us_80182BF0, 2);
                if (tempVar & 2) {
                    SetStep(6);
                }
            }
            break;
        case 5:
            if (GetDistanceToPlayerX() > 0x80) {
                SetStep(4);
            }
            if (tempVar & 0x80) {
                self->animCurFrame = 1;
                self->ext.boneArcher.unk86 = 1;
                step = 0xA;
            }
            break;
        }
        if (!--self->ext.boneArcher.unk86) {
            if (step == 0) {
                step = self->ext.boneArcher.unk8C;
                step += 7;
            }
            SetStep(step);
            if (++self->ext.boneArcher.unk8C > 2) {
                self->ext.boneArcher.unk8C = 0;
            }
        }
        break;

    case 6:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = FIX(-4.0);
            self->step_s++;
            self->animCurFrame = 0xE;
        }
        if (UnkCollisionFunc3(D_us_80182BD8) & 1) {
            SetStep(4);
        }
        break;

    case 7:
    case 8:
    case 10:
    case 9:
        switch (self->step_s) {
        case 0:
            if (self->step == 9) {
                if (self->hitboxHeight == 0xE) {
                    self->step_s = 2;
                } else {
                    self->step_s = 3;
                }
            } else {
                if (self->hitboxHeight == 0x16) {
                    self->step_s = 1;
                } else {
                    self->step_s = 3;
                }
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80182C0C, self)) {
                SetSubStep(3);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80182C04, self)) {
                SetSubStep(3);
            }
            break;
        case 3:
            tempVar = self->step - 7;
            var_s2 = &D_us_80182CD4[tempVar];
            anim = var_s2->animation;
            unused = var_s2->frameA;
            switch (self->step) {
            case 7:
                if (!self->animFrameDuration && self->animFrameIdx == 5) {
                    PlaySfxPositional(SFX_CREAK);
                }
                break;
            case 8:
                if (!self->animFrameDuration && self->animFrameIdx == 1) {
                    PlaySfxPositional(SFX_CREAK);
                }
                break;
            case 10:
                if (!self->animFrameDuration && self->animFrameIdx == 2) {
                    PlaySfxPositional(SFX_CREAK);
                }
                break;
            case 9:
                if (!self->animFrameDuration && self->animFrameIdx == 4) {
                    PlaySfxPositional(SFX_CREAK);
                }
                break;
            }
            if (!AnimateEntity(anim, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.boneArcher.unk84 = 0x40;
                if (self->step == 9) {
                    SetStep(14);
                } else {
                    SetStep(3);
                }
            } else if (!self->animFrameDuration) {
                if (self->animCurFrame != var_s2->frameA) {
                    if (self->animCurFrame == var_s2->frameB) {
                        tempVar = 1;
                    } else {
                        break;
                    }
                } else {
                    tempVar = 0;
                }
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    PlaySfxPositional(SFX_ARROW_SHOT_C);
                    CreateEntityFromEntity(
                        E_BONE_ARCHER_ARROW, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    if (tempVar != 0) {
                        var_s2 = &D_us_80182CD4[0];
                    }
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi += var_s2->xOffset;
                    } else {
                        tempEntity->posX.i.hi += var_s2->xOffset;
                    }
                    tempEntity->posY.i.hi += var_s2->yOffset;
                }
            }
            break;
        }
        break;

    case 11:
        tempVar = GetSideToPlayer() & 1;
        for (i = 0; i < 8; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity == NULL) {
                break;
            }
            CreateEntityFromEntity(E_BONE_ARCHER, self, tempEntity);
            tempEntity->facingLeft = self->facingLeft;
            tempEntity->params = i + 1;
            if (tempVar != 0) {
                tempEntity->velocityX = D_us_80182D04[i];
            } else {
                tempEntity->velocityX = -D_us_80182D04[i];
            }
            tempEntity->velocityY = D_us_80182D24[i];
            tempEntity->ext.boneArcher.unk88 = D_80182D44[i];
        }

        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            PlaySfxPositional(SFX_SKELETON_DEATH_B);
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        DestroyEntity(self);
        return;

    case 12:
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!--self->ext.boneArcher.unk88) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 0;
            }
            DestroyEntity(self);
            return;
        }
        break;

    case 0xFF:
#include "../pad2_anim_debug.h"
    }
    tempVar = self->animCurFrame;
    if ((tempVar > 10 && tempVar < 15) || tempVar > 32) {
        self->hitboxOffX = 4;
        self->hitboxOffY = -7;
        self->hitboxWidth = 8;
        self->hitboxHeight = 22;
    } else {
        self->hitboxOffX = 0;
        self->hitboxOffY = 1;
        self->hitboxWidth = 17;
        self->hitboxHeight = 14;
    }
}

void EntityBoneArcherArrow(Entity* self) {
    Entity* tempEntity;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArcherArrow);
        self->animCurFrame = 0x16;
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        if (self->params) {
            self->hitboxState = 0;
            self->drawFlags |= FLAG_DRAW_ROTZ;
            self->animCurFrame += self->params;
            if (self->params == 1) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->step = 3;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            break;
        }
    case 1:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            for (i = 0; i < 2; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_BONE_ARCHER_ARROW, self, tempEntity);
                    tempEntity->params = i + 1;
                }
            }
            DestroyEntity(self);
            return;
        }
        if (self->hitFlags & 0x80) {
            tempEntity = &PLAYER;
            self->ext.boneArcher.unk94 =
                tempEntity->posX.i.hi - self->posX.i.hi;
            self->ext.boneArcher.unk96 =
                tempEntity->posY.i.hi - self->posY.i.hi;
            self->ext.boneArcher.unk88 = 0x20;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        tempEntity = &PLAYER;
        self->posX.i.hi = tempEntity->posX.i.hi - self->ext.boneArcher.unk94;
        self->posY.i.hi = tempEntity->posY.i.hi - self->ext.boneArcher.unk96;
        if (!--self->ext.boneArcher.unk88) {
            DestroyEntity(self);
            return;
        }
        break;

    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->params == 1) {
            self->rotZ -= 0x20;
        } else {
            self->rotZ += 0x20;
        }
        break;
    }
}
