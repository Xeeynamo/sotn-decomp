// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include <saturn_sprite.h>

void UpdateCapePalette(void);

static void func_800FF708(s32 equipType, s32 arg1) {
    s32 rnd;

    while ((rnd = MTH_GetRand() % 0x5C) == 0x19 ||
           g_AccessoryDefs[rnd].equipType != equipType) {
        // try again
    }
    g_Status.equipment[1 + arg1] = rnd;
}

// original name: status_work_init
void InitStatsAndGear(s32 isDeathTakingItems) {
    s32 prologueBonusState;
    s32 dracDefeatTime;
    u8* fileName;
    s32 rnd;
    s32 i;

    if (D_8003C730 != 0) {
        make_all();
        return;
    }
    if (isDeathTakingItems == 1) {
        if (g_Status.equipment[0] == 0x7D) {
            g_Status.equipment[0] = 0;
        } else if (g_Status.equipment[1] == 0x7D) {
            g_Status.equipment[1] = 0;
        } else if (g_Status.equipHandCount[0x7D]) {
            g_Status.equipHandCount[0x7D]--;
        }
        if (g_Status.equipment[0] == 0x10) {
            g_Status.equipment[0] = 0;
        } else if (g_Status.equipment[1] == 0x10) {
            g_Status.equipment[1] = 0;
        } else if (g_Status.equipHandCount[0x10]) {
            g_Status.equipHandCount[0x10]--;
        }
        if (g_Status.equipment[3] == 0x2D) {
            g_Status.equipment[3] = 0x1A;
        } else if (g_Status.equipBodyCount[0x2D]) {
            g_Status.equipBodyCount[0x2D]--;
        }
        if (g_Status.equipment[4] == 0xF) {
            g_Status.equipment[4] = 0;
        } else if (g_Status.equipBodyCount[0xF]) {
            g_Status.equipBodyCount[0xF]--;
        }
        if (g_Status.equipment[5] == 0x39) {
            g_Status.equipment[5] = 0x30;
            UpdateCapePalette();
        } else if (g_Status.equipBodyCount[0x39]) {
            g_Status.equipBodyCount[0x39]--;
        }
        if (g_Status.equipment[6] == 0x50) {
            g_Status.equipment[6] = 0x3A;
        } else if (g_Status.equipment[7] == 0x50) {
            g_Status.equipment[7] = 0x3A;
        } else if (g_Status.equipBodyCount[0x50]) {
            g_Status.equipBodyCount[0x50]--;
        }
        make_all();
        return;
    }
    for (i = 0; i < 0x800; i++) {
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
    for (i = 0; i < 7; i++) {
        g_Status.statsFamiliars[i].level = 1;
        g_Status.statsFamiliars[i].exp = 0;
        g_Status.statsFamiliars[i].unk8 = 0;
    }
    for (i = 0; i < 0xB0; i++) {
        g_Status.equipHandCount[i] = 0;
        g_Status.equipHandOrder[i] = i;
    }
    g_Status.equipment[2] = 0;
    for (i = 0; i < 0x5C; i++) {
        g_Status.equipBodyCount[i] = 0;
        g_Status.equipBodyOrder[i] = i;
    }
    g_Status.equipHandCount[0] = 1;
    g_Status.equipHandCount[1] = 1;
    g_Status.equipBodyCount[0x1A] = 1;
    g_Status.equipBodyCount[0] = 1;
    g_Status.equipBodyCount[0x30] = 1;
    g_Status.equipBodyCount[0x3A] = 1;
    for (i = 0; i < 8; i++) {
        g_Status.spells[i] = 0;
    }
    g_Status.spellsLearnt = 0;
    if ((g_CurrentRoom.stageID == STAGE_ST0) || (g_PlayableCharacter != 0)) {
        for (i = 0; i < 0x20; i++) {
            g_Status.relics[i] = 1;
        }
        g_Status.relics[0xA] |= 2;
        g_Status.relics[0xB] |= 2;
        g_Status.relics[0xF] |= 2;
        g_Status.relics[0x10] |= 2;
        for (i = 0; i < 0x20; i++) {
            g_Settings.timeAttackRecords[i] = 0;
        }
        g_Settings.D_8003CB00 = 0;
        g_Settings.D_8003CB04 = 0;
        g_Status.subWeapon = 0;
        g_Status.statsBase[0] = 10;
        g_Status.statsBase[1] = 10;
        g_Status.statsBase[2] = 10;
        g_Status.statsBase[3] = 10;
        g_Status.gold = 0;
        g_Status.equipment[0] = 0;
        g_Status.equipment[1] = 0;
        g_Status.equipment[3] = 0x1A;
        g_Status.equipment[4] = 0;
        g_Status.equipment[5] = 0x30;
        g_Status.equipment[6] = 0x3A;
        g_Status.equipment[7] = 0x3A;
        if ((g_CurrentRoom.stageID != STAGE_ST0) &&
            (g_CurrentRoom.stageID != 0x41)) {
            g_Status.subWeapon = MTH_GetRand() % 9 + 1;
        }
        if (g_CurrentRoom.stageID == STAGE_ST0) {
            g_Status.hpMax = g_Status.hp = 50;
            g_Status.hearts = 30;
            g_Status.heartsMax = 99;
            g_Status.mp = g_Status.mpMax = 20;
        } else if (g_PlayableCharacter == 1) {
            g_Status.hpMax = g_Status.hp = 100;
            g_Status.hearts = 30;
            g_Status.heartsMax = 99;
            g_Status.mp = g_Status.mpMax = 20;
        } else {
            g_Status.hpMax = g_Status.hp = 200;
            g_Status.hearts = 99;
            g_Status.heartsMax = 999;
            g_Status.equipment[3] = 0x2D;
            g_Status.mp = g_Status.mpMax = 200;
        }
        if (g_CurrentRoom.stageID == 0x41) {
            TimeAttackController(27, 1);
            TimeAttackController(9, 1);
            TimeAttackController(4, 1);
            TimeAttackController(14, 1);
            TimeAttackController(12, 1);
        }
        g_Status.timerHours = 0;
        g_Status.timerMinutes = 0;
        g_Status.timerSeconds = 0;
        g_Status.timerFrames = 0;
        make_all();
        return;
    }
    if (g_CurrentRoom.stageID == 0x41) {
        g_Status.statsBase[0] = 6;
        g_Status.statsBase[1] = 6;
        g_Status.statsBase[2] = 6;
        g_Status.statsBase[3] = 6;
        g_Status.gold = 0;
        for (i = 0; i < 0x20; i++) {
            g_Status.relics[i] = 0;
        }
        if (D_801397FC != 0) {
            AddToInventory(0xA1, 0);
            prologueBonusState = 3;
        } else if (g_Status.hp == g_Status.hpMax) {
            g_Status.statsBase[0]++;
            g_Status.statsBase[1]++;
            g_Status.statsBase[2]++;
            g_Status.statsBase[3]++;
            prologueBonusState = 0;
        } else if (g_Status.hp >= g_Status.hpMax / 2) {
            g_Status.statsBase[0]++;
            prologueBonusState = 1;
        } else {
            g_Status.statsBase[1]++;
            prologueBonusState = 2;
        }
        if ((g_Status.hearts == 0) && (prologueBonusState < 3)) {
            AddToInventory(0x90, 0);
        }
        g_Status.hpMax = 70;
        if (prologueBonusState == 0) {
            g_Status.hpMax += 5;
        }
        g_Status.hearts = 10;
        g_Status.heartsMax = 50;
        g_Status.mpMax = 20;
        if (D_80139008 > 40) {
            AddToInventory(0x49, 0);
            g_Status.statsBase[2]++;
        } else {
            g_Status.statsBase[0]++;
        }
        if (g_Status.subWeapon == 4) {
            if (prologueBonusState < 3) {
                g_Status.heartsMax += 5;
                g_Status.mpMax += 5;
            }
        } else if (g_Status.subWeapon == 3) {
            if (prologueBonusState < 2) {
                g_Status.heartsMax += 5;
                g_Status.statsBase[2]++;
            }
        } else {
            switch (prologueBonusState) {
            case 0:
                g_Status.statsBase[3] += 5;
                g_Status.statsBase[2]++;
                g_Status.statsBase[1]++;
            case 1:
                g_Status.hpMax += 5;
            case 2:
                g_Status.statsBase[0]++;
            }
        }

        dracDefeatTime = TimeAttackController(0, 0);
        if (dracDefeatTime <= 100) {
            g_Status.hpMax += 5;
            g_Status.mpMax += 5;
            g_Status.heartsMax += 5;
            g_Status.statsBase[0] += 5;
            g_Status.statsBase[1] += 5;
            g_Status.statsBase[2] += 5;
            g_Status.statsBase[3] += 5;
        } else if (dracDefeatTime <= 200) {
            g_Status.statsBase[3] += 2;
        } else if (dracDefeatTime <= 300) {
            g_Status.statsBase[3]++;
        } else if (dracDefeatTime >= 1000) {
            g_Status.statsBase[1]++;
        }

        g_Status.hp = g_Status.hpMax;
        g_Status.mp = g_Status.mpMax;
        g_Status.subWeapon = 0;
        g_Status.equipment[0] = 0x7D;
        g_Status.equipment[1] = 0x10;
        g_Status.equipment[3] = 0x2D;
        g_Status.equipment[4] = 0xF;
        g_Status.equipment[5] = 0x39;
        g_Status.equipment[6] = 0x50;
        g_Status.equipment[7] = 0x3A;
        fileName = g_LuckCode;
        for (i = 0; i < 8; i++) {
            if (g_Status.saveName[i] != *fileName++) {
                break;
            }
        }
        if (i == 8) {
            g_Status.statsBase[0] = 1;
            g_Status.statsBase[1] = 0;
            g_Status.statsBase[2] = 0;
            g_Status.statsBase[3] = 99;
            g_Status.hpMax = 25;
            g_Status.hearts = 5;
            g_Status.heartsMax = 5;
            g_Status.mpMax = 1;
            g_Status.hp = 25;
            g_Status.mp = 1;
            g_Status.equipment[7] = 0x47;
        }
        if (g_GameClearFlag) {
            fileName = g_AxeArmorCode;
            for (i = 0; i < 8; i++) {
                if (g_Status.saveName[i] != *fileName++) {
                    break;
                }
            }
            if (i == 8) {
                AddToInventory(0x19, 2);
            } else {
                fileName = g_GTIClubCode;
                for (i = 0; i < 8; i++) {
                    if (g_Status.saveName[i] != *fileName++) {
                        break;
                    }
                }
                if (i == 8) {
                    g_Status.gold = 250000;
                }
            }
        }
    } else {
        for (i = 0; i < 0x20; i++) {
            g_Settings.timeAttackRecords[i] = 0;
        }
        g_Status.statsBase[0] = 6;
        g_Status.statsBase[1] = 6;
        g_Status.statsBase[2] = 6;
        g_Status.statsBase[3] = 6;
        g_Status.hp = g_Status.hpMax = 70;
        g_Status.hearts = 10;
        g_Status.heartsMax = 50;
        g_Status.mpMax = 20;
        g_Status.mp = g_Status.mpMax;
        g_Status.hearts = 1234;
        g_Status.heartsMax = 2000;
        g_Status.gold = 500000;
        g_Status.exp = 11000;
        if (g_CurrentRoom.stageID & STAGE_INVERTEDCASTLE_FLAG) {
            g_Status.exp = 110000;
        }
        for (i = 0; i < 0x20; i++) {
            g_Status.relics[i] = 3;
            if (g_RelicDefs[i].unk0C != 0) {
                g_Status.relics[i] = 1;
            }
        }
        for (i = 0; i < 0xB0; i++) {
            g_Status.equipHandCount[i] = 50;
        }
        for (i = 0; i < 0x5C; i++) {
            g_Status.equipBodyCount[i] = 1;
        }
        g_Status.timerHours = 0;
        g_Status.timerMinutes = 0;
        g_Status.timerSeconds = 0;
        g_Status.timerFrames = 0;
        g_Status.subWeapon = 6;
        if (MTH_GetRand() & 3) {
            g_Status.subWeapon = MTH_GetRand() % 9 + 1;
        }

        while ((rnd = MTH_GetRand() % 0xB0) == 0xDF ||
               g_EquipDefs[rnd].itemCategory > 4) {
            // try again
        }
        g_Status.equipment[0] = rnd;

        while ((rnd = MTH_GetRand() % 0xB0) == 0xDF ||
               g_EquipDefs[rnd].itemCategory == 5) {
            // try again
        }
        g_Status.equipment[1] = rnd;

        func_800FF708(0, 2);
        func_800FF708(1, 3);
        func_800FF708(2, 4);
        func_800FF708(3, 5);
        func_800FF708(3, 6);
    }
    make_all();
    return;
}

static u16 LookupTblNoToVram(u16 arg0) {
    if (arg0 & 0x4000) {
        return LocalLookupTblNoToVram(arg0 & 0xFFF);
    } else {
        return SPR_2LookupTblNoToVram(arg0 & 0xFFF);
    }
}

static void SetXY(Primitive* prim, s32 x, s32 y) {
    prim->x0 = x;
    prim->y0 = y;
}

typedef struct {
    u16 entry[4];
} SprGourTbl;

extern SprGourTbl* SpGourTbl;
extern u32 D_8003C744;
extern s16 g_StatusHudPrimitiveLayout[];
extern u16 DAT_0605AED8[][2];
extern s16 g_StatusHudSpriteOffsets[][2];

void func_06075838(void) {
    s32 i;
    Primitive* prim;
    s16* temp2;

    D_801397FC = 0;
    D_80139008 = 0;
    g_PlayerHud.unk28 = 0;
    D_8003C744 = 0;
    g_PlayerHud.unk0C = 0x190;
    g_PlayerHud.unk10 = 0x190;
    g_PlayerHud.unk14 = 0x40;
    g_PlayerHud.unk18 = 0;
    g_PlayerHud.unk20 = 0x64;
    g_PlayerHud.unk1C = 0x64;
    g_PlayerHud.unk24 = 0;
    g_PlayerHud.primIndex1 = AllocPrimitives(0, 9);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    temp2 = g_StatusHudSpriteOffsets;
    while (prim != NULL) {
        u16* ptr;
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + *temp2++];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        prim->unk6 =
            LookupTblNoToVram(DAT_06086388->flags + *temp2++) & 0x8FFF | 0x4000;
        prim = prim->next;
    }
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    temp2 = g_StatusHudPrimitiveLayout;
    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->priority = 0x1BF;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    prim->type = 0x1002;
    prim->unk4 = 0x1488;
    prim->x0 = prim->x1 = g_PlayerHud.unk14 + temp2[0];
    prim->y2 = prim->y1 = temp2[1];
    temp2 += 2;
    prim->x2 = prim->x3 = prim->x1 + 0x27;
    prim->y0 = prim->y3 = prim->y1 + 0x5F;
    prim->priority = 0x1BF;
    if (g_CurrentRoom.stageID == STAGE_ST0) {
        prim->drawMode = DRAW_ABSPOS;
    } else {
        prim->drawMode = DRAW_HIDE | DRAW_ABSPOS;
    }
    prim = prim->next;

    prim->type = 0x1001;
    prim->unk4 = 0x1480;
    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->y2 = prim->y0 - 0x20;
    prim->x2 = prim->x0 + 0x8;
    prim->priority = 0x1C0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    prim->type = 0x1001;
    prim->unk4 = 0x1480;
    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->y2 = prim->y0 - 0x20;
    prim->x2 = prim->x0 + 0x8;
    prim->priority = 0x1C0;
    if (g_CurrentRoom.stageID == STAGE_ST0) {
        prim->drawMode = DRAW_ABSPOS;
    } else {
        prim->drawMode = DRAW_HIDE | DRAW_ABSPOS;
    }
    prim->x3 = 0;
    prim->y3 = 0x6;
    prim = prim->next;

    prim->type = 0x1001;
    prim->unk4 = 0x1480;
    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->y2 = prim->y0 - 0x20;
    prim->x2 = prim->x0 + 0x8;
    prim->priority = 0x1C0;
    if (g_CurrentRoom.stageID == STAGE_ST0) {
        prim->drawMode = DRAW_ABSPOS;
    } else {
        prim->drawMode = DRAW_HIDE | DRAW_ABSPOS;
    }
    prim = prim->next;

    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->priority = 0x1C0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->priority = 0x1C0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->priority = 0x1C0;
    prim->drawMode = DRAW_ABSPOS;
    prim = prim->next;

    SetXY(prim, temp2[0], temp2[1]);
    temp2 += 2;
    prim->priority = 0x1BF;
    prim->drawMode = DRAW_ABSPOS;
    for (prim = &g_PrimBuf[g_PlayerHud.primIndex1]; prim != NULL;
         prim = prim->next) {
        prim->unk4 &= 0xFFC7;
    }
    g_PlayerHud.primIndex2 = AllocPrimitives(2, 20);
    prim = &g_PrimBuf[g_PlayerHud.primIndex2];
    for (i = 0; prim != NULL; i++) {
        SprGourTbl* temp;
        u32 texOffset;
        u16 idx;
        u16* ptr2;
        s16* x2p;
        s16* x3p;
        s16* y0p;
        s16* y3p;

        texOffset = i * 0xC0;
        ptr2 = DAT_0605AED8[DAT_06086388->allocationIndex];
        prim->unk8 = ptr2[0];
        prim->unkA = ptr2[1];
        prim->unk8 += (texOffset >> 4) & 0xFFFC;
        prim->unkA = 0xC02;
        prim->unk6 =
            LookupTblNoToVram(DAT_06086388->flags + 2) & 0x8FFF | 0x4000;
        prim->unk4 &= 0xFFC7;

        x2p = &prim->x2;
        x3p = &prim->x3;
        prim->x0 = prim->x1 = (i * 2) + 0x110;
        *x2p = *x3p = prim->x0 + 1;

        y0p = &prim->y0;
        y3p = &prim->y3;
        prim->y1 = prim->y2 = 0x16;
        *y0p = *y3p = 0x75;

        prim->priority = 0x1BE;
        prim->drawMode = DRAW_HIDE;
        idx = prim->unk1C;
        temp = &SpGourTbl[idx];
        temp->entry[0] = (MTH_GetRand() & 0x3F) + 1;
        temp->entry[1] = 0;
        prim = prim->next;
    }
}

