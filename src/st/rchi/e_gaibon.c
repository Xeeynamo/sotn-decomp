// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

extern EInit g_EInitGaibon;

#define SLOGRA self[-8]

typedef enum {
    GAIBON_INIT,
    GAIBON_IDLE = 2,
    GAIBON_FLY_TOWARDS_PLAYER,
    GAIBON_FLY_SHOOT_FIREBALLS,
    GAIBON_LANDING_AFTER_SHOOTING,
    GAIBON_SHOOT_FROM_GROUND,
    GAIBON_FLY_SHOOT_BIG_FIREBALL = 8,
    GAIBON_PICKUP_SLOGRA,
    GAIBON_NEAR_DEATH = 15,
    SLOGRA_GAIBON_RETREAT,
    GAIBON_DYING, // Unused here
    GAIBON_DEBUG = 255,
} GaibonSteps;

typedef enum {
    GAIBON_FLY_TOWARDS_PLAYER_BEGIN,
    GAIBON_FLY_TOWARDS_PLAYER_MOVEMENT,
    GAIBON_FLY_TOWARDS_PLAYER_END,
} GaibonFlyTowardsPlayerSubSteps;

typedef enum {
    GAIBON_FLY_SHOOT_FIREBALLS_BEGIN,
    GAIBON_FLY_SHOOT_FIREBALLS_MOVING_SHOOTING,
    GAIBON_FLY_SHOOT_FIREBALLS_END,
} GaibonFlyShootFirewalls_SubSteps;

typedef enum {
    GAIBON_LANDING_AFTER_SHOOTING_SETUP,
    GAIBON_FALLING_WITHOUT_MAP_COLLISION,
    GAIBON_FALLING_WITH_MAP_COLLISION,
    GAIBON_FALLING_ON_GROUND,
} GaibonLandingAfterShootingSubSteps;

typedef enum {
    GAIBON_SHOOT_FROM_GROUND_FACE_PLAYER,
    GAIBON_SHOOT_FROM_GROUND_FACE_SETUP,
    GAIBON_SHOOT_FROM_GROUND_FACE_SHOOTING,
} GaibonShootFromGroundSubSteps;

typedef enum {
    GAIBON_FLY_SHOOT_BIG_FIREBALL_SETUP,
    GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING,
    GAIBON_FLY_SHOOT_BIG_FIREBALL_END,
} GaibonFlyShootBigFireballSubSteps;

typedef enum {
    GAIBON_PICKUP_SLOGRA_SETUP,
    GAIBON_PICKUP_SLOGRA_MOVING,
    GAIBON_PICKUP_SLOGRA_ASCENDING,
    GAIBON_PICKUP_SLOGRA_AIMING,
    GAIBON_PICKUP_SLOGRA_RELEASE,
} GaibonPickupSlograSubSteps;

typedef enum {
    GAIBON_NEAR_DEATH_SETUP,
    GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT,
    GAIBON_NEAR_DEATH_FLOOR_LANDING,
    GAIBON_NEAR_DEATH_TRANSFORM,
} GaibonNearDeathSubSteps;

typedef enum {
    GAIBON_RETREAT_FACE_SLOGRA,
    GAIBON_RETREAT_PICKUP_SLOGRA,
    GAIBON_RETREAT_FLY_AWAY,
} GaibonRetreatSubSteps;

typedef enum {
    GAIBON_DYING_REACT,
    GAIBON_DYING_TURN_INTO_BONES,
} GaibonDyingSubSteps;

