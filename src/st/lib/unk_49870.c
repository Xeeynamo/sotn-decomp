// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern s16 D_us_8018280C[];
extern s16 D_us_8018282C[];
extern s16 D_us_80182834[];
extern u8 D_us_8018283C[];
extern u8 D_us_80182854[];
extern u8 D_us_80182868[];
extern u8 D_us_80182874[];
extern u8 D_us_8018288C[];
extern s16 D_us_80182898[];

void func_us_801C9870(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if (!self->ext.et_801C9870.unk81 && (self->hitFlags & 3) &&
        self->step != 3) {
        self->hitboxState = 0;
        self->hitPoints = g_api.enemyDefs[15].hitPoints;
        SetStep(3);
        PlaySfxPositional(0x714);
    }
    if (self->flags & FLAG_DEAD) {
        if (!self->ext.et_801C9870.unk81) {
            self->hitboxState = 0;
            self->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[15].hitPoints;
            SetStep(3);
            PlaySfxPositional(0x714);
        } else if (self->step != 7) {
            self->hitboxState = 0;
            SetStep(7);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180878);
        self->zPriority -= 2;
        self->hitboxOffX = 1;
        self->hitboxOffY = 10;
        tempEntity = self + 1;
        CreateEntityFromEntity(E_ID_1C, self, tempEntity);
        self->animCurFrame = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_8018280C) & 1) {
            self->step_s = 0;
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.125);
            } else {
                self->velocityX = FIX(-0.125);
            }
            self->step_s++;
            break;

        case 1:
            AnimateEntity(D_us_8018283C, self);
            UnkCollisionFunc2(D_us_80182834);
            if (CheckColliderOffsets(D_us_8018282C, self->facingLeft)) {
                self->velocityX = 0;
            }
            if (self->ext.et_801C9870.unk7C++ > 0x80) {
                self->ext.et_801C9870.unk7C = 0;
                self->step_s--;
            }
            if (self->animCurFrame == 7) {
                if (self->facingLeft) {
                    self->velocityX -= 0x200;
                } else {
                    self->velocityX += 0x200;
                }
            }
            if (self->animCurFrame == 8) {
                if (self->facingLeft) {
                    self->velocityX += 0x200;
                } else {
                    self->velocityX -= 0x200;
                }
            }
            break;
        }
        break;

    case 3:
        if (!self->step_s) {
            PlaySfxPositional(0x716);
            self->ext.et_801C9870.unk81 = 1;
            for (i = 0; i < 2; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_BLOOD_SPLATTER, self, tempEntity);
                    tempEntity->facingLeft = i;
                    tempEntity->posX.i.hi += 4 - (i * 8);
                }
            }
            tempEntity = self + 1;
            tempEntity->step = 2;
            tempEntity->hitboxState = 0;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182874, self)) {
            tempEntity = self + 1;
            tempEntity->step = 3;
            tempEntity->step_s = 0;
            tempEntity->hitboxOffX = 0;
            tempEntity->hitboxOffY = 0;
            tempEntity->facingLeft = self->facingLeft;
            tempEntity->posY.i.hi = self->posY.i.hi - 0x1A;
            tempEntity->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[14].hitPoints;
            self->animCurFrame = 0x12;
            self->hitboxState = 3;
            SetStep(5);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            (self + 1)->step = 3;
            (self + 1)->animCurFrame = 0x10;
            (self + 1)->animFrameIdx = 0;
            (self + 1)->animFrameDuration = 0;
            (self + 1)->facingLeft = self->facingLeft;
            (self + 1)->zPriority -= 8;
            (self + 1)->posY.i.hi = self->posY.i.hi - 0xA;
            self->ext.et_801C9870.unk81 = 1;
            self->animCurFrame = 0x12;
            self->ext.et_801C9870.unk7C = 8;
            self->ext.et_801C9870.unk7E = 0;
            self->step_s++;
            break;

        case 1:
            if (!--self->ext.et_801C9870.unk7C) {
                self->ext.et_801C9870.unk7E = 0;
                self->ext.et_801C9870.unk7C = 2;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.et_801C9870.unk7C) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 1;
                    tempEntity->posY.i.hi -= self->ext.et_801C9870.unk7E * 8;
                }
                self->ext.et_801C9870.unk7C = 6;
                self->ext.et_801C9870.unk7E++;
                if (self->ext.et_801C9870.unk7E > 1) {
                    PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
                    DestroyEntity(self + 1);
                    SetStep(5);
                }
            }
            break;
        }
        break;

    case 5:
        if (!AnimateEntity(D_us_8018288C, self)) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->step++;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.et_801C9870.unk7C = D_us_80182898[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0 / 16);
            } else {
                self->velocityX = FIX(-1.0 / 16);
            }
            self->step_s++;
            break;

        case 1:
            AnimateEntity(D_us_80182854, self);
            UnkCollisionFunc2(D_us_80182834);
            if (CheckColliderOffsets(D_us_8018282C, self->facingLeft)) {
                self->velocityX = 0;
            }
            if (self->animCurFrame == 1) {
                if (self->facingLeft) {
                    self->velocityX -= 0xA0;
                } else {
                    self->velocityX += 0xA0;
                }
            }
            if (self->animCurFrame == 2) {
                if (self->facingLeft) {
                    self->velocityX += 0xA0;
                } else {
                    self->velocityX -= 0xA0;
                }
            }
            if (!--self->ext.et_801C9870.unk7C) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80182868, self)) {
                self->facingLeft = Random() & 1;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
            }
            break;
        }
        break;

    case 7:
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
        DestroyEntity(self);
        break;

    case 16:
#include "../pad2_anim_debug.h"
    }
}

INCLUDE_ASM("st/lib/nonmatchings/unk_49870", func_us_801CA090);
