// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

s32 g_LevelHPIncrease[] = {1, 3, 6, 10, 20, 30, 40, 50, 100, 200};

#define HUD_NUM_SPRITES 14
u8 g_HudSpriteX[HUD_NUM_SPRITES] = {
    90, 90, 90, 34, 2, 31, 3, 9, 15, 21, 59, 63, 67, 71,
};
u8 g_HudSpriteY[HUD_NUM_SPRITES] = {
    25, 25, 25, 22, 19, 26, 33, 33, 33, 33, 34, 34, 34, 34,
};
u8 g_HudSpriteU[HUD_NUM_SPRITES] = {
    0x00, 0x10, 0x68, 0x20, 0x00, 0x70, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 g_HudSpriteV[HUD_NUM_SPRITES] = {
    0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x18, 0x18, 0x18,
};
u8 g_HudSpriteW[HUD_NUM_SPRITES] = {
    16, 16, 8, 72, 32, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
u8 g_HudSpriteH[HUD_NUM_SPRITES] = {
    16, 16, 8, 24, 32, 56, 16, 16, 16, 16, 8, 8, 8, 8,
};
u16 g_HudSpriteClut[HUD_NUM_SPRITES] = {
    0x0173, 0x0175, 0x0170, 0x0172, 0x0171, 0x0174, 0x0171,
    0x0171, 0x0171, 0x0171, 0x0196, 0x0196, 0x0196, 0x0196,
};
u16 g_HudSpriteBlend[HUD_NUM_SPRITES] = {
    DRAW_HIDE, DRAW_HIDE, DRAW_HIDE, 0x2000, 0x2000, 0x2000, 0x2000,
    0x2000,    0x2000,    0x2000,    0x2000, 0x2000, 0x2000, 0x2000,
};
s16 g_HudSubwpnSpriteClut[HUD_NUM_SPRITES] = {
    0x0175, 0x0176, 0x0175, 0x0176, 0x0175, 0x0176, 0x0175,
    0x0176, 0x0176, 0x0175, 0x0176, 0x0175, 0x0176, 0x0175,
};
u8 g_HudSubwpnSpriteU[HUD_NUM_SPRITES] = {
    0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20,
    0x20, 0x20, 0x20, 0x10, 0x10, 0x00, 0x00};
u8 g_HudSubwpnSpriteV[HUD_NUM_SPRITES] = {
    0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};

#define CAPE_PAL_TERMINATOR -1
s32 g_CapePaletteDefs[] = {
    ITEM_NO_CAPE,        0x409, ITEM_CLOTH_CAPE,     0x412,
    ITEM_REVERSE_CLOAK,  0x40B, ITEM_ELVEN_CLOAK,    0x40E,
    ITEM_CRYSTAL_CLOAK,  0x410, ITEM_ROYAL_CLOAK,    0x40D,
    ITEM_BLOOD_CLOAK,    0x40F, ITEM_JOSEPHS_CLOAK,  0x411,
    ITEM_TWILIGHT_CLOAK, 0x40A, CAPE_PAL_TERMINATOR, 0x409,
};

// BSS
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern PlayerHud g_PlayerHud;
extern s32 g_HealingMailTimer[1]; // maybe part of g_PlayerHud

bool CalcPlayerDamage(DamageParam* damage) {
    if (damage->damageKind != 5) {
        if (damage->damageKind >= 16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if (g_Status.hpMax >= (damage->damageTaken * 20)) {
            damage->damageKind = 3;
        } else {
            damage->damageKind = 2;
        }
    }
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        return true;
    }
    g_Status.hp -= damage->damageTaken;
    return false;
}

s32 func_800FD664(s32 arg0) {
    return g_StageId & STAGE_INVERTEDCASTLE_FLAG ? arg0 << 1 : arg0;
}

ItemCategory GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}

s32 func_800FD6C4(s32 equipTypeFilter) {
    s32 itemCount;
    s32 equipType;
    s32 i;

    switch (equipTypeFilter) {
    case EQUIP_HAND:
        return NUM_HAND_ITEMS;
    case EQUIP_HEAD:
        equipType = EQUIP_HEAD - 1;
        break;
    case EQUIP_ARMOR:
        equipType = EQUIP_ARMOR - 1;
        break;
    case EQUIP_CAPE:
        equipType = EQUIP_CAPE - 1;
        break;
    case EQUIP_ACCESSORY:
        equipType = EQUIP_ACCESSORY - 1;
        break;
    }

    for (itemCount = 0, i = 0; i < NUM_BODY_ITEMS; i++) {
        if (g_AccessoryDefs[i].equipType == equipType) {
            itemCount++;
        }
    }
    return itemCount;
}

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
    if (g_Status.hearts < g_Status.heartsMax) {
        g_Status.hearts += value;
        if (g_Status.heartsMax < g_Status.hearts) {
            g_Status.hearts = g_Status.heartsMax;
        }
        // Creates a heart rising from the player, which flickers away
        CreateEntFactoryFromEntity(&PLAYER, FACTORY(99, 0), 0);
        PlaySfx(SFX_HEART_PICKUP);
    }
}

// Note: Arg3 is unused, but is given in the call from func_80113D7C
s32 HandleDamage(DamageParam* damage, s32 arg1, s32 amount, s32 arg3) {
    s32 ret;
    s32 itemCount;

    func_800F53A4();
    damage->effects = arg1 & ~0x1F;
    damage->damageKind = arg1 & 0x1F;
    if (g_Status.defenseElement & damage->effects) {
        amount *= 2;
    }
    if (g_Status.D_80097C2A & damage->effects) {
        amount /= 2;
    }
    if (g_Status.D_80097C2C & damage->effects) {
        if (!(g_Status.D_80097C2C & damage->effects & EFFECT_UNK_0200)) {
            return 0;
        }
        damage->effects &= ~EFFECT_UNK_0200;
    }

    if (g_Status.D_80097C2E & damage->effects) {
        if (amount < 1) {
            amount = 1;
        }
        damage->unkC = amount;
        if (g_Status.hp != g_Status.hpMax) {
            func_800FE8F0();
            g_Status.hp += damage->unkC;
            if (g_Status.hpMax < g_Status.hp) {
                g_Status.hp = g_Status.hpMax;
            }
        }
        return 5;
    }
    // Player wearing cat-eye circlet. Same as above if-statement but
    //  with arg2 doubled. Item description says "Big HP restore" so makes
    //  sense
    if (CheckEquipmentItemCount(ITEM_CAT_EYE_CIRCLET, EQUIP_HEAD) != 0 &&
        damage->damageKind == 7) {
        amount *= 2;
        if (amount < 1) {
            amount = 1;
        }
        damage->unkC = amount;
        if (g_Status.hp != g_Status.hpMax) {
            func_800FE8F0();
            g_Status.hp += damage->unkC;
            if (g_Status.hpMax < g_Status.hp) {
                g_Status.hp = g_Status.hpMax;
            }
        }
        return 5;
    }

    // Very strange to have ballroom mask check. This item is not known to
    // have special behavior. Also, not possible to equip two. This may be
    // a new discovery of a property of the item. Worth further analysis.
    itemCount = CheckEquipmentItemCount(ITEM_BALLROOM_MASK, EQUIP_HEAD);
    if (itemCount != 0 &&
        (damage->effects &
         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
          EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0100 |
          EFFECT_SOLID_FROM_BELOW))) {
        if (itemCount == 1) {
            amount -= amount / 5;
        }
        if (itemCount == 2) {
            amount -= amount / 3;
        }
    }
    if (g_Player.status & PLAYER_STATUS_STONE) {
        damage->damageTaken = g_Status.hpMax / 8;
        ret = 8;
    } else if (damage->effects & EFFECT_UNK_0200) {
        damage->damageTaken = amount - (g_Status.defenseEquip * 2);
        if (damage->damageTaken <= 0) {
            damage->damageTaken = 0;
        }
        ret = 7;
    } else if (damage->damageKind == 6) {
        if (g_GameTimer % 10 == 0) {
            damage->damageTaken = 1;
        } else {
            damage->damageTaken = 0;
        }
        ret = 9;
    } else {
        if (damage->damageKind < 16) {
            damage->damageTaken = amount - g_Status.defenseEquip;
        } else {
            damage->damageTaken = g_Status.hpMax / 8;
        }
        if (g_Player.status & PLAYER_STATUS_POISON) {
            damage->damageTaken *= 2;
        }
        // Check for player wearing a Talisman (chance to dodge attack)
        itemCount = CheckEquipmentItemCount(ITEM_TALISMAN, EQUIP_ACCESSORY);
        if (itemCount != 0) {
            if (itemCount * g_Status.statsTotal[STAT_LCK] >= (rand() & 511)) {
                return 2;
            }
        }
        if (damage->damageTaken > 0) {
            if (damage->damageKind < 2) {
                if ((damage->damageTaken * 2) >= g_Status.hpMax) {
                    damage->damageKind = 4;
                } else if (amount * 50 >= g_Status.hpMax) {
                    damage->damageKind = 3;
                } else {
                    damage->damageKind = 2;
                }
            }
            ret = 3;
        } else {
            if (g_Status.defenseEquip > 99 &&
                !(damage->effects &
                  (EFFECT_UNK_0100 | EFFECT_SOLID_FROM_BELOW)) &&
                !(g_Player.status & PLAYER_STATUS_STONE)) {
                damage->damageKind = 0;
                ret = 1;
            } else {
                damage->damageKind = 2;
                ret = 3;
            }
            damage->damageTaken = 1;
        }
    }

    // If our HP is less than the damage, we die.
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        if (ret == 7) {
            return 7;
        }
        if (ret == 9) {
            ret = 6;
        } else {
            ret = 4;
        }
    } else {
        if (ret != 9) {
            func_800FE8F0();
        }
        // Here is where we actually take the damage away.
        g_Status.hp -= damage->damageTaken;
        // Blood cloak gives hearts when damage is taken
        if ((CheckEquipmentItemCount(ITEM_BLOOD_CLOAK, EQUIP_CAPE) != 0) &&
            (ret != 9)) {
            AddHearts(damage->damageTaken);
        }
        // Fury Plate "DEF goes up when damage taken", that logic is not here
        // though.
        if (CheckEquipmentItemCount(ITEM_FURY_PLATE, EQUIP_ARMOR) != 0) {
            if (D_80139828[0] < 0x200) {
                D_80139828[0] = 0x200;
            }
        }
    }
    return ret;
}

