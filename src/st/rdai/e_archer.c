// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"


// Copied from Spear Guard. 
// Note: We do not use the return value when calling this function.
// I believe that makes the entire function (besides the first 2 lines)
// totally pointless. Nothing else modifies anything. So all this really
// should do is kepe us moving along the stairs. A bit overkill.
s32 StairsCheckCollision(void) {
    Collider collider;
    s32 x;
    s32 y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi -= 3;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi - 0x1E;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        y = (g_CurrentEntity->posY.i.hi += collider.unk20);
    } else {
        return false;
    }

    if (g_CurrentEntity->velocityX == 0) {
        return true;
    }

    if (g_CurrentEntity->velocityX > 0) {
        x += 0x20;
        y -= 0x24;
    } else {
        x -= 0x20;
        y += 0x1C;
    }
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_UNK_8000)) {
        return false;
    }
    return true;
}

static bool ApproachTarget(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}

static AnimateEntityFrame anim_chair_running[] = {{8, 30}, {8, 31}, {8, 32}, POSE_LOOP(0)};
static AnimateEntityFrame anim_chair_seat_lowering[] = {{1, 31}, {2, 33}, {16, 34}, {6, 33}, {1, 31}, POSE_END};
static AnimateEntityFrame anim_chair_seat_raising[] = {{1, 31}, {2, 35}, {16, 36}, {6, 35}, {1, 31}, POSE_END};
static AnimateEntityFrame anim_bow_drawing[] = {{22, 11}, {8, 12}, {16, 13}, POSE_END};
static AnimateEntityFrame anim_arm_pulling[] = {{22, 25}, {8, 26}, {16, 27}, POSE_END};
static AnimateEntityFrame anim_bow_shooting[] = {{15, 13}, {5, 12}, {5, 14}, {5, 15}, {2, 14}, {2, 15}, {2, 11}, POSE_END};
static AnimateEntityFrame anim_arm_reloading[] = {{22, 25}, {6, 16}, {6, 17}, {22, 18}, {6, 17}, {6, 16}, {22, 25}, POSE_END};
static s16 g_RdaiArcherOffsets[][2] = {
    {3, -4}, {4, -5}, {-5, 4}, {-9, 6}
};


extern EInit g_EInitRdaiUnk1F;

void EntityArcherVehicle(Entity* self) {
    Entity* other;
    s32 velX;
    s32 i;
    s32 anim_running;

    if (self->step) {
        other = self + 4;
        if (other->entityId != E_ARCHER_MAN && self->step != 3) {
            SetStep(3);
        }
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitRdaiUnk1F);
        // Create 3 sub-parts of the vehicle, with params 0, 1, 2.
        // These are the two wheels and the one wheel cover.
        for (other = self + 1, i = 0; i < 3; i++, other++) {
            CreateEntityFromEntity(E_ARCHER_WHEEL, self, other);
            other->params = i;
        }
        other = self + 4;
        CreateEntityFromEntity(E_ARCHER_MAN, self, other);
        SetStep(1);
        break;
    case 0x1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->step_s++;
        }
        if (self->ext.rdaiArcher.unk84 == 0) {
            self->velocityX += FIX(1.0/64);
            if (self->velocityX > FIX(0.75)) {
                self->velocityX = FIX(0.75);
            }
        } else {
            self->velocityX -= FIX(1.0/64);
            if (self->velocityX < FIX(-0.75)) {
                self->velocityX = FIX(-0.75);
            }
        }
        AnimateEntity(anim_chair_running, self);
        StairsCheckCollision();
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_UNK_RDAI_76A);
        }
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;
    case 0x2:
        switch (self->step_s) {
        case 0:
            StairsCheckCollision();
            velX = self->velocityX -= self->velocityX >> 8;
            if (abs(velX) < FIX(0.5)) {
                self->ext.rdaiArcher.unk84 ^= 1;
                self->velocityX = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.rdaiArcher.unk84 == 0) {
                self->velocityX += FIX(1.0/64);
                if (self->velocityX > FIX(0.75)) {
                    self->velocityX = FIX(0.75);
                }
            } else {
                self->velocityX -= FIX(1.0/64);
                if (self->velocityX < FIX(-0.75)) {
                    self->velocityX = FIX(-0.75);
                }
            }
            /* fallthrough */
        case 1:
            StairsCheckCollision();
            if (self->ext.rdaiArcher.unk84 == 0) {
                anim_running = AnimateEntity(anim_chair_seat_raising, self);
            } else {
                anim_running = AnimateEntity(anim_chair_seat_lowering, self);
            }
            if (self->pose > 2) {
                self->step_s = 2;
            }
            if (anim_running == 0) {
                SetStep(1);
            }
        }
        break;
    case 0x3:
        PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
        for (i = 0; i < 9; i++) {
            if (i != 7) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_ARCHER_DEATH_PARTS, self, other);
                    other->params = i + 1;
                }
            }
        }
        PreventEntityFromRespawning(self);
        DestroyEntity(self);
        return;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitRdaiUnk1F;

