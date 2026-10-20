// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

// It is tempting to split up this file into scarecrow and Schmoo (especially
// since by coincidence those are alphabetical, and we know PSP linker places
// files into the overlay in alphabetical order), but sadly charal string for
// scarecrow is in PSP data after the schmoo animations, so schmoo animations
// are before scarecrow and therefore schmoo shares a file with the scarecrow.

static bool ApproachTarget(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}
typedef struct {
    s16 animFrame;
    s16 zOffset;
    s16 xPos;
    s16 yPos;
    s16 minRot;
    s16 maxRot;
} limbParams;

static limbParams limbs[] = {
    {3, -1, 5, -11, ROT(-90), ROT(33.75)},        // Background leg
    {4, -1, -9, -6, ROT(-360) + 1, ROT(360) - 1}, // Background arm
    {5, 1, -9, -6, ROT(-360) + 1, ROT(360) - 1},  // foreground arm
    {6, 1, 5, -11, ROT(-90), ROT(22.5)}};         // foreground leg
static s16 sensors[] = {
    0,
    48,
    1,
    0,
};
static AnimateEntityFrame schmoo_normal[] = {
    {5, 8}, {5, 9}, {5, 10}, {5, 11}, POSE_LOOP(0)};
static AnimateEntityFrame schmoo_turn[] = {{8, 12}, {8, 13}, {8, 12}, POSE_END};

extern EInit g_EInitScarecrow;

// Scarecrow entity is just a stick with a torso on it.
// It has 4 EntityScarecrowLimb entities attached, which represent the
// flopping limbs that bounce with the scarecrow.
void EntityScarecrow(Entity* self) {
    Collider sp2C;
    Entity* other;
    s16 explode_angle;
    s32 yVar;
    s32 xVar;
    s32 var_s2;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step != 3)) {
        SetStep(3);
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitScarecrow);
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 2; // Scarecrow body on stick
        self->hitboxWidth = 12;
        self->hitboxHeight = 8;
        self->hitboxOffY = -6;
        if (!(Random() & 0xF)) {
            self->params |= 1;
        }
        if (self->params) {
            self->palette -= 1;
            self->animCurFrame = 7; // Wrapped scarecrow
            self->hitboxWidth = 9;
            self->hitboxHeight = 12;
            self->hitboxOffY = -6;
            return;
        }
        for (other = self + 1, i = 0; i < 4; i++, other++) {
            CreateEntityFromEntity(E_SCARECROW_LIMB, self, other);
            other->params = i;
            other->nextPart = other - 1;
            other->parent = self;
        }
        self->nextPart = self + 4;
    case 0x1:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-2.5);
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                ApproachTarget(&self->rotate, 0x100, 8);
            } else {
                ApproachTarget(&self->rotate, -0x100, 16);
            }
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi + 0x30; // offset to detect bottom of stick
            g_api.CheckCollision(xVar, yVar, &sp2C, 0);
            if (sp2C.effects & EFFECT_SOLID) {
                self->step_s = 0;
                PlaySfxPositional(SFX_STOMP_HARD_D);
                var_s2 = sp2C.unk18;
                xVar = self->posX.i.hi;
                yVar = self->posY.i.hi + 0x28;
                g_api.CheckCollision(xVar, yVar, &sp2C, 0);
                if (sp2C.effects & EFFECT_SOLID) {
                    self->facingLeft ^= 1;
                    return;
                }
                self->posY.i.hi += var_s2;
                var_s2 = (GetSideToPlayer() & 1) ^ 1;
                xVar = GetDistanceToPlayerX();
                if ((var_s2 != self->facingLeft) && (xVar > 0x40)) {
                    self->facingLeft ^= 1;
                    if (!(Random() & 3)) {
                        SetStep(2);
                    }
                }
            }
            break;
        }
        break;
    case 0x2:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.scarecrow.turnAroundTimer = (Random() & 0x1F) + 0x20;
            self->step_s += 1;
        }
        var_s2 = UnkCollisionFunc2(sensors);
        if (self->facingLeft) {
            self->velocityX += FIX(0.0625);
        } else {
            self->velocityX -= FIX(0.0625);
        }
        if (var_s2 == 0xFF) {
            self->ext.scarecrow.turnAroundTimer = 1;
        }
        if (!--self->ext.scarecrow.turnAroundTimer) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(1);
        }
        break;
    case 0x3:
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 3;
        }
        // Create explosion puffs, starting from the bottom of the stick
        // which is 0x30 long. Make a new one every 8 pixels.
        var_s2 = 0x30;
        explode_angle = self->rotate + 0x400;
        if (self->facingLeft) {
            explode_angle = 0x800 - explode_angle;
        }
        for (i = 0; i < 8; i++) {
            xVar = (var_s2 * rcos(explode_angle)) >> 0xC;
            yVar = (var_s2 * rsin(explode_angle)) >> 0xC;
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLODE_PUFF_OPAQUE, self, other);
                other->params = 3;
                other->rotate = self->rotate;
                other->posX.i.hi += xVar;
                other->posY.i.hi += yVar;
            }
            var_s2 -= 8;
        }
        PlaySfxPositional(SFX_FIRE_SHOT);
        DestroyEntity(self);
        return;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitScarecrowLimb;

