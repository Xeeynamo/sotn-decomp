// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
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
    0x03, 0x14, 0x03, 0x13, 0x03, 0x12, 0x03, 0x11, 0x03, 0x10, 0x03, 0x0F,
    0x03, 0x0E, 0x03, 0x0D, 0x03, 0x0C, 0x03, 0x0B, 0x03, 0x0A, 0x03, 0x09,
    0x02, 0x02, 0xFF, 0x00, 0x40, 0x00, 0x28, 0x00, 0x60, 0x00, 0x38, 0x00};
static s16 D_80182694[] = {0x0000, 0x0018, 0x0000, 0x0004, 0x0008, 0xFFFC,
                           0xFFF0, 0x0000, 0x0000, 0x0018, 0x0008, 0x0000};
static s16 D_801826AC[] = {0x000A, 0x001C, 0x000A, 0x0014, 0x00FF, 0x0000};

typedef enum {
    BLOOD_SKELETON_INIT,
    BLOOD_SKELETON_IDLE,
    BLOOD_SKELETON_WALK,
    BLOOD_SKELETON_DISASSEMBLE,
    BLOOD_SKELETON_REASSEMBLE,
} BLOOD_SKELETON_STEPS;

void EntityBloodSkeleton(Entity* self) {
    u8* animation;

    if ((self->flags & FLAG_DEAD) && (self->step < 3)) {
        PlaySfxPositional(SFX_RED_SKEL_COLLAPSE);
        self->hitboxState = 0;
        SetStep(BLOOD_SKELETON_DISASSEMBLE);
    }

    switch (self->step) {
    case BLOOD_SKELETON_INIT:
        InitializeEntity(g_EInitBloodSkeleton);
        self->facingLeft = (u32)Random() % 2;
        self->animCurFrame = 1;
        self->flags &=
            ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
              FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
        self->palette += self->params;
        break;

    case BLOOD_SKELETON_IDLE:
        if (UnkCollisionFunc3(D_80182694) & 1) {
            self->step_s = 0;
            self->step++;
        }
        break;

    case BLOOD_SKELETON_WALK:
        if (self->animFrameDuration == 0) {
            if (self->facingLeft != 0) {
                self->posX.i.hi += D_80182624[self->animFrameIdx];
            } else {
                self->posX.i.hi -= D_80182624[self->animFrameIdx];
            }
        }

        if ((AnimateEntity(anim_walk, self) == 0) &&
            (GetDistanceToPlayerY() < 48) && (Random() % 4) == 0) {
            self->facingLeft = GetSideToPlayer() % 2 == 0;
        }

        if ((u8)CheckColliderOffsets(D_801826AC, self->facingLeft) != 2) {
            self->facingLeft ^= 1;
        }
        break;

    case BLOOD_SKELETON_DISASSEMBLE:
        if (AnimateEntity(anim_disassemble, self) == 0) {
            self->ext.bloodSkeleton.timer = 0xF0;
            self->flags &= ~FLAG_DEAD;
            if (self->params != 0) {
                self->ext.bloodSkeleton.timer = 4;
            }
            SetStep(BLOOD_SKELETON_REASSEMBLE);
        }
        break;

    case BLOOD_SKELETON_REASSEMBLE:
        switch (self->step_s) {
        case 0:
            if (--self->ext.bloodSkeleton.timer == 0) {
                self->rotZ = 0;
                self->drawFlags |= FLAG_DRAW_ROTZ;
                PlaySfxPositional(SFX_RED_SKEL_REBUILD);
                self->step_s++;
                return;
            }
            break;

        case 1:
            if ((g_Timer % 3) == 0) {
                self->ext.bloodSkeleton.timer++;
                if (self->ext.bloodSkeleton.timer % 2) {
                    self->rotZ = 0x10;
                } else {
                    self->rotZ = -0x10;
                }
            }

            if (self->ext.bloodSkeleton.timer >= 9) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->rotZ = 0;
                self->step_s++;
            }
            break;

        case 2:
            if (self->params == 0) {
                animation = &anim_reassemble;
            } else {
                animation = &anim_reassemble_alt;
            }

            if (AnimateEntity(animation, self) == 0) {
                self->hitPoints = 0;
                self->hitboxState = 3;
                self->flags =
                    g_api.enemyDefs[70].flags &
                    ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                      FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
                SetStep(BLOOD_SKELETON_WALK);
            }
        }
        break;
    }
}
