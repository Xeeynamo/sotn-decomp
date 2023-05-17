/*
 * Overlay: NZ0
 * Enemy: Skeleton
 */

#include "nz0.h"

void func_801C5F2C(Entity* self) {
    if ((func_801BCF74(&D_801824B8) & 0x60) == 0x60) {
        self->posX.val -= self->accelerationX;
    }

    if (!(func_801BD720(&D_801824C0, 3) & 2)) {
        if ((--self->ext.generic.unk7C.U8.unk0) == 0) {
            func_801BD52C(4);
        }
    } else {
        func_801BD52C(SKELETON_JUMP);
    }
}

void EntitySkeleton(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    u8 i;

    if (self->flags & 0x100) {
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
        if (func_801BCCFC(&D_801824A8) != 0) {
            self->step++;
        }
        break;

    case SKELETON_WALK_TOWARDS_PLAYER:
        self->facing = (GetPlayerSide() & 1) ^ 1;
        self->ext.generic.unk80.modeS8.unk0 = self->facing;
        AnimateEntity(D_801823DC, self);

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->accelerationX = -0x8000;
        } else {
            self->accelerationX = 0x8000;
        }

        if (GetPlayerDistanceX() < 76) {
            self->step = SKELETON_WALK_AWAY_FROM_PLAYER;
        }
        func_801C5F2C(self);
        break;

    case SKELETON_WALK_AWAY_FROM_PLAYER:
        self->facing = (GetPlayerSide() & 1) ^ 1;
        self->ext.generic.unk80.modeS8.unk0 = self->facing ^ 1;
        AnimateEntity(D_801823EC, self);

        if (self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->accelerationX = -0x8000;
        } else {
            self->accelerationX = 0x8000;
        }

        if (GetPlayerDistanceX() > 92) {
            self->step = SKELETON_WALK_TOWARDS_PLAYER;
        }
        func_801C5F2C(self);
        break;

    case SKELETON_ATTACK:
        animStatus = AnimateEntity(D_801823FC, self);
        if (!animStatus) {
            func_801BD52C(SKELETON_WALK_AWAY_FROM_PLAYER);
            self->ext.generic.unk7C.S8.unk0 =
                D_80182480[self->subId & 1]
                          [++self->ext.generic.unk84.S8.unk0 & 3];
            break;
        }

        if ((animStatus & 0x80) && (self->animCurFrame == 10)) {
            if (((u32)(((u16)self->posX.i.hi + 16) & 0xFFFF) <= 288) &&
                ((u16)self->posY.i.hi <= 240)) {
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) { // Spawn bone
                    func_801C29B0(NA_SE_EN_SKELETON_THROW_BONE);
                    CreateEntityFromCurrentEntity(0x2F, newEntity);
                    if (self->facing != 0) {
                        newEntity->posX.i.hi -= 8;
                    } else {
                        newEntity->posX.i.hi += 8;
                    }
                    newEntity->posY.i.hi -= 16;
                    newEntity->facing = self->facing;
                }
            }
        }
        break;

    case SKELETON_JUMP:
        switch (self->step_s) {
        case 0:
            if (!(AnimateEntity(D_8018240C, self) & 1)) {
                u8 facing_ = self->ext.generic.unk80.modeS8.unk0;
                s32 facing;

                if (Random() % 4) {
                    facing = facing_;
                } else {
                    facing_ ^= 1;
                    facing = facing_;
                }

                if (facing == 0) {
                    self->accelerationX = -0x20000;
                } else {
                    self->accelerationX = 0x20000;
                }

                self->accelerationY = -0x30000;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case 1:
            if (func_801BCCFC(&D_801824A8) != 0) {
                self->step_s++;
            }
            func_801BD848(&D_801824C0, 2);
            break;

        case 2:
            if (AnimateEntity(D_80182418, self) & 1) {
                self->step_s = 0;
                func_801BD52C(SKELETON_WALK_AWAY_FROM_PLAYER);
            }
        }
        break;

    case SKELETON_DESTROY:
        func_801C29B0(NA_SE_EN_SKELETON_DESTROY);
        for (i = 0; i < 6; i++) { // Spawn Skeleton pieces
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x30, newEntity);
                newEntity->facing = self->facing;
                newEntity->subId = i;
                newEntity->ext.generic.unk88.S8.unk0 = D_80182430[i];
                if (self->facing != 0) {
                    newEntity->posX.i.hi -= D_80182468[i];
                } else {
                    newEntity->posX.i.hi += D_80182468[i];
                }
                newEntity->posY.i.hi += D_80182474[i];
                newEntity->accelerationX = D_80182438[i];
                newEntity->accelerationY = D_80182450[i];
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
            entity->unk1E += D_80182424[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }

    InitializeEntity(D_80180C94);
    entity->unk19 = 4;
    entity->animCurFrame = entity->subId + 15;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }
}

void func_801C6574(Entity* entity) { // Bone Projectile from Skeleton
    s32 accelerationX;
    u32 xDistanceToPlayer;

    if (entity->step) {
        if (entity->flags & 0x100) {
            func_801BD568(0, 0);
            return;
        }

        entity->unk1E += 0x80;
        entity->accelerationY += 0x2400;
        MoveEntity();

        if (entity->posY.i.hi > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(D_80180CA0);
        entity->posY.val -= 0x1000;
        xDistanceToPlayer = GetPlayerDistanceX();
        xDistanceToPlayer /= 32;
        xDistanceToPlayer = CLAMP_MAX(xDistanceToPlayer, 7);
        accelerationX = D_80182488[xDistanceToPlayer];
        xDistanceToPlayer = entity->facing;

        if (xDistanceToPlayer > 0) {
            accelerationX = -accelerationX;
        }

        entity->accelerationY = -0x48000;
        entity->accelerationX = accelerationX;
        entity->unk19 = 4;
    }
}

void func_801C6678(Entity* entity) { // From Skeleton
    if (entity->step == 0) {
        InitializeEntity(D_80180C88);
        entity->unk1A = 0x120;
        entity->unk1C = 0x200;
        entity->unk6C = 0;
        entity->unk3C = 0;
        entity->unk19 = entity->unk19 | 0xB;
        return;
    }

    entity->facing = entity[-1].facing;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animCurFrame = entity[-1].animCurFrame;
    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.i.hi - 20;

    if (entity[-1].objectId != 0x2E) {
        DestroyEntity(entity);
    }
}