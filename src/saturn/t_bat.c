// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "t_bat/batanim.h"
#include "t_bat/batbss.h"
#include "t_bat/batevent.h"
#include "t_bat/batstat.h"
#include <saturn_sprite.h>

void PlaySfx(s32 sfxId);

extern SaturnSpriteImage g_BatTextureSlices[25];
extern SaturnSpriteResource g_BatTextureResource;
extern struct SpriteParts* g_ServantSpriteParts[]; // 0x060D19FC
extern s32 g_CutsceneHasControl;

static inline void SetEntityAnimation(Entity* entity, AnimationFrame* anim) {
    if (entity->anim != anim) {
        entity->anim = anim;
        entity->pose = 0;
        entity->poseTimer = 0;
    }
}

Entity* FindValidTarget(Entity* self) {
    s16 s_TargetMatch[0x80];

    const s32 EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;
        if (!entity->entityId) {
            continue;
        }
        if (entity->hitboxState == 0) {
            continue;
        }
        if (entity->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (entity->posX.i.hi < -16) {
            continue;
        }
        if (entity->posX.i.hi > 336) {
            continue;
        }
        if (entity->posY.i.hi > 240) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (entity->hitboxState & 8 &&
            !g_BatAbilityStats[s_BatStats.level / 10].makeBadAttacks) {
            continue;
        }
        if (ABS(self->posX.i.hi - entity->posX.i.hi) < 64 &&
            ABS(self->posY.i.hi - entity->posY.i.hi) < 64) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }
        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_BatAbilityStats[s_BatStats.level / 10].minimumEnemyHp) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }
    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex =
                    (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }
    return NULL;
}

s32 CheckEntityValid(Entity* entity) {
    if (entity->hitboxState == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 0x150)
        return 0;
    if (entity->posY.i.hi > 0xF0)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    if (entity->hitPoints <= 0)
        return 0;
    return 1;
}

static inline void unused_1560(Entity* self) {}

static inline void CreateBlueTrailEntity(Entity* parent) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }
    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = 0xDA;
        entity->zPriority = parent->zPriority - 1;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX = parent->posX;
        entity->posY = parent->posY;
        entity->ext.batFamBlueTrail.parent = parent;
    }
}

// SAT: func_060CF2E8
void CreateAdditionalBats(s32 amount, s32 entityId) {
    s32 i;
    Entity* entity;

    amount = (amount > 3) ? 3 : amount;

    for (i = 0; i < amount; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == entityId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->unk0 = func_0600B344(
                g_BatTextureResource.allocationIndex,
                g_BatTextureResource.flags, g_BatTextureSlices, 1);
            if (entity->unk0 == NULL) {
                DestroyEntity(entity);
                return;
            }
            entity->pad_B0 = g_ServantSpriteParts;
            entity->unk0->zPriority = PLAYER.zPriority - 2;
            entity->entityId = entityId;
            entity->unk56 = 0x6C;
            entity->palette = 0x140;
            entity->animSet = 0x8014;
            entity->zPriority = PLAYER.zPriority - 2;
            entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
            entity->params = i + 1;
        }
        entity->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        entity->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    }
}

void UpdatePrimitives(Entity* entity, s32 frameIndex);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF410, func_060CF410);

// SAT: func_060CF5F4
void UpdatePrimWhenAlucardIsBat(Entity* entity) {
    Primitive* prim;
    s32 frame;
    s32 x, y;

    frame = 2;
    if (entity->facingLeft) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    x += (rsin(entity->ext.bat.frameCounter * 0x80) * 8) >> 12;
    y -= entity->ext.bat.frameCounter / 2;

    prim = &g_PrimBuf[entity->primIndex];
    prim->x0 = x - g_BatSpriteData[frame].x;
    prim->y0 = y - g_BatSpriteData[frame].y;
}

