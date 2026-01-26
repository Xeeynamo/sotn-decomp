// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitBladeSoldier;
extern EInit g_EInitBladeSoldierAttackHitbox;

static s16 sensors_ground[] = {0, 20, 0, 4, 8, -4, -16, 0};
static s16 sensors_wall[] = {0, 20, 12, 0};
static AnimateEntityFrame anim_walk_towards[] = {
    {.duration = 6, .pose = 0x01},
    {.duration = 4, .pose = 0x02},
    {.duration = 4, .pose = 0x03},
    {.duration = 6, .pose = 0x04},
    {.duration = 5, .pose = 0x05},
    {.duration = 5, .pose = 0x06},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_walk_forward_back[] = {
    {.duration = 6, .pose = 0x01},
    {.duration = 5, .pose = 0x06},
    {.duration = 5, .pose = 0x05},
    {.duration = 6, .pose = 0x04},
    {.duration = 4, .pose = 0x03},
    {.duration = 4, .pose = 0x02},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_short_hop[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 4, .pose = 0x21},
    {.duration = 4, .pose = 0x22},
    {.duration = 1, .pose = 0x01},
    POSE_END,
};
static AnimateEntityFrame anim_hop_land[] = {
    {.duration = 1, .pose = 0x01}, {.duration = 4, .pose = 0x21},
    {.duration = 6, .pose = 0x22}, {.duration = 4, .pose = 0x21},
    {.duration = 1, .pose = 0x01}, POSE_END,
};
static AnimateEntityFrame anim_idle[] = {
    {.duration = 4, .pose = 0x01},  {.duration = 5, .pose = 0x21},
    {.duration = 15, .pose = 0x22}, {.duration = 6, .pose = 0x21},
    {.duration = 4, .pose = 0x01},  POSE_LOOP(0),
};
static AnimateEntityFrame anim_charge_stab[] = {
    {.duration = 5, .pose = 0x01},
    {.duration = 5, .pose = 0x02},
    {.duration = 5, .pose = 0x07},
    {.duration = 6, .pose = 0x08},
    {.duration = 3, .pose = 0x09},
    {.duration = 3, .pose = 0x0A},
    {.duration = 3, .pose = 0x0B},
    {.duration = 3, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},
    {.duration = 2, .pose = 0x0E},
    {.duration = 4, .pose = 0x0D},
    {.duration = 4, .pose = 0x0E},
    {.duration = 5, .pose = 0x0D},
    {.duration = 6, .pose = 0x0E},
    {.duration = 2, .pose = 0x0F},
    {.duration = 2, .pose = 0x10},
    {.duration = 1, .pose = 0x11},
    {.duration = 1, .pose = 0x12},
    {.duration = 1, .pose = 0x13},
    {.duration = 1, .pose = 0x14},
    POSE_END,
};
static AnimateEntityFrame anim_sword_twirl[] = {
    {.duration = 3, .pose = 0x15},
    {.duration = 4, .pose = 0x16},
    {.duration = 4, .pose = 0x17},
    {.duration = 3, .pose = 0x18},
    {.duration = 2, .pose = 0x19},
    {.duration = 2, .pose = 0x1A},
    {.duration = 2, .pose = 0x1B},
    {.duration = 2, .pose = 0x1C},
    {.duration = 2, .pose = 0x1D},
    {.duration = 3, .pose = 0x1E},
    {.duration = 4, .pose = 0x1F},
    {.duration = 4, .pose = 0x04},
    {.duration = 4, .pose = 0x05},
    {.duration = 4, .pose = 0x06},
    POSE_END,
};
static AnimateEntityFrame anim_finish_attack[] = {
    {.duration = 3, .pose = 0x15},
    {.duration = 3, .pose = 0x16},
    {.duration = 3, .pose = 0x20},
    {.duration = 4, .pose = 0x04},
    {.duration = 4, .pose = 0x05},
    {.duration = 4, .pose = 0x06},
    POSE_END,
};

static u16 death_parts_rotation[] = {
    ROT(22.5),  ROT(11.25),   ROT(6.328125), ROT(2.8125),
    ROT(5.625), ROT(1.40625), ROT(2.8125),   ROT(-2.8125)};
static u8 death_part_fall_durations[] = {
    0x30, 0x20, 0x14, 0x0C, 0x18, 0x10, 0x40, 0x30};
static s32 death_parts_velocityX[] = {
    FIX(0.75), FIX(1.75), FIX(1.5),  FIX(1.0),
    FIX(2.0),  FIX(1.75), FIX(-0.5), FIX(0.5)};
static s32 death_parts_velocityY[] = {
    FIX(-5.0), FIX(-3.0),   FIX(-2.0), FIX(-3.0),
    FIX(-4.0), FIX(-0.875), FIX(-6.0), FIX(-4.5)};
static s16 death_parts_posX[] = {-4, 0, 4, -4, -4, 4, -6, 6};
static s16 death_parts_posY[] = {-16, -8, -4, -4, 9, 9, 2, -2};

static u8 attack_timers[] = {0x80, 0x08, 0x08, 0x40, 0xF0, 0xC0, 0xA0, 0x80};
static s16 sensors_unk[] = {-12, 16, 0, -16, 0, -16};

// This is indexed off the current animation frame
static s8 hitbox_indices[] = {0, 2, 3, 4, 4, 4, 0, 0};
// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 hitbox_dimensions[][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {-4, -18, 12, 7},
    {-17, -10, 13, 9},
    {-25, -3, 20, 3}};

