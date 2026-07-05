// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit g_EInitDodoBird;

extern s16 sensors1[] = {0, 15, 8, 0};
extern s16 sensors2[] = {0, 15, 0, 4, 8, -4, -16, 0};
extern u8 anim1[] = {5, 1, 2, 2, 5, 3, 2, 4, 5, 5, 5, 6, 0};
extern u8 anim2[] = {2, 7, 2, 8, 0};

typedef enum { DODO_INIT, DODO_WAIT, DODO_2, DODO_3, DODO_4, DODO_DEAD } DodoSteps;

void func_us_801C8B8C(Entity* self) {
    Entity* other;
    s32 facingLeft;
    s32 collRes;
    s32 i;

    if (self->flags & FLAG_DEAD && self->step < DODO_DEAD) {
        SetStep(DODO_DEAD);
    }
    switch (self->step) {
    case DODO_INIT:
        InitializeEntity(g_EInitDodoBird);
        self->facingLeft = GetSideToPlayer() & 1;
        if (self->params & 0x100) {
            self->drawFlags |= ENTITY_ROTATE;
            self->animCurFrame = 9;
            self->step = DODO_4;
        }
        break;
    case DODO_WAIT:
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->step += 1;
        }
        break;
    case DODO_2:
        AnimateEntity(anim1, self);
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_QUIET_STEPS);
        }
        collRes = UnkCollisionFunc2(sensors1);
        if (collRes == 0) {
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
        if (collRes == 0x80) {
            self->velocityY = FIX(-4.0);
            SetStep(DODO_WAIT);
        }
        if (GetDistanceToPlayerX() < 0x40) {
            facingLeft = self->facingLeft;
            if (facingLeft == (GetSideToPlayer() & 1)) {
                self->ext.ILLEGAL.s16[4] |= 1;
                SetStep(DODO_3);
                self->ext.ILLEGAL.s16[2] = 0x20;
            }
        }
        break;
    case DODO_3:
        AnimateEntity(anim2, self);
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
            AnimateEntity(&anim2, self);
            self->rotate -= 0x80;
            if (!(self->ext.ILLEGAL.s16[2] & 3)) {
                for (i = 0; i < 5; i++) {
                    other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (other != NULL) {
                        CreateEntityFromEntity(E_UNK_4E, self, other);
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
