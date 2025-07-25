// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

typedef enum {
    BONE_SCIMITAR_INIT,
    BONE_SCIMITAR_IDLE,
    BONE_SCIMITAR_WALK_TOWARDS_PLAYER,
    BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER,
    BONE_SCIMITAR_ATTACK,
    BONE_SCIMITAR_JUMP,
    BONE_SCIMITAR_SPECIAL,
    BONE_SCIMITAR_DESTROY
} BoneScimitarSteps;

typedef enum {
    BONE_SCIMITAR_JUMPING,
    BONE_SCIMITAR_IN_AIR,
    BONE_SCIMITAR_LAND
} BoneScimitarJumpSubSteps;

typedef enum {
    BONE_SCIMITAR_WALK_RIGHT,
    BONE_SCIMITAR_WALK_LEFT
} BoneScimitarSpecialSubSteps;

extern u16 g_EInitBoneScimitar[];
extern u16 g_EInitScimitarParts[];

static bool spawn_special =
    false; // Flag for special bone scimitar to appear or not
static u8 anim_walk[] = {0x06, 0x01, 0x04, 0x02, 0x04, 0x03, 0x06,
                         0x04, 0x05, 0x05, 0x05, 0x06, 0x00};
static u8 anim_walk_backwards[] = {0x06, 0x01, 0x05, 0x06, 0x05, 0x05, 0x06,
                                   0x04, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 anim_swing_sword[] = {
    0x05, 0x01, 0x05, 0x02, 0x05, 0x07, 0x06, 0x08, 0x05,
    0x09, 0x05, 0x0A, 0x05, 0x0B, 0x01, 0x0C, 0x1E, 0x0D,
    0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0xFF, 0x00};
static u8 anim_jump[] = {
    0x01, 0x01, 0x04, 0x0E, 0x04, 0x0F, 0x01, 0x01, 0xFF, 0x00};
static u8 anim_land[] = {
    0x01, 0x01, 0x04, 0x0E, 0x06, 0x0F, 0x04, 0x0E, 0x01, 0x01, 0xFF, 0x00};
static u16 anim_bone_rot[] = {
    0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010, 0x0018, 0x0000};
static u8 dead_parts_selector[] = {0x30, 0x20, 0x14, 0x0C, 0x18, 0x10, 0x14};
static s32 dead_parts_velocity_x[] = {
    FIX(.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), FIX(0.75)};
static s32 dead_parts_velocity_y[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-.875), FIX(-4)};
static s16 dead_parts_pos_x[] = {-4, 0, 4, -4, -4, 4, 0};
static s16 dead_parts_pos_y[] = {-16, -8, -4, -4, 9, 9, 0};
static u8 attack_timer_cycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40}, // skeleton type 0, attacks in quick succession
    {0xF0, 0xC0, 0xA0, 0x80}, // type 1, attacks slowly
};
#define XY(x, y) x, y
static u16 sensors_ground[] = {XY(0, 20), XY(0, 4), XY(8, -4), XY(-16, 0)};
static s16 sensors_special[] = {0, 20, 12, 0};
static s16 sensor_move[] = {XY(-12, 16), XY(0, -16), XY(0, -16)};

static void BoneScimitarAttackCheck(void) {
    s32 temp = UnkCollisionFunc2(sensors_special);
    u16 temp2 = UnkCollisionFunc(sensor_move, 3);

    if ((temp == 128) || (temp2 & 2)) {
        SetStep(BONE_SCIMITAR_JUMP);
        return;
    }
    if (!g_CurrentEntity->ext.skeleton.attackTimer) {
        if (GetDistanceToPlayerX() < 64) {
            if (g_CurrentEntity->facingLeft ^ GetSideToPlayer() & 1) {
                SetStep(BONE_SCIMITAR_ATTACK);
            }
        }
    } else {
        g_CurrentEntity->ext.skeleton.attackTimer--;
    }
}