extern SaturnSpriteResource** DAT_060645EC;
extern u8 DAT_06085CE4[];

void func_06075D24(void) {
    s32 uVar6;
    s32 uVar8;
    u16 sVar11;
    s32 iVar12;
    Primitive* prim;
    Primitive* altPrim;
    u16* ptr;
    u8 local_38[10] = {0x0,  0x33, 0x37, 0x34, 0x38,
                       0x35, 0x36, 0x24, 0x3A, 0x39};
    u8 local_2c[10] = {0, 7, 7, 6, 6, 7, 7, 8, 7, 7};

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
    } else {
        if ((D_8003C744 == 1) && (g_PlayerHud.unk28 == 0)) {
            g_PlayerHud.unk10 = g_Entities[0x50].hitPoints;
            g_PlayerHud.unk0C = g_PlayerHud.unk10;
            g_PlayerHud.unk1C = (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10;
            g_PlayerHud.unk20 = 100;
            g_PlayerHud.unk28 = 1;
            D_80139008 = g_Status.hearts;
        }
        if ((D_8003C744 == 2) && (g_PlayerHud.unk28 == 1)) {
            g_PlayerHud.unk10 = g_Entities[0x55].hitPoints;
            g_PlayerHud.unk0C = g_PlayerHud.unk10;
            g_PlayerHud.unk28 = 2;
        }
        if (g_PlayerHud.unk28 != 100) {
            if (D_8003C744 == 1) {
                g_PlayerHud.unk0C = g_Entities[0x50].hitPoints;
            }
            if (D_8003C744 == 2 || D_8003C744 == 3) {
                g_PlayerHud.unk0C = g_Entities[0x55].hitPoints;
            }
            if (g_PlayerHud.unk0C < 0) {
                g_PlayerHud.unk0C = 0;
            }
        }
        if (g_PlayerHud.displayHP < g_Status.hp) {
            g_PlayerHud.displayHP++;
            D_801397FC = 1;
        }
        if (g_PlayerHud.displayHP > g_Status.hp) {
            g_PlayerHud.displayHP--;
        }
        if (D_8003C744 == 1) {
            if (g_PlayerHud.unk1C <
                (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) {
                g_PlayerHud.unk1C++;
            }
            if (g_PlayerHud.unk1C >
                (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) {
                g_PlayerHud.unk1C--;
            }
        }
        if (D_8003C744 == 2 || D_8003C744 == 3) {
            if (g_PlayerHud.unk1C != 0) {
                g_PlayerHud.unk1C--;
            }
            if (g_PlayerHud.unk20 <
                (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) {
                g_PlayerHud.unk20++;
            }
            if (g_PlayerHud.unk20 >
                (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10) {
                g_PlayerHud.unk20--;
            }
        }
        if ((D_8003C744 != 0) && (g_PlayerHud.unk14 != 0)) {
            g_PlayerHud.unk14--;
        }
        prim = &g_PrimBuf[g_PlayerHud.primIndex1];
        prim = prim->next;
        prim->x0 = prim->x1 = g_StatusHudPrimitiveLayout[2] + g_PlayerHud.unk14;
        prim->x2 = prim->x3 = prim->x1 + 0x27;
        if ((D_8003C744 == 3) && (g_PlayerHud.unk20 == 0) &&
            (g_PlayerHud.unk24 == 0 || (g_PlayerHud.unk24 > 0x32))) {
            prim->drawMode = DRAW_HIDE;
            altPrim = &g_PrimBuf[g_PlayerHud.primIndex2];
            while (altPrim != NULL) {
                u16 idx = altPrim->unk1C;
                SprGourTbl* temp = &SpGourTbl[idx];
                if (temp->entry[1] == 0) {
                    altPrim->drawMode = DRAW_ABSPOS;
                    if (temp->entry[0] != 0) {
                        temp->entry[0] -= 1;
                    } else {
                        uVar8 = rand() & 1;
                        altPrim->y1 += uVar8;
                        altPrim->y2 += uVar8;
                        uVar8 = (rand() & 3) + 1;
                        altPrim->y0 += uVar8;
                        altPrim->y3 += uVar8;
                        altPrim->drawMode = DRAW_ABSPOS;
                        if (altPrim->y0 >= 0x100) {
                            altPrim->drawMode = DRAW_ABSPOS;
                            if (altPrim->y0 >= 0x180) {
                                altPrim->drawMode = DRAW_ABSPOS;
                            }
                        }
                        if (altPrim->y0 >= 0x200) {
                            altPrim->drawMode = DRAW_HIDE;
                            temp->entry[1] = 1;
                        }
                    }
                }
                altPrim = altPrim->next;
            }
        }
        prim = prim->next;
        if (g_PlayerHud.displayHP != 0) {
            uVar6 = (g_PlayerHud.displayHP * 90) / g_Status.hpMax;
            prim->y2 = prim->y0 - uVar6;
            prim->drawMode &= ~DRAW_HIDE;
        } else {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = prim->next;

        uVar6 = (g_PlayerHud.unk1C * 90) / 100;
        if (uVar6 < 0) {
            uVar6 = 0;
        }

        if (uVar6 != 0) {
            SetXY(prim, g_StatusHudPrimitiveLayout[6] + g_PlayerHud.unk14,
                  prim->y0);
            prim->y2 = prim->y0 - uVar6;
            prim->x2 = prim->x0 + 8;
            prim->drawMode &= ~DRAW_HIDE;
        } else {
            prim->drawMode |= DRAW_HIDE;
        }
        if (g_CurrentRoom.stageID == 0x1F) {
            if (prim->y3-- == 0) {
                prim->x3++;
                if (prim->x3 == 9) {
                    prim->x3 = 0;
                }
                if (D_8003C744 == 2) {
                    prim->y3 = 1;
                } else {
                    prim->y3 = 4;
                }
                prim->unk6 =
                    LookupTblNoToVram(DAT_060645EC[18]->flags + prim->x3) &
                        0x8FFF |
                    0x4000;
            }
        }

        sVar11 = prim->unk6;
        prim = prim->next;
        uVar6 = (g_PlayerHud.unk20 * 90) / 100;

        if (uVar6 > 90) {
            uVar6 = 90;
        }
        if (uVar6 != 0) {
            SetXY(prim, g_StatusHudPrimitiveLayout[8] + g_PlayerHud.unk14,
                  prim->y0);
            prim->y2 = prim->y0 - uVar6;
            prim->x2 = prim->x0 + 8;
            prim->drawMode &= ~DRAW_HIDE;
        } else {
            prim->drawMode |= DRAW_HIDE;
        }
        prim->unk6 = sVar11;
        prim = prim->next;
        ptr =
            DAT_0605aec0[DAT_06086388->allocationIndex +
                         g_StatusHudSpriteOffsets[5][0] + g_Status.hearts / 10];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];

        if (g_Player.status & PLAYER_STATUS_UNK200000) {
            if (g_Timer & 2) {
                iVar12 = 2;
            } else {
                iVar12 = 0;
            }
        } else {
            iVar12 = 0;
        }
        prim->unk6 =
            LookupTblNoToVram(iVar12 + DAT_06086388->flags) & 0x8FFF | 0x4000;
        altPrim = prim;
        prim = prim->next;
        ptr =
            DAT_0605aec0[DAT_06086388->allocationIndex +
                         g_StatusHudSpriteOffsets[5][0] + g_Status.hearts % 10];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        prim->unk6 = altPrim->unk6;
        prim->drawMode = altPrim->drawMode;
        prim = prim->next;
        if (g_Status.subWeapon == 0) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            s32 sub = g_Status.subWeapon;
            ptr =
                DAT_0605aec0[g_SaturnSharedSpriteBank0Resource.allocationIndex +
                             local_38[sub]];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            prim->unk6 =
                LookupTblNoToVram(DAT_06086388->flags + local_2c[sub]) &
                    0x8FFF |
                0x4000;
            SetXY(prim, DAT_06085CE4[sub * 2], DAT_06085CE4[sub * 2 + 1]);
            prim->drawMode &= ~DRAW_HIDE;
        }
        prim = prim->next;
        if (g_PlayerHud.unk24 == 0) {
            return;
        }
        if (g_PlayerHud.unk24 < 0x6) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 1];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x19);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0xC) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 2];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x1D);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0x11) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 3];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x19);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0x15) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 4];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x15);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 == 0x15) {
        } else if (g_PlayerHud.unk24 > 0x32 && g_PlayerHud.unk24 < 0x39) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 3];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x19);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0x3D) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 2];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x1D);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0x42) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 1];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x19);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 < 0x47) {
            ptr = DAT_0605aec0[DAT_06086388->allocationIndex];
            prim->unk8 = ptr[0];
            prim->unkA = ptr[1];
            SetXY(prim, 0x2D, 0x15);
            g_PlayerHud.unk24++;
        } else if (g_PlayerHud.unk24 == 0x47) {
            g_PlayerHud.unk24 = 0;
        }
    }
}

