// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit g_EInitDodoBird;

extern s32 D_pspeu_09258FB0;
extern s32 D_pspeu_09258FB8;
extern s32 D_pspeu_09258FC8;
extern s32 D_pspeu_09258FD8;

typedef enum { DODO_INIT, DODO_1, DODO_2, DODO_3, DODO_4, DODO_DEAD } DodoSteps;

void func_us_801C8B8C(Entity* self) {
    Entity* other;
    s32 temp_s3;
    s32 temp_v0;
    s32 i;

    if (self->flags & FLAG_DEAD && self->step < DODO_DEAD) {
        SetStep(DODO_DEAD);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDodoBird);
        self->facingLeft = GetSideToPlayer() & 1;
        if (self->params & 0x100) {
            self->drawFlags |= ENTITY_ROTATE;
            self->animCurFrame = 9;
            self->step = DODO_4;
        }
        break;
    case DODO_1:
        if (UnkCollisionFunc3(&D_pspeu_09258FB8) & 1) {
            self->step += 1;
        }
        break;
    case DODO_2:
        AnimateEntity(&D_pspeu_09258FC8, self);
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_QUIET_STEPS);
        }
        temp_v0 = UnkCollisionFunc2(&D_pspeu_09258FB0);
        if (temp_v0 == 0) {
            self->velocityY += FIX(0.25);
        } else {
            self->velocityY = 0;
        }
        if (self->facingLeft) {
            self->velocityX = FIX(-0.75);
        } else {
            self->velocityX = FIX(0.75);
        }
        if (self->ext.ILLEGAL.s16[4]) {
            self->velocityX *= 2;
        }
        if (temp_v0 == 0x80) {
            self->velocityY = FIX(-4.0);
            SetStep(DODO_1);
        }
        if (GetDistanceToPlayerX() < 0x40) {
            temp_s3 = self->facingLeft;
            if (temp_s3 == (GetSideToPlayer() & 1)) {
                self->ext.ILLEGAL.s16[4] |= 1;
                SetStep(DODO_3);
                self->ext.ILLEGAL.s16[2] = 0x20;
            }
        }
        break;
    case DODO_3:
        AnimateEntity(&D_pspeu_09258FD8, self);
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            SetStep(DODO_2);
        }
        break;
    case DODO_4:
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->velocityY = 0;
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                self->step_s += 1;
            }
            break;
        case 1:
            self->velocityY += 0x400;
            self->velocityX = rsin(self->ext.ILLEGAL.s16[2]) * 0x10;
            self->ext.ILLEGAL.s16[2] += 0x20;
            if (self->velocityX > 0) {
                self->rotate -= 0x40;
            } else {
                self->rotate += 0x40;
            }
        }
        break;
    case DODO_DEAD:
        switch (self->step_s) {
        case 0:
            self->ext.ILLEGAL.s16[2] = 0x10;
            self->step_s += 1;
            PlaySfxPositional(SFX_FLEA_RIDER_EXPLODE);
            self->drawFlags |= ENTITY_ROTATE;
            /* fallthrough */
        case 1:
            AnimateEntity(&D_pspeu_09258FD8, self);
            self->rotate -= 0x80;
            if (!(self->ext.ILLEGAL.s16[2] & 3)) {
                for (i = 0; i < 5; i++) {
                    other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (other != NULL) {
                        CreateEntityFromEntity(0x4EU, self, other);
                        other->params = 0x100;
                        other->velocityX = (Random() & 7) << 0xD;
                        if (i != 0) {
                            other->velocityX = -other->velocityX;
                        }
                        other->velocityY = (Random() & 0x3F) * -0x1000;
                        other->posX.i.hi += ((Random() & 0x1F) - 0x10);
                        other->ext.ILLEGAL.s16[2] = Random() * 0x10;
                    }
                }
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->step_s += 1;
            }
            break;
        case 2:
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(2U, self, other);
                other->params = 1;
            }
            DestroyEntity(self);
        }
        break;
    }
}