// !FAKE: explicitly casting two pointers to s32
// before comparing them, that's weird
void func_800FEE6C(void) {
    s32* p = D_80139828;
    do {
        if (*p) {
            (*p)--;
        }
        p++;
    } while ((long long)p < (long long)(D_80139828 + LEN(D_80139828)));
}

s32 HandleTransformationMP(TransformationForm form, CallMode mode) {
    if (form == FORM_BAT) {
        if (!IsRelicActive(RELIC_SOUL_OF_BAT)) {
            return -1;
        }
        if (g_Status.mp - 1 <= 0) {
            return -1;
        }
        if (mode == CHECK_ONLY) {
            return 0;
        }
        if (g_GameTimer % 60 == 0) {
            g_Status.mp -= 1;
        }
        return 0;
    } else if (form == FORM_MIST) {
        if (!IsRelicActive(RELIC_FORM_OF_MIST)) {
            return -1;
        }
        if (IsRelicActive(RELIC_POWER_OF_MIST)) {
            if (g_Status.mp - 2 <= 0) {
                return -1;
            }
            if (mode == CHECK_ONLY) {
                return 0;
            }
            if (g_GameTimer % 30 == 0) {
                g_Status.mp -= 2;
            }
        } else {
            if (g_Status.mp - 10 <= 0) {
                return -1;
            }
            if (mode == CHECK_ONLY) {
                return 0;
            }
            if (!(g_GameTimer & 7)) {
                g_Status.mp -= 10;
            }
        }
        return 0;
    } else if (form == FORM_WOLF) {
        if (IsRelicActive(RELIC_SOUL_OF_WOLF) == false) {
            return -1;
        }
        if (g_Status.mp - 1 > 0) {
            if (mode != CHECK_ONLY) {
                if (g_GameTimer % 120 == 0) {
                    g_Status.mp -= 1;
                }
            }
            return 0;
        }
        return -1;
    }
}

bool HandleGravityBootsMP(CallMode mode) {
    if ((g_Status.mp - 4) > 0) {
        if (mode != CHECK_ONLY) {
            g_Status.mp -= 4;
        }
        return 0;
    }
    return -1;
}

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

void func_800FF0B8(void) {
    s32 i;

    for (i = 0; i < LEN(D_80139828); i++) {
        func_800FF0A0(i);
    }
}

void func_800FF0F4(s32 arg0) { D_80139828[arg0] = 0x1000; }

s32 func_800FF110(s32 arg0) { return D_80139828[arg0]; }

u16 DealDamage(Entity* enemyEntity, Entity* attackerEntity) {
    s32 stats[4];
    EnemyDef sp20;
    EnemyDef* enemy;
    u16 temp_v1;
    u16 elementMask;
    s32 highestStatIdx;
    s32 i;
    u16 element;
    u16 damage;
    u16 result;
    u16 stuff;

    enemy = &sp20;
    sp20 = g_EnemyDefs[enemyEntity->enemyId];
    if (CheckEquipmentItemCount(ITEM_DRAGON_HELM, EQUIP_HEAD) != 0) {
        enemy->defense /= 2;
    }

    element = attackerEntity->attackElement;
    damage = attackerEntity->attack;
    if (element == 0) {
        element = 0x20;
    }
    if (element & 0xFF80) {
        elementMask = 0xFF80;
    } else {
        elementMask = 0x7F;
    }

    result = 0;
    temp_v1 = element & elementMask;
    if (temp_v1 == (temp_v1 & (elementMask & enemy->immunes))) {
        result = DAMAGE_FLAG_IMMUNE;
    } else if (temp_v1 == (temp_v1 & (elementMask & enemy->absorbs))) {
        result = damage + DAMAGE_FLAG_ABSORB;
    } else {
        if (temp_v1 == (temp_v1 & (elementMask & enemy->strengths))) {
            damage /= 2;
        }
        if (element & enemy->weaknesses) {
            damage *= 2;
        }
        if (attackerEntity->entityRoomIndex > (rand() & 0xFF)) {
            for (i = 0; i < 4; i++) {
                stats[i] = (rand() & 0x3F) + g_Status.statsBase[i];
            }

            highestStatIdx = 0;
            for (i = 1; i < 4; i++) {
                if (stats[i] > stats[highestStatIdx]) {
                    highestStatIdx = i;
                }
            }

            switch (highestStatIdx) {
            case STAT_STR:
                damage *= 2;
                break;
            case STAT_CON:
                if (enemy->defense > damage) {
                    damage += enemy->defense / 2;
                } else {
                    damage += damage / 2;
                }
                break;
            case STAT_INT:
                damage += SquareRoot0(g_RoomCount);
                break;
            case STAT_LCK:
#if defined(VERSION_US)
                damage += (rand() % g_Status.statsTotal[STAT_LCK]) + 1;
#elif defined(VERSION_HD)
                damage += (rand() % g_Status.statsTotal[STAT_LCK]);
#endif
                break;
            }
            result = DAMAGE_FLAG_CRITICAL;
        } else {
            result = DAMAGE_FLAG_NORMAL;
        }

        if (damage > enemy->defense) {
            damage = damage - enemy->defense;
        } else {
            damage = 1;
        }

        if (damage < 0 || damage >= 10000) {
            damage = 9999;
        }

        result += damage;
    }

    return result;
}