// SAT: func_060CF6B4
void SwitchModeInitialize(Entity* self) {
    s32 i;

    if (!self->ext.bat.previouslyInitialized) {
        self->ext.bat.batIndex = self->params;
        self->ext.bat.doUpdateCloseAnimation = false;
        switch (self->entityId) {
        case 0xD1:
            self->unk0 = func_0600B344(
                g_BatTextureResource.allocationIndex,
                g_BatTextureResource.flags, g_BatTextureSlices, 1);
            if (self->unk0 == NULL) {
                DestroyEntity(self);
                return;
            }
            self->pad_B0 = g_ServantSpriteParts;
            self->unk0->zPriority = PLAYER.zPriority - 2;
            self->primIndex = AllocPrimitives(0, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            UpdatePrimitives(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->ext.bat.randomMovementAngle = MTH_GetRand() & 0xFFF;
            self->ext.bat.targetAngle = 0;
            self->ext.bat.randomMovementScaler = 12;
            self->ext.bat.frameCounter = MTH_GetRand() & 0xFFF;
            self->ext.bat.angleStep = 0x20;
            self->step++;
            break;
        case 0xD2:
            self->primIndex = AllocPrimitives(0, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            UpdatePrimitives(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (self->ext.bat.batIndex == 0) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[self->ext.bat.batIndex + 3];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
            if (!self->ext.bat.batIndex) {
                for (i = 0; i < 16; i++) {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
                    s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                        self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
                }
            } else {
                for (i = 0; i < 16; i++) {
                    if (PLAYER.facingLeft) {
                        s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                            PLAYER.posX.i.hi +
                            (self->ext.bat.batIndex + 1) * 0x10 +
                            self->ext.bat.cameraX;
                    } else {
                        s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                            PLAYER.posX.i.hi -
                            (self->ext.bat.batIndex + 1) * 0x10 +
                            self->ext.bat.cameraX;
                    }
                    s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                        PLAYER.posY.i.hi + self->ext.bat.cameraY;
                }
                self->posX.i.hi = PLAYER.facingLeft ? 0x180 : -0x80;
                self->posY.i.hi = MTH_GetRand() & 0xFF;
            }
            self->ext.bat.hasShotFireball = false;
            self->step++;
            break;
        }
    } else {
        self->ext.bat.doUpdateCloseAnimation = false;
        switch (self->entityId) {
        case 0xD1:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->ext.bat.frameCounter = MTH_GetRand() & 0xFFF;
            self->step++;
            break;
        case 0xD2:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (self->ext.bat.batIndex == 0) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[self->ext.bat.batIndex + 3];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
            for (i = 0; i < 16; i++) {
                if (PLAYER.facingLeft) {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        PLAYER.posX.i.hi + (self->ext.bat.batIndex + 1) * 0x10 +
                        self->ext.bat.cameraX;
                } else {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        PLAYER.posX.i.hi - (self->ext.bat.batIndex + 1) * 0x10 +
                        self->ext.bat.cameraX;
                }
                s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                    PLAYER.posY.i.hi + self->ext.bat.cameraY;
            }
            self->ext.bat.hasShotFireball = false;
            self->step++;
            break;
        }
    }
    self->ext.bat.previouslyInitialized = self->entityId;
    GetServantStats(self, 0, 0, &s_BatStats);
}

// SAT: func_060CFB00
void ServantInit(s32 mode) {
    Entity* e;

    if ((mode == 1) || (mode == 3)) {
        ProcessEvent(NULL, true);
        if (mode == 3) {
            return;
        }
    }

    e = &g_Entities[4];

    DestroyEntity(e);

    e->unk56 = 0x6C;
    e->palette = 0x140;
    e->animSet = 0x8014;
    e->zPriority = PLAYER.zPriority - 2;
    e->facingLeft = (PLAYER.facingLeft + 1) & 1;
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    e->params = 0;

    if (mode == 1) {
        e->entityId = 0xD1;
        e->posX.val = FIX(128);
        e->posY.val = FIX(-32);
    } else {
        e->entityId = 0xD1;
        if (D_8003C708.flags & FLAG_UNK_20) {
            e->posX.val = ServantUnk0() ? FIX(192) : FIX(64);
            e->posY.val = FIX(160);
        } else {
            e->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(18) : FIX(-18));
            e->posY.val = PLAYER.posY.val - FIX(34);
        }
    }
    e->flags =
        FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
    e->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    s_IsServantDestroyed = 0;
}

// SAT: func_060CFC48
void UpdateServantDefault(Entity* self) {
    s16 targetX;
    s16 targetY;
    s32 dx0;
    s32 dy0;
    s32 angle;
    s32 dAngle;
    s32 distance0;
    s16 xOffset;
    s32 s_TargetPositionX;
    s32 s_TargetPositionY;
    s32 dx1;
    s32 dy1;
    s32 distance1;

    GetServantStats(self, 0, 0, &s_BatStats);
    if (s_IsServantDestroyed) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (D_8003C708.flags & FLAG_UNK_20) {
        switch (ServantUnk0()) {
        case 0:
            dx0 = 0x40;
            break;

        case 1:
            dx0 = 0xC0;
            break;

        case 2:
            dx0 = (self->posX.i.hi > 0x80) ? 0xC0 : 0x40;
            break;
        }
        dy0 = 0xA0;
    } else {
        xOffset = -0x12;
        if (PLAYER.facingLeft) {
            xOffset = -xOffset;
        }
        dx0 = PLAYER.posX.i.hi + xOffset;
        dy0 = PLAYER.posY.i.hi - 0x22;
    }
    angle = self->ext.bat.randomMovementAngle;
    self->ext.bat.randomMovementAngle += 0x10;
    distance0 = self->ext.bat.randomMovementScaler;
    targetX = dx0 + ((rcos(angle) >> 4) * distance0 >> 8);
    targetY = dy0 - ((rsin(angle / 2) >> 4) * distance0 >> 8);
    switch (self->step) {
    case 0:
        SwitchModeInitialize(self);
        break;

    case 1:
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            self->ext.bat.frameCounter = 0;
            self->step = 5;
            break;
        }
        if (D_8003C708.flags & FLAG_UNK_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (ABS(targetX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else if (self->facingLeft && targetX < self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else if (!self->facingLeft && targetX > self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                }
            } else if (self->facingLeft && (self->posX.i.hi - targetX) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (
                !self->facingLeft && (targetX - self->posX.i.hi) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            }
        }
        angle = CalculateAngleToEntity(self, targetX, targetY);
        dAngle = StepAngleTowards(
            angle, self->ext.bat.targetAngle, self->ext.bat.angleStep);
        self->ext.bat.targetAngle = dAngle;
        dx0 = targetX - self->posX.i.hi;
        dy0 = targetY - self->posY.i.hi;
        distance0 = dx0 * dx0 + dy0 * dy0;
        if (distance0 < 800) {
            self->velocityY = -(rsin(dAngle) << 3);
            self->velocityX = rcos(dAngle) << 3;
            self->ext.bat.angleStep = 0x20;
        } else if (distance0 < 3000) {
            self->velocityY = -(rsin(dAngle) << 4);
            self->velocityX = rcos(dAngle) << 4;
            self->ext.bat.angleStep = 0x40;
        } else if (distance0 < 9000) {
            self->velocityY = -(rsin(dAngle) << 5);
            self->velocityX = rcos(dAngle) << 5;
            self->ext.bat.angleStep = 0x60;
        } else if (distance0 < 256 * 256) {
            self->velocityY = -(rsin(dAngle) << 6);
            self->velocityX = rcos(dAngle) << 6;
            self->ext.bat.angleStep = 0x80;
        } else {
            self->velocityX = (targetX - self->posX.i.hi) << 0xE;
            self->velocityY = (targetY - self->posY.i.hi) << 0xE;
            self->ext.bat.angleStep = 0x80;
        }

        self->velocityX = self->velocityX * 5 >> 2;
        if (self->velocityY > FIX(1.0)) {
            SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
        } else if (distance0 < 60 * 60) {
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        } else if (distance0 > 100 * 100) {
            SetEntityAnimation(self, g_BatFarFromTargetAnimationFrame);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (g_CutsceneHasControl) {
            break;
        }
        dx1 = targetX - self->posX.i.hi;
        dy1 = targetY - self->posY.i.hi;
        distance1 = dx1 * dx1 + dy1 * dy1;
        if (distance1 < 24 * 24) {
            if (self->ext.bat.doUpdateCloseAnimation) {
                self->ext.bat.doUpdateCloseAnimation = false;
                SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
            }
            self->ext.bat.frameCounter++;
            if (self->ext.bat.frameCounter >
                g_BatAbilityStats[s_BatStats.level / 10].delayFrames) {
                self->ext.bat.frameCounter = 0;
                self->ext.bat.attackTarget = FindValidTarget(self);
                if (self->ext.bat.attackTarget != NULL) {
                    self->step++;
                }
            }
        } else {
            self->ext.bat.doUpdateCloseAnimation = true;
        }
        break;

    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            PlaySfx(SFX_UI_ALERT_TINK);
            UpdatePrimitives(self, 1);
        } else if (self->ext.bat.frameCounter > 30) {
            self->ext.bat.frameCounter = 0;
            UpdatePrimitives(self, 0);
            self->hitboxWidth = 5;
            self->hitboxHeight = 5;
            GetServantStats(self, 0xf, 1, &s_BatStats);
            self->ext.bat.targetAngle = 0xC00;
            SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
            CreateBlueTrailEntity(self);
            self->step++;
        }
        break;

    case 3:
        s_TargetPositionX = self->ext.bat.attackTarget->posX.i.hi;
        s_TargetPositionY = self->ext.bat.attackTarget->posY.i.hi;
        angle =
            CalculateAngleToEntity(self, s_TargetPositionX, s_TargetPositionY);
        dAngle = StepAngleTowards(
            angle, self->ext.bat.targetAngle,
            g_BatAbilityStats[s_BatStats.level / 10].angleStep);
        self->ext.bat.targetAngle = dAngle;
        self->velocityX = rcos(dAngle) << 2 << 4;
        self->velocityY = -(rsin(dAngle) << 2 << 4);
        if (self->velocityX > 0) {
            self->facingLeft = true;
        }
        if (self->velocityX < 0) {
            self->facingLeft = false;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        dx1 = s_TargetPositionX - self->posX.i.hi;
        dy1 = s_TargetPositionY - self->posY.i.hi;
        distance1 = dx1 * dx1 + dy1 * dy1;
        if ((CheckEntityValid(self->ext.bat.attackTarget) == 0) ||
            (distance1 < 0x40)) {
            self->ext.bat.frameCounter = 0;
            self->step++;
            SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
        }
        break;

    case 4:
        angle = CalculateAngleToEntity(self, targetX, targetY);
        dAngle = StepAngleTowards(angle, self->ext.bat.targetAngle, 0x10);
        self->ext.bat.targetAngle = dAngle;
        self->velocityX = rcos(dAngle) << 2 << 4;
        self->velocityY = -(rsin(dAngle) << 2 << 4);
        self->facingLeft = (self->velocityX >= 0) ? true : false;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter > 30) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step = 1;
        }
        break;

    case 5:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            PlaySfx(SFX_BAT_SCREECH);
            UpdatePrimitives(self, 3);
        } else if (self->ext.bat.frameCounter > 30) {
            UpdatePrimitives(self, 0);
            self->entityId = 0xD2;
            self->step = 0;
        }
        UpdatePrimWhenAlucardIsBat(self);
        break;
    }
    ProcessEvent(self, false);
    unused_1560(self);
    UpdateAnim(NULL, g_BatAnimationFrames);
}

// SAT: func_060D0490
void UpdateBatAttackMode(Entity* self) {
    s32 i;
    s32 distance;
    s16 targetX, targetY;

    GetServantStats(self, 0, 0, &s_BatStats);
    if (s_IsServantDestroyed) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        SwitchModeInitialize(self);
        if (self->ext.bat.batIndex == 0) {
            CreateAdditionalBats(
                g_BatAbilityStats[s_BatStats.level / 10].additionalBatCount,
                0xD2);
        }
        break;

    case 1:
        self->ext.bat.lastPlayerPosX = PLAYER.posX.i.hi;
        self->ext.bat.lastPlayerPosY = PLAYER.posY.i.hi;
        self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
        targetX = s_BatPathingPoints[self->ext.bat.batIndex][0].x -
                  self->ext.bat.cameraX;
        targetY = s_BatPathingPoints[self->ext.bat.batIndex][0].y -
                  self->ext.bat.cameraY;
        self->velocityX = (targetX - self->posX.i.hi) << 0xC;
        self->velocityY = (targetY - self->posY.i.hi) << 0xC;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->velocityX == 0 && self->velocityY == 0) {
            if (self->ext.bat.doUpdateCloseAnimation) {
                SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
                self->ext.bat.doUpdateCloseAnimation = false;
            }
        } else {
            if (self->velocityY > FIX(1.0)) {
                SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
            } else {
                SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            }
            self->ext.bat.doUpdateCloseAnimation = true;
        }
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (!self->ext.bat.hasShotFireball &&
            (g_Player.status & PLAYER_STATUS_SUBWPN)) {
            CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
            self->ext.bat.hasShotFireball = true;
        } else if (self->ext.bat.hasShotFireball &&
                   !(g_Player.status & PLAYER_STATUS_SUBWPN)) {
            self->ext.bat.hasShotFireball = false;
        }
        g_BatFollowDeltaX = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        g_BatFollowDeltaY = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        distance = g_BatFollowDeltaX * g_BatFollowDeltaX +
                   g_BatFollowDeltaY * g_BatFollowDeltaY;
        if (IsMovementAllowed(0) || distance > 0x18 * 0x18) {
            for (i = 0; i < 15; i++) {
                s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                    s_BatPathingPoints[self->ext.bat.batIndex][i + 1].x;
                s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                    s_BatPathingPoints[self->ext.bat.batIndex][i + 1].y;
            }
            s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
            s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
        }
        if (!(g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            self->ext.bat.frameCounter = 0;
            self->step++;
        }
        break;

    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            if (!self->ext.bat.batIndex) {
                PlaySfx(SFX_BAT_SCREECH);
            }
            UpdatePrimitives(self, 2);
        } else if (self->ext.bat.frameCounter > 30) {
            UpdatePrimitives(self, 0);
            if (!self->ext.bat.batIndex) {
                self->entityId = 0xD1;
                self->step = 0;
                break;
            }
            self->step++;
            s_BatPathingPoints[self->ext.bat.batIndex][0].x =
                PLAYER.facingLeft ? -0x80 : 0x180;
            s_BatPathingPoints[self->ext.bat.batIndex][0].y =
                MTH_GetRand() & 0xFF;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        }
        break;

    case 3:
        targetX = s_BatPathingPoints[self->ext.bat.batIndex][0].x;
        targetY = s_BatPathingPoints[self->ext.bat.batIndex][0].y;
        self->velocityX = (targetX - self->posX.i.hi) * 0x400;
        self->velocityY = (targetY - self->posY.i.hi) * 0x400;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posX.i.hi < -0x20 || self->posX.i.hi > 0x120) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    ProcessEvent(self, false);
    unused_1560(self);
    UpdateAnim(NULL, g_BatAnimationFrames);
}

void unused_339C() {}

void unused_33A4() {}

void unused_33AC() {}

void unused_33B4() {}

// SAT: func_060D0968
void func_060D0968(void) {
    Entity* ent;
    s16 i, j;
    s16 dx, dy;

    for (i = 0; i < 4; i++) {
        ent = &g_Entities[4 + i];
        if (ent->entityId == 0xD2 && ent->step == 1) {
            dx = (ent->ext.bat.cameraX - g_Tilemap.scrollX.i.hi) +
                 (ent->ext.bat.lastPlayerPosX - PLAYER.posX.i.hi);
            dy = (ent->ext.bat.cameraY - g_Tilemap.scrollY.i.hi) +
                 (ent->ext.bat.lastPlayerPosY - PLAYER.posY.i.hi);
            for (j = 0; j < 0x10; j++) {
                s_BatPathingPoints[i][j].x -= dx;
                s_BatPathingPoints[i][j].y -= dy;
            }
        }
    }
}

void unused_33C4() {}

void unused_33CC() {}

// UpdateBatBlueTrailEntities
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0A64, func_060D0A64);

