#include "chi.h"

/*
 * File: 2A020.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern Entity D_8007D858;

// D_8018173C
s16 PhysicsSensors_Thornweed[] = {
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
            if (UpdatePhysicsState(&PhysicsSensors_Thornweed) & 1) {
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

extern signed short* sprites_chi_7[];

// [Use SpritePart struct?]
// func_801AB548
// https://decomp.me/scratch/yZqKn
// PSP:func_psp_0923A7F0:Match
// PSP:https://decomp.me/scratch/tPXxN
Primitive* func_801AB548(Entity* entity, Primitive* prim)
{
    s16 y;
    s32 spritePartCount;
    s16 x;
    u8 spriteU0;
    u8 spriteV0;
    s16* spriteData;
    s32 i;
    u8 spriteU1;
    s16 spriteDestX;
    s16 spriteDestY;
    s16 spriteDestW;
    s16 spriteDestH;
    s16 spriteFlags;
    u8 spriteV1;
    s32 xFlip;

    spriteData = sprites_chi_7[entity->animCurFrame];
    spritePartCount = *spriteData;
    spriteData++;
    
    for (i = 0; i < spritePartCount; i++, spriteData += 11) {
        spriteFlags = spriteData[0];
        spriteDestX = spriteData[1];
        spriteDestY = spriteData[2];
        spriteDestW = spriteData[3];
        spriteDestH = spriteData[4];

        // Adjust sprite position to respect sprite flags
        if (spriteFlags & 4) {
            spriteDestW -= 1;
            if (spriteFlags & 2) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 8) {
            spriteDestH -= 1;
            if (spriteFlags & 1) {
                spriteDestY += 1;
            }
        }
        if (spriteFlags & 0x10) {
            spriteDestW -= 1;
            if (!(spriteFlags & 2)) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 0x20) {
            spriteDestH -= 1;
            if (!(spriteFlags & 1)) {
                spriteDestY += 1;
            }
        }

        // Calculate sprite position to respect facing
        x = entity->posX.i.hi;
        y = entity->posY.i.hi;
        if (entity->facingLeft) {
            x -= spriteDestX;
        } else {
            x += spriteDestX;
        }
        y += spriteDestY;
        
        // Set sprite position to respect the above, plus sprite dimensions
        if (entity->facingLeft) {
            LOH(prim->x0) = x - spriteDestW + 1;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + 1;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x - spriteDestW + 1;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + 1;
            LOH(prim->y3) = y + spriteDestH;
        } else {
            LOH(prim->x0) = x;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + spriteDestW;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + spriteDestW;
            LOH(prim->y3) = y + spriteDestH;
        }

        // Entity-relative clut
        prim->clut = entity->palette + spriteData[5];

        spriteU0 = spriteData[7];
        spriteV0 = spriteData[8];
        spriteU1 = spriteData[9];
        spriteV1 = spriteData[10];

        // Adjust sprite UVs to respect sprite flags
        if (spriteFlags & 4) {
            spriteU1--;
        }
        if (spriteFlags & 8) {
            spriteV1--;
        }
        if (spriteFlags & 0x10) {
            spriteU0++;
        }
        if (spriteFlags & 0x20) {
            spriteV0++;
        }

        // Set sprite UVs to respect the above, plus facing
        xFlip = (spriteFlags & 2) ^ entity->facingLeft;
        if (!xFlip) {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU0;
                prim->v0 = spriteV0;
                prim->u1 = spriteU1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU0;
                prim->v2 = spriteV1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU0;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU0;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV0 - 1;
            }
        } else {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV0;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV0 - 1;
            }
        }

        prim->tpage = 0x14;
        // Entity-relative z priority
        prim->priority = entity->zPriority + 1;

        // Next!
        prim = prim->next;
    }
    return prim;
}