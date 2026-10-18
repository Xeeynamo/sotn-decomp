// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

extern EInit g_EInitSniperOfGoth;
extern EInit g_EInitSniperOfGothArrowSingle;
extern EInit g_EInitSniperOfGothArrowFlurry;

static AnimateEntityFrame anim_wing_flap_idle[] = {
    POSE(2, 1, 0),  POSE(4, 2, 0), POSE(2, 3, 0),  POSE(1, 4, 0),
    POSE(2, 5, 0),  POSE(1, 6, 0), POSE(1, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(4, 8, 0), POSE(2, 10, 0), POSE(6, 11, 0),
    POSE(2, 12, 0), POSE(1, 6, 0), POSE(1, 5, 0),  POSE(1, 4, 0),
    POSE(1, 3, 0),  POSE(1, 2, 0), POSE_LOOP(0),
};
// A short, slightly faster wing flap played after an attack
static AnimateEntityFrame anim_attack_recovery[] = {
    POSE(1, 2, 0),  POSE(1, 5, 0),  POSE(1, 8, 0), POSE(1, 11, 0),
    POSE(1, 5, 0),  POSE(1, 1, 0),  POSE(1, 2, 0), POSE(1, 3, 0),
    POSE(1, 4, 0),  POSE(1, 5, 0),  POSE(1, 6, 0), POSE(1, 7, 0),
    POSE(1, 8, 0),  POSE(1, 9, 0),  POSE(2, 8, 0), POSE(1, 10, 0),
    POSE(2, 11, 0), POSE(1, 12, 0), POSE(1, 6, 0), POSE(1, 5, 0),
    POSE(1, 4, 0),  POSE(1, 3, 0),  POSE(1, 2, 0), POSE_LOOP(0),
};
static AnimateEntityFrame anim_fire_bow[] = {
    POSE(33, 13, 0), POSE(17, 14, 0), POSE(1, 15, 0), POSE(1, 16, 0),
    POSE(1, 15, 0),  POSE(1, 16, 0),  POSE(2, 15, 0), POSE(2, 16, 0),
    POSE(3, 15, 0),  POSE(20, 16, 0), POSE_END,
};
static AnimateEntityFrame anim_transform[] = {
    POSE(2, 18, 0), POSE(4, 19, 0), POSE(1, 20, 0), POSE(1, 21, 0),
    POSE(2, 22, 0), POSE(1, 23, 0), POSE(1, 24, 0), POSE(1, 25, 0),
    POSE(1, 26, 0), POSE(1, 27, 0), POSE(1, 28, 0), POSE(1, 29, 0),
    POSE(1, 30, 0), POSE(1, 31, 0), POSE(1, 32, 0), POSE(4, 33, 0),
    POSE(1, 34, 0), POSE(1, 35, 0), POSE(1, 29, 0), POSE(1, 28, 0),
    POSE(1, 27, 0), POSE(1, 25, 0), POSE(1, 23, 0), POSE(1, 22, 0),
    POSE(1, 21, 0), POSE(1, 20, 0), POSE(1, 19, 0), POSE_LOOP(0),
};
// Horizontally oriented animation of only the wings which mirrors the flurry
// attack below
static AnimateEntityFrame anim_wings_only[] = {
    POSE(2, 36, 0), POSE(4, 37, 0), POSE(1, 38, 0), POSE(1, 39, 0),
    POSE(2, 40, 0), POSE(1, 41, 0), POSE(1, 42, 0), POSE(1, 43, 0),
    POSE(1, 44, 0), POSE(1, 45, 0), POSE(1, 46, 0), POSE(1, 47, 0),
    POSE(1, 48, 0), POSE(1, 49, 0), POSE(1, 50, 0), POSE(4, 51, 0),
    POSE(1, 52, 0), POSE(1, 53, 0), POSE(1, 47, 0), POSE(1, 46, 0),
    POSE(1, 45, 0), POSE(1, 43, 0), POSE(1, 41, 0), POSE(1, 40, 0),
    POSE(1, 39, 0), POSE(1, 38, 0), POSE(1, 37, 0), POSE_LOOP(0),
};
static AnimateEntityFrame anim_arrow_flurry_atk[] = {
    POSE(8, 54, 0),
    POSE(8, 55, 0),
    POSE_LOOP(0),
};
// The spell cast animation that appears at the centre of the circular
// arrow flurry
static AnimateEntityFrame anim_flurry_orb[] = {
    POSE(1, 59, 0), POSE(1, 63, 0), POSE(1, 64, 0), POSE(1, 60, 0),
    POSE(1, 63, 0), POSE(1, 64, 0), POSE(1, 61, 0), POSE(1, 63, 0),
    POSE(1, 64, 0), POSE(1, 62, 0), POSE(1, 63, 0), POSE(1, 64, 0),
    POSE_LOOP(0),
};

// Handles movement for the Sniper's cloth which dangles below it
// The cloth is made up of 11 segmeents which are connected and can sway with
// movement
static UpdateCloth(s32 sway) {
    Primitive* prim;
    s32 x;
    s32 y;
    // The positions where the cloth segments meet
    s32 jointX, jointY;
    s16 swayAngle;
    s32 segmentAngle;
    s32 i;
    s32 distanceSquared;

    swayAngle = g_CurrentEntity->ext.sniperOfGoth.clothSwayAngle -=
        ROT(33.75 / 4);
    prim = g_CurrentEntity->ext.sniperOfGoth.prim;
    prim = prim->next;
    if (sway) {
        x = g_CurrentEntity->posX.i.hi - 4;
        y = g_CurrentEntity->posY.i.hi + 4;
    } else {
        x = g_CurrentEntity->posX.i.hi - 6;
        y = g_CurrentEntity->posY.i.hi + 6;
    }
    jointX = x << 8;
    jointY = y << 8;

    for (i = 0; i < 11; i++) {
        prim->x0 = x;
        if (sway) {
            prim->x1 = x + 12;
        } else {
            prim->x1 = x + 14;
        }
        prim->y0 = prim->y1 = y;
        x = prim->x2 << 8;
        y = prim->y2 << 8;
        x += prim->p2;
        y += prim->p3;
        x -= jointX;
        y -= jointY;
        y += 0x180;
        if (g_CurrentEntity->flags & FLAG_DEAD) {
            y -= 0x400;
        }

        segmentAngle = ratan2(-x, y);
        distanceSquared = (x * x) + (y * y);
        if (distanceSquared > (0x800 * 0x800)) {
            x = -((rsin(segmentAngle) * 8) >> 4);
            y = (rcos(segmentAngle) * 8) >> 4;
        }

        y = ((ROT(360) - (abs(rcos(swayAngle)) / 4)) * y) >> 0xC;

        if (sway) {
            x += rcos(swayAngle) >> 6;
        }

        jointX += x;
        jointY += y;
        x = prim->x2 = jointX >> 8;
        y = prim->y2 = jointY >> 8;
        prim->p2 = jointX & 0xFF;
        prim->p3 = jointY & 0xFF;
        if (sway) {
            prim->x3 = x + 0xC;
        } else {
            prim->x3 = x + 0xE;
        }
        prim->y3 = y;
        swayAngle += ROT(45);
        prim = prim->next;
    }
}

typedef enum {
    INIT,
    UNUSED_1,
    UNUSED_2,
    SPAWN,
    FLY_IDLE,
    ATTACK_SINGLE,
    ATTACK_FLURRY,
    TURN_AROUND,
    ATTACK_RECOVERY,
    DEATH,
    FLURRY_WINGS = 17,
    FLURRY_ORB = 18,
    FLURRY_WINGS_AFTERIMAGE = 19,
    DEBUG = 255
} SniperOfGothSteps;

// Params
// 0 = main entity
// 1 = wings during flurry attack
// 2 = orb during flurry attack
void EntitySniperOfGoth(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 i;
    s32 posX;
    s32 posY;
    // When spawning in, we scale up X, scale down Y and become opaque.
    // This tracks when each of the three is done by incrementing the count.
    s32 doneCount;
    s32 primIndex;
    s16 angle;

    if (g_Timer & 1) {
        self->palette = g_EInitSniperOfGoth[3];
    } else {
        self->palette = g_EInitSniperOfGoth[3] + 3;
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        PlaySfxPositional(SFX_SNIPER_OF_GOTH_DEATH);
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitSniperOfGoth);
        self->flags |= FLAG_UNK_2000;
        if (!self->params) {
            // Spawn flurry wings (invisible to start)
            entity = self + 1;
            CreateEntityFromCurrentEntity(E_SNIPER_OF_GOTH, entity);
            entity->params = 1;
            // Wings are drawn below the main body
            entity->zPriority = self->zPriority - 1;

            // Spawn flurry orb (invisible to start)
            entity = self + 2;
            CreateEntityFromCurrentEntity(E_SNIPER_OF_GOTH, entity);
            entity->params = 2;
            entity->zPriority = self->zPriority + 2;

            primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.sniperOfGoth.prim = prim;
            prim->tpage = self->unk5A / 4;
            prim->clut = self->palette + 1;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x38;
            prim->v0 = prim->v1 = 0xC8;
            prim->v2 = prim->v3 = 0xFF;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;

            for (prim = prim->next, i = 0; i < 11; prim = prim->next, i++) {
                prim->tpage = self->unk5A / 4;
                prim->clut = self->palette + 2;
                prim->u0 = prim->u2 = 0xF0;
                prim->u1 = prim->u3 = 0xFF;
                prim->v0 = prim->v1 = (i * 8) + 0x28;
                prim->v2 = prim->v3 = (i * 8) + 0x30;
                prim->x0 = prim->x2 = prim->x1 = prim->x3 = self->posX.i.hi;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
                prim->priority = self->zPriority - 2;
                prim->drawMode = DRAW_HIDE;
            }
        } else {
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
            if (self->params & 0xFF00) {
                self->animCurFrame = self->params >> 8;
                self->params &= 0xFF;
            } else {
                self->flags &= ~FLAG_DESTROY_IF_OUT_OF_CAMERA;
            }

            // Steps FLURRY_WINGS (17) + FLURRY ORBS (18)
            SetStep(self->params + 16);
            break;
        }

        SetStep(SPAWN);
        break;
    case SPAWN:
        // Fire an arrow down and bring in the Sniper
        AnimateEntity(anim_transform, self);
        switch (self->step_s) {
        case 0:
            self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = 0x100;
            self->scaleY = 0x100;
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0xFF;
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = ROT(180);
            self->hitboxState = 0;
            self->step_s++;
            // fallthrough
        case 1:
            self->animCurFrame = 0;
            if (GetDistanceToPlayerX() < 0x40) {
                // Once the player is close enough fire the arrow down and begin
                // spawning
                PlaySfxPositional(SFX_ARROW_SHOT_C);
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                self->posY.i.hi = -0x20;
                self->velocityY = FIX(10.0);
                self->pose = 0;
                self->poseTimer = 0;
                self->animCurFrame = 0x3A;
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->pose = 0;
            self->poseTimer = 0;
            self->animCurFrame = 0x3A;
            self->velocityY -= FIX(0.25);
            if (self->velocityY < FIX(-3.0)) {
                self->velocityY = FIX(-1.0);
                self->scaleX = 8;
                self->scaleY = 0x180;
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            self->rotate = 0;
            doneCount = 0;
            self->scaleX += 12;
            if (self->scaleX > 0x100) {
                self->scaleX = 0x100;
                doneCount++;
            }

            self->scaleY -= 4;
            if (self->scaleY < 0x100) {
                self->scaleY = 0x100;
                doneCount++;
            }

            self->opacity -= 2;
            if (self->opacity < 0x80) {
                self->opacity = 0x80;
                doneCount++;
            }

            if (doneCount == 3) {
                self->drawFlags = ENTITY_DEFAULT;

                prim = self->ext.sniperOfGoth.prim;
                for (prim = prim->next, i = 0; i < 11; prim = prim->next, i++) {
                    prim->x0 = prim->x2 = prim->x1 = prim->x3 = self->posX.i.hi;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
                    prim->drawMode = DRAW_UNK02;
                }
                self->hitboxState = 3;
                self->flags &= ~FLAG_UNK_2000;
                SetStep(FLY_IDLE);
            }
            break;
        }

        // Blink every other frame while spawning in
        if (g_Timer & 1) {
            self->animCurFrame = 0;
        }

        break;
    case FLY_IDLE:
        if (!self->step_s) {
            self->ext.sniperOfGoth.idleTimer = 64;
            self->step_s++;
        }
        MoveEntity();
        AnimateEntity(anim_wing_flap_idle, self);
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }

        entity = &PLAYER;
        posX = entity->posX.i.hi;
        if (self->facingLeft) {
            posX -= 0x50;
        } else {
            posX += 0x50;
        }
        posY = (entity->posY.i.hi - 0x50);
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->velocityX = (rcos(angle) * FIX(1.25)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(1.25)) >> 0xC;
        if (abs(posX) < 8 && abs(posY) < 8) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.sniperOfGoth.idleTimer -= 2;
        } else {
            self->ext.sniperOfGoth.idleTimer -= 1;
        }

        if (GetDistanceToPlayerX() < 0x50) {
            self->ext.sniperOfGoth.timer--;
        } else {
            self->ext.sniperOfGoth.timer = 48;
        }

        // If the player spent enough time close enough,
        // flip around to the other direction
        if (!self->ext.sniperOfGoth.timer) {
            self->step_s = 0;
            self->step = TURN_AROUND;
        }

        if (self->ext.sniperOfGoth.idleTimer <= 0) {
            // Fire 3 single arrow attacks, then perform the circular flurry
            self->ext.sniperOfGoth.attackCount += 1;
            self->ext.sniperOfGoth.attackCount &= 3;
            SetStep(ATTACK_SINGLE);

            if (!self->ext.sniperOfGoth.attackCount) {
                SetStep(ATTACK_FLURRY);
            }
        }
        break;
    case TURN_AROUND:
        AnimateEntity(anim_wing_flap_idle, self);
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        MoveEntity();

        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(3.0);
            } else {
                self->velocityX = FIX(-3.0);
            }
            self->velocityY = 0;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = 0;
            self->step_s++;
            // fallthrough
        case 1:
            entity = &PLAYER;
            if (self->facingLeft) {
                posX = (entity->posX.i.hi + 0x40) - self->posX.i.hi;
            } else {
                posX = self->posX.i.hi - (entity->posX.i.hi - 0x40);
            }

            if (posX < 0x20) {
                self->step_s++;
            }
            break;
        case 2:
            self->rotate -= ROT(5.625);
            if (self->rotate == ROT(-45)) {
                self->facingLeft ^= 1;
                self->step_s++;
            }
            break;
        case 3:
            self->rotate += ROT(5.625);
            if (!self->rotate) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s = 0;
                self->step = ATTACK_RECOVERY;
            }
            break;
        }
        break;
    case ATTACK_RECOVERY:
        switch (self->step_s) {
        case 0:
            self->ext.sniperOfGoth.flapCount = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_attack_recovery, self)) {
                self->ext.sniperOfGoth.flapCount++;
            }

            if (self->ext.sniperOfGoth.flapCount == 2) {
                SetStep(FLY_IDLE);
            }
            break;
        }
        break;
    case ATTACK_SINGLE:
        if (!AnimateEntity(anim_fire_bow, self)) {
            SetStep(ATTACK_RECOVERY);
        }

        if (self->pose == 1 && !self->poseTimer) {
            PlaySfxPositional(SFX_BONE_CREAK);
        }

        if (self->pose == 2 && !self->poseTimer) {
            PlaySfxPositional(SFX_ARROW_SHOT_B);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_SNIPER_OF_GOTH_ARROW, self, entity);
                entity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x28;
                } else {
                    entity->posX.i.hi -= 0x28;
                }
                entity->posY.i.hi += 0x10;
            }
        }
        break;
    case ATTACK_FLURRY:
        AnimateEntity(anim_arrow_flurry_atk, self);
        switch (self->step_s) {
        case 0:
            entity = self + 1;
            entity->ext.sniperOfGoth.flurryActive = true;
            prim = self->ext.sniperOfGoth.prim;
            prim->x0 = prim->x2 = prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_UNK02;
            self->ext.sniperOfGoth.timer = 40;
            PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
            self->step_s++;
            // fallthrough
        case 1:
            prim = self->ext.sniperOfGoth.prim;
            prim->x0 = prim->x2 -= 1;
            prim->x1 = prim->x3 += 1;
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;

            if (!--self->ext.sniperOfGoth.timer) {
                SetSubStep(2);
            }
            break;
        case 2:
            entity = self + 2;
            entity->ext.sniperOfGoth.flurryActive = true;
            self->ext.sniperOfGoth.timer = 32;
            self->step_s++;
            break;
        case 3:
            self->ext.sniperOfGoth.flurryArrowCount = 32;
            if (!--self->ext.sniperOfGoth.timer) {
                self->step_s++;
            }
            break;
        case 4:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_SNIPER_OF_GOTH_ARROW, self, entity);
                entity->params = self->ext.sniperOfGoth.flurryArrowCount;
                entity->facingLeft = self->facingLeft;
            }

            if (!(self->ext.sniperOfGoth.flurryArrowCount & 3)) {
                PlaySfxPositional(SFX_ARROW_SHOT_C);
            }

            if (!--self->ext.sniperOfGoth.flurryArrowCount) {
                self->ext.sniperOfGoth.timer = 32;
                self->step_s++;
            }
            break;
        case 5:
            prim = self->ext.sniperOfGoth.prim;
            prim->x0 = prim->x2 += 1;
            prim->x1 = prim->x3 -= 1;
            prim->y0 = prim->y1 += 1;
            prim->y2 = prim->y3 -= 1;

            if (!--self->ext.sniperOfGoth.timer) {
                prim = self->ext.sniperOfGoth.prim;
                prim->drawMode = DRAW_HIDE;

                entity = self + 1;
                entity->ext.sniperOfGoth.flurryActive = false;

                entity = self + 2;
                entity->ext.sniperOfGoth.flurryActive = false;
                SetStep(ATTACK_RECOVERY);
            }
            break;
        }
        break;
    case DEATH:
        AnimateEntity(anim_transform, self);
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = FIX(1.5);
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            prim = self->ext.sniperOfGoth.prim;
            prim->drawMode = DRAW_HIDE;
            PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.0625);
            self->rotate += ROT(2.8125);
            if (!(g_Timer & 0x1F)) {
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
            }
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = EXPLOSION_FIREBALL;
                    entity->zPriority = self->zPriority + 1;
                    entity->posX.i.hi += (Random() & 0x3F) - 0x1F;
                    entity->posY.i.hi += (Random() & 0x3F) - 0x1F;
                }
            }
            break;
        }
        break;
    // This case is only used for the sub-entity (self + 1)
    case FLURRY_WINGS:
        if (!self->ext.sniperOfGoth.flurryActive) {
            // If the flurry attack is inactive, this entity is invisible
            self->pose = 0;
            self->poseTimer = 0;
            self->animCurFrame = 0;
            break;
        }

        AnimateEntity(anim_wings_only, self);
        // Main body entity
        entity = self - 1;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;

        // Spawn the wings afterimage effect
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_SNIPER_OF_GOTH, self, entity);
            entity->facingLeft = self->facingLeft;
            entity->zPriority = self->zPriority - 1;
            entity->params = self->animCurFrame << 8;
            entity->params += 3;
        }

        entity = self - 1;
        if (entity->entityId != E_SNIPER_OF_GOTH || entity->flags & FLAG_DEAD) {
            DestroyEntity(self);
            return;
        }

        return;
    // This case is only used for the sub-entity (self + 2)
    case FLURRY_ORB:
        if (!self->ext.sniperOfGoth.flurryActive) {
            // If the flurry attack is inactive, this entity is invisible
            self->pose = 0;
            self->poseTimer = 0;
            self->animCurFrame = 0;
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0;
            break;
        }

        // The orb becomes visible scales up to size
        AnimateEntity(anim_flurry_orb, self);
        self->scaleY += 32;
        if (self->scaleY > 0x100) {
            self->drawFlags = ENTITY_DEFAULT;
        }
        self->scaleX = self->scaleY;

        // Main body entity
        entity = self - 2;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->entityId != E_SNIPER_OF_GOTH || entity->flags & FLAG_DEAD) {
            DestroyEntity(self);
            return;
        }

        break;
    // This case is only used for the sub-entity (self + 1)
    case FLURRY_WINGS_AFTERIMAGE:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x60;
            self->step_s++;
        }

        // While the flurry attack is in progress, wings get a flared out
        // afterimage effect
        self->opacity -= 8;
        if (g_Timer & 1) {
            self->animSet = 0;
        } else {
            self->animSet = g_EInitSniperOfGoth[0];
        }

        if (!self->opacity) {
            DestroyEntity(self);
        }
        return;
    case DEBUG:
