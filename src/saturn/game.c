// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

// __game_start
INCLUDE_ASM("asm/saturn/game/data", d6066000, d_06066000);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066040, func_06066040);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60661BC, func_060661BC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066330, func_06066330);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066400, func_06066400);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60664E0, func_060664E0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60665BC, func_060665BC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60666A4, func_060666A4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066854, func_06066854);

#define FLAG_UNK_20000 0x20000
#define STAGE_ENTITY_START 64
#define TOTAL_ENTITY_COUNT 256

void (*func_06064684)();

// SAT: func_060668D4
void func_8011A9D8(void) {
    Entity* entity;
    s32 i;

    func_06064684();

    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = STAGE_ENTITY_START; i < TOTAL_ENTITY_COUNT; i++, entity++) {
        if (!(entity->flags & FLAG_UNK_20000)) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("asm/saturn/game/data", d606692C, d_0606692C);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066B30, func_06066B30);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066B74, func_06066B74);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066CE0, func_06066CE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066FE0, func_06066FE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067090, func_06067090);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60674B8, func_060674B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067958, func_06067958);
INCLUDE_ASM("asm/saturn/game/data", d606797C, d_0606797C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067A04, func_06067A04);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B6F8, func_0606B6F8);

// _READ_SUB_OUT_MODE
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B760, func_0606B760);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BB4C, func_0606BB4C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BEE4, func_0606BEE4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C064, func_0606C064);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C088, func_0606C088);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C160, func_0606C160);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C3E4, func_0606C3E4);

void FUN_0606c504(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[0];
    for (i = 0; i < TOTAL_ENTITY_COUNT; i++, entity++) {
        if (entity->unk68) {
            s32 temp = entity->unk68 * 0x100;
            entity->posX.val += arg0 * temp;
            entity->posY.val += arg1 * temp;
        } else {
            if (entity->flags & FLAG_POS_CAMERA_LOCKED) {
                entity->posX.i.hi += arg0;
                entity->posY.i.hi += arg1;
            }
            if (entity->flags & FLAG_POS_PLAYER_LOCKED) {
                entity->posX.val -= arg2;
                entity->posY.val -= arg3;
            }
        }
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C594, func_0606C594);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C774, func_0606C774);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606CA10, func_0606CA10);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D058, func_0606D058);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D2D0, func_0606D2D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D358, func_0606D358);

// _PSX_POSITION_GET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D3FC, func_0606D3FC);

// _PSX_TO_STAGE_NO_GET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D554, func_0606D554);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D5FC, func_0606D5FC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D6DC, func_0606D6DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D798, func_0606D798);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D804, func_0606D804);

static inline bool IsAlucart(void) {
    if (CheckEquipmentItemCount(0xAB, 0) && CheckEquipmentItemCount(0xAA, 0) &&
        CheckEquipmentItemCount(0x5B, 2))
        return true;
    return false;
}

extern u8 DAT_06057f62;

void func_0606D880(void) {
    s32* statsPtr;
    s32 correctStonesEquipped;
    s32 hourOfDay;
    s32 i, j;
    s32 statBonus;

    statsPtr = g_Status.statsEquip;
    for (i = 0; i < 4; i++) {
        *statsPtr++ = 0;
    }

    // Iterate through each Item Slot
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus =
                g_AccessoryDefs[g_Status.equipment[3 + i]].statsBonus[j];
            if (statBonus > 0x80) {
                statBonus -= 0x100;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }

    // different
    hourOfDay = (DAT_06057f62 / 16) * 10 + DAT_06057f62 % 16;

    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3C, 4);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3B, 4);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    }

    if (g_StatBuffTimers[4]) {
        g_Status.statsEquip[0] += 20;
    }
    if (g_StatBuffTimers[3]) {
        g_Status.statsEquip[2] += 20;
    }
    if (g_StatBuffTimers[2]) {
        g_Status.statsEquip[3] += 20;
    }
    if (g_Status.relics[0x1B] & 2) {
        g_Status.statsEquip[1] += 10;
    }
    if (g_Status.relics[0x1D] & 2) {
        g_Status.statsEquip[3] += 10;
    }
    if (g_Status.relics[0x1A] & 2) {
        g_Status.statsEquip[0] += 10;
    }
    if (g_Status.relics[0x1C] & 2) {
        g_Status.statsEquip[2] += 10;
    }
    if (IsAlucart()) {
        g_Status.statsEquip[3] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] = g_Status.statsBase[1] + g_Status.statsEquip[1] * 8;
    g_Status.statsTotal[2] = g_Status.statsBase[2] + g_Status.statsEquip[2] * 4;
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