void unused_3C0C() {}

void unused_3C14() {}

void unused_3C1C() {}

void unused_3C24() {}

// SAT: func_060D1040
void DestroyServantEntity(Entity* entity) {
    if (entity->params == 0xF) {
        s_IsServantDestroyed = 1;
    }
    DestroyEntity(entity);
}

// SAT: func_060D1070
u32 ServantUpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    s32 ret = 0;

    if (self->poseTimer == -1) {
        ret = -1;
    } else if (self->poseTimer == 0) {
        self->poseTimer = self->anim[self->pose].duration;
        ret = 0;
    } else if (--self->poseTimer == 0) {
        self->pose++;
        if (self->anim[self->pose].duration == 0) {
            self->pose = self->anim[self->pose].pose;
            self->poseTimer = self->anim[self->pose].duration;
            ret = 0;
        } else if (self->anim[self->pose].duration == 0xFFFF) {
            self->pose--;
            self->poseTimer = -1;
            ret = -1;
        } else if (self->anim[self->pose].duration == 0xFFFE) {
            self->anim = frames[self->anim[self->pose].pose];
            self->pose = 0;
            self->poseTimer = self->anim[self->pose].duration;
            ret = -2;
        } else {
            self->poseTimer = self->anim[self->pose].duration;
        }
    }
    if (frameProps != NULL) {
        frameProps += ((self->anim[self->pose].pose >> 9) & 0x7F) * 4;
        self->hitboxOffX = *frameProps++;
        self->hitboxOffY = *frameProps++;
        self->hitboxWidth = *frameProps++;
        self->hitboxHeight = *frameProps++;
    }
    self->animCurFrame = self->anim[self->pose].pose & 0x1FF;
    if (self->unk0 != NULL) {
        func_060C1618();
    }
    return ret;
}