#include "../pad2_anim_debug.h"
    }

    // Hitbox per pose: flying (1-12)
    if (self->animCurFrame < 13) {
        self->hitboxOffX = -6;
        self->hitboxOffY = 9;
        self->hitboxWidth = 0x14;
        self->hitboxHeight = 0x17;
    }
    // drawing the bow (13-16)
    else if (self->animCurFrame < 17) {
        self->hitboxOffX = -0xB;
        self->hitboxOffY = -2;
        self->hitboxWidth = 0x14;
        self->hitboxHeight = 0x17;
    }
    // flurry/spawn (17+)
    else {
        self->hitboxOffX = 0;
        self->hitboxOffY = -5;
        self->hitboxWidth = 0xE;
        self->hitboxHeight = 0x16;
    }

    if (!self->params) {
        prim = self->ext.sniperOfGoth.prim;
        prim->clut = self->palette + 1;

        prim = prim->next;
        while (prim != NULL) {
            prim->clut = self->palette + 2;
            prim = prim->next;
        }

        // When doing the flurry attack, Sniper is stationary so dull the sway
        // effects on the cloth.
        if (self->step == SPAWN || self->step == ATTACK_FLURRY) {
            UpdateCloth(false);
        } else {
            UpdateCloth(true);
        }
    }
}

