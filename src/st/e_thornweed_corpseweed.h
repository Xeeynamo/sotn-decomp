// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

extern EInit g_EInitThornweed;
extern EInit g_EInitCorpseweed;
extern EInit g_EInitCorpseweedProjectile;

static s16 PhysicsSensors[] = {
    0, 1, 0, 4, 2, -4, -4, 0,
};

static AnimateEntityFrame anim_ThornweedWakeup[] = {
    {2, 1}, {6, 2}, {6, 3}, {6, 4}, POSE_END};

static AnimateEntityFrame anim_ThornweedIdle[] = {
    {6, 5}, {6, 6}, {6, 7}, {6, 8}, POSE_LOOP(0)};

static AnimateEntityFrame anim_CorpseweedWakeup[] = {
    {2, 9}, {6, 10}, {6, 11}, {6, 12}, POSE_END};

static AnimateEntityFrame anim_CorpseweedIdle[] = {
    {6, 13}, {6, 14}, {6, 15}, {6, 16}, POSE_LOOP(0)};

static AnimateEntityFrame anim_CorpseweedAttackCharge[] = {
    {2, 19}, {2, 20}, POSE_LOOP(0)};

static AnimateEntityFrame anim_CorpseweedProjectileAirborne[] = {
    {2, 22}, {2, 23}, POSE_LOOP(0)};

static AnimateEntityFrame anim_CorpseweedProjectileDeath[] = {
    {4, 24}, {3, 25}, {2, 26}, {2, 27}, POSE_END};

static AnimateEntityFrame* anim_All[] = {
    anim_ThornweedWakeup, anim_CorpseweedWakeup, // WakeUp
    anim_ThornweedIdle, anim_CorpseweedIdle,     // Idle
};

#define XYWH(x, y, w, h) x, y, w, h

static s8 HitboxData[] = {
    XYWH(0, 0, 0, 0),  XYWH(1, 0, 3, 3),     XYWH(1, -2, 3, 4),
    XYWH(0, -6, 7, 9), XYWH(1, -5, 9, 7),    XYWH(-63, -63, 0, 0),
    XYWH(2, 9, 5, 8),  XYWH(0, 0, 4, 4),     XYWH(3, -11, 4, 12),
    XYWH(4, -3, 5, 5), XYWH(15, -11, 23, 21)};

static u8 HitboxIndices[] = {0, 1, 2, 2, 3, 4, 4, 4, 4, 1, 2, 2, 3, 4, 4,
                             4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 9, 9, 5, 10};

