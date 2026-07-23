// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/scl.h"
#include <saturn_sprite.h>

void UpdateCapePalette(void);

extern u16 D_8003C730;
extern u8 g_CastleMap[];
extern s32 D_801397FC;
extern s32 D_80139008;
extern s32 g_GameClearFlag;
extern char* g_LuckCode;
extern char* g_AxeArmorCode;
extern char* g_GTIClubCode;

extern s32 TimeAttackController(s32 eventId, s32 action);

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
    if ((DAT_0605d750.stageID == STAGE_ST0) || (g_PlayableCharacter != 0)) {
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
        if ((DAT_0605d750.stageID != STAGE_ST0) &&
            (DAT_0605d750.stageID != 0x41)) {
            g_Status.subWeapon = MTH_GetRand() % 9 + 1;
        }
        if (DAT_0605d750.stageID == STAGE_ST0) {
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
        if (DAT_0605d750.stageID == 0x41) {
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
    if (DAT_0605d750.stageID == 0x41) {
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
        if (DAT_0605d750.stageID & STAGE_INVERTEDCASTLE_FLAG) {
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

inline void SetXW(Primitive* prim, s32 x, s32 w) {
    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + w - 1;
}

void SetYH(Primitive* prim, s32 y, s32 h) {
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + h - 1;
}

extern u16 DAT_0605aec0[][2];
extern SaturnSpriteResource* DAT_06086388;

static inline u16 unkFunc(u16 arg0) {
    if (arg0 & 0x4000) {
        return func_06007CE0(arg0 & 0xFFF);
    } else {
        return SPR_2LookupTblNoToVram(arg0 & 0xFFF);
    }
}

void func_060771D4(Primitive* prim, s32 arg1) {
    u16* ptr;

    ptr = DAT_0605aec0[DAT_06086388->allocationIndex + arg1];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = unkFunc(DAT_06086388->flags + arg1);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
}

void func_06077260(Primitive* prim) {
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
    prim->unk6 = unkFunc(DAT_06086388->flags + 11);
    prim->unk6 = sVar6 + prim->unk6 & 0x8FFF | 0x4000;
}

extern SaturnSpriteResource g_SaturnSharedSpriteBank4Resource;
extern u8 g_HudSpriteU[];
extern u8 g_HudSpriteV[];
extern u8 g_HudSpriteWidth[];

void func_06077354(Primitive* prim) {
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
    prim->unk6 = unkFunc(uVar13);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteU[i], g_HudSpriteWidth[i]);
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
    prim->unk6 = unkFunc(uVar13);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteU[i], g_HudSpriteWidth[i]);
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
    prim->unk6 = unkFunc(uVar13);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        SetXW(prim, g_HudSpriteU[i], g_HudSpriteWidth[i]);
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
    prim->unk6 = unkFunc(uVar13);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    SetXW(prim, g_HudSpriteU[i], g_HudSpriteWidth[i]);
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
        x = g_HudSpriteU[6];
    } else if (displayHP >= 100) {
        leading_zeros = 1;
        x = g_HudSpriteU[7];
    } else if (displayHP >= 10) {
        leading_zeros = 2;
        x = g_HudSpriteU[8];
    } else {
        leading_zeros = 3;
        x = g_HudSpriteU[9];
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
    prim->unk6 = unkFunc(uVar11);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteV[6];
        leading_zeros = 0;
        x += 7;
    }
    prim = prim->next;
    digit = (displayHP / 100) % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = unkFunc(uVar11);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteV[6];
        leading_zeros = 0;
        x += 7;
    }
    prim = prim->next;
    digit = (displayHP / 10) % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = unkFunc(uVar11);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    if (leading_zeros != 0) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_HudSpriteV[6];
        x += 7;
    }
    prim = prim->next;
    digit = displayHP % 10;
    digit += DAT_06086388->allocationIndex + 10;
    ptr = DAT_0605aec0[digit];
    prim->unk8 = ptr[0];
    prim->unkA = ptr[1];
    prim->unk6 = unkFunc(uVar11);
    prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    prim->x0 = x;
    prim->y0 = g_HudSpriteV[6];
}

// _status_disp_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077B20, func_06077B20);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077D88, func_06077D88);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078120, func_06078120);
