// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

void func_us_801CDDD8(u8 step) {
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->ext.et_801CDE20.unk7C = 0;
    g_CurrentEntity->ext.et_801CDE20.unk7D = 0;
    g_CurrentEntity->ext.et_801CDE20.unk7E = 0;
    g_CurrentEntity->step = step;
}

extern u16 D_us_80180A7C[];
extern u8* D_us_8018285C[];
extern u8* D_us_80182864[];
extern u8 D_us_8018286C[];
extern u8 D_us_8018287C[];
extern u8 D_us_80182888[];
extern u8 D_us_80182894[];
extern u8 D_us_801828C0[];
extern u16 D_us_801828F8[];
extern s16 D_us_80182900[];
extern s16 D_us_80182910[];
extern s16 D_us_80182930[];
extern s16 D_us_80182940[];
extern s32 D_us_80182950[][2];

void func_us_801CDE20(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step < 0xB)) {
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        if (self->step == 7) {
            self->step = 0xC;
        } else {
            self->step = 0xB;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A7C);
        CreateEntityFromEntity(E_ID_42, self, self + 1);
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80182900) & 1) {
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(D_us_801828C0, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x70) {
            self->ext.et_801CDE20.unk80 = (Random() & 1);
            self->ext.et_801CDE20.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(3);
        }
        break;
    case 3:
        UnkCollisionFunc2(D_us_801828F8);
        if (self->ext.et_801CDE20.unk7D) {
            if (self->animFrameDuration == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi += D_us_80182930[self->animCurFrame];
                } else {
                    self->posX.i.hi -= D_us_80182930[self->animCurFrame];
                }
            }
        } else {
            self->ext.et_801CDE20.unk7D = 1;
        }
        if (CheckColliderOffsets(D_us_80182910, self->facingLeft) == 0) {
            self->ext.et_801CDE20.unk7E |= 1;
        }
        if (AnimateEntity(D_us_8018285C[self->ext.et_801CDE20.unk80], self) ==
            0) {
            if (self->facingLeft) {
                self->posX.i.hi -= D_us_80182930[self->animCurFrame];
            } else {
                self->posX.i.hi += D_us_80182930[self->animCurFrame];
            }
            if (!--self->ext.et_801CDE20.unk7F) {
                self->ext.et_801CDE20.unk7E |= 1;
            }
        }
        if (self->ext.et_801CDE20.unk7E) {
            self->ext.et_801CDE20.unk80 = (Random() & 1);
            self->ext.et_801CDE20.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(4);
        }
        break;
    case 4:
        UnkCollisionFunc2(D_us_801828F8);
        if (self->animFrameDuration == 0) {
            if (self->facingLeft) {
                self->posX.i.hi -= D_us_80182940[self->animCurFrame];
            } else {
                self->posX.i.hi += D_us_80182940[self->animCurFrame];
            }
        }
        if (CheckColliderOffsets(D_us_80182910, self->facingLeft ^ 1) == 0) {
            self->ext.et_801CDE20.unk7E |= 1;
        }
        if (AnimateEntity(D_us_80182864[self->ext.et_801CDE20.unk80], self) ==
            0) {
            if (!--self->ext.et_801CDE20.unk7F) {
                self->ext.et_801CDE20.unk7E |= 1;
            }
        }
        if (self->ext.et_801CDE20.unk7E) {
            self->animCurFrame = 1;
            if (self->facingLeft) {
                self->posX.i.hi += D_us_80182940[self->animCurFrame];
            } else {
                self->posX.i.hi -= D_us_80182940[self->animCurFrame];
            }

            if (self->step_s) {
                func_us_801CDDD8(9);
            } else {
                func_us_801CDDD8(8);
            }
            self->step_s ^= 1;
        }
        break;
    case 5:
        if (AnimateEntity(D_us_8018287C, self) == 0) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.25);
            } else {
                self->velocityX = FIX(-1.25);
            }
            func_us_801CDDD8(7);
        }
        break;
    case 6:
        if (AnimateEntity(D_us_80182888, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.et_801CDE20.unk80 = (Random() & 1);
            self->ext.et_801CDE20.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(3);
        }
        break;
    case 7:
        UnkCollisionFunc2(D_us_801828F8);
        AnimateEntity(D_us_8018286C, self);
        if (self->animCurFrame == 7) {
            if (self->facingLeft) {
                self->velocityX += FIX(5.0 / 32);
            } else {
                self->velocityX -= FIX(5.0 / 32);
            }
        }
        if (self->animCurFrame == 0xC) {
            if (self->facingLeft) {
                self->velocityX -= FIX(5.0 / 32);
            } else {
                self->velocityX += FIX(5.0 / 32);
            }
        }
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_STOMP_HARD_C);
        }
        if (self->ext.et_801CDE20.unk7C++ > 0x60) {
            self->velocityX = 0;
            func_us_801CDDD8(6);
        }
        break;
    case 8:
        if (AnimateEntity(D_us_80182894, self) == 0) {
            func_us_801CDDD8(0xA);
        }
        if (!self->animFrameDuration && self->animFrameIdx == 7) {
            PlaySfxPositional(SFX_CREAK);
        }
        if (!self->animFrameDuration && self->animFrameIdx == 0xB) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }
        break;
    case 9:
        AnimateEntity(D_us_801828C0, self);
        if (self->ext.et_801CDE20.unk7C % 7 == 0) {
            PlaySfxPositional(SFX_BONE_THROW);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                DestroyEntity(tempEntity);
                CreateEntityFromEntity(E_ID_43, self, tempEntity);
                if (self->facingLeft) {
                    tempEntity->velocityX = FIX(1) + (Random() & 7) * 0x2800;
                } else {
                    tempEntity->velocityX = FIX(-1) - (Random() & 7) * 0x2800;
                }
                tempEntity->velocityY = FIX(-5.75);
                tempEntity->posY.i.hi -= 8;
            }
        }
        if (self->ext.et_801CDE20.unk7C++ > 0x60) {
            func_us_801CDDD8(0xA);
        }
        break;
    case 10:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if ((GetDistanceToPlayerX() > 0x70) && (Random() & 1)) {
            func_us_801CDDD8(5);
        } else {
            self->ext.et_801CDE20.unk7F = (Random() & 1) + 1;
            self->ext.et_801CDE20.unk80 = (Random() & 1);
            func_us_801CDDD8(3);
        }
        break;
    case 11:
        for (i = 0; i < 5; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                MakeEntityFromId(E_ID_41, self, tempEntity);
                tempEntity->palette = 0x8160;
                tempEntity->hitboxState = 0;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                    FLAG_POS_CAMERA_LOCKED | FLAG_UNK_2000;
                tempEntity->animCurFrame = i + 0x28;
                if (self->facingLeft) {
                    tempEntity->velocityX = -D_us_80182950[i][0];
                } else {
                    tempEntity->velocityX = D_us_80182950[i][0];
                }
                tempEntity->velocityY = D_us_80182950[i][1];
                tempEntity->step = 0xD;
                if (tempEntity->animCurFrame == 0x28) {
                    tempEntity->drawFlags |= FLAG_DRAW_ROTZ;
                    tempEntity->velocityY -= FIX(2);
                }
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        DestroyEntity(self);
        break;
    case 12:
        for (i = 0; i < 4; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                MakeEntityFromId(E_ID_41, self, tempEntity);
                tempEntity->palette = 0x226;
                tempEntity->hitboxState = 0;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                    FLAG_POS_CAMERA_LOCKED;
                tempEntity->animCurFrame = i + 0x2D;

                if (self->facingLeft) {
                    tempEntity->velocityX = -D_us_80182950[i][0];
                } else {
                    tempEntity->velocityX = D_us_80182950[i][0];
                }
                tempEntity->velocityY = D_us_80182950[i][1];
                tempEntity->step = 0xD;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        DestroyEntity(self);
        break;
    case 13:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotZ += 0x80;
        if (self->ext.et_801CDE20.unk7C++ > 4) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 0;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
            }
            self->ext.et_801CDE20.unk7C = 0;
        }
        break;
    case 32:
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }

        if (g_pads[0].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    if (self->animCurFrame >= 7 && self->animCurFrame < 14) {
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0xD;
        self->hitboxOffX = -0xF;
        self->hitboxOffY = 0xD;
    } else {
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x16;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_4DDD8", func_us_801CE958);

INCLUDE_ASM("st/no1/nonmatchings/unk_4DDD8", func_us_801CEA2C);
