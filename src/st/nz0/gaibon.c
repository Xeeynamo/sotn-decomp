#include "nz0.h"
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
} GaibonFlyShootBigFireballSubSteps;
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
void EntityGaibon(Entity* self) {
    Collider collider;
    Entity* other;
    s16 angle;
    s32 speed;
    s32 speedLimit;
    s8* hitboxPtr;

    s32 yVar;
    s32 xVar;

    if ((self->step) && (!self->ext.GS_Props.nearDeath) &&
        self->hitPoints < g_api.enemyDefs[0xFE].hitPoints / 2) {
        self->ext.GS_Props.grabedAscending = 0;
        self->ext.GS_Props.nearDeath = 1;
        SetStep(GAIBON_NEAR_DEATH);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < GAIBON_NEAR_DEATH)) {
        self->ext.GS_Props.grabedAscending = 0;
        self->hitboxState = 0;
        SetStep(GAIBON_NEAR_DEATH);
    } else {
        other = &SLOGRA;
        if ((other->ext.GS_Props.pickupFlag) && (self->step < 5)) {
            SetStep(9);
        }
    }
REDACTED
REDACTED
REDACTED
        other = self + 1;
        // func_801B69E8
        CreateEntityFromCurrentEntity(68, other);
        other->zPriority = (self->zPriority + 4);
        SetStep(GAIBON_IDLE);
        break;
REDACTED
REDACTED
        if (!self->animFrameDuration && self->animFrameIdx == 1) {
            PlaySfxPositional(NA_SE_EN_GAIBON_FLAP_WINGS);
        }
        if (self->hitFlags) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
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
            if (!AnimateEntity(D_80181264, self)) {
                SetStep(4);
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
REDACTED
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
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
            break;
        }
        break;
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
            /* fallthrough */
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_801812DC, self) != 0) {

            } else {
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
                SetStep(GAIBON_LANDING_AFTER_SHOOTING);
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
            } else if (!other->ext.GS_Props.pickupFlag) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
                self->velocityX = 0;
                self->velocityY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
            /* fallthrough */
        case GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT:
            if (UnkCollisionFunc3(D_80181240) & 1) {
                PlaySfxPositional(NA_SE_EN_GAIBON_SCREAM);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (self->flags & FLAG_DEAD) {
                    PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                    SetStep(GAIBON_DYING);
                } else {
                    PlaySfxPositional(NA_SE_EN_GAIBON_SCREAM);
                }
            }
            break;
REDACTED
REDACTED
REDACTED
                self->palette = D_80180D30[3] + self->ext.GS_Props.flag;
                if (self->ext.GS_Props.flag == 6) {
                    self->flags &= ~0xF;
                    SetStep(4);
                }
            }
            break;
        }
        break;
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_80181304, self) == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 0x1F;
                self->flags &= ~0xF;
                // do-while needed on PSX but not PSP
                do {
                    self->palette = D_80180D30[3];
                    PlaySfxPositional(SFX_EXPLODE_SMALL);
                    self->step_s++;
                } while (0);
            }
            break;
REDACTED
REDACTED
                PlaySfxPositional(NA_SE_EN_GAIBON_FLAME);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_WARG_EXP_OPAQUE, self, other);
                    other->posY.i.hi += 28;
                    // Scatter bones randomly between +- 32
                    other->posX.i.hi += ((Random() & 63) - 32);
                    other->zPriority = self->zPriority + 1;
                    other->params = 0;
                }
            }
            if (!(--self->ext.GS_Props.timer)) {
REDACTED
REDACTED
REDACTED
REDACTED
            break;
        }
        break;
    // Unreachable debug mode
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
    if (!(self->flags & FLAG_DEAD)) {
        xVar = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if ((self->velocityX > 0) && (xVar > 0x310)) {
            self->posX.i.hi = 0x310 - g_Tilemap.scrollX.i.hi;
        }
        if ((self->velocityX < 0) && (xVar < 0x60)) {
            self->posX.i.hi = 0x60 - g_Tilemap.scrollX.i.hi;
        }
        if ((self->velocityY > 0) && (yVar > 0x1A4)) {
            self->posY.i.hi = 0x1A4 - g_Tilemap.scrollY.i.hi;
        }
        hitboxPtr = &D_80181310[0];
        hitboxPtr += D_80181340[self->animCurFrame] * 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr++;
    }
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
        InitializeEntity(D_80180D48);
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
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
