// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

static s16 D_us_8018280C[] = {0, 23, 0, 4, 8, -4, -16, 0};
static s16 D_us_8018281C[] = {0, 12, 0, 4, 8, -4, -16, 0};
static s16 D_us_8018282C[] = {16, 8, 255, 0};
static s16 D_us_80182834[] = {0, 23, 8, 0};
static u8 D_us_8018283C[] = {20, 1, 20, 2, 20, 3, 20, 2, 0, 0, 0, 0};
static u8 D_us_80182848[] = {24, 4, 24, 5, 24, 6, 24, 5, 0, 0, 0, 0};
static u8 D_us_80182854[] = {
    24, 7, 24, 8, 24, 9, 24, 8, 0, 0, 0, 0, 18, 8, 18, 9, -1, 0, 0, 0};
static u8 D_us_80182868[] = {8, 7, 8, 10, 4, 7, 32, 10, 0, 0, 0, 0};
static u8 D_us_80182874[] = {
    8, 1, 8, 11, 8, 12, 8, 13, 4, 14, 2, 15, -1, 0, 0, 0};
static u8 D_us_80182884[] = {2, 16, 2, 17, 0, 0, 0, 0};
static u8 D_us_8018288C[] = {2, 18, 2, 19, 2, 18, 2, 19, 0, 0, 0, 0};
static s16 D_us_80182898[] = {0x040, 0x0E0, 0x200, 0x180};
static s16 D_us_801828A0[] = {
    4,  3,  2,  2,  2,  1,  0,  0,  -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2, 0,  0};

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
                    self->velocityX -= FIX(1.0 / 128);
                } else {
                    self->velocityX += FIX(1.0 / 128);
                }
            }
            if (self->animCurFrame == 8) {
                if (self->facingLeft) {
                    self->velocityX += FIX(1.0 / 128);
                } else {
                    self->velocityX -= FIX(1.0 / 128);
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
                    self->velocityX -= FIX(5.0 / 2048);
                } else {
                    self->velocityX += FIX(5.0 / 2048);
                }
            }
            if (self->animCurFrame == 2) {
                if (self->facingLeft) {
                    self->velocityX += FIX(5.0 / 2048);
                } else {
                    self->velocityX -= FIX(5.0 / 2048);
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

void func_us_801CA090(Entity* self) {
    Entity* tempEntity;
    s16 angle;
    s32 dx, dy;

    if ((self->flags & FLAG_DEAD) && self->step > 5) {
        self->step = 5;
        self->step_s = 0;
        self->hitboxState = 0;
        self->ext.et_801C9870.unk7E = 0;
        self->ext.et_801C9870.unk80 = 0;
        PlaySfxPositional(0x715);
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180884);
        self->hitboxOffX = -4;
        self->hitboxOffY = -0xE;
        self->ext.et_801C9870.unk80 = 0;
        break;

    case 1:
        self->facingLeft = (self - 1)->facingLeft;
        if ((self->hitFlags & 3) || (self->flags & FLAG_DEAD)) {
            self->hitboxState = 0;
            self->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[14].hitPoints;
            (self - 1)->step = 4;
            (self - 1)->step_s = 0;
            (self - 1)->animFrameIdx = 0;
            (self - 1)->animFrameDuration = 0;
            self->step++;
        }
        break;

    case 3:
        self->hitboxState = 3;
        if (!self->step_s) {
            self->velocityY = FIX(-0.8125);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (!AnimateEntity(D_us_80182884, self)) {
            self->step_s = 0;
            self->step = 6;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            dx = self->posX.val - tempEntity->posX.val;
            dy = self->posY.val - tempEntity->posY.val;
            angle = ratan2(dx, -dy);
            self->rotZ = angle;
            self->velocityX = rsin(angle) * 0x28;
            self->velocityY = rcos(angle) * -0x28;
            self->ext.et_801C9870.unk7C = 2;
            self->step_s++;
            break;

        case 1:
            if (UnkCollisionFunc3(D_us_8018281C) & 1) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 3;
                }
                DestroyEntity(self);
            } else {
                if (!--self->ext.et_801C9870.unk7C) {
                    tempEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                        tempEntity->params = 1;
                        tempEntity->drawFlags = FLAG_DRAW_ROTZ;
                        tempEntity->rotZ = self->rotZ;
                    }
                    self->ext.et_801C9870.unk7C = 6;
                }
            }
            break;
        }
        break;

    case 6:
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (self->velocityY > FIX(0.5)) {
            self->velocityY = 0;
            self->step = 7;
        }
        break;

    case 7:
        if ((Random() & 0x7F) == 0) {
            self->ext.et_801C9870.unk80 = 1;
        }
        if ((Random() & 0x1F) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_BLOOD_DRIPS, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 8) - 4;
                tempEntity->posY.i.hi += 13;
                tempEntity->pfnUpdate = EntityBloodDrips;
            }
        }
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->ext.et_801C9870.unk7C = 0x60;
            self->step_s++;
        } else {
            MoveEntity();
            AnimateEntity(D_us_80182848, self);
            if (!--self->ext.et_801C9870.unk7C) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
                self->step++;
            }
        }
        break;

    case 8:
        tempEntity = &PLAYER;
        if (!self->step_s) {
            self->ext.et_801C9870.unk7C = 0x40;
            angle = GetAngleBetweenEntitiesShifted(self, tempEntity);
            SetEntityVelocityFromAngle(angle, 6);
            self->step_s++;
        } else {
            if ((Random() & 0x7F) == 0) {
                self->ext.et_801C9870.unk80 = 1;
            }
            if ((Random() & 0x1F) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_BLOOD_DRIPS, self, tempEntity);
                    tempEntity->posX.i.hi += (Random() & 8) - 4;
                    tempEntity->posY.i.hi += 13;
                    tempEntity->pfnUpdate = EntityBloodDrips;
                }
            }
            MoveEntity();
            AnimateEntity(D_us_80182848, self);
            if (!--self->ext.et_801C9870.unk7C) {
                self->velocityY = 0;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
                self->step--;
            }
        }
        break;
    }
    if (self->step < 2) {
        self->posX.i.hi = (self - 1)->posX.i.hi;
        self->posY.i.hi = (self - 1)->posY.i.hi;
    }
    if (self->ext.et_801C9870.unk80 && g_Timer % 3 == 0) {
        self->posY.i.hi += D_us_801828A0[self->ext.et_801C9870.unk7E];
        self->ext.et_801C9870.unk7E++;
        if (self->ext.et_801C9870.unk7E > 0x17) {
            self->ext.et_801C9870.unk7E = 0;
            self->ext.et_801C9870.unk80 = 0;
        }
    }
}