// params: 0 = Thornweed, 1 = Corpseweed
void EntityThornweed(Entity* self) {
    const int EntityFormCount = 2; // Thornweed, Corpseweed
    const int AnimFrame_ThornweedInit = 1;
    const int AnimFrame_CorpseweedInit = 9;
    const int WakeDistance = 0x50;
    const int CorpseweedSpawnDelay = 0x40;
    const int DeathExplosionDelay = 0x80;

    enum Step {
        INIT = 0,
        DROP_TO_GROUND = 1,
        WAIT_TO_WAKE = 2,
        WAKE_UP = 3,
        IDLE = 4,
        CORPSEWEED_DEATH = 6,
    };

    Entity* entity;
    AnimateEntityFrame* animFrames;
    s8* hitboxData;
    u32 hitboxIndex;

    // Check for death
    if ((self->flags & FLAG_DEAD) && (self->step < 6)) {
        if ((self->params) && (self->ext.corpseweed.isCorpseweedSpawned)) {
            SetStep(CORPSEWEED_DEATH);
        } else {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posY.i.hi -= 4;
                entity->params = 0;
            }
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
            DestroyEntity(self);
            return;
        }
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitThornweed);
        if (self->params) {
            self->animCurFrame = AnimFrame_CorpseweedInit;
        } else {
            self->animCurFrame = AnimFrame_ThornweedInit;
        }
        break;

    case DROP_TO_GROUND:
        if (UnkCollisionFunc3(&PhysicsSensors) & 1) {
            SetStep(WAIT_TO_WAKE);
        }
        break;

    case WAIT_TO_WAKE:
        if (GetDistanceToPlayerX() < WakeDistance) {
            SetStep(WAKE_UP);
        }
        break;

    case WAKE_UP:
        animFrames = anim_All[self->params];
        if (AnimateEntity(animFrames, self) == 0) {
            self->ext.corpseweed.timer = CorpseweedSpawnDelay;
            SetStep(IDLE);
        }
        break;

    case IDLE:
        // Check for any necessary idle init
        if (!self->step_s) {
            if (self->params) {
                if (!--self->ext.corpseweed.timer) {
                    self->step_s++;

                    // Spawn the Corpseweed stalk/head
                    entity = self + 1;
                    CreateEntityFromEntity(E_CORPSEWEED, self, entity);
                    entity->facingLeft = (GetSideToPlayer() & 1);
                    self->enemyId = 0x9E;
                    self->ext.corpseweed.isCorpseweedSpawned = true;
                }
            } else {
                self->step_s++;
            }
        }

        // Animate
        animFrames = anim_All[self->params + EntityFormCount];
        AnimateEntity(animFrames, self);
        break;

    case CORPSEWEED_DEATH:
        if (!self->step_s) {
            entity = self + 1;
            entity->flags |= FLAG_DEAD;
            self->hitboxState = 0;
            self->opacity = DeathExplosionDelay;
            self->drawFlags |= ENTITY_OPACITY;
            self->step_s++;
        }
        if (!--self->opacity) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posY.i.hi -= 0xC;
                entity->params = 2;
            }
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
            DestroyEntity(self);
            return;
        }
        break;
    }

    // Update the hitbox based on the current animation frame
    hitboxData = HitboxData;
    hitboxIndex = HitboxIndices[self->animCurFrame];
    hitboxData += hitboxIndex * 4; // 4 entries per index
    self->hitboxOffX = *hitboxData++;
    self->hitboxOffY = *hitboxData++;
    self->hitboxWidth = *hitboxData++;
    self->hitboxHeight = *hitboxData++;
}

