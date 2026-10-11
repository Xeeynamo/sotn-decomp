// SPDX-License-Identifier: AGPL-3.0-or-later

// Macros to let the two pieces access each other
#define TORSO (self + 1)
#define LEGS (self - 1)

static s16 sensors1[] = {0, 23, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 12, 0, 4, 8, -4, -16, 0};
static s16 sensors3[] = {16, 8, 255, 0};
static s16 sensors4[] = {0, 23, 8, 0};
static AnimateEntityFrame anim_walk[] = {{20, 1}, {20, 2}, {20, 3}, {20, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_flying[] = {{24, 4}, {24, 5}, {24, 6}, {24, 5}, POSE_LOOP(0)};
static AnimateEntityFrame anim_legs_walk[] = {{24, 7}, {24, 8}, {24, 9}, {24, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_unused_legs_walk[] = {{18, 8}, {18, 9}, POSE_END};
static AnimateEntityFrame anim_legs_waist_throb[] = {{8, 7}, {8, 10}, {4, 7}, {32, 10}, POSE_LOOP(0)};
static AnimateEntityFrame anim_separation[] = {{8, 1}, {8, 11}, {8, 12}, {8, 13}, {4, 14}, {2, 15}, POSE_END};
static AnimateEntityFrame anim_torso_throb[] = {{2, 16}, {2, 17}, POSE_LOOP(0)};
static AnimateEntityFrame anim_waist_throb_fast[] = {{2, 18}, {2, 19}, {2, 18}, {2, 19}, POSE_LOOP(0)};
static s16 D_us_80182898[] = {0x040, 0x0E0, 0x200, 0x180};
static s16 D_us_801828A0[] = {4,  3,  2,  2,  2,  1,  0,  0,  -1, -1, -1, -1,
                              -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2};

extern EInit g_EInitFlyingZombie;

typedef enum{
    FZ_INIT,
    FZ_INIT_GROUND,
    FZ_WALK,
    FZ_SEPARATION,
    FZ_4,
    FZ_5,
    FZ_6,
    FZ_7
} FlyingZombieSteps;

typedef enum{
    FZT_0,
    FZT_1,
    FZT_2,
    FZT_SEPARATION,
    FZT_4,
    FZT_5,
    FZT_6,
    FZT_7,
    FZT_8,
} FlyingZombieTorsoSteps;

// This entity is the legs, it places a torso at itself + 1
void EntityFlyingZombie(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if (!self->ext.flyingZombie.unk81 && (self->hitFlags & 3) &&
        self->step != FZ_SEPARATION) {
        self->hitboxState = 0;
        self->hitPoints = g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_2].hitPoints;
        SetStep(FZ_SEPARATION);
        PlaySfxPositional(SFX_FLYING_ZOMBIE_PAIN);
    }
    if (self->flags & FLAG_DEAD) {
        if (!self->ext.flyingZombie.unk81) {
            self->hitboxState = 0;
            self->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_2].hitPoints;
            SetStep(FZ_SEPARATION);
            PlaySfxPositional(SFX_FLYING_ZOMBIE_PAIN);
        } else if (self->step != FZ_7) {
            self->hitboxState = 0;
            SetStep(FZ_7);
        }
    }
    switch (self->step) {
    case FZ_INIT:
        InitializeEntity(g_EInitFlyingZombie);
        self->zPriority -= 2;
        self->hitboxOffX = 1;
        self->hitboxOffY = 10;
        tempEntity = TORSO;
        CreateEntityFromEntity(E_FLYING_ZOMBIE_TORSO, self, tempEntity);
        self->animCurFrame = 1;
#ifdef STAGE_IS_RNO2
        self->zPriority += 2;
#endif
        /* fallthrough */
    case FZ_INIT_GROUND:
        if (UnkCollisionFunc3(sensors1) & 1) {
            self->step_s = 0;
            self->step++;
        }
        break;

    case FZ_WALK:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.125);
            } else {
                self->velocityX = FIX(-0.125);
            }
            self->step_s++;
            break;

        case 1:
            AnimateEntity(anim_walk, self);
            UnkCollisionFunc2(sensors4);
            if (CheckColliderOffsets(sensors3, self->facingLeft)) {
                self->velocityX = 0;
            }
            if (self->ext.flyingZombie.unk7C++ > 0x80) {
                self->ext.flyingZombie.unk7C = 0;
                self->step_s--;
            }
            if (self->animCurFrame == 7) {
                if (self->facingLeft) {
                    self->velocityX -= FIX(1.0 / 128);
                } else {
                    self->velocityX += FIX(1.0 / 128);
                }
            }
            if (self->animCurFrame == 8) {
                if (self->facingLeft) {
                    self->velocityX += FIX(1.0 / 128);
                } else {
                    self->velocityX -= FIX(1.0 / 128);
                }
            }
            break;
        }
        break;

    case FZ_SEPARATION:
        if (!self->step_s) {
            PlaySfxPositional(SFX_FLYING_ZOMBIE_BODY_RIP);
            self->ext.flyingZombie.unk81 = 1;
            for (i = 0; i < 2; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_BLOOD_SPLATTER, self, tempEntity);
                    tempEntity->facingLeft = i;
                    tempEntity->posX.i.hi += 4 - (i * 8);
                }
            }
            tempEntity = TORSO;
            tempEntity->step = FZT_2;
            tempEntity->hitboxState = 0;
            self->step_s++;
        }
        if (!AnimateEntity(anim_separation, self)) {
            tempEntity = TORSO;
            tempEntity->step = FZT_SEPARATION;
            tempEntity->step_s = 0;
            tempEntity->hitboxOffX = 0;
            tempEntity->hitboxOffY = 0;
            tempEntity->facingLeft = self->facingLeft;
            tempEntity->posY.i.hi = self->posY.i.hi - 26;
            tempEntity->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_1].hitPoints;
            self->animCurFrame = 0x12;
            self->hitboxState = 3;
            SetStep(FZ_5);
        }
        break;

    case FZ_4:
        switch (self->step_s) {
        case 0:
            TORSO->step = FZT_SEPARATION;
            TORSO->animCurFrame = 0x10;
            TORSO->pose = 0;
            TORSO->poseTimer = 0;
            TORSO->facingLeft = self->facingLeft;
            TORSO->zPriority -= 8;
            TORSO->posY.i.hi = self->posY.i.hi - 10;
            self->ext.flyingZombie.unk81 = 1;
            self->animCurFrame = 0x12;
            self->ext.flyingZombie.unk7C = 8;
            self->ext.flyingZombie.unk7E = 0;
            self->step_s++;
            break;

        case 1:
            if (!--self->ext.flyingZombie.unk7C) {
                self->ext.flyingZombie.unk7E = 0;
                self->ext.flyingZombie.unk7C = 2;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.flyingZombie.unk7C) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 1;
                    tempEntity->posY.i.hi -= self->ext.flyingZombie.unk7E * 8;
                }
                self->ext.flyingZombie.unk7C = 6;
                self->ext.flyingZombie.unk7E++;
                if (self->ext.flyingZombie.unk7E > 1) {
                    PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
                    DestroyEntity(TORSO);
                    SetStep(FZ_5);
                }
            }
            break;
        }
        break;

    case FZ_5:
        if (!AnimateEntity(anim_waist_throb_fast, self)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }
        break;

    case FZ_6:
        switch (self->step_s) {
        case 0:
            self->ext.flyingZombie.unk7C = D_us_80182898[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0 / 16);
            } else {
                self->velocityX = FIX(-1.0 / 16);
            }
            self->step_s++;
            break;

        case 1:
            AnimateEntity(anim_legs_walk, self);
            UnkCollisionFunc2(sensors4);
            if (CheckColliderOffsets(sensors3, self->facingLeft)) {
                self->velocityX = 0;
            }
            if (self->animCurFrame == 1) {
                if (self->facingLeft) {
                    self->velocityX -= FIX(5.0 / 2048);
                } else {
                    self->velocityX += FIX(5.0 / 2048);
                }
            }
            if (self->animCurFrame == 2) {
                if (self->facingLeft) {
                    self->velocityX += FIX(5.0 / 2048);
                } else {
                    self->velocityX -= FIX(5.0 / 2048);
                }
            }
            if (!--self->ext.flyingZombie.unk7C) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case 2:
            if (!AnimateEntity(anim_legs_waist_throb, self)) {
                self->facingLeft = Random() & 1;
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 0;
            }
            break;
        }
        break;

    case FZ_7:
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
        DestroyEntity(self);
        break;

    case 16:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitFlyingZombieTorso;
