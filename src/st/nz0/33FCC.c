/*
 * Overlay: NZ0
 * Enemy: Slogra & Gaibon Boss
 */

#include "nz0.h"

#define BOSS_FLAG_DOORS_CLOSED (1 << 0)
#define BOSS_FLAG_DOORS_OPEN (1 << 1)
#define BOSS_FLAG_FIGHT_BEGIN (1 << 2)
#define BOSS_FLAG_GAIBON_DEAD (1 << 3)
#define BOSS_FLAG_SLOGRA_DEAD (1 << 4)

#define GAIBON self[8]
#define SLOGRA self[-8]

typedef enum {
    SLOGRA_INIT,
    SLOGRA_FLOOR_ALIGN,
    SLOGRA_IDLE,
    SLOGRA_TAUNT_WITH_SPEAR,
    SLOGRA_SPEAR_POKE,
    SLOGRA_SPEAR_FIRE,
    SLOGRA_ATTACK,
    SLOGRA_KNOCKBACK = 8,
    SLOGRA_WALKING_WITH_SPEAR,
    SLOGRA_TAUNT_WITHOUT_SPEAR,
    SLOGRA_WALKING_WITHOUT_SPEAR,
    SLOGRA_LOSE_SPEAR,
    SLOGRA_GAIBON_COMBO_ATTACK,
    SLOGRA_DYING = 16,
    SLOGRA_DEBUG = 255,
} SlograSteps;

typedef enum {
    SLOGRA_FIRE_FACE_PLAYER,
    SLOGRA_FIRE_PROJECTILE,
    SLOGRA_FIRE_COOLDOWN,
    SLOGRA_FIRE_END,
} SlograSpearFireSubSteps;

typedef enum {
    SLOGRA_COMBO_ATTACK_START,
    SLOGRA_COMBO_ATTACK_PLUNGE,
    SLOGRA_COMBO_ATTACK_COOLDOWN,
} SlograComboAttackSubSteps;

typedef enum {
    SLOGRA_KNOCKBACK_FLOOR_CHECK,
    SLOGRA_KNOCKBACK_ACCEL,
    SLOGRA_KNOCKBACK_ARC,
} SlograKnockbackSubSteps;

typedef enum {
    SLOGRA_DYING_START,
    SLOGRA_DYING_EXPLODING,
    SLOGRA_DYING_END,
} SlograDyingSubSteps;

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
    GAIBON_DYING_REACT,
    GAIBON_DYING_TURN_INTO_BONES,
} GaibonDyingSubSteps;

// DECOMP_ME_WIP EntityCloseBossRoom https://decomp.me/scratch/bqgN9 95.04 %
// figuring out D_80181014 struct might help
// trigger to stop music and close slogra/gaibon room
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityCloseBossRoom);

// blocks that move to close slogra/gaibon room
void EntityBossRoomBlock(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D00);
        self->animCurFrame = 8;

    case 1:
        if (g_BossFlag & 1) {
            self->ext.GS_Props.timer = 16;
            self->step++;
        }
        break;

    case 2:
        if (self->subId == 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        func_801BD9A0(self, 8, 8, 5);
        if (!(g_blinkTimer & 3)) {
            g_api.PlaySfx(0x608);
        }
        if (--self->ext.GS_Props.timer) {
            break;
        }
        self->step++;
        break;

    case 3:
        func_801BD9A0(self, 8, 8, 5);
        if (g_BossFlag & BOSS_FLAG_DOORS_OPEN) {
            self->step++;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->subId != 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        break;
    }
}

