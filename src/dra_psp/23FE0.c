// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

// Appears to be start of a file, there is zero padding before this function.

u8* GetEquipOrder(EquipKind kind) {
    switch (kind) {
    case EQUIP_HAND:
        return g_Status.equipHandOrder;
    }
    return g_Status.equipBodyOrder;
}

u8* GetEquipCount(EquipKind kind) {
    switch (kind) {
    case EQUIP_HAND:
        return g_Status.equipHandCount;
    }
    return g_Status.equipBodyCount;
}

const char* GetEquipmentName(EquipKind kind, s32 equipId) {
    switch (kind) {
    case EQUIP_HAND:
        return g_EquipDefs[equipId].name;
    }
    // This can alternatively be made a Default case.
    return g_AccessoryDefs[equipId].name;
}

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    switch (equipType) {
    case 0:
        return (g_Status.equipment[LEFT_HAND_SLOT] == itemId) +
               (g_Status.equipment[RIGHT_HAND_SLOT] == itemId);
    case 1:
        return g_Status.equipment[HEAD_SLOT] == itemId;
    case 2:
        return g_Status.equipment[ARMOR_SLOT] == itemId;
    case 3:
        return g_Status.equipment[CAPE_SLOT] == itemId;
    case 4:
        return (g_Status.equipment[ACCESSORY_1_SLOT] == itemId) +
               (g_Status.equipment[ACCESSORY_2_SLOT] == itemId);
    }
    // seems to require missing return
}

void AddToInventory(u16 id, EquipKind kind) {
    s32 i;
    EquipKind found;
    u8* order;
    u8* count;
    u8* pOrder;
    s32 existingItemSlot;
    s32 emptySlot;

    order = GetEquipOrder(kind);
    count = GetEquipCount(kind);
    if (count[id] >= 99) {
        return;
    }
    // Increment the count of the item.
    count[id]++;
    // If the amount we now have is not 1, then we already had one (or more).
    // Done.
    if (count[id] != 1) {
        return;
    }
    // If the amount we now have IS 1, then change it back to 0 and do more
    // processing.
    count[id]--;
    // If it's not a hand item, then figure out what equipType it is.
    if (kind != EQUIP_HAND) {
        found = g_AccessoryDefs[id].equipType;
    }

    pOrder = order;
    // Odd way to write this loop, this is the only way that works on all
    // systems.
    for (i = 0; true;) {
        if (*pOrder == id) {
            existingItemSlot = i;
            break;
        }
        i++;
        pOrder++;
    }

    pOrder = order;
    for (i = 0; true; i++, pOrder++) {
        if (count[*pOrder]) {
            continue;
        }
        if (kind == EQUIP_HAND || found == g_AccessoryDefs[*pOrder].equipType) {
            emptySlot = i;
            break;
        }
    }

    count[id]++;
    if (emptySlot < existingItemSlot) {
        order[existingItemSlot] = order[emptySlot];
        order[emptySlot] = id;
    }
}

void GetSpellDef(SpellDef* spell, s32 id) {
    *spell = g_SpellDefs[id];
    spell->attack += (g_Status.statsTotal[STAT_INT] * 2 + (rand() % 12)) / 10;
    if (CheckEquipmentItemCount(ITEM_MOJO_MAIL, EQUIP_ARMOR) != 0) {
        spell->attack += spell->attack / 2;
    }
}

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
        petrify_adjustment =
            (((rand() % 12) + g_Status.statsTotal[STAT_CON]) - 9) / 10;
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

