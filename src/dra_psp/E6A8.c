// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "../dra/menu.h"

bool CheckIfAllButtonsAreAssigned(void) {
    s32 buf[8];
    s32 i;
    s32 bitMask_Assigned;
    s32* miscPtr;

    for (i = 1; i < 8; i++) {
        buf[i] = 0;
    }

    for (i = 0; i < 7; i++) {
        buf[g_Settings.buttonConfig[i] + 1] = 1;
    }

    // What is the purpose of this loop?
    for (i = 0, miscPtr = &buf[1]; i < 7; miscPtr++, i++) {
        if (*miscPtr == 0) {
            break;
        }
    }

    for (i = 0; i < 7; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    miscPtr = g_Settings.buttonConfig;
    for (i = 1; i < 8; i++) {
        bitMask_Assigned |= 1 << *miscPtr++;
    }

    return bitMask_Assigned == 0x7F;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", IsAlucart);

extern s32 g_StatBuffTimers[16];

void func_800F4994(void) {
    s32* statsPtr = &g_Status.statsEquip[0];
    s32 correctStonesEquipped;
    s32 hourOfDay;
    s32 i, j;
    s32 statBonus;

    for (i = 0; i < 4; i++, statsPtr++) {
        *statsPtr = 0;
    }

    // Iterate through each Item Slot
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus = g_AccessoryDefs[g_Status.equipment[HEAD_SLOT + i]]
                            .statsBonus[j];
            if (statBonus > 128) {
                statBonus -= 256;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }
    hourOfDay = g_Status.timerHours % 24;

    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_SUNSTONE, EQUIP_ACCESSORY);
        statsPtr = &g_Status.statsEquip[0];
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_MOONSTONE, EQUIP_ACCESSORY);
        statsPtr = &g_Status.statsEquip[0];
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    }

    if (g_StatBuffTimers[4]) {
        g_Status.statsEquip[STAT_STR] += 20;
    }
    if (g_StatBuffTimers[3]) {
        g_Status.statsEquip[STAT_INT] += 20;
    }
    if (g_StatBuffTimers[2]) {
        g_Status.statsEquip[STAT_LCK] += 20;
    }
    if (g_Status.relics[RELIC_RIB_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_CON] += 10;
    }
    if (g_Status.relics[RELIC_EYE_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_LCK] += 10;
    }
    if (g_Status.relics[RELIC_TOOTH_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_STR] += 10;
    }
    if (g_Status.relics[RELIC_RING_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_INT] += 10;
    }
    if (IsAlucart() != false) {
        g_Status.statsEquip[STAT_LCK] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] =
        (g_Status.statsEquip[1] * 8) + g_Status.statsBase[1];
    g_Status.statsTotal[2] =
        (g_Status.statsEquip[2] * 4) + g_Status.statsBase[2];
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

extern s32 g_StatBuffTimers[16];

s32 CalcAttack(s32 equipId, u32 otherEquipId) {
    s32 i;
    s16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (g_EquipDefs[equipId].itemCategory == ITEM_FOOD ||
        g_EquipDefs[equipId].itemCategory == ITEM_MEDICINE) {
        return 0;
    }
    if (g_EquipDefs[equipId].itemCategory == ITEM_SHIELD &&
        g_EquipDefs[equipId].attack == 1) {
        return 0;
    }

    if (equipId == ITEM_ALUCARD_SHIELD) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            g_AccessoryDefs[g_Status.equipment[2 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (totalAttack <= strengthStat) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    if (equipId == ITEM_BADELAIRE) {
        totalAttack += g_Status.timerHours;
    }
    if (equipId == ITEM_MURAMASA) {
        totalAttack += SquareRoot0(g_Status.D_80097C40);
    }
    if (equipId == 4 && g_EquipDefs[otherEquipId].itemCategory == ITEM_SHIELD) {
        totalAttack += 5;
    }
    if (equipId == ITEM_SWORD_FAMILIAR) {
        totalAttack += g_Status.statsFamiliars[FAM_STATS_SWORD].level;
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

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EB850);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EB8B8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F53A4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EBE50);

u8 func_800F548C(u8 arg0) {
    if (arg0 & 0x100) {
        return func_800F548C(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_800F548C((arg0 & 0x7F) + 3);
    }
    return arg0 << 4;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EBF50);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EBFA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EC0C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EC248);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawImg);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F5A90);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F5AE4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawSprite);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawRect);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F5E68);

extern s16 g_RelicMenuFadeTimer;
void DrawRelicsMenu(MenuContext* ctx) {
    s32 ctx_h;
    s32 switchFadeLevel;
    s32 i;
    s32 spriteX;
    s32 spriteY;
    s32 baseY;
    s32 var_s3;
    s32 u_OnOff;
    u8* relic;

    ctx_h = ctx->h;
    relic = &g_Status.relics[RELIC_SOUL_OF_BAT];

    for (i = 0; i < 30; i++, relic++) {
#define INDEXER i
        spriteX = (i & 1) * 0xB0;
        spriteY = ctx_h + ((INDEXER / 2) * 0x13 + 0x22);
        if (*relic & RELIC_FLAG_FOUND) {
            if (spriteY < 0) {
                continue;
            }
            if (spriteY >= 193) {
                continue;
            }
            if ((i & 2) == 0) {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i / 4 + 0x80), 0x1A1, 6, 1, 0, 0);
            } else {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i / 4 + 0x103), 0x1A1, 7, 1, 0, 0);
            }
        }
        // Determine the U value for the texture to use for the switch
        if (*relic & RELIC_FLAG_ACTIVE) {
            u_OnOff = 0;
        } else {
            u_OnOff = 0x30;
        }
        switchFadeLevel = 0;
        if (INDEXER == g_MenuNavigation.cursorRelic) {
            // This routine handles the fade in/fade out of the ON/OFF switch
            // when hovering
            if (++g_RelicMenuFadeTimer >= 0x48) {
                g_RelicMenuFadeTimer = 0;
            }
            if (g_RelicMenuFadeTimer < 0x24) {
                // Fade up
                switchFadeLevel = g_RelicMenuFadeTimer / 6;
            } else {
                // Fade down
                switchFadeLevel = 6 - ((g_RelicMenuFadeTimer - 0x24) / 6);
            }
        }
        MenuDrawSprite(ctx, spriteX + 8, spriteY, 0x2F, 0xF, u_OnOff, 0x70,
                       switchFadeLevel + 0x1C8, 0x1F,
                       INDEXER == g_MenuNavigation.cursorRelic, 0x40, 0);
    }
    spriteY = ctx_h + ((g_MenuNavigation.cursorRelic / 2) * 0x13 + 0x22);
    MenuDrawRect(ctx, ((g_MenuNavigation.cursorRelic & 1) * 0xB0) + 8,
                 spriteY - 1, 0xA8, 0x12, 0x60, 0, 0);
#undef INDEXER
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawAlucardPortrait);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECD58);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECD78);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawAlucardCloakPreview);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECF20);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F6568);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F6618);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F66BC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawChar);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawStr);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawInt);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawTime);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F6A48);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuJosephsCloakDraw);

u8 g_ChButtons[] = {SQUARE,  CIRCLE,  CROSS,   TRIANGLE, CH('L'), CH('R'), CH('L'), NULL};
u8 g_ChButtons2[] = {NULL, NULL, CH('+'), NULL, NULL, NULL, NULL, NULL};
u8 g_ChButtons3[] = {NULL, NULL, CH('R'), NULL, NULL, NULL, NULL, NULL};

