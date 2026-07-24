// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/scl.h"

void PlaySfx(s32 sfxId);
void func_0606D880(void);
s32 CalcAttack(s32 equipId, s32 otherEquipId);
void make_all(void);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606E0D0, func_0606E0D0);

extern u16 DAT_0605cea0;
extern s32 DAT_0605c11a;
extern Unk0605cd70 DAT_0605cd70;

void func_0606EEF8(u16);
void func_06005208(s32);
void func_0606F14C(void);
void RunMainEngine(void);
void SubDisp(void);
void func_060728B4(void);
void CheckWeaponCombo(void);

// original name: MODE_GAME
void ModeGame(void) {
    switch (DAT_0605cea0) {
    case 1:
        func_0606EEF8(DAT_0605c11a);
        UpdateCapePalette();
        CheckWeaponCombo();
        func_06005208(1);
        DAT_0605cea0++;
        break;
    case 2:
        DAT_0605cea0++;
    case 3:
        switch (DAT_0605cd70.unk2) {
        case 1:
            RunMainEngine();
            func_0606F14C();
            break;
        case 4:
            SubDisp();
            break;
        case 5:
            func_060728B4();
            break;
        }
        break;
    }
}

extern SaturnStageFileRecord g_StageFileRecords[];
extern s32 DAT_0605c108;
extern s32 DAT_0605c10c;
extern s32 DAT_06061dd0;
extern u16 DAT_06065470;
extern s32 DAT_0608609c;

void func_0606F01C(void);
void func_06074AA8(void);

void func_0606EEF8(u16 param_1) {
    u16 stageID;

    g_GameTimer = 0;
    memset(g_Entities, 0, sizeof(g_Entities));
    stageID = DAT_0605d750.stageID;
    if (param_1 == 0) {
        func_0606F01C();
        DAT_0608609c = DAT_0605c10c;
    } else {
        DAT_0608609c = DAT_0605c10c;
    }
    func_0600FEFC();
    func_800FDE00();
    if (DAT_06061dd0 == 0) {
        DAT_0605c108 = g_StageFileRecords[stageID].unk14;
    }
    DAT_0605d750.unk2 = stageID;
    func_06032E88(1);
    SCL_SET_CCRTMD(0);
    SCL_SET_CCMD(1);
    SCL_SetColMixMode(6, 1);
    SCL_SET_SPCCEN(1);
    DAT_06065470 &= 0xFFFB;
    SclProcess = 1;
    func_06074AA8();
}

extern s16 g_ButtonMask[];

void func_0606F01C(void) {
    s32 i;
    u8* ptr;

    for (i = 0; i < 0x300; i++) {
        g_CastleFlags[i] = 0;
    }
    g_CastleFlags[0xB9] = 1;
    g_CastleFlags[0x9B] = 1;
    if (g_PlayableCharacter != 0) {
        g_CastleFlags[0x35] = 1;
        g_CastleFlags[0x62] = 1;
        g_CastleFlags[0x63] = 1;
        g_CastleFlags[0x85] = 1;
        g_CastleFlags[0x95] = 1;
        g_CastleFlags[0x96] = 1;
    }
    for (i = 0, ptr = (u8*)&g_MenuNavigation; i < sizeof(MenuNavigation); i++) {
        *ptr++ = 0;
    }
    for (i = 0; i < 8; i++) {
        g_Settings.buttonConfig[i] = i;
        g_Settings.buttonMask[i] = g_ButtonMask[i];
    }
    for (i = 0; i < 6; i++) {
        g_Settings.cloakColors[i] = 0;
    }
    g_Settings.windowColors[0] = 0;
    g_Settings.windowColors[1] = 0;
    g_Settings.windowColors[2] = 8;
    g_Settings.isCloakLiningReversed = 0;
    for (i = 0; i < 11; i++) {
        g_Settings.equipOrderTypes[i] = i;
    }
    D_8003C708.flags = 0;
    if (g_PlayableCharacter != 0) {
        g_Status.timerFrames = g_Status.timerMinutes = g_Status.timerHours = 0;
        g_Status.timerSeconds = 1;
    }
}

