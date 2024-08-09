/*
 * Overlay: NZ0
 * Enemy: Skeleton
 */

#include "nz0.h"
#include "sfx.h"

typedef enum {
    SKELETON_INIT,
    SKELETON_IDLE,
    SKELETON_WALK_TOWARDS_PLAYER,
    SKELETON_WALK_AWAY_FROM_PLAYER,
    SKELETON_ATTACK,
    SKELETON_JUMP,
    SKELETON_DESTROY
} SKELETON_STEPS;

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
static s8 dead_parts_selector[] = {0x30, 0x20, 0x14, 0x0C, 0x18, 0x10};
static s32 dead_parts_velocity_x[] = {
    FIX(.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75)};
static s32 dead_parts_velocity_y[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-.875)};
static u16 dead_parts_pos_x[] = {0 - 4, 0, 4, -4, -4, 4};
static u16 dead_parts_pos_y[] = {-16, -8, -4, -4, 9, 9};
static u8 attack_timer_cycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40}, {0xF0, 0xC0, 0xA0, 0x80}};
static u32 bone_projectile_velocity_x[] = {
    FIX(-.125), FIX(-.5),  FIX(-1), FIX(-1.5),
    FIX(-2),    FIX(-2.5), FIX(-3), FIX(-3.5)};
static s16 sensors_ground[][2] = {{0, 19}, {0, 4}, {8, -4}, {-16, 0}};
static s16 D_801824B8[] = {0, 19, 8, 0};
static s16 sensors_move[][2] = {{-12, 16}, {0, -16}, {0, -16}};

void func_801C5F2C(Entity* self) {
    if ((func_801BCF74(D_801824B8) & 0x60) == 0x60) {
        self->posX.val -= self->velocityX;
    }

    if (!(func_801BD720(sensors_move, LEN(sensors_move)) & 2)) {
        if ((--self->ext.generic.unk7C.U8.unk0) == 0) {
            SetStep(4);
        }
    } else {
        SetStep(SKELETON_JUMP);
    }
}

void EntitySkeleton(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    u8 i;

    if (self->flags & FLAG_DEAD) {
        self->step = SKELETON_DESTROY;
    }

    switch (self->step) {
    case SKELETON_INIT:
        InitializeEntity(D_80180C88);
        self->ext.generic.unk7C.S8.unk0 = 0x50;
        self->ext.generic.unk80.modeS8.unk0 = 0;
        self->ext.generic.unk84.S8.unk0 = 0;
        break;
    case SKELETON_IDLE: // Wait for player to be close enough
        if (func_801BCCFC(sensors_ground) != 0) {
            self->step++;
        }
        break;
    case SKELETON_WALK_TOWARDS_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.generic.unk80.modeS8.unk0 = self->facingLeft;
        AnimateEntity(anim_walk, self);

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() < 76) {
            self->step = SKELETON_WALK_AWAY_FROM_PLAYER;
        }
        func_801C5F2C(self);
        break;
    case SKELETON_WALK_AWAY_FROM_PLAYER:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.generic.unk80.modeS8.unk0 = self->facingLeft ^ 1;
        AnimateEntity(anim_walk_backwards, self);

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() > 92) {
            self->step = SKELETON_WALK_TOWARDS_PLAYER;
        }
        func_801C5F2C(self);
        break;
    case SKELETON_ATTACK:
        animStatus = AnimateEntity(anim_throw_bone, self);
        if (!animStatus) {
            SetStep(SKELETON_WALK_AWAY_FROM_PLAYER);
            self->ext.generic.unk7C.S8.unk0 =
                attack_timer_cycles[self->params & 1]
                                   [++self->ext.generic.unk84.S8.unk0 & 3];
            break;
        }

        if ((animStatus & 0x80) && (self->animCurFrame == 10)) {
            if (((u32)(((u16)self->posX.i.hi + 16) & 0xFFFF) <= 288) &&
                ((u16)self->posY.i.hi <= 240)) {
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) { // Spawn bone
                    func_801C29B0(NA_SE_EN_SKELETON_THROW_BONE);
                    CreateEntityFromCurrentEntity(0x2F, newEntity);
                    if (self->facingLeft != 0) {
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
        case 0:
            if (!(AnimateEntity(anim_jump1, self) & 1)) {
                u8 facing_ = self->ext.generic.unk80.modeS8.unk0;
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
        case 1:
            if (func_801BCCFC(sensors_ground) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(sensors_move, 2);
            break;
        case 2:
            if (AnimateEntity(anim_jump2, self) & 1) {
                self->step_s = 0;
                SetStep(SKELETON_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;
    case SKELETON_DESTROY:
        func_801C29B0(SFX_SKELETON_DEATH_C);
        for (i = 0; i < 6; i++) { // Spawn Skeleton pieces
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x30, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = i;
                newEntity->ext.generic.unk88.S8.unk0 = dead_parts_selector[i];
                if (self->facingLeft != 0) {
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

void func_801C6494(Entity* entity) { // From skeleton death explosion
    if (entity->step) {
        entity->ext.generic.unk88.S8.unk0--;
        if (entity->ext.generic.unk88.S8.unk0 & 0xFF) {
            entity->rotZ += anim_bone_rot[entity->params];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->params = 0;
        entity->step = 0;
        return;
    }

    InitializeEntity(D_80180C94);
    entity->drawFlags = FLAG_DRAW_ROTZ;
    entity->animCurFrame = entity->params + 15;

    if (entity->facingLeft != 0) {
        entity->velocityX = -entity->velocityX;
    }
}

void func_801C6574(Entity* entity) { // Bone Projectile from Skeleton
    s32 velocityX;
    u32 xDistanceToPlayer;

    if (entity->step) {
        if (entity->flags & FLAG_DEAD) {
            EntityExplosionSpawn(0, 0);
            return;
        }

        entity->rotZ += 0x80;
        entity->velocityY += 0x2400;
        MoveEntity();

        if (entity->posY.i.hi > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(D_80180CA0);
        entity->posY.val -= FIX(0.0625);
        xDistanceToPlayer = GetDistanceToPlayerX();
        xDistanceToPlayer /= 32;
        xDistanceToPlayer = MAX(xDistanceToPlayer, 7);
        velocityX = bone_projectile_velocity_x[xDistanceToPlayer];
        xDistanceToPlayer = entity->facingLeft;

        if (xDistanceToPlayer > 0) {
            velocityX = -velocityX;
        }

        entity->velocityY = FIX(-4.5);
        entity->velocityX = velocityX;
        entity->drawFlags = FLAG_DRAW_ROTZ;
    }
}

void func_801C6678(Entity* entity) { // From Skeleton
    if (entity->step == 0) {
        InitializeEntity(D_80180C88);
        entity->rotX = 0x120;
        entity->rotY = 0x200;
        entity->unk6C = 0;
        entity->hitboxState = 0;
        entity->drawFlags = entity->drawFlags | 0xB;
        return;
    }

    entity->facingLeft = entity[-1].facingLeft;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animCurFrame = entity[-1].animCurFrame;
    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.i.hi - 20;

    if (entity[-1].entityId != 0x2E) {
        DestroyEntity(entity);
    }
}