s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((u32)(arg0 * g_Status.statsTotal[STAT_LCK]) >> 7);
}

// Determine what type of item to drop
s32 func_800FF494(EnemyDef* arg0) {
    /* Ring of Arcana is an item that increases
     * enemy item drop rates when equipped
     */
    s32 ringOfArcanaCount =
        CheckEquipmentItemCount(ITEM_RING_OF_ARCANA, EQUIP_ACCESSORY);
    s32 rnd = rand() & 0xFF;

    rnd -= ((rand() & 0x1F) + g_Status.statsTotal[3]) / 20;

    if (ringOfArcanaCount != 0) {
        rnd -= arg0->rareItemDropRate * ringOfArcanaCount;
    }

    if (rnd < arg0->rareItemDropRate) {
        return 0x40; // drop the enemy's rare item
    } else {
        // drop a common item, typically hearts or money
        rnd -= arg0->rareItemDropRate;
        if (ringOfArcanaCount != 0) {
            rnd -= arg0->uncommonItemDropRate * ringOfArcanaCount;
        }
        rnd -= ((rand() & 0x1F) + g_Status.statsTotal[3]) / 20;

        if (rnd >= arg0->uncommonItemDropRate) {
            rnd = rand() % 28;
            if (arg0->rareItemDropRate == 0) {
                rnd++;
            }
            if (arg0->uncommonItemDropRate == 0) {
                rnd++;
            }
            return rnd + ringOfArcanaCount;
        } else {
            return 0x20; // drop the enemy's uncommon item
        }
    }
}

void UpdateCapePalette(void) {
    s32 clut;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (g_Status.equipment[CAPE_SLOT] == g_CapePaletteDefs[i]) {
            break;
        }

        if (g_CapePaletteDefs[i] == CAPE_PAL_TERMINATOR) {
            break;
        }
        i += 2;
    }

    clut = g_CapePaletteDefs[i + 1];
    if (g_Status.equipment[CAPE_SLOT] == ITEM_REVERSE_CLOAK &&
        g_Settings.isCloakLiningReversed) {
        clut++;
    }

    func_800EA5E4(clut);
    if (g_Status.equipment[CAPE_SLOT] == ITEM_TWILIGHT_CLOAK) {
        func_800EA5E4(0x415);
    }
}

void RefreshCapePalette(void) {
    if (g_StageId != STAGE_ST0 && g_PlayableCharacter == PLAYER_ALUCARD) {
        UpdateCapePalette();
    }
}

void func_800FF708(s32 equipType, s32 arg1) {
    s32 rnd;

    do {
    loop_1:
        rnd = rand() % 90;
        while (rnd == 0x19) {
            goto loop_1;
        }
    } while (g_AccessoryDefs[rnd].equipType != equipType);
    g_Status.equipment[arg1 + 2] = rnd;
}