char D_psp_0914A3B8[] = {CH('R'), CH('G'), CH('B')}; //en
char D_psp_0914A3C0[] = {CH('R'), CH('V'), CH('B')}; //it
char D_psp_0914A3C8[] = {CH('R'), CH('V'), CH('A')}; //sp
char D_psp_0914A3D0[] = {CH('R'), CH('V'), CH('B')}; //fr
char D_psp_0914A3D8[] = {CH('R'), CH('G'), CH('B')}; //ge

extern u8* g_ChRgb[];

extern u8* func_psp_090EAF08(void*, void*, void*, void*, void*);

void MenuWindowColorsDraw(MenuContext* context) {
    s32 x = 188;
    s32 y;
    s32 i;

    *g_ChRgb = func_psp_090EAF08(&D_psp_0914A3B8, &D_psp_0914A3D0, &D_psp_0914A3C8,
                          &D_psp_0914A3D8, &D_psp_0914A3C0);

    for (i = 0; i < 3; i++) {
        MenuDrawChar((*g_ChRgb)[i], x + 32, (i * 12) + 80, context);
        MenuDrawInt(g_Settings.windowColors[i], x + 72, 80 + i * 12, context);
    }
    func_800F5E68(
        context, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", SortTimeAttackEntries);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuTimeAttackDraw);

void MenuButtonConfigDraw(MenuContext* ctx) {
    s32 i;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;

    const s32 InitCursorX = 0xA4;
    const s32 W = 0x54;
    
    s32 cursorX = InitCursorX;

    for (i = 0; i < 7; i++) {
        MenuDrawStr(g_MenuStr[22 + i], cursorX, 0x30 + (i * 0x10), ctx);
        buttonId = g_Settings.buttonConfig[i];
        btn1_x = (buttonId * 12);
        MenuDrawChar(g_ChButtons[buttonId], 0xFC + btn1_x, 0x30 + (i * 0x10), ctx);
        if (buttonId >= 4) {
            MenuDrawChar(g_ChButtons2[buttonId-4], 0x104 + btn1_x, 0x30 + (i * 0x10), ctx);
            btn2_x = btn1_x + 8;
            MenuDrawChar(g_ChButtons3[buttonId-4], 0x104 + btn2_x,
                         0x30 + (i * 0x10), ctx);
        }
    }

    func_800F5E68(
        ctx, g_MenuNavigation.cursorButtons, cursorX - 2, 46, W, 12, 4, 1);
}

void MenuReverseCloakDraw(MenuContext* context) {
    const int StrX = 188;
    const int ImgW = 88;
    char** menuStr;

    menuStr = g_MenuStr;
    MenuDrawStr(menuStr[30], StrX, 48, context);
    menuStr = g_MenuStr;
    MenuDrawStr(menuStr[31], StrX, 64, context);
    func_800F5E68(context, g_Settings.isCloakLiningReversed, StrX - 2, 46, ImgW,
                  12, 4, 1);
}

void MenuSoundConfigDraw(MenuContext* context) {}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ED9E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EDA78);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EDB70);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EDBA0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuStatChangesDraw);

const char** D_800A2D68;

extern MenuData g_MenuData;

void MenuDrawStats(s32 menuDialogue) {
    MenuContext* ctx;
    char* menuStr;
    s32 temp_s1;
    s32 temp_var;
    s32 x;
    s32 y;
    s32 i;
    s32 temp_y;
    s32 phi_a0_5;

    ctx = &g_MenuData.menus[menuDialogue];
    func_800F53A4();
    if (menuDialogue == MENU_DG_BG) {
        MenuDrawAlucardPortrait(ctx);
        if(IsAlucart()){
            MenuDrawStr(g_MenuStr[42], 128, 40, ctx);
        } else {
            MenuDrawStr(g_MenuStr[0], 128, 40, ctx);
        }
        MenuDrawStr(g_MenuStr[12], 96, 56, ctx);
        MenuDrawInt(g_Status.hp, 168, 56, ctx);
        MenuDrawChar(CH('/'), 176, 56, ctx);
        MenuDrawInt(g_Status.hpMax, 208, 56, ctx);
        MenuDrawStr(g_MenuStr[13], 96, 68, ctx);
        MenuDrawInt(g_Status.mp, 168, 68, ctx);
        MenuDrawChar(CH('/'), 176, 68, ctx);
        MenuDrawInt(g_Status.mpMax, 208, 68, ctx);
        MenuDrawStr(g_MenuStr[14], 96, 80, ctx);
        MenuDrawInt(g_Status.hearts, 168, 80, ctx);
        MenuDrawChar(CH('/'), 176, 80, ctx);
        MenuDrawInt(g_Status.heartsMax, 208, 80, ctx);
        MenuDrawStr(g_MenuStr[5], 32, 176, ctx);
        MenuDrawInt(g_Status.exp, 144, 176, ctx);
        MenuDrawStr(g_MenuStr[6], 32, 188, ctx);
        MenuDrawInt(g_Status.level != 99
                        ? g_ExpNext[g_Status.level + 1] - g_Status.exp
                        : 0,
                    144, 188, ctx);
        MenuDrawStr(g_MenuStr[7], 32, 200, ctx);
        MenuDrawInt(g_Status.gold, 144, 200, ctx);
        MenuDrawStr(g_MenuStr[8], 248, 40, ctx);
        MenuDrawInt(g_Status.level, 304, 40, ctx);
        MenuDrawStr(g_MenuStr[15], 248, 56, ctx);
        i = 37;
        if (g_Player.status & PLAYER_STATUS_CURSE) {
            i = 40;
        }
        if (g_Player.status & PLAYER_STATUS_POISON) {
            i = 38;
        }
        if (g_Player.status & PLAYER_STATUS_STONE) {
            i = 39;
        }
        if (IsAlucart()) {
            i = 45;
        }
        MenuDrawStr(g_MenuStr[i], 260, 68, ctx);
        MenuDrawStr(g_MenuStr[10], 252, 150, ctx);
        MenuDrawInt(g_RoomCount, 340, 150, ctx);
        MenuDrawStr(g_MenuStr[11], 252, 164, ctx);
        MenuDrawInt(g_Status.killCount, 340, 164, ctx);
        MenuDrawStr(g_MenuStr[9], 244, 192, ctx);
        MenuDrawInt(g_Status.timerHours, 300, 192, ctx);
        MenuDrawChar(CH(':'), 308, 192, ctx);
        MenuDrawTime(g_Status.timerMinutes, 324, 192, ctx, 2);
        MenuDrawChar(CH(':'), 332, 192, ctx);
        MenuDrawTime(g_Status.timerSeconds, 348, 192, ctx, 2);
    }

    if (ctx == &g_MenuData.menus[MENU_DG_BG]) {
        x = 248;
        y = 88;
    } else {
        x = 232;
        y = 80;
    }
    func_800F66BC(D_800A2D68[0], x, y, ctx, 1);

    temp_var = g_Settings.buttonConfig[0];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        MenuDrawChar(g_ChButtons[temp_s1], x + 44, y, ctx);
    } else {
        if(temp_s1 == 7){
            MenuDrawChar(g_ChButtons[temp_s1], x + 40, y, ctx);
            MenuDrawChar(g_ChButtons2[temp_s1], x + 48, y, ctx);
            MenuDrawChar(g_ChButtons3[4 + temp_s1], x + 56, y, ctx);
        } else {
            MenuDrawChar(g_ChButtons[temp_s1], x + 44, y, ctx);
        }
        
    }
    MenuDrawInt(g_Status.attackHands[0], x + 76, y, ctx);

    temp_var = g_Settings.buttonConfig[1];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        MenuDrawChar(g_ChButtons[temp_s1], x + 44, y + 10, ctx);
    } else {
        if(temp_s1 == 7){
            MenuDrawChar(g_ChButtons[temp_s1], x + 40, y + 10, ctx);
            MenuDrawChar(g_ChButtons2[temp_s1], x + 48, y + 10, ctx);
            MenuDrawChar(g_ChButtons3[4 + temp_s1], x + 56, y + 10, ctx);
        } else {
            MenuDrawChar(g_ChButtons[temp_s1], x + 44, y + 10, ctx);
        }
    }

    MenuDrawInt(g_Status.attackHands[1], x + 76, y + 10, ctx);
    func_800F66BC(D_800A2D68[1], x, y + 20, ctx, 1);
    MenuDrawInt(g_Status.defenseEquip, x + 76, y + 26, ctx);
    if (ctx == (&g_MenuData.menus[MENU_DG_BG])) {
        x = 32;
        y = 120;
    } else {
        func_800F66BC(D_800A2D68[g_MenuNavigation.cursorEquip + 0x12], 15, 40, ctx, true);
        x = 12;
        y = 70;
    }

    for (i = 0, temp_y = y; i < 4; temp_y += 12, i++) {
        s32* statsBase = &g_Status.statsBase[i];
        MenuDrawStr(g_MenuStr[1 + i], x, temp_y, ctx);
        MenuDrawInt(*statsBase, x + 44, temp_y, ctx);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                MenuDrawChar(CH('+'), x + 52, temp_y, ctx);
                phi_a0_5 = g_Status.statsEquip[i];
            } else {
                MenuDrawChar(CH('-'), x + 52, temp_y, ctx);
                phi_a0_5 = -g_Status.statsEquip[i];
            }
            MenuDrawInt(phi_a0_5, x + 68, temp_y, ctx);
        }
    }
}