s32 EntitySlograSpecialCollision(u16* unused) {
    /**
     * This function keeps Slogra between safe
     * boundaries of the room when he gets hit by the player.
     * EntitySlogra passes D_8018105C to this function but it's unused
     */
    s32 ret = 0;
    s32 slograPosX;

    MoveEntity();
    g_CurrentEntity->accelerationY += 0x4000;
    slograPosX = g_CurrentEntity->posX.i.hi + g_Camera.posX.i.hi;

    if (g_CurrentEntity->accelerationX > 0 && slograPosX > 896) {
        g_CurrentEntity->posX.i.hi = 896 - g_Camera.posX.i.hi;
    }

    if (g_CurrentEntity->accelerationX < 0 && slograPosX < 64) {
        g_CurrentEntity->posX.i.hi = 64 - g_Camera.posX.i.hi;
    }

    if (g_CurrentEntity->posY.i.hi + g_Camera.posY.i.hi > 416) {
        ret = 1;
        g_CurrentEntity->posY.i.hi = 416 - g_Camera.posY.i.hi;
        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;
    }

    return ret;
}

void EntitySlogra(Entity* self) {
    Entity* newEntity;
    s32 entityOnFloor;
    u8* animation;
    s32 hitPoints;
    s8* hitbox;

    self->ext.GS_Props.pickupFlag = 0;

    FntPrint("beri_flag %x\n", g_BossFlag);

    if (self->step >= SLOGRA_TAUNT_WITH_SPEAR) {
        if ((self->unk48 & 3) && (self->step != SLOGRA_KNOCKBACK)) {
            SetStep(SLOGRA_KNOCKBACK);
        }
        if (self->ext.GS_Props.nearDeath == false) {
            hitPoints = g_api.enemyDefs[243].hitPoints;
            if (hitPoints < 0) {
                hitPoints += 3;
            }
            if ((self->hitPoints < (hitPoints >> 2)) &&
                (self->step != SLOGRA_LOSE_SPEAR)) {
                SetStep(SLOGRA_LOSE_SPEAR);
            }
        }
    }

    if ((self->flags & 0x100) && (self->step != SLOGRA_DYING)) {
        SetStep(SLOGRA_DYING);
    }

    if (GAIBON.ext.GS_Props.grabedAscending) {
        if (self->step != SLOGRA_DYING) {
            if (self->step != SLOGRA_GAIBON_COMBO_ATTACK) {
                SetStep(SLOGRA_GAIBON_COMBO_ATTACK);
            }
        }
    }

    switch (self->step) {
    case SLOGRA_INIT:
        InitializeEntity(D_80180D0C);
        CreateEntityFromCurrentEntity(E_SLOGRA_SPEAR, &self[1]);

    case SLOGRA_FLOOR_ALIGN:
        if (EntitySlograSpecialCollision(D_8018105C) & 1) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case SLOGRA_IDLE:
        AnimateEntity(D_80181080, self);
        if (self->unk48 != 0) {
            g_BossFlag |= BOSS_FLAG_FIGHT_BEGIN;
        }
        if (g_BossFlag & BOSS_FLAG_FIGHT_BEGIN) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_TAUNT_WITH_SPEAR:
        if (AnimateEntity(D_80181080, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITH_SPEAR:
        if (self->step_s == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            if (self->ext.GS_Props.attackMode != 0) { // shoot projectile ?
                self->ext.GS_Props.flag = 1;
            } else {
                self->ext.GS_Props.flag = 0;
            }
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_80181074, self);
        self->facing = (GetPlayerSide() & 1) ^ 1;

        if (self->facing != self->ext.GS_Props.flag) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }
        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetPlayerDistanceX() < 72) {
                if (self->ext.GS_Props.attackMode == 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (self->ext.GS_Props.flag != 0) {
            if (GetPlayerDistanceX() > 112) {
                if (self->ext.GS_Props.attackMode != 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITH_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            if (self->ext.GS_Props.attackMode != 0) {
                SetStep(SLOGRA_SPEAR_FIRE);
            } else {
                SetStep(SLOGRA_SPEAR_POKE);
            }

            self->ext.GS_Props.attackMode ^= 1;
        }
        break;

    case SLOGRA_SPEAR_POKE:
        if (self->step_s == 0) {
            func_801C29B0(NA_SE_EN_SLOGRA_HISSING);
            self->step_s++;
        }
        if (AnimateEntity(D_801810B4, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        if (*(s32*)&self->animFrameIdx == 4) {
            func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_SLASH);
        }
        break;

    case SLOGRA_SPEAR_FIRE:
        switch (self->step_s) {
        case SLOGRA_FIRE_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;

        case SLOGRA_FIRE_PROJECTILE:
            if (AnimateEntity(D_8018108C, self) == 0) {
                func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_PROJECTILE);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_SLOGRA_SPEAR_PROJECTILE, self,
                                           newEntity);
                    if (self->facing != 0) {
                        newEntity->posX.i.hi += 68;
                    } else {
                        newEntity->posX.i.hi -= 68;
                    }
                    newEntity->posY.i.hi -= 6;
                    newEntity->facing = self->facing;
                    newEntity->zPriority = self->zPriority + 1;
                }
                SetSubStep(SLOGRA_FIRE_COOLDOWN);
            }
            break;

        case SLOGRA_FIRE_COOLDOWN:
            if (AnimateEntity(D_8018109C, self) == 0) {
                SetSubStep(SLOGRA_FIRE_END);
            }
            break;

        case SLOGRA_FIRE_END: // go back to standing position
            if (AnimateEntity(D_801810A8, self) == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
            }
            break;
        }
        break;

    case SLOGRA_KNOCKBACK: // Knocked up, Chance to get picked up by gaibon
        switch (self->step_s) {
        case SLOGRA_KNOCKBACK_FLOOR_CHECK:
            if (EntitySlograSpecialCollision(D_8018105C) & 1) {
                self->step_s++;
            }
            break;

        case SLOGRA_KNOCKBACK_ACCEL:
            self->accelerationY = -0x40000;
            if (!(GetPlayerSide() & 1)) {
                self->accelerationX = -0x8000;
            } else {
                self->accelerationX = 0x8000;
            }
            func_801C29B0(NA_SE_EN_SLOGRA_HURT);
            self->step_s++;

        case SLOGRA_KNOCKBACK_ARC:
            if (0x18000 > self->accelerationY) {
                self->ext.GS_Props.pickupFlag = 1;
            }
            entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
            self->accelerationY -= 0x2400;
            if (self->ext.GS_Props.nearDeath != 0) {
                animation = &D_80181114;
            } else {
                animation = &D_801810D4;
            }
            if (AnimateEntity(animation, self) == 0 && entityOnFloor & 1) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
                }
            }
        }
        break;

    case SLOGRA_LOSE_SPEAR:
        entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
        if (AnimateEntity(D_801810E8, self) == 0) {
            if (entityOnFloor & 1) {
                SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
            }
        }
        if (self->animFrameIdx >= 2) {
            self->ext.GS_Props.nearDeath = 1;
        }
        break;

    case SLOGRA_TAUNT_WITHOUT_SPEAR:
        if (AnimateEntity(D_80181108, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITHOUT_SPEAR:
        if (self->step_s == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->ext.GS_Props.flag = 1;
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_801810FC, self);
        self->facing = (GetPlayerSide() & 1) ^ 1;

        if (!(self->facing == self->ext.GS_Props.flag)) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }

        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetPlayerDistanceX() < 72) {
                self->ext.GS_Props.flag ^= 1;
            }
            if (self->ext.GS_Props.flag != 0) {
                if (GetPlayerDistanceX() > 112) {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        } else {
            if (GetPlayerDistanceX() > 112) {
                self->ext.GS_Props.flag ^= 1;
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            SetStep(SLOGRA_ATTACK);
        }
        break;

    case SLOGRA_ATTACK: // Attack without spear
        if (AnimateEntity(D_80181128, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        if (*(s32*)&self->animFrameIdx == 7) {
            func_801C29B0(NA_SE_EN_SLOGRA_BEAK_ATTACK);
        }
        break;

    case SLOGRA_GAIBON_COMBO_ATTACK:
        switch (self->step_s) {
        case SLOGRA_COMBO_ATTACK_START: // inmobilize, Gaibon picks him up
            if (!GAIBON.ext.GS_Props.grabedAscending) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_PLUNGE:
            if (self->ext.GS_Props.nearDeath != 0) {
                AnimateEntity(D_80181140, self);
            } else {
                AnimateEntity(D_80181158, self);
            }

            MoveEntity();
            self->accelerationY += 0x4000;
            if (self->posY.i.hi + g_Camera.posY.i.hi > 416) {
                self->posY.i.hi = 416 - g_Camera.posY.i.hi;
                func_801C29B0(NA_SE_EN_SLOGRA_FLOOR_STOMP);
                g_api.func_80102CD8(1);
                self->ext.GS_Props.timer = 16;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_COOLDOWN:
            if (--self->ext.GS_Props.timer == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
                }
            }
            break;
        }
        break;

    case SLOGRA_DYING:
        switch (self->step_s) {
        case SLOGRA_DYING_START:
            self->unk3C = 0;
            if (self->ext.GS_Props.nearDeath == 0) {
                self->ext.GS_Props.nearDeath = 1;
            }
            self->ext.GS_Props.timer = 64;
            func_801C29B0(NA_SE_EN_SLOGRA_DEATH_EXPLOSION);
            self->step_s++;

        case SLOGRA_DYING_EXPLODING:
            EntitySlograSpecialCollision(D_8018105C);
            AnimateEntity(D_80181150, self);
            if (!(g_blinkTimer % 4)) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->posX.i.hi -= 16 - (Random() & 31);
                    newEntity->posY.i.hi -= 16 - (Random() & 31);
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->subId = 1;
                }
            }

            if (--self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case SLOGRA_DYING_END:
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->subId = 3;
                newEntity->posY.i.hi += 16;
            }
            g_BossFlag |= BOSS_FLAG_SLOGRA_DEAD;
            DestroyEntity(self);
            return;
        }
        break;

    case SLOGRA_DEBUG:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                self->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    hitbox = &D_801811B8[self->animCurFrame][D_80181178];
    hitbox--;
    hitbox++;
    self->unk10 = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntitySlograSpear(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D18);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_801811E0;
        hitbox += 4 * D_80181218[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].ext.GS_Props.nearDeath != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C29B0(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D24);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(D_80181160, self) == 0) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_80181170, self);
        break;
    }
}