// original name: status_pause
bool StatusPause(s32 arg0) {
    if (arg0 == 0) {
        if (g_PlayerHud.unk24 != 0) {
            return 0;
        }
        g_PlayerHud.unk24 = 1;
    } else if (arg0 == 1) {
        if (g_PlayerHud.unk24 != 0x15) {
            return 0;
        }
        g_PlayerHud.unk24 = 0x33;
    }
    return 1;
}

s32 func_06076718(void) { return g_PlayerHud.unk24 == 0x15; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607672C, func_0607672C);

extern s16 g_AlternateStatusHudSpriteOffsets[][2];

// func_06076A04
void UpdateCompactStatusHud(void) {
    s32 sVar4;
    u16 sVar9;
    s32 iVar10;
    Primitive* prim;
    u16* ptr;

    u8 local_30[10] = {0x0,  0x33, 0x37, 0x34, 0x38,
                       0x35, 0x36, 0x24, 0x3A, 0x39};
    u8 local_31[10] = {0x0, 0x8, 0x8, 0x7, 0x7, 0x8, 0x8, 0x9, 0x8, 0x8};

    if (g_PlayerHud.displayHP < g_Status.hp) {
        g_PlayerHud.displayHP += 5;
        if (g_PlayerHud.displayHP > g_Status.hp) {
            g_PlayerHud.displayHP = g_Status.hp;
        }
    } else if (g_PlayerHud.displayHP > g_Status.hp) {
        g_PlayerHud.displayHP -= 5;
        if (g_PlayerHud.displayHP < g_Status.hp) {
            g_PlayerHud.displayHP = g_Status.hp;
        }
    }
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    prim = prim->next;
    if (g_PlayerHud.displayHP != 0) {
        sVar4 = ((g_PlayerHud.displayHP * 90) / g_Status.hpMax);
        prim->y2 = prim->y0 - sVar4;
        prim->drawMode &= ~DRAW_HIDE;
    } else {
        prim->drawMode |= DRAW_HIDE;
    }
    sVar4 = (g_Status.mp * 57) / g_Status.mpMax;
    prim = prim->next;
    if (g_Status.mp == g_Status.mpMax) {
        u16 uVar11 = (g_Timer & 0x10) ? g_Timer % 0x10 : ~g_Timer % 0x10;
        sVar9 = uVar11 + 1;
        if (sVar9 > 0xE) {
            sVar9 = 0xE;
        }
    } else {
        sVar9 = 0xF;
    }

    prim->unk6 = LookupTblNoToVram(DAT_06086388->flags + 10);
    prim->unk6 = sVar9 + prim->unk6 & 0x8FFF | 0x4000;
    prim->y3 = prim->y2 = prim->y0 - sVar4;
    prim = prim->next;
    if (g_Status.hearts < 100) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex +
                           g_AlternateStatusHudSpriteOffsets[3][0] +
                           (g_Status.hearts / 100)];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
    }
    prim = prim->next;
    if (g_Status.hearts < 10) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex +
                           g_AlternateStatusHudSpriteOffsets[4][0] +
                           ((g_Status.hearts / 10) % 10)];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
    }
    prim = prim->next;
    ptr = DAT_0605aec0[DAT_06086388->allocationIndex +
                       g_AlternateStatusHudSpriteOffsets[5][0] +
                       (g_Status.hearts % 10)];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim = prim->next;
    if (g_Status.subWeapon == 0) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        s32 sub = g_Status.subWeapon;
        ptr = DAT_0605aec0[g_SaturnSharedSpriteBank0Resource.allocationIndex +
                           local_30[sub]];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        prim->unk6 =
            LookupTblNoToVram(DAT_06086388->flags + local_31[sub]) & 0x8FFF |
            0x4000;
        SetXY(prim, DAT_06085d3c[sub * 2], DAT_06085d3c[sub * 2 + 1]);
        prim->drawMode &= ~DRAW_HIDE;
    }
    prim = prim->next;
    if ((s32)g_Player.unk3FC > 300) {
        iVar10 = ((g_GameTimer >> 2) & 1) + 5;
    } else if ((s32)g_Player.unk3FC > 200) {
        iVar10 = ((g_GameTimer >> 2) & 1) + 3;
    } else if ((s32)g_Player.unk3FC > 100) {
        iVar10 = ((g_GameTimer >> 3) & 1) + 3;
    } else {
        iVar10 = 0x0;
    }

    prim->unk6 =
        LookupTblNoToVram(DAT_06086388->flags + iVar10) & 0x8FFF | 0x4000;
    if (g_PlayerHud.unk24 == 0) {
        if ((g_Status.D_80097BF8 & 1) == 0) {
            if ((g_Timer & 0xF) == 0) {
                g_Status.mp++;
            }
            if (g_Status.mp > g_Status.mpMax) {
                g_Status.mp = g_Status.mpMax;
            }
        }
    } else if (g_PlayerHud.unk24 != 0x0 && g_PlayerHud.unk24 < 0x6) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 1];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x19);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0xC) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 2];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x1D);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0x11) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 3];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x19);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0x15) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 4];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x15);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 0x15) {
    } else if (g_PlayerHud.unk24 > 0x32 && g_PlayerHud.unk24 < 0x39) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 3];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x19);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0x3D) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 2];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x1D);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0x42) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex + 1];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x19);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 < 0x47) {
        ptr = DAT_0605aec0[DAT_06086388->allocationIndex];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        SetXY(prim, 0x2D, 0x15);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 0x47) {
        g_PlayerHud.unk24 = 0;
    }
}