void MenuSpellsDraw(MenuContext* ctx) {
    s32 buttonCFG;
    s32 spell;
    s32 charNum;
    s32 i;
    s32 colorIntensity;
    s32 yCoord;
    s32 v1;

    const s32 startXCoord = 180;
    func_800F66BC(D_800A2D68[2], 136, 36, ctx, 1);

    for (i = 0; i < NUM_SPELLS; i++) {
        spell = g_Status.spells[i];
        if (!(spell & 0x80)) {
            continue;
        }
        spell ^= 0x80;
        charNum = 0;
        yCoord = 64 + i * 16;
        // Count up how many characters are in the combo
        for(v1 = 0; g_SpellDefs[spell].combo[v1] != 0; v1++) {
            if(g_SpellDefs[spell].combo[v1] == 0xC0 && g_SpellDefs[spell].combo[v1+1] == 0xD2){
                charNum--;
            } else {
                charNum++;
            }
        }

        if (spell != SPELL_WING_SMASH) {
            MenuDrawStr(g_SpellDefs[spell].combo, startXCoord, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + ((charNum-1) * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[0];
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG], startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG], startXCoord + (charNum * 8), yCoord, ctx);
                if(buttonCFG == 7){
                    MenuDrawChar(g_ChButtons2[buttonCFG-4], startXCoord + (charNum * 8), yCoord, ctx);
                    MenuDrawChar(g_ChButtons3[buttonCFG-4], startXCoord + 8 + (charNum * 8), yCoord, ctx);
                    charNum++;
                }
            }
            MenuDrawChar(15, startXCoord + ((charNum+1) * 8), yCoord, ctx);

            buttonCFG = g_Settings.buttonConfig[1];
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG], startXCoord + ((charNum + 2) * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG],   startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                MenuDrawChar(g_ChButtons2[buttonCFG-4], startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                MenuDrawChar(g_ChButtons3[buttonCFG-4], startXCoord + 8 + ((charNum + 2) * 8), yCoord, ctx);
                if(buttonCFG == 7){
                    MenuDrawChar(g_ChButtons2[buttonCFG-4], startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                    MenuDrawChar(g_ChButtons3[buttonCFG-4], startXCoord + 8 + ((charNum + 2) * 8), yCoord, ctx);
                }
            }
        } else {
            MenuDrawChar(CH('?'), startXCoord, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + 8, yCoord, ctx);
            MenuDrawStr(g_SpellDefs[spell].combo, startXCoord + 16, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + 16 + ((charNum-1) * 8), yCoord, ctx);
            MenuDrawChar(CH('?'), startXCoord + 24 + ((charNum-1) * 8), yCoord, ctx);
        }
        MenuDrawStr(g_MenuStr[13], 292, yCoord, ctx);
        MenuDrawInt(g_SpellDefs[spell].mpUsage, 316, yCoord, ctx);
    }
    for (i = 0; i < 8; i++) {
        if (g_Status.spells[i] & 0x80) {
            MenuDrawImg(ctx, 0x1C, 0x3C + 0x10 * i, 0xF0, 0x10U, 0,
                        func_800F548C(0x80 + i) & 0xFF, 0x1A1, 6, true, 0);
        }
    }
    // The highlighted spell glows yellow, increasing and decreasing.
    if (g_Timer & 0x20) {
        colorIntensity = (g_Timer & 0x1F) + 0x60;
    } else {
        colorIntensity = 0x7F - (g_Timer & 0x1F);
    }
    // The colorIntensity gets passed to the MenuRect's R and G values, making
    // it a brighter or dimmer yellow.
    MenuDrawRect(ctx, 26, (g_MenuNavigation.cursorSpells * 0x10) + 0x3B, 300,
                 17, colorIntensity, colorIntensity, 0);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuFamiliarsDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F82F4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuSystemDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F84CC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F86E4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F8754);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuEquipSortDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F892C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F8990);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawLine);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", DrawConsumableCount);

extern MenuData g_MenuData;
extern s32 D_801377FC[NUM_MENU];

u8 D_800A2D80[] = {0x00, 0x20, 0x30, 0x40, 0x50, 0x60, 0x69, 0x70,
    0x75, 0x78, 0x7A, 0x7C, 0x7D, 0x7E, 0x7F, 0x80};

