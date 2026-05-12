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

typedef struct {
    s32 level;
    s32 exp;
    s32 unk8; // Possibly the number of times loaded
} FamiliarStats;

INCLUDE_ASM("asm/saturn/t_bat/data", d60CF000, d_060CF000);

extern u32 s_LastTargetedEntityIndex; // 0x060D1E00
extern BatAbilityValues g_BatAbilityStats[]; // 0x060D1D34
extern FamiliarStats s_BatStats; // 0x060D2830

Entity* FindValidTarget(Entity *self) {
    #define ABS(x, y) (((x) - (y)) < 0 ? (y) - (x) : (x) - (y))
    s16 s_TargetMatch[0x80];

    const s32 EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity *entity;

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
        if (entity->flags & 0x200000) {
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
        if (entity->hitboxState & 8 && !g_BatAbilityStats[s_BatStats.level / 10].makeBadAttacks) {
            continue;
        }
        if (ABS(self->posX.i.hi, entity->posX.i.hi) < 64 &&
            ABS(self->posY.i.hi, entity->posY.i.hi) < 64) {
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
        if (entity->flags & 0x80000) {
            if (entity->hitPoints >= g_BatAbilityStats[s_BatStats.level / 10].minimumEnemyHp) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= 0x80000;
            return entity;
        }
    }
    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex = (foundIndex + 1) % EntitySearchCount;
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

void f60D0938() {}
void f60D0944() {}
void f60D0950() {}
void f60D095C() {}
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0968, func_060D0968);
void f60D0A4C() {}
void f60D0A58() {}
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0A64, func_060D0A64);
void f60D1010() {}
void f60D101C() {}
void f60D1028() {}
void f60D1034() {}

extern s32 s_IsServantDestroyed; // 0x060D1DFCh

void DestroyEntity(Entity*); // func_0600FFB8h

// PSX: func_80173C2C
// SAT: func_060D1040
void DestroyServantEntity(Entity* entity) {
    if (entity->params == 0xF) {
        s_IsServantDestroyed = 1;
    }
    func_0600FFB8(entity); // DestroyEntity
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1070, func_060D1070);

// PSX: TT_000:func_80173E78
// SAT: T_BAT:f_021B8 / func_060D11B8
s32 func_80173E78(s32 arg0, s32 arg1) {
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

// PSX: func_80173F30
// SAT: func_060D1224
s32 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 diffx = x - entity->posX.i.hi;
    // not the same implementation as ratan2
    return func_0600EE88(-(s16)(y - entity->posY.i.hi), diffx) &
           0xFFF; // was entity->posY.i.hi
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D125C, func_060D125C);

s32 func_0600F914(s32, s32);

// SAT: func_060D12AC
// PSX: func_80173FE8
s32 func_80173FE8(Entity* entity, s32 x, s32 y) {
    s32 diffX = x - entity->posX.i.hi;
    s32 diffY = y - entity->posY.i.hi;

    // not shifted by 12
    return func_0600F914((diffX * diffX + diffY * diffY),
                         diffX); // SquareRoot12
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D12DC, func_060D12DC);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D141C, func_060D141C);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1640, func_060D1640);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D16D0, func_060D16D0);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1784, func_060D1784);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1808, func_060D1808);
INCLUDE_ASM("asm/saturn/t_bat/data", d60D1858, d_060D1858);