// These are unused in RCHI
static s16 sensors[] = {0, 28, 0, 4, 4, -4, -8, 0};
static AnimateEntityFrame anim_wing_flap[] = {
    {6, 1},  {3, 9}, {2, 2}, {2, 3},       {3, 4},
    {4, 10}, {5, 3}, {5, 2}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_wing_flap_fast[] = {
    {2, 1},  {1, 9}, {1, 2}, {1, 3},       {1, 4}, {1, 10}, {2, 3},
    {2, 2},  {4, 1}, {2, 9}, {1, 2},       {1, 3}, {2, 4},  {2, 10},
    {3, 3},  {3, 2}, {5, 1}, {2, 9},       {2, 2}, {2, 3},  {2, 4},
    {3, 10}, {4, 3}, {4, 2}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_wing_flap_shoot[] = {
    {6, 5},  {3, 11}, {2, 6}, {2, 7},       {3, 8},
    {4, 12}, {5, 7},  {5, 6}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_wing_flap_no_leg[] = {
    {6, 32}, {3, 33}, {2, 34}, {2, 35},      {3, 36},
    {4, 37}, {5, 35}, {5, 34}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_land[] = {
    {5, 13}, {5, 14}, {4, 15}, {8, 14}, POSE_END,
};
static AnimateEntityFrame anim_ground_shoot[] = {
    {3, 14}, {3, 16}, {3, 17}, {4, 18}, {4, 19}, {34, 18}, POSE_END,
};
static AnimateEntityFrame anim_big_fireball_shoot[] = {
    {4, 3},  {1, 22}, {1, 21}, {1, 22},  {4, 21},
    {4, 23}, {4, 20}, {1, 24}, POSE_END,
};
static AnimateEntityFrame anim_land_near_death[] = {
    {5, 13}, {5, 18}, {5, 25}, {4, 26}, {41, 25}, POSE_END,
};
static AnimateEntityFrame anim_near_death_transform[] = {
    {2, 25},
    {2, 27},
    POSE_LOOP(0),
};
// This animation goes unused in RCHI
static AnimateEntityFrame anim_death[] = {
    {16, 25}, {5, 28}, {6, 29}, {32, 30}, POSE_END,
};
static s8 gaibonHitboxes[][4] = {
    {0, 0, 0, 0},     {-3, -4, 15, 27}, {-3, -3, 15, 25}, {-3, -1, 15, 24},
    {-3, -1, 15, 23}, {-4, 4, 15, 23},  {-3, -3, 16, 21}, {-3, -3, 16, 20},
    {-5, 4, 17, 23},  {-59, -74, 0, 0}, {-5, -7, 15, 20}, {-5, -5, 15, 18},
};
static u8 gaibonHitboxIdx[] = {
    0, 1, 2, 3, 4, 1, 2, 3, 4, 1, 4,  1,  4,  4,  5,  5,  5,  5,  5,  5, 5, 6,
    6, 7, 8, 8, 8, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 11, 10, 11, 11, 0, 0, 0};

void EntityGaibon(Entity* self) {
    Collider collider;
    Entity* other;
    s16 angle;
    s8* hitboxPtr;
    s32 xVar;
    s32 yVar;
    s32 speed;
    s32 speedLimit;

    if (self->step && !self->ext.GS_Props.nearDeath) {
        if (self->hitPoints < g_api.enemyDefs[0xFE].hitPoints / 2) {
            self->ext.GS_Props.nearDeath = 1;
            SetStep(GAIBON_NEAR_DEATH);
        }
    }

    if (self->flags & FLAG_DEAD && self->step < GAIBON_NEAR_DEATH) {
        self->hitboxState = 0;
        SetStep(GAIBON_NEAR_DEATH);
    }

    switch (self->step) {
    case GAIBON_INIT:
        InitializeEntity(g_EInitGaibon);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_GAIBON_LEG, other);
        other->zPriority = self->zPriority + 4;
        SetStep(GAIBON_IDLE);
        break;

    case GAIBON_IDLE:
        AnimateEntity(anim_wing_flap, self);
        if (!self->poseTimer && self->pose == 1) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (GetDistanceToPlayerX() < 0x40) {
            SetStep(GAIBON_FLY_TOWARDS_PLAYER);
        }
        break;
    case GAIBON_FLY_TOWARDS_PLAYER:
        switch (self->step_s) {
        case GAIBON_FLY_TOWARDS_PLAYER_BEGIN:
            self->facingLeft = (GetSideToPlayer() & 1) ^
                               1; // Results in facing away from player
            other = &PLAYER;
            xVar = other->posX.i.hi;
            yVar = other->posY.i.hi - 0x20;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            self->ext.GS_Props.angle = ratan2(yVar, xVar);
            self->ext.GS_Props.speed = 0;
            self->ext.GS_Props.timer = 0x60;
            if (self->ext.GS_Props.nearDeath) {
                self->ext.GS_Props.timer = 0x30;
            }
            self->step_s++;
            /* fallthrough */
        case GAIBON_FLY_TOWARDS_PLAYER_MOVEMENT:
            speedLimit = FIX(2);
            if (self->ext.GS_Props.nearDeath) {
                speedLimit *= 2;
            }
            self->ext.GS_Props.speed += FIX(5.0 / 128);
            if (self->ext.GS_Props.speed >= speedLimit) {
                self->ext.GS_Props.speed = speedLimit;
            }
            speed = self->ext.GS_Props.speed;
            self->velocityX = (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->velocityY = (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
            MoveEntity();
            AnimateEntity(anim_wing_flap, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!(--self->ext.GS_Props.timer)) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_TOWARDS_PLAYER_END:
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;
            if (!AnimateEntity(anim_wing_flap_fast, self)) {
                SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
            }
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            break;
        }
        break;
    case GAIBON_FLY_SHOOT_FIREBALLS:
        switch (self->step_s) {
        case GAIBON_FLY_SHOOT_FIREBALLS_BEGIN:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            other = &PLAYER;
            xVar = other->posX.i.hi;
            if (GetSideToPlayer() & 1) {
                xVar += 0x60;
            } else {
                xVar -= 0x60;
            }
            yVar = other->posY.i.hi - 0x80;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            self->ext.GS_Props.angle = ratan2(yVar, xVar);
            self->ext.GS_Props.speed = 0;
            self->ext.GS_Props.timer = 80;
            if (self->ext.GS_Props.nearDeath) {
                self->ext.GS_Props.timer = 40;
            }
            self->step_s++;
            /* fallthrough */
        case GAIBON_FLY_SHOOT_FIREBALLS_MOVING_SHOOTING:
            speedLimit = FIX(2);
            if (self->ext.GS_Props.nearDeath) {
                speedLimit *= 2;
            }
            self->ext.GS_Props.speed += FIX(5.0 / 128);
            if (self->ext.GS_Props.speed >= speedLimit) {
                self->ext.GS_Props.speed = speedLimit;
            }
            speed = self->ext.GS_Props.speed;
            self->velocityX = (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->velocityY = (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
            MoveEntity();
            AnimateEntity(anim_wing_flap_shoot, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            // Reuse of speedLimit variable, unrelated to speed
            speedLimit = 0xF;
            if (self->ext.GS_Props.nearDeath) {
                speedLimit = 7;
            }
            if (!(self->ext.GS_Props.timer & speedLimit)) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    if (self->ext.GS_Props.nearDeath) {
                        CreateEntityFromEntity(
                            E_GAIBON_BIG_FIREBALL, self, other);
                        PlaySfxPositional(SFX_EXPLODE_B);
                    } else {
                        CreateEntityFromEntity(
                            E_GAIBON_SMALL_FIREBALL, self, other);
                        PlaySfxPositional(SFX_EXPLODE_FAST_A);
                    }
                    other->posY.i.hi -= 2;
                    if (self->facingLeft) {
                        other->posX.i.hi += 12;
                        other->rotate = 0x220;
                    } else {
                        other->posX.i.hi -= 12;
                        other->rotate = 0x5E0;
                    }
                    other->zPriority = (self->zPriority + 1);
                }
            }
            if (!--self->ext.GS_Props.timer) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_SHOOT_FIREBALLS_END:
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;
            if (AnimateEntity(anim_wing_flap_fast, self) == 0) {
                SetStep(GAIBON_FLY_TOWARDS_PLAYER);
                if (self->ext.GS_Props.nearDeath) {
                    SetStep(GAIBON_FLY_SHOOT_BIG_FIREBALL);
                }
            }
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            break;
        }
        break;
    case GAIBON_LANDING_AFTER_SHOOTING:
        switch (self->step_s) {
        case GAIBON_LANDING_AFTER_SHOOTING_SETUP:
            self->animCurFrame = 9;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case GAIBON_FALLING_WITHOUT_MAP_COLLISION:
            MoveEntity();
            self->velocityY += FIX(12.0 / 128);
            other = &PLAYER;
            // We enter the version with collision only if
            // the player's Y position minus ours is less than 48?
            // So if the player is 48 or more below us, there is no collision.
            // Weird!
            yVar = other->posY.i.hi - self->posY.i.hi;
            if (yVar < 48) {
                self->step_s++;
            }
            break;
        case GAIBON_FALLING_WITH_MAP_COLLISION:
            MoveEntity();
            self->velocityY += FIX(12.0 / 128);
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi + 28;
            g_api.CheckCollision(xVar, yVar, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            }
            break;
        case GAIBON_FALLING_ON_GROUND:
            if (AnimateEntity(anim_land, self) == 0) {
                SetStep(GAIBON_SHOOT_FROM_GROUND);
            }
            break;
        }
        break;
    case GAIBON_SHOOT_FROM_GROUND:
        switch (self->step_s) {
        case GAIBON_SHOOT_FROM_GROUND_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            /* fallthrough */
        case GAIBON_SHOOT_FROM_GROUND_FACE_SETUP:
            if (AnimateEntity(anim_ground_shoot, self) == 0) {
                self->ext.GS_Props.timer = 64;
                if (self->ext.GS_Props.nearDeath) {
                    self->ext.GS_Props.timer *= 2;
                }
                self->step_s++;
            }
            break;
        case GAIBON_SHOOT_FROM_GROUND_FACE_SHOOTING:
            if (!(self->ext.GS_Props.timer & 0xF)) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    if (!self->ext.GS_Props.nearDeath) {
                        CreateEntityFromEntity(
                            E_GAIBON_SMALL_FIREBALL, self, other);
                        PlaySfxPositional(SFX_EXPLODE_FAST_A);
                    } else {
                        CreateEntityFromEntity(
                            E_GAIBON_BIG_FIREBALL, self, other);
                        PlaySfxPositional(SFX_EXPLODE_B);
                    }
                    other->posY.i.hi -= 6;
                    if (self->facingLeft) {
                        other->posX.i.hi += 16;
                        other->rotate = 0;
                    } else {
                        other->posX.i.hi -= 16;
                        other->rotate = 0x800;
                    }
                    other->zPriority = self->zPriority + 1;
                }
            }
            if (!--self->ext.GS_Props.timer) {
                SetStep(GAIBON_FLY_TOWARDS_PLAYER);
            }
            break;
        }
        break;
    case GAIBON_FLY_SHOOT_BIG_FIREBALL:
        switch (self->step_s) {
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SETUP:
            if (AnimateEntity(anim_big_fireball_shoot, self) == 0) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING:
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self, other);
                    PlaySfxPositional(SFX_EXPLODE_B);
                    other->posY.i.hi -= 2;
                    if (self->facingLeft) {
                        other->posX.i.hi += 12;
                        other->rotate = 0x220;

                    } else {
                        other->posX.i.hi -= 12;
                        other->rotate = 0x5E0;
                    }
                    other->zPriority = self->zPriority + 1;
                }
            }
            self->velocityY = FIX(-2);
            if (self->facingLeft) {
                self->velocityX = FIX(-2);
            } else {
                self->velocityX = FIX(2);
            }
            self->ext.GS_Props.timer = 32;
            self->step_s++;
            /* fallthrough */
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_END:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            self->velocityY -= self->velocityY / 16;
            if (!--self->ext.GS_Props.timer) {
                SetStep(GAIBON_FLY_TOWARDS_PLAYER);
            }
            break;
        }
        break;
    case GAIBON_PICKUP_SLOGRA:
        switch (self->step_s) {
        case GAIBON_PICKUP_SLOGRA_SETUP:
            other = &SLOGRA;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (xVar > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->ext.GS_Props.speed = 0;
            self->step_s++;
            /* fallthrough */
        case GAIBON_PICKUP_SLOGRA_MOVING:
            other = &SLOGRA;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - (self->posY.i.hi + 0x1C);
            angle = ratan2(yVar, xVar);
            self->ext.GS_Props.speed += FIX(0.5);
            if (self->ext.GS_Props.speed >= FIX(3.5)) {
                self->ext.GS_Props.speed = FIX(3.5);
            }
            speed = self->ext.GS_Props.speed;
            self->velocityX = (speed * rcos(angle)) >> 0xC;
            self->velocityY = (speed * rsin(angle)) >> 0xC;
            MoveEntity();
            if (abs(xVar) < 8 && abs(yVar) < 8) {
                self->ext.GS_Props.grabedAscending = 1;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            if (!other->ext.GS_Props.pickupFlag) {
                self->ext.GS_Props.grabedAscending = 0;
                SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
            }
            break;
        case GAIBON_PICKUP_SLOGRA_ASCENDING:
            AnimateEntity(anim_wing_flap_no_leg, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            MoveEntity();
            self->velocityY -= FIX(5.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->velocityY = FIX(-2);
            }
            other = &SLOGRA;
            other->posX.i.hi = self->posX.i.hi;
            other->posY.i.hi = self->posY.i.hi + 28;
            self->ext.GS_Props.grabedAscending = 1;
            if (self->posY.i.hi < 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->ext.GS_Props.timer = 96;
                self->step_s++;
            }
            break;
        case GAIBON_PICKUP_SLOGRA_AIMING:
            AnimateEntity(anim_wing_flap_no_leg, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            if (GetSideToPlayer() & 1) {
                self->velocityX -= FIX(5.0 / 128);
            } else {
                self->velocityX += FIX(5.0 / 128);
            }
            if (self->velocityX < FIX(-2)) {
                self->velocityX = FIX(-2);
            }
            if (self->velocityX > FIX(2)) {
                self->velocityX = FIX(2);
            }
            MoveEntity();
            other = &SLOGRA;
            other->posX.i.hi = self->posX.i.hi;
            other->posY.i.hi = self->posY.i.hi + 28;
            other->velocityY = 0;
            self->ext.GS_Props.grabedAscending = 0;
            if (!--self->ext.GS_Props.timer) {
                self->step_s++;
            }
            break;
        case GAIBON_PICKUP_SLOGRA_RELEASE:
            self->ext.GS_Props.grabedAscending = 0;
            SetStep(GAIBON_FLY_TOWARDS_PLAYER);
        }
        break;
    case GAIBON_NEAR_DEATH:
        switch (self->step_s) {
        case GAIBON_NEAR_DEATH_SETUP:
            self->animCurFrame = 9;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT:
            PlaySfxPositional(SFX_SLOGRA_PAIN_A);
            SetSubStep(GAIBON_NEAR_DEATH_FLOOR_LANDING);
            break;
        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            self->posY.val += FIX(0.125);
            if (AnimateEntity(anim_land_near_death, self) == 0) {
                self->ext.GS_Props.flag = 0;
                SetSubStep(GAIBON_NEAR_DEATH_TRANSFORM);
                if (self->flags & FLAG_DEAD) {
                    PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                    SetStep(SLOGRA_GAIBON_RETREAT);
                } else {
                    PlaySfxPositional(SFX_SLOGRA_PAIN_A);
                }
            }
            break;
        case GAIBON_NEAR_DEATH_TRANSFORM:
            self->posY.val += FIX(0.125);
            if (AnimateEntity(anim_near_death_transform, self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette = g_EInitGaibon[3] + self->ext.GS_Props.flag;
                if (self->ext.GS_Props.flag == 6) {
                    self->flags &= ~0xF;
                    SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
                }
            }
            break;
        }
        break;
    case SLOGRA_GAIBON_RETREAT:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.GS_Props.timer = 0x60;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!(self->ext.GS_Props.timer & 7)) {
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posX.i.hi += ((Random() & 31) - 16);
                    other->posY.i.hi += (Random() & 31) - 4;
                    other->zPriority = self->zPriority + 1;
                    other->params = 3;
                }
            }
            if (!--self->ext.GS_Props.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
    hitboxPtr = &gaibonHitboxes[0][0];
    hitboxPtr += gaibonHitboxIdx[self->animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void EntityGaibonLeg(Entity* self) {
    Entity* parent;
    s32 frame;

    if (!self->step) {
        InitializeEntity(g_EInitGaibon);
        self->hitboxState = 0;
    }

    parent = self - 1;
    self->facingLeft = parent->facingLeft;
    self->palette = parent->palette;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->animCurFrame = 0;
    frame = parent->animCurFrame;

    if (0x1F < frame && frame < 0x23) {
        self->animCurFrame = 0x26;
    } else if (frame == 0x23) {
        self->animCurFrame = 0x27;
    } else if (0x23 < frame && frame < 0x26) {
        self->animCurFrame = 0x28;
    }

    if (parent->entityId != 0x19) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitGaibonProjectile;
static AnimateEntityFrame anim_small_fireball[] = {
    {2, 3}, {2, 4}, {2, 5}, {2, 4}, POSE_LOOP(0),
};

void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = E_EXPLOSION;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonProjectile);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->drawFlags = ENTITY_SCALEX | ENTITY_ROTATE;
        self->scaleX = 0xC0;
        self->velocityX = (rcos(self->rotate) * FIX(2.5)) >> 0xC;
        self->velocityY = (rsin(self->rotate) * FIX(2.5)) >> 0xC;
        self->rotate -= ROT(90);
        self->palette = PAL_FLAG(PAL_UNK_1B6);

    case 1:
        MoveEntity();
        AnimateEntity(anim_small_fireball, self);
        return;
    }
}

extern EInit g_EInitGaibonLargeProjectile;

static AnimateEntityFrame anim_large_fireball[] = {
    {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 15}, {2, 14}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_explosion[] = {
    {1, 1}, {1, 2}, {1, 3},  {1, 4},  {1, 5},  {1, 6},  {1, 7},
    {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13}, POSE_END,
};

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->params = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonLargeProjectile);
        if (!self->params) {
            self->animSet = ANIMSET_DRA(2);
            self->drawFlags = ENTITY_ROTATE;
            self->velocityX = (rcos(self->rotate) * FIX(3.5)) >> 0xC;
            self->velocityY = (rsin(self->rotate) * FIX(3.5)) >> 0xC;
            self->rotate -= ROT(90);
            self->palette = PAL_FLAG(PAL_UNK_1B6);
        } else {
            self->animSet = ANIMSET_DRA(14);
            self->unk5A = 0x79;
            self->drawFlags = ENTITY_SCALEX | ENTITY_ROTATE | ENTITY_OPACITY;
            self->scaleX = 0x100;
            self->opacity = 0x80;
            self->palette = PAL_FLAG(PAL_UNK_1F3);
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
            self->step = 2;
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(anim_large_fireball, self);
        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self, newEntity);
                newEntity->params = 1;
                newEntity->rotate = self->rotate;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->opacity -= 2;
        self->scaleX -= 4;
        if (AnimateEntity(anim_explosion, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