extern u8 DAT_060850ec[];

s32 CalcAttack(s32 equipId, s32 otherEquipId) {
    s32 i;
    s16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (g_EquipDefs[equipId].itemCategory == 6 ||
        g_EquipDefs[equipId].itemCategory == 10) {
        return 0;
    }

    if (g_EquipDefs[equipId].itemCategory == 9 &&
        g_EquipDefs[equipId].attack == 1) {
        return 0;
    }

    if (equipId == 0x10) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            g_AccessoryDefs[g_Status.equipment[3 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (totalAttack <= strengthStat) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    switch (equipId) {
    case 0x7F:
        totalAttack += g_Status.timerHours;
        break;
    case 0x8F:
        totalAttack += SquareRoot0(g_Status.D_80097C40);
        break;
    case 4:
        if (g_EquipDefs[otherEquipId].itemCategory == 9) {
            totalAttack += 5;
        }
        break;
    case 0x80:
        totalAttack += g_Status.statsFamiliars[4].level;
        break;
    case 0x6F: {
        s32 j;
        s32 sVar3 = 0;
        for (j = 0; j < 2; j++) {
            s32 index = g_Status.equipment[6 + j] - 0x40;
            if (index < 0) {
                continue;
            }
            if (index < 7) {
                sVar3 += DAT_060850ec[index];
            }
        }
        totalAttack += sVar3;
    } break;
    }

    if (g_StatBuffTimers[1]) {
        totalAttack += 20;
    }
    if (totalAttack < 0) {
        totalAttack = 0;
    }
    if (totalAttack > 999) {
        totalAttack = 999;
    }
    return totalAttack;
}

inline void make_att(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        s32 equipId = g_Status.equipment[i];
        s32 otherEquipId = g_Status.equipment[1 - i];
        g_Status.attackHands[i] = CalcAttack(equipId, otherEquipId);
    }
}

void CalcDefense(void) {
    Accessory* acc;
    s32 thisHandItem;
    s32 i;
    s16 totalDefense;

    totalDefense = 0;
    g_Status.elementsWeakTo = 0;
    g_Status.elementsResist = 0;
    g_Status.elementsImmune = 0;
    g_Status.elementsAbsorb = 0;

    // Iterate over player's hands, hand 0 and hand 1.
    for (i = 0; i < 2; i++) {
        thisHandItem = g_Status.equipment[i];
        totalDefense += g_EquipDefs[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if (thisHandItem == 4 &&
            g_EquipDefs[g_Status.equipment[1 - i]].itemCategory == 9) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &g_AccessoryDefs[g_Status.equipment[i + 3]];
        totalDefense += acc->defBonus;
        g_Status.elementsWeakTo |= acc->weakToElements;
        g_Status.elementsResist |= acc->resistElements;
        g_Status.elementsImmune |= acc->immuneElements;
        g_Status.elementsAbsorb |= acc->absorbElements;
    }

    if (CheckEquipmentItemCount(13, 0) != 0) {
        g_Status.elementsImmune |= 0x200;
    }
    if (CheckEquipmentItemCount(15, 0) != 0) {
        g_Status.elementsImmune |= 0x8000;
    }
    if (g_Status.relics[0x19] & 2) {
        g_Status.elementsImmune |= 0x100;
    }
    if (g_StatBuffTimers[5]) {
        g_Status.elementsResist |= 0x8000;
    }
    if (g_StatBuffTimers[6]) {
        g_Status.elementsResist |= 0x2000;
    }
    if (g_StatBuffTimers[7]) {
        g_Status.elementsResist |= 0x4000;
    }
    if (g_StatBuffTimers[8]) {
        g_Status.elementsResist |= 0x100;
    }
    if (g_StatBuffTimers[9]) {
        g_Status.elementsResist |= 0x1000;
    }
    if (g_StatBuffTimers[10]) {
        g_Status.elementsImmune |= 0x200;
    }
    if (g_StatBuffTimers[11]) {
        g_Status.elementsResist |= 0x800;
    }

    totalDefense += SquareRoot0(g_Status.statsTotal[1]) - 2;

    if (CheckEquipmentItemCount(19, 2) != 0) {
        totalDefense += g_RoomCount / 60;
    }

    if (g_StatBuffTimers[0]) {
        totalDefense += 20;
    }
    if (totalDefense < 0) {
        totalDefense = 0;
    }
    if (totalDefense > 999) {
        totalDefense = 999;
    }
    g_Status.defenseEquip = totalDefense;
}

void make_all(void) {
    func_0606D880();
    make_att();
    CalcDefense();
}

extern s32 D_8013AEE4;

void CheckWeaponCombo(void) {
    s32 i;

    u32 handFlag = 0x80000000; // right hand

    s32 leftHand = g_Status.equipment[LEFT_HAND_SLOT];
    s32 rightHand = g_Status.equipment[RIGHT_HAND_SLOT];

    u32 combo =
        g_EquipDefs[leftHand].comboSub & g_EquipDefs[rightHand].comboMain;

    if (combo != 0) {
        handFlag = 0;
    }
    combo |= g_EquipDefs[leftHand].comboMain & g_EquipDefs[rightHand].comboSub;

    if (combo != 0) {
        for (i = 0xB1; i < 0xE4; i++) {
            if (combo & g_EquipDefs[i].comboSub) {
                D_8013AEE4 = handFlag + i;
                return;
            }
        }
    }
    D_8013AEE4 = 0;
}

// original name: servant_work_clear
void ServantWorkClear(void) {
    s32 i;
    Entity* entity;

    entity = &g_Entities[4];
    for (i = 4; i < STAGE_ENTITY_START; i++, entity++) {
        u16 entityID = entity->entityId;
        if (entityID >= 0xD0 && entityID < 0xE0) {
            DestroyEntity(entity);
        }
    }
}

void init_work_sub_out_p(void) {
    s32 i;
    Entity* entity;

    entity = &g_Entities[0];
    for (i = 0; i < STAGE_ENTITY_START; i++, entity++) {
        u16 entityID = entity->entityId;
        if (entityID >= 0xE0 && entityID < 0x100) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("asm/saturn/game/data", d606E0C8, d_0606E0C8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606E0D0, func_0606E0D0);

// _MODE_GAME
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606EE28, func_0606EE28);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606EEF8, func_0606EEF8);

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

extern s32 DAT_0605c10c;
extern s32 DAT_0608609c;

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

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F1C8, func_0606F1C8);

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
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
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
// sh2 compiler is more literal?
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
    if (g_StageId == STAGE_ST0) {
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

// FILE SPLIT HERE

bool func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if (g_unkGraphicsStruct.D_800973FC != 0 || D_8006BB00 != 0) {
            return false;
        }
        if (D_8003C708.flags & (0x40 | 0x20)) {
            return false;
        }
        D_801375C8 = 1;
        return true;
    }
    D_801375C8 = 8;
}

