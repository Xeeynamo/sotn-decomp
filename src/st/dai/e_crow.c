// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static u8 anim_1[] = {38, 1, 6, 2, 6, 3, 6, 2, 6, 3, 6, 2, 0, 0, 0, 0};
static u8 anim_2[] = {7, 4, 1, 5, 10, 6, 7, 5, 0, 0, 0, 0};
static u8 anim_3[] = {3, 4, 1, 5, 6, 6, 3, 5, 0, 0, 0, 0};
static u8 anim_4[] = {6, 4, 6, 7, 15, 8, 255, 0};
static u8 anim_5[] = {10, 11, 10, 12, 0, 0, 0, 0};
static u8 anim_6[] = {6, 13, 6, 14, 6, 15, 6, 16, 0, 0, 0, 0};
static u8 anim_7[] = {3, 13, 3, 14, 3, 15, 3, 16, 0, 0, 0, 0};
static s16 hitbox_offsets[] = {
    0, 0, 0, 0,  0,  1,  8, 8,  0, 1,  8, 8,  0, 1, 8, 8, 0, -6, 4, 13, 0, 1, 4,
    8, 0, 5, 4,  12, 0,  4, 4,  7, 0,  0, 0,  0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 2,
    8, 8, 0, -2, 6,  10, 0, -6, 4, 11, 0, -4, 4, 9, 0, 0, 4, 7,  0, -1, 4, 9};

void EntityBlackCrow(Entity* self) {
    s16* ptr;
    s32 posY;
    Entity* entity;

    if ((self->flags & FLAG_DEAD) && self->step != 4) {
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->velocityY = 0;
        self->hitboxState = 0;
        PlaySfxPositional(SFX_CROW_CAW_PAIN);
        SetStep(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlackCrow);
        self->animCurFrame = 1;
        self->ext.et_crow.unk84 = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 176;
        break;
    case 1:
        if (!AnimateEntity(anim_1, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (GetDistanceToPlayerX() < 80 && GetDistanceToPlayerY() < 64) {
            SetStep(3);
        }
        break;
    case 2:
        if (!AnimateEntity(anim_2, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (self->ext.et_crow.unk80) {
            self->ext.et_crow.unk80--;
        } else {
            SetStep(3);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(4.0);
            PlaySfxPositional(SFX_CROW_CAW);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            if (self->velocityY < FIX(-2)) {
                AnimateEntity(anim_3, self);
            } else {
                AnimateEntity(anim_2, self);
                self->velocityY -= FIX(0.125);
            }
            if (self->velocityY < 0) {
                posY = self->posY.val + g_Tilemap.scrollY.val;
                posY -= self->ext.et_crow.unk84;
                if (posY < 0) {
                    self->velocityX = 0;
                    self->step_s++;
                }
            }
            break;
        case 2:
            AnimateEntity(anim_3, self);
            MoveEntity();
            self->velocityY += FIX(0.25);
            if (self->velocityY > FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            posY = self->posY.val + g_Tilemap.scrollY.val;
            posY -= self->ext.et_crow.unk84;
            if (posY > 0) {
                self->ext.et_crow.unk80 = 128;
                self->animCurFrame = 1;
                self->facingLeft = GetSideToPlayer() & 1;
                SetStep(2);
            }
            break;
        }
        break;
    case 4:
        MoveEntity();
        self->rotate += 64;
        self->velocityY += FIX(0.09375);
        if (!AnimateEntity(anim_4, self)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0;
            }
            DestroyEntity(self);
            return;
        }
    }
    ptr = &hitbox_offsets[self->animCurFrame * 4];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void EntityBlueRaven(Entity* self) {
    s16* ptr;
    Entity* entity;

    if ((self->flags & FLAG_DEAD) && self->step != 3) {
        PlaySfxPositional(SFX_CROW_CAW_PAIN);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlueRaven);
        self->animCurFrame = 11;
        self->ext.et_crow.unk84 = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 0xB0;
        break;
    case 1:
        if (!AnimateEntity(anim_5, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (GetDistanceToPlayerX() < 96 && GetDistanceToPlayerY() < 48) {
            SetStep(2);
        }
        break;
    case 2:
        entity = &g_Entities[0];
        if (entity->posY.i.hi > self->posY.i.hi) {
            self->velocityY = FIX(1.0);
        } else {
            self->velocityY = FIX(-1.0);
        }
        self->velocityX = 0;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        SetStep(3);
        break;
    case 3:
        AnimateEntity(anim_6, self);
        MoveEntity();
        if (GetDistanceToPlayerY() < 8) {
            self->ext.et_crow.unk80 = 32;
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(anim_7, self);
        if (!--self->ext.et_crow.unk80) {
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            PlaySfxPositional(SFX_CROW_CAW);
            self->step++;
        }
        break;
    case 5:
        AnimateEntity(anim_7, self);
        MoveEntity();
        self->velocityY -= FIX(0.03125);
        if (self->facingLeft) {
            self->velocityX += FIX(0.0625);
        } else {
            self->velocityX -= FIX(0.0625);
        }
        break;
    }
    ptr = &hitbox_offsets[self->animCurFrame * 4];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}
