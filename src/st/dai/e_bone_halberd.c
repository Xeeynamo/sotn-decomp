// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static u8 anim_1[] = {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0, 0, 0, 0};
static u8 anim_2[] = {3, 1, 2, 2, 2, 3, 3, 4, 2, 5, 2, 6, 0, 0, 0, 0};
static u8 anim_3[] = {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0, 0, 0, 0};
static u8 anim_4[] = {
    5, 1,  5, 2,  5, 7,  6, 8,  2, 9,  2, 10, 2, 11, 2, 12, 2, 13, 2,  10,
    2, 11, 2, 12, 2, 13, 3, 14, 5, 15, 5, 16, 5, 17, 1, 18, 2, 19, 20, 20,
    5, 21, 3, 22, 2, 23, 2, 24, 2, 25, 1, 26, 1, 27, 1, 28, 2, 29, -1, 0};
static u8 anim_5[] = {1, 1, 4, 30, 4, 31, 1, 1, -1, 0, 0, 0};
static u8 anim_6[] = {1, 1, 4, 30, 6, 31, 4, 30, 1, 1, -1, 0};
static u16 rotation_interval[] = {256, 128, 72, 32, 64, 16, 32, -32, 32, 0};
static u8 D_us_80181DD8[] = {
    48, 32, 20, 12, 24, 16, 64, 48, 48, 0, 0, 0,
};
static s32 velocity_x[] = {FIX(0.75), FIX(1.75), FIX(1.5), FIX(1.0), FIX(2.0),
                           FIX(1.75), FIX(-0.5), FIX(0.0), FIX(0.5)};
static s32 velocity_y[] = {
    FIX(-5.0),   FIX(-3.0), FIX(-2.0), FIX(-3.0), FIX(-4.0),
    FIX(-0.875), FIX(-6.0), FIX(-4.5), FIX(-4.5)};
static s16 interval_x[] = {
    -4, 0, 4, -4, -4, 4, -6, 0, 6, 0,
};
static s16 interval_y[] = {-16, -8, -4, -4, 9, 9, 2, 0, -2, 0};
static u8 D_us_80181E54[][4] = {{96, 8, 8, 32}, {32, 64, 16, 80}};
static s16 sensors[] = {0, 0x14, 0, 4, 8, -4, -16};
static s16 attack_sensors_2[] = {0, 0x14, 12, 0};
static s16 attack_sensors[] = {-12, 16, 0, -16, 0, -16};
static s16 hitbox[] = {
    0,   0,   0,  0, -9,  -22, 6,  6,  -25, -16, 8,  3, -29, -21, 10, 3,
    -39, -26, 10, 3, -54, -16, 15, 11, -64, -5,  11, 3, -64, -5,  11, 3};

