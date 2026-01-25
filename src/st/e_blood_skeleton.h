// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

static u8 anim_walk[] = {
    0x03, 0x01, 0x06, 0x02, 0x06, 0x03, 0x06, 0x04, 0x06, 0x05,
    0x06, 0x06, 0x06, 0x07, 0x06, 0x08, 0x03, 0x01, 0x00, 0x00};
static s16 D_80182624[] = {0, 1, 1, 3, 6, 2, 1, 4, 4, 0};
static u8 anim_disassemble[] = {
    0x08, 0x09, 0x08, 0x0A, 0x08, 0x0B, 0x08, 0x0C, 0x08, 0x0D,
    0x08, 0x0E, 0x08, 0x0F, 0x08, 0x10, 0x08, 0x11, 0x08, 0x12,
    0x08, 0x13, 0x10, 0x14, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_reassemble[] = {
    0x08, 0x14, 0x08, 0x13, 0x08, 0x12, 0x08, 0x11, 0x08, 0x10,
    0x08, 0x0F, 0x08, 0x0E, 0x08, 0x0D, 0x08, 0x0C, 0x08, 0x0B,
    0x08, 0x0A, 0x08, 0x09, 0x10, 0x02, 0xFF, 0x00};
static u8 anim_reassemble_alt[] = {
    0x03, 0x14, 0x03, 0x13, 0x03, 0x12, 0x03, 0x11, 0x03, 0x10,
    0x03, 0x0F, 0x03, 0x0E, 0x03, 0x0D, 0x03, 0x0C, 0x03, 0x0B,
    0x03, 0x0A, 0x03, 0x09, 0x02, 0x02, 0xFF, 0x00};

static s16 timers[] = {64, 40, 96, 56};

static s16 D_80182694[] = {
    0x0000, 0x0018, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000};

// These are not present on PSP
static s16 unused[] = {0x0000, 0x0018, 0x0008, 0x0000};

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
                self->drawFlags |= FLAG_DRAW_ROTATE;
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
                self->drawFlags = FLAG_DRAW_DEFAULT;
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
#ifdef STAGE_IS_NZ0
                self->flags =
                    g_api.enemyDefs[70].flags &
                    ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                      FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
#else
                self->flags = g_api.enemyDefs[70].flags;
#endif
                SetStep(BLOOD_SKELETON_WALK);
            }
            break;
        }
        break;
    }
}
