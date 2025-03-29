// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

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

INCLUDE_ASM("dra_psp/psp/dra_psp/13080", func_psp_090F01C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/13080", func_psp_090F0220);

INCLUDE_ASM("dra_psp/psp/dra_psp/13080", func_psp_090F0308);

INCLUDE_ASM("dra_psp/psp/dra_psp/13080", func_psp_090F0330);