void func_0606F14C(void) {
    g_Status.timerFrames += DAT_0605c10c - DAT_0608609c;
    DAT_0608609c = DAT_0605c10c;
    if (g_Status.timerFrames >= 60) {
        g_Status.timerFrames -= 60;
        g_Status.timerSeconds++;
        if (g_Status.timerSeconds >= 60) {
            g_Status.timerSeconds -= 60;
            g_Status.timerMinutes++;
            if (g_Status.timerMinutes >= 60) {
                g_Status.timerMinutes -= 60;
                g_Status.timerHours++;
                if (g_Status.timerHours >= 100) {
                    g_Status.timerSeconds = 59;
                    g_Status.timerMinutes = 59;
                    g_Status.timerHours = 99;
                }
            }
        }
    }
}

void TekiInit(Entity*, u16);

void func_0606F1C8(Entity* entity) {
    u8 pad[4];

    switch (entity->step) {
    case 0:
        TekiInit(entity, 3);
        entity->palette = (entity->entityId == 1) ? 0x83FF : 0x83E0;
        entity->step++;
        break;

    case 1: // could be any number, required for match
        break;
    }
}

s32 TimeAttackController(s32 eventId, s32 action) {
    switch (action) {
    case 0:
        return g_Settings.timeAttackRecords[eventId];

    case 1:
        if (g_Settings.timeAttackRecords[eventId] != 0) {
            return 1;
        }
        g_Settings.timeAttackRecords[eventId] = g_Status.timerSeconds;
        g_Settings.timeAttackRecords[eventId] += g_Status.timerMinutes * 100;
        g_Settings.timeAttackRecords[eventId] += g_Status.timerHours * 10000;
        break;

    case 2:
        g_Settings.D_8003CB00 |= (1 << eventId);
        break;
    }
    return 0;
}

// FILE SPLIT HERE

bool CalcPlayerDamage(DamageParam* damage) {
    if (damage->damageKind != DAMAGEKIND_5) {
        if (damage->damageKind >= DAMAGEKIND_16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if ((damage->damageTaken * 20) > g_Status.hpMax) {
            damage->damageKind = DAMAGEKIND_2;
        } else {
            damage->damageKind = DAMAGEKIND_3;
        }
    }
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        return true;
    }
    g_Status.hp -= damage->damageTaken;
    return false;
}

// SAT: func_0606F328
s32 func_800FD664(s32 arg0) {
    if (DAT_0605d750.stageID & STAGE_INVERTEDCASTLE_FLAG) {
        arg0 *= 2;
    }
    return arg0;
}

// SAT: func_0606F348
u8 GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}

// SAT: func_0606F378
s32 func_800FD6C4(EquipKind equipTypeFilter) {
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

// SAT: func_0606F3D8
inline u8* GetEquipOrder(EquipKind kind) {
    switch (kind) {
    case EQUIP_HAND:
        return g_Status.equipHandOrder;
    }
    return g_Status.equipBodyOrder;
}

// SAT: func_0606F3F8
inline u8* GetEquipCount(EquipKind kind) {
    switch (kind) {
    case EQUIP_HAND:
        return g_Status.equipHandCount;
    }
    return g_Status.equipBodyCount;
}

// SAT: func_0606F418
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
    case 0: {
        s32 isInLeftHand = g_Status.equipment[0] == itemId;
        s32 isInRightHand = g_Status.equipment[1] == itemId;
        return isInLeftHand + isInRightHand;
    }
    case 1:
        return g_Status.equipment[3] == itemId;
    case 2:
        return g_Status.equipment[4] == itemId;
    case 3:
        return g_Status.equipment[5] == itemId;
    case 4: {
        s32 isAcc1 = g_Status.equipment[6] == itemId;
        s32 isAcc2 = g_Status.equipment[7] == itemId;
        return isAcc1 + isAcc2;
    }
    }
    return 0;
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
    if (existingItemSlot > emptySlot) {
        order[existingItemSlot] = order[emptySlot];
        order[emptySlot] = id;
    }
}

