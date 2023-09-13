#define INCLUDE_ASM_NEW
#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

s32 func_800FD6C4(s32 equipTypeFilter) {
    s32 itemCount;
    s32 equipType;
    s32 i;

    switch (equipTypeFilter) {
    case HAND_TYPE:
        return NUM_HAND_ITEMS;
    case HEAD_TYPE:
        equipType = HEAD_TYPE - 1;
        break;
    case ARMOR_TYPE:
        equipType = ARMOR_TYPE - 1;
        break;
    case CAPE_TYPE:
        equipType = CAPE_TYPE - 1;
        break;
    case ACCESSORY_TYPE:
        equipType = ACCESSORY_TYPE - 1;
        break;
    }

    for (itemCount = 0, i = 0; i < 90; i++) {
        if (D_800A7734[i].unk00 == equipType) {
            itemCount++;
        }
    }
    return itemCount;
}

const u32 rodataPadding_jpt_800FD6E0 = 0;

u8* GetEquipOrder(s32 equipTypeFilter) {
    if (equipTypeFilter == 0) {
        return g_Status.equipHandOrder;
    }
    return g_Status.equipBodyOrder;
}

u8* GetEquipCount(s32 equipTypeFilter) {
    if (equipTypeFilter == 0) {
        return g_Status.equipHandCount;
    }
    return g_Status.equipBodyCount;
}

const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId) {
    if (!equipTypeFilter) {
        return D_800A4B04[equipId].name;
    } else {
        return D_800A7718[equipId].name;
    }
}

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
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
    }
    // seems to require missing return
}

// fix missing padding at end of jump table.
// this probably indicates the end of a C file
const u32 rodataPadding_800DCBD8 = 0;

#ifndef NON_EQUIVALENT
INCLUDE_ASM("dra/nonmatchings/5D6C4", AddToInventory);
#else
void AddToInventory(u16 itemId, s32 itemCategory) {
    u8 temp_a1;
    s32 new_var2;
    u8* phi_a0;
    u8* phi_a0_2;
    long i;
    s32 phi_a1;
    s32 phi_a1_2;
    u8* cursorY = GetEquipOrder(itemCategory);
    u8* itemArray = GetEquipCount(itemCategory);
    if (itemArray[itemId] < 99) {
        temp_a1 = itemArray[itemId];
        itemArray[itemId]++;
        if (itemArray[itemId] == 1) {
            itemArray[itemId] = temp_a1;
            phi_a1_2 = itemCategory;
            if (phi_a1_2 != 0) {
                i = D_800A7734[itemId].unk00;
            }
            phi_a0 = cursorY;
            for (phi_a1_2 = 0; true; phi_a1_2++) {
                if (phi_a0[phi_a1_2] == itemId) {
                    break;
                }
            }

            phi_a0_2++;
            phi_a0_2 = cursorY;
            for (phi_a1 = 0; true; phi_a1++) {
                if (((!itemArray[*phi_a0_2]) && phi_a1_2) &&
                    (i == D_800A7734[*phi_a0_2].unk00)) {
                    new_var2 = phi_a1;
                    cursorY[new_var2] = itemId;
                    break;
                }
            }

            itemArray[itemId]++;
            if (new_var2 < phi_a1_2) {
                cursorY[phi_a1_2] = cursorY[new_var2];
                cursorY[new_var2] = itemId;
            }
        }
    }
}
#endif

void func_800FD9D4(SpellDef* spell, s32 id) {
    *spell = g_SpellDefs[id];
    spell->attack += (g_Status.statsTotal[2] * 2 + (rand() % 12)) / 10;
    if (CheckEquipmentItemCount(ITEM_MOJO_MAIL, ARMOR_TYPE) != 0) {
        spell->attack += spell->attack / 2;
    }
}