enum BladeSoldierSteps {
    INIT = 0,
    FALL_TO_GROUND = 1,
    IDLE = 2,
    WALK_TOWARDS = 3,
    WALK_FORWARD_BACK = 4,
    CHARGE_STAB = 5,
    SHORT_HOP = 6,
    DEATH = 7
};

static void CheckSurroundings(void) {
    s32 collisionTestOne;
    u16 collisionTestTwo;

    collisionTestOne = UnkCollisionFunc2(sensors_wall);
    if (collisionTestOne == 0x80) {
        collisionTestTwo = UnkCollisionFunc(sensors_unk, 3);
        // Think this is triggered when encountering an edge of a pit or hole
        if (collisionTestTwo & 2) {
            SetStep(SHORT_HOP);
        }
    } else if (!g_CurrentEntity->ext.bladeSoldier.attackTimer) {
        // If our attack timer has expired and the player
        // is close enough, attack
        if (GetDistanceToPlayerX() < 0x40 &&
            g_CurrentEntity->facingLeft ^ (GetSideToPlayer() & 1)) {
            SetStep(CHARGE_STAB);
        }
    } else {
        g_CurrentEntity->ext.bladeSoldier.attackTimer--;
    }
}

static void SpawnDustParticles(void) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
    if (newEntity != NULL) {
        CreateEntityFromEntity(E_INTENSE_EXPLOSION, g_CurrentEntity, newEntity);
        newEntity->posY.i.hi += 0x14;
        if (g_CurrentEntity->facingLeft) {
            newEntity->posX.i.hi -= 4;
        } else {
            newEntity->posX.i.hi += 4;
        }
        newEntity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        newEntity->scaleX = newEntity->scaleY = 0x80;
        newEntity->zPriority = g_CurrentEntity->zPriority + 2;
        newEntity->params = 0x10;
    }
}