void MenuDraw(void) {
    u8 padding[32];
    s32 x;
    s32 y;
    Primitive* prim;
    Accessory* acc;
    Equipment* equip;
    MenuContext* menu;
    s16 swap;
    s32 cy;
    s32 cx;
    s16 r0;
    s16 g0;
    s16 b0;
    s16 r1;
    s16 g1;
    s16 b1;
    s32 var_a1;
    s32 cursorXMovement;
    s32 equipIndex;
    s32 cw;
    s32 ch;
    s32 flag;
    s32 i;
    s32 j;

    for (i = 0; i < NUM_MENU; i++) {
        prim = &g_PrimBuf[D_801377FC[i]];
        menu = &g_MenuData.menus[i];
        if (menu->unk1C == 2) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        cx = menu->cursorX;
        cy = menu->cursorY;
        cw = menu->cursorW;
        ch = menu->cursorH;
        var_a1 = menu->unk14 - menu->w;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        if (var_a1 == -1) {
            var_a1 = -2;
        }
        menu->w += var_a1 / 2;

        var_a1 = menu->unk16 - menu->h;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        if (var_a1 == -1) {
            var_a1 = -2;
        }
        menu->h += var_a1 / 2;

        x = cx + menu->w;
        y = cy + menu->h;

        if (menu->unk1C == 1) {
            menu->unk1D++;
            if (menu->unk1D == 16) {
                menu->unk1C = 2;
                prim->drawMode = DRAW_HIDE;
                continue;
            }
            cy += ch / 16 * menu->unk1D;
            ch -= ch / 16 * menu->unk1D;
            j = 16 - menu->unk1D;

            cursorXMovement = cw / 2 * (128 - D_800A2D80[j]) / 128;
            cx += cursorXMovement;
            cw -= cursorXMovement * 2;
        }
        if (menu->unk1C == 3) {
            menu->unk1D++;
            if (menu->unk1D == 16) {
                menu->unk1C = 0;
            } else {
                cursorXMovement =
                    cw / 2 * (128 - D_800A2D80[menu->unk1D]) / 128;
                cx += cursorXMovement;
                cw -= cursorXMovement * 2;
                j = 16 - menu->unk1D;
                ch -= ch / 16 * j;
            }
        }
        menu->unk1.x = cx;
        menu->unk1.y = cy;
        menu->unk1.w = cw;
        menu->unk1.h = ch;
        SetPrimRect(prim, cx, cy, cw, ch);

        r0 = (s16)(g_Settings.windowColors[0] * 8) - 0x20;
        if (r0 < 0) {
            r0 = 0;
        }
        g0 = (s16)(g_Settings.windowColors[1] * 8) - 0x20;
        if (g0 < 0) {
            g0 = 0;
        }
        b0 = (s16)(g_Settings.windowColors[2] * 8) - 0x20;
        if (b0 < 0) {
            b0 = 0;
        }
        r1 = (s16)(g_Settings.windowColors[0] * 8) + 0x20;
        if (r1 > 0xFF) {
            r1 = 0xFF;
        }
        g1 = (s16)(g_Settings.windowColors[1] * 8) + 0x20;
        if (g1 > 0xFF) {
            g1 = 0xFF;
        }
        b1 = (s16)(g_Settings.windowColors[2] * 8) + 0x20;
        if (b1 > 0xFF) {
            b1 = 0xFF;
        }
        if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_MAD) {
            swap = r0;
            r0 = r1;
            r1 = swap;
            swap = g0;
            g0 = g1;
            g1 = swap;
            swap = b0;
            b0 = b1;
            b1 = swap;
        }
        prim->r0 = r0;
        prim->g0 = g0;
        prim->b0 = b0;

        prim->r1 = r0;
        prim->g1 = g0;
        prim->b1 = b0;

        prim->r2 = r1;
        prim->g2 = g1;
        prim->b2 = b1;

        prim->r3 = r1;
        prim->g3 = g1;
        prim->b3 = b1;
        prim->priority = menu->otIdx;
        prim->drawMode = DRAW_UNK_400 | DRAW_MENU;

        // draw the white window border
        MenuDrawLine(cx, cy, cx, cy + ch - 1, i + 1);
        MenuDrawLine(cx, cy, cx + cw - 1, cy, i + 1);
        MenuDrawLine(cx + cw - 1, cy, cx + cw - 1, cy + ch - 1, i + 1);
        MenuDrawLine(cx, cy + ch - 1, cx + cw - 1, cy + ch - 1, i + 1);

        switch (i) {
        case MENU_DG_MAIN:
            func_800F6568(menu);
            func_800F8754(menu, x, y);
            break;
        case MENU_DG_BG:
            MenuDrawStats(1);
            break;
        case MENU_DG_EQUIP_OVERVIEW:
            MenuDrawStats(2);
            equipIndex = g_Status.equipment[LEFT_HAND_SLOT];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 30, menu);
            DrawConsumableCount(equipIndex, LEFT_HAND_SLOT, menu);
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x10);

            equipIndex = g_Status.equipment[RIGHT_HAND_SLOT];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 43, menu);
            DrawConsumableCount(equipIndex, RIGHT_HAND_SLOT, menu);
            flag = equip->itemCategory == 5;
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x11);

            for (j = 0; j < 5; j++) {
                acc = &g_AccessoryDefs[g_Status.equipment[j + 2]];
                MenuDrawStr(acc->name, 112, 56 + j * 13, menu);
                LoadEquipIcon(acc->icon, acc->iconPalette, j + 0x12);
            }

            for (j = 0; j < 7; j++) {
                // Equivalent (but not matching) with (j==0 || j==1) && flag
                if (!(j != 0 && j != 1) && flag) {
                    if (j == 0) {
                        func_800F892C(j + 0x10, 0x5E, 0x20 + j * 13, menu);
                    }
                } else {
                    func_800F892C(j + 0x10, 0x5E, 0x1a + j * 13, menu);
                }
            }
            func_800F6618(i, g_MenuStep != 0x40);
            break;
        case MENU_DG_EQUIP_SELECTOR:
            func_800F8990(menu, x, y);
            MenuStatChangesDraw();
            break;
        case MENU_DG_INFO_BAR:
            func_800F5AE4(menu);
            break;
        case MENU_DG_RELICS:
            DrawRelicsMenu(menu);
            break;
        case MENU_DG_SPELLS:
            MenuSpellsDraw(menu);
            break;
        case MENU_DG_SETTINGS:
            MenuSystemDraw(menu);
            break;
        case MENU_DG_CLOAK_COLOR:
            MenuDrawAlucardCloakPreview(menu);
            MenuJosephsCloakDraw(menu);
            break;
        case MENU_DG_CFG_BUTTONS:
            MenuButtonConfigDraw(menu);
            break;
        case MENU_DG_CLOAK_LINING:
            MenuReverseCloakDraw(menu);
            break;
        case MENU_DG_CFG_SOUND:
            MenuSoundConfigDraw(menu);
            break;
        case MENU_DG_WINDOW_COLORS:
            MenuWindowColorsDraw(menu);
            break;
        case MENU_DG_TIME_ATTACK:
            MenuTimeAttackDraw(menu);
            break;
        case MENU_DG_EQUIP_SORT:
            MenuEquipSortDraw(menu);
            break;
        case MENU_DG_FAMILIARS:
            MenuFamiliarsDraw(menu);
            break;
        case MENU_PSP_EXTRA_1:
        case MENU_PSP_EXTRA_3:
            func_psp_090ED9E0(menu);
            break;
        case MENU_PSP_EXTRA_2:
            func_psp_090EDA78(menu);
            break;
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F9690);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F96F4);

extern u8* D_8013794C;
extern s32 D_80137950;
extern s32 D_80137954;

void func_800F97DC(void) {
    D_8013794C = g_Pix[0];
    D_80137950 = 0x180;
    D_80137954 = 0;
}
INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F9808);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F98AC);

