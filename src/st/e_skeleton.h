// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

extern s32 D_us_80181ACC;

typedef enum {
    SKELETON_INIT,
    SKELETON_IDLE,
    SKELETON_WALK_TOWARDS_PLAYER,
    SKELETON_WALK_AWAY_FROM_PLAYER,
    SKELETON_ATTACK,
    SKELETON_JUMP,
    SKELETON_DESTROY,
    SKELETON_LIB_UNK = 32
} SKELETON_STEPS;

typedef enum {
    SKELETON_JUMPING,
    SKELETON_IN_AIR,
    SKELETON_LAND
} SkeletonJumpSubSteps;

static u8 anim_walk[] = {0x06, 0x01, 0x04, 0x02, 0x04, 0x03, 0x06,
                         0x04, 0x05, 0x05, 0x05, 0x06, 0x00};
static u8 anim_walk_backwards[] = {0x06, 0x01, 0x05, 0x06, 0x05, 0x05, 0x06,
                                   0x04, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 anim_throw_bone[] = {0x05, 0x07, 0x06, 0x08, 0x05, 0x09, 0x05,
                               0x0A, 0x05, 0x0B, 0x05, 0x0C, 0xFF, 0x00};
static u8 anim_jump1[] = {0x01, 0x01, 0x04, 0x0D, 0x04, 0x0E, 0x01, 0x01, 0x00};
static u8 anim_jump2[] = {
    0x01, 0x01, 0x04, 0x0D, 0x06, 0x0E, 0x04, 0x0D, 0x01, 0x01, 0x00};
static u16 anim_bone_rot[] = {0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010};
static u8 dead_parts_selector[] = {0x30, 0x20, 0x14, 0x0C, 0x18, 0x10};
static u32 dead_parts_velocity_x[] = {
    FIX(.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75)};
static u32 dead_parts_velocity_y[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-.875)};
static s16 dead_parts_pos_x[] = {0 - 4, 0, 4, -4, -4, 4};
static s16 dead_parts_pos_y[] = {-16, -8, -4, -4, 9, 9};
static u8 attack_timer_cycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40}, {0xF0, 0xC0, 0xA0, 0x80}};
static u32 bone_projectile_velocity_x[] = {
    FIX(-.125), FIX(-.5),  FIX(-1), FIX(-1.5),
    FIX(-2),    FIX(-2.5), FIX(-3), FIX(-3.5)};
static s16 sensors_ground[][2] = {{0, 19}, {0, 4}, {8, -4}, {-16, 0}};
static s16 sensors_special[] = {0, 19, 8, 0};
static s16 sensors_move[][2] = {{-12, 16}, {0, -16}, {0, -16}};

static void SkeletonAttackCheck(Entity* self) {
    u16 unk = 1 & 0xFFFF;
    u16 collision;
    if ((UnkCollisionFunc2(sensors_special) & 0x60) == 0x60) {
        self->posX.val -= self->velocityX;
    }

    collision = UnkCollisionFunc(sensors_move, LEN(sensors_move));
    if (!(unk & 1) || (collision & 2)) {
        SetStep(SKELETON_JUMP);
        return;
    }

    if (!--self->ext.skeleton.attackTimer) {
        SetStep(SKELETON_ATTACK);
    }
}

