// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

typedef struct {
    s32 delayFrames;
    s32 angleStep;
    s32 additionalBatCount;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
} BatAbilityValues;

extern AnimationFrame g_DefaultBatAnimationFrame[];       // 0x060D1B84
extern AnimationFrame g_BatCloseToTargetAnimationFrame[]; // 0x060D1C28
extern AnimationFrame g_BatHighVelocityAnimationFrame[];  // 0x060D1CC8
extern AnimationFrame* g_BatAnimationFrames[];            // 0x060D1CD0
extern s16 g_BatSpriteData[4][10];                        // 0x060D1CE4
extern BatAbilityValues g_BatAbilityStats[];              // 0x060D1D34
extern s32 s_IsServantDestroyed;                          // 0x060D1DFC
extern u32 s_LastTargetedEntityIndex;                     // 0x060D1E00
extern ServantEvent g_Events[];                           // 0x060D1E04
extern s32 g_PlaySfxStep;                                 // 0x060D2734
extern s16 g_EntityRanges[];                              // 0x060D2738
extern ServantEvent* g_EventQueue;                        // 0x060D2740
extern u32 g_CurrentServant;                              // 0x060D2744
extern s32 g_CurrentRoomX;                                // 0x060D2748
extern s32 g_CurrentRoomY;                                // 0x060D274C
extern s16 DAT_060d2750;                                  // 0x060D2750
extern s16 DAT_060d2752;                                  // 0x060D2752
extern FamiliarStats s_BatStats;                          // 0x060D2830
extern Point16 s_BatPathingPoints[4][0x10];               // 0x060D2840
extern s32 g_CutsceneHasControl;

INCLUDE_ASM("asm/saturn/t_bat/data", d60CF000, d_060CF000);

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

void CreateAdditionalBats(s32 amount, s32 entityId);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF2E8, func_060CF2E8);

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
    prim->x0 = x - g_BatSpriteData[frame][0];
    prim->y0 = y - g_BatSpriteData[frame][1];
}

void SwitchModeInitialize(Entity* self);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF6B4, func_060CF6B4);

// ServantInit
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFB00, func_060CFB00);

// UpdateServantDefault
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFC48, func_060CFC48);

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
        DAT_060d2750 = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        DAT_060d2752 = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        distance = DAT_060d2750 * DAT_060d2750 + DAT_060d2752 * DAT_060d2752;
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
            s_BatPathingPoints[self->ext.bat.batIndex][0].y = rand() & 0xFF;
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

// func_060D1070
u32 ServantUpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    s32 ret = 0;

    if (self->poseTimer == -1) {
        ret = -1;
    } else if (self->poseTimer == 0) {
        self->poseTimer = self->anim[self->pose].duration;
    } else if (--self->poseTimer == 0) {
        self->pose++;
        if (self->anim[self->pose].duration == 0) {
            self->pose = self->anim[self->pose].pose;
            self->poseTimer = self->anim[self->pose].duration;
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
        frameProps += (self->anim[self->pose].pose >> 9) * 4;
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
            PlaySfx(0xF0000010);
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
        if (func_80131F68()) {
            entity->step++;
        }
        break;
    case 4:
        if (!func_80131F68()) {
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
            PlaySfx(0xF0000011);
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
        PlaySfx(0xF0000080);
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
                if (!(g_StageId & 0x20)) {
                    continue;
                }
            } else {
                if (g_StageId & 0x20) {
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
    if (g_StageId >= 0x20 && g_StageId < 0x35) {
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

INCLUDE_ASM("asm/saturn/t_bat/data", d60D1858, d_060D1858);
