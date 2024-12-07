// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", func_psp_09100D70);

s16 GetStatusAilmentTimer(StatusAilments statusAilment, s16 timer) {
    s16 ret;
    s32 petrify_adjustment;

    switch (statusAilment) {
    case STATUS_AILMENT_POISON:
        ret = timer;
        ret -= (g_Status.statsTotal[STAT_CON] * 16);
        if (ret < 256) {
            ret = 256;
        }
        break;
    case STATUS_AILMENT_CURSE:
        ret = timer;
        ret -= (g_Status.statsTotal[STAT_CON] * 4);
        if (ret < 64) {
            ret = 64;
        }
        break;
    case STATUS_AILMENT_PETRIFIED:
        ret = timer;
        petrify_adjustment = (((rand() % 12) + g_Status.statsTotal[STAT_CON]) - 9) / 10;
        if (petrify_adjustment < 0) {
            petrify_adjustment = 0;
        }
        if (petrify_adjustment > 4) {
            petrify_adjustment = 4;
        }
        ret -= petrify_adjustment;
        break;
    case STATUS_AILMENT_DARK_METAMORPHOSIS:
        ret = timer;
        ret += (g_Status.statsTotal[STAT_INT] * 4);
        break;
    case STATUS_AILMENT_UNK04:
    case STATUS_AILMENT_UNK05:
        ret = timer;
        if (CheckEquipmentItemCount(ITEM_BWAKA_KNIFE, EQUIP_ACCESSORY) != 0) {
            ret += ret / 2;
        }
        break;
    }

    return ret;
}

bool CastSpell(SpellIds spellId) {
    s32 mpUsage = g_SpellDefs[spellId].mpUsage;

    if (g_Status.mp < mpUsage) {
        return false;
    } else {
        g_Status.mp -= mpUsage;
        return true;
    }
}

void LearnSpell(s32 spellId) {
    s32 i;

    if ((g_Status.spellsLearnt & (1 << spellId)) == 0) {
        g_Status.spellsLearnt |= 1 << spellId;
        for (i = 0; i < LEN(g_Status.spells); i++) {
            if (!g_Status.spells[i]) {
                g_Status.spells[i] = spellId | 0x80;
                return;
            }
        }
    }
}

// BSS
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 g_LevelHPIncrease[];

bool func_800FDD44(s32 itemType) {
    s32 equippedItem = g_Status.equipment[itemType];
    bool isConsumable = g_EquipDefs[equippedItem].isConsumable;

    if (CheckEquipmentItemCount(ITEM_DUPLICATOR, EQUIP_ACCESSORY)) {
        return false;
    }
    if (isConsumable) {
        if (!g_Status.equipHandCount[equippedItem]) {
            g_Status.equipment[itemType] = ITEM_EMPTY_HAND;
            func_800F53A4();
            return true;
        }
        g_Status.equipHandCount[equippedItem]--;
    }
    return false;
}

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

u32 CheckAndDoLevelUp(void) {
    s32 i;
    s32 statsGained;
    s32 statgain;

    if (D_80137960 != 0) {
        D_80137960 -= 1;
        return 3;
    }
    if (D_80137964 != 0) {
        D_80137964 -= 1;
        return 2;
    }
    if (D_80137968 != 0) {
        D_80137968 -= 1;
        return 4;
    }
    if (g_Status.level == 99) {
        return 0;
    }
    if (g_ExpNext[g_Status.level + 1] <= g_Status.exp) {
        g_Status.level++;
        g_Status.mpMax += 4 + (rand() & 1);
        g_Status.hp += g_LevelHPIncrease[(s32)g_Status.level / 10];
        g_Status.hpMax += g_LevelHPIncrease[(s32)g_Status.level / 10];
        g_Status.heartsMax += 2;
        // Run again, in case we have enough EXP to level up twice
        CheckAndDoLevelUp();
        statsGained = 0;
        for (i = 0; i < LEN(g_Status.statsBase); i++) {
            // Flip a coin to decide if you will gain a stat here
            statgain = rand() & 1;
            g_Status.statsBase[i] += statgain;

            if (g_Status.statsBase[i] > 99) {
                g_Status.statsBase[i] = 99;
                statgain = 0;
            }
            statsGained += statgain;
        }
        // If we gained less than 2 stats (got unlucky) give a mercy point to
        // random stat
        if (statsGained < 2) {
            // Note this is its own random event, so there's a chance to get +2
            // to one stat.
            i = rand() & 3;
            g_Status.statsBase[i]++;
            if (g_Status.statsBase[i] > 99) {
                g_Status.statsBase[i] = 99;
            }
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", func_800FE044);

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", IsRelicActive);

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", func_800FE3C4);

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", GetEquipProperties);

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", HasEnoughMp);

INCLUDE_ASM("dra_psp/psp/dra_psp/243F0", func_800FE8F0);