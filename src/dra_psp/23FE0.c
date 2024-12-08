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

s32 HandleDamage(DamageParam* damage, s32 arg1, s32 amount, s32 arg3) {
    s32 ret = 0;
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
        if (g_Status.D_80097C2C & damage->effects & EFFECT_UNK_0200) {
            damage->effects &= ~EFFECT_UNK_0200;
        } else {
            return 0;
        }
    }

    if (g_Status.D_80097C2E & damage->effects) {
        if (amount < 1) {
            amount = 1;
        }
        damage->unkC = amount;
        if (g_Status.hp != g_Status.hpMax) {
            func_800FE8F0();
            g_Status.hp += damage->unkC;
            if (g_Status.hp > g_Status.hpMax) {
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
            if (g_Status.hp > g_Status.hpMax) {
                g_Status.hp = g_Status.hpMax;
            }
        }
        return 5;
    }

    // Very strange to have ballroom mask check. This item is not known to
    // have special behavior. Also, not possible to equip two. This may be
    // a new discovery of a property of the item. Worth further analysis.
    ;
    if (itemCount = CheckEquipmentItemCount(ITEM_BALLROOM_MASK, EQUIP_HEAD)) {
        if (damage->effects &
            (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
             EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0100 |
             EFFECT_SOLID_FROM_BELOW)) {
            if (itemCount == 1) {
                amount -= amount / 5;
            }
            if (itemCount == 2) {
                amount -= amount / 3;
            }
        }
    }
    if (g_Player.status & PLAYER_STATUS_STONE) {
        damage->damageTaken = g_Status.hpMax / 8;
        ret = 8;
    } else if (damage->effects & EFFECT_UNK_0200) {
        damage->damageTaken = amount - ((s32)g_Status.defenseEquip * 2);
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
        if (itemCount =
                CheckEquipmentItemCount(ITEM_TALISMAN, EQUIP_ACCESSORY)) {
            if (g_Status.statsTotal[STAT_LCK] * itemCount >= (rand() & 511)) {
                return 2;
            }
        }
        if (damage->damageTaken > 0) {
            if (damage->damageKind == 1 || damage->damageKind == 0) {
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
            if (g_Status.defenseEquip >= 100 &&
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
            return ret;
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

void func_800FEE6C(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        if (!D_80139828[i]) {
            continue;
        }
        switch (i) {
        default:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            D_80139828[i]--;
        }
    }
}

s32 HandleTransformationMP(TransformationForm form, CallMode mode) {
    if (form == FORM_BAT) {
        if (!IsRelicActive(RELIC_SOUL_OF_BAT)) {
            return -1;
        }
        if (g_Status.mp - 1 > 0) {
            if (mode != CHECK_ONLY) {
                if (g_GameTimer % 60 == 0) {
                    g_Status.mp -= 1;
                }
            }
            return 0;
        } else {
            return -1;
        }
    } else if (form == FORM_MIST) {
        if (!IsRelicActive(RELIC_FORM_OF_MIST)) {
            return -1;
        }
        if (IsRelicActive(RELIC_POWER_OF_MIST)) {
            if (g_Status.mp - 2 > 0) {
                if (mode != CHECK_ONLY) {
                    if (g_GameTimer % 30 == 0) {
                        g_Status.mp -= 2;
                    }
                }
                return 0;
            } else {
                return -1;
            }
        } else {
            if (g_Status.mp - 10 > 0) {
                if (mode != CHECK_ONLY) {
                    if ((g_GameTimer % 8) == 0) {
                        g_Status.mp -= 10;
                    }
                }
                return 0;
            } else {
                return -1;
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
    u16 element;
    u16 enemyElements;
    u16 elementMask;
    u16 maskedElement;
    s32 highestStatIdx;
    s32 i;
    u16 damage;
    u16 result;

    enemy = &sp20;
    *enemy = g_EnemyDefs[enemyEntity->enemyId];
    if (CheckEquipmentItemCount(ITEM_DRAGON_HELM, EQUIP_HEAD) != 0) {
        enemy->defense /= 2;
    }

    element = attackerEntity->attackElement;
    damage = attackerEntity->attack;
    if (!element) {
        element = 0x20;
    }
    if (element & 0xFF80) {
        elementMask = 0xFF80;
    } else {
        elementMask = 0x7F;
    }

    result = 0;
    maskedElement = element & elementMask;

    // These could be written as nested if-else, but more readable with goto.
    enemyElements = enemy->immunes & elementMask;
    if (maskedElement == (maskedElement & enemyElements)) {
        result = DAMAGE_FLAG_IMMUNE;
        goto exit;
    }
    enemyElements = enemy->absorbs & elementMask;
    if (maskedElement == (maskedElement & enemyElements)) {
        result = damage + DAMAGE_FLAG_ABSORB;
        goto exit;
    }

    enemyElements = enemy->strengths & elementMask;
    if (maskedElement == (maskedElement & enemyElements)) {
        damage /= 2;
    }
    maskedElement = element & enemy->weaknesses;
    if (maskedElement) {
        damage *= 2;
    }
    // Looks like this block triggers for a critical hit.
    // Implies that attackerEntity->entityRoomIndex is a crit rate?
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
#else
            damage += (rand() % g_Status.statsTotal[STAT_LCK]);
#endif
            break;
        }
        result = DAMAGE_FLAG_CRITICAL;
    }

    if (damage > enemy->defense) {
        damage -= enemy->defense;
    } else {
        damage = 1;
    }

    if (damage > 9999) {
        damage = 9999;
    }

    result += damage;

exit:
    return result;
}

s32 func_800FF460(u32 arg0){
    s32 res;
    if (arg0 == 0) {
        return 0;
    }
    res = arg0 + (arg0 * g_Status.statsTotal[STAT_LCK]) / 0x80;
    return res;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09103128);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_091032C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", RenderTilemap);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", SetRoomForegroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", SetRoomBackgroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", LoadRoomLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09103E68);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_800EAEA4);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", ResetPendingGfxLoad);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", LoadGfxAsync);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_091040A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", DecompressWriteNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", DecompressReadNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", DecompressData);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", LoadPendingGfx);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_800EB4F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", LoadEquipIcon);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09104810);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09104878);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_091048B8);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09104958);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_091049E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09104AA0);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09104C80);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_psp_09105200);

INCLUDE_ASM("dra_psp/psp/dra_psp/23FE0", func_80109A44);
