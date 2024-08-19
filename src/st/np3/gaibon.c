#include "np3.h"
#include "sfx.h"

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

extern u16 D_80180B68[];

static s32 D_801814B4[] = {
    0x001C0000,
    0x00040000,
    0xFFFC0004,
    0x0000FFF8,
};
static u8 D_801814C4[] = {0x06, 0x01, 0x03, 0x09, 0x02, 0x02, 0x02, 0x03, 0x03,
                          0x04, 0x04, 0x0A, 0x05, 0x03, 0x05, 0x02, 0x00};
static u8 D_801814D8[] = {
    0x02, 0x01, 0x01, 0x09, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04,
    0x01, 0x0A, 0x02, 0x03, 0x02, 0x02, 0x04, 0x01, 0x02, 0x09,
    0x01, 0x02, 0x01, 0x03, 0x02, 0x04, 0x02, 0x0A, 0x03, 0x03,
    0x03, 0x02, 0x05, 0x01, 0x02, 0x09, 0x02, 0x02, 0x02, 0x03,
    0x02, 0x04, 0x03, 0x0A, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 D_8018150C[] = {0x06, 0x05, 0x03, 0x0B, 0x02, 0x06, 0x02, 0x07, 0x03,
                          0x08, 0x04, 0x0C, 0x05, 0x07, 0x05, 0x06, 0x00};
static u8 D_80181520[] = {0x06, 0x20, 0x03, 0x21, 0x02, 0x22, 0x02, 0x23, 0x03,
                          0x24, 0x04, 0x25, 0x05, 0x23, 0x05, 0x22, 0x00};
static u8 D_80181534[] = {
    0x05, 0x0D, 0x05, 0x0E, 0x04, 0x0F, 0x08, 0x0E, 0xFF, 0x00};
static u8 D_80181540[] = {0x03, 0x0E, 0x03, 0x10, 0x03, 0x11, 0x04,
                          0x12, 0x04, 0x13, 0x22, 0x12, 0xFF, 0x00};
static u8 D_80181550[] = {0x04, 0x03, 0x01, 0x16, 0x01, 0x15, 0x01, 0x16, 0x04,
                          0x15, 0x04, 0x17, 0x04, 0x14, 0x01, 0x18, 0xFF, 0x00};
static u8 D_80181564[] = {
    0x05, 0x0D, 0x05, 0x12, 0x05, 0x19, 0x04, 0x1A, 0x29, 0x19, 0xFF, 0x00};
static u8 D_80181570[] = {0x02, 0x19, 0x02, 0x1B, 0x00, 0x00, 0x00, 0x00};
static u8 D_80181578[] = {
    0x10, 0x19, 0x05, 0x1C, 0x06, 0x1D, 0x20, 0x1E, 0xFF, 0x00};
static u8 D_80181584[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0xFD, 0xFC, 0x0F, 0x1B},
    {0xFD, 0xFD, 0x0F, 0x19}, {0xFD, 0xFF, 0x0F, 0x18},
    {0xFD, 0xFF, 0x0F, 0x17}, {0xFC, 0x04, 0x0F, 0x17},
    {0xFD, 0xFD, 0x10, 0x15}, {0xFD, 0xFD, 0x10, 0x14},
    {0xFB, 0x04, 0x11, 0x17}, {0xC5, 0xB6, 0x00, 0x00},
    {0xFB, 0xF9, 0x0F, 0x14}, {0xFB, 0xFB, 0x0F, 0x12},
};
static u8 D_801815B4[][4] = {
    {0x00, 0x01, 0x02, 0x03}, {0x04, 0x01, 0x02, 0x03},
    {0x04, 0x01, 0x04, 0x01}, {0x04, 0x04, 0x05, 0x05},
    {0x05, 0x05, 0x05, 0x05}, {0x05, 0x06, 0x06, 0x07},
    {0x08, 0x08, 0x08, 0x08}, {0x08, 0x08, 0x09, 0x09},
    {0x0A, 0x0A, 0x0A, 0x0B}, {0x0B, 0x0B, 0x0A, 0x0B},
    {0x0B, 0x00, 0x00, 0x00},
};
static u8 D_801815E0[] = {0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x04, 0x00};
static u8 D_801815EC[] = {0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02,
                          0x10, 0x02, 0x0F, 0x02, 0x0E, 0x00};
static u8 D_801815FC[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x05,
    0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A,
    0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D, 0xFF, 0x00};