void func_800F2860(void) {
    switch (D_801375C8) {
    case 0:
        break;
    case 1:
        PlaySfx(0xF0000080);
        D_801375C8++;
        break;
    case 2:
        if (func_80131F68() == 0) {
            D_801375C8++;
        }
        break;
    case 3:
        PlaySfx(0xE0000120);
        D_801375C8++;
        break;
    case 4:
        if (func_80131F68() != 0) {
            D_801375C8++;
        }
        break;
    case 5:
        if (func_80131F68() == 0) {
            D_801375C8++;
        }
        break;
    case 6:
        PlaySfx(currentMusicId);
        D_801375C8 = 0;
        break;
    case 7:
        if (func_80131F68() == 0) {
            D_801375C8--;
        }
        break;
    case 8:
        PlaySfx(0xF0000080);
        D_801375C8--;
        break;
    }
}

// RunMainEngine
INCLUDE_ASM("asm/saturn/game/data", d6070A60, d_06070A60);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6071C3C, func_06071C3C);

// _INIT_ROOM
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60720F4, func_060720F4);

// _SET_DEFAULT_SCL_PRIORITY
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60726A8, func_060726A8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60727DC, func_060727DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607284C, func_0607284C);
INCLUDE_ASM("asm/saturn/game/data", d60728B4, d_060728B4);

// _INIT_GAME_OVER
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072BCC, func_06072BCC);

// _GAMEOVER_FADEIN
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072C04, func_06072C04);

// _SUB_DISP
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072C94, func_06072C94);

bool CheckIfAllButtonsAreAssigned(void) {
    s32 buf[9];
    s32 i;
    s32 bitMask_Assigned;
    s32* buttonConfig;

    for (i = 0; i < 9; i++) {
        buf[i] = 0;
    }

    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        buf[*buttonConfig++] = 1;
    }

    for (i = 0; i < 9; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[8] = i;
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 9; i++) {
        bitMask_Assigned |= 1 << *buttonConfig++;
    }
    if (bitMask_Assigned == 0xFF) {
        return true;
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073280, func_06073280);

