// SPDX-License-Identifier: AGPL-3.0-or-later

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

extern u8 D_pspeu_092589E8[];
extern u8 D_pspeu_092589F8[];
extern u8 D_pspeu_09258A10[];
extern u8 D_pspeu_09258A30[];
extern EInit D_pspeu_092607C0;

typedef enum{
    BF_INIT,
    BF_IDLE = 2,
    BF_HIT = 4,
    BF_DEAD = 8
} BitterflySteps;

typedef enum{
    BF_DEAD_INIT,
    BF_DEAD_BECOME_SKULL,
    BF_DEAD_FALL,
    BF_DEAD_EXPLODE
} BitterflyDeadSubsteps;

void EntityUnk31(Entity* self) {
    Entity* other;
    s32 xVar;
    s32 yVar;
    s16 angle;
    s32 tempVar; // Used as a temp in 2 different places

    if ((self->flags & FLAG_DEAD) && (self->step < BF_DEAD)) {
        SetStep(BF_DEAD);
    }
    if ((self->hitFlags & 3) && (self->step != BF_HIT)) {
        SetStep(BF_HIT);
    }
    switch (self->step) {
    case BF_INIT:
        InitializeEntity(D_pspeu_092607C0);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->hitboxOffY = 1;
        SetStep(BF_IDLE);
        break;
    case BF_IDLE:
        AnimateEntity(D_pspeu_092589F8, self);
        MoveEntity();
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = (other->posY.i.hi - 0x40) - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->ext.bitterfly.angle =
                GetNormalizedAngle(8, self->ext.bitterfly.angle, angle);
            self->velocityX = (rcos(self->ext.bitterfly.angle) << 0xF) >> 0xC;
            self->velocityY = (rsin(self->ext.bitterfly.angle) << 0xF) >> 0xC;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }

            tempVar = ((GetSideToPlayer() & 1) ^ 1);
            if (self->facingLeft == tempVar && GetDistanceToPlayerX() < 0x20) {
                self->step_s = 1;
            }
            break;
        case 1:
            if ((GetDistanceToPlayerY() > 0x50) ||
                (GetDistanceToPlayerX() > 0x50)) {
                self->step_s = 0;
            }
            break;
        }
        break;
    case BF_HIT:
        // Run hit animation and go back to idle.
        if (AnimateEntity(D_pspeu_09258A10, self) == 0) {
            SetStep(BF_IDLE);
        }
        break;
    case BF_DEAD:
        switch (self->step_s) {
        case BF_DEAD_INIT:
            self->drawFlags = ENTITY_DEFAULT;
            self->blendMode = BLEND_NO;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s += 1;
            /* fallthrough */
        case BF_DEAD_BECOME_SKULL:
            if (AnimateEntity(D_pspeu_09258A30, self) == 0) {
                self->ext.bitterfly.deathTimer = 0;
                self->step_s += 1;
            }
            break;
        case BF_DEAD_FALL:
            if (UnkCollisionFunc3(&D_pspeu_092589E8) & 1) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->ext.bitterfly.deathTimer = 0x18;
                self->step_s += 1;
            }
            break;
        case BF_DEAD_EXPLODE:
            if (!--self->ext.bitterfly.deathTimer) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 2;
                }
                PlaySfxPositional(SFX_RAPID_SCRAPE_3X);
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    // When not dead, bitterfly fades in and out according to player movement
    // If player is moving, we fade out by 0x10 units per frame. If player is
    // stopped, we fade in at the same rate. Opacity is capped at each end by
    // 0x00 and 0xA0.
    if (!(self->flags & FLAG_DEAD)) {
        other = &PLAYER;
        tempVar = self->opacity;
        if ((other->velocityX != 0) || (other->velocityY != 0)) {
            tempVar -= 0x10;
            if (tempVar < 0) {
                tempVar = 0;
            }
        } else {
            tempVar += 0x10;
            if (tempVar > 0xA0) {
                tempVar = 0xA0;
            }
        }
        self->opacity = tempVar;
    }
}