// original name: set_XYWH
void SetXYWH(Primitive* prim, s32 x, s32 y, s32 w, s32 h) {
    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + w - 1;
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + h - 1;
}

void SetXW(Primitive* prim, s32 x, s32 w) {
    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + w - 1;
}

void SetYH(Primitive* prim, s32 y, s32 h) {
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + h - 1;
}

// func_060771D4
void SetHudPrimSprite(Primitive* prim, s32 arg1) {
    u16* ptr;

    ptr = DAT_0605aec0[DAT_06086388->allocationIndex + arg1];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 =
        LookupTblNoToVram(DAT_06086388->flags + arg1) & 0x8FFF | 0x4000;
}

// func_06077260
void UpdateMpBarPrim(Primitive* prim) {
    u32 uVar4;
    u16 sVar6;
    u16 sVar7;

    uVar4 = g_GameTimer;
    if (g_Status.mp == g_Status.mpMax) {
        if (uVar4 & 0x10) {
            sVar7 = uVar4 % 0x10;
        } else {
            sVar7 = ~uVar4 % 0x10;
        }

        prim->x1 = prim->x2 = prim->x0 + 61;

        sVar6 = sVar7 + 1;
        if (sVar6 > 0xE) {
            sVar6 = 0xE;
        }
    } else {
        prim->x1 = prim->x2 = prim->x0 + (g_Status.mp * 61) / g_Status.mpMax;
        sVar6 = 0xF;
    }
    prim->unk6 = LookupTblNoToVram(DAT_06086388->flags + 11);
    prim->unk6 = sVar6 + prim->unk6 & 0x8FFF | 0x4000;
}

