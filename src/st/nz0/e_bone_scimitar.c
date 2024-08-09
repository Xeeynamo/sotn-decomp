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

void func_801C3708(void) {
    s32 temp = func_801BCF74(&D_8018216C);
    s32 temp2 = func_801BD720(&D_80182174, 3);

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
        InitializeEntity(D_80180C4C);
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
        if (func_801BCCFC(&D_8018215C) != 0) {
            self->step++;
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_WALK_TOWARDS_PLAYER:
        if (AnimateEntity(D_80182090, self) == 0) {
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
        if (AnimateEntity(D_801820A0, self) == 0) {
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
        animStatus = AnimateEntity(D_801820B0, self);
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
                D_80182154[self->params % 2]
                          [(++self->ext.generic.unk84.S8.unk0) & 3];
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_JUMP:
        switch (self->step_s) {
        case BONE_SCIMITAR_JUMPING:
            if (!(AnimateEntity(D_801820CC, self) & 1)) {
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
            if (func_801BCCFC(&D_8018215C) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(&D_80182174, 2);
            break;

        case BONE_SCIMITAR_LAND:
            if (AnimateEntity(D_801820D8, self) == 0) {
                SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;

    case BONE_SCIMITAR_SPECIAL:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        func_801BCF74(&D_8018216C);
        if (((((u32)self->velocityX) >> 0x1F) ^ self->facingLeft) != 0) {
            AnimateEntity(D_80182090, self);
        } else {
            AnimateEntity(D_801820A0, self);
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
        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_BONE_SCIMITAR_HEAD, newEntity);
            newEntity->facingLeft = self->facingLeft;
            newEntity->params = i;
            newEntity->ext.generic.unk88.S8.unk0 = D_801820F4[i];

            if (self->facingLeft != 0) {
                newEntity->posX.i.hi -= D_80182134[i];
            } else {
                newEntity->posX.i.hi += D_80182134[i];
            }
            newEntity->posY.i.hi += D_80182144[i];
            newEntity->velocityX = D_801820FC[i];
            newEntity->velocityY = D_80182118[i];
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
            entity->rotZ += D_801820E4[entity->params];
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