void EntityScarecrowLimb(Entity* self) {
    s32 yOffset;
    s32 xOffset;
    s32 sine;
    s32 cosine;
    s16 angle;
    s16 angleChange;
    s32 yVar;
    s32 xVar;
    Entity* other;
    limbParams* limb;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(g_EInitScarecrowLimb);
        self->drawFlags |= ENTITY_ROTATE;
        other = (self - 1) - (self->params);
        limb = &limbs[self->params];
        self->animCurFrame = limb->animFrame;
        self->zPriority = other->zPriority + limb->zOffset;
        self->ext.scarecrow.prevXVel = other->velocityX;
        self->ext.scarecrow.prevYVel = other->velocityY;
        /* fallthrough */
    case 1:
        // get the scarecrow
        other = (self - 1) - (self->params);
        // get our parameters
        limb = &limbs[self->params];
        // copy the scarecrow's stuff into us
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->facingLeft = other->facingLeft;
        self->palette = other->palette;
        // Now get our position in world-space.
        // We need to take the X,Y position of ourself,
        // relative to the scarecrow's stick axis, and
        // rotate by the scarecrow rotation to find our position
        // in world space.
        angle = other->rotate;
        xVar = limb->xPos;
        yVar = limb->yPos;
        sine = rsin(angle);
        cosine = rcos(angle);
        // This is doing a 2D rotation matrix!
        xOffset = ((xVar * cosine) - (yVar * sine)) >> 0xC;
        yOffset = ((xVar * sine) + (yVar * cosine)) >> 0xC;
        if (self->facingLeft) {
            self->posX.i.hi -= xOffset;
        } else {
            self->posX.i.hi += xOffset;
        }
        self->posY.i.hi += yOffset;

        // Now that we have our position set, control our angle.
        // See how much velocity is changing to get acceleration.
        // Use those accelerations to control our flopping angle.
        xVar = other->velocityX - self->ext.scarecrow.prevXVel;
        if (self->facingLeft) {
            xVar = -xVar;
        }
        yVar = -(other->velocityY - self->ext.scarecrow.prevYVel);
        angleChange = xVar >> 8;
        angleChange += yVar >> 8;
        self->rotate += angleChange;
        ApproachTarget(&self->rotate, 0, 16);
        if (self->rotate > limb->maxRot) {
            self->rotate = limb->maxRot;
        }
        if (self->rotate < limb->minRot) {
            self->rotate = limb->minRot;
        }
        self->ext.scarecrow.prevXVel = other->velocityX;
        self->ext.scarecrow.prevYVel = other->velocityY;
        if (other->entityId != E_SCARECROW) {
            DestroyEntity(self);
        }
    }
}

extern EInit g_EInitSchmoo;

void EntitySchmoo(Entity* self) {
    Entity* other;
    s32 side;
    s32 xDist;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 1;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSchmoo);
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        /* fallthrough */
    case 1:
        AnimateEntity(schmoo_normal, self);
        MoveEntity();
        side = GetSideToPlayer();
        if (self->facingLeft) {
            self->velocityX += FIX(6.0 / 128);
            if (self->velocityX > FIX(3)) {
                self->velocityX = FIX(3);
            }
        } else {
            self->velocityX -= FIX(6.0 / 128);
            if (self->velocityX < FIX(-3)) {
                self->velocityX = FIX(-3);
            }
        }
        // If player is above the schmoo
        if (side & 2) {
            self->velocityY -= FIX(6.0 / 128);
            if (self->velocityY < FIX(-1.5)) {
                self->velocityY = FIX(-1.5);
            }
        } else {
            self->velocityY += FIX(6.0 / 128);
            if (self->velocityY > FIX(1.5)) {
                self->velocityY = FIX(1.5);
            }
        }
        side = (side & 1) ^ 1;
        xDist = GetDistanceToPlayerX();
        if ((side != self->facingLeft) && (xDist > 0x58)) {
            SetStep(2); // turn around
        }
        break;
    case 2:
        MoveEntity();
        switch (self->step_s) {
        case 0: // slow down until we are under 0.25
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (abs(self->velocityX) < FIX(0.25)) {
                self->step_s += 1;
            }
            break;
        case 1: // now we can turn around
            self->velocityX -= self->velocityX >> 8;
            self->velocityY -= self->velocityY >> 8;
            if (AnimateEntity(schmoo_turn, self) == 0) {
                SetStep(1);
            }
            if (!self->poseTimer && self->pose == 2) {
                self->facingLeft ^= 1;
            }
            break;
        }
        break;
    }
    self->rotate = -abs(self->velocityX >> 8);
}