// func_06077354
// original name: set_heart_num
void SetHeartsNum(Primitive* prim) {
    u32 digit;
    s32 i;
    s32 leading_zeros;
    u32 uVar13;
    SubweaponDef subwpn;
    u16* ptr;
    u32 hearts;

    i = 10;
    hearts = g_Status.hearts;
    if (hearts >= 1000) {
        leading_zeros = 0;
    } else if (hearts >= 100) {
        leading_zeros = 1;
    } else if (hearts >= 10) {
        leading_zeros = 2;
    } else {
        leading_zeros = 3;
        i = 11;
    }

    if (func_800FE3C4(&subwpn, 0, false)) {
        if (g_Timer & 0x2) {
            uVar13 = DAT_06086388->flags + 9;
        } else {
            uVar13 = g_SaturnSharedSpriteBank4Resource.flags + 8;
        }
    } else {
        uVar13 = DAT_06086388->flags + 9;
    }

    digit = (hearts / 1000) % 10;
    if (digit == 0) {
        digit = 10;
    }
    digit += g_SaturnSharedSpriteBank4Resource.allocationIndex + 3;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar13) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteX[i], g_HudSpriteW[i]);
        leading_zeros = 0;
        i++;
    }
    prim = prim->next;

    digit = (hearts / 100) % 10;
    if (digit == 0) {
        digit = 10;
    }
    digit += g_SaturnSharedSpriteBank4Resource.allocationIndex + 3;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar13) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteX[i], g_HudSpriteW[i]);
        leading_zeros = 0;
        i++;
    }
    prim = prim->next;

    digit = (hearts / 10) % 10;
    if (digit == 0) {
        digit = 10;
    }
    digit += g_SaturnSharedSpriteBank4Resource.allocationIndex + 3;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar13) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteX[i], g_HudSpriteW[i]);
        i++;
    }
    prim = prim->next;

    digit = hearts % 10;
    if (digit == 0) {
        digit = 10;
    }
    digit += g_SaturnSharedSpriteBank4Resource.allocationIndex + 3;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar13) & 0x8FFF | 0x4000;
    SetXW(prim, g_HudSpriteX[i], g_HudSpriteW[i]);
}