s16 GetStatusAilmentTimer(StatusAilments statusAilment, s16 timer) {
    s16 ret;
    s32 var_v1;

    switch (statusAilment) {
    case STATUS_AILMENT_POISON:
        ret = timer - (g_Status.statsTotal[STAT_CON] * 16);
        if (ret < 256) {
            ret = 256;
        }
        break;
    case STATUS_AILMENT_CURSE:
        ret = timer - (g_Status.statsTotal[STAT_CON] * 4);
        if (ret < 64) {
            ret = 64;
        }
        break;
    case STATUS_AILMENT_PETRIFIED:
        ret = timer;
        var_v1 = (((rand() % 12) + g_Status.statsTotal[STAT_CON]) - 9) / 10;
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        if (var_v1 > 4) {
            var_v1 = 4;
        }
        ret -= var_v1;
        break;
    case STATUS_AILMENT_DARK_METAMORPHOSIS:
        ret = timer + (g_Status.statsTotal[STAT_INT] * 4);
        break;
    case STATUS_AILMENT_UNK04:
    case STATUS_AILMENT_UNK05:
        ret = timer;
        if (CheckEquipmentItemCount(ITEM_BWAKA_KNIFE, ACCESSORY_TYPE) != 0) {
            ret += ret / 2;
        }
        break;
    }

    return ret;
}

bool CastSpell(SpellIds spellId) {
    u8 mpUsage = g_SpellDefs[spellId].mpUsage;

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
            if (g_Status.spells[i] == 0) {
                g_Status.spells[i] = spellId | (~0x7F);
                return;
            }
        }
    }
}

bool func_800FDD44(s32 itemType) {
    s32 equippedItem = g_Status.equipment[itemType];
    bool isConsumable = D_800A4B04[equippedItem].isConsumable;

    if (CheckEquipmentItemCount(ITEM_DUPLICATOR, ACCESSORY_TYPE) == 0) {
        if (isConsumable) {
            if (g_Status.equipHandCount[equippedItem] == 0) {
                g_Status.equipment[itemType] = ITEM_EMPTY_HAND;
                func_800F53A4();
                return true;
            }
            g_Status.equipHandCount[equippedItem]--;
        }
    }
    return false;
}

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

