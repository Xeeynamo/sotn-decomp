// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum BoneHalberdSteps {
    BONE_HALBERD_INIT,
    BONE_HALBERD_READY,
    BONE_HALBERD_IDLE,
    BONE_HALBERD_MOVE,
    BONE_HALBERD_SPIN_STAB,
    BONE_HALBERD_JUMP,
    BONE_HALBERD_DEATH,
    BONE_HALBERD_LUNGE,
};

enum BoneHalberdJumpSubsteps {
    BONE_HALBERD_JUMP_INIT,
    BONE_HALBERD_JUMP_MOVE,
    BONE_HALBERD_JUMP_LAND,
};

enum BoneHalberdLungeSubsteps {
    BONE_HALBERD_LUNGE_INIT,
    BONE_HALBERD_LUNGE_CLOSE_GAP,
    BONE_HALBERD_LUNGE_STAB,
    BONE_HALBERD_LUNGE_CONCLUDE,
};

extern EInit g_EInitBoneHalberd;
extern EInit g_EInitBoneHalberdAttack;

static AnimateEntityFrame anim_idle[] = {
    {6, 1}, {4, 2}, {4, 3}, {6, 4}, {5, 5}, {5, 6}, POSE_LOOP(0)};
static AnimateEntityFrame anim_lunge[] = {
    {3, 1}, {2, 2}, {2, 3}, {3, 4}, {2, 5}, {2, 6}, POSE_LOOP(0)};
