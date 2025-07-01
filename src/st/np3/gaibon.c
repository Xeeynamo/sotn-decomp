// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "sfx.h"

#ifdef VERSION_PSP
extern s32 E_ID(GAIBON);
extern s32 E_ID(GAIBON_IDLE);
extern s32 E_ID(GAIBON_SMALL_FIREBALL);
extern s32 E_ID(GAIBON_BIG_FIREBALL);
#endif

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
    GAIBON_DYING,
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
} GaibonFlyShootBigFirewallSubSteps;

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

static s32 D_801814B4[] = {
    0x001C0000,
    0x00040000,
    0xFFFC0004,
    0x0000FFF8,
};
static u8 anim1[] = {0x06, 0x01, 0x03, 0x09, 0x02, 0x02, 0x02, 0x03, 0x03,
                     0x04, 0x04, 0x0A, 0x05, 0x03, 0x05, 0x02, 0x00};
static u8 anim2[] = {0x02, 0x01, 0x01, 0x09, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04,
                     0x01, 0x0A, 0x02, 0x03, 0x02, 0x02, 0x04, 0x01, 0x02, 0x09,
                     0x01, 0x02, 0x01, 0x03, 0x02, 0x04, 0x02, 0x0A, 0x03, 0x03,
                     0x03, 0x02, 0x05, 0x01, 0x02, 0x09, 0x02, 0x02, 0x02, 0x03,
                     0x02, 0x04, 0x03, 0x0A, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 anim3[] = {0x06, 0x05, 0x03, 0x0B, 0x02, 0x06, 0x02, 0x07, 0x03,
                     0x08, 0x04, 0x0C, 0x05, 0x07, 0x05, 0x06, 0x00};
static u8 anim4[] = {0x06, 0x20, 0x03, 0x21, 0x02, 0x22, 0x02, 0x23, 0x03,
                     0x24, 0x04, 0x25, 0x05, 0x23, 0x05, 0x22, 0x00};
static u8 anim5[] = {0x05, 0x0D, 0x05, 0x0E, 0x04,
                     0x0F, 0x08, 0x0E, 0xFF, 0x00};
static u8 anim6[] = {0x03, 0x0E, 0x03, 0x10, 0x03, 0x11, 0x04,
                     0x12, 0x04, 0x13, 0x22, 0x12, 0xFF, 0x00};
static u8 anim7[] = {0x04, 0x03, 0x01, 0x16, 0x01, 0x15, 0x01, 0x16, 0x04,
                     0x15, 0x04, 0x17, 0x04, 0x14, 0x01, 0x18, 0xFF, 0x00};
static u8 anim8[] = {0x05, 0x0D, 0x05, 0x12, 0x05, 0x19,
                     0x04, 0x1A, 0x29, 0x19, 0xFF, 0x00};
static u8 anim9[] = {0x02, 0x19, 0x02, 0x1B, 0x00, 0x00, 0x00, 0x00};
static u8 anim10[] = {0x10, 0x19, 0x05, 0x1C, 0x06,
                      0x1D, 0x20, 0x1E, 0xFF, 0x00};
static s8 gaibonHitboxes[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0xFD, 0xFC, 0x0F, 0x1B},
    {0xFD, 0xFD, 0x0F, 0x19}, {0xFD, 0xFF, 0x0F, 0x18},
    {0xFD, 0xFF, 0x0F, 0x17}, {0xFC, 0x04, 0x0F, 0x17},
    {0xFD, 0xFD, 0x10, 0x15}, {0xFD, 0xFD, 0x10, 0x14},
    {0xFB, 0x04, 0x11, 0x17}, {0xC5, 0xB6, 0x00, 0x00},
    {0xFB, 0xF9, 0x0F, 0x14}, {0xFB, 0xFB, 0x0F, 0x12},
};
static u8 gaibonHitboxIdx[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04, 0x01, 0x04,
    0x01, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06,
    0x06, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A,
    0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x00, 0x00, 0x00};