// SAT: func_060D11B8
s32 AccumulateTowardZero(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

// SAT: func_060D11DC
Entity* SearchForEntityInRange(s32 rangeIndex, s32 entityId) {
    s32 start = g_EntityRanges[rangeIndex * 2 + 0];
    s32 end = g_EntityRanges[rangeIndex * 2 + 1];
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; i <= end; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}

// SAT: func_060D1224
s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY) {
    s16 angle;
    s16 deltaY;
    s16 deltaX;

    deltaX = targetX - entity->posX.i.hi;
    deltaY = targetY - entity->posY.i.hi;
    angle = ratan2(-deltaY, deltaX) & 0xFFF;
    return angle;
}

// SAT: func_060D125C
s16 StepAngleTowards(s16 current, s16 target, s16 step) {
    s16 maxStep = ABS(target - current);
    if (step > maxStep) {
        step = maxStep;
    }

    if (target < current) {
        if (maxStep < 0x800) {
            target += step;
        } else {
            target -= step;
        }
    } else {
        if (maxStep < 0x800) {
            target -= step;
        } else {
            target += step;
        }
    }
    return target & 0xFFF;
}

// SAT: func_060D12AC
s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY) {
    s32 dx = targetX - entity->posX.i.hi;
    s32 dy = targetY - entity->posY.i.hi;

    return SquareRoot0(dx * dx + dy * dy);
}

