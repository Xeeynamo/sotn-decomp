// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

void PlaySfx(s32 sfxId);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B6F8, func_0606B6F8);

// _READ_SUB_OUT_MODE
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B760, func_0606B760);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BB4C, func_0606BB4C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BEE4, func_0606BEE4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C064, func_0606C064);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C088, func_0606C088);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C160, func_0606C160);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C3E4, func_0606C3E4);

void func_0606C504(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

extern s32 DAT_0605c108;
extern RoomTeleport g_RoomTeleports[];
extern u16 D_8003C730;
extern s32 D_80097C98;
extern s32 DAT_0606459c;
extern RoomLoadDefHolder D_801375BC;

// original name: PSX_TO_STAGE_NO_GET
void func_0606D554(s32 arg0) {
    RoomTeleport* ptr;

    ptr = &g_RoomTeleports[DAT_0605c108];

    if (D_8003C730 == 0) {
        if (D_80097C98 == 4) {
            g_CurrentRoom.stageID = 0x2B;
        } else if (D_80097C98 == 5) {
            g_CurrentRoom.stageID = 11;
        } else if (D_80097C98 == 6) {
            g_CurrentRoom.stageID = 0x40;
        } else if (arg0 != 0x0) {
            g_CurrentRoom.stageID = ptr->stageId;
            if ((g_CurrentRoom.stageID & 0x10) != 0x10 &&
                (g_CurrentRoom.unk2 & 0x20) == 0x20) {
                g_CurrentRoom.stageID ^= 0x20;
            }
        }
        D_801375BC.def = DAT_0606459c + ptr->roomId + 4;
        g_CurrentRoom.unk4 = D_801375BC.def->tileLayoutId;
    }
}

void func_0606D5FC(void) {
    RoomTeleport* ptr;

    if ((D_8003C708.flags & FLAG_UNK_40) == 0) {
        return;
    }
    if (D_8003C708.unk2 != 0 &&
        (PLAYER.posX.i.hi < 8 || PLAYER.posX.i.hi > 0x318)) {
        return;
    }
    switch (D_8003C708.unk2) {
    case 0:
        ptr = &g_RoomTeleports[DAT_0605c108];
        D_8003C708.unk4 = ptr->stageId;
        if (g_CurrentRoom.stageID & 0x20) {
            D_8003C708.unk4 ^= 0x20;
        }
        D_8003C708.zPriority = ptr->reloadStageId;
        if (g_CurrentRoom.stageID & 0x20) {
            D_8003C708.zPriority ^= 0x20;
        }
        if (D_8003C708.flags == FLAG_UNK_40) {
            g_Player.demo_timer = 0x18;
            g_Player.padSim = 0x4000;
        } else {
            g_Player.demo_timer = 0x18;
            g_Player.padSim = 0x8000;
        }
        D_8003C708.unk2++;
        break;
    case 1:
        D_8003C708.unk2++;
        break;
    case 2:
    case 3:
        break;
    }
}

void func_0606D6DC(void) {
    if (g_CurrentRoom.stageID == 6 && g_CurrentRoom.unk8 == 0) {
        switch (g_CurrentRoom.unk4) {
        case 2:
        case 3:
        case 9:
        case 10:
            g_CurrentRoom.unkC--;
            break;
        case 8:
            if (g_CurrentRoom.unkA == 0 && g_CurrentRoom.unk6 == 1) {
                g_CurrentRoom.unkC--;
            }
            break;
        }
    } else if (g_CurrentRoom.stageID == 0x2B && g_CurrentRoom.unk8 != 0) {
        switch (g_CurrentRoom.unk4) {
        case 1:
            if (g_CurrentRoom.unk6 == 0 || g_CurrentRoom.unk6 == 2 ||
                g_CurrentRoom.unk6 == 3 || g_CurrentRoom.unk6 == 4) {
                g_CurrentRoom.unkC--;
            }
            break;
        }
    }
}

void func_0606D798(void) {
    if (g_CurrentRoom.stageID == 6 && g_CurrentRoom.unk8 == 0) {
        if (g_CurrentRoom.unk4 != 8) {
            if (g_CurrentRoom.unk4 != 9) {
                return;
            }
            g_CurrentRoom.unkC++;
        } else {
            if (g_CurrentRoom.unk6 != 2) {
                return;
            }
            g_CurrentRoom.unkC++;
        }
    } else if (g_CurrentRoom.stageID == 0x26 && g_CurrentRoom.unk8 == 0) {
        if (g_CurrentRoom.unk4 != 2) {
            if (g_CurrentRoom.unk4 != 3) {
                return;
            }
        }
        g_CurrentRoom.unkC++;
    }
}

s32 func_0606D804(u16 arg0) {
    s32 ret;

    ret = DAT_0606459c;

    switch (arg0) {
    case 6:
        if (g_CurrentRoom.unk8 != 0) {
            ret += 0x6C;
        }
        break;
    case 9:
        if (g_CurrentRoom.unk8 == 1) {
            ret += 0x42;
        } else if (g_CurrentRoom.unk8 == 2) {
            ret += 0x114;
        }
        break;
    case 3:
    case 11:
        if (g_CurrentRoom.unk8 != 0) {
            ret += 0x66;
        }
        break;
    }
    return ret;
}

static bool IsAlucart(void) {
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

extern u8 g_JewelSwordAttackBonus[];

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
                sVar3 += g_JewelSwordAttackBonus[index];
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

void make_att(void) {
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
