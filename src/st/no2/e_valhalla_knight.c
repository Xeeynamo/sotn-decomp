// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

extern s16 D_us_80182028[];
extern s16 D_us_80182038[];
extern u8 D_us_80182040[];
extern u8 D_us_8018204C[];
extern u8 D_us_80182058[];
extern u8 D_us_80182064[];
extern s8 D_us_80182074[];
extern Point16 D_us_801820F4[];

void EntityValhallaKnight(Entity* self) {
    Entity* tempEntity;
    Entity* tempEntity2;
    s32 i;
    s32 posX;
    s8* hitboxPtr;
    s32 temp_a0_2;

    if (self->flags & FLAG_DEAD) {
        SetStep(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitValhallaKnight);
        self->animCurFrame = 1;
        self->ext.valhallaKnight.unk84 = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_35, tempEntity);
        tempEntity->params = 0;
        self->unk60 = tempEntity;
        self->unk5C = NULL;
        tempEntity = self + 2;
        CreateEntityFromCurrentEntity(E_UNK_35, tempEntity);
        tempEntity->params = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80182028) & 1) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(2);
        }
        break;

    case 2:
        if (!self->step_s) {
            self->ext.valhallaKnight.unk80 = 0x80;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_8018204C, self)) {
            PlaySfxPositional(0x719);
        }
        temp_a0_2 = UnkCollisionFunc2(D_us_80182038);
        if (self->facingLeft) {
            self->velocityX = FIX(-2.5);
        } else {
            self->velocityX = FIX(2.5);
        }
        if (temp_a0_2 == 0x80) {
            SetStep(5);
            self->step_s = 2;
        }
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->facingLeft) {
            posX = self->ext.valhallaKnight.unk84 - posX;
        } else {
            posX = posX - self->ext.valhallaKnight.unk84;
        }
        if (posX > 0x60) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            PlaySfxPositional(0x718);
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_80182038);
        self->velocityX -= self->velocityX / 0x20;
        if (!self->poseTimer) {
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, -4, 40, 0, 4);
            } else {
                EntityGreyPuffSpawner(self, 5, 3, 4, 40, 0, -4);
            }
        }
        if (!AnimateEntity(D_us_80182058, self)) {
            self->facingLeft ^= 1;
            tempEntity2 = &PLAYER;
            if (tempEntity2->velocityY != 0 && GetDistanceToPlayerX() < 0x80) {
                self->animCurFrame = 1;
                SetStep(5);
            } else {
                self->animCurFrame = 6;
                SetStep(2);
            }
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->ext.valhallaKnight.unk80 = 0x10;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!AnimateEntity(D_us_80182040, self)) {
                PlaySfxPositional(0x719);
            }
            UnkCollisionFunc2(D_us_80182038);
            if (!self->ext.valhallaKnight.unk80) {
                if (GetDistanceToPlayerX() < 0x50) {
                    self->step_s = 2;
                }
            } else {
                self->ext.valhallaKnight.unk80--;
            }
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->facingLeft) {
                posX = self->ext.valhallaKnight.unk84 - posX;
            } else {
                posX = posX - self->ext.valhallaKnight.unk84;
            }
            if (posX > 0x60) {
                SetStep(3);
            }
            break;

        case 2:
            self->velocityY = FIX(-3.0);
            if (self->facingLeft) {
                self->velocityX = FIX(-3.5);
            } else {
                self->velocityX = FIX(3.5);
            }
            self->animCurFrame = 15;
            self->step_s++;
            /* fallthrough */
        case 3:
            UnkCollisionFunc3(D_us_80182028);
            self->velocityY -= FIX(5.0 / 32);
            if (self->velocityY > FIX(-0.75)) {
                self->animCurFrame = 16;
            }
            if (self->velocityY > FIX(0.75)) {
                self->animCurFrame = 17;
                self->step_s++;
            }
            break;
        case 4:
            if (UnkCollisionFunc3(D_us_80182028) & 1) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, -4, 40, 0, 4);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, 4, 40, 0, -4);
                }
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.5);
                } else {
                    self->velocityX = FIX(2.5);
                }
                SetSubStep(5);
            }
            break;
        case 5:
            UnkCollisionFunc2(D_us_80182038);
            if (!AnimateEntity(D_us_80182064, self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 6:
        for (i = 0; i < 3; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                if (self->facingLeft) {
                    tempEntity->posX.i.hi -= D_us_801820F4[i].x;
                } else {
                    tempEntity->posX.i.hi += D_us_801820F4[i].x;
                }
                tempEntity->posY.i.hi += D_us_801820F4[i].y;
                tempEntity->params = 3;
            }
        }
        for (i = 0; i < 13; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_UNK_36, self, tempEntity);
                tempEntity->params = i;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->velocityX = self->velocityX;
                tempEntity->velocityY = self->velocityY;
            }
        }
        g_api.PlaySfx(SFX_EXPLODE_A);
        DestroyEntity(self);
        return;

    case 0xFF:
#include "../pad2_anim_debug.h"
    }
    hitboxPtr = D_us_80182074;
    if (self->animCurFrame == 11 || self->animCurFrame == 12) {
        hitboxPtr += 4;
    }
    if (self->animCurFrame == 13 || self->animCurFrame == 14) {
        hitboxPtr += 8;
    }
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

INCLUDE_ASM("st/no2/nonmatchings/e_valhalla_knight", func_us_801C8954);

INCLUDE_ASM("st/no2/nonmatchings/e_valhalla_knight", func_us_801C8AAC);
