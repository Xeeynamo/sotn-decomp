// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

// The dodo is a little weird. When it dies it spawns a bunch of feather
// entities. But those entities are actually the same internal entity,
// just running on a different step.
#define FLAG_FEATHER (0x100)

extern EInit g_EInitDodoBird;

static s16 sensors1[] = {0, 15, 8, 0};
static s16 sensors2[] = {0, 15, 0, 4, 8, -4, -16, 0};
static u8 dodo_walk[] = {5, 1, 2, 2, 5, 3, 2, 4, 5, 5, 5, 6, 0};
static u8 dodo_freakout[] = {2, 7, 2, 8, 0};

typedef enum {
    DODO_INIT,
    DODO_WAIT,
    DODO_WALK,
    DODO_FREAKOUT,
    DODO_FEATHER,
    DODO_DEAD
} DodoSteps;

void EntityDodoBird(Entity* self) {
    Entity* other;
    u16 facingLeft;
    s32 collRes;
    s32 i;

    if (self->flags & FLAG_DEAD && self->step < DODO_DEAD) {
        SetStep(DODO_DEAD);
    }
    switch (self->step) {
    case DODO_INIT:
        InitializeEntity(g_EInitDodoBird);
        self->facingLeft = GetSideToPlayer() & 1;
        if (self->params & FLAG_FEATHER) {
            self->drawFlags |= ENTITY_ROTATE;
            self->animCurFrame = 9;
            self->step = DODO_FEATHER;
        }
        break;
    case DODO_WAIT:
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->step += 1;
        }
        break;
    case DODO_WALK:
        AnimateEntity(dodo_walk, self);
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
        if (self->ext.dodo.doubleSpeed) {
            self->velocityX *= 2;
        }
        if (collRes == 0x80) {
            self->velocityY = FIX(-4.0);
            SetStep(DODO_WAIT);
        }
        if (GetDistanceToPlayerX() < 64) {
            if ((GetSideToPlayer() & 1) == self->facingLeft) {
                self->ext.dodo.doubleSpeed |= 1;
                SetStep(DODO_FREAKOUT);
                self->ext.dodo.timer = 0x20;
            }
        }
        break;
    case DODO_FREAKOUT:
        AnimateEntity(dodo_freakout, self);
        if (!--self->ext.dodo.timer) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            SetStep(DODO_WALK);
        }
        break;
    case DODO_FEATHER:
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->velocityY = 0;
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;
        case 1:
            self->velocityY += 0x400;
            self->velocityX = rsin(self->ext.dodo.timer) * 0x10;
            self->ext.dodo.timer += 0x20;
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
            self->ext.dodo.timer = 16;
            self->step_s += 1;
            PlaySfxPositional(SFX_FLEA_RIDER_EXPLODE);
            self->drawFlags |= ENTITY_ROTATE;
            /* fallthrough */
        case 1:
            AnimateEntity(&dodo_freakout, self);
            self->rotate -= 0x80;
            // Every 4 frames, spawn 5 more feathers.
            // Timer starts at 16, so this will hit 4 times.
            // Total of 20 feathers.
            if (!(self->ext.dodo.timer & 3)) {
                for (i = 0; i < 5; i++) {
                    other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (other != NULL) {
                        CreateEntityFromEntity(E_DODO_BIRD, self, other);
                        other->params = FLAG_FEATHER;
                        other->velocityX = (Random() & 7) << 0xD;
                        if (i != 0) {
                            other->velocityX = -other->velocityX;
                        }
                        other->velocityY = -(Random() & 0x3F) * 0x1000;
                        other->posX.i.hi += ((Random() & 0x1F) - 0x10);
                        other->ext.dodo.timer = Random() * 0x10;
                    }
                }
            }
            if (!--self->ext.dodo.timer) {
                self->step_s += 1;
            }
            break;
        case 2:
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 1;
            }
            DestroyEntity(self);
        }
        break;
    }
}
