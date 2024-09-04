#include "np3.h"
#include "sfx.h"

#define SLOGRA self[-8]

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    SLOGRA_GAIBON_RETREAT,
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
        if ((!(self->flags & FLAG_DEAD) || (self->step >= GAIBON_NEAR_DEATH)) &&
REDACTED
REDACTED
REDACTED
REDACTED
        if (D_801812CC) {
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
            self->velocityX = (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->velocityY = (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
REDACTED
            AnimateEntity(D_801814C4, self);
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!(--self->ext.GS_Props.timer)) {
                self->step_s++;
            }
            break;
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            /* fallthrough */
REDACTED
            speedLimit = FIX(2);
            if (self->ext.GS_Props.nearDeath) {
                speedLimit *= 2;
            }
            self->ext.GS_Props.speed += FIX(5.0 / 128);
            if (self->ext.GS_Props.speed >= speedLimit) {
                self->ext.GS_Props.speed = speedLimit;
REDACTED
REDACTED
            self->velocityX = (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->velocityY = (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
REDACTED
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
REDACTED
REDACTED
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;
            if (AnimateEntity(D_801814D8, self) == 0) {
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
                    SetStep(5);
                } else {
                    SetStep(3);
                }
REDACTED
REDACTED
REDACTED
REDACTED
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
            break;
        }
        break;
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = 0;
            self->velocityY = 0;
REDACTED
            /* fallthrough */
REDACTED
REDACTED
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
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
            /* fallthrough */
        case GAIBON_SHOOT_FROM_GROUND_FACE_SETUP:
            if (AnimateEntity(D_80181540, self) == 0) {
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
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
REDACTED
                self->velocityX = FIX(2);
REDACTED
REDACTED
REDACTED
            /* fallthrough */
REDACTED
REDACTED
            self->velocityX -= self->velocityX / 16;
            self->velocityY -= self->velocityY / 16;
            if (!(--self->ext.GS_Props.timer)) {
                xVar = self->posX.i.hi - 0x80;
                if (abs(xVar) < 0x60) {
REDACTED
REDACTED
REDACTED
REDACTED
            }
            break;
        }
        break;
REDACTED
REDACTED
REDACTED
            other = &SLOGRA;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (xVar > 0) {
                self->facingLeft = 1;
REDACTED
                self->facingLeft = 0;
REDACTED
REDACTED
REDACTED
            /* fallthrough */
        case GAIBON_PICKUP_SLOGRA_MOVING:
            other = &SLOGRA;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - (self->posY.i.hi + 0x1C);
            angle = ratan2(yVar, xVar);
            self->ext.GS_Props.speed += FIX(0.5);
            if (self->ext.GS_Props.speed >= FIX(3.5)) {
                self->ext.GS_Props.speed = FIX(3.5);
REDACTED
REDACTED
            self->velocityX = (speed * rcos(angle)) >> 0xC;
            self->velocityY = (speed * rsin(angle)) >> 0xC;
REDACTED
            if ((abs(xVar) < 8) && (abs(yVar) < 8)) {
                self->ext.GS_Props.grabedAscending = 1;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            if (!other->ext.GS_Props.pickupFlag) {
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.GS_Props.nearDeath = 1;
            self->step_s++;
            /* fallthrough */
        case GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT:
            if (UnkCollisionFunc3(D_801814B4) & 1) {
REDACTED
REDACTED
REDACTED
        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            if (AnimateEntity(D_80181564, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
        case GAIBON_NEAR_DEATH_TRANSFORM:
            if (AnimateEntity(D_80181570, self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette = D_80180B68[3] + self->ext.GS_Props.flag;
REDACTED
REDACTED
REDACTED
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
REDACTED
                self->facingLeft = 0;
REDACTED
REDACTED
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
REDACTED
REDACTED
            self->velocityX = (speed * rcos(angle)) >> 0xC;
            self->velocityY = (speed * rsin(angle)) >> 0xC;
REDACTED
            if (abs(xVar) < 8 && abs(yVar) < 8) {
                self->velocityX = 0;
                self->velocityY = 0;
REDACTED
REDACTED
REDACTED
        case 2:
            AnimateEntity(D_80181520, self);
            MoveEntity();
            self->velocityY -= FIX(5.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->velocityY = FIX(-2);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    // Because we are in the initial Entrance encounter, it is not possible to
    // reach this step. The fact that it is here anyway seems like strong
    // evidence that this whole function was copy-pasted, and then tweaked to
    // suit the needs in Entrance.
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_80181578, self) == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 0x1F;
                self->flags &= ~0xF;
                self->palette = D_80180B68[3];
                self->step_s++;
            }
            break;
REDACTED
REDACTED
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
REDACTED
REDACTED
            if (self->params) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    hitboxPtr = &D_80181584[0];
    hitboxPtr += D_801815B4[0][self->animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    return;
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
    self->facingLeft = prevEntity->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (prevEntity->entityId != E_GAIBON) {
REDACTED
REDACTED
REDACTED

// small red projectile from gaibon
REDACTED
    if (self->flags & FLAG_DEAD) {
REDACTED
        self->drawFlags = 0;
REDACTED
        self->entityId = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->animSet = ANIMSET_DRA(2);
REDACTED
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ;
        self->rotX = 0xC0;
        self->velocityX = (rcos(self->rotZ) * 0x28000) >> 0xC;
        self->velocityY = (rsin(self->rotZ) * 0x28000) >> 0xC;
REDACTED
        self->rotZ -= 0x400;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_DEAD) {
REDACTED
        self->entityId = 2;
        self->drawFlags = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B80);
REDACTED
            self->animSet = ANIMSET_DRA(2);
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->velocityX = (rcos(self->rotZ) * 0x38000) >> 0xC;
            self->velocityY = (rsin(self->rotZ) * 0x38000) >> 0xC;
REDACTED
            self->rotZ -= 0x400;
REDACTED
            self->animSet = ANIMSET_DRA(14);
REDACTED
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
            self->rotX = 0x100;
REDACTED
REDACTED
            self->drawMode = 0x30;
REDACTED
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_801815EC, self);
        if (!(g_Timer & 3)) {
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity->rotZ = self->rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotX -= 4;
        if (AnimateEntity(D_801815FC, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
