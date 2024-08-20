/*
 * Overlay: NZ0
 * Enemy: Blood Skeleton
 */

#include "nz0.h"

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
        PlaySfxPositional(NA_SE_EN_BLOOD_SKELETON_DISASSEMBLES);
        self->hitboxState = 0;
        SetStep(BLOOD_SKELETON_DISASSEMBLE);
    }

    switch (self->step) {
    case BLOOD_SKELETON_INIT:
        InitializeEntity(D_80180C40);
        self->facingLeft = (u32)Random() % 2;
        self->animCurFrame = 1;
        self->flags &= 0x1FFFFFFF;
        self->palette += self->params;
        break;

    case BLOOD_SKELETON_IDLE:
        if (func_801BCCFC(&D_80182694) & 1) {
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

        if ((AnimateEntity(D_80182610, self) == 0) &&
            (GetDistanceToPlayerY() < 48) && (Random() % 4) == 0) {
            self->facingLeft = GetSideToPlayer() % 2 == 0;
        }

        if ((u8)CheckColliderOffsets(&D_801826AC, self->facingLeft) != 2) {
            self->facingLeft ^= 1;
        }
        break;

    case BLOOD_SKELETON_DISASSEMBLE:
        if (AnimateEntity(D_80182638, self) == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 0xF0;
            self->flags &= ~0x100;
            if (self->params != 0) {
                self->ext.generic.unk80.modeS16.unk0 = 4;
            }
            SetStep(BLOOD_SKELETON_REASSEMBLE);
        }
        break;

    case BLOOD_SKELETON_REASSEMBLE:
        switch (self->step_s) {
        case 0:
            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                self->rotZ = 0;
                self->drawFlags |= 4;
                PlaySfxPositional(NA_SE_EN_BLOOD_SKELETON_REASSEMBLES);
                self->step_s++;
                return;
            }
            break;

        case 1:
            if ((g_Timer % 3) == 0) {
                self->ext.generic.unk80.modeS16.unk0++;
                if (self->ext.generic.unk80.modeS16.unk0 % 2) {
                    self->rotZ = 0x10;
                } else {
                    self->rotZ = -0x10;
                }
            }

            if (self->ext.generic.unk80.modeS16.unk0 >= 9) {
                self->drawFlags = 0;
                self->rotZ = 0;
                self->step_s++;
            }
            break;

        case 2:
            if (self->params == 0) {
                animation = &D_80182654;
            } else {
                animation = &D_80182670;
            }

            if (AnimateEntity(animation, self) == 0) {
                self->hitPoints = 0;
                self->hitboxState = 3;
                self->flags = g_api.enemyDefs[70].flags & 0x1FFFFFFF;
                SetStep(BLOOD_SKELETON_WALK);
            }
        }
        break;
    }
}