void EntityArcherWheel(Entity* self) {
    Entity* entity;
    s32 velocity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
        self->step = self->params + 1;
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
        break;

    case 1:
        // Frame 2: metal rectangle which partially covers the lower-left wheel
        // This makes the vehicle more 3D, since the wheel has higher priority.
        self->animCurFrame = 2;
        entity = self - 1;
        if (entity->entityId != E_ARCHER_VEHICLE) {
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->zPriority = entity->zPriority + 2;
        break;

    case 2:
        // Frame 8: one wheel
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 2;
        if (entity->entityId != E_ARCHER_VEHICLE) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ARCHER_DEATH_PARTS, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi + 28;
        self->posY.i.hi = entity->posY.i.hi - 38;
        self->zPriority = entity->zPriority - 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        self->ext.rdaiArcher.unk88 += velocity * 2;
        self->posY.i.hi += abs((rsin(self->ext.rdaiArcher.unk88) << 3) >> 12);
        break;

    case 3:
        // The other wheel
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 3;
        if (entity->entityId != E_ARCHER_VEHICLE) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ARCHER_DEATH_PARTS, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi - 32;
        self->posY.i.hi = entity->posY.i.hi + 24;
        self->zPriority = entity->zPriority + 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        self->ext.rdaiArcher.unk88 += velocity * 2;
        self->posY.i.hi += abs((rsin(self->ext.rdaiArcher.unk88) << 3) >> 12);
        break;
    }
}

extern EInit g_EInitArcher;