// _INIT_SUB_GAMEN
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60732E4, func_060732E4);

// _PSX_cursor_up_down
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60733A4, func_060733A4);

// SAT: func_0607356C
bool func_800FB1EC(s32 arg0) {
    if (D_801375CC == EQUIP_HAND) {
        if (arg0 == 0) {
            return true;
        }
    } else if ((arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) ||
               (arg0 == 0x3A)) { // 3A instead of 39
        return true;
    }

    return false;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60735A4, func_060735A4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607360C, func_0607360C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607369C, func_0607369C);

// _PSX_id_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60736D4, func_060736D4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607371C, func_0607371C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073740, func_06073740);

// _goto_equip
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073770, func_06073770);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60737A0, func_060737A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073E58, func_06073E58);

// _PSX_sort_item
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073EEC, func_06073EEC);

// _PSX_equip_id_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073FEC, func_06073FEC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074048, func_06074048);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074068, func_06074068);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60740F8, func_060740F8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074278, func_06074278);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60743B8, func_060743B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074470, func_06074470);

// _EVENT_SCL_TRANS
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60744F8, func_060744F8);

// _SS_MOJI_SET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60745A0, func_060745A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074698, func_06074698);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074700, func_06074700);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074724, func_06074724);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074964, func_06074964);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60749F8, func_060749F8);

extern s32 DAT_06085c70;
s32* func_06074A98(void) { return &DAT_06085c70; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074AA8, func_06074AA8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074BF4, func_06074BF4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074C28, func_06074C28);

// _status_work_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074CC8, func_06074CC8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075838, func_06075838);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075D24, func_06075D24);

// _status_pause
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60766DC, func_060766DC);

struct Unk_060860D8 {
    u8 pad[0x23];
    s32 unk24;
};

extern struct Unk_060860D8 DAT_060860D8;
s32 func_06076718(void) { return DAT_060860D8.unk24 == 0x15; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607672C, func_0607672C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6076A04, func_06076A04);

// _set_XYWH
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077148, func_06077148);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607718C, func_0607718C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60771B0, func_060771B0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60771D4, func_060771D4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077260, func_06077260);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077354, func_06077354);

// _set_life_num
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077764, func_06077764);

// _status_disp_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077B20, func_06077B20);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077D88, func_06077D88);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078120, func_06078120);

extern s32 DAT_00292000;

s32* func_060784A8(void) { return &DAT_00292000; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60784B8, func_060784B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078550, func_06078550);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078604, func_06078604);

// _disp_num_string
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078684, func_06078684);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607872C, func_0607872C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078748, func_06078748);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60787C8, func_060787C8);

// _SubDispSpecial
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078920, func_06078920);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60789C4, func_060789C4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078D58, func_06078D58);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078E80, func_06078E80);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078F58, func_06078F58);

// _SubDispSortKind
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079008, func_06079008);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60790B4, func_060790B4);

// _SubDispFace
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079208, func_06079208);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60792B8, func_060792B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079424, func_06079424);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079580, func_06079580);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079670, func_06079670);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607973C, func_0607973C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60797FC, func_060797FC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079958, func_06079958);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079A2C, func_06079A2C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079AF0, func_06079AF0);

// original name: normal_move
inline void NormalMove(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        temp->unk14 += entity->velocityX;
        temp->unk18 += entity->velocityY;
        entity->posX.val = temp->unk14;
        entity->posY.val = temp->unk18;
    }
}

inline void MoveEntity(Entity* entity) {
    entity->posX.val += entity->velocityX;
    entity->posY.val += entity->velocityY;
}

inline void func_06079BB4(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        temp->unk14 = entity->posX.val;
        temp->unk18 = entity->posY.val;
    }
}

inline void func_06079BCC(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        entity->posX.val = temp->unk14;
        entity->posY.val = temp->unk18;
    }
}

inline void FallEntity(Entity* entity) {
#define TERMINAL_VELOCITY FIX(6)
#define GRAVITY FIX(0.25f)

    if (entity->velocityY < TERMINAL_VELOCITY) {
        entity->velocityY += GRAVITY;
    }
}

