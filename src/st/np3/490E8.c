/*
 * Overlay: NP3
 * Enemy: Bone Scimitar
 */

#include "np3.h"
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

void func_801C90E8(void) {
    s32 temp = func_801BCB5C(&D_80182540);
    s16 temp2 = func_801BD308(&D_80182548, 3);

    if ((temp == 128) || (temp2 & 2)) {
        SetStep(BONE_SCIMITAR_JUMP);
        return;
    }
    if ((g_CurrentEntity->ext.generic.unk7C.U8.unk0) == 0) {
        if (GetDistanceToPlayerX() < 64) {
            if (g_CurrentEntity->facingLeft != (GetSideToPlayer() & 1)) {
                SetStep(BONE_SCIMITAR_ATTACK);
            }
        }
    } else {
        g_CurrentEntity->ext.generic.unk7C.S8.unk0--;
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
        InitializeEntity(D_80180AE4);
        if (self->params != 0) {
            self->palette += self->params;
            self->flags &= ~(FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                             FLAG_DESTROY_IF_OUT_OF_CAMERA | 0xC00);
            self->ext.generic.unk9C = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (self->params & D_80182460) {
                DestroyEntity(self);
                return;
            }
        }
        self->ext.generic.unk7C.S8.unk0 = 80;    // Skeleton attack timer cycle
        self->ext.generic.unk80.modeS8.unk0 = 0; // Facing init
        self->ext.generic.unk84.S8.unk0 = 0; // Skeleton attack timer selector
        break;

    case BONE_SCIMITAR_IDLE:
        if (func_801BC8E4(&D_80182530) != 0) {
            self->step++;
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_WALK_TOWARDS_PLAYER:
        if (AnimateEntity(D_80182464, self) == 0) {
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
        func_801C90E8();
        break;

    case BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER:
        if (AnimateEntity(D_80182474, self) == 0) {
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
        func_801C90E8();
        break;

    case BONE_SCIMITAR_ATTACK:
        animStatus = AnimateEntity(D_80182484, self);
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
            func_801916C4(SFX_BONE_SWORD_SWISH_B);
        }

        if (animStatus == 0) {
            SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            self->ext.generic.unk7C.S8.unk0 =
                D_80182528[self->params % 2]
                          [(++self->ext.generic.unk84.S8.unk0) & 3];
            if (self->params != 0) {
                SetStep(BONE_SCIMITAR_SPECIAL);
            }
        }
        break;

    case BONE_SCIMITAR_JUMP:
        switch (self->step_s) {
        case BONE_SCIMITAR_JUMPING:
            if (!(AnimateEntity(D_801824A0, self) & 1)) {
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
            if (func_801BC8E4(&D_80182530) != 0) {
                self->step_s++;
            }
            CheckFieldCollision(&D_80182548, 2);
            break;

        case BONE_SCIMITAR_LAND:
            if (AnimateEntity(D_801824AC, self) == 0) {
                SetStep(BONE_SCIMITAR_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;

    case BONE_SCIMITAR_SPECIAL:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        func_801BCB5C(&D_80182540);
        if (((((u32)self->velocityX) >> 0x1F) ^ self->facingLeft) != 0) {
            AnimateEntity(D_80182464, self);
        } else {
            AnimateEntity(D_80182474, self);
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
            newEntity->ext.generic.unk88.S8.unk0 = D_801824C8[i];

            if (self->facingLeft != 0) {
                newEntity->posX.i.hi -= D_80182508[i];
            } else {
                newEntity->posX.i.hi += D_80182508[i];
            }
            newEntity->posY.i.hi += D_80182518[i];
            newEntity->velocityX = D_801824D0[i];
            newEntity->velocityY = D_801824EC[i];
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
            D_80182460 |= self->params;
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
            entity->rotZ += D_801824B8[entity->params];
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
    InitializeEntity(D_80180AF0);
    entity->drawFlags = FLAG_DRAW_ROTZ;
    entity->animCurFrame = *(u8*)&entity->params + 16;

    if (entity->facingLeft != 0) {
        entity->velocityX = -entity->velocityX;
    }

    if (entity->params & 0xF00) {
        entity->palette += entity->params / 256;
    }
}