s32 g_LevelHPIncrease[] = {1, 3, 6, 10, 20, 30, 40, 50, 100, 200};

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
    if (c_arrExpNext[g_Status.level] <= g_Status.exp) {
        g_Status.level++;
        statsGained = 0;
        g_Status.mpMax += 4 + (rand() & 1);
        g_Status.hp += g_LevelHPIncrease[(s32)g_Status.level / 10];
        g_Status.hpMax += g_LevelHPIncrease[(s32)g_Status.level / 10];
        g_Status.heartsMax += 2;
        // Run again, in case we have enough EXP to level up twice
        CheckAndDoLevelUp();
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
    s32 oldHeartMax;
    s32 activeFamiliar;
    s32 levelDiff;
    s32 i;
    s32 familiarXPBoost;
    u32 playerXPBoost;

    // Life Max Up
    if (type == 0x8000) {
        if (g_Status.hpMax == 9999) {
            return 1;
        }
        g_Status.hpMax += amount;
        if (g_Status.hpMax > 9999) {
            g_Status.hpMax = 9999;
        }
        if (g_CurrentPlayableCharacter != 0) {
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
        if (g_CurrentPlayableCharacter != 0) {
            return 1;
        }
        oldHeartMax = g_Status.heartsMax;
        if (oldHeartMax == 9999) {
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
        // Fake! This is needed to avoid having the compiler swap
        // the previous and following line. There may be other methods to
        // achieve the same goal, but this one at least works.
        amount++;
        amount--;
        if (D_800A872C[amount].unk0) {
            g_Status.relics[amount] = 1;
        }
        D_80137968++;
        return 0;
    }

    // Gain XP from defeating enemy
    if (amount != 0 && g_Status.level != 99) {
        // Done checking types, rename variable for clarity.
        s32 enemyLevel = type;
        playerXPBoost = amount;
        if (enemyLevel < (s32)g_Status.level) {
            levelDiff = g_Status.level - enemyLevel;
            for (i = 0; i < levelDiff; i++) {
                playerXPBoost = playerXPBoost * 2 / 3;
            }
            if (playerXPBoost == 0) {
                playerXPBoost = 1;
            }
        }
        if ((s32)g_Status.level < enemyLevel) {
            levelDiff = enemyLevel - g_Status.level;
            if (levelDiff > 5) {
                levelDiff = 5;
            }
            for (i = 0; i < levelDiff; i++) {
                playerXPBoost += playerXPBoost / 4;
            }
        }
        g_Status.exp += playerXPBoost;
        if (g_Status.exp >= D_800AC90C) {
            g_Status.exp = D_800AC90C;
        }

        activeFamiliar = D_8006CBC4 - 1;
        if (D_8006CBC4 == 0) {
            return;
        }

        // Note: playerXPBoost is meaningless as a name here. But register a2 is
        // playerXPBoost, and is used as the loop variable for this loop, so I
        // reuse it here. Strange logic, the familiarXPBoost seems to be log
        // base 2 of arg0/familiar.exp.

        playerXPBoost =
            (amount / g_Status.statsFamiliars[activeFamiliar].level);

        for (familiarXPBoost = 0; playerXPBoost != 0; familiarXPBoost++) {
            playerXPBoost >>= 1;
        }
#if defined(VERSION_HD)
        familiarXPBoost -= 2;
#endif
        if (familiarXPBoost <= 0) {
            familiarXPBoost = 1;
        }
        g_Status.statsFamiliars[activeFamiliar].exp += familiarXPBoost;
        if (g_Status.statsFamiliars[activeFamiliar].exp >= 9900) {
            g_Status.statsFamiliars[activeFamiliar].exp = 9899;
        }
        g_Status.statsFamiliars[activeFamiliar].level =
            (g_Status.statsFamiliars[activeFamiliar].exp / 100) + 1;
    }
}

bool IsRelicActive(RelicIds relicId) {
    u8 bitTest = RELIC_FLAG_ACTIVE;
    return (g_Status.relics[relicId] & bitTest) != 0;
}

s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts) {
    u32 accessoryCount;

    if (subweaponId == 0) {
        *subwpn = g_Subweapons[g_Status.subWeapon];
        accessoryCount =
            CheckEquipmentItemCount(ITEM_HEART_BROACH, ACCESSORY_TYPE);
        if (accessoryCount == 1) {
            subwpn->heartCost = subwpn->heartCost / 2;
        }
        if (accessoryCount == 2) {
            subwpn->heartCost = subwpn->heartCost / 3;
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
        *subwpn = g_Subweapons[subweaponId];
        if (CheckEquipmentItemCount(ITEM_BRILLIANT_MAIL, ARMOR_TYPE) != 0) {
            subwpn->attack += 10;
        }
#if defined(VERSION_US)
        if (subweaponId == 4 || subweaponId == 12) {
#elif defined(VERSION_HD)
        if (subweaponId == 4) {
#endif
            accessoryCount =
                CheckEquipmentItemCount(ITEM_STAUROLITE, ACCESSORY_TYPE);
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
    s32 criticalModRate;
    Equipment* var_a2;
    s32 criticalRate;
    u8 itemCategory;

    var_a2 = &D_800A4B04[(s16)equipId]; // FAKE
    criticalModRate = 5;

    __builtin_memcpy(res, &D_800A4B04[equipId], sizeof(Equipment));
    criticalRate = res->criticalRate;
    criticalRate = criticalRate - criticalModRate +
                   SquareRoot0((g_Status.statsTotal[3] * 2) + (rand() & 0xF));
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
    itemCategory = D_800A4B04[equipId].itemCategory;
    if (itemCategory != ITEM_FOOD && itemCategory != ITEM_MEDICINE) {
        res->attack = CalcAttack(equipId, g_Status.equipment[1 - handId]);
        if (g_Player.unk0C & PLAYER_STATUS_POISON) {
            res->attack >>= 1;
        }
    }
}

bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (g_Status.mp >= mpCount) {
        if (subtractMp != 0) {
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
        func_8011AAFC(g_Entities, 99, 0);
        PlaySfx(NA_SE_PL_COLLECT_HEART);
    }
}

// Note: Arg3 is unused, but is given in the call from func_80113D7C
s32 HandleDamage(DamageParam* damage, s32 arg1, s32 amount, s32 arg3) {
    s32 ret;
    s32 itemCount;

    func_800F53A4();
    damage->unk0 = arg1 & ~0x1F;
    damage->damageKind = arg1 & 0x1F;
    if (g_Status.defenseElement & damage->unk0) {
        amount *= 2;
    }
    if (g_Status.D_80097C2A & damage->unk0) {
        amount /= 2;
    }
    if (g_Status.D_80097C2C & damage->unk0) {
        if (!(g_Status.D_80097C2C & damage->unk0 & 0x200)) {
            return 0;
        }
        damage->unk0 &= ~0x200;
    }

    if (g_Status.D_80097C2E & damage->unk0) {
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
    if (CheckEquipmentItemCount(ITEM_CAT_EYE_CIRCLET, HEAD_TYPE) != 0 &&
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
    itemCount = CheckEquipmentItemCount(ITEM_BALLROOM_MASK, HEAD_TYPE);
    if (itemCount != 0 && (damage->unk0 & 0xF980)) {
        if (itemCount == 1) {
            amount -= amount / 5;
        }
        if (itemCount == 2) {
            amount -= amount / 3;
        }
    }
    if (g_Player_unk0C & 0x80) {
        damage->damageTaken = g_Status.hpMax / 8;
        ret = 8;
    } else if (damage->unk0 & 0x200) {
        damage->damageTaken = amount - (g_Status.defenseEquip * 2);
        if (damage->damageTaken <= 0) {
            damage->damageTaken = 0;
        }
        ret = 7;
    } else if (damage->damageKind == 6) {
        if (D_8003C8C4 == ((D_8003C8C4 / 10) * 0xA)) {
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
        if (g_Player_unk0C & 0x4000) {
            damage->damageTaken *= 2;
        }
        // Check for player wearing a Talisman (chance to dodge attack)
        itemCount = CheckEquipmentItemCount(ITEM_TALISMAN, ACCESSORY_TYPE);
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
            if (g_Status.defenseEquip > 99 && !(damage->unk0 & 0x180) &&
                !(g_Player_unk0C & 0x80)) {
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
        if ((CheckEquipmentItemCount(ITEM_BLOOD_CLOAK, CAPE_TYPE) != 0) &&
            (ret != 9)) {
            AddHearts(damage->damageTaken);
        }
        // Fury Plate "DEF goes up when damage taken", that logic is not here
        // though.
        if (CheckEquipmentItemCount(ITEM_FURY_PLATE, ARMOR_TYPE) != 0) {
            if (*D_80139828 < 0x200) {
                *D_80139828 = 0x200;
            }
        }
    }
    return ret;
}

// !FAKE: explicitly casting two pointers to s32
// before comparing them, that's weird
void func_800FEE6C(void) {
    s32* var_v1 = D_80139828;

    do {
        if (*var_v1 != 0) {
            (*var_v1)--;
        }
        var_v1++;
    } while ((s32)var_v1 < (s32)&D_80139828[0x10]);
}

INCLUDE_ASM("dra/nonmatchings/5D6C4", func_800FEEA4);

s32 func_800FF064(s32 arg0) {
    s32 playerMP;

    playerMP = g_Status.mp - 4;

    if (playerMP > 0) {
        if (arg0 != 0) {
            g_Status.mp = playerMP;
        }
        return 0;
    }
    return -1;
}

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

void func_800FF0B8(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
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
    if (CheckEquipmentItemCount(ITEM_DRAGON_HELM, HEAD_TYPE) != 0) {
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
                damage += SquareRoot0(g_roomCount);
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
    return arg0 + ((u32)(arg0 * g_Status.statsTotal[3]) >> 7);
}

// Determine what type of item to drop
s32 func_800FF494(EnemyDef* arg0) {
    /* Ring of Arcana is an item that increases
     * enemy item drop rates when equipped
     */
    s32 ringOfArcanaCount =
        CheckEquipmentItemCount(ITEM_RING_OF_ARCANA, ACCESSORY_TYPE);
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

void func_800FF60C(void) {
    s32 var_a0_2;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (g_Status.equipment[CAPE_SLOT] == D_800A2FBC[i]) {
            break;
        }

        if (D_800A2FBC[i] == -1) {
            break;
        }
        i += 2;
    }

    var_a0_2 = D_800A2FC0[i];
    if (g_Status.equipment[CAPE_SLOT] == ITEM_REVERSE_CLOAK &&
        g_Settings.isCloakLiningReversed) {
        var_a0_2++;
    }
    func_800EA5E4(var_a0_2);
    if (g_Status.equipment[CAPE_SLOT] == ITEM_TWILIGHT_CLOAK) {
        func_800EA5E4(0x415);
    }
}

void func_800FF60C();

void func_800FF6C4(void) {
    if (g_StageId != STAGE_ST0 &&
        g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
        func_800FF60C();
    }
}

void func_800FF708(s32 arg0, s32 arg1) {
    s32 rnd;

    do {
    loop_1:
        rnd = rand() % 90;
        if (rnd == 0x19) {
            goto loop_1;
        }
    } while (D_800A7734[rnd].unk00 != arg0);
    g_Status.equipment[arg1 + 2] = rnd;
}

extern const char* g_CheatCodes[2];
// I cannot use the following declaration because it forces to import both data
// and rodata, leading to a linker error as we are not yet importing data in DRA
// const char g_CheatCodes[2][12] = {
// {'x', '-', 'x', '!', 'v', '\'', '\'', 'q', '\0', '\0', '\0', '\0'},
// {'a', 'x', 'e', 'a', 'r', 'm', 'o', 'r', '\0', '\n', '\r', '\n'},
// };
void InitStatsAndGear(bool isDeathTakingItems) {
    s32 prologueBonusState;
    s32 dracDefeatTime;
    u8* fileName;
    s32 equipId;
    s32 i;

    if (D_8003C730 != 0) {
        func_800F53A4();
        func_800FF60C();
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
            func_800FF60C();
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
            D_8006BB74[i] = 0;
        }
        g_roomCount = 0;

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
            (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {

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
                    AddToInventory(ITEM_POTION, HAND_TYPE);
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
                    AddToInventory(ITEM_HEART_REFRESH, HAND_TYPE);
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
                    AddToInventory(ITEM_NEUTRON_BOMB, HAND_TYPE);
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
                        AddToInventory(ITEM_AXE_LORD_ARMOR, ARMOR_TYPE);
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
                    if (D_800A872C[i].unk0 != 0) {
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

                AddToInventory(ITEM_FIREBRAND, HAND_TYPE);
                AddToInventory(ITEM_THUNDERBRAND, HAND_TYPE);
                AddToInventory(ITEM_ICEBRAND, HAND_TYPE);
                AddToInventory(ITEM_CLAYMORE, HAND_TYPE);
                AddToInventory(ITEM_MACE, HAND_TYPE);
                AddToInventory(ITEM_KATANA, HAND_TYPE);
                AddToInventory(ITEM_KNIGHT_SHIELD, HAND_TYPE);
                AddToInventory(ITEM_IRON_SHIELD, HAND_TYPE);
                AddToInventory(ITEM_BASILARD, HAND_TYPE);
                AddToInventory(ITEM_RAPIER, HAND_TYPE);
                AddToInventory(ITEM_KNUCKLE_DUSTER, HAND_TYPE);
                AddToInventory(ITEM_CUTLASS, HAND_TYPE);

                AddToInventory(ITEM_CLOTH_TUNIC, ARMOR_TYPE);
                AddToInventory(ITEM_BRONZE_CUIRASS, ARMOR_TYPE);
                AddToInventory(ITEM_IRON_CUIRASS, ARMOR_TYPE);
                AddToInventory(ITEM_STEEL_CUIRASS, ARMOR_TYPE);
                AddToInventory(ITEM_SILVER_PLATE, ARMOR_TYPE);
                AddToInventory(ITEM_GOLD_PLATE, ARMOR_TYPE);
                AddToInventory(ITEM_FIRE_MAIL, ARMOR_TYPE);
                AddToInventory(ITEM_MIRROR_CUIRASS, ARMOR_TYPE);

                AddToInventory(ITEM_VELVET_HAT, HEAD_TYPE);
                AddToInventory(ITEM_LEATHER_HAT, HEAD_TYPE);
                AddToInventory(ITEM_STEEL_HELM, HEAD_TYPE);

                AddToInventory(ITEM_CLOTH_CAPE, CAPE_TYPE);
                AddToInventory(ITEM_ELVEN_CLOAK, CAPE_TYPE);
                AddToInventory(ITEM_ROYAL_CLOAK, CAPE_TYPE);
                AddToInventory(ITEM_REVERSE_CLOAK, CAPE_TYPE);

                AddToInventory(ITEM_MEDAL, ACCESSORY_TYPE);
                AddToInventory(ITEM_GAUNTLET, ACCESSORY_TYPE);

                for (i = 0; i < 80; i++) {
                    AddToInventory(ITEM_POTION, HAND_TYPE);
                }

                for (i = 0; i < 10; i++) {
                    AddToInventory(ITEM_MAGIC_MISSILE, HAND_TYPE);
                    AddToInventory(ITEM_TURKEY, HAND_TYPE);
                    AddToInventory(ITEM_POT_ROAST, HAND_TYPE);
                    AddToInventory(ITEM_ANTIVENOM, HAND_TYPE);
                    AddToInventory(ITEM_BOOMERANG, HAND_TYPE);
                    AddToInventory(ITEM_JAVELIN, HAND_TYPE);
                    AddToInventory(ITEM_PENTAGRAM, HAND_TYPE);
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
                } while (D_800A4B04[equipId].itemCategory > 4);

                g_Status.equipment[LEFT_HAND_SLOT] = equipId;
                do {
                loop_check_equip_id_2:
                    equipId = rand() % 169;
                    if (equipId == 216) {
                        goto loop_check_equip_id_2;
                    }
                } while (D_800A4B04[equipId].itemCategory == 5);

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

void DrawHudRichter(void) {
    Primitive* prim;

    D_80137978 = 400;
    D_8013797C = 400;
    D_801397FC = 0;
    D_80139008 = 0;
    D_80137994 = 0;
    D_8003C744 = 0;
    D_80137980 = 48;
    D_80137984 = 0;
    D_80137990.unk0 = 0;
    D_8013798C = 40000 / D_80137978;
    D_80137988 = 40000 / D_8013797C;
    D_80137970 = func_800EDD9C(4, 9);
    prim = &g_PrimBuf[D_80137970];

    SetTexturedPrimRect(prim, 2, 22, 32, 96, 0, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x101;
    prim->priority = 0x1EF;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, D_80137980 + 216, 22, 32, 96, 32, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x100;
    prim->priority = 0x1EF;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, 4, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x105;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, D_80137980 + 228, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim->p1 = 0;
    prim->p2 = 6;
    prim = prim->next;

    SetTexturedPrimRect(prim, D_80137980 + 236, 112, 9, 3, 64, 89);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, 14, 27, 8, 8, 0, 96);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, 22, 27, 8, 8, 0, 96);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, 18, 38, 8, 8, 0, 0);
    prim->tpage = 0x1B;
    prim->clut = 0x102;
    prim->priority = 0x1F0;
    prim->blendMode = 0x2000;
    prim = prim->next;

    SetTexturedPrimRect(prim, 33, 20, 64, 24, 64, 40);
    prim->tpage = 0x1B;
    prim->clut = 0x103;
    prim->priority = 0x1EF;
    prim->blendMode = 0x2000;

    D_80137974 = func_800EDD9C(4, 16);
    prim = &g_PrimBuf[D_80137974];
    if (prim != 0) {
        s32 u = 32;
        s32 x = 216;
        do {
            SetTexturedPrimRect(prim, x, 22, 2, 96, u, 0);
            func_801072DC(prim);
            prim->tpage = 0x1B;
            prim->clut = 0x100;
            prim->priority = 0x1EE;
            prim->blendMode = BLEND_VISIBLE;
            prim->p1 = (rand() & 0x3F) + 1;
            prim->p2 = 0;
            prim = prim->next;
            u += 2;
            x += 2;
        } while (prim != 0);
    }
}

INCLUDE_ASM("dra/nonmatchings/5D6C4", func_80100B50);

extern Unkstruct_80137990 D_80137990;

bool func_8010183C(s32 arg0) {
    if (arg0 == 0) {
        if (D_80137990.unk0 == 0) {
            D_80137990.unk0 = 1;
            return true;
        }
        return false;
    } else if (arg0 == 1) {
        if (D_80137990.unk0 == 0x15) {
            D_80137990.unk0 = 0x33;
            return true;
        }
        return false;
    }
    return true;
}
void DrawHudRichter(void);

void func_8010189C(void) {
    Primitive* poly;
    s32 i;
    u16* new_var;

    D_8013B5E8 = 0;
    g_HealingMailTimer[0] = 0;
    g_DisplayHP[0] = g_Status.hp;

    if ((g_StageId == STAGE_ST0) ||
        (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4, 14);
    poly = &g_PrimBuf[D_80137970];

    if (poly != NULL) {
        for (i = 0; poly != NULL; i++) {
            SetTexturedPrimRect(
                poly, D_800A2EE8[i], D_800A2EF8[i], D_800A2F28[i],
                D_800A2F38[i], D_800A2F08[i], D_800A2F18[i]);
            poly->tpage = 0x1F;
            new_var = &D_800A2F48[i];
            poly->clut = *new_var;
            poly->priority = 0x1F0;
            poly->blendMode = D_800A2F64[i];

            if (i == 5) {
                SetPrimRect(
                    poly, D_800A2EED, D_800A2EFD, D_800A2F3D, D_800A2F2D);
                poly->y0 = poly->y2;
                poly->x1 = poly->x0;
                poly->x2 = poly->x3;
                poly->y3 = poly->y1;
            }

            if (i == 1) {
                poly->p1 = 0;
                poly->p2 = rand() + 8;
                poly->p3 = (7 & rand()) + 1;
            }

            poly = poly->next;
        }
    }
}

void DrawHudAlucard() {
    SubweaponDef subwpn;
    RECT rect;
    Primitive* prim;

    s32 statXPos;
    s32 hpdiff;
    s32 mpFillSteps;
    s32 leading_zeros;
    s32 digitSpacing;
    u16 clut;

    if (g_StageId == STAGE_ST0 || g_CurrentPlayableCharacter != 0) {
        func_80100B50();
        return;
    }
    func_800EB4F8(D_800C52F8[g_Status.subWeapon], 0, 0x3C0, 0x120);
    prim = &g_PrimBuf[D_80137970];
    if (g_Status.subWeapon != 0) {
        // This is 0x2031. Since blendMode is probably bits, write it this way.
        prim->blendMode = 0x2000 | 0x0020 | 0x0010 | 0x0001;
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
                prim->clut = D_800A2F7E[prim->p1];
                prim->u0 = D_800A2F9B[prim->p1];
                prim->v0 = D_800A2F9B[prim->p1 + 16];
                prim->u1 = D_800A2F9B[prim->p1] + 16;
                prim->v1 = D_800A2F9B[prim->p1 + 16];
                prim->u2 = D_800A2F9B[prim->p1];
                prim->v2 = D_800A2F9B[prim->p1 + 16] + 16;
                prim->u3 = D_800A2F9B[prim->p1] + 16;
                prim->v3 = D_800A2F9B[prim->p1 + 16] + 16;
            }
        }
        if (prim->p1 != 0) {
            prim->blendMode = 0x2000;
        } else {
            prim->blendMode = BLEND_VISIBLE;
        }
        prim = prim->next;
        prim->blendMode = 0x2000;
    } else {
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
        prim->blendMode = BLEND_VISIBLE;
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
        if (!(D_8003C8C4 & 0x3F)) {
            g_Status.mp++;
        }
        if ((CheckEquipmentItemCount(ITEM_MYSTIC_PENDANT, ACCESSORY_TYPE) !=
             0) &&
            ((D_8003C8C4 & 0x3F) == 0x1F)) {
            g_Status.mp++;
        }
        if (g_Status.mp > g_Status.mpMax) {
            g_Status.mp = g_Status.mpMax;
        }
    }

    if ((CheckEquipmentItemCount(ITEM_HEALING_MAIL, ARMOR_TYPE)) &&
        ((g_Player.unk0C & 0x04000007) == 0x04000000)) {
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
    LoadTPage(D_800C52F8[10] + 1, 0, 0, 0x3DC, 0x100, 8, mpFillSteps);
    // Use one clut if MP is full, otherwise a different one
    prim->clut = mpFillSteps == 50 ? 0x162 : 0x174;

    if (D_8013B5E8 == 0) {
        hpdiff = g_Status.hp - g_DisplayHP[0];
        if (hpdiff > 0) {
            if (hpdiff >= 11) {
                g_DisplayHP[0] += (hpdiff) / 10;
            } else {
                g_DisplayHP[0]++;
            }
        }
        if (hpdiff < 0) {
            if (hpdiff < -10) {
                g_DisplayHP[0] += (hpdiff) / 10;
            } else {
                g_DisplayHP[0]--;
            }
        }
    } else {
        D_8013B5E8--;
    }
    if (g_DisplayHP[0] == g_Status.hpMax) {
        func_800EA5E4(2); // Likely related to HP showing bold when full
    } else if (g_DisplayHP[0] <= g_Status.hpMax >> 2) {
        func_800EA5E4(3); // Show yellow if under 1/4 health
    } else {
        func_800EA5E4(1); // Normal health display
    }

    if (g_DisplayHP[0] >= 1000) {
        leading_zeros = 0;
        digitSpacing = 6;
        statXPos = 3;
    } else if (g_DisplayHP[0] >= 100) {
        leading_zeros = 1;
        digitSpacing = 6;
        statXPos = 0;
    } else {
        digitSpacing = 7;
        statXPos = -6;
        if (g_DisplayHP[0] >= 10) {
            leading_zeros = 2;
        } else {
            leading_zeros = 3;
        }
    }
    // Thousands digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_DisplayHP[0] / 1000) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos;
    prim->x1 = prim->x3 = statXPos + 8;
    prim->blendMode = 0x2000;

    if (leading_zeros != 0) {
        leading_zeros--;
        prim->blendMode = BLEND_VISIBLE;
    }
    // Hundreds digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_DisplayHP[0] / 100) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + digitSpacing;
    prim->x1 = prim->x3 = statXPos + digitSpacing + 8;
    prim->blendMode = 0x2000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->blendMode = BLEND_VISIBLE;
    }
    // Tens digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_DisplayHP[0] / 10) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + (digitSpacing * 2);
    prim->x1 = prim->x3 = statXPos + (digitSpacing * 2) + 8;
    prim->blendMode = 0x2000;

    if (leading_zeros != 0) {
        prim->blendMode = BLEND_VISIBLE;
    }
    // Ones digit of HP
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_DisplayHP[0] % 10) * 8) + 0x20;
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
    } else if (g_blinkTimer & 2) {
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
    prim->blendMode = 0x2000;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->blendMode = BLEND_VISIBLE;
    }
    // Hundreds digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_Status.hearts / 100) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 4;
    prim->x1 = prim->x3 = statXPos + 0xC;
    prim->blendMode = 0x2000;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->blendMode = BLEND_VISIBLE;
    }
    // Tens digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = (((g_Status.hearts / 10) % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 8;
    prim->x1 = prim->x3 = statXPos + 0x10;
    prim->blendMode = 0x2000;
    prim->clut = clut;
    if (leading_zeros != 0) {
        prim->blendMode = BLEND_VISIBLE;
    }
    // Ones digit of hearts
    prim = prim->next;
    prim->u2 = prim->u0 = ((g_Status.hearts % 10) * 8) + 0x20;
    prim->u3 = prim->u1 = prim->u0 + 8;
    prim->x0 = prim->x2 = statXPos + 0xC;
    prim->x1 = prim->x3 = statXPos + 0x14;
    prim->clut = clut;
}

void func_801024DC(void) {
    Primitive* prim;
    Primitive* prim2;
    s32 x;

    D_8013799C = AllocPrimitives(PRIM_TILE, 4);
    prim = &g_PrimBuf[D_8013799C];
    for (x = 0; prim != 0; x++) {
        prim->x0 = (x & 1) << 7;
        prim->u0 = 0x80;
        prim->v0 = 0xF0;
        prim->priority = 0x1FD;
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
    }
    D_801379A8 = 0;
    D_801379A4 = 0;

    D_801379A0 = AllocPrimitives(PRIM_GT4, 1);
    prim2 = &g_PrimBuf[D_801379A0];
    prim2->u1 = 0xFF;
    prim2->v2 = 0xFF;
    prim2->u3 = 0xFF;
    prim2->v3 = 0xFF;
    prim2->tpage = 0x1D;
    prim2->clut = 0x1C0;
    prim2->priority = 0x1FE;
    prim2->u0 = 0;
    prim2->v0 = 0;
    prim = prim2;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->blendMode = BLEND_VISIBLE;
}

extern Unkstruct_80086FFA D_80086FFA[];

u16 func_801025F4(void) { return D_80086FFA[D_8013799C].unk0; }

void func_80102628(s32 arg0) {
    Primitive* poly;
    s32 temp;
    s32 i = 0;

    poly = &g_PrimBuf[D_8013799C];

    if (poly != NULL) {
        temp = arg0 / 2;
        while (poly != NULL) {
            poly->y0 = 0;
            poly->u0 = (u8)temp;
            poly->v0 = 0xF0;
            poly->b0 = 0;
            poly->g0 = 0;
            poly->r0 = 0;
            poly->priority = 0x1FD;
            poly->blendMode = BLEND_VISIBLE;
            poly->x0 = temp * (i & 1);
            poly = poly->next;
            i++;
        }
    }
}

void func_801026BC(s32 arg0) {
    Primitive* poly = &g_PrimBuf[D_801379A0];

    if (arg0 == 0) {
        poly->blendMode = BLEND_VISIBLE;
        return;
    } else if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
        SetPrimRect(poly, 0, 1, 255, 255);
    } else {
        poly->x2 = 255;
        poly->x0 = 255;
        poly->y1 = 240;
        poly->y0 = 240;
        poly->x3 = 0;
        poly->x1 = 0;
        poly->y3 = -15;
        poly->y2 = -15;
    }

    func_80107250(poly, arg0 * 2);

    if (arg0 == 0x40) {
        poly->blendMode = 0;
    } else {
        poly->blendMode = 0x35;
    }
}

void func_801027A4(void) { func_801026BC(0); }