// SAT: func_060D12DC
void ProcessSfxState(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        if (g_CutsceneHasControl) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        if (CdSoundCommandQueueEmpty()) {
            PlaySfx(SET_UNK_10);
            func_06010400();
            entity->step++;
        }
        break;
    case 1:
        if (func_80133950()) {
            entity->step++;
        }
        break;
    case 2:
        PlaySfx(entity->params);
        entity->step++;
        break;
    case 3:
        if (func_80131F68_2()) {
            entity->step++;
        }
        break;
    case 4:
        if (!func_80131F68_2()) {
            entity->step++;
        }
        break;
    case 5:
        if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        if (CdSoundCommandQueueEmpty()) {
            PlaySfx(SET_XA_PLAYBACK);
            entity->step++;
        }
        break;
    case 6:
        if (func_80133950()) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        break;
    case 7:
        PlaySfx(SET_UNK_80);
        entity->step = 4;
        break;
    case 8:
        g_PlaySfxStep = 99;
        DestroyEntity(entity);
        return;
    }
    g_PlaySfxStep = entity->step;
}

// SAT: func_060D141C
void ProcessEvent(Entity* self, bool resetEvent) {
    ServantEvent* evt;
    ServantEvent* queue;
    s32 cameraX;
    s32 cameraY;
    s32 i;

    if (resetEvent) {
        g_CurrentServant = g_CurrentRoomX = g_CurrentRoomY = 0;
        return;
    }

    cameraX = g_Tilemap.scrollX.i.hi;
    cameraY = g_Tilemap.scrollY.i.hi;
    if (g_CurrentServant != g_Servant || g_CurrentRoomX != g_Tilemap.left ||
        g_CurrentRoomY != g_Tilemap.top) {
        g_CurrentServant = g_Servant;
        g_CurrentRoomX = g_Tilemap.left;
        g_CurrentRoomY = g_Tilemap.top;
        queue = g_EventQueue;
        for (i = 1; g_Events[i].roomX != -1; i++) {
            evt = &g_Events[i];
            // Filter by familiar
            if (evt->servantId != -1 && evt->servantId != g_CurrentServant) {
                continue;
            }

            if (evt->roomX < 0) {
                if (!(DAT_0605d750.stageID & STAGE_INVERTEDCASTLE_FLAG)) {
                    continue;
                }
            } else {
                if (DAT_0605d750.stageID & STAGE_INVERTEDCASTLE_FLAG) {
                    continue;
                }
            }
            if (ABS(evt->roomX) != g_CurrentRoomX ||
                evt->roomY != g_CurrentRoomY) {
                continue;
            }

            if (evt->cameraX == cameraX && evt->cameraY == cameraY &&
                (evt->condition == -1 ||
                 (!(evt->condition & 0x80000000) ||
                  !g_CastleFlags[evt->condition & 0xFFFF]) &&
                     (!(evt->condition & 0x40000000) ||
                      !(g_Status.relics[evt->condition & 0xFFFF] & 1)))) {
                evt->timer = 0;
                if (evt->delay == 0) {
                    CreateEventEntity(self, evt->entityId, evt->params);
                    if (evt->unk2C) {
                        continue;
                    }
                }
            }
            if (evt->delay > 0) {
                evt->timer = evt->delay - 1;
            }
            queue->next = evt;
            queue = evt;
        }
        queue->next = NULL;
    } else {
        queue = g_EventQueue;
        while (queue->next != NULL) {
            if (queue->next->cameraX == cameraX &&
                queue->next->cameraY == cameraY &&
                (queue->next->condition == -1 ||
                 (!(queue->next->condition & 0x80000000) ||
                  !g_CastleFlags[queue->next->condition & 0xFFFF]) &&
                     (!(queue->next->condition & 0x40000000) ||
                      !(g_Status.relics[queue->next->condition & 0xFFFF] &
                        1)))) {
                if (queue->next->timer > 0) {
                    queue->next->timer--;
                } else {
                    CreateEventEntity(
                        self, queue->next->entityId, queue->next->params);
                    if (queue->next->unk2C) {
                        queue->next = queue->next->next;
                        continue;
                    } else {
                        queue->next->timer = queue->next->delay;
                    }
                }
            }
            queue = queue->next;
        }
    }
}