// SAT: func_0606F59C
void GetSpellDef(SpellDef* spell, s32 id) {
    *spell = g_SpellDefs[id];
    spell->attack += (g_Status.statsTotal[2] * 2 + (rand() % 12)) / 10;
    if (CheckEquipmentItemCount(0x15, 2) != 0) {
        spell->attack = spell->attack + spell->attack / 2;
    }
}

// original name: etc_hosei
s16 GetStatusAilmentTimer(s32 statusAilment, s16 timer) {
    s16 ret;
    s32 petrify_adjustment;

    switch (statusAilment) {
    case 0:
        ret = timer;
        ret -= g_Status.statsTotal[1] * 16;
        if (ret < 0x100) {
            ret = 0x100;
        }
        break;
    case 1:
        ret = timer;
        ret -= g_Status.statsTotal[1] * 4;
        if (ret < 0x40) {
            ret = 0x40;
        }
        break;
    case 2:
        ret = timer;
        petrify_adjustment = ((g_Status.statsTotal[1] + rand() % 12) - 9) / 10;
        if (petrify_adjustment < 0) {
            petrify_adjustment = 0;
        }
        if (4 < petrify_adjustment) {
            petrify_adjustment = 4;
        }
        ret -= petrify_adjustment;
        break;
    case 3:
        ret = timer;
        ret += g_Status.statsTotal[2] * 4;
        break;
    case 4:
    case 5:
        ret = timer;
        if (CheckEquipmentItemCount(0x52, 4) != 0) {
            ret += ret / 2;
        }
        break;
    }

    return ret;
}

// SAT: func_0606F760
bool CastSpell(SpellIds spellId) {
    u8 mpUsage = g_SpellDefs[spellId].mpUsage;

    if (g_Status.mp < mpUsage) {
        return false;
    } else {
        g_Status.mp -= mpUsage;
        return true;
    }
}

// _waza_work_set
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F798, func_0606F798);

// original name: reduce_weapon
bool ReduceWeapon(s32 hand) {
    s32* equippedItem;
    bool isConsumable;

    if (hand > 2) {
        return true;
    }
    equippedItem = &g_Status.equipment[hand];
    isConsumable = g_EquipDefs[*equippedItem].isConsumable;
    if (CheckEquipmentItemCount(0x56, 4)) {
        return false;
    }
    if (isConsumable) {
        if (!g_Status.equipHandCount[*equippedItem]) {
            *equippedItem = 0;
            make_all();
            return true;
        }
        g_Status.equipHandCount[*equippedItem]--;
    }
    return false;
}

// SAT: func_0606F884
// no return value on PSX?
s32 func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
    return 0;
}

extern s32 g_LevelHPIncrease[];
extern s32 g_ExpNext[];

