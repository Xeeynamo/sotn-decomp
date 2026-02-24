// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

static u8 anim_walk[] = {
    3, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7, 6, 8, 3, 1, 0, 0};
static s16 D_80182624[] = {0, 1, 1, 3, 6, 2, 1, 4, 4, 0};
static u8 anim_disassemble[] = {
    8,  9, 8,  10, 8,  11, 8,  12, 8,  13, 8,  14, 8,
    15, 8, 16, 8,  17, 8,  18, 8,  19, 16, 20, -1, 0};
static u8 anim_reassemble[] = {
    8, 20, 8, 19, 8, 18, 8, 17, 8, 16, 8,  15, 8,  14,
    8, 13, 8, 12, 8, 11, 8, 10, 8, 9,  16, 2,  -1, 0};
static u8 anim_reassemble_alt[] = {
    3, 20, 3, 19, 3, 18, 3, 17, 3, 16, 3, 15, 3,  14,
    3, 13, 3, 12, 3, 11, 3, 10, 3, 9,  2, 2,  -1, 0};

static s16 timers[] = {64, 40, 96, 56};

static s16 D_80182694[] = {0, 24, 0, 4, 8, -4, -16, 0};

// These are not present on PSP
static s16 unused[] = {0, 24, 8, 0};

static s16 D_801826AC[] = {0x000A, 0x001C, 0x000A, 0x0014, 0x00FF, 0x0000};

typedef enum {
    BLOOD_SKELETON_INIT,
    BLOOD_SKELETON_IDLE,
    BLOOD_SKELETON_WALK,
    BLOOD_SKELETON_DISASSEMBLE,
    BLOOD_SKELETON_REASSEMBLE,
} BLOOD_SKELETON_STEPS;

extern EInit g_EInitBloodSkeleton;

void EntityBloodSkeleton(Entity* self) {
    s32 animationResult;
    u8 collider;

    if ((self->flags & FLAG_DEAD) && (self->step < 3)) {
        PlaySfxPositional(SFX_RED_SKEL_COLLAPSE);
        self->hitboxState = 0;
        SetStep(BLOOD_SKELETON_DISASSEMBLE);
    }

    switch (self->step) {
    case BLOOD_SKELETON_INIT:
        InitializeEntity(g_EInitBloodSkeleton);
        self->facingLeft = Random() & 1;
        self->animCurFrame = 1;
#ifdef STAGE_IS_NZ0
        self->flags &=
            ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
              FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
#endif
        self->palette += self->params;
        break;

    case BLOOD_SKELETON_IDLE:
        if (UnkCollisionFunc3(D_80182694) & 1) {
            self->step_s = 0;
            self->step++;
        }
        break;

    case BLOOD_SKELETON_WALK:
#if defined(STAGE_IS_CAT) || defined(STAGE_IS_RCAT)
        if (!self->step_s) {
            self->ext.bloodSkeleton.timer = timers[Random() & 3];
            self->step_s++;
        }

        if (!--self->ext.bloodSkeleton.timer) {
            self->step_s = 0;
            self->facingLeft = Random() & 1;
        }
#endif

        if (self->poseTimer == 0) {
            if (self->facingLeft) {
                self->posX.i.hi += D_80182624[self->pose];
            } else {
                self->posX.i.hi -= D_80182624[self->pose];
            }
        }

        if (!AnimateEntity(anim_walk, self) && GetDistanceToPlayerY() < 48 &&
            (Random() & 3) == 0) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }

        collider = CheckColliderOffsets(D_801826AC, self->facingLeft);
        if (collider ^ 2) {
            self->facingLeft ^= 1;
        }
        break;

    case BLOOD_SKELETON_DISASSEMBLE:
        if (AnimateEntity(anim_disassemble, self) == 0) {
            self->flags &= ~FLAG_DEAD;
            self->ext.bloodSkeleton.timer = 0xF0;
            if (self->params) {
                self->ext.bloodSkeleton.timer = 4;
            }
            SetStep(BLOOD_SKELETON_REASSEMBLE);
        }
        break;

    case BLOOD_SKELETON_REASSEMBLE:
        switch (self->step_s) {
        case 0:
            if (!--self->ext.bloodSkeleton.timer) {
                self->drawFlags |= ENTITY_ROTATE;
                self->rotate = 0;
                PlaySfxPositional(SFX_RED_SKEL_REBUILD);
                self->step_s++;
                return;
            }
            break;

        case 1:
            if ((g_Timer % 3) == 0) {
                self->ext.bloodSkeleton.timer++;
                if (self->ext.bloodSkeleton.timer % 2) {
                    self->rotate = 0x10;
                } else {
                    self->rotate = -0x10;
                }
            }

            if (self->ext.bloodSkeleton.timer > 8) {
                self->drawFlags = ENTITY_DEFAULT;
                self->rotate = 0;
                self->step_s++;
            }
            break;

        case 2:
            if (!self->params) {
                animationResult = AnimateEntity(anim_reassemble, self);
            } else {
                animationResult = AnimateEntity(anim_reassemble_alt, self);
            }

            if (!animationResult) {
                self->hitPoints = 0;
                self->hitboxState = 3;
                self->flags = g_api.enemyDefs[70].flags;
#ifdef STAGE_IS_NZ0
                self->flags &=
                    ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                      FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
#endif
                SetStep(BLOOD_SKELETON_WALK);
            }
            break;
        }
        break;
    }
}