void func_800F99B8(char* str, s32 arg1, s32 arg2) {
    // See src/st/blit_char.h
    const u16 DOUBLE_SPACE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    char sp5f;
    s32 sp54;
    s32 sp50;
    s32 sp4c;
    s32 sp48;
    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s2;
    s32 var_s1;
    s32 var_s0;
    s32 i;
    s32 j;
    u8* dest_addr;

    if (arg2) {
        var_s0 = 0x3C;
    } else {
        var_s0 = 0x90;
    }
    for (i = 0, sp4c = var_s0 * FontHeight; i < sp4c; i++) {
        D_8013794C[i] = 0;
    }
    var_s1 = 0;
    sp50 = 0;
    if (arg1 & 0x100) {
        sp50 = 0x40;
    }
    if (arg1 & 0x200) {
        sp50 += 0x20;
        arg1 &= ~0x200;
    }
    sp48 = func_800F548C(arg1 & 0xFF) & 0xFF;
    while (*str != 0) {
        sp54 = 0;
        var_a0 = func_psp_0913F960(str, &sp5f);
        var_s2 = *str++;
        if ('a' <= var_s2 && var_s2 <= 'z') {
            var_a0 = var_s2 + 0x8220;
        } else if ('A' <= var_s2 && var_s2 <= 'Z') {
            var_a0 = var_s2 + 0x821F;
        } else if (var_s2 == ' ') {
            var_a0 = DOUBLE_SPACE;
            sp54 = 2;
        } else {
            sp54 = sp5f;
            if (sp5f > 1) {
                str += (sp5f - 1);
            }
            if (var_a0 == DOUBLE_SPACE) {
                var_s2 = ' ';
            }
        }
        // var_a2 = (u8*)func_80106A28(var_a0, 0);
        var_a2 = (u8*)func_psp_0913FA28(var_a0, 0);
        while (1) {
            if (var_s2 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontWidth / 2] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontWidth / 2];
                // Effectively shift everything down an index
                for (j = 0; j < 5; j++) {
                    dest_addr[0] = dest_addr[1];
                    dest_addr += 1;
                }
                // Set last index to 0
                *dest_addr = 0;
            }
        }
        for (i = 0, var_a3 = 0; i < FontHeight; i++) {
            for (j = 0; j < FontWidth / 2; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontWidth / 2 + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (var_a2[i * FontWidth / 2 + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontWidth / 2) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_8013794C[(i * var_s0) + var_s1];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s1 += var_a3 + sp54;
        if (var_s1 >= var_s0) {
            break;
        }
    }

    LoadTPage((u_long*)D_8013794C, 0, 0, D_80137950 + sp50, D_80137954 + sp48,
              var_s0 * 2, 0x10);
    D_8013794C += sp4c;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F0DD8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F0E10);

extern u8* D_psp_0914A394;
extern s32 D_psp_0914A0D0;
extern s32 D_psp_09149E90;
extern s32 D_psp_0914A248;
extern s32 D_psp_09149FB0;
extern s32 D_psp_0914A388;

RECT D_800A2D90 = {0x180, 0x30, 0x80, 0x80};

void func_800F9E18(s32 arg0) {
    char buffer[38];
    const int ItemsPerRow = 2;
    s32 i = arg0 * 5;
    s32 nHalfScreenSize;
    s32 nItems = i + 5;

    if (arg0 == 0) {
        ClearImage(&D_800A2D90, 0, 0, 0);
        DrawSync(0);
    }

    D_psp_0914A394 = func_psp_090EAF08(0, &D_psp_0914A0D0, &D_psp_09149E90, &D_psp_0914A248, &D_psp_09149FB0);
    if (D_psp_0914A394) {
        func_psp_091040A0(&D_psp_0914A388);
    }

    for (nHalfScreenSize = i; i < nItems; i++, nHalfScreenSize++) {
        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 128, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 259, 1);
        }

        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow + 1].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 640, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 771, 1);
        }
    }
}
INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F9F40);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuHandleCursorInput);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F1418);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuEquipHandlePageScroll);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", CheckWeaponCombo);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F18B0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F1968);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", InitWeapon);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAB1C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuHide);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuShow);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FABEC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAC0C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAC30);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAC48);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F1CE0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F1CE8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAD34);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FADC0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F1EA0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAEC4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FAF44);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FB004);

typedef struct EquipMenuHelper {
    s32 equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

extern EquipMenuHelper g_EquipMenuHelper[];

extern EquipKind D_801375CC;
extern s32 D_801375D4;

void func_800FB0FC(void) {
    EquipMenuHelper* helper = &g_EquipMenuHelper[g_MenuNavigation.cursorEquip];
    D_801375CC = helper->equipTypeFilter;
    D_801375D4 = helper->index;
    func_800FAF44(helper->isAccessory);
    func_800FB004();
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F2178);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F21F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FB23C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FB9BC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800FBAC4);

void func_800FAEC4(s32* cursor_unused, u16 count, const char* str, u16 icon, u16 pal);
void func_800FAD34(const char* str, u8 count, u16 equipIcon, u16 palette);
s32 func_800FB23C(s32* nav, u8* order, u8* count, u32* selected);
extern s32 D_80137614;
void MenuHandleCursorInput(s32* nav, u8 nOptions, u32 arg2);
extern s32 g_ServantPrevious;
s32 D_801375DC;
s32 D_801375E0[NUM_FAMILIARS + 1];
extern s32 g_IsCloakLiningUnlocked;
extern s32 g_IsCloakColorUnlocked;
extern s32 D_80137958;
const char* D_800A2D64[];
char** D_800A2D48;
extern s32 D_80137608;
extern s32 g_IsSelectingEquipment;
extern MenuData g_MenuData;
extern s32 D_80137948;
s32 g_EquipOrderType;
s32 D_80137844[1];
s32 D_80137848[1];
s32 D_801375D0;
s32* D_801375D8;
extern bool D_psp_091CDD48;
extern s32 D_8B42058;
extern s32 D_psp_091CDD40;

extern u32 D_psp_08B42050; // psp cross button
extern u32 D_psp_08B42054; // psp triangle button

#define PAD_MENU_SELECT_ALT (D_psp_08B42050)
#define PAD_MENU_SELECT (PAD_MENU_SELECT_ALT | PAD_SQUARE)
#define PAD_MENU_BACK (D_psp_08B42054)
#define PAD_MENU_SORT (PAD_SQUARE)
#define PAD_MENU_BACK_ALT (PAD_MENU_BACK | PAD_MENU_SELECT)

#define ShowText(str, id) func_800F99B8(str, id, 0);

s32 D_8013784C;
typedef enum {
    ENGINE_INIT_SERVANT_0 = 0,
    MENU_SWITCH_SERVANT,
    ENGINE_INIT_SERVANT_2,
    MENU_SAME_SERVANT
} InitializeMode;

extern const char* D_800A2D10[];
extern const char* D_800A2D14[];
extern const char* D_800A2D18[];
extern const char* D_800A2D58[];