static void BoneHalberdAttack(void) {
    s32 collision2 = UnkCollisionFunc2(&attack_sensors_2);
    u16 collision = UnkCollisionFunc(&attack_sensors, 3);

    if ((collision2 == 128) || (collision & 2)) {
        SetStep(5);
        return;
    }
    if (!g_CurrentEntity->ext.boneHalberd.unk7C) {
        if (GetDistanceToPlayerX() < 84) {
            if ((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
                SetStep(4);
            }
        }
    } else {
        g_CurrentEntity->ext.boneHalberd.unk7C--;
        if ((!g_CurrentEntity->ext.boneHalberd.unk7C) && !(Random() & 3)) {
            SetStep(7);
        }
    }
}

void EntityBoneHalberd(Entity* self) {
    s32 collision;
    u8 tempVar;
    s32 idx;
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        self->step = 6;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneHalberd);
        self->ext.boneHalberd.unk7C = 64;
        self->ext.boneHalberd.facingLeft = 0;
        self->ext.boneHalberd.unk84 = 0;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_BONE_HALBERD_NAGINATA, entity);
        break;
    case 1:
        if (UnkCollisionFunc3(sensors)) {
            self->step++;
            return;
        }
    default:
        break;
    case 2:
        if (!AnimateEntity(anim_1, self)) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        self->ext.boneHalberd.facingLeft = self->facingLeft;
        if (self->ext.boneHalberd.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 76) {
            self->step = 3;
        }
        BoneHalberdAttack();
        break;
    case 3:
        if (!AnimateEntity(anim_3, self)) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        self->ext.boneHalberd.facingLeft = ((self->facingLeft) ^ 1);
        if (self->ext.boneHalberd.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 92) {
            self->step = 2;
        }
        BoneHalberdAttack();
        break;
    case 4:
        tempVar = AnimateEntity(anim_4, self);
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
        }
        if ((!self->poseTimer) && ((self->pose) == 18)) {
            PlaySfxPositional(SFX_WEAPON_STAB_B);
        }
        if (!tempVar) {
            SetStep(3);
            tempVar = ++self->ext.boneHalberd.unk84 & 3;
            self->ext.boneHalberd.unk7C =
                D_us_80181E54[self->params & 1][tempVar];
            return;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.boneHalberd.unk8C = 192;
            self->step_s++;
            break;
        case 1:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            AnimateEntity(anim_2, self);
            collision = UnkCollisionFunc2(&attack_sensors_2);
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            if ((collision & 128) || (!--self->ext.boneHalberd.unk8C)) {
                SetSubStep(3);
            }
            if (GetDistanceToPlayerX() < 56) {
                self->ext.boneHalberd.unk8C = ((Random() & 3) + 1);
                self->poseTimer = 16;
                self->pose = 14;
                SetSubStep(2);
                return;
            }
            break;
        case 2:
            if ((!self->poseTimer) && ((self->pose) == 5)) {
                PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
            }
            if ((!self->poseTimer) && ((self->pose) == 18)) {
                PlaySfxPositional(SFX_WEAPON_STAB_B);
            }
            if (!AnimateEntity(anim_4, self)) {
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                self->pose = 2;
                self->poseTimer = 0;
                self->ext.boneHalberd.unk8C--;
                if (!self->ext.boneHalberd.unk8C) {
                    SetSubStep(3);
                    return;
                }
            }
            break;
        case 3:
            SetStep(3);
            tempVar = ++self->ext.boneHalberd.unk84 & 3;
            self->ext.boneHalberd.unk7C =
                D_us_80181E54[self->params & 1][tempVar];
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!(AnimateEntity(anim_5, self) & 1)) {
                tempVar = self->ext.boneHalberd.facingLeft;
                if (!(Random() & 3)) {
                    tempVar ^= 1;
                }
                if (tempVar) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->velocityY = FIX(-3.0);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
                return;
            }
            break;
        case 1:
            if (UnkCollisionFunc3(sensors)) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->step_s++;
            }
            CheckFieldCollision(attack_sensors, 2);
            break;
        case 2:
            if (!AnimateEntity(anim_6, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        for (idx = 0; idx < 9; idx++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_BONE_HALBERD_PARTS, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = idx;
                entity->ext.boneHalberd.unk88 = D_us_80181DD8[idx];
                if (self->facingLeft) {
                    entity->posX.i.hi -= interval_x[idx];
                } else {
                    entity->posX.i.hi += interval_x[idx];
                }
                entity->posY.i.hi += interval_y[idx];
                entity->velocityX = velocity_x[idx];
                entity->velocityY = velocity_y[idx];
            } else {
                break;
            }
        }
        entity = self + 1;
        DestroyEntity(entity);
        g_api.PlaySfx(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBoneHalberdParts(Entity* self) {
    if (self->step) {
        if (--self->ext.skeleton.explosionTimer) {
            self->rotate += rotation_interval[self->params];
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
    InitializeEntity(g_EInitBoneHalberd);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 32;
    self->drawFlags = FLAG_DRAW_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void EntityBoneHalberdNaginata(Entity* self) {
    Entity* parent;
    s16* hitboxPtr;
    s32 animCurFrame;

    if (!self->step) {
        InitializeEntity(g_EInitBoneHalberdNaginata);
        self->hitboxState = 1;
    }
    parent = self - 1;
    POS(self->posX) = POS(parent->posX);
    self->facingLeft = parent->facingLeft;
    animCurFrame = parent->animCurFrame;
    animCurFrame -= 13;
    if (animCurFrame < 0) {
        animCurFrame = 0;
    }
    if (animCurFrame > 7) {
        animCurFrame = 0;
    }
    hitboxPtr = &hitbox[animCurFrame * 4];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    if ((parent->entityId) != 50) {
        DestroyEntity(self);
    }
}
