// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum ShortcutSteps {
    SHORTCUT_INIT,
    SHORTCUT_CHECK_STATUE,
    SHORTCUT_MOVE_BLOCK,
    SHORTCUT_OPEN = 16,
};

#ifdef VERSION_PSP
extern s32 E_ID(STATUE);
#endif

extern EInit g_EInitEnvironment;

static s16 sensors[] = {0, -15, 0, 0};

void EntityBlock(Entity* self) {
    u32 collision;
    Entity* statue;
    Entity* playerPtr;

    switch (self->step) {
    case SHORTCUT_INIT:
        OVL_EXPORT(InitializeEntity)(g_EInitEnvironment);
        self->animCurFrame = 1;
        if (g_CastleFlags[NO2_TO_DAI_SHORTCUT]) {
            self->posX.i.hi += 32;
            self->posY.i.hi += 32;
            self->step = SHORTCUT_OPEN;
        } else {
            statue = self + 1;
            OVL_EXPORT(CreateEntityFromEntity)(E_ID(STATUE), self, statue);
            statue->posX.i.hi += 16;
            statue->posY.i.hi += 16;
        case SHORTCUT_CHECK_STATUE:
            statue = self + 1;
            if (!statue->entityId) {
                g_CastleFlags[NO2_TO_DAI_SHORTCUT] = true;
                self->step++;
            }
        }
        break;
    case SHORTCUT_MOVE_BLOCK:
        self->velocityX = FIX(0.25);
        collision = OVL_EXPORT(UnkCollisionFunc2)(sensors);
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        }
        if (!(collision & (EFFECT_UNK_0020 | EFFECT_SOLID_FROM_ABOVE))) {
            self->step++;
        }
        break;
    }
    self->hitboxState = 1;
    self->hitboxOffX = 8;
    self->hitboxOffY = -68;
    self->hitboxWidth = 8;
    self->hitboxHeight = 6;
    // Collision with top
    collision = OVL_EXPORT(GetPlayerCollisionWith)(self, 8, 6, 4);
    if (collision & 4) {
        playerPtr = &PLAYER;
        playerPtr->posY.i.hi++;
        g_unkGraphicsStruct.shoveY.i.hi++;
    }
    self->hitboxOffX = -16;
    self->hitboxOffY = -60;
    self->hitboxWidth = 16;
    self->hitboxHeight = 48;
    // Any collision
    collision = OVL_EXPORT(GetPlayerCollisionWith)(self, 16, 48, 7);
}

void EntityStatue(Entity* self) {
    Entity* entity;

    if (!self->step) {
        OVL_EXPORT(InitializeEntity)(g_EInitEnvironment);
        self->animCurFrame = 2;
        self->hitboxState = 2;
        self->hitPoints = 4;
        self->hitboxOffX = -8;
        self->hitboxOffY = -32;
        self->hitboxWidth = 8;
        self->hitboxHeight = 16;
        entity = &PLAYER;
        if (entity->posX.i.hi < 128) {
            self->hitboxState = 0;
        }
    }
    if (self->flags & FLAG_DEAD) {
        entity = OVL_EXPORT(AllocEntity)(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            OVL_EXPORT(CreateEntityFromEntity)(E_EXPLOSION, self, entity);
            entity->posX.i.hi -= 8;
            entity->posY.i.hi -= 8;
            entity->params = EXPLOSION_FIREBALL;
        }
        g_api.PlaySfx(SFX_EXPLODE_B);
        DestroyEntity(self);
    }
}
