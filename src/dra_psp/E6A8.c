// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

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

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EC380);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EC518);

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

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECCC0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECD58);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECD78);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawAlucardCloakPreview);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ECF20);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F6568);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F6618);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ED058);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawChar);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawStr);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawInt);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ED248);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ED2E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuJosephsCloakDraw);

extern s32 D_psp_0914A3B8;
extern s32 D_psp_0914A3D0;
extern s32 D_psp_0914A3C8;
extern s32 D_psp_0914A3D8;
extern s32 D_psp_0914A3C0;

extern u8* g_ChRgb[];

extern u8* func_psp_090EAF08(void*, void*, void*, void*, void*);

void MenuWindowColorsDraw(MenuContext* context) {
    s32 x = 188;
    s32 y;
    s32 i;

    *g_ChRgb = func_psp_090EAF08(&D_psp_0914A3B8, &D_psp_0914A3D0, &D_psp_0914A3C8, &D_psp_0914A3D8, &D_psp_0914A3C0);

    for (i = 0; i < 3; i++) {
        MenuDrawChar((*g_ChRgb)[i], x + 32, (i * 12) + 80, context);
        MenuDrawInt(g_Settings.windowColors[i], x + 72, 80 + i * 12, context);
    }
    func_800F5E68(
        context, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090ED570);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuTimeAttackDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuButtonConfigDraw);

void MenuReverseCloakDraw(MenuContext* context) {
    const int StrX = 188;
    const int ImgW = 88;
    char** menuStr;
    
    menuStr= g_MenuStr;
    MenuDrawStr(menuStr[30], StrX, 48, context);
    menuStr= g_MenuStr;
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

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawStats);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuSpellsDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuFamiliarsDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EEDF8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuSystemDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EEFA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090EF1A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F8754);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuEquipSortDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F892C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_800F8990);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", MenuDrawLine);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", DrawConsumableCount);

extern MenuData g_MenuData;
extern s32 D_801377FC[NUM_MENU];
extern u8 D_800A2D80[];

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
                // Not sure what's going on here. Should just be j==0 || j==1
                if (((j == 0) || (j == (0, 1))) && flag) {
                    if (j == 0) {
                        func_800F892C(j + 0x10, 0x5E, 0x20 + j * 13, menu);
                    }
                    continue;
                }
                func_800F892C(j + 0x10, 0x5E, 0x1a + j * 13, menu);
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

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F01C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F0220);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F0308);

INCLUDE_ASM("dra_psp/psp/dra_psp/E6A8", func_psp_090F0330);

