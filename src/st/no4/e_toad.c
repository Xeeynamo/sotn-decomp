// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

// PSX: https://decomp.me/scratch/EQbZe
// PSP: https://decomp.me/scratch/B70fl

extern s16 D_us_8018261C[]; // sensors_ground
extern u8 D_us_801825CC[];
extern u8 D_us_801825D8[];
extern u8 D_us_801825E8[];
extern u8 D_us_801825EC[];
extern u8 D_us_80182600[];
extern u8 D_us_801825F8[];
extern s16 D_us_80182648[];
extern s16 D_us_80182658[];
extern Point32 D_us_80182668[]; // velocities
extern s16 D_us_8018262C[][2];  // hitbox data

void EntityToad(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 temp_s2;
    s32 posX;
    s32 posY;

    if (self->flags & FLAG_DEAD) {
        if (self->ext.toad.entity) {
            entity = self->ext.toad.entity;
            DestroyEntity(entity);
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        PlaySfxPositional(0x71B);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitToad);
        if (self->params) {
            self->hitboxHeight = 3;
            self->hitboxOffY = -1;
            self->hitPoints = 0x7FFF;
            self->hitboxState = 1;
            self->step = 6;
            self->animCurFrame = 0;
        }
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_8018261C) & 1) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.toad.unk82 = 0x20;
            self->ext.toad.unk80 = 0x40;
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
            if (self->ext.toad.unk82) {
                self->ext.toad.unk82--;
            } else {
                SetStep(3);
                break;
            }

            if (self->ext.toad.unk80) {
                self->ext.toad.unk80--;
            } else {
                SetStep(4);
                break;
            }

            PlaySfxPositional(0x71A);

            break;
        case 1:
            if (!AnimateEntity(D_us_801825CC, self)) {
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                self->step_s--;
                break;
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801825D8, self)) {
                temp_s2 = Random() & 3;
                self->velocityX = D_us_80182668[temp_s2].x;
                if (!self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = D_us_80182668[temp_s2].y;
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
            if (UnkCollisionFunc3(D_us_8018261C) & 1) {
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
            if (!AnimateEntity(D_us_801825E8, self)) {
                self->ext.toad.unk82 = D_us_80182648[Random() & 7];
                SetStep(2);
            }
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->step_s++;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID_3C, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = 1;
                entity->zPriority = self->zPriority + 1;
                self->ext.toad.entity = entity;
                break;
            }
            SetStep(2);
            self->ext.toad.entity = NULL;
            break;
        case 1:
            if (!AnimateEntity(D_us_801825EC, self)) {
                PlaySfxPositional(SFX_BOING);
                SetSubStep(2);
            }
            break;
        case 2:
            entity = self->ext.toad.entity;
            if (!AnimateEntity(D_us_80182600, entity)) {
                DestroyEntity(entity);
                self->ext.toad.entity = NULL;
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_801825F8, self)) {
                SetStep(2);
                self->ext.toad.unk80 = D_us_80182658[Random() & 7];
            }
            break;
        }
        break;
    case 6:
        temp_s2 = self->animCurFrame - 9;
        self->hitboxOffX = D_us_8018262C[temp_s2][0];
        self->hitboxWidth = D_us_8018262C[temp_s2][1];
        break;
    }
}