void EntityGaibon(Entity* self) {
    Collider collider;
    Entity* other;
    s16 angle;
    s8* hitboxPtr;
    s32 xVar;
    s32 yVar;
    s32 speed;
    s32 speedLimit;

    if (self->step) {
        if (!self->ext.GS_Props.nearDeath) {
            if (self->hitPoints < g_api.enemyDefs[0xFE].hitPoints / 2) {
                self->ext.GS_Props.nearDeath = 1;
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
                    self->hitboxState = 0;
                    SetStep(GAIBON_NEAR_DEATH);
                }
            }
        }
        if (!(self->flags & FLAG_DEAD) || (self->step >= GAIBON_NEAR_DEATH)) {
            other = self - 8;
            if ((other->ext.GS_Props.pickupFlag) &&
                (self->step < GAIBON_LANDING_AFTER_SHOOTING)) {
                SetStep(GAIBON_PICKUP_SLOGRA);
            }
        }
        if (slograGaibonRetreat) {
            self->hitboxState = 0;
            if (self->step != SLOGRA_GAIBON_RETREAT) {
                SetStep(SLOGRA_GAIBON_RETREAT);
            }
        }
    }
    switch (self->step) {
    case 0x0:
        if (g_CastleFlags[SLO_GAI_DEFEATED]) {
            DestroyEntity(self);
            return;
        }
        if (g_CastleFlags[SLO_GAI_RETREATED]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitGaibonNP3);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        other = self + 1;
        CreateEntityFromCurrentEntity(E_ID(GAIBON_IDLE), other);
        other->zPriority = self->zPriority + 4;
        SetStep(GAIBON_IDLE);
        break;

    case GAIBON_IDLE:
        AnimateEntity(anim1, self);
        if (!self->poseTimer && self->pose == 1) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if ((GetDistanceToPlayerX() < 0x60) &&
            (GetDistanceToPlayerY() < 0x60)) {
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
            AnimateEntity(anim1, self);
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
            if (!AnimateEntity(anim2, self)) {
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
            AnimateEntity(anim3, self);
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
                    CreateEntityFromEntity(
                        E_ID(GAIBON_SMALL_FIREBALL), self, other);
                    PlaySfxPositional(SFX_EXPLODE_FAST_A);
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
            if (!(--self->ext.GS_Props.timer)) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_SHOOT_FIREBALLS_END:
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;
            if (AnimateEntity(anim2, self) == 0) {
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
                    SetStep(5);
                } else {
                    SetStep(3);
                }
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
            if (AnimateEntity(anim5, self) == 0) {
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
            if (AnimateEntity(anim6, self) == 0) {
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
                            E_ID(GAIBON_SMALL_FIREBALL), self, other);
                        PlaySfxPositional(SFX_EXPLODE_FAST_A);
                    } else {
                        CreateEntityFromEntity(
                            E_ID(GAIBON_BIG_FIREBALL), self, other);
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
            if (!(--self->ext.GS_Props.timer)) {
                SetStep(GAIBON_FLY_TOWARDS_PLAYER);
            }
            break;
        }
        break;
    case GAIBON_FLY_SHOOT_BIG_FIREBALL:
        switch (self->step_s) {
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SETUP:
            if (AnimateEntity(anim7, self) == 0) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING:
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    PlaySfxPositional(SFX_EXPLODE_B);
                    CreateEntityFromEntity(
                        E_ID(GAIBON_BIG_FIREBALL), self, other);
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
            if (!(--self->ext.GS_Props.timer)) {
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
                    SetStep(GAIBON_LANDING_AFTER_SHOOTING);
                } else {
                    SetStep(GAIBON_FLY_TOWARDS_PLAYER);
                }
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
            if ((abs(xVar) < 8) && (abs(yVar) < 8)) {
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
            AnimateEntity(anim4, self);
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
            AnimateEntity(anim4, self);
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
            if (!(--self->ext.GS_Props.timer)) {
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
            self->ext.GS_Props.nearDeath = 1;
            self->step_s++;
            /* fallthrough */
        case GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT:
            if (UnkCollisionFunc3(D_801814B4) & 1) {
                SetSubStep(GAIBON_NEAR_DEATH_FLOOR_LANDING);
            }
            break;
        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            if (AnimateEntity(anim8, self) == 0) {
                self->ext.GS_Props.flag = 0;
                SetSubStep(GAIBON_NEAR_DEATH_TRANSFORM);
            }
            break;
        case GAIBON_NEAR_DEATH_TRANSFORM:
            if (AnimateEntity(anim9, self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette = g_EInitGaibonNP3[3] + self->ext.GS_Props.flag;
                if (self->ext.GS_Props.flag == 6) {
                    self->flags &= ~0xF;
                    slograGaibonRetreat = 1;
                    SetStep(SLOGRA_GAIBON_RETREAT);
                }
            }
            break;
        }
        break;
    case SLOGRA_GAIBON_RETREAT:
        switch (self->step_s) {
        case 0:
            other = self - 8;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (xVar > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->ext.GS_Props.speed = 0;
            g_CastleFlags[SLO_GAI_RETREATED] |= 1;
            self->step_s++;
            /* fallthrough */
        case 1:
            other = &SLOGRA;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - (self->posY.i.hi + 28);
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
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(anim4, self);
            MoveEntity();
            self->velocityY -= FIX(5.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->velocityY = FIX(-2);
            }
            other = self - 8;
            other->posX.i.hi = self->posX.i.hi;
            other->posY.i.hi = self->posY.i.hi + 28;
            break;
        }
        break;
    // Because we are in the initial Entrance encounter, it is not possible to
    // reach this step. The fact that it is here anyway seems like strong
    // evidence that this whole function was copy-pasted, and then tweaked to
    // suit the needs in Entrance.
    case GAIBON_DYING:
        switch (self->step_s) {
        case GAIBON_DYING_REACT:
            if (AnimateEntity(anim10, self) == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 0x1F;
                self->flags &= ~0xF;
                self->palette = g_EInitGaibonNP3[3];
                self->step_s++;
            }
            break;
        case GAIBON_DYING_TURN_INTO_BONES:
            if (!(self->ext.GS_Props.timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posY.i.hi += 28;
                    // Scatter bones randomly between +- 32
                    other->posX.i.hi += ((Random() & 63) - 32);
                    other->zPriority = self->zPriority + 1;
                    other->params = 2;
                }
            }
            if (!(--self->ext.GS_Props.timer)) {
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

void func_801B8CC0(Entity* self) {
    Entity* gaibon;
    s32 gaibonFrame;

    if (!self->step) {
        InitializeEntity(g_EInitGaibonNP3);
        self->hitboxState = 0;
    }

    gaibon = self - 1;
    self->facingLeft = gaibon->facingLeft;
    self->palette = gaibon->palette;
    self->posX.i.hi = gaibon->posX.i.hi;
    self->posY.i.hi = gaibon->posY.i.hi;
    self->animCurFrame = 0;

    gaibonFrame = gaibon->animCurFrame;
    if (0x1F < gaibonFrame && gaibonFrame < 0x23) {
        self->animCurFrame = 0x26;
    } else if (gaibonFrame == 0x23) {
        self->animCurFrame = 0x27;
    } else if (0x23 < gaibonFrame && gaibonFrame < 0x26) {
        self->animCurFrame = 0x28;
    }

    if (gaibon->entityId != E_ID(GAIBON)) {
        DestroyEntity(self);
    }
}

static u8 anim_small_fireball[] = {
    0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x04, 0x00};
static u8 anim_large_fireball1[] = {0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02,
                                    0x10, 0x02, 0x0F, 0x02, 0x0E, 0x00};
static u8 anim_large_fireball2[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x05,
    0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A,
    0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D, 0xFF, 0x00};

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonProjectileNP3);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_ROTATE;
        self->scaleX = 0xC0;
        self->velocityX = (rcos(self->rotate) * FIX(2.5)) >> 0xC;
        self->velocityY = (rsin(self->rotate) * FIX(2.5)) >> 0xC;
        self->rotate -= 0x400;
        self->palette = PAL_OVL(0x1B6);

    case 1:
        MoveEntity();
        AnimateEntity(anim_small_fireball, self);
        break;
    }
}

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & FLAG_DEAD) {
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->params = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonLargeProjectileNP3);
        if (!self->params) {
            self->animSet = ANIMSET_DRA(2);
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->velocityX = (rcos(self->rotate) * FIX(3.5)) >> 0xC;
            self->velocityY = (rsin(self->rotate) * FIX(3.5)) >> 0xC;
            self->rotate -= 0x400;
            self->palette = PAL_OVL(0x1B6);
        } else {
            self->animSet = ANIMSET_DRA(14);
            self->unk5A = 0x79;
            self->drawFlags =
                FLAG_DRAW_SCALEX | FLAG_DRAW_ROTATE | FLAG_DRAW_OPACITY;
            self->scaleX = 0x100;
            self->opacity = 0x80;
            self->palette = PAL_OVL(0x1F3);
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->step = 2;
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(anim_large_fireball1, self);
        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(GAIBON_BIG_FIREBALL), self, newEntity);
                newEntity->params = 1;
                newEntity->rotate = self->rotate;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->opacity -= 2;
        self->scaleX -= 4;
        if (AnimateEntity(anim_large_fireball2, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