void EntitySkeleton(Entity* self) {
    Entity* newEntity;
    u8 animStatus; // reused for multiple things
    u8 i;

#ifdef STAGE_IS_LIB
    if (self->params & 0x10 && D_us_80181ACC & 2) {
        self->hitFlags |= 3;
        self->flags |= FLAG_DEAD;
    }
#endif

    if (self->flags & FLAG_DEAD) {
        self->step = SKELETON_DESTROY;
    }

    switch (self->step) {
    case SKELETON_INIT:
        InitializeEntity(g_EInitSkeleton);
        self->ext.skeleton.attackTimer = 80; // Skeleton attack timer cycle
        self->ext.skeleton.facingLeft = 0;   // Facing init
        self->ext.skeleton.attackTimerIndex = 0;
#ifdef STAGE_IS_LIB
        if (self->params & 0x10) {
            self->flags |= FLAG_UNK_2000;
            self->hitboxState = 0;
            self->animCurFrame = 0;
            self->step = SKELETON_LIB_UNK;
            return;
        }
        break;
    case SKELETON_LIB_UNK:
        func_us_801BB8DC(sensors_ground);
#endif
        break;
    case SKELETON_IDLE: // Wait for player to be close enough
        if (UnkCollisionFunc3(sensors_ground) != 0) {
            self->step++;
        }
        break;
    case SKELETON_WALK_TOWARDS_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft;
        AnimateEntity(anim_walk, self);

        if (self->ext.skeleton.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() < 76) {
            self->step = SKELETON_WALK_AWAY_FROM_PLAYER;
        }
        SkeletonAttackCheck(self);
        break;
    case SKELETON_WALK_AWAY_FROM_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft ^ 1;
        AnimateEntity(anim_walk_backwards, self);

        if (self->ext.skeleton.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() > 92) {
            self->step = SKELETON_WALK_TOWARDS_PLAYER;
        }
        SkeletonAttackCheck(self);
        break;
    case SKELETON_ATTACK:
        animStatus = AnimateEntity(anim_throw_bone, self);
        if (!animStatus) {
            SetStep(SKELETON_WALK_AWAY_FROM_PLAYER);
            animStatus = (++self->ext.skeleton.attackTimerIndex) & 3;
            self->ext.skeleton.attackTimer =
                attack_timer_cycles[self->params & 1][animStatus];
            break;
        }

        if ((animStatus & 0x80) && (self->animCurFrame == 10)) {
            if ((self->posX.i.hi >= -16 && self->posX.i.hi <= 272) &&
                (self->posY.i.hi >= 0 && self->posY.i.hi <= 240)) {
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) { // Spawn bone
                    PlaySfxPositional(SFX_BONE_THROW);
                    CreateEntityFromCurrentEntity(
                        E_SKELETON_THROWN_BONE, newEntity);
                    if (self->facingLeft) {
                        newEntity->posX.i.hi -= 8;
                    } else {
                        newEntity->posX.i.hi += 8;
                    }
                    newEntity->posY.i.hi -= 16;
                    newEntity->facingLeft = self->facingLeft;
                }
            }
        }
        break;
    case SKELETON_JUMP:
        switch (self->step_s) {
        case SKELETON_JUMPING:
            if (!(AnimateEntity(anim_jump1, self) & 1)) {
                animStatus = self->ext.skeleton.facingLeft;
                if (!(Random() & 3)) {
                    animStatus ^= 1;
                }

                if (animStatus) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = FIX(-2);
                }

                self->velocityY = FIX(-3);
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;
        case SKELETON_IN_AIR:
            if (UnkCollisionFunc3(sensors_ground) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(sensors_move, 2);
            break;
        case SKELETON_LAND:
            if (AnimateEntity(anim_jump2, self) & 1) {
                self->step_s = 0;
                SetStep(SKELETON_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;
    case SKELETON_DESTROY:
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
        for (i = 0; i < 6; i++) { // Spawn Skeleton pieces
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_SKELETON_PIECES, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = i;
                newEntity->ext.skeleton.explosionTimer = dead_parts_selector[i];
                if (self->facingLeft) {
                    newEntity->posX.i.hi -= dead_parts_pos_x[i];
                } else {
                    newEntity->posX.i.hi += dead_parts_pos_x[i];
                }
                newEntity->posY.i.hi += dead_parts_pos_y[i];
                newEntity->velocityX = dead_parts_velocity_x[i];
                newEntity->velocityY = dead_parts_velocity_y[i];
            } else {
                break;
            }
        }
        DestroyEntity(self);
        break;
    }
}

void EntitySkeletonPieces(Entity* self) { // From skeleton death explosion
    if (self->step) {
        if (--self->ext.skeleton.explosionTimer) {
            self->rotZ += anim_bone_rot[self->params];
            FallEntity();
            MoveEntity();
            return;
        }

        self->entityId = E_EXPLOSION;
        self->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }

    InitializeEntity(g_EInitSkeletonPieces);
    self->animCurFrame = self->params + 15;
    self->drawFlags = FLAG_DRAW_ROTZ;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void EntitySkeletonThrownBone(Entity* self) { // Bone Projectile from Skeleton
    u32 xDistanceToPlayer;
    u32 velocityX;

    if (self->step) {
        if (self->flags & FLAG_DEAD) {
            EntityExplosionSpawn(0, 0);
            return;
        }

        self->rotZ += 0x80;
        self->velocityY += 0x2400;
        MoveEntity();

        if (self->posY.i.hi > 240) {
            DestroyEntity(self);
        }
    } else {
        InitializeEntity(g_EInitSkeletonBone);
        self->posY.val -= FIX(0.0625);
        xDistanceToPlayer = (u32)GetDistanceToPlayerX() >> 5;
        if (xDistanceToPlayer > 7) {
            xDistanceToPlayer = 7;
        }
        velocityX = bone_projectile_velocity_x[xDistanceToPlayer];

        if (self->facingLeft) {
            velocityX = -velocityX;
        }

        self->velocityX = velocityX;
        self->velocityY = FIX(-4.5);
        self->drawFlags = FLAG_DRAW_ROTZ;
    }
}

// Unclear if this has a way to run. Not called, and not in
// the main entity list.
void UnusedSkeletonEntity(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitSkeleton);
        self->rotX = 0x120;
        self->rotY = 0x200;
        self->unk6C = 0;
        self->hitboxState = 0;
        self->drawFlags |= FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        return;
    }

    self->facingLeft = self[-1].facingLeft;
    self->zPriority = self[-1].zPriority - 1;
    self->animCurFrame = self[-1].animCurFrame;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi - 20;

    if (self[-1].entityId != E_SKELETON) {
        DestroyEntity(self);
    }
}
