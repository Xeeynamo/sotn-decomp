// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

static u8 anim_change_dir[] = {
    0x05, 0x01, 0x05, 0x02, 0x05, 0x01, 0x05, 0x02, 0x05, 0x01, 0xFF, 0x00};
static u8 anim_jump[] = {0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x02, 0x02,
                         0x02, 0x01, 0x09, 0x02, 0x04, 0x03, 0xFF, 0x00};
static u8 anim_land[] = {0x02, 0x06, 0xFF, 0x00};
static u8 anim_open_mouth[] = {
    0x09, 0x01, 0x02, 0x02, 0x01, 0x01, 0x06, 0x07, 0x08, 0x08, 0xFF, 0x00};
static u8 anim_close_mouth[] = {0x08, 0x08, 0x06, 0x07, 0x03, 0x01, 0xFF, 0x00};
static u8 anim_tongue[] = {
    0x01, 0x09, 0x01, 0x0A, 0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D,
    0x01, 0x0E, 0x06, 0x0F, 0x05, 0x0E, 0x04, 0x0D, 0x03, 0x0C,
    0x02, 0x0B, 0x02, 0x0A, 0x03, 0x09, 0xFF, 0x00};
static s16 sensors_ground[4][2] = {{0, 12}, {0, 4}, {4, -4}, {-8, 0}};
// { hitboxOffX, hitboxWidth }
static s16 tongueHitbox[][2] = {
    {-9, 4}, {-9, 4}, {-12, 5}, {-12, 5}, {-16, 9}, {-16, 9}, {-22, 16}};
static s16 jumpIntervals[] = {256, 32, 8, 96, 96, 32, 256, 64};
static s16 lickIntervals[] = {32, 32, 16, 512, 128, 192, 256, 8};
static Point32 jumpVelocities[] = {
    {.x = FIX(0.5), .y = FIX(-6)},
    {.x = FIX(1.5), .y = FIX(-4)},
    {.x = FIX(2), .y = FIX(-2)},
    {.x = FIX(2.5), .y = FIX(-1)},
};

void EntityToad(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 index;
    s32 posX;
    s32 posY;

    if (self->flags & FLAG_DEAD) {
        if (self->ext.frogToad.tongueEntity) {
            entity = self->ext.frogToad.tongueEntity;
            DestroyEntity(entity);
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }

        PlaySfxPositional(SFX_FROG_CROAK);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitToad);
        if (self->params) {
            // params set to 1 means this is the toad's tongue
            self->hitboxHeight = 3;
            self->hitboxOffY = -1;
            self->hitPoints = 0x7FFF;
            self->hitboxState = 1;
            self->step = 6;
            self->animCurFrame = 0;
        }
        break;
    case 1:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.frogToad.jumpTimer = 0x20;
            self->ext.frogToad.lickTimer = 0x40;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 1;
            if (!Random()) {
                self->poseTimer = 0;
                self->pose = 0;
                self->step_s++;
            }
            if (self->ext.frogToad.jumpTimer) {
                self->ext.frogToad.jumpTimer--;
            } else {
                SetStep(3);
                break;
            }

            if (self->ext.frogToad.lickTimer) {
                self->ext.frogToad.lickTimer--;
            } else {
                SetStep(4);
                break;
            }
            PlaySfxPositional(SFX_TOAD_CROAK);

            break;
        case 1:
            if (!AnimateEntity(anim_change_dir, self)) {
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                self->step_s--;
                break;
            }
            break;
        }
        break;
    // Jump
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_jump, self)) {
                index = Random() & 3;
                self->velocityX = jumpVelocities[index].x;
                if (!self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = jumpVelocities[index].y;
                self->hitboxOffX = 1;
                self->hitboxOffY = -7;
                self->hitboxWidth = 7;
                self->hitboxHeight = 0xC;
                PlaySfxPositional(SFX_BLIPS_A);
                self->step_s++;
            }
            break;
        case 1:
            posX = self->posX.i.hi;
            if (self->velocityX > 0) {
                posX += 0x10;
            }
            if (self->velocityX < 0) {
                posX -= 0x10;
            }
            posY = self->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            if (self->velocityY < 0) {
                posY -= 0x10;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    self->velocityY = 0;
                }
            }
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                SetSubStep(2);
            }
            if (self->velocityY < 0) {
                self->animCurFrame = 4;
                break;
            }
            self->animCurFrame = 5;
            self->hitboxOffX = -4;
            self->hitboxOffY = -4;
            self->hitboxWidth = 8;
            self->hitboxHeight = 10;
            break;
        case 2:
            self->hitboxOffX = 0;
            self->hitboxOffY = 2;
            self->hitboxWidth = 9;
            self->hitboxHeight = 10;
            if (!AnimateEntity(anim_land, self)) {
                self->ext.frogToad.jumpTimer = jumpIntervals[Random() & 7];
                SetStep(2);
            }
        }
        break;
    // Lick
    case 4:
        switch (self->step_s) {
        case 0:
            self->step_s++;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                // Spawn the toad tongue
                CreateEntityFromEntity(E_TOAD, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = 1;
                entity->zPriority = self->zPriority + 1;
                self->ext.frogToad.tongueEntity = entity;
                break;
            }
            SetStep(2);
            self->ext.frogToad.tongueEntity = NULL;
            break;
        case 1:
            if (!AnimateEntity(anim_open_mouth, self)) {
                PlaySfxPositional(SFX_FROG_TOAD_TONGUE);
                SetSubStep(2);
            }
            break;
        case 2:
            entity = self->ext.frogToad.tongueEntity;
            if (!AnimateEntity(anim_tongue, entity)) {
                DestroyEntity(entity);
                self->ext.frogToad.tongueEntity = NULL;
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(anim_close_mouth, self)) {
                SetStep(2);
                self->ext.frogToad.lickTimer = lickIntervals[Random() & 7];
            }
            break;
        }
        break;
    case 6:
        index = self->animCurFrame - 9;
        self->hitboxOffX = tongueHitbox[index][0];
        self->hitboxWidth = tongueHitbox[index][1];
        break;
    }
}
