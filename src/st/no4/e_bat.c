// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

static u8 bat_anim_fly[] = {4, 21, 1, 22, 1, 23, 1, 30, 1, 24, 1, 25, 4, 26,
                            2, 27, 2, 28, 2, 29, 1, 30, 2, 23, 2, 22, 0, 0};
static u8 bat_anim_drop[] = {5, 31, 5, 32, 5, 31, 5, 32, 5,  31, 5,   32, 4, 31,
                             4, 32, 3, 31, 3, 32, 2, 31, 12, 32, 255, 0,  0, 0};

// This is a slightly modified version of the Bat enemy
// present in other overlays. Has a different SFX and some
// slightly enhanced movement behaviour.
void EntityBat(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;
    s32 posX;
    s32 posY;
    bool changeDir;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
        }
        g_api.PlaySfx(SFX_BAT_SCREECH);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBat);
        self->animCurFrame = 31;
        break;

    case 1:
        xDistance = GetDistanceToPlayerX();
        yDistance = GetDistanceToPlayerY();
        if (xDistance < 0x60 && yDistance < 0x70 && !(GetSideToPlayer() & 2)) {
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(bat_anim_drop, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->velocityY = FIX(0.875);
            if (self->facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->pose = (Random() & 3) * 3;
            self->poseTimer = 0;
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();
        changeDir = false;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 0x20;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & (EFFECT_WATER | EFFECT_SOLID)) {
            self->velocityY = 0;
            changeDir = true;
        }
        if (GetDistanceToPlayerY() < 0x20) {
            changeDir = true;
        }

        if (changeDir) {
            if (self->facingLeft) {
                self->velocityX = FIX(1);
            } else {
                self->velocityX = FIX(-1);
            }
            self->ext.batEnemy.accelY = 0x800;
            self->step = 4;
        }
        break;

    case 4:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();
        if (self->velocityY < FIX(-1) || self->velocityY > FIX(1)) {
            self->ext.batEnemy.accelY = -self->ext.batEnemy.accelY;
        }
        // accelY is already an s32, but psp needs the cast. I dunno.
        self->velocityY += (s32)self->ext.batEnemy.accelY;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->velocityY > 0) {
            posY += 4;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & (EFFECT_WATER | EFFECT_SOLID)) {
                self->velocityY = 0;
            }
        }
        break;
    }
}
