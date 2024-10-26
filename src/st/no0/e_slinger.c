// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

typedef enum {
    SLINGER_INIT,
    SLINGER_IDLE,
    SLINGER_WALK_TOWARDS_PLAYER,
    SLINGER_WALK_AWAY_FROM_PLAYER,
    SLINGER_ATTACK,
    SLINGER_JUMP,
    SLINGER_DESTROY
} SLINGER_STEPS;

typedef enum {
    SLINGER_JUMPING,
    SLINGER_IN_AIR,
    SLINGER_LAND
} SlingerJumpSubSteps;

static u8 anim_walk[] = {0x06, 0x01, 0x04, 0x02, 0x04, 0x03, 0x06,
                         0x04, 0x05, 0x05, 0x05, 0x06, 0x00};
static u8 anim_walk_backwards[] = {0x06, 0x01, 0x05, 0x06, 0x05, 0x05, 0x06,
                                   0x04, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 anim_throw_bone[] = {0x05, 0x07, 0x06, 0x08, 0x05, 0x09, 0x05,
                               0x0A, 0x05, 0x0B, 0x05, 0x0C, 0xFF, 0x00};
static u8 anim_jump1[] = {0x01, 0x01, 0x04, 0x0D, 0x04, 0x0E, 0x01, 0x01, 0x00};
static u8 anim_jump2[] = {
    0x01, 0x01, 0x04, 0x0D, 0x06, 0x0E, 0x04, 0x0D, 0x01, 0x01, 0x00};
static u16 anim_bone_rot[] = {
    0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010, 0x0030, 0x0000};
static s8 dead_parts_selector[] = {
    0x30, 0x20, 0x14, 0x0C, 0x18, 0x10, 0x20, 0x00};
static s32 dead_parts_velocity_x[] = {
    FIX(.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), 0};
static s32 dead_parts_velocity_y[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-.875), FIX(-4)};
static u16 dead_parts_pos_x[] = {-4, 0, 4, -4, -4, 4, 0, 0};
static u16 dead_parts_pos_y[] = {-16, -8, -4, -4, 9, 9, 0, 0};
static u8 attack_timer_cycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40}, {0xF0, 0xC0, 0xA0, 0x80}};
static s16 sensors_ground[][2] = {{0, 19}, {8, 0}};
static s16 sensors_move[][2] = {{-12, 16}, {0, -16}, {0, -16}};

void SlingerAttackCheck(Entity* self) {
    s32 groundCollision = UnkCollisionFunc2(sensors_ground);
    s16 moveCollision = UnkCollisionFunc(sensors_move, 3);

    if ((groundCollision & 0xFFFF) == 128 && (moveCollision & 2) != 0) {
        SetStep(SLINGER_JUMP);
    } else if (--self->ext.skeleton.attackTimer == 0) {
        SetStep(SLINGER_ATTACK);
    }
}

extern u16 g_EInitSlinger[];
void EntitySlinger(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    u8 i;

    if (self->flags & FLAG_DEAD) {
        self->step = SLINGER_DESTROY;
    }

    switch (self->step) {
    case SLINGER_INIT:
        InitializeEntity(g_EInitSlinger);
        self->ext.skeleton.attackTimer = 80; // Slinger attack timer cycle
        self->ext.skeleton.facingLeft = 0;   // Facing init
        self->ext.skeleton.attackTimerIndex = 0;
        break;
    case SLINGER_IDLE: // Wait for player to be close enough
        if (UnkCollisionFunc3(sensors_ground) != 0) {
            self->step++;
        }
        break;
    case SLINGER_WALK_TOWARDS_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft;
        AnimateEntity(anim_walk, self);

        if (self->ext.skeleton.facingLeft == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() < 76) {
            self->step = SLINGER_WALK_AWAY_FROM_PLAYER;
        }
        SlingerAttackCheck(self);
        break;
    case SLINGER_WALK_AWAY_FROM_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft ^ 1;
        AnimateEntity(anim_walk_backwards, self);

        if (self->ext.skeleton.facingLeft == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() > 92) {
            self->step = SLINGER_WALK_TOWARDS_PLAYER;
        }
        SlingerAttackCheck(self);
        break;
    case SLINGER_ATTACK:
        animStatus = AnimateEntity(anim_throw_bone, self);
        if (!animStatus) {
            SetStep(SLINGER_WALK_AWAY_FROM_PLAYER);
            self->ext.skeleton.attackTimerIndex++;
            self->ext.skeleton.attackTimer =
                attack_timer_cycles[self->params & 1]
                                   [self->ext.skeleton.attackTimerIndex & 3];
            break;
        }

        if ((animStatus & 0x80) && (self->animCurFrame == 10)) {
            if ((self->posX.i.hi >= -16 && self->posX.i.hi <= 272) &&
                (self->posY.i.hi >= 0 && self->posY.i.hi <= 240)) {
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) { // Spawn bone
                    PlaySfxPositional(SFX_BONE_THROW);
                    CreateEntityFromCurrentEntity(
                        E_SLINGER_THROWN_BONE, newEntity);
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
    case SLINGER_JUMP:
        switch (self->step_s) {
        case SLINGER_JUMPING:
            if (!(AnimateEntity(anim_jump1, self) & 1)) {
                u8 facing_ = self->ext.skeleton.facingLeft;
                s32 facing;

                if (Random() % 4) {
                    facing = facing_;
                } else {
                    facing_ ^= 1;
                    facing = facing_;
                }

                if (facing == 0) {
                    self->velocityX = FIX(-2);
                } else {
                    self->velocityX = FIX(2);
                }

                self->velocityY = FIX(-3);
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;
        case SLINGER_IN_AIR:
            if (UnkCollisionFunc3(sensors_ground) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(sensors_move, 2);
            break;
        case SLINGER_LAND:
            if (AnimateEntity(anim_jump2, self) & 1) {
                self->step_s = 0;
                SetStep(SLINGER_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;
    case SLINGER_DESTROY:
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        for (i = 0; i < 7; i++) { // Spawn Slinger pieces
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_SLINGER_PIECES, newEntity);
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

// Bone parts that rotate and fall down when killed
// This is a duplicate of EntitySkeletonPieces and EntityBoneScimitarParts
extern u16 g_EInitSlingerPieces[];
void EntitySlingerPieces(Entity* self) {
    if (self->step) {
        self->ext.skeleton.explosionTimer--;
        if (self->ext.skeleton.explosionTimer & 0xFF) {
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

    InitializeEntity(g_EInitSlingerPieces);
    self->drawFlags = FLAG_DRAW_ROTZ;
    self->animCurFrame = self->params + 15;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}
