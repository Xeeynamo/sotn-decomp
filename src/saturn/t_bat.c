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

INCLUDE_ASM("asm/saturn/t_bat/data", d60CF000, d_060CF000);

extern BatAbilityValues g_BatAbilityStats[]; // 0x060D1D34
extern s32 s_IsServantDestroyed;             // 0x060D1DFC
extern u32 s_LastTargetedEntityIndex;        // 0x060D1E00
extern ServantEvent g_Events[];              // 0x060D1E04
extern s32 g_PlaySfxStep;                    // 0x060D2734
extern s16 g_EntityRanges[];                 // 0x060D2738
extern ServantEvent* g_EventQueue;           // 0x060D2740
extern u32 g_CurrentServant;                 // 0x060D2744
extern s32 g_CurrentRoomX;                   // 0x060D2748
extern s32 g_CurrentRoomY;                   // 0x060D274C
extern FamiliarStats s_BatStats;             // 0x060D2830
extern Point16 s_BatPathingPoints[4][0x10];  // 0x060D2840
extern s32 g_CutsceneHasControl;

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF2E8, func_060CF2E8);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF410, func_060CF410);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF5F4, func_060CF5F4);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF6B4, func_060CF6B4);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFB00, func_060CFB00);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFC48, func_060CFC48);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0490, func_060D0490);

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1070, func_060D1070);

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
