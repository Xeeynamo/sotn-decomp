/*
 * Overlay: NZ0
 * Enemy: Bone Scimitar
 */

#include "nz0.h"
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

extern u16 g_BoneScimitarInit[];
static s32 D_8018208C = 0; // Flag for special bone scimitar to appear or not
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
static s16 anim_bone_rot[] = {
    0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010, 0x0018, 0x0000};
static s8 dead_parts_selector[] = {
    0x30, 0x20, 0x14, 0x0C, 0x18, 0x10, 0x14, 0x00};
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
static u16 sensors_ground[][2] = {{0, 20}, {0, 4}, {8, -4}, {-16, 0}};
static s16 D_8018216C[] = {0, 20, 12, 0};
static u16 sensor_move[][2] = {{-12, 16}, {0, -16}, {0, -16}};

void func_801C3708(void) {
    s32 temp = func_801BCF74(D_8018216C);
    s32 temp2 = func_801BD720(sensor_move, LEN(sensor_move));

    if ((temp == 128) || (temp2 & 2)) {
        SetStep(BONE_SCIMITAR_JUMP);
        return;
    }

    if (g_CurrentEntity->ext.generic.unk7C.U8.unk0 == 0) {
        if (GetDistanceToPlayerX() < 64) {
            if (g_CurrentEntity->facingLeft != (GetSideToPlayer() & 1)) {
                SetStep(BONE_SCIMITAR_ATTACK);
            }
        }
    } else {
        g_CurrentEntity->ext.generic.unk7C.U8.unk0--;
    }
}

void EntityBoneScimitar(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        self->step = BONE_SCIMITAR_DESTROY;
    }

    switch (self->step) {
    case BONE_SCIMITAR_INIT:
        InitializeEntity(g_BoneScimitarInit);
        if (self->params != 0) {
            self->palette += self->params;
            self->flags &= ~(FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                             FLAG_DESTROY_IF_OUT_OF_CAMERA | 0xC00);
            self->ext.generic.unk9C = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (self->params & D_8018208C) {
                DestroyEntity(self);
                return;
            }
        }
        self->ext.generic.unk7C.S8.unk0 = 80;    // Skeleton attack timer cycle
        self->ext.generic.unk80.modeS8.unk0 = 0; // Facing init
        self->ext.generic.unk84.S8.unk0 = 0; // Skeleton attack timer selector
        break;

    case BONE_SCIMITAR_IDLE:
        if (func_801BCCFC(sensors_ground) != 0) {
            self->step++;
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_WALK_TOWARDS_PLAYER:
        if (AnimateEntity(anim_walk, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.generic.unk80.modeS8.unk0 = self->facingLeft;

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() < 76) {
            self->step = BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER;
        }
        func_801C3708();
        break;

    case BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER:
        if (AnimateEntity(anim_walk_backwards, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.generic.unk80.modeS8.unk0 = self->facingLeft ^ 1;

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() > 92) {
            self->step = BONE_SCIMITAR_WALK_TOWARDS_PLAYER;
        }
        func_801C3708();
        break;

    case BONE_SCIMITAR_ATTACK:
        animStatus = AnimateEntity(anim_swing_sword, self);
        if (self->animCurFrame == 12) {
            self->hitboxWidth = 20;
            self->hitboxHeight = 17;
            *(s16*)&self->hitboxOffX = -11;
            self->hitboxOffY = -14;
        } else {
            self->hitboxWidth = 8;
            self->hitboxHeight = 18;
            *(s16*)&self->hitboxOffX = -1;
            self->hitboxOffY = 0;
        }

        if (self->animFrameIdx == 7 && self->animFrameDuration == 0) {
            func_801C29B0(NA_SE_EN_BONE_SCIMITAR_SWORD_SLASH);
        }

        if (animStatus == 0) {
            SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            self->ext.generic.unk7C.S8.unk0 =
                attack_timer_cycles[self->params % 2]
                                   [(++self->ext.generic.unk84.S8.unk0) & 3];
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_JUMP:
        switch (self->step_s) {
        case BONE_SCIMITAR_JUMPING:
            if (!(AnimateEntity(anim_jump, self) & 1)) {
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

        case BONE_SCIMITAR_IN_AIR:
            if (func_801BCCFC(sensors_ground) != 0) {
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
        func_801BCF74(&D_8018216C);
        if (((((u32)self->velocityX) >> 0x1F) ^ self->facingLeft) != 0) {
            AnimateEntity(anim_walk, self);
        } else {
            AnimateEntity(anim_walk_backwards, self);
        }

        switch (self->step_s) {
        case BONE_SCIMITAR_WALK_RIGHT:
            self->velocityX = FIX(0.5);
            if (((s16)((g_Tilemap.scrollX.i.hi + self->posX.i.hi) -
                       ((u16)self->ext.generic.unk9C))) > 32) {
                self->step_s++;
            }
            break;

        case BONE_SCIMITAR_WALK_LEFT:
            self->velocityX = FIX(-0.5);
            if (((s16)((g_Tilemap.scrollX.i.hi + ((u16)self->posX.i.hi)) -
                       ((u16)self->ext.generic.unk9C))) < -32) {
                self->step_s--;
            }
            break;
        }

        if (self->ext.generic.unk7C.U8.unk0 != 0) { // Attack delay counter
            self->ext.generic.unk7C.U8.unk0--;
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
            CreateEntityFromCurrentEntity(E_BONE_SCIMITAR_HEAD, newEntity);
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
            newEntity->params |= self->params << 8;
        }

        newEntity = &self[1];
        // If he's one of the special ones from entrance (first visit)
        if (self->params != 0) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
            if (!(self->params & 1)) {
                self[1].params = ITEM_RED_RUST;
            } else {
                self[1].params = ITEM_SHORT_SWORD;
            }
            newEntity->params |= 0x8000;
            D_8018208C |= self->params;
        }
        DestroyEntity(self);
        break;
    }
}

// Bone parts that rotate and fall down when killed
void EntityBoneScimitarParts(Entity* entity) {
    if (entity->step) {
        entity->ext.generic.unk88.S8.unk0--;
        if (entity->ext.generic.unk88.S8.unk0 & 0xFF) {
            entity->rotZ += anim_bone_rot[entity->params];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->params = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(D_80180C58);
    entity->drawFlags = FLAG_DRAW_ROTZ;
    entity->animCurFrame = *(u8*)&entity->params + 16;

    if (entity->facingLeft != 0) {
        entity->velocityX = -entity->velocityX;
    }

    if (entity->params & 0xF00) {
        entity->palette += entity->params / 256;
    }
}