s32 UnkCollisionFunc3(Entity* entity, s16* sensors) {
    Collider col;
    Collider colBack;
    s16 x, y;
    s16 i;

    NormalMove(entity);
    FallEntity(entity);
    func_06079BCC(entity);

    if (entity->velocityY >= 0) {
        x = entity->posX.i.hi;
        y = entity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            CheckCollision(x * 0x10000, y * 0x10000, &col, 0);
            if ((col.effects & EFFECT_UNK_8000) && i == 1) {
                if (col.effects & EFFECT_SOLID) {
                    CheckCollision(x * 0x10000, (y - 8) * 0x10000, &colBack, 0);
                    if (colBack.effects & EFFECT_SOLID) {
                        continue;
                    }
                    entity->posY.i.hi += col.unk18 / 0x10000 + 4;
                    entity->velocityX = 0;
                    entity->velocityY = 0;
                    entity->flags &= ~FLAG_UNK_10000000;
                    func_06079BB4(entity);
                    return 1;
                }
            } else if ((col.effects & EFFECT_NOTHROUGH) && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    entity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                CheckCollision(x * 0x10000, (y - 8) * 0x10000, &colBack, 0);
                if (colBack.effects & EFFECT_SOLID) {
                    continue;
                }
                entity->posY.i.hi += col.unk18 / 0x10000;
                entity->velocityX = 0;
                entity->velocityY = 0;
                entity->flags &= ~FLAG_UNK_10000000;
                func_06079BB4(entity);
                return 1;
            }
        }
    }
    entity->flags |= FLAG_UNK_10000000;
    func_06079BB4(entity);
    return 0;
}

s32 UnkCollisionFunc2(Entity* entity, s16* posX) {
    Collider collider;
    s16 x, y;

    func_06079BCC(entity);
    entity->posX.val += entity->velocityX;
    entity->posY.i.hi += 3;
    x = entity->posX.i.hi + *posX++;
    y = entity->posY.i.hi + *posX++;
    CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        entity->posY.i.hi += collider.unk18 / 0x10000;
    } else {
        func_06079BB4(entity);
        return 0;
    }
    if (entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            x -= *posX++;
        } else {
            x += *posX++;
        }
        y += *posX++;
        y -= 7;
        CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                entity->posX.val -= entity->velocityX;
                entity->velocityX = 0;
                func_06079BB4(entity);
                return 0xFF;
            } else {
                func_06079BB4(entity);
                return 0x61;
            }
        }
        y += 0xF;
        CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                func_06079BB4(entity);
                return 0x61;
            } else {
                func_06079BB4(entity);
                return 1;
            }
        } else {
            entity->posX.val -= entity->velocityX;
            entity->velocityX = 0;
            func_06079BB4(entity);
            return 0x80;
        }
    } else {
        func_06079BB4(entity);
        return 1;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079F60, func_06079F60);

// _v_side_hosei
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A030, func_0607A030);

u8 CheckColliderOffsets(Entity* entity, s16* arg0, u8 facing) {
    Collider collider;
    s16 posX, posY;
    u8 ret;

    if (g_CurrentEntity->unk0 != NULL) {
        func_06079BCC(entity);
    }
    ret = 0;
    while (*arg0 != 0xFF) {
        ret <<= 1;
        if (facing) {
            posX = entity->posX.i.hi + *arg0++;
        } else {
            posX = entity->posX.i.hi - *arg0++;
        }
        posY = entity->posY.i.hi + *arg0++;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            ret |= 1;
        }
    }
    return ret;
}