const char g_CheatLuckCode[] = {"x-x!v''q"};
const char g_CheatAxearmorCode[] = {"axearmor"};
const char* g_CheatCodes[] = {g_CheatLuckCode, g_CheatAxearmorCode};
void InitStatsAndGear(bool isDeathTakingItems) {
    s32 prologueBonusState;
    s32 dracDefeatTime;
    u8* fileName;
    s32 equipId;
    s32 i;

    if (D_8003C730 != 0) {
        func_800F53A4();
        UpdateCapePalette();
        return;
    }

    if (isDeathTakingItems == true) {
        if (g_Status.equipment[LEFT_HAND_SLOT] == ITEM_ALUCARD_SWORD) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_EMPTY_HAND;
        } else if (g_Status.equipment[RIGHT_HAND_SLOT] == ITEM_ALUCARD_SWORD) {
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_EMPTY_HAND;
        } else if (g_Status.equipHandCount[ITEM_ALUCARD_SWORD] != 0) {
            g_Status.equipHandCount[ITEM_ALUCARD_SWORD]--;
        }

        if (g_Status.equipment[LEFT_HAND_SLOT] == ITEM_ALUCARD_SHIELD) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_EMPTY_HAND;
        } else if (g_Status.equipment[RIGHT_HAND_SLOT] == ITEM_ALUCARD_SHIELD) {
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_EMPTY_HAND;
        } else if (g_Status.equipHandCount[ITEM_ALUCARD_SHIELD] != 0) {
            g_Status.equipHandCount[ITEM_ALUCARD_SHIELD]--;
        }

        if (g_Status.equipment[HEAD_SLOT] == ITEM_DRAGON_HELM) {
            g_Status.equipment[HEAD_SLOT] = ITEM_EMPTY_HEAD;
        } else if (g_Status.equipBodyCount[ITEM_DRAGON_HELM] != 0) {
            g_Status.equipBodyCount[ITEM_DRAGON_HELM]--;
        }

        if (g_Status.equipment[ARMOR_SLOT] == ITEM_ALUCARD_MAIL) {
            g_Status.equipment[ARMOR_SLOT] = ITEM_NO_ARMOR;
        } else if (g_Status.equipBodyCount[ITEM_ALUCARD_MAIL] != 0) {
            g_Status.equipBodyCount[ITEM_ALUCARD_MAIL]--;
        }

        if (g_Status.equipment[CAPE_SLOT] == ITEM_TWILIGHT_CLOAK) {
            g_Status.equipment[CAPE_SLOT] = ITEM_NO_CAPE;
            UpdateCapePalette();
        } else if (g_Status.equipBodyCount[ITEM_TWILIGHT_CLOAK] != 0) {
            g_Status.equipBodyCount[ITEM_TWILIGHT_CLOAK]--;
        }

        if (g_Status.equipment[ACCESSORY_1_SLOT] == ITEM_NECKLACE_OF_J) {
            g_Status.equipment[ACCESSORY_1_SLOT] = ITEM_NO_ACCESSORY;
        } else if (g_Status.equipment[ACCESSORY_2_SLOT] == ITEM_NECKLACE_OF_J) {
            g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_NO_ACCESSORY;
        } else if (g_Status.equipBodyCount[ITEM_NECKLACE_OF_J] != 0) {
            g_Status.equipBodyCount[ITEM_NECKLACE_OF_J]--;
        }
    } else {
        // I think this zeros out all the rooms to mark as unvisited
        for (i = 0; i < 2048; i++) {
            g_CastleMap[i] = 0;
        }
        g_RoomCount = 0;

        g_Status.D_80097BF8 = 0;
        for (i = 0; i < 4; i++) {
            g_Status.statsEquip[i] = 0;
        }

        g_Status.exp = 0;
        g_Status.level = 1;
        g_Status.killCount = 0;

        for (i = 0; i < NUM_FAMILIARS; i++) {
            g_Status.statsFamiliars[i].level = 1;
            g_Status.statsFamiliars[i].exp = 0;
            g_Status.statsFamiliars[i].unk8 = 0;
        }

        for (i = 0; i < 169; i++) {
            g_Status.equipHandCount[i] = 0;
            g_Status.equipHandOrder[i] = i;
        }

        for (i = 0; i < 90; i++) {
            g_Status.equipBodyCount[i] = 0;
            g_Status.equipBodyOrder[i] = i;
        }

        g_Status.equipHandCount[ITEM_EMPTY_HAND] = 1;
        g_Status.equipBodyCount[ITEM_EMPTY_HEAD] = 1;
        g_Status.equipBodyCount[ITEM_NO_ARMOR] = 1;
        g_Status.equipBodyCount[ITEM_NO_CAPE] = 1;
        g_Status.equipBodyCount[ITEM_NO_ACCESSORY] = 1;

        for (i = 0; i < LEN(g_Status.spells); i++) {
            g_Status.spells[i] = 0;
        }
        g_Status.spellsLearnt = 0;

        // If playing as Richter, either in the Prologue or Richter Mode
        if ((g_StageId == STAGE_ST0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {

            for (i = 0; i < LEN(g_Status.relics); i++) {
                g_Status.relics[i] = RELIC_FLAG_FOUND;
            }

            // These relics are special for Richter
            g_Status.relics[RELIC_CUBE_OF_ZOE] |= 2;
            g_Status.relics[RELIC_SPIRIT_ORB] |= 2;
            g_Status.relics[RELIC_FAERIE_SCROLL] |= 2;
            g_Status.relics[RELIC_JEWEL_OF_OPEN] |= 2;

            // Zero out all time attack records
            for (i = 0; i < 32; i++) {
                g_Settings.timeAttackRecords[i] = 0;
            }
            g_Settings.D_8003CB00 = 0;
            g_Settings.D_8003CB04 = 0;

            g_Status.subWeapon = 0;

            // If this function is called outside the start of the game,
            // Richter gets a random subweapon.
            if ((g_StageId != STAGE_ST0) && (g_StageId != STAGE_NO3)) {
                g_Status.subWeapon = (rand() % 9) + 1;
            }

            // Richter's stats table
            g_Status.hp = 50;
            g_Status.hpMax = 50;
            g_Status.hearts = 30;
            g_Status.heartsMax = 99;
            g_Status.mpMax = 20;
            g_Status.mp = 20;
            g_Status.statsBase[STAT_STR] = 10;
            g_Status.statsBase[STAT_CON] = 10;
            g_Status.statsBase[STAT_INT] = 10;
            g_Status.statsBase[STAT_LCK] = 10;
            g_Status.equipment[HEAD_SLOT] = ITEM_EMPTY_HEAD;
            g_Status.equipment[CAPE_SLOT] = ITEM_NO_CAPE;
            g_Status.equipment[ACCESSORY_1_SLOT] = ITEM_NO_ACCESSORY;
            g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_NO_ACCESSORY;
            g_Status.gold = 0;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_EMPTY_HAND;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_EMPTY_HAND;
            g_Status.equipment[ARMOR_SLOT] = ITEM_NO_ARMOR;

            // Eliminate the time attacks that Richter can't do
            if (g_StageId == STAGE_NO3) {
                TimeAttackController(
                    TIMEATTACK_EVENT_FIRST_MARIA_MEET, TIMEATTACK_SET_RECORD);
                TimeAttackController(
                    TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_SET_RECORD);
                TimeAttackController(TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT,
                                     TIMEATTACK_SET_RECORD);
                TimeAttackController(
                    TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_RECORD);
                TimeAttackController(
                    TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_SET_RECORD);
            }
            g_Status.timerHours = 0;
            g_Status.timerMinutes = 0;
            g_Status.timerSeconds = 0;
            g_Status.timerFrames = 0;
        } else {
            // This Else block is for non-Richter play.
            if (g_StageId == STAGE_NO3) {
                g_Status.statsBase[STAT_STR] = 6;
                g_Status.statsBase[STAT_CON] = 6;
                g_Status.statsBase[STAT_INT] = 6;
                g_Status.statsBase[STAT_LCK] = 6;
                g_Status.gold = 0;
                for (i = 0; i < LEN(g_Status.relics); i++) {
                    g_Status.relics[i] = RELIC_FLAG_DISABLE;
                }

                // If we died in prologue and needed Maria's rescue
                if (D_801397FC != 0) {
                    AddToInventory(ITEM_POTION, EQUIP_HAND);
                    prologueBonusState = 3;
                    // If no damage was taken as Richter, bonus to each stat
                } else if (g_Status.hp == g_Status.hpMax) {
                    g_Status.statsBase[STAT_STR]++;
                    g_Status.statsBase[STAT_CON]++;
                    g_Status.statsBase[STAT_INT]++;
                    g_Status.statsBase[STAT_LCK]++;
                    prologueBonusState = 0;
                    // If Richter finished over half HP, bonus to strength
                } else if (g_Status.hp >= g_Status.hpMax / 2) {
                    g_Status.statsBase[STAT_STR]++;
                    prologueBonusState = 1;
                    // If under half HP, bonus to constitution
                } else {
                    g_Status.statsBase[STAT_CON]++;
                    prologueBonusState = 2;
                }

                // If we ran out of hearts and didn't die, give heart refresh
                if ((g_Status.hearts == 0) && (prologueBonusState < 3)) {
                    AddToInventory(ITEM_HEART_REFRESH, EQUIP_HAND);
                }

                // Set initial max HP to 70, unless we took no damage, then 75.
                g_Status.hpMax = 70;
                if (prologueBonusState == 0) {
                    g_Status.hpMax = 75;
                }
                g_Status.hearts = 10;
                g_Status.heartsMax = 50;
                g_Status.mpMax = 20;

                // If we had more than 41 hearts in prologue, give neutron bomb
                if (D_80139008 >= 41) {
                    AddToInventory(ITEM_NEUTRON_BOMB, EQUIP_HAND);
                    g_Status.statsBase[STAT_INT]++;
                } else {
                    g_Status.statsBase[STAT_STR]++;
                }

                // If we finished with the cross subweapon
                if (g_Status.subWeapon == 4) {
                    //...and didn't die in prologue
                    if (prologueBonusState < 3) {
                        g_Status.heartsMax += 5;
                        g_Status.mpMax += 5;
                    }
                    // If we finished with the holy water subweapon
                } else if (g_Status.subWeapon == 3) {
                    //...and finished with over half HP
                    if (prologueBonusState < 2) {
                        g_Status.heartsMax += 5;
                        g_Status.statsBase[STAT_INT]++;
                    }
                } else {
                    // If we didn't pick up a subweapon in prologue
                    switch (prologueBonusState) {
                    // Took no damage
                    case 0:
                        g_Status.statsBase[STAT_LCK] += 5;
                        g_Status.statsBase[STAT_INT]++;
                        g_Status.statsBase[STAT_CON]++;
                    // Over half health
                    case 1:
                        g_Status.hpMax += 5;
                    // Survived
                    case 2:
                        g_Status.statsBase[STAT_STR]++;
                        break;
                    }
                }
                dracDefeatTime = TimeAttackController(
                    TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_GET_RECORD);
                // If you defeated him in less than 101 seconds
                if (dracDefeatTime <= 100) {
                    g_Status.hpMax += 5;
                    g_Status.mpMax += 5;
                    g_Status.heartsMax += 5;
                    g_Status.statsBase[STAT_STR] += 5;
                    g_Status.statsBase[STAT_CON] += 5;
                    g_Status.statsBase[STAT_INT] += 5;
                    g_Status.statsBase[STAT_LCK] += 5;
                } else if (dracDefeatTime <= 200) {
                    g_Status.statsBase[STAT_LCK] += 2;
                } else if (dracDefeatTime <= 300) {
                    g_Status.statsBase[STAT_LCK]++;
                    // Strange - if you wait over 1000 you get a bonus CON
                } else if (dracDefeatTime >= 1000) {
                    g_Status.statsBase[STAT_CON]++;
                }
                g_Status.equipment[LEFT_HAND_SLOT] = ITEM_ALUCARD_SWORD;
                g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_ALUCARD_SHIELD;
                g_Status.equipment[HEAD_SLOT] = ITEM_DRAGON_HELM;
                g_Status.equipment[ARMOR_SLOT] = ITEM_ALUCARD_MAIL;
                g_Status.equipment[CAPE_SLOT] = ITEM_TWILIGHT_CLOAK;
                g_Status.equipment[ACCESSORY_1_SLOT] = ITEM_NECKLACE_OF_J;
                g_Status.subWeapon = 0;
                g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_NO_ACCESSORY;
                g_Status.hp = g_Status.hpMax;
                g_Status.mp = g_Status.mpMax;

                // Luck mode code check! This is X-X!V''Q
                fileName = g_CheatCodes[0];
                for (i = 0; i < 8; i++) {
                    if (g_SaveName[i] != *fileName++) {
                        break;
                    }
                }
                if (i == 8) {
                    // Being after the prologue bonuses, this erases them.
                    g_Status.statsBase[STAT_STR] = 1;
                    g_Status.statsBase[STAT_CON] = 0;
                    g_Status.statsBase[STAT_INT] = 0;
                    g_Status.statsBase[STAT_LCK] = 99;
                    g_Status.hpMax = 25;
                    g_Status.hearts = 5;
                    g_Status.heartsMax = 5;
                    g_Status.mpMax = 1;
                    g_Status.hp = g_Status.hpMax;
                    g_Status.mp = g_Status.mpMax;
                    g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_LAPIS_LAZULI;
                }

                if (g_IsTimeAttackUnlocked) {
                    fileName = g_CheatCodes[1];
                    for (i = 0; i < 8; i++) {
                        if (g_SaveName[i] != *fileName++) {
                            break;
                        }
                    }
                    if (i == 8) {
                        AddToInventory(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR);
                    }
                }
            } else {
                // This Else block is for this function if called outside
                // the "Entrance (first visit)" overlay. Applies to demo mode.
                for (i = 0; i < LEN(g_Settings.timeAttackRecords); i++) {
                    g_Settings.timeAttackRecords[i] = 0;
                }
                g_Status.statsBase[STAT_STR] = 6;
                g_Status.statsBase[STAT_CON] = 6;
                g_Status.statsBase[STAT_INT] = 6;
                g_Status.statsBase[STAT_LCK] = 6;
                g_Status.hpMax = 70;
                g_Status.hp = 70;
                g_Status.hearts = 10;
                g_Status.gold = 500000;
                g_Status.heartsMax = 50;
                g_Status.mpMax = 20;
                g_Status.mp = 20;
                g_Status.hearts = 1234;
                g_Status.heartsMax = 2000;
                g_Status.exp = 11000;
#if defined(VERSION_US)
                g_Status.level = 20;
                if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
                    g_Status.exp = 110000;
                }
#elif defined(VERSION_HD)
                if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
                    g_Status.exp = 40000;
                }
#endif
                for (i = 0; i < LEN(g_Status.relics); i++) {
                    g_Status.relics[i] = RELIC_FLAG_FOUND | RELIC_FLAG_ACTIVE;
                    if (g_RelicDefs[i].unk0C != 0) {
                        g_Status.relics[i] = RELIC_FLAG_FOUND;
                    }
                }

                // In Demo mode, Alucard gets 50 of everything holdable
                for (i = 0; i < 169; i++) {
                    g_Status.equipHandCount[i] = 50;
                }
                // And 1 of everything wearable
                for (i = 0; i < 90; i++) {
                    g_Status.equipBodyCount[i] = 1;
                }
#if defined(VERSION_US)
                g_Status.equipment[LEFT_HAND_SLOT] = ITEM_SHORT_SWORD;
                g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_LEATHER_SHIELD;
                g_Status.equipment[HEAD_SLOT] = ITEM_EMPTY_HEAD;
                g_Status.equipment[ARMOR_SLOT] = ITEM_HIDE_CUIRASS;
                g_Status.equipment[CAPE_SLOT] = ITEM_NO_CAPE;
                g_Status.equipment[ACCESSORY_1_SLOT] = ITEM_NO_ACCESSORY;
                g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_NO_ACCESSORY;
                g_Status.timerHours = 0;
                g_Status.timerMinutes = 0;
                g_Status.timerSeconds = 0;
                g_Status.timerFrames = 0;
                g_Status.subWeapon = 0;
                g_Status.relics[RELIC_CUBE_OF_ZOE] = 3;
                g_Status.relics[RELIC_SPIRIT_ORB] = 3;
                g_Status.relics[RELIC_FAERIE_SCROLL] = 3;
                g_Status.relics[RELIC_SOUL_OF_BAT] = 3;
                g_Status.relics[RELIC_FIRE_OF_BAT] = 3;
                g_Status.relics[RELIC_SOUL_OF_WOLF] = 3;
                g_Status.relics[RELIC_POWER_OF_WOLF] = 3;
                g_Status.relics[RELIC_SKILL_OF_WOLF] = 3;
                g_Status.relics[RELIC_FORM_OF_MIST] = 3;
                g_Status.relics[RELIC_GRAVITY_BOOTS] = 3;
                g_Status.relics[RELIC_LEAP_STONE] = 3;

                AddToInventory(ITEM_FIREBRAND, EQUIP_HAND);
                AddToInventory(ITEM_THUNDERBRAND, EQUIP_HAND);
                AddToInventory(ITEM_ICEBRAND, EQUIP_HAND);
                AddToInventory(ITEM_CLAYMORE, EQUIP_HAND);
                AddToInventory(ITEM_MACE, EQUIP_HAND);
                AddToInventory(ITEM_KATANA, EQUIP_HAND);
                AddToInventory(ITEM_KNIGHT_SHIELD, EQUIP_HAND);
                AddToInventory(ITEM_IRON_SHIELD, EQUIP_HAND);
                AddToInventory(ITEM_BASILARD, EQUIP_HAND);
                AddToInventory(ITEM_RAPIER, EQUIP_HAND);
                AddToInventory(ITEM_KNUCKLE_DUSTER, EQUIP_HAND);
                AddToInventory(ITEM_CUTLASS, EQUIP_HAND);

                AddToInventory(ITEM_CLOTH_TUNIC, EQUIP_ARMOR);
                AddToInventory(ITEM_BRONZE_CUIRASS, EQUIP_ARMOR);
                AddToInventory(ITEM_IRON_CUIRASS, EQUIP_ARMOR);
                AddToInventory(ITEM_STEEL_CUIRASS, EQUIP_ARMOR);
                AddToInventory(ITEM_SILVER_PLATE, EQUIP_ARMOR);
                AddToInventory(ITEM_GOLD_PLATE, EQUIP_ARMOR);
                AddToInventory(ITEM_FIRE_MAIL, EQUIP_ARMOR);
                AddToInventory(ITEM_MIRROR_CUIRASS, EQUIP_ARMOR);

                AddToInventory(ITEM_VELVET_HAT, EQUIP_HEAD);
                AddToInventory(ITEM_LEATHER_HAT, EQUIP_HEAD);
                AddToInventory(ITEM_STEEL_HELM, EQUIP_HEAD);

                AddToInventory(ITEM_CLOTH_CAPE, EQUIP_CAPE);
                AddToInventory(ITEM_ELVEN_CLOAK, EQUIP_CAPE);
                AddToInventory(ITEM_ROYAL_CLOAK, EQUIP_CAPE);
                AddToInventory(ITEM_REVERSE_CLOAK, EQUIP_CAPE);

                AddToInventory(ITEM_MEDAL, EQUIP_ACCESSORY);
                AddToInventory(ITEM_GAUNTLET, EQUIP_ACCESSORY);

                for (i = 0; i < 80; i++) {
                    AddToInventory(ITEM_POTION, EQUIP_HAND);
                }

                for (i = 0; i < 10; i++) {
                    AddToInventory(ITEM_MAGIC_MISSILE, EQUIP_HAND);
                    AddToInventory(ITEM_TURKEY, EQUIP_HAND);
                    AddToInventory(ITEM_POT_ROAST, EQUIP_HAND);
                    AddToInventory(ITEM_ANTIVENOM, EQUIP_HAND);
                    AddToInventory(ITEM_BOOMERANG, EQUIP_HAND);
                    AddToInventory(ITEM_JAVELIN, EQUIP_HAND);
                    AddToInventory(ITEM_PENTAGRAM, EQUIP_HAND);
                }
#elif defined(VERSION_HD)
                g_Status.timerHours = 0;
                g_Status.timerMinutes = 0;
                g_Status.timerSeconds = 0;
                g_Status.timerFrames = 0;
                g_Status.subWeapon = 6;

                if (rand() & 3) {
                    g_Status.subWeapon = (rand() % 9) + 1;
                }

                do {
                loop_check_equip_id_1:
                    equipId = rand() % 169;
                    if (equipId == 216) {
                        goto loop_check_equip_id_1;
                    }
                } while (g_EquipDefs[equipId].itemCategory > 4);

                g_Status.equipment[LEFT_HAND_SLOT] = equipId;
                do {
                loop_check_equip_id_2:
                    equipId = rand() % 169;
                    if (equipId == 216) {
                        goto loop_check_equip_id_2;
                    }
                } while (g_EquipDefs[equipId].itemCategory == 5);

                g_Status.equipment[RIGHT_HAND_SLOT] = equipId;
                func_800FF708(0, 0);
                func_800FF708(1, 1);
                func_800FF708(2, 2);
                func_800FF708(3, 3);
                func_800FF708(3, 4);
#endif
            }
        }
    }
    func_800F53A4();
}

