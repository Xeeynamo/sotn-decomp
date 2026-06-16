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

extern u32 s_LastTargetedEntityIndex;        // 0x060D1E00
extern BatAbilityValues g_BatAbilityStats[]; // 0x060D1D34
extern s32 s_IsServantDestroyed;             // 0x060D1DFC
extern FamiliarStats s_BatStats;             // 0x060D2830

extern s32 g_CutsceneHasControl;
extern s32 g_PlaySfxStep;

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0968, func_060D0968);

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D11DC, func_060D11DC);

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D125C, func_060D125C);

// SAT: func_060D12AC
s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY) {
    s32 dx = targetX - entity->posX.i.hi;
    s32 dy = targetY - entity->posY.i.hi;

    return SquareRoot0(dx * dx + dy * dy);
}

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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D141C, func_060D141C);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1640, func_060D1640);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D16D0, func_060D16D0);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1784, func_060D1784);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1808, func_060D1808);
INCLUDE_ASM("asm/saturn/t_bat/data", d60D1858, d_060D1858);