// Confirmed equivalent behaviour in game.
// Mostly regalloc, instruction reordering
// https://decomp.me/scratch/QGtpG
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityGaibon);
#else
void EntityGaibon(Entity* self) {
    s32 slograGaibonDistX;
    s32 slograGaibonDistY;
    Collider collider;
    Entity* newEntity;
    s32 animStatus;
    s32 shootSpeed;
    s16 hitPoints;
    s32 maxSpeed;
    s8* hitbox;
    s16 angle;
    s32 speed;
    s32 step; // !FAKE
    s32 var_s3;

    if (self->step != GAIBON_INIT && self->ext.GS_Props.nearDeath == 0) {
        hitPoints = g_api.enemyDefs[254].hitPoints;
        if (self->hitPoints < hitPoints / 2) {
            self->ext.GS_Props.grabedAscending = 0;
            self->ext.GS_Props.nearDeath = 1;
            SetStep(GAIBON_NEAR_DEATH);
        }
    }

    if (self->flags & 0x100 && self->step < GAIBON_NEAR_DEATH) {
        self->ext.GS_Props.grabedAscending = 0;
        self->unk3C = 0;
        SetStep(GAIBON_NEAR_DEATH);
    } else if (SLOGRA.ext.GS_Props.pickupFlag != 0) {
        if (self->step < GAIBON_LANDING_AFTER_SHOOTING) {
            SetStep(GAIBON_PICKUP_SLOGRA);
        }
    }

    switch (self->step) {
    case GAIBON_INIT:
        InitializeEntity(D_80180D30);
        CreateEntityFromCurrentEntity(0x44, &self[1]);
        self[1].zPriority = self->zPriority + 4;
        SetStep(GAIBON_IDLE);
        break;

    case GAIBON_IDLE:
        AnimateEntity(D_80181250, self);
        if (*(s32*)&self->animFrameIdx == 1) {
            func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
        }
        if (self->unk48 != 0) {
            g_BossFlag |= BOSS_FLAG_FIGHT_BEGIN;
        }
        if (g_BossFlag & BOSS_FLAG_FIGHT_BEGIN) {
            SetStep(GAIBON_FLY_TOWARDS_PLAYER);
        }
        break;

    case GAIBON_FLY_TOWARDS_PLAYER:
        switch (self->step_s) {
        case GAIBON_FLY_TOWARDS_PLAYER_BEGIN:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->ext.GS_Props.angle =
                ratan2((PLAYER.posY.i.hi - 32) - self->posY.i.hi,
                       PLAYER.posX.i.hi - self->posX.i.hi);
            self->ext.GS_Props.speed = 0;
            self->ext.GS_Props.timer = 96;
            if (self->ext.GS_Props.nearDeath != 0) {
                self->ext.GS_Props.timer = 48;
            }
            self->step_s++;

        case GAIBON_FLY_TOWARDS_PLAYER_MOVEMENT:
            if (self->ext.GS_Props.nearDeath != 0) {
                maxSpeed = 0x40000;
            } else {
                maxSpeed = 0x20000;
            }
            self->ext.GS_Props.speed += 0xA00;
            if (self->ext.GS_Props.speed >= maxSpeed) {
                self->ext.GS_Props.speed = maxSpeed;
            }
            speed = self->ext.GS_Props.speed;
            self->accelerationX =
                (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->accelerationY =
                (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
            MoveEntity();
            AnimateEntity(D_80181250, self);
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case GAIBON_FLY_TOWARDS_PLAYER_END:
            MoveEntity();
            self->accelerationX -= self->accelerationX / 32;
            self->accelerationY -= self->accelerationY / 32;
            if (AnimateEntity(D_80181264, self) == 0) {
                SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
            }
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
        }
        break;

    // flying up while shooting down at an angle
    case GAIBON_FLY_SHOOT_FIREBALLS:
        switch (self->step_s) {
        case GAIBON_FLY_SHOOT_FIREBALLS_BEGIN:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            newEntity = &PLAYER;
            var_s3 = newEntity->posX.i.hi;
            if (GetPlayerSide() & 1) {
                var_s3 += 0x60;
            } else {
                var_s3 -= 0x60;
            }
            self->ext.GS_Props.angle =
                ratan2(newEntity->posY.i.hi - 128 - self->posY.i.hi,
                       var_s3 - self->posX.i.hi);
            self->ext.GS_Props.speed = 0;
            self->ext.GS_Props.timer = 80;
            if (self->ext.GS_Props.nearDeath != 0) {
                self->ext.GS_Props.timer = 40;
            }
            self->step_s++;

        case GAIBON_FLY_SHOOT_FIREBALLS_MOVING_SHOOTING:
            if (self->ext.GS_Props.nearDeath != 0) {
                maxSpeed = 0x40000;
            } else {
                maxSpeed = 0x20000;
            }
            self->ext.GS_Props.speed += 0xA00;
            if (self->ext.GS_Props.speed >= maxSpeed) {
                self->ext.GS_Props.speed = maxSpeed;
            }
            speed = self->ext.GS_Props.speed;
            self->accelerationX =
                (speed * rcos(self->ext.GS_Props.angle)) >> 0xC;
            self->accelerationY =
                (speed * rsin(self->ext.GS_Props.angle)) >> 0xC;
            MoveEntity();
            AnimateEntity(D_80181298, self);
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }

            if (self->ext.GS_Props.nearDeath != 0) {
                shootSpeed = 7;
            } else {
                shootSpeed = 15;
            }
            if (self->ext.GS_Props.timer & shootSpeed == 0) {
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_GAIBON_SMALL_FIREBALL, self,
                                           newEntity);
                    func_801C29B0(NA_SE_EN_GAIBON_SMALL_FIREBALL);
                    newEntity->posY.i.hi -= 2;
                    if (self->facing != 0) {
                        newEntity->unk1E = 0x220;
                        newEntity->posX.i.hi += 12;
                    } else {
                        newEntity->unk1E = 0x5E0;
                        newEntity->posX.i.hi -= 12;
                    }
                }
            }
            newEntity->zPriority = self->zPriority + 1;
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case GAIBON_FLY_SHOOT_FIREBALLS_END:
            MoveEntity();
            self->accelerationX -= self->accelerationX / 32;
            self->accelerationY -= self->accelerationY / 32;
            if (AnimateEntity(D_80181264, self) == 0) {
                SetStep(GAIBON_LANDING_AFTER_SHOOTING);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(GAIBON_FLY_SHOOT_BIG_FIREBALL);
                }
            }
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
        }
        break;

    case GAIBON_LANDING_AFTER_SHOOTING:
        switch (self->step_s) {
        case GAIBON_LANDING_AFTER_SHOOTING_SETUP:
            self->animCurFrame = 9;
            self->accelerationX = 0;
            self->accelerationY = 0;
            self->step_s++;

        case GAIBON_FALLING_WITHOUT_MAP_COLLISION:
            MoveEntity();
            self->accelerationY += 0x1800;
            if (PLAYER.posY.i.hi - self->posY.i.hi < 48) {
                self->step_s++;
            }
            break;

        case GAIBON_FALLING_WITH_MAP_COLLISION:
            MoveEntity();
            self->accelerationY += 0x1800;
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 28,
                                 &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->posY.i.hi = self->posY.i.hi + *(u16*)&collider.unk18;
                self->step_s++;
            }
            break;

        case GAIBON_FALLING_ON_GROUND:
            if (AnimateEntity(D_801812C0, self) == 0) {
                SetStep(GAIBON_SHOOT_FROM_GROUND);
            }
        }
        break;

    case GAIBON_SHOOT_FROM_GROUND:
        switch (self->step_s) {
        case GAIBON_SHOOT_FROM_GROUND_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;

        case GAIBON_SHOOT_FROM_GROUND_FACE_SETUP:
            if (AnimateEntity(D_801812CC, self) == 0) {
                self->ext.GS_Props.timer = 64;
                if (self->ext.GS_Props.nearDeath != 0) {
                    self->ext.GS_Props.timer = 128;
                }
                self->step_s++;
            }
            break;

        case GAIBON_SHOOT_FROM_GROUND_FACE_SHOOTING:
            if (!(self->ext.GS_Props.timer % 16)) {
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    if (self->ext.GS_Props.nearDeath == 0) {
                        CreateEntityFromEntity(E_GAIBON_SMALL_FIREBALL, self,
                                               newEntity);
                        func_801C29B0(NA_SE_EN_GAIBON_SMALL_FIREBALL);
                    } else {
                        CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self,
                                               newEntity);
                        func_801C29B0(NA_SE_EN_GAIBON_BIG_FIREBALL);
                    }
                    newEntity->posY.i.hi -= 6;
                    if (self->facing != 0) {
                        newEntity->unk1E = 0;
                        newEntity->posX.i.hi += 16;
                    } else {
                        newEntity->unk1E = 0x800;
                        newEntity->posX.i.hi -= 16;
                    }
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                SetStep(GAIBON_FLY_TOWARDS_PLAYER);
            }
        }
        break;

    case GAIBON_FLY_SHOOT_BIG_FIREBALL:
        switch (self->step_s) {
        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SETUP:
            if (AnimateEntity(D_801812DC, self) == 0) {
                self->step_s++;
            }
            break;

        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING:
            if (AllocEntity(D_8007A958, &D_8007A958[32]) != 0) {
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self,
                                           newEntity);
                    func_801C29B0(NA_SE_EN_GAIBON_BIG_FIREBALL);
                    newEntity->posY.i.hi -= 2;
                    if (self->facing != 0) {
                        newEntity->unk1E = 0x220;
                        newEntity->posX.i.hi += 12;
                    } else {
                        newEntity->unk1E = 0x5E0;
                        newEntity->posX.i.hi -= 12;
                    }
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            self->accelerationY = -0x20000;
            if (self->facing != 0) {
                self->accelerationX = -0x20000;
            } else {
                self->accelerationX = 0x20000;
            }
            self->ext.GS_Props.timer = 32;
            self->step_s++;

        case GAIBON_FLY_SHOOT_BIG_FIREBALL_END:
            MoveEntity();
            self->accelerationX -= self->accelerationX / 16;
            self->accelerationY -= self->accelerationY / 16;
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                SetStep(GAIBON_LANDING_AFTER_SHOOTING);
            }
        }
        break;

    case GAIBON_PICKUP_SLOGRA:
        switch (self->step_s) {
        case GAIBON_PICKUP_SLOGRA_SETUP:
            if (SLOGRA.posX.i.hi - self->posX.i.hi > 0) {
                self->facing = 1;
            } else {
                self->facing = 0;
            }
            self->ext.GS_Props.speed = 0;
            self->step_s++;

        case GAIBON_PICKUP_SLOGRA_MOVING:
            slograGaibonDistX = SLOGRA.posX.i.hi - self->posX.i.hi;
            slograGaibonDistY = (SLOGRA.posY.i.hi - 28) - self->posY.i.hi;
            angle = ratan2(slograGaibonDistY, slograGaibonDistX);
            self->ext.GS_Props.speed += 0x8000;
            if (self->ext.GS_Props.speed >= 0x38000) {
                self->ext.GS_Props.speed = 0x38000;
            }
            speed = self->ext.GS_Props.speed;
            self->accelerationX = (speed * rcos(angle)) >> 0xC;
            self->accelerationY = (speed * rsin(angle)) >> 0xC;
            MoveEntity();
            if (ABS(slograGaibonDistX) < 8) {
                if (ABS(slograGaibonDistY) < 8) {
                    self->ext.GS_Props.grabedAscending = 1;
                    self->accelerationX = 0;
                    self->accelerationY = 0;
                    self->step_s++;
                } else {
                    if (SLOGRA.ext.GS_Props.pickupFlag == 0) {
                        self->ext.GS_Props.grabedAscending = 0;
                        SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
                    }
                }
            } else {
                if (SLOGRA.ext.GS_Props.pickupFlag == 0) {
                    self->ext.GS_Props.grabedAscending = 0;
                    SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
                }
            }
            break;

        case GAIBON_PICKUP_SLOGRA_ASCENDING:
            AnimateEntity(D_801812AC, self);
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
            MoveEntity();
            self->accelerationY -= 0xA00;
            if (self->accelerationY < -0x20000) {
                self->accelerationY = -0x20000;
            }
            self->ext.GS_Props.grabedAscending = 1;
            SLOGRA.posX.i.hi = self->posX.i.hi;
            SLOGRA.posY.i.hi = self->posY.i.hi + 28;
            if (self->posY.i.hi < 16) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->ext.GS_Props.timer = 96;
                self->step_s++;
            }
            break;

        case GAIBON_PICKUP_SLOGRA_AIMING:
            AnimateEntity(D_801812AC, self);
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }
            if (GetPlayerSide() & 1) {
                self->accelerationX -= 0xA00;
            } else {
                self->accelerationX += 0xA00;
            }
            if (self->accelerationX < -0x20000) {
                self->accelerationX = -0x20000;
            }
            if (self->accelerationX > 0x20000) {
                self->accelerationX = 0x20000;
            }
            MoveEntity();

            SLOGRA.accelerationY = 0;
            self->ext.GS_Props.grabedAscending = 0;
            SLOGRA.posX.i.hi = self->posX.i.hi;
            SLOGRA.posY.i.hi = self->posY.i.hi + 28;
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
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
            self->accelerationX = 0;
            self->accelerationY = 0;
            self->step_s++;

        case GAIBON_NEAR_DEATH_FLOOR_HIT_WAIT:
            if (func_801BCCFC(&D_80181240) & 1) {
                func_801C29B0(NA_SE_EN_GAIBON_SCREAM);
                SetSubStep(GAIBON_NEAR_DEATH_FLOOR_LANDING);
            }
            break;

        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            if (AnimateEntity(D_801812F0, self) == 0) {
                self->ext.GS_Props.flag = 0;
                SetSubStep(GAIBON_NEAR_DEATH_TRANSFORM);
                if (self->flags & 0x100) {
                    func_801C29B0(NA_SE_EN_GAIBON_COLLAPSE);
                    SetStep(GAIBON_DYING);
                } else {
                    func_801C29B0(NA_SE_EN_GAIBON_SCREAM);
                }
            }
            break;

        case GAIBON_NEAR_DEATH_TRANSFORM:
            if (AnimateEntity(D_801812FC, self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette = self->ext.GS_Props.flag + D_80180D36;
                if (self->ext.GS_Props.flag == 6) {
                    self->flags &= ~0xF;
                    SetStep(GAIBON_FLY_SHOOT_FIREBALLS);
                }
            }
        }
        break;

    case GAIBON_DYING:
        switch (self->step_s) {
        case GAIBON_DYING_REACT:
            animStatus = AnimateEntity(D_80181304, self);
            if (animStatus == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 31;
                self->flags &= ~0xF;
                do {
                } while (0);
                self->palette = D_80180D36;
                func_801C29B0(NA_SE_EN_GAIBON_FLAME_OUT);
                self->step_s++;
            }
            break;

        case GAIBON_DYING_TURN_INTO_BONES:
            if ((self->ext.GS_Props.timer % 8) == 0) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAME);
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FIRE, self, newEntity);
                    newEntity->posY.i.hi += 28;
                    newEntity->posX.i.hi -= 32 - (Random() & 63);
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->subId = 0;
                }
            }
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                g_BossFlag |= BOSS_FLAG_GAIBON_DEAD;
                DestroyEntity(self);
                return;
            }
        }
        break;

    case GAIBON_DEBUG:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                self->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }

    if (!(self->flags & 0x100)) {
        slograGaibonDistX = self->posX.i.hi + g_Camera.posX.i.hi;
        slograGaibonDistY = self->posY.i.hi + g_Camera.posY.i.hi;

        if (self->accelerationX > 0 && slograGaibonDistX > 784) {
            self->posX.i.hi = 784 - g_Camera.posX.i.hi;
        }

        if (self->accelerationX < 0 && slograGaibonDistX < 96) {
            self->posX.i.hi = 96 - g_Camera.posX.i.hi;
        }
        if (self->accelerationY > 0 && slograGaibonDistY > 420) {
            self->posY.i.hi = 420 - g_Camera.posY.i.hi;
        }

        hitbox = &D_80181340[self->animCurFrame][D_80181310];
        hitbox--;
        hitbox++;
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = hitbox[0];
        self->hitboxHeight = hitbox[1];
    }
}
#endif

void func_801B69E8(Entity* self) {
    Entity* prevEntity;
    s16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_80180D30);
        self->unk3C = 0;
    }

    prevEntity = &self[-1];
    self->facing = prevEntity->facing;
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

    if (prevEntity->objectId != E_GAIBON) {
        DestroyEntity(self);
    }
}

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D3C);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_8018136C, self);
        break;
    }
}

// large red projectile from gaibon
void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D48);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->flags |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181378, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_GAIBON_BIG_FIREBALL, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(D_80181388, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