void DrawRichterHud(void) {
    Primitive* prim;

    g_PlayerHud.unk0C = 400;
    g_PlayerHud.unk10 = 400;
    D_801397FC = 0;
    D_80139008 = 0;
    g_PlayerHud.unk28 = 0;
    D_8003C744 = 0;
    g_PlayerHud.unk14 = 48;
    g_PlayerHud.unk18 = 0;
    g_PlayerHud.unk24 = 0;
    g_PlayerHud.unk20 = 40000 / (u32)g_PlayerHud.unk0C;
    g_PlayerHud.unk1C = 40000 / g_PlayerHud.unk10;
    g_PlayerHud.primIndex1 = func_800EDD9C(PRIM_GT4, 9);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];

    SetTexturedPrimRect(prim, 2, 22, 32, 96, 0, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x101;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, g_PlayerHud.unk14 + 216, 22, 32, 96, 32, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x100;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, 4, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x105;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, g_PlayerHud.unk14 + 228, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim->p1 = 0;
    prim->p2 = 6;
    prim = prim->next;

    SetTexturedPrimRect(prim, g_PlayerHud.unk14 + 236, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, 14, 27, 8, 8, 0, 96);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, 22, 27, 8, 8, 0, 96);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, 18, 38, 8, 8, 0, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x102;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetTexturedPrimRect(prim, 33, 20, 64, 24, 64, 40);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_ABSPOS;

    g_PlayerHud.primIndex2 = func_800EDD9C(4, 16);
    prim = &g_PrimBuf[g_PlayerHud.primIndex2];
    if (prim != 0) {
        s32 u = 32;
        s32 x = 216;
        do {
            SetTexturedPrimRect(prim, x, 22, 2, 96, u, 0);
            func_801072DC(prim);
            prim->tpage = 0x1B;
            prim->clut = 0x100;
            prim->priority = 0x1EE;
            prim->drawMode = DRAW_HIDE;
            prim->p1 = (rand() & 0x3F) + 1;
            prim->p2 = 0;
            prim = prim->next;
            u += 2;
            x += 2;
        } while (prim != 0);
    }
}