// original name: check_experience
u32 CheckAndDoLevelUp(void) {
    s32 statgain;
    s32 i;
    s32 statsGained;
    bool maxMp;

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
        if (g_Status.mp == g_Status.mpMax) {
            maxMp = true;
        } else {
            maxMp = false;
        }
        g_Status.mpMax += 4 + (rand() & 1);
        if (maxMp) {
            g_Status.mp = g_Status.mpMax;
        }
        g_Status.hp += g_LevelHPIncrease[g_Status.level / 10];
        g_Status.hpMax += g_LevelHPIncrease[g_Status.level / 10];
        g_Status.heartsMax += 2;
        statsGained = 0;
        CheckAndDoLevelUp();
        for (i = 0; i < 4; i++) {
            statgain = rand() & 1;
            g_Status.statsBase[i] += statgain;
            if (g_Status.statsBase[i] > 99) {
                g_Status.statsBase[i] = 99;
                statgain = 0;
            }
            statsGained += statgain;
        }
        if (statsGained < 2) {
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

// SAT: func_0606FA30
s32 func_800FE044(s32 amount, s32 type) {
    s32 iVar4;
    u32 uVar8;
    s32 oldHeartMax;
    u32 playerXPBoost;
    s32 i;
    s32 levelDiff;
    s32 activeFamiliar;

    if (type == 0x8000) {
        if (g_Status.hpMax == 9999) {
            return 1;
        }
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
        g_Status.hearts += g_Status.heartsMax - oldHeartMax;
        D_80137964++;
        return 0;
    }
    if (type == 0x2000) {
        g_Status.relics[amount] = 3;
        if (g_RelicDefs[amount].unk0C) {
            g_Status.relics[amount] = 1;
        }
        D_80137968++;
        return 0;
    }
    if (amount == 0) {
        return 1;
    }

    if (g_Status.level == 99) {
        return 1;
    }
    playerXPBoost = amount;
    if (g_Status.level > type) {
        levelDiff = g_Status.level - type;
        for (i = 0; i < levelDiff; i++) {
            playerXPBoost = playerXPBoost * 2 / 3;
        }
        if (playerXPBoost == 0) {
            playerXPBoost = 1;
        }
    }
    if (g_Status.level < type) {
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
        return 0;
    }
    activeFamiliar = g_Servant - 1;
    playerXPBoost = amount / g_Status.statsFamiliars[activeFamiliar].level;
    for (i = 0; playerXPBoost > 0; i++) {
        playerXPBoost = playerXPBoost / 2;
    }
    if (i < 1) {
        i = 1;
    }
    g_Status.statsFamiliars[activeFamiliar].exp += i;
    if (g_Status.statsFamiliars[activeFamiliar].exp > 9899) {
        g_Status.statsFamiliars[activeFamiliar].exp = 9899;
    }
    g_Status.statsFamiliars[activeFamiliar].level =
        (g_Status.statsFamiliars[activeFamiliar].exp / 100) + 1;
    return 0;
}

// SAT: func_0606FC60
inline bool IsRelicActive(s32 relicId) {
    if (g_Status.relics[relicId] & 2) {
        return 1;
    }
    return 0;
}

// SAT: func_0606FC80
s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts) {
    u32 accessoryCount;

    if (subweaponId == 0) {
        *subwpn = g_SubwpnDefs[g_Status.subWeapon];
        accessoryCount = CheckEquipmentItemCount(0x4F, 4); // 4F instead of 4D
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
        if (CheckEquipmentItemCount(0x14, 2) != 0) {
            subwpn->attack += 10;
        }
        if (subweaponId == 4 || subweaponId == 12) {
            accessoryCount =
                CheckEquipmentItemCount(0x3e, 4); // 3e instead of 3d
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

// SAT: func_0606FE60
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId) {
    s32 criticalRate;
    u8 itemCategory;

    *res = g_EquipDefs[equipId]; // hack not needed
    criticalRate = res->criticalRate;
    criticalRate +=
        SquareRoot0((g_Status.statsTotal[3] * 2) + (rand() & 0xF)) - 5;
    if (criticalRate > 255) {
        criticalRate = 255;
    }
    if (criticalRate < 0) {
        criticalRate = 0;
    }
    if (DAT_0605d750.stageID == STAGE_ST0) {
        criticalRate = 0;
    }

    res->criticalRate = criticalRate;
    func_0606D880();
    itemCategory = g_EquipDefs[equipId].itemCategory;
    if (itemCategory == ITEM_FOOD || itemCategory == ITEM_MEDICINE) {
        return;
    }
    res->attack = CalcAttack(equipId, g_Status.equipment[1 - handId]);
    if (g_Player.status & PLAYER_STATUS_POISON) {
        res->attack >>= 1;
    }
}

// SAT: func_0606FFA0
bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (mpCount <= g_Status.mp) {
        if (subtractMp) {
            g_Status.mp -= mpCount;
        }
        return false;
    }
    return true;
}

// SAT: func_0606FFC8
inline void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

// SAT: func_0606FFE4
inline void AddHearts(s32 value) {
    Entity* player;
    if (g_Status.hearts < g_Status.heartsMax) {
        g_Status.hearts += value;
        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
        player = &PLAYER;
        g_api.CreateEntFactoryFromEntity(player, 99, 0); // g_api is new

        PlaySfx(SFX_HEART_PICKUP);
    }
}

// original name: get_damage_sub
s32 HandleDamage(DamageParam* damage, s32 arg1, s32 amount) {
    s32 ret;
    s32 itemCount;

    make_all();
    damage->effects = arg1 & ~0x1F;
    damage->damageKind = arg1 & 0x1F;
    // Damage doubled, weakness
    if (g_Status.elementsWeakTo & damage->effects) {
        amount *= 2;
    }
    // Damage halved, resistance
    if (g_Status.elementsResist & damage->effects) {
        amount /= 2;
    }
    // Immune, zero damage
    if (g_Status.elementsImmune & damage->effects) {
        if ((g_Status.elementsImmune & damage->effects) & 0x200) {
            damage->effects &= 0xFFFFFDFF;
        } else {
            return 0;
        }
    }
    // Absorb, hp goes up based on damage amount
    if (g_Status.elementsAbsorb & damage->effects) {
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
    if (CheckEquipmentItemCount(0x2B, 1) != 0 && damage->damageKind == 7) {
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

    itemCount = CheckEquipmentItemCount(0x1C, 1);
    if ((itemCount != 0) &&
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
        damage->damageTaken = amount - g_Status.defenseEquip * 2;
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
        if (damage->damageKind < 0x10) {
            damage->damageTaken = amount - g_Status.defenseEquip;
        } else {
            damage->damageTaken = g_Status.hpMax / 8;
        }
        if (g_Player.status & PLAYER_STATUS_POISON) {
            damage->damageTaken *= 2;
        }
        // Check for player wearing a Talisman (chance to dodge attack)
        itemCount = CheckEquipmentItemCount(0x55, 4);
        if (itemCount != 0) {
            if (g_Status.statsTotal[3] * itemCount >= (rand() & 0x1FF)) {
                return 2;
            }
        }
        if (damage->damageTaken > 0) {
            if (damage->damageKind == 0 || damage->damageKind == 1) {
                if (damage->damageTaken * 2 >= g_Status.hpMax) {
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
        if ((CheckEquipmentItemCount(0x37, 3) != 0) && (ret != 9)) {
            AddHearts(damage->damageTaken);
        }
        // Fury Plate "DEF goes up when damage taken", so here we get 0x200
        // frames of defense stat buff.
        if (CheckEquipmentItemCount(0x16, 2) != 0) {
            if (g_StatBuffTimers[0] < 0x200) {
                g_StatBuffTimers[0] = 0x200;
            }
        }
    }
    return ret;
}

void DecrementStatBuffTimers(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        if (!g_StatBuffTimers[i]) {
            continue;
        }
        switch ((u32)i) {
        default:
            // !FAKE
            i++;
            i--;
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
            g_StatBuffTimers[i]--;
        }
    }
}

s32 HandleTransformationMP(s32 form, s32 mode) {
    if (form == 0) {
        if (!IsRelicActive(0)) {
            return -1;
        }
        if (g_Status.mp - 1 > 0) {
            if (mode != 0) {
                if (g_GameTimer % 60 == 0) {
                    g_Status.mp -= 1;
                }
            }
            return 0;
        }
        return -1;
    } else if (form == 1) {
        if (!IsRelicActive(7)) {
            return -1;
        }
        if (IsRelicActive(8)) {
            if (g_Status.mp - 2 > 0) {
                if (mode != 0) {
                    if (g_GameTimer % 30 == 0) {
                        g_Status.mp -= 2;
                    }
                }
                return 0;
            }
            return -1;
        } else {
            if (g_Status.mp - 10 > 0) {
                if (mode != 0) {
                    if (g_GameTimer % 8 == 0) {
                        g_Status.mp -= 10;
                    }
                }
                return 0;
            }
            return -1;
        }
    } else if (form == 2) {
        if (!IsRelicActive(4)) {
            return -1;
        }
        if (g_Status.mp - 1 > 0) {
            if (mode != 0) {
                if (g_GameTimer % 120 == 0) {
                    g_Status.mp -= 1;
                }
            }
            return 0;
        }
        return -1;
    }
    return -1;
}

// SAT: func_06070540
s32 HandleGravityBootsMP(s32 mode) {
    if ((g_Status.mp - 4) > 0) {
        if (mode != 0) {
            g_Status.mp -= 4;
        }
        return 0;
    }
    return -1;
}

// SAT: func_06070568
inline void ClearStatBuff(s32 i) { g_StatBuffTimers[i] = 0; }

void ClearStatBuffs(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        ClearStatBuff(i);
    }
}

// SAT: func_060705A0
void GiveStatBuff(s32 i) { g_StatBuffTimers[i] = 0x1000; }

// SAT: func_060705B8
s32 GetStatBuffTimer(s32 i) { return g_StatBuffTimers[i]; }

// SAT: func_060705CC
u16 DealDamage(Entity* enemyEntity, Entity* attackerEntity) {
    s32 stats[4];
    EnemyDef sp20;
    EnemyDef* enemy;
    u16 element;
    u16 elementMask;
    u16 maskedElement;
    s32 higherStatIdx;
    s32 i;
    u16 damage;
    u16 result;

    enemy = &sp20;
    sp20 = g_EnemyDefs[enemyEntity->enemyId];
    if (CheckEquipmentItemCount(0x2D, 1) != 0) {
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
    maskedElement = element & elementMask;
    if (maskedElement == (maskedElement & (elementMask & enemy->immunes))) {
        result = DAMAGE_FLAG_IMMUNE;
    } else if (
        maskedElement == (maskedElement & (elementMask & enemy->absorbs))) {
        result = damage + DAMAGE_FLAG_ABSORB;
    } else {
        if (maskedElement ==
            (maskedElement & (elementMask & enemy->strengths))) {
            damage /= 2;
        }
        if (element & enemy->weaknesses) {
            damage *= 2;
        }
        if (attackerEntity->entityRoomIndex > (rand() & 0xFF)) {
            for (i = 0; i < 4; i++) {
                stats[i] = (rand() & 0x3F) + g_Status.statsBase[i];
            }

            higherStatIdx = 0;
            for (i = 1; i < 4; i++) {
                if (stats[i] > stats[higherStatIdx]) {
                    higherStatIdx = i;
                }
            }

            switch (higherStatIdx) {
            case 0:
                damage *= 2;
                break;
            case 1:
                if (enemy->defense > damage) {
                    damage += enemy->defense / 2;
                } else {
                    damage += damage / 2;
                }
                break;
            case 2:
                damage += SquareRoot0(g_RoomCount);
                break;
            case 3:
                damage += (rand() % g_Status.statsTotal[3]) + 1;
                break;
            }
            result = DAMAGE_FLAG_CRITICAL;
        } else {
            result = DAMAGE_FLAG_NORMAL;
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
    }

    return result;
}

// SAT: func_060707F0
s32 func_800FF460(u32 arg0) {
    s32 res;

    if (arg0 == 0) {
        return 0;
    }
    res = arg0 + (arg0 * g_Status.statsTotal[3]) / 0x80;
    return res;
}

// SAT: func_06070820
// Determine what type of item to drop
s32 func_800FF494(EnemyDef* arg0) {
    // 0x4B is the item ID for Ring of Arcana
    // Ring of Arcana is an item that increases enemy item drop rates when
    // equipped
    s32 ringOfArcanaCount = CheckEquipmentItemCount(0x4D, 4); // 4d not 4b
    s32 rnd = rand() & 0xFF;

    rnd -= (g_Status.statsTotal[3] + (rand() & 0x1F)) / 20;

    if (ringOfArcanaCount != 0) {
        rnd -= arg0->rareItemDropRate * ringOfArcanaCount;
    }

    if (rnd < arg0->rareItemDropRate) {
        return 0x40; // drop the enemy's rare item
    }

    // drop a common item, typically hearts or money
    rnd -= arg0->rareItemDropRate;
    if (ringOfArcanaCount != 0) {
        rnd -= arg0->uncommonItemDropRate * ringOfArcanaCount;
    }
    rnd -= (g_Status.statsTotal[3] + (rand() & 0x1F)) / 20;

    if (rnd < arg0->uncommonItemDropRate) {
        return 0x20; // drop the enemy's uncommon item
    }
    rnd = rand() % 28;
    if (!arg0->rareItemDropRate) {
        rnd++;
    }
    if (!arg0->uncommonItemDropRate) {
        rnd++;
    }
    rnd += ringOfArcanaCount;
    return rnd;
}