static AnimateEntityFrame anim_move[] = {
    {6, 1}, {5, 6}, {5, 5}, {6, 4}, {4, 3}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_spin_stab[] = {
    {5, 1},  {5, 2},  {5, 7},  {6, 8},   {2, 9},  {2, 10}, {2, 11}, {2, 12},
    {2, 13}, {2, 10}, {2, 11}, {2, 12},  {2, 13}, {3, 14}, {5, 15}, {5, 16},
    {5, 17}, {1, 18}, {2, 19}, {20, 20}, {5, 21}, {3, 22}, {2, 23}, {2, 24},
    {2, 25}, {1, 26}, {1, 27}, {1, 28},  {2, 29}, POSE_END};
static AnimateEntityFrame anim_jump[] = {
    {1, 1}, {4, 30}, {4, 31}, {1, 1}, POSE_END};
static AnimateEntityFrame anim_land[] = {
    {1, 1}, {4, 30}, {6, 31}, {4, 30}, {1, 1}, POSE_END};
static u16 rotation_interval[] = {256, 128, 72, 32, 64, 16, 32, -32, 32};
static u8 part_lifespan[] = {48, 32, 20, 12, 24, 16, 64, 48, 48};
static s32 velocity_x[] = {FIX(0.75), FIX(1.75), FIX(1.5), FIX(1.0), FIX(2.0),
                           FIX(1.75), FIX(-0.5), FIX(0.0), FIX(0.5)};
static s32 velocity_y[] = {
    FIX(-5.0),   FIX(-3.0), FIX(-2.0), FIX(-3.0), FIX(-4.0),
    FIX(-0.875), FIX(-6.0), FIX(-4.5), FIX(-4.5)};
static s16 interval_x[] = {
    -4, 0, 4, -4, -4, 4, -6, 0, 6, 0,
};
static s16 interval_y[] = {-16, -8, -4, -4, 9, 9, 2, 0, -2, 0};
static u8 attack_intervals[][4] = {{96, 8, 8, 32}, {32, 64, 16, 80}};
static s16 sensors_bone_halberd[] = {0, 20, 0, 4, 8, -4, -16};
static s16 sensors_lunge[] = {0, 20, 12, 0};
static s16 sensors_jump[] = {-12, 16, 0, -16, 0, -16};
// Groups of x, y, w, and h
static s16 hitbox_offsets[] = {
    0,   0,   0,  0, -9,  -22, 6,  6,  -25, -16, 8,  3, -29, -21, 10, 3,
    -39, -26, 10, 3, -54, -16, 15, 11, -64, -5,  11, 3, -64, -5,  11, 3};

static void BoneHalberdMove(void) {
    // Is one of these functions checking for wall collision and one checking
    // for ledge collision?
    s32 collision2 = UnkCollisionFunc2(sensors_lunge);
    u16 collision = UnkCollisionFunc(sensors_jump, 3);

    if ((collision2 == 128) || (collision & 2)) {
        SetStep(BONE_HALBERD_JUMP);
        return;
    }
    if (!g_CurrentEntity->ext.boneHalberd.timer) {
        if (GetDistanceToPlayerX() < 84) {
            if (g_CurrentEntity->facingLeft ^ (GetSideToPlayer() & 1)) {
                SetStep(BONE_HALBERD_SPIN_STAB);
            }
        }
    } else {
        g_CurrentEntity->ext.boneHalberd.timer--;
        if (!g_CurrentEntity->ext.boneHalberd.timer && !(Random() & 3)) {
            SetStep(BONE_HALBERD_LUNGE);
        }
    }
}

void EntityBoneHalberd(Entity* self) {
    s32 collision;
    u8 tempVar;
    s32 partIdx;
    Entity* boneHalberdPart;

    if (self->flags & FLAG_DEAD) {
        self->step = BONE_HALBERD_DEATH;
    }
    switch (self->step) {
    case BONE_HALBERD_INIT:
        InitializeEntity(g_EInitBoneHalberd);
        self->ext.boneHalberd.timer = 64;
        self->ext.boneHalberd.facingLeft = 0;
        self->ext.boneHalberd.attackIntervalIdx = 0;
        boneHalberdPart = self + 1;
        CreateEntityFromCurrentEntity(E_BONE_HALBERD_ATTACK, boneHalberdPart);
        break;
    case BONE_HALBERD_READY:
        // Could this function be CheckGroundCollision?
        if (UnkCollisionFunc3(sensors_bone_halberd)) {
            self->step++;
            return;
        }
    default:
        break;
    case BONE_HALBERD_IDLE:
        if (!AnimateEntity(anim_idle, self)) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        self->ext.boneHalberd.facingLeft = self->facingLeft;
        if (self->ext.boneHalberd.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 76) {
            self->step = BONE_HALBERD_MOVE;
        }
        BoneHalberdMove();
        break;
    case BONE_HALBERD_MOVE:
        if (!AnimateEntity(anim_move, self)) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        self->ext.boneHalberd.facingLeft = ((self->facingLeft) ^ 1);
        if (self->ext.boneHalberd.facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 92) {
            self->step = BONE_HALBERD_IDLE;
        }
        BoneHalberdMove();
        break;
    case BONE_HALBERD_SPIN_STAB:
        tempVar = AnimateEntity(anim_spin_stab, self);
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
        }
        if ((!self->poseTimer) && (self->pose == 18)) {
            PlaySfxPositional(SFX_WEAPON_STAB_B);
        }
        if (!tempVar) {
            SetStep(BONE_HALBERD_MOVE);
            tempVar = ++self->ext.boneHalberd.attackIntervalIdx & 3;
            self->ext.boneHalberd.timer =
                attack_intervals[self->params & 1][tempVar];
            return;
        }
        break;
    case BONE_HALBERD_LUNGE:
        switch (self->step_s) {
        case BONE_HALBERD_LUNGE_INIT:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.boneHalberd.lungeTimer = 192;
            self->step_s++;
            break;
        case BONE_HALBERD_LUNGE_CLOSE_GAP:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            AnimateEntity(anim_lunge, self);
            collision = UnkCollisionFunc2(sensors_lunge);
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            // Encounters a wall or ledge (unsure which) or timer expires
            if ((collision & 128) || (!--self->ext.boneHalberd.lungeTimer)) {
                SetSubStep(BONE_HALBERD_MOVE);
            }
            if (GetDistanceToPlayerX() < 56) {
                // random number of stabs between 1 and 4
                self->ext.boneHalberd.lungeTimer = ((Random() & 3) + 1);
                self->poseTimer = 16;
                self->pose = 14;
                SetSubStep(BONE_HALBERD_LUNGE_STAB);
                return;
            }
            break;
        case BONE_HALBERD_LUNGE_STAB:
            if ((!self->poseTimer) && ((self->pose) == 5)) {
                PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
            }
            if ((!self->poseTimer) && ((self->pose) == 18)) {
                PlaySfxPositional(SFX_WEAPON_STAB_B);
            }
            if (!AnimateEntity(anim_spin_stab, self)) {
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                self->pose = 2;
                self->poseTimer = 0;
                self->ext.boneHalberd.lungeTimer--;
                if (!self->ext.boneHalberd.lungeTimer) {
                    SetSubStep(BONE_HALBERD_LUNGE_CONCLUDE);
                    return;
                }
            }
            break;
        case BONE_HALBERD_LUNGE_CONCLUDE:
            SetStep(BONE_HALBERD_MOVE);
            tempVar = ++self->ext.boneHalberd.attackIntervalIdx & 3;
            self->ext.boneHalberd.timer =
                attack_intervals[self->params & 1][tempVar];
            break;
        }
        break;
    case BONE_HALBERD_JUMP:
        switch (self->step_s) {
        case BONE_HALBERD_JUMP_INIT:
            if (!(AnimateEntity(anim_jump, self) & 1)) {
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
        case BONE_HALBERD_JUMP_MOVE:
            if (UnkCollisionFunc3(sensors_bone_halberd)) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->step_s++;
            }
            CheckFieldCollision(sensors_jump, 2);
            break;
        case BONE_HALBERD_JUMP_LAND:
            if (!AnimateEntity(anim_land, self)) {
                SetStep(BONE_HALBERD_MOVE);
            }
            break;
        }
        break;
    case BONE_HALBERD_DEATH:
        for (partIdx = 0; partIdx < 9; partIdx++) {
            boneHalberdPart = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (boneHalberdPart != 0) {
                CreateEntityFromCurrentEntity(
                    E_BONE_HALBERD_PARTS, boneHalberdPart);
                boneHalberdPart->facingLeft = self->facingLeft;
                boneHalberdPart->params = partIdx;
                boneHalberdPart->ext.boneHalberd.partLifespan =
                    part_lifespan[partIdx];
                if (self->facingLeft) {
                    boneHalberdPart->posX.i.hi -= interval_x[partIdx];
                } else {
                    boneHalberdPart->posX.i.hi += interval_x[partIdx];
                }
                boneHalberdPart->posY.i.hi += interval_y[partIdx];
                boneHalberdPart->velocityX = velocity_x[partIdx];
                boneHalberdPart->velocityY = velocity_y[partIdx];
            } else {
                break;
            }
        }
        boneHalberdPart = self + 1;
        DestroyEntity(boneHalberdPart);
        g_api.PlaySfx(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBoneHalberdParts(Entity* self) {
    if (self->step) {
        if (--self->ext.boneHalberd.partLifespan) {
            self->rotate += rotation_interval[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = EXPLOSION_SMALL;
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

void EntityBoneHalberdAttack(Entity* self) {
    Entity* boneHalberd;
    s16* hitboxOffsetPtr;
    s32 animCurFrame;

    if (!self->step) {
        InitializeEntity(g_EInitBoneHalberdAttack);
        self->hitboxState = 1;
    }
    boneHalberd = self - 1;
    POS(self->posX) = POS(boneHalberd->posX);
    self->facingLeft = boneHalberd->facingLeft;
    animCurFrame = boneHalberd->animCurFrame;
    animCurFrame -= 13;
    if (animCurFrame < 0) {
        animCurFrame = 0;
    }
    if (animCurFrame > 7) {
        animCurFrame = 0;
    }
    hitboxOffsetPtr = &hitbox_offsets[animCurFrame * 4];
    self->hitboxOffX = *hitboxOffsetPtr++;
    self->hitboxOffY = *hitboxOffsetPtr++;
    self->hitboxWidth = *hitboxOffsetPtr++;
    self->hitboxHeight = *hitboxOffsetPtr++;
    if ((boneHalberd->entityId) != E_BONE_HALBERD) {
        DestroyEntity(self);
    }
}
