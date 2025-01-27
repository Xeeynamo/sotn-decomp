// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

typedef struct {
    u8* animation;
    u8 frameA;
    u8 frameB;
    s16 xOffset;
    s16 yOffset;
} unk_801D0598;

extern s16 D_us_80182BD8[];
extern s16 D_us_80182BE8[];
extern u16 D_us_80182BF0[];
extern u8 D_us_80182BF8[];
extern u8 D_us_80182C04[];
extern u8 D_us_80182C0C[];
extern unk_801D0598 D_us_80182CD4[];
extern s32 D_us_80182D04[];
extern s32 D_us_80182D24[];
extern u8 D_80182D44[];

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
        InitializeEntity(D_us_80180AC4);
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
                    CreateEntityFromEntity(E_ID_45, self, tempEntity);
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
            CreateEntityFromEntity(E_ID_44, self, tempEntity);
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

// Bone Archer arrow
void EntityBoneArcherArrow(Entity* self) {
    Entity* tempEntity;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AD0);
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
                    CreateEntityFromEntity(E_ID_45, self, tempEntity);
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