RicSubwpnIconParams g_ricSubwpnIcons[] = {
    {0x9, 0x00F, 0x018, 0x010, 0x0A8, 0x0C0, 0x01E, 0x17F},
    {0x009, 0x007, 0x018, 0x018, 0x080, 0x0C0, 0x01E, 0x17F},
    {0x00C, 0x00D, 0x010, 0x010, 0x028, 0x070, 0x01B, 0x102},
    {0x008, 0x00C, 0x018, 0x018, 0x038, 0x068, 0x01B, 0x102},
    {0x00C, 0x007, 0x010, 0x018, 0x098, 0x0D8, 0x01E, 0x17F},
    {0x00C, 0x007, 0x010, 0x018, 0x098, 0x0C0, 0x01E, 0x17F},
    {0x00F, 0x013, 0x008, 0x008, 0x0C0, 0x0D0, 0x01E, 0x163},
    {0x008, 0x00D, 0x018, 0x010, 0x0A8, 0x0D0, 0x01E, 0x17F},
    {0x008, 0x006, 0x018, 0x018, 0x080, 0x0D8, 0x01E, 0x17F}};

void DrawRichterHudSubweapon(void) {
    Primitive* prim;
    Primitive* altPrim;
    s32 temp_subweapon;
    s32 temp_a0;
    s32 temp_s2;
    u8 temp_r0;
    u8 temp_p2;
    RicSubwpnIconParams* temp_s0;

    if (D_8003C744 == 5) {
        prim = &g_PrimBuf[g_PlayerHud.primIndex1];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[g_PlayerHud.primIndex2];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;
    }
    if ((D_8003C744 == 1) && (g_PlayerHud.unk28 == 0)) {
        g_PlayerHud.unk20 = 100;
        g_PlayerHud.unk28 = D_8003C744;
        g_PlayerHud.unk10 = g_Entities[80].hitPoints;
        g_PlayerHud.unk0C = g_Entities[80].hitPoints;
        D_80139008 = g_Status.hearts;
        // Not really sure what the point of this is.
        g_PlayerHud.unk1C =
            (g_Entities[80].hitPoints * 100) / (u32)g_Entities[80].hitPoints;
    }
    if ((D_8003C744 == 2) && (g_PlayerHud.unk28 == 1)) {
        g_PlayerHud.unk28 = D_8003C744;
        g_PlayerHud.unk10 = g_Entities[85].hitPoints;
        g_PlayerHud.unk0C = g_Entities[85].hitPoints;
    }
    if (g_PlayerHud.unk28 != 100) {
        if (D_8003C744 == 1) {
            g_PlayerHud.unk0C = g_Entities[80].hitPoints;
        }
        if ((D_8003C744 - 2) < 2U) {
            g_PlayerHud.unk0C = g_Entities[85].hitPoints;
        }
        if (g_PlayerHud.unk0C < 0) {
            g_PlayerHud.unk0C = 0;
        }
    }
    if (g_PlayerHud.displayHP < g_Status.hp) {
        g_PlayerHud.displayHP++;
        D_801397FC = 1;
    }
    if (g_Status.hp < g_PlayerHud.displayHP) {
        g_PlayerHud.displayHP--;
    }
    if (D_8003C744 == 1) {
        if (g_PlayerHud.unk1C <
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk1C++;
        }
        if (((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) <
            g_PlayerHud.unk1C) {
            g_PlayerHud.unk1C--;
        }
    }
    if ((D_8003C744 - 2) < 2U) {
        if (g_PlayerHud.unk1C != 0) {
            g_PlayerHud.unk1C -= 1;
        }
        if (g_PlayerHud.unk20 <
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk20++;
        }
        if (((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) <
            g_PlayerHud.unk20) {
            g_PlayerHud.unk20--;
        }
    }
    if ((D_8003C744 != 0) && (g_PlayerHud.unk14 != 0)) {
        g_PlayerHud.unk14--;
    }
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xD8, 0x16, 0x20, 0x60);
    if ((D_8003C744 == 3) && (g_PlayerHud.unk20 == 0) &&
        ((g_PlayerHud.unk24 == 0) || (g_PlayerHud.unk24 >= 0x33U))) {
        prim->drawMode = DRAW_HIDE;

        for (altPrim = &g_PrimBuf[g_PlayerHud.primIndex2]; altPrim != NULL;
             altPrim = altPrim->next) {
            if (altPrim->p2 != 0) {
                continue;
            }
            altPrim->drawMode = DRAW_ABSPOS | DRAW_COLORS;
            if (altPrim->p1 != 0) {
                altPrim->p1--;
                continue;
            }
            temp_a0 = rand() & 1;
            altPrim->y0 += temp_a0;
            altPrim->y1 += temp_a0;
            temp_a0 = (rand() & 3) + 1;
            altPrim->drawMode = DRAW_ABSPOS | DRAW_COLORS;
            altPrim->y2 += temp_a0;
            altPrim->y3 += temp_a0;
            if (altPrim->r2 >= 3) {
                temp_s2 = altPrim->r2 - 3;
                func_801071CC(altPrim, temp_s2, 2);
                func_801071CC(altPrim, temp_s2, 3);
            }
            if (altPrim->y2 >= 0x100) {
                altPrim->drawMode =
                    DRAW_ABSPOS | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                if (altPrim->r0 != 0) {
                    temp_r0 = altPrim->r0;
                    temp_s2 = temp_r0 & 0xFF;
                    altPrim->r0 = temp_r0 + 0xFF;
                    func_801071CC(altPrim, temp_s2, 0);
                    func_801071CC(altPrim, temp_s2, 1);
                }
                if (altPrim->y2 >= 0x180) {
                    altPrim->drawMode =
                        DRAW_ABSPOS | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                        DRAW_COLORS | DRAW_TRANSP;
                }
            }
            if (altPrim->y2 >= 0x200) {
                altPrim->drawMode = DRAW_HIDE;
                altPrim->p2 = 1;
            }
        }
    }

    prim = prim->next;
    temp_a0 = (g_PlayerHud.displayHP * 0x5B) / g_Status.hpMax;
    prim->y0 = prim->y1 = prim->y2 - temp_a0;
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xE4, 0x70, 9, 3);
    temp_a0 = (g_PlayerHud.unk1C * 0x5B) / 100;
    if (temp_a0 < 0) {
        temp_a0 = 0;
    }
    temp_p2 = prim->p2;
    prim->y0 = prim->y1 = prim->y2 - temp_a0;
    prim->p2 = temp_p2 + 0xFF;
    if (temp_p2 == 0) {
        prim->p1++;
        if (prim->p1 == 9) {
            prim->p1 = 0;
        }
        if (D_8003C744 == 2) {
            prim->p2 = 1;
        } else {
            prim->p2 = 4;
        }
        prim->clut = prim->p1 + 0x103;
    }
    temp_s2 = prim->clut;
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xEC, 0x70, 9, 3);
    temp_a0 = (g_PlayerHud.unk20 * 0x5B) / 100;
    if (temp_a0 >= 0x5C) {
        temp_a0 = 0x5B;
    }
    prim->clut = temp_s2;
    prim->y0 = prim->y1 = prim->y2 - temp_a0;
    prim = prim->next;

    prim->u0 = (g_Status.hearts / 10) * 8;
    prim->v0 = 0x60;
    prim->u1 = ((g_Status.hearts / 10) * 8) + 8;
    prim->v1 = 0x60;
    prim->u2 = (g_Status.hearts / 10) * 8;
    prim->v2 = 0x68;
    prim->u3 = ((g_Status.hearts / 10) * 8) + 8;
    prim->v3 = 0x68;
    // Perhaps flashes the heart numbers when you have enough for a crash
    if ((g_Player.status & PLAYER_STATUS_UNK200000) && !(g_Timer & 2)) {
        prim->clut = 0x100;
    } else {
        prim->clut = 0x103;
    }
    altPrim = prim;
    prim = prim->next;
    prim->u0 = (g_Status.hearts % 10) * 8;
    prim->v0 = 0x60;
    prim->u1 = ((g_Status.hearts % 10) * 8) + 8;
    prim->v1 = 0x60;
    prim->u2 = (g_Status.hearts % 10) * 8;
    prim->v2 = 0x68;
    prim->u3 = ((g_Status.hearts % 10) * 8) + 8;
    prim->v3 = 0x68;

    prim->clut = altPrim->clut;
    prim->drawMode = altPrim->drawMode;
    prim = prim->next;
    temp_subweapon = g_Status.subWeapon;
    if (temp_subweapon == 0) {
        prim->drawMode = DRAW_HIDE;
    } else {
        // Convert from system where 0 is "no subweapon" to "first subweapon"
        temp_subweapon--;
        temp_s0 = &g_ricSubwpnIcons[temp_subweapon];
        SetTexturedPrimRect(prim, temp_s0->x + 2, temp_s0->y + 0x16, temp_s0->w,
                            temp_s0->h, temp_s0->u, temp_s0->v);
        prim->tpage = temp_s0->tpage;
        prim->clut = temp_s0->clut;
        prim->drawMode = DRAW_ABSPOS;

        if (prim->clut == 0x17F) {
            prim->drawMode = DRAW_ABSPOS | DRAW_TPAGE | DRAW_TRANSP;
        }
    }
    prim = prim->next;
    // This should be a switch, but that doesn't work.
    if (g_PlayerHud.unk24 == 0) {
    } else if (g_PlayerHud.unk24 < 9) {
        prim->clut = g_PlayerHud.unk24 + 0x102;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 9) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0);
        prim->clut = 0x103;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 10) {
        SetTexturedPrimRect(prim, 0x21, 0x1C, 0x40, 8, 0x40, 0x10);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 11) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0x18);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 12) {
        SetTexturedPrimRect(prim, 0x21, 0x14, 0x40, 0x18, 0x40, 0x40);
        prim->clut = 0x112;
        g_PlayerHud.unk24++;
    } else if (13 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 20) {
        prim->clut = 0x11F - g_PlayerHud.unk24;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 21) {
    } else if (51 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 58) {
        prim->clut = g_PlayerHud.unk24 + 0xD8;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 59) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0x18);
        prim->clut = 0x103;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 60) {
        SetTexturedPrimRect(prim, 0x21, 0x1C, 0x40, 8, 0x40, 0x10);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 61) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 62) {
        SetTexturedPrimRect(prim, 0x21, 0x14, 0x40, 0x18, 0x40, 0x28);
        prim->clut = 0x10A;
        g_PlayerHud.unk24++;
    } else if (63 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 70) {
        prim->clut = 0x149 - g_PlayerHud.unk24;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 71) {
        g_PlayerHud.unk24 = 0;
    }
}