void EntityGaibon(Entity* self) {
    Collider collider;
    Entity* other;
    s16 angle;
    s8* hitboxPtr;
    s32 xVar;
    s32 yVar;
    s32 speedLimit;
    s32 speed;

    if (self->step != 0) {
        if (self->ext.GS_Props.nearDeath == 0) {
            if (self->hitPoints < g_api.enemyDefs[0xFE].hitPoints / 2) {
                self->ext.GS_Props.nearDeath = 1;
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
                    self->hitboxState = 0;
                    SetStep(GAIBON_NEAR_DEATH);
                }
            }
        }
        if ((!(self->flags & FLAG_DEAD) || (self->step >= GAIBON_NEAR_DEATH)) &&
            (SLOGRA.ext.GS_Props.pickupFlag) &&
            (self->step < GAIBON_LANDING_AFTER_SHOOTING)) {
            SetStep(GAIBON_PICKUP_SLOGRA);
        }
        if (D_801812CC) {
            self->hitboxState = 0;
            if (self->step != SLOGRA_GAIBON_RETREAT) {
                SetStep(SLOGRA_GAIBON_RETREAT);
            }
        }
    }
    switch (self->step) {
    case 0x0:
        if ((g_CastleFlags[132] == 0) && (*(&g_CastleFlags[56] + 1) == 0)) {
            InitializeEntity(D_80180B68);
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            CreateEntityFromCurrentEntity(E_801B8CC0, self + 1);
            (self + 1)->zPriority = self->zPriority + 4;
            SetStep(GAIBON_IDLE);
            break;
        }
        DestroyEntity(self);
        return;
    case GAIBON_IDLE:
        AnimateEntity(D_801814C4, self);
        if (self->animFrameDuration == 0 && self->animFrameIdx == 1) {
            PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            AnimateEntity(D_801814C4, self);
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            if (!AnimateEntity(D_801814D8, self)) {
                SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
            }
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            AnimateEntity(D_8018150C, self);
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
                        E_GAIBON_SMALL_FIREBALL, self, other);
                    PlaySfxPositional(SFX_EXPLODE_FAST_A);
                    other->posY.i.hi -= 2;
                    if (self->facingLeft) {
                        other->posX.i.hi += 12;
                        other->rotZ = 0x220;
                    } else {
                        other->posX.i.hi -= 12;
                        other->rotZ = 0x5E0;
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
            if (AnimateEntity(D_801814D8, self) == 0) {
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
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            if (AnimateEntity(D_80181534, self) == 0) {
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
            if (AnimateEntity(D_80181540, self) == 0) {
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
                        other->rotZ = 0;
                    } else {
                        other->posX.i.hi -= 16;
                        other->rotZ = 0x800;
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
            if (AnimateEntity(D_80181550, self) == 0) {
                self->step_s++;
            }
            break;
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING:
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    PlaySfxPositional(SFX_EXPLODE_B);
                    CreateEntityFromEntity(0x54, self, other);
                    other->posY.i.hi -= 2;
                    if (self->facingLeft) {
                        other->posX.i.hi += 12;
                        other->rotZ = 0x220;

                    } else {
                        other->posX.i.hi -= 12;
                        other->rotZ = 0x5E0;
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
            AnimateEntity(D_80181520, self);
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            AnimateEntity(D_80181520, self);
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
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
            if (func_801BC8E4(D_801814B4) & 1) {
                SetSubStep(GAIBON_NEAR_DEATH_FLOOR_LANDING);
            }
            break;
        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            if (AnimateEntity(D_80181564, self) == 0) {
                self->ext.GS_Props.flag = 0;
                SetSubStep(GAIBON_NEAR_DEATH_TRANSFORM);
            }
            break;
        case GAIBON_NEAR_DEATH_TRANSFORM:
            if (AnimateEntity(D_80181570, self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette = D_80180B68[3] + self->ext.GS_Props.flag;
                if (self->ext.GS_Props.flag == 6) {
                    D_801812CC = 1;
                    self->flags &= ~0xF;
                    SetStep(SLOGRA_GAIBON_RETREAT);
                }
            }
            break;
        }
        break;
    case SLOGRA_GAIBON_RETREAT:
        switch (self->step_s) {
        case 0:
            xVar = SLOGRA.posX.i.hi - self->posX.i.hi;
            if (xVar > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->ext.GS_Props.speed = 0;
            g_CastleFlags[57] |= 1;
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
            AnimateEntity(D_80181520, self);
            MoveEntity();
            self->velocityY -= FIX(5.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->velocityY = FIX(-2);
            }
            SLOGRA.posX.i.hi = self->posX.i.hi;
            SLOGRA.posY.i.hi = self->posY.i.hi + 28;
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
            if (AnimateEntity(D_80181578, self) == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 0x1F;
                self->flags &= ~0xF;
                self->palette = D_80180B68[3];
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
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    hitboxPtr = &D_80181584[0];
    hitboxPtr += D_801815B4[0][self->animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    return;
}

void func_801B8CC0(Entity* self) {
    Entity* prevEntity;
    s16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_80180B68);
        self->hitboxState = 0;
    }

    prevEntity = &self[-1];
    self->facingLeft = prevEntity->facingLeft;
    self->palette = prevEntity->palette;
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    self->animCurFrame = 0;

    if ((prevEntity->animCurFrame - 32) < 3U) {
        self->animCurFrame = 0x26;
    } else if (prevEntity->animCurFrame == 35) {
        self->animCurFrame = 0x27;
    } else if ((prevEntity->animCurFrame - 36) < 2U) {
        self->animCurFrame = 0x28;
    }

    if (prevEntity->entityId != E_GAIBON) {
        DestroyEntity(self);
    }
}

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        self->pfnUpdate = EntityExplosion;
        self->drawFlags = 0;
        self->step = 0;
        self->entityId = 2;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B74);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ;
        self->rotX = 0xC0;
        self->velocityX = (rcos(self->rotZ) * 0x28000) >> 0xC;
        self->velocityY = (rsin(self->rotZ) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->rotZ -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_801815E0, self);
        break;
    }
}

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & FLAG_DEAD) {
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->drawFlags = 0;
        self->step = 0;
        self->params = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B80);
        if (self->params == 0) {
            self->animSet = ANIMSET_DRA(2);
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->velocityX = (rcos(self->rotZ) * 0x38000) >> 0xC;
            self->velocityY = (rsin(self->rotZ) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->rotZ -= 0x400;
        } else {
            self->animSet = ANIMSET_DRA(14);
            self->unk5A = 0x79;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
            self->rotX = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->drawMode = 0x30;
            self->step = 2;
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(D_801815EC, self);
        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self, newEntity);
                newEntity->params = 1;
                newEntity->rotZ = self->rotZ;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->rotX -= 4;
        if (AnimateEntity(D_801815FC, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