// original name: set_life_num
void SetLifeNum(Primitive* prim) {
    s32 digit;
    s32 x;
    s32 leading_zeros;
    u32 displayHP;
    u32 uVar11;
    u16* ptr;

    displayHP = g_PlayerHud.displayHP;
    if (displayHP >= 1000) {
        leading_zeros = 0;
        x = g_HudSpriteX[6];
    } else if (displayHP >= 100) {
        leading_zeros = 1;
        x = g_HudSpriteX[7];
    } else if (displayHP >= 10) {
        leading_zeros = 2;
        x = g_HudSpriteX[8];
    } else {
        leading_zeros = 3;
        x = g_HudSpriteX[9];
    }
    if (g_PlayerHud.displayHP == g_Status.hpMax) {
        uVar11 = DAT_06086388->flags + 2;
    } else if (g_PlayerHud.displayHP <= g_Status.hpMax >> 2) {
        uVar11 = DAT_06086388->flags + 10;
    } else {
        uVar11 = DAT_06086388->flags;
    }
    digit = (displayHP / 1000) % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar11) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteY[6];
        leading_zeros = 0;
        x += 7;
    }
    prim = prim->next;
    digit = (displayHP / 100) % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar11) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteY[6];
        leading_zeros = 0;
        x += 7;
    }
    prim = prim->next;
    digit = (displayHP / 10) % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar11) & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteY[6];
        x += 7;
    }
    prim = prim->next;
    digit = displayHP % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = LookupTblNoToVram(uVar11) & 0x8FFF | 0x4000;
    prim->x0 = x;
    prim->y0 = g_HudSpriteY[6];
}