void EntityBoneScimitar(Entity* self) {
    Entity* newEntity;
    bool leftTemp;
    u8 tempByte;
    s16 xPos;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        self->step = BONE_SCIMITAR_DESTROY;
    }

    switch (self->step) {
    case BONE_SCIMITAR_INIT:
        InitializeEntity(g_EInitBoneScimitar);
        if (self->params) {
            self->palette += self->params;
            self->flags &= ~(FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                             FLAG_DESTROY_IF_OUT_OF_CAMERA | 0xC00);
            self->ext.skeleton.initialX =
                g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (spawn_special & self->params) {
                DestroyEntity(self);
                return;
            }
        }
        self->ext.skeleton.attackTimer = 80; // Skeleton attack timer cycle
        self->ext.skeleton.facingLeft = 0;   // Facing init
        self->ext.skeleton.attackTimerIndex =
            0; // Skeleton attack timer selector
        break;

    case BONE_SCIMITAR_IDLE:
        if (UnkCollisionFunc3(sensors_ground) != 0) {
            self->step++;
            if (self->params) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_WALK_TOWARDS_PLAYER:
        if (AnimateEntity(anim_walk, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.skeleton.facingLeft = self->facingLeft;

        if (self->ext.skeleton.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() < 76) {
            self->step = BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER;
        }
        BoneScimitarAttackCheck();
        break;

    case BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER:
        if (AnimateEntity(anim_walk_backwards, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.skeleton.facingLeft = self->facingLeft ^ 1;

        if (self->ext.skeleton.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() > 92) {
            self->step = BONE_SCIMITAR_WALK_TOWARDS_PLAYER;
        }
        BoneScimitarAttackCheck();
        break;

    case BONE_SCIMITAR_ATTACK:
        tempByte = AnimateEntity(anim_swing_sword, self);
        if (self->animCurFrame == 12) {
            self->hitboxWidth = 20;
            self->hitboxHeight = 17;
            self->hitboxOffX = -11;
            self->hitboxOffY = -14;
        } else {
            self->hitboxWidth = 8;
            self->hitboxHeight = 18;
            self->hitboxOffX = -1;
            self->hitboxOffY = 0;
        }

        if (self->pose == 7 && !self->poseTimer) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
        }

        if (!tempByte) {
            SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            tempByte = ++self->ext.skeleton.attackTimerIndex & 3;
            self->ext.skeleton.attackTimer =
                attack_timer_cycles[self->params & 1][tempByte];
            if (self->params) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_JUMP:
        switch (self->step_s) {
        case BONE_SCIMITAR_JUMPING:
            if (!(AnimateEntity(anim_jump, self) & 1)) {
                tempByte = self->ext.skeleton.facingLeft;

                if ((Random() & 3) == 0) {
                    tempByte ^= 1;
                }
                if (tempByte) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = FIX(-2);
                }

                self->velocityY = FIX(-3);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case BONE_SCIMITAR_IN_AIR:
            if (UnkCollisionFunc3(sensors_ground) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(sensor_move, 2);
            break;

        case BONE_SCIMITAR_LAND:
            if (AnimateEntity(anim_land, self) == 0) {
                SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;

    case BONE_SCIMITAR_SPECIAL:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        UnkCollisionFunc2(sensors_special);
        if (self->velocityX < 0) {
            leftTemp = 1;
        } else {
            leftTemp = 0;
        }
        leftTemp ^= self->facingLeft;
        if (leftTemp) {
            AnimateEntity(anim_walk, self);
        } else {
            AnimateEntity(anim_walk_backwards, self);
        }

        switch (self->step_s) {
        case BONE_SCIMITAR_WALK_RIGHT:
            self->velocityX = FIX(0.5);
            xPos = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            xPos = xPos - self->ext.skeleton.initialX;
            if (xPos > 32) {
                self->step_s++;
            }
            break;

        case BONE_SCIMITAR_WALK_LEFT:
            self->velocityX = FIX(-0.5);
            xPos = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            xPos = xPos - self->ext.skeleton.initialX;
            if (xPos < -32) {
                self->step_s--;
            }
            break;
        }

        if (self->ext.skeleton.attackTimer) { // Attack delay counter
            self->ext.skeleton.attackTimer--;
            return;
        }

        if ((GetDistanceToPlayerX() < 48) && (GetDistanceToPlayerY() < 32)) {
            SetStep(BONE_SCIMITAR_ATTACK);
        }
        break;

    case BONE_SCIMITAR_DESTROY:
        g_api.PlaySfx(SFX_SKELETON_DEATH_C);
        for (i = 0; i < LEN(dead_parts_pos_x); i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_BONE_SCIMITAR_PARTS, newEntity);
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
            newEntity->params |= self->params << 8;
        }

        // If he's one of the special ones from entrance (first visit)
        if (self->params) {
            newEntity = self + 1;
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
            if (self->params & 1) {
                newEntity->params = ITEM_SHORT_SWORD;
            } else {
                newEntity->params = ITEM_RED_RUST;
            }
            newEntity->params |= 0x8000;
            spawn_special |= self->params;
        }
        DestroyEntity(self);
        break;
    }
}

// Bone parts that rotate and fall down when killed
void EntityBoneScimitarParts(Entity* self) {
    if (self->step) {
        if (--self->ext.skeleton.explosionTimer) {
            self->rotate += anim_bone_rot[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitScimitarParts);
    self->animCurFrame = (self->params & 0xFF) + 16;
    self->drawFlags = FLAG_DRAW_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }

    if (self->params & 0xF00) {
        self->palette += self->params >> 8;
    }
}