bool func_8010183C(s32 arg0) {
    if (arg0 == 0) {
        if (g_PlayerHud.unk24 == 0) {
            g_PlayerHud.unk24 = 1;
            return true;
        }
        return false;
    } else if (arg0 == 1) {
        if (g_PlayerHud.unk24 == 0x15) {
            g_PlayerHud.unk24 = 0x33;
            return true;
        }
        return false;
    }
    return true;
}

void DrawHud(void) {
    Primitive* prim;
    s32 i;

    D_8013B5E8 = 0;
    g_HealingMailTimer[0] = 0;
    g_PlayerHud.displayHP = g_Status.hp;

    if ((g_StageId == STAGE_ST0) || (g_PlayableCharacter != PLAYER_ALUCARD)) {
        DrawRichterHud();
        return;
    }

    g_PlayerHud.primIndex1 = func_800EDD9C(PRIM_GT4, HUD_NUM_SPRITES);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    if (!prim) {
        return;
    }

    for (i = 0; prim != NULL; i++) {
        SetTexturedPrimRect(
            prim, g_HudSpriteX[i], g_HudSpriteY[i], g_HudSpriteW[i],
            g_HudSpriteH[i], g_HudSpriteU[i], g_HudSpriteV[i]);
        prim->tpage = 0x1F;
        prim->clut = g_HudSpriteClut[i];
        prim->priority = 0x1F0;
        prim->drawMode = g_HudSpriteBlend[i];

        if (i == 5) {
            SetPrimRect(prim, g_HudSpriteX[i], g_HudSpriteY[i], g_HudSpriteH[i],
                        g_HudSpriteW[i]);
            prim->y0 = prim->y2;
            prim->x1 = prim->x0;
            prim->x2 = prim->x3;
            prim->y3 = prim->y1;
        }

        if (i == 1) {
            prim->p1 = 0;
            prim->p2 = rand() + 8;
            prim->p3 = (7 & rand()) + 1;
        }

        prim = prim->next;
    }
}