// Params
// 0 = Single arrow shot
// !0 = Flurry arrow attack
void EntitySniperOfGothArrow(Entity* self) {
    Entity* entity;
    s16 angle;
    s32 hitFlags;

    if (g_Timer & 1) {
        self->palette = g_EInitSniperOfGoth[3];
    } else {
        self->palette = g_EInitSniperOfGoth[3] + 3;
    }

    switch (self->step) {
    case 0:
        if (!self->params) {
            InitializeEntity(g_EInitSniperOfGothArrowSingle);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
            self->velocityY = FIX(4.0);
            self->hitboxOffX = -4;
            self->hitboxOffY = 5;
        } else {
            InitializeEntity(g_EInitSniperOfGothArrowFlurry);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            angle = self->params << 7;
            if (self->facingLeft) {
                self->facingLeft = false;
                angle = -angle;
            }
            // Flurry arrows fan out in a circle around the Sniper
            self->rotate = angle;
            self->drawFlags = ENTITY_ROTATE;
            self->posX.i.hi += (rsin(angle) * 0x10) >> 0xC;
            self->posY.i.hi -= (rcos(angle) * 0x10) >> 0xC;
            self->velocityX = rsin(angle) * 0x70;
            self->velocityY = rcos(angle) * -0x70;
            self->hitboxOffX = (rsin(angle) * 0xA) >> 0xC;
            self->hitboxOffY = (rcos(angle) * -0xA) >> 0xC;
        }
        // fallthrough
    case 1:
        MoveEntity();
        hitFlags = self->hitFlags;
        if (hitFlags & 0x80) {
            // If the arrow hits the player, store the offset and stick to the
            // player for a bit before despawning
            entity = &PLAYER;
            self->ext.sniperOfGothArrow.hitPlayerX =
                entity->posX.i.hi - self->posX.i.hi;
            self->ext.sniperOfGothArrow.hitPlayerY =
                entity->posY.i.hi - self->posY.i.hi;
            self->ext.sniperOfGoth.timer = 32;
            self->hitboxState = 0;
            self->step++;
            break;
        }

        if (hitFlags != 0 || self->flags & FLAG_DEAD) {
            // Arrow was hit by something other than the player
            self->hitboxState = 0;
            self->step_s = 0;
            self->step = 3;
        }
        break;
    case 2:
        entity = &PLAYER;
        self->posX.i.hi =
            entity->posX.i.hi - self->ext.sniperOfGothArrow.hitPlayerX;
        self->posY.i.hi =
            entity->posY.i.hi - self->ext.sniperOfGothArrow.hitPlayerY;
        if (!--self->ext.sniperOfGoth.timer) {
            DestroyEntity(self);
        }
        break;
    case 3:
        // Otherwise, if the arrow is deflected, bounce back and fall before
        // despawning
        if (!self->step_s) {
            self->drawFlags |= ENTITY_ROTATE;
            self->velocityX = -self->velocityX / 2;
            self->velocityY = -self->velocityY / 2;
            self->step_s++;
        }
        MoveEntity();

        self->velocityY += FIX(0.125);
        self->rotate += ROT(5.625);
        if (g_Timer & 1) {
            self->animCurFrame = 0;
            break;
        }

        if (self->params) {
            self->animCurFrame = 0x3A;
            break;
        }

        self->animCurFrame = 0x11;
        break;
    }
}