bool UnkCollisionFunc5(Entity* entity, s16* pointXY) {
    Collider collider;

    FallEntity(entity);
    func_06079BCC(entity);
    MoveEntity(entity);

    if (entity->velocityY >= 0) {
        s16 posX = entity->posX.i.hi + pointXY[0];
        s16 posY = entity->posY.i.hi + pointXY[1];
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            entity->posY.i.hi += collider.unk18 / 0x10000;
            entity->velocityY = -entity->velocityY / 2;
            func_06079BB4(entity);
            if (entity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}

u8 UnkCollisionFunc4(Entity* entity, u8 arg1) {
    Collider collider;
    u8 bits_01;
    u8 bits_23;
    u8 bits_45;
    u8 bits_67;
    u16 collEff;
    s16 posX, posY;

    NormalMove(entity);
    func_06079BCC(entity);

    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    collEff = 0;
    bits_01 = arg1 & 3;
    switch (bits_01) {
    case 0:
        entity->posY.i.hi += 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posY.i.hi += collider.unk18 / 0x10000;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi - 4;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (entity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    entity->velocityX = -entity->velocityX;
                }
                entity->velocityY = -entity->velocityX;
                entity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posX.val -= entity->velocityX;
            if (entity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                entity->velocityX = -entity->velocityX;
            }
            entity->velocityY = entity->velocityX;
            entity->velocityX = 0;
        }
        break;
    case 1:
        entity->posY.i.hi -= 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posY.i.hi += collider.unk20 / 0x10000;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi + 4;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (entity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    entity->velocityX = -entity->velocityX;
                }
                entity->velocityY = entity->velocityX;
                entity->velocityX = 0;
            }
        } else {
            bits_67 = -0x80;
            entity->posX.val -= entity->velocityX;
            if (entity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                entity->velocityX = -entity->velocityX;
            }
            entity->velocityY = -entity->velocityX;
            entity->velocityX = 0;
        }
        break;
    case 2:
        entity->posX.i.hi += 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posX.i.hi += collider.unk14 / 0x10000;
            posX = entity->posX.i.hi - 4;
            posY = entity->posY.i.hi;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (entity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    entity->velocityY = -entity->velocityY;
                }
                entity->velocityX = -entity->velocityY;
                entity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posY.val -= entity->velocityY;
            if (entity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                entity->velocityY = -entity->velocityY;
            }
            entity->velocityX = entity->velocityY;
            entity->velocityY = 0;
        }
        break;
    case 3:
        entity->posX.i.hi -= 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posX.i.hi += collider.unk1C / 0x10000;
            posX = entity->posX.i.hi + 4;
            posY = entity->posY.i.hi;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (entity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    entity->velocityY = -entity->velocityY;
                }
                entity->velocityX = entity->velocityY;
                entity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posY.val -= entity->velocityY;
            if (entity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                entity->velocityY = -entity->velocityY;
            }
            entity->velocityX = -entity->velocityY;
            entity->velocityY = 0;
        }
        break;
    }

    func_06079BB4(entity);

    if (collEff & 0x8000) {
        bits_23 = 4;
    }
    if (collEff & 0x1000) {
        bits_23 = 8;
    }
    if (collEff & 0x2000) {
        bits_23 = 0xC;
    }
    if (collEff & 0x0800) {
        bits_45 = 0x20;
    }
    if (collEff & 0x4000) {
        bits_45 = 0x10;
    }
    bits_01 = bits_01 + bits_67 + bits_23 + bits_45;
    return bits_01;
}