void EntityArcherMan(Entity* self) {
    Entity* entity;
    s32 i;
    s32 animIndex;
    s16 angle;
    s32 deltaX;
    s32 deltaY;

    entity = self - 4;
    self->posX.i.hi = entity->posX.i.hi + 0x28;
    self->posY.i.hi = entity->posY.i.hi + 0x10;
    animIndex = entity->animCurFrame - 0x21;
    if (animIndex >= 0) {
        s16* offsets = (s16*)g_RdaiArcherOffsets;
        offsets += animIndex * 2;
        self->posX.i.hi += offsets[0];
        self->posY.i.hi += offsets[1];
    }

    if ((self->flags & FLAG_DEAD) && self->step != 3) {
        SetStep(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitArcher);
        self->animCurFrame = 29;
        // Params 1 is the arm pulling the bow string
        entity = self + 1;
        CreateEntityFromEntity(E_ARCHER_MAN_ARMS, self, entity);
        entity->params = 1;
        entity->nextPart = self;
        self->nextPart = entity;
        // Params 2 is background arm holding the bow
        entity = self + 2;
        CreateEntityFromEntity(E_ARCHER_MAN_ARMS, self, entity);
        entity->params = 2;
        // Params 3 is the bow
        entity = self + 3;
        CreateEntityFromEntity(E_ARCHER_MAN_ARMS, self, entity);
        entity->params = 3;
        // fallthrough

    case 1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->ext.rdaiArcher.mode = 0;
            self->step_s++;
        }
        entity = &PLAYER;
        deltaX = entity->posX.i.hi - self->posX.i.hi;
        deltaY = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(deltaY, deltaX);
        if (angle > ROT(45)) {
            angle = ROT(45);
        }
        if (angle < ROT(-45)) {
            angle = ROT(-45);
        }
        ApproachTarget(&self->rotate, angle, 8);
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.rdaiArcher.timer = 0x60;
            self->ext.rdaiArcher.mode = 1;
            self->step_s++;
            // fallthrough
        case 1:
            entity = &PLAYER;
            deltaX = entity->posX.i.hi - self->posX.i.hi;
            deltaY = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            if (angle > ROT(45)) {
                angle = ROT(45);
            }
            if (angle < ROT(-45)) {
                angle = ROT(-45);
            }
            ApproachTarget(&self->rotate, angle, 8);
            if (!--self->ext.rdaiArcher.timer) {
                PlaySfxPositional(SFX_ARROW_SHOT_D);
                self->ext.rdaiArcher.mode = 2;
                self->ext.rdaiArcher.timer = 0x30;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.rdaiArcher.timer) {
                self->ext.rdaiArcher.mode = 3;
                self->ext.rdaiArcher.timer = 0x80;
                self->step_s++;
            }
            break;

        case 3:
            if (!--self->ext.rdaiArcher.timer) {
                SetStep(1);
            }
            break;
        }
        break;

    case 3:
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ARCHER_DEATH_PARTS, self, entity);
                entity->params = i + 0x13;
            }
        }
        DestroyEntity(self);
        break;
    }
}
extern EInit g_EInitRdaiUnk1F;
// Archer man creates 3 of these, with params 1, 2, 3.
// Then the case 0 sets self->step = self->params
// So each step is a different entity which forms part of the man.
// These are the two arms and the bow.
void EntityArcherManArms(Entity* self) {
    Entity* other;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
        self->drawFlags = ENTITY_ROTATE;
        self->step = self->params;
        self->hitboxState = 0;
        if (self->params == 1) { // The arm to pull the bow string
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                CreateEntityFromEntity(E_ARCHER_ARROW, self, other);
                other->ext.rdaiArcher.unk9C = self;
                other->zPriority = self->zPriority - 1;
            }
        }
        break;
    case 1: // The arm which pulls the bow string
        other = self - 1;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = other->zPriority + 3;
        self->rotate = other->rotate;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(anim_arm_pulling, self);
            if ((!self->poseTimer) && (self->pose == 1)) {
                PlaySfxPositional(SFX_BONE_CREAK);
            }
            break;
        case 2:
            self->animCurFrame = 0x1B;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        case 3:
            AnimateEntity(anim_arm_reloading, self);
            if ((!self->poseTimer) && (self->pose == 6)) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_ARCHER_ARROW, self, other);
                    other->ext.rdaiArcher.unk9C = self;
                    other->zPriority = self->zPriority - 1;
                }
                other = self - 1;
            }
            break;
        default:
            self->animCurFrame = 0x19;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.rdaiArcher.mode = other->ext.rdaiArcher.mode;
        if (other->entityId != E_ARCHER_MAN) {
            DestroyEntity(self);
            return;
        }
        break;
    case 2: // The other arm in the background
        other = self - 2;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) - 1);
        self->rotate = other->rotate;
        self->animCurFrame = 28;
        if (other->entityId != E_ARCHER_MAN) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3: // The bow itself
        other = self - 3;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) + 1);
        self->rotate = other->rotate;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(anim_bow_drawing, self);
            if (other->ext.rdaiArcher.mode == 2) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.rdaiArcher.mode = 2;
            }
            break;
        case 2:
            AnimateEntity(anim_bow_shooting, self);
            break;
        case 3:
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        default:
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.rdaiArcher.mode = other->ext.rdaiArcher.mode;
        if (other->entityId != E_ARCHER_MAN) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180884;