void DrawHudSubweapon() {
    SubweaponDef subwpn;
    RECT rect;
    Primitive* prim;

    s32 statXPos;
    s32 hpdiff;
    s32 mpFillSteps;
    s32 leading_zeros;
    s32 digitSpacing;
    u16 clut;

    if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
        DrawRichterHudSubweapon();
        return;
    }
    func_800EB4F8(D_800C52F8[g_Status.subWeapon], 0, 0x3C0, 0x120);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    if (g_Status.subWeapon != 0) {
        prim->drawMode = DRAW_ABSPOS | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;
        prim->p2--;
        if (prim->p2 == 0) {
            prim->p1 += 1;
            if (prim->p1 == 0xF) {
                prim->p1 = 0;
                prim->p2 = rand() + 8;
                prim->p3--;
                if (prim->p3 != 0) {
                    prim->p1 = 1;
                    prim->p2 = 1;
                } else {
                    prim->p3 = (rand() & 7) + 1;
                }
            } else {
                prim->p2 = 1;
                prim->clut = g_HudSubwpnSpriteClut[prim->p1 - 1];
                prim->u0 = g_HudSubwpnSpriteU[prim->p1 - 1];
                prim->v0 = g_HudSubwpnSpriteV[prim->p1 - 1];
                prim->u1 = g_HudSubwpnSpriteU[prim->p1 - 1] + 16;
                prim->v1 = g_HudSubwpnSpriteV[prim->p1 - 1];
                prim->u2 = g_HudSubwpnSpriteU[prim->p1 - 1];
                prim->v2 = g_HudSubwpnSpriteV[prim->p1 - 1] + 16;
                prim->u3 = g_HudSubwpnSpriteU[prim->p1 - 1] + 16;
                prim->v3 = g_HudSubwpnSpriteV[prim->p1 - 1] + 16;
            }
        }
        if (prim->p1 != 0) {
            prim->drawMode = DRAW_ABSPOS;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim->drawMode = DRAW_ABSPOS;
    } else {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
    }

    // Want to use prim = prim->next->next->next but that uses wrong register
    prim = prim->next;
    prim = prim->next;
    prim = prim->next;
    rect.x = 988;
    rect.y = 256;
    rect.w = 2;
    rect.h = 56;

    ClearImage(&rect, 0, 0, 0);
    if (!(g_Status.D_80097BF8 & 1)) {
        if (!(g_GameTimer & 0x3F)) {
            g_Status.mp++;
        }
        if ((CheckEquipmentItemCount(ITEM_MYSTIC_PENDANT, EQUIP_ACCESSORY) !=
             0) &&
            ((g_GameTimer & 0x3F) == 0x1F)) {
            g_Status.mp++;
        }
        if (g_Status.mp > g_Status.mpMax) {
            g_Status.mp = g_Status.mpMax;
        }
    }

    if ((CheckEquipmentItemCount(ITEM_HEALING_MAIL, EQUIP_ARMOR)) &&
        ((g_Player.status & (PLAYER_STATUS_TRANSFORM |
                             PLAYER_STATUS_UNK4000000)) == 0x04000000)) {
        g_HealingMailTimer[0]++;
        if (g_HealingMailTimer[0] >= 128) {
            g_Player.unk56 = 2;
            g_Player.unk58 = 1;
            g_HealingMailTimer[0] = 0;
        }
    } else {
        g_HealingMailTimer[0] = 0;
    }

    func_800FEE6C();
    // Represents MP fill level in fraction of 50 (2% each)
    mpFillSteps = (g_Status.mp * 50) / g_Status.mpMax;
    LoadTPage(D_800C52F8[10] + 4, 0, 0, 0x3DC, 0x100, 8, mpFillSteps);
    // Use one clut if MP is full, otherwise a different one
    prim->clut = mpFillSteps == 50 ? 0x162 : 0x174;

    if (D_8013B5E8 == 0) {
        hpdiff = g_Status.hp - g_PlayerHud.displayHP;
        if (hpdiff > 0) {
            if (hpdiff >= 11) {
                g_PlayerHud.displayHP += (hpdiff) / 10;
            } else {
                g_PlayerHud.displayHP++;
            }
        }
        if (hpdiff < 0) {
            if (hpdiff < -10) {
                g_PlayerHud.displayHP += (hpdiff) / 10;
            } else {
                g_PlayerHud.displayHP--;
            }
        }
    } else {
        D_8013B5E8--;
    }
    if (g_PlayerHud.displayHP == g_Status.hpMax) {
        func_800EA5E4(2); // Likely related to HP showing bold when full
    } else if (g_PlayerHud.displayHP <= g_Status.hpMax >> 2) {
        func_800EA5E4(3); // Show yellow if under 1/4 health
    } else {
        func_800EA5E4(1); // Normal health display
    }

    if (g_PlayerHud.displayHP >= 1000) {
        leading_zeros = 0;
        digitSpacing = 6;
        statXPos = 3;
    } else if (g_PlayerHud.displayHP >= 100) {
        leading_zeros = 1;
        digitSpacing = 6;
        statXPos = 0;
    } else {
        digitSpacing = 7;
        statXPos = -6;
        if (g_PlayerHud.displayHP >= 10) {
            leading_zeros = 2;
        } else {
            leading_zeros = 3;
        }
    }
    // Thousands digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_PlayerHud.displayHP / 1000) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos;
    prim->x1 = prim->x3 = statXPos + 8;
    prim->drawMode = DRAW_ABSPOS;

    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Hundreds digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_PlayerHud.displayHP / 100) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + digitSpacing;
    prim->x1 = prim->x3 = statXPos + digitSpacing + 8;
    prim->drawMode = DRAW_ABSPOS;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Tens digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_PlayerHud.displayHP / 10) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + (digitSpacing * 2);
    prim->x1 = prim->x3 = statXPos + (digitSpacing * 2) + 8;
    prim->drawMode = DRAW_ABSPOS;

    if (leading_zeros != 0) {
        prim->drawMode = DRAW_HIDE;
    }
    // Ones digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_PlayerHud.displayHP % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + (digitSpacing * 3);
    prim->x1 = prim->x3 = statXPos + (digitSpacing * 3) + 8;

    if (g_Status.hearts >= 1000) {
        leading_zeros = 0;
        statXPos = 0x3B;
    } else if (g_Status.hearts >= 100) {
        leading_zeros = 1;
        statXPos = 0x37;
    } else {
        statXPos = 0x33;
        if (g_Status.hearts >= 10) {
            leading_zeros = 2;
        } else {
            leading_zeros = 3;
        }
    }

    // Seems like this should be a simple || but that doesn't work here.
    if (func_800FE3C4(&subwpn, 0, false) == 0) {
        clut = 0x196;
    } else if (g_Timer & 2) {
        clut = 0x196;
    } else {
        clut = 0x193;
    }

    // Thousands digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_Status.hearts / 1000) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos;
    prim->x1 = prim->x3 = statXPos + 8;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Hundreds digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_Status.hearts / 100) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 4;
    prim->x1 = prim->x3 = statXPos + 0xC;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Tens digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_Status.hearts / 10) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 8;
    prim->x1 = prim->x3 = statXPos + 0x10;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        prim->drawMode = DRAW_HIDE;
    }
    // Ones digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_Status.hearts % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 0xC;
    prim->x1 = prim->x3 = statXPos + 0x14;
    prim->clut = clut;
}