void EntityBladeSoldier(Entity* self) {
    Entity* entity;
    s32 i;
    s32 var_s2;

    if (self->flags & FLAG_DEAD) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBladeSoldier);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_BLADE_SOLDIER_ATTACK_HITBOX, entity);
        break;
    case FALL_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground)) {
            SetStep(IDLE);
        }
        break;
    case IDLE:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(anim_idle, self);

        // When the player is close enough wake and begin walking to and fro
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(WALK_FORWARD_BACK);
        }
        break;
    case WALK_TOWARDS:
        if (!AnimateEntity(anim_walk_towards, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.bladeSoldier.walkDirection = self->facingLeft;

        if (self->ext.bladeSoldier.walkDirection) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        // Once we're back close enough to the player,
        // begin the to and fro walk again
        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = WALK_FORWARD_BACK;
        }

        CheckSurroundings();
        break;
    case WALK_FORWARD_BACK:
        if (!AnimateEntity(anim_walk_forward_back, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        // Walk left and right repeatedly
        self->ext.bladeSoldier.walkDirection = self->facingLeft ^ 1;

        if (self->ext.bladeSoldier.walkDirection) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        // If the player gets too far away walk directly towards them
        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = WALK_TOWARDS;
        }

        CheckSurroundings();
        break;
    case CHARGE_STAB:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeSoldier.chargeDuration = 0x20;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_charge_stab, self)) {
                if (!--self->ext.bladeSoldier.chargeDuration) {
                    self->step_s++;
                }
            }

            if (self->animCurFrame == 0xF) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
            }

            if (!self->poseTimer && self->pose == 0xF) {
                PlaySfxPositional(SFX_BLADE_SOLDIER_CHARGE_STAB);
            }

            // NOTE: result appears unused?
            var_s2 = UnkCollisionFunc2(sensors_wall);
            break;
        case 2:
            // Occasionally Blade Soldier will do a sword twirl
            // animation after attacking
            if (Random() & 1) {
                self->ext.bladeSoldier.animPtr = (u8*)anim_sword_twirl;
            } else {
                self->ext.bladeSoldier.animPtr = (u8*)anim_finish_attack;
            }
            SetSubStep(3);
            break;
        case 3:
            var_s2 = AnimateEntity(self->ext.bladeSoldier.animPtr, self);
            UnkCollisionFunc2(sensors_wall);

            if (abs(self->velocityX) > 0x10000) {
                SpawnDustParticles();
            }

            self->velocityX -= self->velocityX / 16;
            // BUG! This abs looks to be written with incorrect bracket
            if (!var_s2 && abs(self->velocityX < FIX(0.25))) {
                self->step_s++;
            }

            break;
        case 4:
            // Set the amount of time until we attack the player again
            var_s2 = ++self->ext.bladeSoldier.attackCount & 7;
            self->ext.bladeSoldier.attackTimer = attack_timers[var_s2];
            SetStep(WALK_FORWARD_BACK);
        }
        break;
    case SHORT_HOP:
        switch (self->step_s) {
        case 0:
            if (!(AnimateEntity(anim_short_hop, self) & 1)) {
                var_s2 = self->ext.bladeSoldier.walkDirection;
                if (!(Random() & 3)) {
                    var_s2 ^= 1;
                }

                if (var_s2) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }

                self->velocityY = FIX(-3.0);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (UnkCollisionFunc3(sensors_ground)) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->step_s++;
            }
            CheckFieldCollision(sensors_unk, 2);
            break;
        case 2:
            if (!AnimateEntity(&anim_hop_land, self)) {
                SetStep(WALK_FORWARD_BACK);
            }
            break;
        }
        break;
    case DEATH:
        for (i = 0; i < 8; i++) {
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity == NULL) {
                break;
            }

            CreateEntityFromCurrentEntity(E_BLADE_SOLDIER_DEATH_PARTS, entity);
            entity->facingLeft = self->facingLeft;
            entity->params = i;
            entity->ext.bladeSoldier.deathPartFallDuration =
                death_part_fall_durations[i];
            if (self->facingLeft) {
                entity->posX.i.hi -= death_parts_posX[i];
            } else {
                entity->posX.i.hi += death_parts_posX[i];
            }
            entity->posY.i.hi += death_parts_posY[i];
            entity->velocityX = death_parts_velocityX[i];
            entity->velocityY = death_parts_velocityY[i];
        }

        entity = self + 1;
        DestroyEntity(entity);
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBladeSoldierDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.bladeSoldier.deathPartFallDuration) {
            self->rotate += death_parts_rotation[self->params];
            FallEntity();
            MoveEntity();
            return;
        }

        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = EXPLOSION_SMALL;
        self->step = 0;
        return;
    }

    InitializeEntity(g_EInitBladeSoldier);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 0x23;
    self->drawFlags = FLAG_DRAW_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void EntityBladeSoldierAttackHitbox(Entity* self) {
    s32 index;
    s8* ptr;
    Entity* bladeSoldier;

    if (!self->step) {
        InitializeEntity(g_EInitBladeSoldierAttackHitbox);
        self->hitboxState = 1;
    }

    bladeSoldier = self - 1;
    POS(self->posX) = POS(bladeSoldier->posX);
    self->facingLeft = bladeSoldier->facingLeft;
    index = bladeSoldier->animCurFrame;
    index -= 0xF;

    if (index < 0) {
        index = 0;
    }

    if (index > 5) {
        index = 0;
    }

    ptr = &hitbox_indices[index];
    index = *ptr;
    ptr = hitbox_dimensions[index];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;

    if (bladeSoldier->entityId != E_BLADE_SOLDIER) {
        DestroyEntity(self);
    }
}
