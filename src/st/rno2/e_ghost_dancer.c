// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

static s16 sensors1[] = {0, 29, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 29, 6, 0};
static AnimateEntityFrame anim_walk[] = {
    {4, 1}, {4, 2}, {4, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim_turnaround[] = {
    {3, 8}, {3, 9}, {3, 10}, {3, 11}, POSE_END};
static AnimateEntityFrame anim_crouched[] = {
    {4, 12}, {4, 13}, {4, 14}, POSE_END};
static s16 deathPartsData[][4] = {
    {0, 0, 64, 32}, {0, 0, 32, 18}, {0, 0, 48, 24},
    {0, 0, 16, 12}, {0, 0, 64, 20}, {0, 0, 8, 16}};

STATIC_PAD_DATA(4);

extern EInit g_EInitGhostDancer;

typedef enum {
    GD_INIT,
    GD_GROUND_DETECT,
    GD_WALK,
    GD_TURN_AROUND,
    GD_LEAP,
    GD_5_UNUSED,
    GD_DEATHPARTS
} GD_Steps;

void EntityGhostDancer(Entity* self) {
    Entity* other;
    s16* deathPartsParams;
    s32 coll;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                deathPartsParams = deathPartsData[i];
                CreateEntityFromEntity(E_GHOST_DANCER, self, other);
                other->facingLeft = self->facingLeft;
                other->params = (i + 0x100);
                if (self->facingLeft) {
                    other->posX.i.hi -= *deathPartsParams++;
                } else {
                    other->posX.i.hi += *deathPartsParams++;
                }
                other->posY.i.hi += *deathPartsParams++;
                other->ext.ghostDancer.rotSpeed = *deathPartsParams++;
                other->ext.ghostDancer.timer = *deathPartsParams++;
                other->velocityY = (Random() & 0x1F) * -0x1000;
                other->velocityX = (Random() & 0x3F) * 0xC00;
                if (((GetSideToPlayer() & 1) ^ 1)) {
                    other->velocityX = -other->velocityX;
                }
            }
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 2;
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case GD_INIT:
        InitializeEntity(g_EInitGhostDancer);
        self->hitboxOffY = 2;
        if (Random() & 1) {
            self->palette++;
        }
        if (self->params & 0x100) {
            self->drawFlags |= ENTITY_ROTATE;
            self->animCurFrame = (self->params & 0xF) + 0x10;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000 |
                           FLAG_UNK_2000;
            self->step = GD_DEATHPARTS;
            return;
        }
        self->animCurFrame = 1;
        self->ext.ghostDancer.timer = 0;
        return;
    case GD_GROUND_DETECT:
        if (UnkCollisionFunc3(sensors1) & 1) {
            self->step++;
        }
        break;
    case GD_WALK:
        if (self->facingLeft) {
            self->velocityX = FIX(1.5);
        } else {
            self->velocityX = FIX(-1.5);
        }
        coll = UnkCollisionFunc2(sensors2);
        if (coll == 0x80) {
            SetStep(GD_LEAP);
        }
        if (coll == 0xFF) {
            SetStep(GD_TURN_AROUND);
        }
        if (AnimateEntity(anim_walk, self) == 0) {
            if (self->facingLeft == (GetSideToPlayer() & 1)) {
                SetStep(GD_TURN_AROUND);
            }
        }
        if (!self->ext.ghostDancer.timer) {
            if ((self->facingLeft ^ (GetSideToPlayer() & 1)) &&
                (GetDistanceToPlayerX() < 0x40)) {
                SetStep(GD_LEAP);
            }
        } else {
            self->ext.ghostDancer.timer--;
        }
        break;
    case GD_TURN_AROUND:
        if (AnimateEntity(anim_turnaround, self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 1;
            SetStep(GD_WALK);
        }
        break;
    case GD_LEAP:
        switch (self->step_s) {
        case 0:
            self->hitboxWidth = 8;
            self->hitboxHeight = 0xF;
            self->hitboxOffX = -2;
            self->hitboxOffY = 0xD;
            if (AnimateEntity(anim_crouched, self) == 0) {
                self->step_s++;
            }
            break;
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-6.5);
            self->drawFlags |= ENTITY_ROTATE;
            self->animCurFrame = 15;
            self->rotate = ROT(45);
            self->hitboxOffY = -8;
            self->step_s++;
            /* fallthrough */
        case 2:
            self->rotate -= ROT(1.40625);
            if (UnkCollisionFunc3(sensors1) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->hitboxOffY = 0xD;
                self->drawFlags = ENTITY_DEFAULT;
                self->animCurFrame = 14;
                self->ext.ghostDancer.timer = 0x10;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.ghostDancer.timer) {
                self->hitboxWidth = 5;
                self->hitboxHeight = 0x19;
                self->hitboxOffX = 0;
                self->hitboxOffY = 2;
                self->ext.ghostDancer.timer = 0x20;
                SetStep(GD_WALK);
            }
        }
        break;
    case GD_DEATHPARTS:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotate += self->ext.ghostDancer.rotSpeed;
        if (!--self->ext.ghostDancer.timer) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}
