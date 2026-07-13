// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

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

extern s16 g_ButtonMask[];

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

extern s8 DAT_06057f68;
void (*func_060645BC)(void);
void (*func_060645FC)(void);
void (*func_06064600)(void);
void (*func_06064620)(void);
void (*func_06064638)(void);
extern s16 DAT_06086220[];

void func_06074278(s32);

// original name: INIT_SUB_GAMEN
void func_060732E4(s32 arg0) {
    s16 sVar3;
    s32 i;

    switch (arg0) {
    case 7:
        (*func_06064638)();
        for (i = 0; i < 10; i++) {
            DAT_06086220[i] = 0x7E + i * 14;
        }
        func_06074278(0);
        break;
    case 8:
        (*func_060645FC)();
        func_06074278(0);
        break;
    case 9:
        (*func_060645BC)();
        func_06074278(0);
        break;
    case 10:
        (*func_06064620)();
        func_06009570(3);
        func_06074278(1);
        break;
    case 11:
        (*func_06064600)();
        func_06009570(4);
        func_06074278(1);
        break;
    }
    DAT_06057f68 = 1;
}

extern s32 DAT_060855ac;

// original name: PSX_cursor_up_down
void MenuHandleCursorInput(s32* nav, u8 nOptions, u32 type) {
    u8 prevCursor = *nav;

    switch (type) {
    case 3: // vertical clamp
        if (g_pads[0].repeat & 0x1000) {
            if (*nav) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & 0x2000) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 0: // vertical loop
        if (g_pads[0].repeat & 0x1000) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & 0x2000) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 4: // horizontal clamp
        if (g_pads[0].repeat & 0x4000) {
            if (*nav) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & 0x8000) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 5: // horizontal loop
        if (g_pads[0].repeat & 0x4000) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & 0x8000) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 1:
    case 2:
        if (g_pads[0].repeat & 0x1000) {
            if (*nav >= 2) {
                *nav -= 2;
            }
        } else if (g_pads[0].repeat & 0x2000) {
            if (*nav == nOptions - 2) {
                if (*nav & 1) {
                    *nav += 1;
                }
            }
            if (*nav < nOptions - 2) {
                *nav += 2;
            }
        }
        if (g_pads[0].repeat & 0xC000) {
            *nav ^= 1;
            if (*nav == nOptions) {
                *nav ^= 1;
            }
        }
        if ((type == 2) && (DAT_060855ac == 0)) {
            if (g_pads[0].repeat & 8) {
                if (*nav >= 10) {
                    *nav -= 10;
                } else {
                    *nav = 0;
                }
            }
            if (g_pads[0].repeat & 0x80) {
                if (*nav < nOptions - 10) {
                    *nav += 10;
                } else {
                    *nav = nOptions - 1;
                }
            }
        }
        break;
    }
    if (prevCursor != *nav) {
        PlaySfx(SFX_UI_MOVE);
    }
}

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

extern s32 g_NewPlayerStatsTotal[];
extern s32 g_NewAttackRightHand;
extern s32 g_NewAttackLeftHand;
extern s32 g_NewDefenseEquip;

// SAT: func_060735A4
void func_800F7244(void) {
    s32 i;

    g_NewAttackRightHand = g_Status.attackHands[0];
    g_NewAttackLeftHand = g_Status.attackHands[1];
    g_NewDefenseEquip = g_Status.defenseEquip;
    for (i = 0; i < 4; i++) {
        g_NewPlayerStatsTotal[i] =
            g_Status.statsBase[i] + g_Status.statsEquip[i];
    }
}

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

void func_06074C28(void) {
    g_Status.equipment[0] = 0xA6;
    g_Status.equipment[1] = 0x10;
    g_Status.subWeapon = 0;
    g_Status.hpMax = g_Status.hp = 300;
    g_Status.mpMax = g_Status.mp = 1000;
    g_Status.equipment[3] = 0x2F;
    g_Status.equipment[4] = 0xF;
    g_Status.equipment[5] = 0x39;
    g_Status.equipment[6] = 0x50;
    g_Status.equipment[7] = 0x48;
}

INCLUDE_ASM("asm/saturn/game/data", d6074C9C, d_06074C9C);

extern u16 D_8003C730;
extern u8 g_CastleMap[];
extern s32 D_801397FC;
extern s32 D_80139008;
extern s32 g_GameClearFlag;
extern char* g_LuckCode;
extern char* g_AxeArmorCode;
extern char* g_GTIClubCode;

extern void UpdateCapePalette(void);
extern s32 TimeAttackController(s32 eventId, s32 action);
extern u32 MTH_GetRand(void);

static inline void func_800FF708(s32 equipType, s32 arg1) {
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
    if ((g_StageId == 0x1F) || (g_PlayableCharacter != 0)) {
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
        if ((g_StageId != 0x1F) && (g_StageId != 0x41)) {
            g_Status.subWeapon = MTH_GetRand() % 9 + 1;
        }
        if (g_StageId == 0x1F) {
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
        if (g_StageId == 0x41) {
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
    if (g_StageId == 0x41) {
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
        if (g_GameClearFlag != 0) {
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
        if (g_StageId & 0x20) {
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

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075838, func_06075838);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075D24, func_06075D24);

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
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6076A04, func_06076A04);

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

extern s32 DAT_06086390;

char* func_06078748(s32 id) {
    char* ret = NULL;
    switch (DAT_06086390) {
    case 1:
        if (id < 0xB0) {
            Equipment* equip = &g_EquipDefs[id];
            ret = equip->name;
        } else {
            Accessory* acc;
            id -= 0xB0;
            acc = &g_AccessoryDefs[id];
            ret = acc->name;
        }
        break;
    case 3: {
        RelicDesc* relic = &g_RelicDefs[id];
        ret = relic->name;
    } break;
    case 2: {
        SpellDef* spell = &g_SpellDefs[id];
        ret = spell->name;
    } break;
    }
    return ret;
}

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

u16 LimitAngleChange(u16 delta, u16 base, u16 target) {
    u16 temp_a2 = (s16)(target - base);
    u16 ret;

    if (temp_a2 & 0x800) {
        ret = (0x800 - temp_a2) & 0x7FF;
    } else {
        ret = temp_a2;
    }

    if (ret > delta) {
        if (temp_a2 & 0x800) {
            ret = base - delta;
        } else {
            ret = base + delta;
        }
        return ret;
    }
    return target;
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

void PlaySfxVolPan();

void PlaySfxPositional(s32 sfxId) {
    Entity* entity = g_CurrentEntity;
    s16 sfxVol;
    int dx;
    s32 dy;
    s16 sfxPan;

    dx = entity->posX.i.hi - 0xA0;
    sfxPan = (ABS(dx) - 0x28) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (dx < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = ABS(dx) - 0x60;

    dy = ABS(entity->posY.i.hi - 0x80) - 0x70;
    if (dy > 0) {
        sfxVol += dy;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 0x7F - (sfxVol >> 1);
    if (sfxVol > 0) {
        PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}

void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B7B4, func_0607B7B4);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BE38, func_0607BE38);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BED0, func_0607BED0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C054, func_0607C054);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0A0, func_0607C0A0);

// _MTH_GetRand
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0BC, func_0607C0BC);
