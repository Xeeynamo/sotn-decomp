// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum CrowSteps {
    CROW_INIT,
    CROW_READY,
    CROW_HOVER,
    CROW_SWOOP,
    CROW_DEATH,
};

enum CrowSubsteps {
    CROW_SWOOP_INIT,
    CROW_SWOOP_MOVE,
    CROW_SWOOP_RECOVER,
};

enum RavenSteps {
    RAVEN_INIT,
    RAVEN_READY,
    RAVEN_DISMOUNT,
    RAVEN_MATCH_HEIGHT,
    RAVEN_HOVER,
    RAVEN_ATTACK,
};

extern EInit g_EInitBlueRaven;
extern EInit g_EInitBlackCrow;

static AnimateEntityFrame anim_crow_idle[] = {
    {38, 1}, {6, 2}, {6, 3}, {6, 2}, {6, 3}, {6, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_crow_hover[] = {
    {7, 4}, {1, 5}, {10, 6}, {7, 5}, POSE_LOOP(0)};
static AnimateEntityFrame anim_crow_swoop[] = {
    {3, 4}, {1, 5}, {6, 6}, {3, 5}, POSE_LOOP(0)};
static AnimateEntityFrame anim_crow_death[] = {
    {6, 4}, {6, 7}, {15, 8}, POSE_END};
static AnimateEntityFrame anim_raven_idle[] = {
    {10, 11}, {10, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_raven_match_height[] = {
    {6, 13}, {6, 14}, {6, 15}, {6, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_raven_hover[] = {
    {3, 13}, {3, 14}, {3, 15}, {3, 16}, POSE_LOOP(0)};
// These are groups of x, y, w, and h values for the hitbox
static s16 hitbox_offsets[] = {
    0, 0, 0, 0,  0,  1,  8, 8,  0, 1,  8, 8,  0, 1, 8, 8, 0, -6, 4, 13, 0, 1, 4,
    8, 0, 5, 4,  12, 0,  4, 4,  7, 0,  0, 0,  0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 2,
    8, 8, 0, -2, 6,  10, 0, -6, 4, 11, 0, -4, 4, 9, 0, 0, 4, 7,  0, -1, 4, 9};

void EntityBlackCrow(Entity* self) {
    s16* hitboxPtr;
    s32 posY;
    Entity* explosion;

    if ((self->flags & FLAG_DEAD) && self->step != CROW_DEATH) {
        self->drawFlags |= ENTITY_ROTATE;
        self->velocityY = 0;
        self->hitboxState = 0;
        PlaySfxPositional(SFX_CROW_DEATH);
        OVL_EXPORT(SetStep)(CROW_DEATH);
    }
    switch (self->step) {
    case CROW_INIT:
        OVL_EXPORT(InitializeEntity)(g_EInitBlackCrow);
        self->animCurFrame = 1;
        self->ext.crow.referenceY = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 176;
        break;
    case CROW_READY:
        if (!OVL_EXPORT(AnimateEntity)(anim_crow_idle, self)) {
            self->facingLeft = (OVL_EXPORT(GetSideToPlayer)() & 1) ^ 1;
        }
        if (OVL_EXPORT(GetDistanceToPlayerX)() < 80 &&
            OVL_EXPORT(GetDistanceToPlayerY)() < 64) {
            OVL_EXPORT(SetStep)(CROW_SWOOP);
        }
        break;
    case CROW_HOVER:
        if (!OVL_EXPORT(AnimateEntity)(anim_crow_hover, self)) {
            self->facingLeft = (OVL_EXPORT(GetSideToPlayer)() & 1) ^ 1;
        }
        if (self->ext.crow.hoverTimer) {
            self->ext.crow.hoverTimer--;
        } else {
            OVL_EXPORT(SetStep)(CROW_SWOOP);
        }
        break;
    case CROW_SWOOP:
        switch (self->step_s) {
        case CROW_SWOOP_INIT:
            self->facingLeft = (OVL_EXPORT(GetSideToPlayer)() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(4.0);
            PlaySfxPositional(SFX_CROW_CAW);
            self->step_s++;
            break;
        case CROW_SWOOP_MOVE:
            OVL_EXPORT(MoveEntity)();
            if (self->velocityY < FIX(-2)) {
                OVL_EXPORT(AnimateEntity)(anim_crow_swoop, self);
            } else {
                OVL_EXPORT(AnimateEntity)(anim_crow_hover, self);
                self->velocityY -= FIX(0.125);
            }
            if (self->velocityY < 0) {
                posY = self->posY.val + g_Tilemap.scrollY.val;
                posY -= self->ext.crow.referenceY;
                if (posY < 0) {
                    self->velocityX = 0;
                    self->step_s++;
                }
            }
            break;
        case CROW_SWOOP_RECOVER:
            OVL_EXPORT(AnimateEntity)(anim_crow_swoop, self);
            OVL_EXPORT(MoveEntity)();
            self->velocityY += FIX(0.25);
            if (self->velocityY > FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            posY = self->posY.val + g_Tilemap.scrollY.val;
            posY -= self->ext.crow.referenceY;
            if (posY > 0) {
                self->ext.crow.hoverTimer = 128;
                self->animCurFrame = 1;
                self->facingLeft = OVL_EXPORT(GetSideToPlayer)() & 1;
                OVL_EXPORT(SetStep)(CROW_HOVER);
            }
            break;
        }
        break;
    case CROW_DEATH:
        OVL_EXPORT(MoveEntity)();
        self->rotate += 64;
        self->velocityY += FIX(0.09375);
        if (!OVL_EXPORT(AnimateEntity)(anim_crow_death, self)) {
            explosion =
                OVL_EXPORT(AllocEntity)(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                OVL_EXPORT(CreateEntityFromEntity)
                (E_EXPLOSION, self, explosion);
                explosion->params = EXPLOSION_SMALL;
            }
            DestroyEntity(self);
            return;
        }
    }
    hitboxPtr = &hitbox_offsets[self->animCurFrame * 4];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void EntityBlueRaven(Entity* self) {
    s16* hitboxPtr;
    Entity* entity;

    if ((self->flags & FLAG_DEAD) && self->step != RAVEN_MATCH_HEIGHT) {
        PlaySfxPositional(SFX_CROW_DEATH);
        entity = OVL_EXPORT(AllocEntity)(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            OVL_EXPORT(CreateEntityFromEntity)(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_SMALL;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case RAVEN_INIT:
        OVL_EXPORT(InitializeEntity)(g_EInitBlueRaven);
        self->animCurFrame = 11;
        self->ext.crow.referenceY = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 176;
        break;
    case RAVEN_READY:
        if (!OVL_EXPORT(AnimateEntity)(anim_raven_idle, self)) {
            self->facingLeft = (OVL_EXPORT(GetSideToPlayer)() & 1) ^ 1;
        }
        if (OVL_EXPORT(GetDistanceToPlayerX)() < 96 &&
            OVL_EXPORT(GetDistanceToPlayerY)() < 48) {
            OVL_EXPORT(SetStep)(RAVEN_DISMOUNT);
        }
        break;
    case RAVEN_DISMOUNT:
        entity = &PLAYER;
        if (entity->posY.i.hi > self->posY.i.hi) {
            self->velocityY = FIX(1.0);
        } else {
            self->velocityY = FIX(-1.0);
        }
        self->velocityX = 0;
        self->facingLeft = (OVL_EXPORT(GetSideToPlayer)() & 1) ^ 1;
        OVL_EXPORT(SetStep)(RAVEN_MATCH_HEIGHT);
        break;
    case RAVEN_MATCH_HEIGHT:
        OVL_EXPORT(AnimateEntity)(anim_raven_match_height, self);
        OVL_EXPORT(MoveEntity)();
        if (OVL_EXPORT(GetDistanceToPlayerY)() < 8) {
            self->ext.crow.hoverTimer = 32;
            OVL_EXPORT(SetStep)(RAVEN_HOVER);
        }
        break;
    case RAVEN_HOVER:
        OVL_EXPORT(AnimateEntity)(anim_raven_hover, self);
        if (!--self->ext.crow.hoverTimer) {
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            PlaySfxPositional(SFX_CROW_CAW);
            self->step++;
        }
        break;
    case RAVEN_ATTACK:
        OVL_EXPORT(AnimateEntity)(anim_raven_hover, self);
        OVL_EXPORT(MoveEntity)();
        self->velocityY -= FIX(0.03125);
        if (self->facingLeft) {
            self->velocityX += FIX(0.0625);
        } else {
            self->velocityX -= FIX(0.0625);
        }
        break;
    }
    hitboxPtr = &hitbox_offsets[self->animCurFrame * 4];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}
