#include "sfx.h"
#include "sotn.h"

typedef enum {
    E_AXE_KNIGHT_AXE = 0x2A,
    E_BONE_SCIMITAR_HEAD = 0x28,
    E_FIRE = 0x38,
    E_SLOGRA_SPEAR = 0x41,
    E_SLOGRA_SPEAR_PROJECTILE = 0x42,
    E_GAIBON = 0x43,
    E_GAIBON_SMALL_FIREBALL = 0x45,
    E_GAIBON_BIG_FIREBALL = 0x46,
} ObjectIds;

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

#define SLOGRA self[-1]

int func_801BCCFC(void*) { return 0; }
void func_801C29B0(s32 sfxId) {}

#define BOSS_FLAG_DOORS_CLOSED (1 << 0)
#define BOSS_FLAG_DOORS_OPEN (1 << 1)
#define BOSS_FLAG_FIGHT_BEGIN (1 << 2)
#define BOSS_FLAG_GAIBON_DEAD (1 << 3)
#define BOSS_FLAG_SLOGRA_DEAD (1 << 4)

int g_BossFlag = 0;
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
        InitializeEntity(GetStagePtr(0x80180D30));
        CreateEntityFromCurrentEntity(0x44, &self[1]);
        self[1].zPriority = self->zPriority + 4;
        SetStep(GAIBON_IDLE);
        break;

    case GAIBON_IDLE:
        AnimateEntity(GetStagePtr(0x80181250), self);
        if (*(s32*)&self->animFrameIdx == 1) {
            func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
        }
        SetStep(GAIBON_FLY_TOWARDS_PLAYER);
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
            AnimateEntity(GetStagePtr(0x80181250), self);
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
            if (AnimateEntity(GetStagePtr(0x80181264), self) == 0) {
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
            AnimateEntity(GetStagePtr(0x80181298), self);
            if (*(s32*)&self->animFrameIdx == 1) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAP_WINGS);
            }

            if (self->ext.GS_Props.nearDeath != 0) {
                shootSpeed = 7;
            } else {
                shootSpeed = 15;
            }
            if (self->ext.GS_Props.timer & shootSpeed == 0) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[STAGE_ENTITY_START + 0x40]);
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
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case GAIBON_FLY_SHOOT_FIREBALLS_END:
            MoveEntity();
            self->accelerationX -= self->accelerationX / 32;
            self->accelerationY -= self->accelerationY / 32;
            if (AnimateEntity(GetStagePtr(0x80181264), self) == 0) {
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
            if (collider.unk0 & 1) {
                self->posY.i.hi = self->posY.i.hi + *(u16*)&collider.unk18;
                self->step_s++;
            }
            break;

        case GAIBON_FALLING_ON_GROUND:
            if (AnimateEntity(GetStagePtr(0x801812C0), self) == 0) {
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
            if (AnimateEntity(GetStagePtr(0x801812CC), self) == 0) {
                self->ext.GS_Props.timer = 64;
                if (self->ext.GS_Props.nearDeath != 0) {
                    self->ext.GS_Props.timer = 128;
                }
                self->step_s++;
            }
            break;

        case GAIBON_SHOOT_FROM_GROUND_FACE_SHOOTING:
            if (!(self->ext.GS_Props.timer % 16)) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[STAGE_ENTITY_START + 0x40]);
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
            if (AnimateEntity(GetStagePtr(0x801812DC), self) == 0) {
                self->step_s++;
            }
            break;

        case GAIBON_FLY_SHOOT_BIG_FIREBALL_SHOOTING:
            if (AllocEntity(&g_Entities[STAGE_ENTITY_START],
                            &g_Entities[STAGE_ENTITY_START + 0x40]) != 0) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[STAGE_ENTITY_START + 0x40]);
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
            AnimateEntity(GetStagePtr(0x801812AC), self);
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
            AnimateEntity(GetStagePtr(0x801812AC), self);
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
            if (func_801BCCFC(NULL) & 1) {
                func_801C29B0(NA_SE_EN_GAIBON_SCREAM);
                SetSubStep(GAIBON_NEAR_DEATH_FLOOR_LANDING);
            }
            break;

        case GAIBON_NEAR_DEATH_FLOOR_LANDING:
            if (AnimateEntity(GetStagePtr(0x801812F0), self) == 0) {
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
            if (AnimateEntity(GetStagePtr(0x801812FC), self) == 0) {
                self->ext.GS_Props.flag++;
                self->palette =
                    self->ext.GS_Props.flag + GetStagePtr(0x80180D36);
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
            animStatus = AnimateEntity(GetStagePtr(0x80181304), self);
            if (animStatus == 0) {
                self->ext.GS_Props.timer = 96;
                self->animCurFrame = 31;
                self->flags &= ~0xF;
                do {
                } while (0);
                self->palette = GetStagePtr(0x80180D36);
                func_801C29B0(NA_SE_EN_GAIBON_FLAME_OUT);
                self->step_s++;
            }
            break;

        case GAIBON_DYING_TURN_INTO_BONES:
            if ((self->ext.GS_Props.timer % 8) == 0) {
                func_801C29B0(NA_SE_EN_GAIBON_FLAME);
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[STAGE_ENTITY_START + 0x40]);
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

        // hitbox = &D_801815B4[self->animCurFrame][D_80181584];
        // hitbox--;
        // hitbox++;
        // self->unk10 = *hitbox++;
        // self->unk12 = *hitbox++;
        // self->hitboxWidth = hitbox[0];
        // self->hitboxHeight = hitbox[1];
    }
}