void EntityBloodDrips(Entity* self);

void EntityFlyingZombieTorso(Entity* self) {
    Entity* tempEntity;
    s16 angle;
    s32 dx, dy;

    if ((self->flags & FLAG_DEAD) && self->step > FZT_5) {
        self->step = FZT_5;
        self->step_s = 0;
        self->hitboxState = 0;
        self->ext.flyingZombie.unk7E = 0;
        self->ext.flyingZombie.unk80 = 0;
        PlaySfxPositional(SFX_FLYING_ZOMBIE_DEATH);
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
    }
    switch (self->step) {
    case FZT_0:
        InitializeEntity(g_EInitFlyingZombieTorso);
        self->hitboxOffX = -4;
        self->hitboxOffY = -14;
        self->ext.flyingZombie.unk80 = 0;
        break;

    case FZT_1:
        self->facingLeft = LEGS->facingLeft;
        if ((self->hitFlags & 3) || (self->flags & FLAG_DEAD)) {
            self->hitboxState = 0;
            self->flags &= ~FLAG_DEAD;
            self->hitPoints = g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_1].hitPoints;
            LEGS->step = FZ_4;
            LEGS->step_s = 0;
            LEGS->pose = 0;
            LEGS->poseTimer = 0;
            self->step++;
        }
        break;

    case FZT_SEPARATION:
        self->hitboxState = 3;
        if (!self->step_s) {
            self->velocityY = FIX(-13.0 / 16);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.5 / 16);
        if (!AnimateEntity(anim_torso_throb, self)) {
            self->step_s = 0;
            self->step = FZT_6;
        }
        break;

    case FZT_5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            dx = self->posX.val - tempEntity->posX.val;
            dy = self->posY.val - tempEntity->posY.val;
            angle = ratan2(dx, -dy);
            self->rotate = angle;
            self->velocityX = rsin(angle) * 40;
            self->velocityY = rcos(angle) * -40;
            self->ext.flyingZombie.unk7C = 2;
            self->step_s++;
            break;

        case 1:
            if (UnkCollisionFunc3(sensors2) & 1) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 3;
                }
                DestroyEntity(self);
            } else {
                if (!--self->ext.flyingZombie.unk7C) {
                    tempEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                        tempEntity->params = 1;
                        tempEntity->drawFlags = ENTITY_ROTATE;
                        tempEntity->rotate = self->rotate;
                    }
                    self->ext.flyingZombie.unk7C = 6;
                }
            }
            break;
        }
        break;

    case FZT_6:
        MoveEntity();
        self->velocityY += FIX(0.5 / 16);
        if (self->velocityY > FIX(0.5)) {
            self->velocityY = 0;
            self->step = FZT_7;
        }
        break;

    case FZT_7:
        if ((Random() & 0x7F) == 0) {
            self->ext.flyingZombie.unk80 = 1;
        }
        if ((Random() & 0x1F) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_BLOOD_DRIPS, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 8) - 4;
                tempEntity->posY.i.hi += 13;
                tempEntity->pfnUpdate = EntityBloodDrips;
            }
        }
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->ext.flyingZombie.unk7C = 0x60;
            self->step_s++;
        } else {
            MoveEntity();
            AnimateEntity(anim_flying, self);
            if (!--self->ext.flyingZombie.unk7C) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 0;
                self->step++;
            }
        }
        break;

    case FZT_8:
        tempEntity = &PLAYER;
        if (!self->step_s) {
            self->ext.flyingZombie.unk7C = 0x40;
            angle = GetAngleBetweenEntitiesShifted(self, tempEntity);
            SetEntityVelocityFromAngle(angle, 6);
            self->step_s++;
        } else {
            if ((Random() & 0x7F) == 0) {
                self->ext.flyingZombie.unk80 = 1;
            }
            if ((Random() & 0x1F) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_BLOOD_DRIPS, self, tempEntity);
                    tempEntity->posX.i.hi += (Random() & 8) - 4;
                    tempEntity->posY.i.hi += 13;
                    tempEntity->pfnUpdate = EntityBloodDrips;
                }
            }
            MoveEntity();
            AnimateEntity(anim_flying, self);
            if (!--self->ext.flyingZombie.unk7C) {
                self->velocityY = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 0;
                self->step--;
            }
        }
        break;
    }
    if (self->step < FZT_2) {
        self->posX.i.hi = LEGS->posX.i.hi;
        self->posY.i.hi = LEGS->posY.i.hi;
    }
    if (self->ext.flyingZombie.unk80 && g_Timer % 3 == 0) {
        self->posY.i.hi += D_us_801828A0[self->ext.flyingZombie.unk7E];
        self->ext.flyingZombie.unk7E++;
        if (self->ext.flyingZombie.unk7E > LEN(D_us_801828A0) - 1) {
            self->ext.flyingZombie.unk7E = 0;
            self->ext.flyingZombie.unk80 = 0;
        }
    }
}