// original name: status_disp_init
void StatusDispInit(void) {
    Primitive* prim;
    s32 i;

    DAT_06086388 = DAT_06064650[11];
    D_8013B5E8 = 0;
    g_PlayerHud.displayHP = g_Status.hp;
    g_PlayerHud.g_HealingMailTimer = 0;

    if ((g_CurrentRoom.stageID == STAGE_ST0) || (g_PlayableCharacter == 1)) {
        func_06075838();
    } else if (g_PlayableCharacter == 2) {
        func_0607672C();
    } else {
        g_PlayerHud.primIndex1 = AllocPrimitives(0x0, 0xE);
        prim = &g_PrimBuf[g_PlayerHud.primIndex1];
        for (i = 0; prim != NULL; i++) {
            SetXYWH(prim, g_HudSpriteX[i], g_HudSpriteY[i], g_HudSpriteW[i],
                    g_HudSpriteH[i]);
            prim->priority = 0x1C0;
            prim->drawMode = g_HudSpriteBlend[i];
            switch (i) {
            case 4:
                SetHudPrimSprite(prim, 0);
                break;
            case 5:
                SetHudPrimSprite(prim, 1);
                break;
            case 3:
                prim->type = 0x1004;
                prim->unk4 = 0x4C0;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
                prim->type = 0x1001;
                prim->unk4 |= 0x1000;
            }
            prim->unk4 &= 0xFFC7;
            prim = prim->next;
        }
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077D88, func_06077D88);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078120, func_06078120);