// SAT: func_060D1640
void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId;
        entity->zPriority = entityParent->zPriority;
        entity->facingLeft = entityParent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = entityParent->posX.val;
        entity->posY.val = entityParent->posY.val;
        // Not necessarily making batFamBlueTrail here, but
        // that's an Ext that works. Just needs parent at 0x8C.
        entity->ext.batFamBlueTrail.parent = entityParent;
        entity->params = params;
    }
}

// SAT: func_060D16D0
s32 IsMovementAllowed(s32 arg0) {
    if (PLAYER.velocityY < 0 && !(g_Player.vram_flag & TOUCHING_GROUND)) {
        return 1;
    }

    if (PLAYER.velocityY > 0 && !(g_Player.vram_flag & TOUCHING_CEILING)) {
        return 1;
    }

    if (PLAYER.velocityX < 0 && !(g_Player.vram_flag & TOUCHING_L_WALL))
        return 1;

    if (PLAYER.velocityX > 0 && !(g_Player.vram_flag & TOUCHING_R_WALL))
        return 1;

    if (arg0 == 0)
        return 0;

    if (g_Player.unk320 != PLAYER.step || PLAYER.step != Player_Stand)
        return 1;

    if (g_Player.unk322 != PLAYER.step_s)
        return 1;

    if (PLAYER.step_s != 0 && PLAYER.step_s != 4)
        return 1;
    return 0;
}

// SAT: func_060D1784
s32 CheckAllEntitiesValid(void) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 0x80; i++, entity++) {
        if (!entity->entityId)
            continue;
        if (entity->hitboxState == 0)
            continue;
        if (entity->flags & FLAG_UNK_00200000)
            continue;
        if (entity->posX.i.hi < -16)
            continue;
        if (entity->posX.i.hi > 336)
            continue;
        if (entity->posY.i.hi > 240)
            continue;
        if (entity->posY.i.hi < 0)
            continue;
        if (entity->hitPoints < 0x7000)
            return 1;
    }
    return 0;
}

// SAT: func_060D1808
s32 ServantUnk0(void) {
    if (DAT_0605d750.stageID >= 0x20 && DAT_0605d750.stageID < 0x35) {
        if (D_8003C708.flags == 0x22) {
            return 1;
        }
        if (D_8003C708.flags == FLAG_UNK_20) {
            return 0;
        }
        return 2;
    } else {
        if (D_8003C708.flags == 0x22) {
            return 0;
        }

        if (D_8003C708.flags == FLAG_UNK_20) {
            return 1;
        }
        return 2;
    }
}