void (*GetPlayerSensor)(Collider* col);
u8 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags) {
    Entity* player;
    s16 x, y;
    u16 checks;
    Collider col;
    s32 plStatus;

    plStatus = g_Player.status;
    player = &PLAYER;

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    if (x > 0x160 || x < -0x20 || y < -0x180 || y > 0x180) {
        return 0;
    }

    x = player->posX.i.hi - x;
    y = player->posY.i.hi - y;

    if (g_CurrentEntity->facingLeft) {
        x += g_CurrentEntity->hitboxOffX;
    } else {
        x -= g_CurrentEntity->hitboxOffX;
    }
    y -= g_CurrentEntity->hitboxOffY;

    (*GetPlayerSensor)(&col);
    w += col.unk14 >> 0x10;
    h += col.unk18 >> 0x10;

    if (x > 0) {
        checks = 1;
    } else {
        checks = 0;
    }
    if (y > 0) {
        checks |= 2;
    }
    x += w;
    y += h;
    w += w;
    h += h;

    if ((u16)x <= w && (u16)y <= h) {
        if (x != 0 && x != w) {
            if ((flags & 4) && checks ^ 2 && player->velocityY >= 0) {
                if (y < 8) {
                    player->posY.i.hi -= y;
                    g_unkGraphicsStruct.unk94 -= y;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_GROUND;
                    if (plStatus & 3) {
                        return 0;
                    }
                    return 4;
                }
            }
            if ((flags & 2) && (checks & 2) &&
                (player->velocityY <= 0 || (flags & 0x10))) {
                y = h - y;
                if (y < 0x10) {
                    player->posY.i.hi += y;
                    g_unkGraphicsStruct.unk94 += y;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_CEILING;
                    if (plStatus & 3) {
                        return 0;
                    }
                    return 2;
                }
            }
        }
        if (y != 0 && y != h) {
            if (flags & 1) {
                if (checks & 1) {
                    x = w - x;
                    if (flags & 8 && x > 2) {
                        x = 2;
                    }
                    player->posX.i.hi += x;
                    g_unkGraphicsStruct.unk90 += x;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_L_WALL;
                    return 1;
                } else {
                    if (flags & 8 && x > 2) {
                        x = 2;
                    }
                    player->posX.i.hi -= x;
                    g_unkGraphicsStruct.unk90 -= x;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_R_WALL;
                    return 1;
                }
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A88C, func_0607A88C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A994, func_0607A994);

// SAT func_0607A9F8
// Original name: _hkyori_search
// Absolute distance from the specified entity to the player in the X Axis
s32 GetDistanceToPlayerX(Entity* self) {
    s16 xDistance = self->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// SAT func_0607AA1C
// Absolute distance from the specified entity to the player in the Y Axis
s32 GetDistanceToPlayerY(Entity* self) {
    s16 yDistance = self->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA40, func_0607AA40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA74, func_0607AA74);

void func_0607AAA4(Entity* entity) {
    Entity* player = &PLAYER;
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= player->posX.val) {
        entity->facingLeft = 0;
    } else {
        entity->facingLeft = 1;
    }
}

void func_0607AACC(Entity* entity) {
    Entity* player = &PLAYER;
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= player->posX.val) {
        entity->facingLeft = 1;
    } else {
        entity->facingLeft = 0;
    }
}

// SAT func_0607AAF4
/*
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
s32 GetSideToPlayer(Entity* self) {
    Entity* player = &PLAYER;
    s16 side = 0;

    if (self->posX.val > player->posX.val) {
        side = 1;
    }

    if (self->posY.val > player->posY.val) {
        side |= 2;
    }
    return side;
}

// func_0607AB1C
// saturn unique?
s32 GetSideToPlayer2(Entity* self) {
    s16 side = 0;

    if (g_CurrentEntity->posX.val > PLAYER.posX.val) {
        side = 1;
    }
    if (g_CurrentEntity->posY.val > PLAYER.posY.val) {
        side |= 2;
    }

    return side;
}

// original name: bicyousei_dir_0
void BicyouseiDir0(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= PLAYER.posX.val) {
        temp->unk0 &= ~0x10;
        entity->facingLeft = 0;
    } else {
        temp->unk0 |= 0x10;
        entity->facingLeft = 1;
    }
}

void BicyouseiDir1(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= PLAYER.posX.val) {
        temp->unk0 |= 0x10;
        entity->facingLeft = 0;
    } else {
        temp->unk0 &= ~0x10;
        entity->facingLeft = 1;
    }
}

// original name: hanten_dir_0
bool HantenDir0(Entity* entity) {
    Unk0600B344* temp = entity->unk0;
    bool ret = false;
    Entity* player = &PLAYER;

    if (entity->facingLeft == 0) {
        if (temp->unk14 < player->posX.val) {
            ret = true;
        }
    } else {
        if (temp->unk14 > player->posX.val) {
            ret = true;
        }
    }
    return ret;
}

bool HantenDir1(Entity* entity) {
    Unk0600B344* temp = entity->unk0;
    bool ret = false;
    Entity* player = &PLAYER;

    if (entity->facingLeft == 0) {
        if (temp->unk14 > player->posX.val) {
            ret = true;
        }
    } else {
        if (temp->unk14 < player->posX.val) {
            ret = true;
        }
    }
    return ret;
}

extern u8 DAT_06099811;
u8 func_0607AC2C(void) { return DAT_06099811; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AC40, func_0607AC40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AE48, func_0607AE48);

Entity* FindFirstFreeEntity(s16 start, s16 end) {
    Entity* current = &g_Entities[start];

    while (start < end) {
        if (current->entityId == 0) {
            return current;
        }
        start++;
        current++;
    }
    return NULL;
}

extern s16 g_SineTable[];

inline s32 GetSineScaled(u8 arg0, s16 arg1) {
    s32 sine = g_SineTable[arg0];
    return sine * arg1;
}

s16 GetSine(u8 arg0) { return g_SineTable[arg0]; }

void SetEntityVelocityFromAngle(Entity* entity, u8 arg0, s16 arg1) {
    entity->velocityX = GetSineScaled(arg0, arg1);
    entity->velocityY = GetSineScaled(arg0 - 0x40, arg1);
}

inline u8 Ratan2Shifted(s16 x, s16 y) {
    u8 angle = ratan2(y, x) >> 4;
    return angle + 0x40;
}

u8 GetAngleBetweenEntitiesShifted(Entity* a, Entity* b) {
    s16 dx = b->posX.i.hi - a->posX.i.hi;
    s16 dy = b->posY.i.hi - a->posY.i.hi;
    return Ratan2Shifted(dx, dy);
}

// original name: search_point
u8 GetAnglePointToEntityShifted(Entity* entity, s16 x, s16 y) {
    s16 dx = x - entity->posX.i.hi;
    s16 dy = y - entity->posY.i.hi;

    return Ratan2Shifted(dx, dy);
}

u8 AdjustValueWithinThreshold(u8 threshold, u8 currentValue, u8 targetValue) {
    u8 absoluteDifference;
    s8 relativeDifference = targetValue - currentValue;

    if (relativeDifference < 0) {
        absoluteDifference = -relativeDifference;
    } else {
        absoluteDifference = relativeDifference;
    }

    if (absoluteDifference > threshold) {
        if (relativeDifference < 0) {
            absoluteDifference = currentValue - threshold;
        } else {
            absoluteDifference = currentValue + threshold;
        }

        return absoluteDifference;
    }

    return targetValue;
}

void UnkEntityFunc0(Entity* entity, u16 slope, s16 speed) {
    entity->velocityX = rcos(slope) * speed / 16;
    entity->velocityY = rsin(slope) * speed / 16;
}

u16 Ratan2(s16 x, s16 y) { return ratan2(y, x); }

u16 GetAngleBetweenEntities(Entity* a, Entity* b) {
    s32 dx = b->posX.i.hi - a->posX.i.hi;
    s32 dy = b->posY.i.hi - a->posY.i.hi;
    return ratan2(dy, dx);
}

u16 GetAnglePointToEntity(Entity* entity, s16 x, s16 y) {
    s16 dx = x - entity->posX.i.hi;
    s16 dy = y - entity->posY.i.hi;
    return ratan2(dy, dx);
}

u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2) {
    u16 temp_a2 = (s16)(arg2 - arg1);
    u16 ret;

    if (temp_a2 & 0x800) {
        ret = (0x800 - temp_a2) & 0x7FF;
    } else {
        ret = temp_a2;
    }

    if (ret > arg0) {
        if (temp_a2 & 0x800) {
            ret = arg1 - arg0;
        } else {
            ret = arg1 + arg0;
        }
        return ret;
    }
    return arg2;
}

// SAT: func_0607B184
Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->entityId == 0) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

// SAT: func_0607B1C8
void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u16 index = entity->entityRoomIndex - 1 >> 5;
        g_unkGraphicsStruct.D_80097428[index] |=
            1 << ((entity->entityRoomIndex - 1) & 0x1F);
    }
}

// SAT: func_0607B218
void SetStep(s32 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

// SAT: func_0607B240
void SetSubStep(s32 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

// original name: teki_init
void TekiInit(Entity* entity, u16 enemyId) {
    EnemyDef* enemy;

    g_CurrentEntity->enemyId = enemyId;

    enemy = &g_EnemyDefs[enemyId];
    entity->hitPoints = enemy->hitPoints;
    entity->attack = enemy->attack;
    entity->attackElement = enemy->attackElement;
    entity->hitboxState = enemy->hitboxState;
    entity->hitboxWidth = enemy->hitboxWidth * 5 / 4;
    entity->hitboxHeight = enemy->hitboxHeight;
    entity->flags = enemy->flags;
    entity->hitboxOffX = 0;
    entity->hitboxOffY = 0;
    entity->step_s = 0;
}

extern u32 g_randomNext;

// SAT: func_0607B2F4
s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = (*PfnEntityUpdates)[entityId - 1]->func;
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = (*PfnEntityUpdates)[entityId - 1]->func;
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B3D0, func_0607B3D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B448, func_0607B448);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B4B8, func_0607B4B8);

void func_0607B604(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    temp->unk14 = entity->posX.val;
    temp->unk18 = entity->posY.val;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B618, func_0607B618);

u32 AnimateEntity(u8 frames[], Entity* entity) {
    u8* currentFrame;
    u16 flag;

    flag = 0;
    currentFrame = frames + entity->pose * 2;
    if (!entity->poseTimer) {
        if (*currentFrame) {
            if (*currentFrame == 0xFF) {
                return 0;
            }

            entity->poseTimer = currentFrame[0];
            entity->animCurFrame = currentFrame[1];
            currentFrame += 2;
            entity->pose++;
            flag |= 0x80;
        } else {
            entity->pose = 0;
            currentFrame = frames;
            entity->poseTimer = currentFrame[0];
            entity->animCurFrame = currentFrame[1];
            entity->pose++;
            return 0;
        }
    }
    entity->poseTimer--;
    entity->animCurFrame = currentFrame[-1];
    flag |= 1;

    return flag;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B714, func_0607B714);

void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B7B4, func_0607B7B4);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BE38, func_0607BE38);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BED0, func_0607BED0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C054, func_0607C054);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0A0, func_0607C0A0);

// _MTH_GetRand
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0BC, func_0607C0BC);
