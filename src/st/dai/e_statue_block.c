// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(STATUE);
#endif
static s16 sensors[] = {0, -15, 0, 0};

void EntityBlock(Entity* self) {
    u32 collision;
    Entity* entity;
    Entity* playerPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStatueBlock);
        self->animCurFrame = 1;
        if (g_CastleFlags[NO2_TO_DAI_SHORTCUT]) {
            self->posX.i.hi += 32;
            self->posY.i.hi += 32;
            self->step = 16;
        } else {
            entity = self + 1;
            CreateEntityFromEntity(E_ID(STATUE), self, entity);
            entity->posX.i.hi += 16;
            entity->posY.i.hi += 16;
        case 1:
            entity = self + 1;
            if (!entity->entityId) {
                g_CastleFlags[NO2_TO_DAI_SHORTCUT] = 1;
                self->step++;
            }
        }
        break;
    case 2:
        self->velocityX = FIX(0.25);
        collision = UnkCollisionFunc2(&sensors);
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        }
        if (!(collision & 0x60)) {
            self->step++;
        }
        break;
    }
    self->hitboxState = 1;
    self->hitboxOffX = 8;
    self->hitboxOffY = -68;
    self->hitboxWidth = 8;
    self->hitboxHeight = 6;
    collision = GetPlayerCollisionWith(self, 8, 6, 4);
    if (collision & 4) {
        playerPtr = &PLAYER;
        playerPtr->posY.i.hi++;
        D_80097488.y.i.hi++;
    }
    self->hitboxOffX = -16;
    self->hitboxOffY = -60;
    self->hitboxWidth = 16;
    self->hitboxHeight = 48;
    collision = GetPlayerCollisionWith(self, 16, 48, 7);
}

void EntityStatue(Entity* self) {
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitStatueBlock);
        self->animCurFrame = 2;
        self->hitboxState = 2;
        self->hitPoints = 4;
        self->hitboxOffX = -8;
        self->hitboxOffY = -32;
        self->hitboxWidth = 8;
        self->hitboxHeight = 16;
        entity = g_Entities;
        if (entity->posX.i.hi < 128) {
            self->hitboxState = 0;
        }
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->posX.i.hi -= 8;
            entity->posY.i.hi -= 8;
            entity->params = 1;
        }
        g_api.PlaySfx(SFX_EXPLODE_B);
        DestroyEntity(self);
    }
}