void MenuHandle(void) {
    s32 temp_s1;
    s32 i;
    s32 id;
    s32 var_s1;
    u8 equipId;
    s32 isSecondAccessory;
    char* buttonAssignStr;

    D_80137614 = 1;
    func_800F97DC();
    if (g_MenuStep >= MENU_STEP_OPENED && g_pads[0].tapped & PAD_START) {
        if (CheckIfAllButtonsAreAssigned()) {
            g_MenuStep = MENU_STEP_EXIT_BEGIN;
        } else {
            goto block_117;
        }
    }
block_4:
    switch (g_MenuStep) {
    case MENU_STEP_INIT:
        if (!CdSoundCommandQueueEmpty()) {
            break;
        }
        func_psp_090EAFA8();
        PlaySfx(SET_UNK_10);
        func_800EA5E4(0);
        func_800FAC30();
        func_800FB9BC();
        g_PrevEquippedWeapons[LEFT_HAND_SLOT] =
            g_Status.equipment[LEFT_HAND_SLOT];
        g_PrevEquippedWeapons[RIGHT_HAND_SLOT] =
            g_Status.equipment[RIGHT_HAND_SLOT];
        if (g_Status.wornEquipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
            g_PrevEquippedWeapons[LEFT_HAND_SLOT] = 0xD8;
            g_PrevEquippedWeapons[RIGHT_HAND_SLOT] = 0xD8;
        }
        g_ServantPrevious = g_Servant;
        for (i = 0; i < NUM_SPELLS; i++) {
            if (!(g_Status.spells[i] & SPELL_FLAG_KNOWN)) {
                break;
            }
        }
        D_801375DC = i;
        for (i = 0; i < LEN(D_801375E0); i++) {
            D_801375E0[i] = 0;
        }
        for (i = 0; i < NUM_RELICS; i++) {
            if (!(g_Status.relics[i] & RELIC_FLAG_FOUND)) {
                continue;
            }
            if (g_RelicDefs[i].unk0C == 0) {
                continue;
            }
            D_801375E0[g_RelicDefs[i].unk0C - 1] = 1;
            D_801375E0[NUM_FAMILIARS] = 1;
        }
        g_IsCloakLiningUnlocked =
            g_Status.equipBodyCount[ITEM_REVERSE_CLOAK] |
            g_Status.wornEquipment[CAPE_SLOT] == ITEM_REVERSE_CLOAK;
        g_IsCloakColorUnlocked =
            g_Status.equipBodyCount[ITEM_JOSEPHS_CLOAK] |
            g_Status.wornEquipment[CAPE_SLOT] == ITEM_JOSEPHS_CLOAK;
        g_MenuStep++;
        break;
    case MENU_STEP_FADE_FROM_GAME:
        if (func_801025F4() == 0) {
            break;
        }
        SetGPUBuffRGBZero();
        func_80102628(0x180);
        SetMenuDisplayBuffer();
        func_800FAC48();
        D_800973EC = 1;
        g_MenuStep++;
        break;
    case MENU_STEP_OPENING:
        if (func_80133950()) {
            D_80137958 = D_80097910;
            D_80097910 = 0;
            func_800F6A48();
            func_800F84CC();
            func_801027C4(2);
            func_800F98AC(*D_800A2D10, 0);
            func_800F98AC(*D_800A2D14, 0x100);
            func_800F98AC(*D_800A2D18, 1);
            func_800F98AC(*D_800A2D18, 0x101);
            func_800FABEC(MENU_DG_MAIN);
            func_800FABEC(MENU_DG_BG);
            D_80137608 = 0;
            g_IsSelectingEquipment = 0;
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_EXIT_BEGIN:
        func_801027C4(1);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_4:
        if (func_801025F4()) {
            func_80102628(0x100);
            SetStageDisplayBuffer();
            func_800FAC48();
            func_800EB6B4();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_5:
        UpdateCapePalette();
        LoadGfxAsync(D_80097904);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_6:
        if (func_800EB720()) {
            break;
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_7:
        if(!func_psp_090F1968(LEFT_HAND_SLOT)){
            break;
        }
        if (!g_UseDisk) {
            InitWeapon(LEFT_HAND_SLOT);
        }
        if(g_UseDisk){
            if(g_IsUsingCd) {
                break;
            }
            InitWeapon(LEFT_HAND_SLOT);
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_8:
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_9:
        if(!func_psp_090F1968(RIGHT_HAND_SLOT)){
            break;
        }
        if (!g_UseDisk) {
            InitWeapon(RIGHT_HAND_SLOT);
        }
        if(g_UseDisk){
            if(g_IsUsingCd) {
                break;
            }
            InitWeapon(RIGHT_HAND_SLOT);
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_10:
        if (g_Servant == FAM_ACTIVE_NONE || g_Servant != g_ServantPrevious) {
            func_800FAB1C();
        }
        if (g_Servant == FAM_ACTIVE_NONE || g_Servant == g_ServantLoaded) {
            if(g_Servant != FAM_ACTIVE_NONE){
                if (g_Servant != g_ServantPrevious) {
                    if (g_Status.statsFamiliars[g_Servant - 1].unk8 < 9999) {
                        g_Status.statsFamiliars[g_Servant - 1].unk8++;
                    }
                    InitializeServant(MENU_SWITCH_SERVANT);
                } else {
                    InitializeServant(MENU_SAME_SERVANT);
                }
            }
            g_MenuStep += 2;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_ServantChr;
                g_LoadOvlIdx = g_Servant - 1;
            }
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_11:
        if (func_8932EA4()) {
            if (g_UseDisk){
                if(g_IsUsingCd) {
                    break;
                }
            } else {        
                func_800E6250();
            }
            InitializeServant(MENU_SWITCH_SERVANT);
            g_ServantLoaded = g_Servant;
            if (g_Status.statsFamiliars[g_Servant - 1].unk8 < 9999) {
                g_Status.statsFamiliars[g_Servant - 1].unk8++;
            }
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_12:
        if (g_IsUsingCd) {
            break;
        }
        if (CdSoundCommandQueueEmpty() == false) {
            break;
        }
        D_80097910 = D_80137958;
        if (D_80097928 != 0) {
            PlaySfx(0xB);
        } else {
            PlaySfx(SET_UNK_11);
        }
        CheckWeaponCombo();
        func_800F53A4();
        D_800973EC = 0;
        func_800FAC30();
        func_800F86E4();
        func_8010A234(1);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_13:
        if (func_80133950() == false) {
            break;
        }
        func_801027C4(2);
        g_MenuStep++;
        if(D_psp_091CDD48){
            D_psp_091CDD48 = 0;
            SetGameState(3);
            g_GameStep = 0x63;
        }
        break;
    case MENU_STEP_RETURN_TO_GAMEPLAY:
        if (func_801025F4() == 0) {
            break;
        }
        PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
        PlaySfx(SET_KEY_ON_20_21);
        PlaySfx(SET_KEY_ON_22_23);
        g_GameEngineStep = Engine_Normal;
        break;
    case MENU_STEP_OPENED:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            g_MenuStep = MENU_STEP_EXIT_BEGIN;
            goto block_4;
        }
        MenuHandleCursorInput(&g_MenuNavigation.cursorMain, 7, 0);
        if (g_pads[0].tapped & PAD_MENU_SELECT) {
            switch (g_MenuNavigation.cursorMain) {
            case 0:
                MenuShow(MENU_DG_EQUIP_OVERVIEW);
                func_800FB0FC();
                func_800FADC0();
                MenuShow(MENU_DG_EQUIP_SELECTOR);
                MenuShow(MENU_DG_INFO_BAR);
                g_MenuStep = MENU_STEP_EQUIP;
                break;
            case 1:
                if (D_801375DC) {
                    g_MenuStep = MENU_STEP_SPELL_INIT;
                }
                break;
            case 2:
                func_800F9E18(0);
                g_MenuStep = MENU_STEP_RELIC_INIT;
                break;
            case 3:
                g_MenuStep = MENU_STEP_SYSTEM_INIT;
                break;
            case 4:
                if (D_801375E0[NUM_FAMILIARS]) {
                    g_MenuStep = MENU_STEP_FAMILIAR_INIT;
                }
                break;
            case 5:
                if(D_8006C378 < 0){
                    break;
                }
                MenuShow(0x10);
                D_psp_091CDD40 = 1;
                g_MenuStep = 0x80;
                break;
            case 6:
                MenuShow(0x10);
                D_psp_091CDD40 = 1;
                g_MenuStep = 0x90;
                break;
            }
            if (!(g_MenuStep == MENU_STEP_OPENED || g_MenuStep == 0x80 || g_MenuStep == 0x90)) {
                MenuHide(MENU_DG_MAIN);
                MenuHide(MENU_DG_BG);
                PlaySfx(SFX_UI_CONFIRM);
            } else {
                if(g_MenuStep == 0x80 || g_MenuStep == 0x90){
                    PlaySfx(SFX_UI_CONFIRM);
                } else {
                    PlaySfx(SFX_UI_ERROR);
                }
            }
        }
        break;
    case 0x80:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            PlaySfx(SFX_UI_ERROR);
            MenuHide(0x10);
            g_MenuStep = 0x10;
            break;
        }
        MenuHandleCursorInput(&D_psp_091CDD40, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_SELECT)) {
            break;
        }
        if(D_psp_091CDD40 == 0){
            PlaySfx(SFX_UI_CONFIRM);
            func_psp_090DFC80();
            MenuHide(0x10);
            D_psp_091CDD48 = 1;
            g_MenuStep = 3;
            goto block_4;
        }
        PlaySfx(SFX_UI_ERROR);
        MenuHide(0x10);
        g_MenuStep = 0x10;
        break;
    case 0x90:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            PlaySfx(SFX_UI_ERROR);
            MenuHide(0x10);
            g_MenuStep = 0x10;
            break;
        }
        MenuHandleCursorInput(&D_psp_091CDD40, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_SELECT)) {
            break;
        }
        if(D_psp_091CDD40 == 0){
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(0x10);
            D_psp_091CDD48 = 1;
            g_MenuStep = 3;
            goto block_4;
        }
        PlaySfx(SFX_UI_ERROR);
        MenuHide(0x10);
        g_MenuStep = 0x10;
        break;
    case MENU_STEP_FAMILIAR_INIT:
        func_800EA5E4(0x21);
        func_800EAEA4();
        MenuShow(MENU_DG_FAMILIARS);
        g_MenuStep++;
        break;
    case MENU_STEP_FAMILIAR:
        if (g_pads[0].tapped & (PAD_MENU_SELECT | PAD_MENU_BACK)) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            func_800EAEA4();
            MenuHide(MENU_DG_FAMILIARS);
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_SYSTEM_INIT:
        func_800F82F4();
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_SETTINGS);
        g_MenuStep++;
    case MENU_STEP_SYSTEM:
        MenuHandleCursorInput(&g_MenuNavigation.cursorSettings, 5, 0);
        DrawSync(0);
        func_800F9808(2);
        i = g_MenuNavigation.cursorSettings + 1;
        if (i == 2 && g_IsCloakLiningUnlocked == false) {
            i = 0;
        }
        if (i == 3 && g_IsCloakColorUnlocked == false) {
            i = 0;
        }
        if (i == 5 && g_IsTimeAttackUnlocked == false) {
            i = 0;
        }
        ShowText(D_800A2D48[i], 2);
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_SETTINGS);
            g_MenuStep = MENU_STEP_OPENED;
        } else if (g_pads[0].tapped & PAD_MENU_SELECT) {
            switch (g_MenuNavigation.cursorSettings) {
            case 0:
                MenuShow(MENU_DG_CFG_BUTTONS);
                g_MenuStep = MENU_STEP_SYSTEM_BUTTONS;
                break;
            case 1:
                if (g_IsCloakLiningUnlocked) {
                    MenuShow(MENU_DG_CLOAK_LINING);
                    g_MenuStep = MENU_STEP_SYSTEM_CLOAK_LINING;
                }
                break;
            case 2:
                if (g_IsCloakColorUnlocked) {
                    func_800FABEC(MENU_DG_CLOAK_COLOR);
                    g_MenuStep = MENU_STEP_SYSTEM_CLOAK_COLOR;
                }
                break;
            case 3:
                MenuShow(MENU_DG_WINDOW_COLORS);
                g_MenuStep = MENU_STEP_SYSTEM_WINDOW_COLOR;
                break;
            case 4:
                if (g_IsTimeAttackUnlocked) {
                    SortTimeAttackEntries();
                    MenuShow(MENU_DG_TIME_ATTACK);
                    g_MenuStep = MENU_STEP_SYSTEM_TIME_ATTACK;
                }            
            }
            
            if (g_MenuStep != MENU_STEP_SYSTEM) {
                PlaySfx(SFX_UI_CONFIRM);
            } else {
                PlaySfx(SFX_UI_ERROR);
            }
        }
        break;
    case MENU_STEP_SYSTEM_BUTTONS:
        MenuHandleCursorInput(&g_MenuNavigation.cursorButtons, 6, 0);
        MenuHandleCursorInput(
            &g_Settings.buttonConfig[g_MenuNavigation.cursorButtons], 6, 5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            if (CheckIfAllButtonsAreAssigned()) {
                PlaySfx(SFX_UI_CONFIRM);
                MenuHide(MENU_DG_CFG_BUTTONS);
                g_MenuStep = MENU_STEP_SYSTEM;
            } else {
            block_117:
                func_800F9808(2);
                switch(D_8B42058){
                    default:
                    case LANG_EN:
                        buttonAssignStr = "ENG_STR";
                        break;
                    case LANG_FR:
                        buttonAssignStr = "FR_STR";
                        break;
                    case LANG_SP:
                        buttonAssignStr = "SP_STR";
                        break;
                    case LANG_GE:
                        buttonAssignStr = "GE_STR";
                        break;
                    case LANG_IT:
                        buttonAssignStr = "IT_STR";
                        break;
                }
                ShowText(buttonAssignStr, 2);
                PlaySfx(SFX_UI_ERROR);
            }
        }
        break;
    case MENU_STEP_SYSTEM_CLOAK_LINING:
        MenuHandleCursorInput(&g_Settings.isCloakLiningReversed, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_BACK_ALT)) {
            break;
        }
        PlaySfx(SFX_UI_CONFIRM);
        MenuHide(MENU_DG_CLOAK_LINING);
        g_MenuStep = MENU_STEP_SYSTEM;
        break;
    case MENU_STEP_SYSTEM_CLOAK_COLOR:
        MenuHandleCursorInput(&g_MenuNavigation.cursorCloak, 6, 0);
        MenuHandleCursorInput(
            &g_Settings.cloakColors[g_MenuNavigation.cursorCloak], 32, 5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            func_800FAC0C(MENU_DG_CLOAK_COLOR);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_WINDOW_COLOR:
        MenuHandleCursorInput(&g_MenuNavigation.cursorWindowColors, 3, 0);
        MenuHandleCursorInput(
            &g_Settings.windowColors[g_MenuNavigation.cursorWindowColors], 16,
            5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_WINDOW_COLORS);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_SOUND:
        MenuHandleCursorInput(&g_Settings.isSoundMono, 2, 0);
        func_800E493C();
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_CFG_SOUND);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_TIME_ATTACK:
        MenuHandleCursorInput(&g_MenuNavigation.cursorTimeAttack, 0x10, 3);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_TIME_ATTACK);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_RELIC_INIT:
        func_800F9E18(1);
        g_MenuStep++;
        break;
    case MENU_STEP_RELIC_INIT_2:
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_RELICS);
        func_800F9808(2);
        id = g_MenuNavigation.cursorRelic;
        if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
            ShowText(g_RelicDefs[id].desc, 2);
        }
        func_800F9E18(2);
        g_MenuStep++;
        break;
    case MENU_STEP_RELIC:
        g_MenuData.menus[5].unk16 = (((g_MenuNavigation.cursorRelic / 2) * -140)) / 15;
        var_s1 = g_MenuNavigation.cursorRelic;
        MenuHandleCursorInput(
            &g_MenuNavigation.cursorRelic, NUM_AVAIL_RELICS, 1);
        id = g_MenuNavigation.cursorRelic;
        if (g_pads[0].tapped & PAD_MENU_SELECT && g_Status.relics[id] & RELIC_FLAG_FOUND) {
            PlaySfx(SFX_UI_CONFIRM);
            g_Status.relics[id] = g_Status.relics[id] ^ 2;
            if (g_RelicDefs[id].unk0C > 0) {
                for (i = 0; i < NUM_RELICS; i++) {
                    if (i == id) {
                        continue;
                    }
                    if (g_RelicDefs[i].unk0C <= 0) {
                        continue;
                    }
                    g_Status.relics[i] &= ~RELIC_FLAG_ACTIVE;
                }

                if (g_Status.relics[id] & RELIC_FLAG_ACTIVE) {
                    i = ITEM_SWORD_FAMILIAR;
                    g_Servant = g_RelicDefs[id].unk0C;
                    func_8932E78(g_Servant - 1);
                    if (g_Servant == FAM_ACTIVE_SWORD) {
                        if (g_Status.equipment[LEFT_HAND_SLOT] == i) {
                            g_Status.equipment[LEFT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(i, 0);
                        }
                        if (g_Status.equipment[RIGHT_HAND_SLOT] == i) {
                            g_Status.equipment[RIGHT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(i, 0);
                        }
                    }
                } else {
                    g_Servant = FAM_ACTIVE_NONE;
                }
            }
        }
        if (var_s1 != id) {
            func_800F9808(2);
            if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
                ShowText(g_RelicDefs[id].desc, 2);
            }
        }

        D_80137608 = 0;
        if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
            D_80137608 = 1;
            LoadEquipIcon(g_RelicDefs[id].unk08, g_RelicDefs[id].unk0A, 0x1F);
        }
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_RELICS);
            D_80137608 = 0;
            g_MenuStep = MENU_STEP_OPENED;
        }

        break;
    case MENU_STEP_SPELL_INIT:
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_SPELLS);
        func_800F9808(2);
        func_800F9F40();
        g_MenuStep++;
        break;
    case MENU_STEP_SPELL:
        temp_s1 = g_MenuNavigation.cursorSpells;
        MenuHandleCursorInput(&g_MenuNavigation.cursorSpells, D_801375DC, 3);
        if (1) {
            func_800F9808(2);
            id = g_Status.spells[g_MenuNavigation.cursorSpells];
            id ^= SPELL_FLAG_KNOWN;
            ShowText(g_SpellDefs[id].description, 2);
        }
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_SPELLS);
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_UNK_32:
        if (func_801025F4()) {
            func_80102628(0x100);
            SetStageDisplayBuffer();
            func_800FAC48();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_33:
        if (!g_IsUsingCd) {
            g_GpuBuffers[1].draw.isbg = 0;
            g_GpuBuffers[0].draw.isbg = 0;
            func_801083BC();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_34:
        func_800F5A90();
        g_MenuStep++;
        break;
    case MENU_STEP_UNK_35:
        func_800F5A90();
        if (g_pads[0].tapped & (PAD_MENU_SELECT | PAD_MENU_BACK)) {
            func_801073C0();
            g_CdStep = CdStep_None;
            SetGPUBuffRGBZero();
            func_80102628(0x180);
            SetMenuDisplayBuffer();
            func_800FAC48();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_36:
        func_801027C4(2);
        func_800F9808(2);
        id = g_Status.spells[g_MenuNavigation.cursorSpells];
        id ^= SPELL_FLAG_KNOWN;
        ShowText(g_SpellDefs[id].description, 2);
        func_800F9F40();
        g_MenuStep++;
        break;
    case MENU_STEP_UNK_37:
        if (func_801025F4() == 0) {
            break;
        }
        g_MenuStep = MENU_STEP_SPELL;
        break;
    case MENU_STEP_EQUIP:
        D_80137948 = 0;
        func_800FB0FC();
        var_s1 = g_MenuNavigation.cursorEquip;
        MenuHandleCursorInput(&g_MenuNavigation.cursorEquip, NUM_ITEM_SLOTS, 0);
        MenuEquipHandlePageScroll(1);
        func_800FB0FC();
        if (var_s1 != g_MenuNavigation.cursorEquip) {
            func_800FADC0();
        }
        if (g_pads[0].tapped & PAD_MENU_SORT && D_801375CC == 0) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuShow(MENU_DG_EQUIP_SORT);
            g_MenuStep = MENU_STEP_EQUIP_SORT;
            g_EquipOrderType = 0;
        } else if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuHide(MENU_DG_EQUIP_OVERVIEW);
            MenuHide(MENU_DG_EQUIP_SELECTOR);
            MenuHide(MENU_DG_INFO_BAR);
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            *D_80137844 = 0;
            *D_80137848 = 0;
            D_80137608 = 0;
            g_MenuStep = MENU_STEP_OPENED;
        } else if (g_pads[0].tapped & PAD_MENU_SELECT) {
            PlaySfx(SFX_UI_CONFIRM);
        block_191:
            func_800FB0FC();
            if (g_MenuNavigation.cursorEquip < HEAD_SLOT) {
                g_MenuStep = MENU_STEP_EQUIP_HAND_INIT;
            } else {
                g_MenuStep = MENU_STEP_EQUIP_ACC_INIT;
            }
        }
        break;
    case MENU_STEP_EQUIP_SORT:
        func_800FB0FC();
        MenuHandleCursorInput(&g_EquipOrderType, 11, 0);
        MenuEquipHandlePageScroll(0);
        if (g_pads[0].tapped & PAD_MENU_SELECT_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            func_800FBAC4();
            g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 = 0;
            g_MenuNavigation.cursorEquipType[0] = 0;
            func_800FB0FC();
        } else if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuHide(MENU_DG_EQUIP_SORT);
            g_MenuStep = MENU_STEP_EQUIP;
        }
        break;
    case MENU_STEP_EQUIP_HAND_INIT:
        equipId = g_Status.equipHandOrder[g_MenuNavigation.cursorEquipType[0]];
        func_800FAEC4(
            &g_MenuNavigation.cursorEquipType[0],
            g_Status.equipHandCount[equipId], g_EquipDefs[equipId].description,
            g_EquipDefs[equipId].icon, g_EquipDefs[equipId].iconPalette);
        func_800FAF44(0);
    case MENU_STEP_EQUIP_HAND:
        if (g_MenuNavigation.cursorEquip == LEFT_HAND_SLOT) {
            D_801375D0 = LEFT_HAND_SLOT;
        } else {
            D_801375D0 = RIGHT_HAND_SLOT;
        }
        i = func_800FB23C(
            &g_MenuNavigation.cursorEquipType[0], 
            g_Status.equipHandOrder,
            g_Status.equipHandCount, 
            &g_Status.equipment[D_801375D0]);
        if (i == 2) {
            equipId =
                g_Status.equipHandOrder[g_MenuNavigation.cursorEquipType[0]];
            func_800FAD34(
                g_EquipDefs[equipId].description,
                g_Status.equipHandCount[equipId], g_EquipDefs[equipId].icon,
                g_EquipDefs[equipId].iconPalette);
        } else if (i == 1) {
            goto block_191;
        }
        break;
    case MENU_STEP_EQUIP_ACC_INIT:
        equipId = g_Status.equipBodyOrder[D_801375D8[g_MenuNavigation.cursorEquipType[D_801375D4]]];
        func_800FAEC4(
            &g_MenuNavigation.cursorEquipType[D_801375D4],
            g_Status.equipBodyCount[equipId],
            g_AccessoryDefs[equipId].description, g_AccessoryDefs[equipId].icon,
            g_AccessoryDefs[equipId].iconPalette);
        func_800FAF44(1);
    case MENU_STEP_EQUIP_ACC:
      isSecondAccessory = g_MenuNavigation.cursorEquip;
      isSecondAccessory = (isSecondAccessory == ACCESSORY_2_SLOT);
        i = func_800FB23C(
            &g_MenuNavigation.cursorEquipType[D_801375D4],
            g_Status.equipBodyOrder, 
            g_Status.equipBodyCount,
            &g_Status.wornEquipment[D_801375D4 + isSecondAccessory]);
        if (i == 2) {
            equipId = g_Status.equipBodyOrder[D_801375D8[g_MenuNavigation.cursorEquipType[1 + D_801375D4]]];
            func_800FAD34(
                g_AccessoryDefs[equipId].description,
                g_Status.equipBodyCount[equipId], g_AccessoryDefs[equipId].icon,
                g_AccessoryDefs[equipId].iconPalette);
        } else if (i == 1) {
            goto block_191;
        }
        break;
    }
    if (g_MenuStep >= MENU_STEP_OPENED ||
        g_MenuStep == MENU_STEP_EXIT_BEGIN || g_MenuStep == MENU_STEP_EXIT_4) {
        MenuDraw();
        func_800F9690();
        func_800F96F4();
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", DrawHudSubweapon2);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F4FC8);