void EntityCorpseweed(Entity* self) {
    // Sprites
    const int SpriteLeavesLeft = 0;
    const int SpriteLeavesRight = 0x18;
    const int SpriteLeavesTop = 0x28;
    const int SpriteLeavesBottom = 0x50;
    const int SpriteStalkLeft = 0x40;
    const int SpriteStalkRight = 0x18;
    const int SpriteStalkTop = 0;
    const int SpriteStalkBottom = 0x70;
    // Anim Frames
    const int AnimFrameInit = 0;
    const int AnimFrameIdle = 0x13;
    const int AnimFrameAttack = 0x15;
    // Growth Dimensions
    const int LeavesGrowMaxWidth = 0x18;
    const int LeavesGrowMaxHeight = 0x28;
    const int StalkGrowMaxWidthFacing = 0xA;
    const int StalkGrowMaxWidthNonFacing = 0x10;
    const int StalkGrowNonFacingStartHeight = 0x59;
    const int StalkGrowMaxHeight = 0x70;
    const int StalkGrowMaxHalfWidth = 0x14;
    // Attack
    const int DelayBeforeFirstAttack = 0x80;
    const int DelayBetweenAttackChecks = 0x20;
    const int AttackChargeDuration = 0x20;
    const int ProjectileSpawnOffsetX = 4;
    const int ProjectileSpawnOffsetY = 0xD;
    const int PostAttackResetDelay = 0x10;
    // Bobbing
    const int BobbingTimer = 0x20;
    const int BobbingOriginOffsX_Leaves = 0xC;
    const int BobbingOriginOffsY_Leaves = 0x28;
    const int BobbingSpeedX_Leaves = 0x100;
    const int BobbingSpeedY_Leaves = 0x200;
    const int BobbingOriginOffsX_Stalk = 0x14;
    const int BobbingOriginOffsY_Stalk = 0x70;
    const int BobbingSpeedX_Stalk = 0x38;
    const int BobbingSpeedY_Stalk = 0x64;
    // Death
    const int DeathHeadFallAccel = FIX(0.09375);
    const int DeathHeadRotateSpeed = 0x20;

    enum Step {
        INIT = 0,
        GROW_LEAVES = 1,
        GROW_STEM = 2,
        GROW_TO_IDLE = 3,
        IDLE = 4,
        ATTACK = 5,
        DEATH = 6,
    };

    enum GrowLeaves_Substep {
        GROW_LEAVES_H = 0,
        GROW_LEAVES_V = 1,
        GROW_LEAVES_DONE = 2,
    };

    enum GrowStem_Substep {
        GROW_STEM_H1 = 0,
        GROW_STEM_UNEVEN_V = 1,
        GROW_STEM_FINISH_V = 2,
        GROW_STEM_H2 = 3,
    };

    enum Attack_Substep {
        ATTACK_INIT = 0,
        ATTACK_DELAY = 1,
        ATTACK_PROJECTILE = 2,
        ATTACK_RESET_DELAY = 3,
    };

    enum Death_Substep {
        DEATH_INIT = 0,
        DEATH_DROP_HEAD = 1,
        DEATH_SHRINK_AND_FADE = 2,
    };

    Collider collider;
    Primitive* prim;
    s32 y;
    Entity* entity;
    s32 primIdx;
    s32 pos;
    s32 x;
    s32 doneCount;
    s16 t;

    if ((self->flags & FLAG_DEAD) && (self->step < DEATH)) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitCorpseweed);
        self->animCurFrame = AnimFrameInit;
        self->hitboxOffX = 2;
        self->hitboxOffY = 9;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0;
        self->hitboxState = 0;
        self->ext.corpseweed.bobbingAngle = 8;

        // Setup primitives
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIdx == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIdx;
        prim = &g_PrimBuf[primIdx];
        self->ext.corpseweed.prim = prim;

        // Leaves primitive
        prim->tpage = CORPSEWEED_TPAGE;
        // Palettes are different in CHI
        prim->clut = CORPSEWEED_PAL;
        prim->u0 = prim->u2 = SpriteLeavesLeft;
        prim->u1 = prim->u3 = SpriteLeavesRight;
        prim->v0 = prim->v1 = SpriteLeavesTop;
        prim->v2 = prim->v3 = SpriteLeavesBottom;
        prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
        prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority - 1;
        prim->drawMode = ENTITY_SCALEY;

        // Stalk primitive
        prim = prim->next;
        prim->tpage = CORPSEWEED_TPAGE;
        prim->clut = CORPSEWEED_PAL;
        prim->u0 = prim->u2 = SpriteStalkLeft;
        prim->u1 = prim->u3 = SpriteStalkRight;
        prim->v0 = prim->v1 = SpriteStalkTop;
        prim->v2 = prim->v3 = SpriteStalkBottom;
        prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
        prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
        if (self->facingLeft) {
            prim->x2 = self->posX.i.hi - BobbingOriginOffsX_Stalk;
            prim->x3 = self->posX.i.hi + BobbingOriginOffsX_Stalk;
        } else {
            prim->x2 = self->posX.i.hi + BobbingOriginOffsX_Stalk;
            prim->x3 = self->posX.i.hi - BobbingOriginOffsX_Stalk;
        }
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority - 2;
        prim->drawMode = ENTITY_SCALEY;
        prim = prim->next;
        // Fallthrough
    case GROW_LEAVES:
        prim = self->ext.corpseweed.prim;
        switch (self->step_s) {
        case GROW_LEAVES_H:
            // Expand leaves sprite horizontally
            prim->x0 = --prim->x2;
            prim->x1 = ++prim->x3;
            x = prim->x1 - prim->x0;
            if (x >= LeavesGrowMaxWidth) {
                self->step_s++;
            }
            // fallthrough
        case GROW_LEAVES_V:
            // Extend leaves sprite up
            prim->y0 = --prim->y1;
            y = prim->y2 - prim->y0;
            if (y >= LeavesGrowMaxHeight) {
                self->step_s++;
            }
            break;

        case GROW_LEAVES_DONE:
            self->ext.corpseweed.leavesDoneGrowing = true;
            SetStep(GROW_STEM);
            break;
        }
        break;

    case GROW_STEM:
        prim = self->ext.corpseweed.prim;
        prim = prim->next;
        switch (self->step_s) {
        case GROW_STEM_H1:
            // Extend stalk sprite up
            prim->y1 = prim->y0 -= 2;
            // Expand stalk sprite horizontally
            x = prim->x0 - self->posX.i.hi;
            x = abs(x);
            // Only expand in facing direction so far
            if (x < StalkGrowMaxWidthFacing) {
                if (self->facingLeft) {
                    prim->x0--;
                } else {
                    prim->x0++;
                }
            }
            // Expand opposite of facing direction always
            if (self->facingLeft) {
                prim->x1++;
            } else {
                prim->x1--;
            }
            // Once stalk sprite has expanded enough opposite
            // of facing direction
            x = self->posX.i.hi - prim->x1;
            x = abs(x);
            if (x >= StalkGrowMaxWidthNonFacing) {
                self->step_s++;
            }
            break;

        case GROW_STEM_UNEVEN_V:
            // Extend the facing edge of stalk sprite up
            if (self->facingLeft) {
                prim->y0--;
                y = prim->y2 - prim->y0;
                // Then start extending the non-facing edge of stalk sprite up
                if (y < StalkGrowNonFacingStartHeight) {
                    prim->y1--;
                }
            } else {
                prim->y1--;
                y = prim->y2 - prim->y1;
                // Then start extending the non-facing edge of stalk sprite up
                if (y < StalkGrowNonFacingStartHeight) {
                    prim->y0--;
                }
            }
            if (y >= StalkGrowMaxHeight) {
                self->step_s++;
            }
            break;

        case GROW_STEM_FINISH_V:
            // Extend the non-facing edge of stalk sprite up
            if (self->facingLeft) {
                prim->y1--;
                y = prim->y3 - prim->y1;
            } else {
                prim->y0--;
                y = prim->y3 - prim->y0;
            }
            if (y >= StalkGrowMaxHeight) {
                self->step_s++;
            }
            break;

        case GROW_STEM_H2:
            doneCount = 0;

            // Facing edge
            x = prim->x0 - self->posX.i.hi;
            x = abs(x);
            if (x < StalkGrowMaxHalfWidth) {
                if (self->facingLeft) {
                    prim->x0--;
                } else {
                    prim->x0++;
                }
            } else {
                doneCount += 1;
            }

            // Non-facing edge
            x = self->posX.i.hi - prim->x1;
            x = abs(x);
            if (x < StalkGrowMaxHalfWidth) {
                if (self->facingLeft) {
                    prim->x1++;
                } else {
                    prim->x1--;
                }
            } else {
                doneCount += 1;
            }

            // Check if both edges are done
            if (doneCount == 2) {
                self->ext.corpseweed.stalkDoneGrowing = true;
                self->hitboxState = 3;
                SetStep(GROW_TO_IDLE);
            }
            break;
        }
        break;

    case GROW_TO_IDLE:
        self->animCurFrame = AnimFrameIdle;
        if (self->scaleX < 0x100) {
            self->scaleX = self->scaleY += 8;
        } else {
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(IDLE);
        }
        break;

    case IDLE:
        if (!self->step_s) {
            self->ext.corpseweed.timer = DelayBeforeFirstAttack;
            self->step_s += 1;
        }
        self->animCurFrame = AnimFrameIdle;
        if (!--self->ext.corpseweed.timer) {
            if ((GetSideToPlayer() & 1) == self->facingLeft) {
                SetStep(ATTACK);
            } else {
                self->ext.corpseweed.timer = DelayBetweenAttackChecks;
            }
        }
        if (self->hitFlags & 2) {
            self->ext.corpseweed.bobbingTimer = BobbingTimer;
        }
        break;

    case ATTACK:
        switch (self->step_s) {
        case ATTACK_INIT:
            self->ext.corpseweed.timer = AttackChargeDuration;
            self->step_s += 1;
            // fallthrough
        case ATTACK_DELAY:
            AnimateEntity(anim_CorpseweedAttackCharge, self);
            if (!--self->ext.corpseweed.timer) {
                SetSubStep(ATTACK_PROJECTILE);
            }
            break;

        case ATTACK_PROJECTILE:
            self->animCurFrame = AnimFrameAttack;
            // Spawn projectile entity
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
#ifndef CORPSEWEED_NO_ATTACK_SFX
                PlaySfxPositional(SFX_CORPSEWEED_ATTACK);
#endif

                CreateEntityFromEntity(E_CORPSEWEED_PROJECTILE, self, entity);
                entity->zPriority = self->zPriority + 1;
                entity->facingLeft = self->facingLeft;
                entity->posY.i.hi += ProjectileSpawnOffsetY;
                if (self->facingLeft) {
                    entity->posX.i.hi -= ProjectileSpawnOffsetX;
                } else {
                    entity->posX.i.hi += ProjectileSpawnOffsetX;
                }
            }
            self->ext.corpseweed.timer = PostAttackResetDelay;
            self->step_s++;
            // fallthrough
        case ATTACK_RESET_DELAY:
            if (!--self->ext.corpseweed.timer) {
                SetStep(IDLE);
            }
            break;
        }
        break;

    case DEATH:
        switch (self->step_s) {
        case DEATH_INIT:
            self->ext.corpseweed.leavesDoneGrowing = false;
            self->ext.corpseweed.stalkDoneGrowing = false;
            self->hitboxState = 0;
            self->drawFlags = ENTITY_ROTATE;
            // Need a no-op self access here for PSP match
            self->step_s;
            self->step_s++;
            // fallthrough
        case DEATH_DROP_HEAD:
            MoveEntity();
            self->velocityY += DeathHeadFallAccel;
            self->rotate += DeathHeadRotateSpeed;

            // Wait until head hits the ground
            x = self->posX.i.hi;
            y = self->posY.i.hi + 8;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
                self->posY.i.hi += collider.unk18;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

                // Spawn multiple flames
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 1;
                }

                // Hide head
                self->animCurFrame = 0;

                // "Parent" Thornweed
                entity = self - 1;
                entity->flags |= FLAG_DEAD;

                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                self->step_s++;
            }
            break;

        case DEATH_SHRINK_AND_FADE:
            self->ext.corpseweed.timer++;
            prim = self->ext.corpseweed.prim;

            // Leaves: Half speed
            if (self->ext.corpseweed.timer & 1) {
                prim->drawMode |= DRAW_COLORS;
                // Contract horizontally
                if (prim->x1 > prim->x0) {
                    prim->x0++;
                    prim->x1--;
                }
                // Collapse down
                if (prim->y0 < prim->y2) {
                    prim->y0++;
                }
                if (prim->y1 < prim->y3) {
                    prim->y1++;
                }
                PrimDecreaseBrightness(prim, 3U);
            }

            // Stalk
            prim = prim->next;
            prim->drawMode |= DRAW_COLORS;
            if (self->facingLeft) {
                // Contract horizontally
                if (prim->x1 > prim->x0) {
                    prim->x0++;
                    prim->x1--;
                }
            } else {
                // Contract horizontally
                if (prim->x0 > prim->x1) {
                    prim->x1++;
                    prim->x0--;
                }
            }
            // Collapse down
            if (prim->y0 < prim->y2) {
                prim->y0++;
            }
            if (prim->y1 < prim->y3) {
                prim->y1++;
            }
            // Slide Vs up, giving effect of sinking into floor
            if (prim->v2 > 0) {
                prim->v2 -= 1;
            }
            if (prim->v3 > 0) {
                prim->v3 -= 1;
            }
            PrimDecreaseBrightness(prim, 1U);
            break;
        }
    }

    // Update bobbing back and forth state
    if (self->ext.corpseweed.bobbingTimer) {
        self->ext.corpseweed.bobbingTimer--;
        if (self->ext.corpseweed.bobbingTimer & 0x10) {
            // Go right
            self->ext.corpseweed.bobbingAngle++;
        } else {
            // Go left
            self->ext.corpseweed.bobbingAngle--;
        }
    } else {
        // No bobbing
        self->ext.corpseweed.bobbingAngle = 8;
    }

    // Update leaves for bobbing back and forth
    if (self->ext.corpseweed.leavesDoneGrowing) {
        prim = self->ext.corpseweed.prim;

        // X
        t = self->ext.corpseweed.bobbingLeavesXT += BobbingSpeedX_Leaves;
        x = (rcos(t) * 2) >> 0xC;
        pos = (prim->x2 + prim->x3) / 2;
        // 0xC represents BobbingOriginOffsX_Leaves
        prim->x0 = pos - 0xC + x;
        prim->x1 = pos + 0xC + x;

        // Y
        t = self->ext.corpseweed.bobbingLeavesYT += BobbingSpeedY_Leaves;
        y = (rsin(t) * 4) >> 0xC;
        pos = prim->y2;
        // 0x28 represents BobbingOriginOffsY_Leaves
        prim->y0 = pos - 0x28 + y;
        prim->y1 = pos - 0x28 - y;
    }

    // Update stalk for bobbing back and forth
    if (self->ext.corpseweed.stalkDoneGrowing) {
        prim = self->ext.corpseweed.prim;
        prim = prim->next;

        // X
        t = self->ext.corpseweed.bobbingStalkXT += BobbingSpeedX_Stalk;
        pos = self->ext.corpseweed.bobbingAngle;
        x = (pos * rsin(t)) >> 0xC;
        pos = (prim->x2 + prim->x3) / 2;
        if (self->facingLeft) {
            // 0x14 represents BobbingOriginOffsX_Stalk
            prim->x1 = pos + 0x14 + x;
            prim->x0 = pos - 0x14 + x;
        } else {
            // 0x14 represents BobbingOriginOffsX_Stalk
            prim->x1 = pos - 0x14 + x;
            prim->x0 = pos + 0x14 + x;
        }

        // Y
        t = self->ext.corpseweed.bobbingStalkYT += BobbingSpeedY_Stalk;
        y = (rsin(t) * 4) >> 0xC;
        pos = prim->y2;
        // 0x70 represents BobbingOriginOffsY_Stalk
        prim->y0 = pos - 0x70 + y;
        prim->y1 = pos - 0x70 - y;

        // Adjust for facing dir
        if (self->facingLeft) {
            x = prim->x0 + 0xC;
        } else {
            x = prim->x0 - 0xC;
        }
        y = prim->y0 + 0xC;
        self->posX.i.hi = x;
        self->posY.i.hi = y;
    }

    // Security check: Only spawnable by E_THORNWEED
    entity = self - 1;
    if (entity->entityId != E_THORNWEED) {
        DestroyEntity(self);
    }
}