s32 func_800FE044(s32 amount, s32 type) {
    s32 oldHPMax; // unused
    s32 oldHeartMax;
    s32 activeFamiliar;
    s32 levelDiff;
    s32 i;
    u32 playerXPBoost;

    // Life Max Up
    if (type == 0x8000) {
        if (g_Status.hpMax == 9999) {
            return 1;
        }
        oldHPMax = g_Status.hpMax;
        g_Status.hpMax += amount;
        if (g_Status.hpMax > 9999) {
            g_Status.hpMax = 9999;
        }
        if (g_PlayableCharacter != 0) {
            g_Status.hpMax += amount;
            if (g_Status.hpMax > 9999) {
                g_Status.hpMax = 9999;
            }
        }
        g_Status.hp = g_Status.hpMax;
        D_80137960++;
        return 0;
    }

    // Heart Max Up
    if (type == 0x4000) {
        if (g_PlayableCharacter != 0) {
            return 1;
        }
        oldHeartMax = g_Status.heartsMax;
        if (g_Status.heartsMax == 9999) {
            return 1;
        }
        g_Status.heartsMax += amount;
        if (g_Status.heartsMax > 9999) {
            g_Status.heartsMax = 9999;
        }
        g_Status.hearts += (g_Status.heartsMax - oldHeartMax);
        D_80137964++;
        return 0;
    }

    // Collect a relic. "amount" here isn't an amount, it's the relic ID.
    if (type == 0x2000) {
        g_Status.relics[amount] = 3;
        if (g_RelicDefs[amount].unk0C) {
            g_Status.relics[amount] = 1;
        }
        D_80137968++;
        return 0;
    }

    // Gain XP from defeating enemy
    if (amount != 0 && g_Status.level != 99) {
        playerXPBoost = amount;
        // from here on, "type" is really the enemy's level
        if ((s32)g_Status.level > type) {
            levelDiff = g_Status.level - type;
            for (i = 0; i < levelDiff; i++) {
                playerXPBoost = playerXPBoost * 2 / 3;
            }
            if (playerXPBoost == 0) {
                playerXPBoost = 1;
            }
        }
        if ((s32)g_Status.level < type) {
            levelDiff = type - g_Status.level;
            if (levelDiff > 5) {
                levelDiff = 5;
            }
            for (i = 0; i < levelDiff; i++) {
                playerXPBoost += playerXPBoost / 4;
            }
        }
        g_Status.exp += playerXPBoost;
        if (g_ExpNext[99] <= g_Status.exp) {
            g_Status.exp = g_ExpNext[99];
        }

        if (g_Servant == 0) {
            return;
        }
        activeFamiliar = g_Servant - 1;
        playerXPBoost =
            (amount / g_Status.statsFamiliars[activeFamiliar].level);
        // Here we reuse i to keep track of how much xp the familiar gains.
        i = 0;
        while (playerXPBoost != 0) {
            i++;
            playerXPBoost >>= 1;
        }
#if defined(VERSION_HD)
        i -= 2;
#endif
        if (i <= 0) {
            i = 1;
        }
        g_Status.statsFamiliars[activeFamiliar].exp += i;
        if (g_Status.statsFamiliars[activeFamiliar].exp > 9899) {
            g_Status.statsFamiliars[activeFamiliar].exp = 9899;
        }
        g_Status.statsFamiliars[activeFamiliar].level =
            (g_Status.statsFamiliars[activeFamiliar].exp / 100) + 1;
    }
}

bool IsRelicActive(RelicIds relicId) {
    if (g_Status.relics[relicId] & RELIC_FLAG_ACTIVE) {
        return 1;
    }
    return 0;
}

s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts) {
    u32 accessoryCount;

    if (subweaponId == 0) {
        *subwpn = g_SubwpnDefs[g_Status.subWeapon];
        accessoryCount =
            CheckEquipmentItemCount(ITEM_HEART_BROACH, EQUIP_ACCESSORY);
        if (accessoryCount == 1) {
            subwpn->heartCost /= 2;
        }
        if (accessoryCount == 2) {
            subwpn->heartCost /= 3;
        }
        if (subwpn->heartCost <= 0) {
            subwpn->heartCost = 1;
        }
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        } else {
            return 0;
        }
    } else {
        *subwpn = g_SubwpnDefs[subweaponId];
        if (CheckEquipmentItemCount(ITEM_BRILLIANT_MAIL, EQUIP_ARMOR) != 0) {
            subwpn->attack += 10;
        }
#if defined(VERSION_US)
        if (subweaponId == 4 || subweaponId == 12) {
#elif defined(VERSION_HD) || defined(VERSION_PSP)
        if (subweaponId == 4) {
#endif
            accessoryCount =
                CheckEquipmentItemCount(ITEM_STAUROLITE, EQUIP_ACCESSORY);
            if (accessoryCount == 1) {
                subwpn->attack *= 2;
            }
            if (accessoryCount == 2) {
                subwpn->attack *= 3;
            }
        }
        subwpn->attack += ((g_Status.statsTotal[2] * 2) + (rand() % 12)) / 10;
        return subweaponId;
    }
}

void GetEquipProperties(s32 handId, Equipment* res, s32 equipId) {
    s32 criticalRate;
    u8 itemCategory;

    *res = g_EquipDefs[equipId];
    criticalRate = res->criticalRate;
    criticalRate +=
        SquareRoot0((g_Status.statsTotal[STAT_LCK] * 2) + (rand() & 0xF)) - 5;
    if (criticalRate > 255) {
        criticalRate = 255;
    }
    if (criticalRate < 0) {
        criticalRate = 0;
    }
    if (g_StageId == STAGE_ST0) {
        criticalRate = 0;
    }

    res->criticalRate = criticalRate;
    func_800F4994();
    itemCategory = g_EquipDefs[equipId].itemCategory;
    if (itemCategory == ITEM_FOOD || itemCategory == ITEM_MEDICINE) {
        return;
    }
    res->attack = CalcAttack(equipId, g_Status.equipment[1 - handId]);
    if (g_Player.status & PLAYER_STATUS_POISON) {
        res->attack >>= 1;
    }
}

bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (mpCount <= g_Status.mp) {
        if (subtractMp) {
            g_Status.mp -= mpCount;
        }
        return false;
    }
    return true;
}

void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

void AddHearts(s32 value) {
    Entity* player;
    if (g_Status.hearts < g_Status.heartsMax) {
        g_Status.hearts += value;
        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
        // Creates a heart rising from the player, which flickers away
        player = &PLAYER;
        CreateEntFactoryFromEntity(player, FACTORY(99, 0), 0);
        PlaySfx(SFX_HEART_PICKUP);
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_091020A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09102800);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09102898);