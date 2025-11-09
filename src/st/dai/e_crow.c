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
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->velocityY = 0;
        self->hitboxState = 0;
        PlaySfxPositional(SFX_CROW_DEATH);
        SetStep(CROW_DEATH);
    }
    switch (self->step) {
    case CROW_INIT:
        InitializeEntity(g_EInitBlackCrow);
        self->animCurFrame = 1;
        self->ext.crow.referenceY = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 176;
        break;
    case CROW_READY:
        if (!AnimateEntity(anim_crow_idle, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (GetDistanceToPlayerX() < 80 && GetDistanceToPlayerY() < 64) {
            SetStep(CROW_SWOOP);
        }
        break;
    case CROW_HOVER:
        if (!AnimateEntity(anim_crow_hover, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (self->ext.crow.hoverTimer) {
            self->ext.crow.hoverTimer--;
        } else {
            SetStep(CROW_SWOOP);
        }
        break;
    case CROW_SWOOP:
        switch (self->step_s) {
        case CROW_SWOOP_INIT:
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
        case CROW_SWOOP_MOVE:
            MoveEntity();
            if (self->velocityY < FIX(-2)) {
                AnimateEntity(anim_crow_swoop, self);
            } else {
                AnimateEntity(anim_crow_hover, self);
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
            AnimateEntity(anim_crow_swoop, self);
            MoveEntity();
            self->velocityY += FIX(0.25);
            if (self->velocityY > FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            posY = self->posY.val + g_Tilemap.scrollY.val;
            posY -= self->ext.crow.referenceY;
            if (posY > 0) {
                self->ext.crow.hoverTimer = 128;
                self->animCurFrame = 1;
                self->facingLeft = GetSideToPlayer() & 1;
                SetStep(CROW_HOVER);
            }
            break;
        }
        break;
    case CROW_DEATH:
        MoveEntity();
        self->rotate += 64;
        self->velocityY += FIX(0.09375);
        if (!AnimateEntity(anim_crow_death, self)) {
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, explosion);
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
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_SMALL;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case RAVEN_INIT:
        InitializeEntity(g_EInitBlueRaven);
        self->animCurFrame = 11;
        self->ext.crow.referenceY = g_Tilemap.scrollY.val + self->posY.val;
        self->zPriority = 176;
        break;
    case RAVEN_READY:
        if (!AnimateEntity(anim_raven_idle, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (GetDistanceToPlayerX() < 96 && GetDistanceToPlayerY() < 48) {
            SetStep(RAVEN_DISMOUNT);
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
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        SetStep(RAVEN_MATCH_HEIGHT);
        break;
    case RAVEN_MATCH_HEIGHT:
        AnimateEntity(anim_raven_match_height, self);
        MoveEntity();
        if (GetDistanceToPlayerY() < 8) {
            self->ext.crow.hoverTimer = 32;
            SetStep(RAVEN_HOVER);
        }
        break;
    case RAVEN_HOVER:
        AnimateEntity(anim_raven_hover, self);
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
        AnimateEntity(anim_raven_hover, self);
        MoveEntity();
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