void EntityCorpseweedProjectile(Entity* self) {
    // Sprites
    const int SpriteLeft = 0x40;
    const int SpriteRight = 0x80;
    const int SpriteTop = 0x40;
    const int SpriteBottom = 0x80;
    // Misc
    const int Brightness = 0x40;
    const int RangeMaxX = 0x60;
    const int SpeedX = FIX(0.03125);
    const int Gravity = FIX(0.125);

    enum Step {
        INIT = 0,
        AIRBORNE = 1,
        DEATH = 2,
    };

    enum Death_Substep {
        DEATH_INIT = 0,
        DEATH_RIGHT = 1,
        DEATH_LEFT = 2,
    };

    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIdx;
    s32 x;
    s8* hitboxData;
    u32 hitboxIndex;
    s32 y;

    // Death detection
    if ((self->hitFlags) && !(self->hitFlags & 0x80)) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitCorpseweedProjectile);
        x = GetDistanceToPlayerX();
        if (x > RangeMaxX) {
            x = RangeMaxX;
        }
        if (self->facingLeft) {
            self->velocityX = -x * SpeedX;
        } else {
            self->velocityX = x * SpeedX;
        }
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIdx == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIdx;
        prim = &g_PrimBuf[primIdx];
        self->ext.corpseweed.prim = prim;

        prim->tpage = CORPSEWEED_TPAGE;
        prim->clut = CORPSEWEED_PROJ_PAL;
        prim->u0 = prim->u2 = SpriteLeft;
        prim->u1 = prim->u3 = SpriteRight;
        prim->v0 = prim->v1 = SpriteTop;
        prim->v2 = prim->v3 = SpriteBottom;
        prim->r0 = prim->g0 = prim->b0 = Brightness;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority - 1;
        prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
        break;

    case AIRBORNE:
        AnimateEntity(anim_CorpseweedProjectileAirborne, self);
        MoveEntity();

        self->velocityY += Gravity;

        // Check for collision
        x = self->posX.i.hi;
        y = self->posY.i.hi + 1;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            self->posY.i.hi += collider.unk18;
            SetStep(DEATH);
        }
        break;

    case DEATH:
        if (AnimateEntity(anim_CorpseweedProjectileDeath, self) == 0) {
            DestroyEntity(self);
            return;
        }

        prim = self->ext.corpseweed.prim;
        switch (self->step_s) {
        case DEATH_INIT:
            prim->y0 = self->posY.i.hi - 4;
            prim->y1 = self->posY.i.hi - 0x20;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS |
                             DRAW_TPAGE | DRAW_TPAGE2;

            if (self->facingLeft) {
                self->step_s = DEATH_LEFT;
                prim->x0 = prim->x2 = self->posX.i.hi;
                prim->x1 = prim->x3 = self->posX.i.hi - 0x20;
            } else {
                self->step_s = DEATH_RIGHT;
                prim->x0 = prim->x2 = self->posX.i.hi;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x20;
            }
            break;

        case DEATH_RIGHT:
            prim->x0 += 1;
            prim->x1 += 8;
            prim->x2 -= 1;
            prim->x3 += 6;
            prim->y0 -= 3;
            prim->y1 -= 0xA;
            prim->y2 += 1;
            prim->y3 -= 1;
            PrimDecreaseBrightness(prim, 7U);
            break;

        case DEATH_LEFT:
            prim->x0 -= 1;
            prim->x1 -= 8;
            prim->x2 += 1;
            prim->x3 -= 6;
            prim->y0 -= 3;
            prim->y1 -= 0xA;
            prim->y2 += 1;
            prim->y3 -= 1;
            PrimDecreaseBrightness(prim, 7U);
            break;
        }
        break;
    }

    // Update the hitbox based on the current animation frame
    hitboxData = &HitboxData[0];
    hitboxIndex = HitboxIndices[self->animCurFrame];
    hitboxData = &hitboxData[hitboxIndex << 2]; // 4 entries per index
    self->hitboxOffX = *hitboxData++;
    self->hitboxOffY = *hitboxData++;
    self->hitboxWidth = *hitboxData++;
    self->hitboxHeight = *hitboxData++;
}
