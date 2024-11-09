// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "common.h"

extern u8 D_us_80181FC8[];
extern u8 D_us_80181FD8[];
extern s16 D_us_80181FE0[];

void EntityGhostEnemy(Entity* self) {
    Entity* newEntity;
    s16 angle;
    s32 speed;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_GHOST_ENEMY_HOWL);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGhostEnemy);
        self->hitboxOffX = 1;
        self->hitboxOffY = -1;
        self->hitboxState = 0;
        // fallthrough
    case 1:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->step++;
        break;
    case 2:
        if (!AnimateEntity(D_us_80181FC8, self)) {
            self->hitboxState = 7;
            SetStep(3);
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80181FD8, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();

        // Seek towards player
        newEntity = &PLAYER;
        angle = GetAngleBetweenEntities(self, newEntity);
        angle = GetNormalizedAngle(16, self->ext.ghostEnemy.angle, angle);
        speed = self->ext.ghostEnemy.speed;
        self->velocityX = (speed * rcos(angle)) >> 12;
        self->velocityY = (speed * rsin(angle)) >> 12;
        self->ext.ghostEnemy.angle = angle;

        speed += FIX(0.015625);
        if (speed > FIX(0.75)) {
            speed = FIX(0.75);
        }
        // If player is hit, bounce back off in opposite direction
        if (self->hitFlags) {
            speed = FIX(-0.75);
        }
        self->ext.ghostEnemy.speed = speed;
        break;
    }
}

void EntityGhostEnemySpawner(Entity* self) {
    Entity* entity;
    s32 xPos;
    s32 yPos;
    s16* minMaxPositions;

    if (!self->step) {
        InitializeEntity(D_us_80180A88);
        self->flags &= ~FLAG_UNK_2000;
        self->ext.ghostEnemySpawner.timer = 1;
    }
    if (!--self->ext.ghostEnemySpawner.timer) {
        self->ext.ghostEnemySpawner.timer = (Random() & 47) + 48;
        entity = &PLAYER;
        xPos = g_Tilemap.scrollX.i.hi + entity->posX.i.hi;
        yPos = g_Tilemap.scrollY.i.hi + entity->posY.i.hi;
        if (self->params) {
            minMaxPositions = &D_us_80181FE0[(self->params - 1) * 4];
            if (xPos < minMaxPositions[0] || xPos > minMaxPositions[1] ||
                yPos < minMaxPositions[2] || yPos > minMaxPositions[3]) {
                return;
            }
        }

        entity = AllocEntity(&g_Entities[160], &g_Entities[164]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_GHOST_ENEMY, self, entity);
            entity->zPriority = 170;
            entity->posX.i.hi = xPos - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = yPos - g_Tilemap.scrollY.i.hi;
            xPos = (Random() & 63) + 48;
            if (Random() & 1) {
                entity->posX.i.hi += xPos;
            } else {
                entity->posX.i.hi -= xPos;
            }

            yPos = ((Random() & 127) - 64);
            entity->posY.i.hi += yPos;
        }
    }
}
