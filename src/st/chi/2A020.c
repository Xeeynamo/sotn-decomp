#include "chi.h"

/*
 * File: 2A020.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern Entity D_8007D858;

// D_8018173C
s16 PhysicsSensors[] = {
    0, 1, 0, 4, 2, -4, -4, 0,
};

// D_8018174C
u8 AnimFrames_ThornweedWakeup[] = {
    0x02, 0x01, 0x06, 0x02, 0x06, 0x03, 0x06, 0x04, 0xFF, 0x00, 0x00, 0x00
};

// D_80181758
u8 AnimFrames_ThornweedIdle[] = {
    0x06, 0x05, 0x06, 0x06, 0x06, 0x07, 0x06, 0x08, 0x00, 0x00, 0x00, 0x00
};

// D_80181764
u8 AnimFrames_CorpseweedWakeup[] = {
    0x02, 0x09, 0x06, 0x0A, 0x06, 0x0B, 0x06, 0x0C, 0xFF, 0x00, 0x00, 0x00
};

// D_80181770
u8 AnimFrames_CorpseweedIdle[] = {
    0x06, 0x0D, 0x06, 0x0E, 0x06, 0x0F, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00
};

// D_8018177C
u8 AnimFrames_CorpseweedAttackCharge[] = {
    0x02, 0x13, 0x02, 0x14, 0x00, 0x00, 0x00, 0x00
};

// D_80181784
u8 AnimFrames_CorpseweedProjectileAirborne[] = {
    0x02, 0x16, 0x02, 0x17, 0x00, 0x00, 0x00, 0x00
};

// D_8018178C
u8 AnimFrames_CorpseweedProjectileDeath[] = {
    0x04, 0x18, 0x03, 0x19, 0x02, 0x1A, 0x02, 0x1B, 0xFF, 0x00, 0x00, 0x00
};

// D_80181798
u8* AnimFrames_All[] = {
    &AnimFrames_ThornweedWakeup, &AnimFrames_CorpseweedWakeup,  // WakeUp
    &AnimFrames_ThornweedIdle, &AnimFrames_CorpseweedIdle,      // Idle
};

// D_801817A8
s8 HitboxData[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x03, 0x01, 0xFE, 0x03, 0x04, 0x00, 0xFA, 0x07, 0x09,
    0x01, 0xFB, 0x09, 0x07, 0xC1, 0xC1, 0x00, 0x00, 0x02, 0x09, 0x05, 0x08, 0x00, 0x00, 0x04, 0x04,
    0x03, 0xF5, 0x04, 0x0C, 0x04, 0xFD, 0x05, 0x05, 0x0F, 0xF5, 0x17, 0x15
};

// D_801817D4
u8 HitboxIndices[] = {
    0x00, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x04,
    0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x08, 0x09, 0x09, 0x05, 0x0A, 0x00, 0x00, 0x00
};

extern EntityInit EntityInit_801806D0;

// E_THORNWEED
// params: 0 = Thornweed, 1 = Corpseweed
// func_801AA020
// PSP:func_psp_09249750:Match
// PSP:https://decomp.me/scratch/LAyvk
void EntityThornweed(Entity* self)
{
    const int EntityFormCount = 2;  // Thornweed, Corpseweed
    const int AnimFrame_ThornweedInit = 1;
    const int AnimFrame_CorpseweedInit = 9;
    const int WakeDistance = 0x50;
    const int CorpseweedSpawnDelay = 0x40;
    const int DeathExplosionDelay = 0x80;

    enum Step {
        Init = 0,
        DropToGround = 1,
        WaitToWake = 2,
        WakeUp = 3,
        Idle = 4,
        CorpseweedDeath = 6,
    };

    Entity* entity;
    u8* animFrames;
    s8* hitboxData;
    u32 hitboxIndex;

    // Check for death
    if ((self->flags & FLAG_DEAD) && (self->step < 6)) {
        if ((self->params) && (self->ext.thornweed.isCorpseweedSpawned)) {
            SetStep(CorpseweedDeath);
        } else {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posY.i.hi -= 4;
                entity->params = 0;
            }
            g_api.PlaySfx(NA_SE_EN_THORNWEED_DEATH);
            DestroyEntity(self);
            return;
        }
    }

    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_801806D0);
            if (self->params) {
                self->animCurFrame = AnimFrame_CorpseweedInit;
            } else {
                self->animCurFrame = AnimFrame_ThornweedInit;
            }
            break;

        case DropToGround:
            if (UpdatePhysicsState(&PhysicsSensors) & 1) {
                SetStep(WaitToWake);
            }
            break;

        case WaitToWake:
            if (GetDistanceToPlayerX() < WakeDistance) {
                SetStep(WakeUp);
            }
            break;

        case WakeUp:
            animFrames = AnimFrames_All[self->params];
            if (AnimateEntity(animFrames, self) == 0) {
                self->ext.thornweed.timer = CorpseweedSpawnDelay;
                SetStep(Idle);
            }
            break;

        case Idle:
            // Check for any necessary idle init
            if (!self->step_s) {
                if (self->params) {
                    if (!--self->ext.thornweed.timer) {
                        self->step_s++;

                        // Spawn the Corpseweed stalk/head
                        entity = self + 1;
                        CreateEntityFromEntity(E_CORPSEWEED, self, entity);
                        entity->facingLeft = (GetSideToPlayer() & 1);
                        self->enemyId = 0x9E;
                        self->ext.thornweed.isCorpseweedSpawned = true;
                    }
                } else {
                    self->step_s++;
                }
            }

            // Animate
            animFrames = AnimFrames_All[self->params + EntityFormCount];
            AnimateEntity(animFrames, self);
            break;

        case CorpseweedDeath:
            if (!self->step_s) {
                entity = self + 1;
                entity->flags |= FLAG_DEAD;
                self->hitboxState = 0;
                self->unk6C = DeathExplosionDelay;
                self->drawFlags |= FLAG_DRAW_UNK8;
                self->step_s++;
            }
            if (!--self->unk6C) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posY.i.hi -= 0xC;
                    entity->params = 2;
                }
                g_api.PlaySfx(NA_SE_EN_THORNWEED_DEATH);
                DestroyEntity(self);
                return;
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

extern EntityInit EntityInit_801806E8;

// E_CORPSEWEED
// func_801AA390
// https://decomp.me/scratch/QVcDz
// PSP:func_psp_09249BE0:No match
// PSP:https://decomp.me/scratch/lqXTP
void EntityCorpseweed(Entity* self)
{
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
    const int DeathHeadFallAccel = 0x1800;
    const int DeathHeadRotateSpeed = 0x20;

    enum Step {
        Init = 0,
        GrowLeaves = 1,
        GrowStalk = 2,
        GrowToIdle = 3,
        Idle = 4,
        Attack = 5,
        Death = 6,
    };

    enum GrowLeaves_Substep {
        GrowLeaves_H = 0,
        GrowLeaves_V = 1,
        GrowLeaves_Done = 2,
    };

    enum GrowStalk_Substep {
        GrowStalk_H1 = 0,
        GrowStalk_UnevenV = 1,
        GrowStalk_FinishV = 2,
        GrowStalk_H2 = 3,
    };

    enum Attack_Substep {
        Attack_Init = 0,
        Attack_Delay = 1,
        Attack_Projectile = 2,
        Attack_ResetDelay = 3,
    };

    enum Death_Substep {
        Death_Init = 0,
        Death_DropHead = 1,
        Death_ShrinkAndFade = 2,
    };

    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIdx;
    s32 pos;
    s32 y;
    s32 x;
    s32 doneCount;
    s16 t;

    if ((self->flags & FLAG_DEAD) && (self->step < Death)) {
        SetStep(Death);
    }

    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_801806E8);
            self->animCurFrame = AnimFrameInit;
            self->hitboxOffX = 2;
            self->hitboxOffY = 9;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->rotX = self->rotY = 0;
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
            self->ext.prim = prim;

            // Leaves primitive
            prim->tpage = 0x13;
            prim->clut = PAL_DRA(0x206);
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
            prim->drawMode = FLAG_DRAW_ROTY;

            // Stalk primitive
            prim = prim->next;
            prim->tpage = 0x13;
            prim->clut = PAL_DRA(0x206);
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
            prim->drawMode = FLAG_DRAW_ROTY;
            prim = prim->next;
            // Fallthrough
        case GrowLeaves:
            prim = self->ext.prim;
            switch (self->step_s) {
                case GrowLeaves_H:
                    // Expand leaves sprite horizontally
                    prim->x0 = --prim->x2;
                    prim->x1 = ++prim->x3;
                    x = prim->x1 - prim->x0;
                    if (x >= LeavesGrowMaxWidth) {
                        self->step_s++;
                    }
                    // fallthrough
                case GrowLeaves_V:
                    // Extend leaves sprite up
                    prim->y0 = --prim->y1;
                    y = prim->y2 - prim->y0;
                    if (y >= LeavesGrowMaxHeight) {
                        self->step_s++;
                    }
                    break;

                case GrowLeaves_Done:
                    self->ext.corpseweed.leavesDoneGrowing = true;
                    SetStep(GrowStalk);
                    break;
            }
            break;

        case GrowStalk:
            prim = self->ext.prim;
            prim = prim->next;
            switch (self->step_s) {
                case GrowStalk_H1:
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
                    // Once stalk sprite has expanded enough opposite of facing direction
                    x = self->posX.i.hi - prim->x1;
                    x = abs(x);
                    if (x >= StalkGrowMaxWidthNonFacing) {
                        self->step_s++;
                    }
                    break;

                case GrowStalk_UnevenV:
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

                case GrowStalk_FinishV:
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

                case GrowStalk_H2:
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
                        SetStep(3);
                    }
                    break;
            }
            break;

        case GrowToIdle:
            self->animCurFrame = AnimFrameIdle;
            if (self->rotX < 0x100) {
                self->rotX = self->rotY += 8;
            } else {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                SetStep(Idle);
            }
            break;

        case Idle:
            if (!self->step_s) {
                self->ext.corpseweed.timer = DelayBeforeFirstAttack;
                self->step_s += 1;
            }
            self->animCurFrame = AnimFrameIdle;
            if (!--self->ext.corpseweed.timer) {
                if ((GetSideToPlayer() & 1) == self->facingLeft) {
                    SetStep(Attack);
                } else {
                    self->ext.corpseweed.timer = DelayBetweenAttackChecks;
                }
            }
            if (self->hitFlags & 2) {
                self->ext.corpseweed.bobbingTimer = BobbingTimer;
            }
            break;

        case Attack:
            switch (self->step_s) {
                case Attack_Init:
                    self->ext.corpseweed.timer = AttackChargeDuration;
                    self->step_s += 1;
                    // fallthrough
                case Attack_Delay:
                    AnimateEntity(AnimFrames_CorpseweedAttackCharge, self);
                    if (!--self->ext.corpseweed.timer) {
                        SetSubStep(Attack_Projectile);
                    }
                    break;

                case Attack_Projectile:
                    self->animCurFrame = AnimFrameAttack;
                    // Spawn projectile entity
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        PlaySfxWithPosArgs(NA_SE_EN_CORPSEWEED_ATTACK);

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
                case Attack_ResetDelay:
                    if (!--self->ext.corpseweed.timer) {
                        SetStep(Idle);
                    }
                    break;
            }
        break;

        case Death:
            switch (self->step_s) {
                case Death_Init:
                    self->ext.corpseweed.leavesDoneGrowing = false;
                    self->ext.corpseweed.stalkDoneGrowing = false;
                    self->hitboxState = 0;
                    self->drawFlags = FLAG_DRAW_ROTZ;
                    self->step_s++;
                    // fallthrough
                case Death_DropHead:
                    MoveEntity();
                    self->velocityY += DeathHeadFallAccel;
                    self->rotZ += DeathHeadRotateSpeed;

                    // Wait until head hits the ground
                    x = self->posX.i.hi;
                    y = self->posY.i.hi + 8;
                    g_api.CheckCollision(x, y, &collider, 0);
                    if (collider.effects & 1) {
                        g_api.PlaySfx(NA_SE_EN_CORPSEWEED_DEATH);
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

                        PlaySfxWithPosArgs(NA_SE_EN_CORPSEWEED_COLLAPSE);
                        self->step_s++;
                    }
                    break;

                case Death_ShrinkAndFade:
                    self->ext.corpseweed.timer++;
                    prim = self->ext.prim;

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
                        func_801AE70C(prim, 3U);
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
                    func_801AE70C(prim, 1U);
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
        prim = self->ext.prim;

        // X
        t = self->ext.corpseweed.bobbingLeavesXT += BobbingSpeedX_Leaves;
        x = (rcos(t) * 2) >> 0xC;
        pos = (prim->x2 + prim->x3) / 2;
        prim->x0 = pos - BobbingOriginOffsX_Leaves + x;
        prim->x1 = pos + BobbingOriginOffsX_Leaves + x;

        // Y
        t = self->ext.corpseweed.bobbingLeavesYT += BobbingSpeedY_Leaves;
        y = (rsin(t) * 4) >> 0xC;
        pos = prim->y2;
        prim->y0 = pos - BobbingOriginOffsY_Leaves + y;
        prim->y1 = pos - BobbingOriginOffsY_Leaves - y;
    }

    // Update stalk for bobbing back and forth
    if (self->ext.corpseweed.stalkDoneGrowing) {
        prim = self->ext.prim;
        prim = prim->next;

        // X
        t = self->ext.corpseweed.bobbingStalkXT += BobbingSpeedX_Stalk;
        pos = self->ext.corpseweed.bobbingAngle;
        x = (pos * rsin(t)) >> 0xC;
        pos = (prim->x2 + prim->x3) / 2;
        if (self->facingLeft) {
            prim->x1 = pos + BobbingOriginOffsX_Stalk + x;
            prim->x0 = pos - BobbingOriginOffsX_Stalk + x;
        } else {
            prim->x1 = pos - BobbingOriginOffsX_Stalk + x;
            prim->x0 = pos + BobbingOriginOffsX_Stalk + x;
        }

        // Y
        t = self->ext.corpseweed.bobbingStalkYT += BobbingSpeedY_Stalk;
        y = (rsin(t) * 4) >> 0xC;
        pos = prim->y2;
        prim->y0 = pos - BobbingOriginOffsY_Stalk + y;
        prim->y1 = pos - BobbingOriginOffsY_Stalk - y;

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

extern EntityInit EntityInit_801806F4;

// E_CORPSEWEED_PROJECTILE
// func_801AB0C0
// PSP:func_psp_0924AE40:Match
// PSP:https://decomp.me/scratch/qpbbH
void EntityCorpseweedProjectile(Entity* self)
{
    // Sprites
    const int SpriteLeft = 0x40;
    const int SpriteRight = 0x80;
    const int SpriteTop = 0x40;
    const int SpriteBottom = 0x80;
    // Misc
    const int Brightness = 0x40;
    const int RangeMaxX = 0x60;
    const int SpeedX = 0x800;
    const int Gravity = FIX(0.125);

    enum Step {
        Init = 0,
        Airborne = 1,
        Death = 2,
    };

    enum Death_Substep {
        Death_Init = 0,
        Death_Right = 1,
        Death_Left = 2,
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
        case Init:
            InitializeEntity(&EntityInit_801806F4);
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
            self->ext.prim = prim;
            
            prim->tpage = 0x13;
            prim->clut = PAL_DRA(0x209);
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

        case Airborne:
            AnimateEntity(AnimFrames_CorpseweedProjectileAirborne, self);
            MoveEntity();

            self->velocityY += Gravity;

            // Check for collision
            x = self->posX.i.hi;
            y = self->posY.i.hi + 1;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & 1) {
                g_api.PlaySfx(NA_SE_EN_CORPSEWEED_COLLAPSE);
                self->posY.i.hi += collider.unk18;
                SetStep(Death);
            }
            break;

        case Death:
            if (AnimateEntity(AnimFrames_CorpseweedProjectileDeath, self) == 0) {
                DestroyEntity(self);
                return;
            }

            prim = self->ext.prim;
            switch (self->step_s) {
                case Death_Init:
                    prim->y0 = self->posY.i.hi - 4;
                    prim->y1 = self->posY.i.hi - 0x20;
                    prim->y2 = prim->y3 = self->posY.i.hi;
                    prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;

                    if (self->facingLeft) {
                        self->step_s = Death_Left;
                        prim->x0 = prim->x2 = self->posX.i.hi;
                        prim->x1 = prim->x3 = self->posX.i.hi - 0x20;
                    } else {
                        self->step_s = Death_Right;
                        prim->x0 = prim->x2 = self->posX.i.hi;
                        prim->x1 = prim->x3 = self->posX.i.hi + 0x20;
                    }
                    break;

                case Death_Right:
                    prim->x0 += 1;
                    prim->x1 += 8;
                    prim->x2 -= 1;
                    prim->x3 += 6;
                    prim->y0 -= 3;
                    prim->y1 -= 0xA;
                    prim->y2 += 1;
                    prim->y3 -= 1;
                    func_801AE70C(prim, 7U);
                    break;

                case Death_Left:
                    prim->x0 -= 1;
                    prim->x1 -= 8;
                    prim->x2 += 1;
                    prim->x3 -= 6;
                    prim->y0 -= 3;
                    prim->y1 -= 0xA;
                    prim->y2 += 1;
                    prim->y3 -= 1;
                    func_801AE70C(prim, 7U);
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

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801ACEF4);    // [Entity]

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/2A020", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