void EntityArcherArrow(Entity* self) {
    Entity* other;
    s16 angle;
    s32 i;
    s32 size;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_80180884);
        self->animCurFrame = 22;
        self->drawFlags |= ENTITY_ROTATE;
        self->hitboxState = 0;
        if (self->params) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->animCurFrame += self->params;
            if (self->params == 1) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->step = 4;
            return;
        }
    case 1:
        other = self->ext.rdaiArcher.unk9C;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->rotate = other->rotate;
        angle = self->rotate;
        size = 24;
        if (other->animCurFrame == 0x1A) {
            size = 14;
        }
        if (other->animCurFrame == 0x1B) {
            size = 8;
        }
        self->posX.i.hi += (size * rcos(angle)) >> 0xC;
        self->posY.i.hi += (size * rsin(angle)) >> 0xC;
        if (other->entityId != E_ARCHER_MAN_ARMS) {
            DestroyEntity(self);
            return;
        }
        if ((other->ext.rdaiArcher.mode) == 2) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->velocityX = (rcos(angle) * FIX(5)) >> 0xC;
            self->velocityY = (rsin(angle) * FIX(5)) >> 0xC;
            self->hitboxState = 3;
            self->hitboxOffX = (rcos(angle) * 8) >> 0xC;
            self->hitboxOffY = (rsin(angle) * 8) >> 0xC;
            self->hitboxWidth = self->hitboxHeight = 4;
            self->step = 2;
        }
        break;
    case 2:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            for (i = 0; i < 2; i++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_ARCHER_ARROW, self, other);
                    other->params = i + 1;
                    other->rotate = self->rotate;
                }
            }
            DestroyEntity(self);
            return;
        }
        if (self->hitFlags & 0x80) {
            other = &PLAYER;
            self->ext.rdaiArcher.unk94 = other->posX.i.hi - self->posX.i.hi;
            self->ext.rdaiArcher.unk96 = other->posY.i.hi - self->posY.i.hi;
            self->ext.rdaiArcher.timer = 0x20;
            self->hitboxState = 0;
            self->step++;
            return;
        }
        break;
    case 3:
        other = &PLAYER;
        self->posX.i.hi = other->posX.i.hi - self->ext.rdaiArcher.unk94;
        self->posY.i.hi = other->posY.i.hi - self->ext.rdaiArcher.unk96;
        if (!--self->ext.rdaiArcher.timer) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->params == 1) {
            self->rotate += ROT(2.8125);
        } else {
            self->rotate -= ROT(2.8125);
        }
        break;
    }
}

extern s16* sprites_rdai_2[];

extern EInit D_us_80180890;

void EntityArcherDeathParts(Entity* self) {
    Entity* other;
    s16 angle;
    s32 xPivot;
    s32 yPivot;
    s16* spritePtr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180890);
        self->animCurFrame = self->params;
        spritePtr = sprites_rdai_2[self->animCurFrame];
        xPivot = spritePtr[2]; // From sprite definition
        yPivot = spritePtr[3]; // From sprite definition
        xPivot += spritePtr[4] / 2; // Shift by half width
        yPivot += spritePtr[5] / 2; // Shift by half height
        self->ext.rdaiArcher.unk94 = xPivot;
        self->ext.rdaiArcher.unk96 = yPivot;
        self->ext.rdaiArcher.timer = ((Random() & 0xF) + 8);
        angle = ratan2(yPivot, xPivot);
        self->velocityX = (rcos(angle) * FIX(2)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(2)) >> 0xC;
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->posX.i.hi += xPivot;
            other->posY.i.hi += yPivot;
            other->params = 1;
        }
        if (self->params > 0x12) {
            self->step = 2;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (!--self->ext.rdaiArcher.timer) {
            PlaySfxPositional(SFX_EXPLODE_D);
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->posX.i.hi += self->ext.rdaiArcher.unk94;
                other->posY.i.hi += self->ext.rdaiArcher.unk96;
                other->params = 1;
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        switch (self->params) {
        case 19:
            if (!self->step_s) {
                self->velocityY = FIX(-2.5);
                self->ext.rdaiArcher.timer = 0x10;
                self->step_s++;
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!--self->ext.rdaiArcher.timer) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posX.i.hi += self->ext.rdaiArcher.unk94;
                    other->posY.i.hi += self->ext.rdaiArcher.unk96;
                    other->params = 1;
                }
                DestroyEntity(self);
                return;
            }
            break;
        case 20:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x18;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!--self->ext.rdaiArcher.timer) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posX.i.hi += self->ext.rdaiArcher.unk94;
                    other->posY.i.hi += self->ext.rdaiArcher.unk96;
                    other->params = 1;
                }
                DestroyEntity(self);
                return;
            }
            break;
        case 21:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x40;
                self->velocityY = 0;
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
        }
        break;
    }
}
