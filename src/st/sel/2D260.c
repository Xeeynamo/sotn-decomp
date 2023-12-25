#include "sel.h"
#include "memcard.h"

typedef enum {
    Tips_Generic,
    Tips_Input,
    Tips_YesNo,
    Tips_Confirm,
    Tips_MenuNavigation,
    Tips_NoYes,
} NavigationTips;

extern char g_AsciiSet[];

void DrawNavigationTips(NavigationTips mode) {
    u8** imgs;
    POLY_GT4* poly;

    func_801ACBE4(6, 8);
    imgs = &D_801803C4;
    poly = &g_PrimBuf[D_801BAF48];

    switch (mode) {
    case Tips_Generic:
        func_801B2670(poly, 32, 176, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 32, 208, 16, 16);
        poly->pad3 = 0;
        break;

    case Tips_Input:
        func_801B2670(poly, 288, 32, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 48, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 64, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 80, 16, 16);
        poly->pad3 = 0;
        break;

    case Tips_YesNo:
    case Tips_NoYes:
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        poly = (POLY_GT4*)poly->tag;
        func_801B2670(poly, 32, 208, 16, 16);
        poly->pad3 = 0;
        if (mode == Tips_YesNo) {
            func_801AD1D0();
        } else {
            func_801AD218();
        }
        break;

    case Tips_Confirm:
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        DrawImages8x8(*imgs, 52, 196, 1);
        break;

    case Tips_MenuNavigation:
        func_801B2670(poly, 32, 184, 16, 16);
        poly->pad3 = 0;
        poly = (POLY_GT4*)poly->tag;
        func_801B2670(poly, 32, 200, 16, 16);
        poly->pad3 = 0;
        break;
    }
}

void func_801AD490(void) {
    s32 i;

    DrawNavigationTips(Tips_MenuNavigation);
    DrawImages8x8(D_801803A8 /* "select" */, 52, 188, 1);
    DrawImages8x8(D_801803AC /* "start" */, 52, 204, 1);
    DrawString16x16("select", 240, 32, 1);
    DrawString16x16("your", 256, 48, 1);
    DrawString16x16("destiny", 232, 64, 1);

    for (i = 0; i < NUM_MENU_OPTIONS; i++) {
        POLY_GT4* poly = &g_PrimBuf[D_801BAF18[i + 1][0]];
        if (i == D_801D6B0C) {
            poly->clut = 0x203;
        } else {
            poly->clut = 0x200;
        }
    }
}

void func_801AD590(void) {
    if (g_pads[0].tapped & (PAD_RIGHT + PAD_DOWN)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (++D_801D6B0C == 5) {
            D_801D6B0C = 1;
        }
    }
    if (g_pads[0].tapped & (PAD_LEFT + PAD_UP)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (--D_801D6B0C == 0) {
            D_801D6B0C = 4;
        }
    }
    func_801B2608(D_80180454[D_801D6B0C], 9);
}

void func_801AD66C(void) {
    s32 i;
    s32 nSpaces;
    char* strRichter;

    // check if the name only contain spaces
    for (nSpaces = 0, i = 0; i < 8; i++) {
        g_SaveName[i] = g_InputSaveName[i];
        if (g_InputSaveName[i] == ' ') {
            nSpaces++;
        }
    }

    // if it only contain spaces, set a default name
    if (nSpaces == 8) {
        __builtin_memcpy(g_SaveName, D_801A7754, 9);
    }

    D_80097B98 = 0;
    D_80097B99 = 0;

    // check if the name is Richter
    for (strRichter = D_80180468, i = 0; i < 8; i++) {
        if (g_SaveName[i] != *strRichter++) {
            break;
        }
    }

    if (g_IsTimeAttackUnlocked != false) {
        g_IsTimeAttackUnlocked = 2;
    }

    // play as Richter only if the game was previously cleared
    if (i == 8 && g_IsTimeAttackUnlocked != false) {
        g_PlayableCharacter = PLAYER_RICHTER;
    } else {
        g_PlayableCharacter = PLAYER_ALUCARD;
    }
}

/* DATA */
extern u8* D_801803B0;
extern u8* D_801803B4;
/* RODATA */
extern const char* D_801A7760[]; // "a b c d e f g h"
extern const char* D_801A7770[]; // "i j k l m n o p"
extern const char* D_801A7780[]; // "q r s t u v w x"
extern const char* D_801A7790[]; // "y z & ! - . '  "
/* BSS */
extern s32 D_801BAF58;
extern s32 D_801BAF68;

void func_801AD78C(void) {
    DrawImages8x8(D_801803A8, 0x134, 0x24, 1);
    DrawImages8x8(D_801803B4, 0x134, 0x34, 1);
    DrawImages8x8(D_801803B0, 0x134, 0x44, 1);
    DrawImages8x8(D_801803AC, 0x134, 0x54, 1);
    DrawString16x16(D_801A7760, 0x48, 0x70, 1);
    DrawString16x16(D_801A7770, 0x48, 0x88, 1);
    DrawString16x16(D_801A7780, 0x48, 0xA0, 1);
    DrawString16x16(D_801A7790, 0x48, 0xB8, 1);
    func_801B26A0(&g_PrimBuf[D_801BAF58], (g_InputCursorPos * 0x10) + 0x80,
                  0x48, 0x0F, 0x0F, 0xF0, 0xF0);
    func_801B26A0(&g_PrimBuf[D_801BAF68], ((D_801BC3E0 & 7) << 5) + 0x40,
                  (D_801BC3E0 & 0x18) * 3 + 0x68, 0x20, 0x20, 0, 0x48);
    if (g_Timer & 8) {
        func_801ACBE4(8, 0);
    } else {
        func_801ACBE4(8, 8);
    }
    DrawString16x16(g_InputSaveName, 0x80, 0x48, 1);
}

void UpdateNameEntry(void) {
    if (g_pads[0].repeat & PAD_RIGHT) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 + 1) & 7);
    }

    if (g_pads[0].repeat & PAD_DOWN) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = ((D_801BC3E0 + 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].repeat & PAD_LEFT) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 - 1) & 7);
    }

    if (g_pads[0].repeat & PAD_UP) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = ((D_801BC3E0 - 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].tapped & (PAD_R1 + PAD_R2)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (++g_InputCursorPos == 8) {
            g_InputCursorPos = 0;
        }
    }

    if (g_pads[0].tapped & (PAD_L1 + PAD_L2)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (--g_InputCursorPos == -1) {
            g_InputCursorPos = 7;
        }
    }

    if (g_pads[0].tapped & PAD_CROSS) { // Input Character
        g_api.PlaySfx(0x8CD);
        g_InputSaveName[g_InputCursorPos] = g_AsciiSet[D_801BC3E0];
        if (++g_InputCursorPos == 8) {
            g_InputCursorPos = 0;
        }
    }

    if (g_pads[0].tapped & PAD_TRIANGLE) { // Backspace
        if (--g_InputCursorPos == -1) {
            g_InputCursorPos = 7;
        }
        g_InputSaveName[g_InputCursorPos] = ' ';
    }
}

void UpdateFileSelect(void) {
    if (g_SaveSummary[0].padding >= 0 || g_SaveSummary[1].padding >= 0) {
        if (g_pads[0].repeat & PAD_RIGHT) { // move selector to the right
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 1) % 6;
        }

        if (g_pads[0].repeat & PAD_DOWN) { // move selector down
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 4) % 5;
        }

        if (g_pads[0].repeat & PAD_LEFT) { // move selector to the left
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 5) % 6;
        }

        if (g_pads[0].repeat & PAD_UP) { // move selector up
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 1) % 5;
        }

        if (g_SaveSummary[0].padding > 0 && g_SaveSummary[1].padding > 0 &&
            (g_pads[0].tapped & (PAD_L2 + PAD_R2 + PAD_L1 + PAD_R1))) {
            g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 3) % 6;
        }

        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }

        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }

        D_801D6B04 = (g_MemCardSelectorX % 3) + (g_MemCardSelectorY * 3) +
                     ((g_MemCardSelectorX / 3) * 0xF);
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801ADF94);

void func_801AE6D0(void) {
    Primitive* prim;
    SaveSummary* s;
    s32 port;
    s32 slot;
    s32 percentage;
    s32 percentageDecimal;
    s32 level;

    port = D_801BC3EC / 15;
    slot = D_801BC3EC % 15;
    s = &g_SaveSummary[port];
    func_801ACBE4(0x12, 0x11);
    prim = g_PrimBuf[D_801BAF18[18][0]].next;
    func_801B26A0(prim, 168, (D_801BAF08 % 3) + 127, 48, 16, 0xB0, 0x80);
    prim->blendMode = 0;
    func_801ACBE4(0x13, 0);
    func_801ACBE4(0x14, 0);
    func_801ACFBC(port, slot, 10);
    PrintFileSelectPlaceName(port, slot, 72);

    level = (g_SaveSummary + port)->level[slot]; // FAKE
    func_801B2BD4(g_SaveSummary[port].level[slot], 148, 104, 1);
    func_801B2BD4(g_SaveSummary[port].playHours[slot], 200, 104, 1);
    func_801B2C70(g_SaveSummary[port].playMinutes[slot], 224, 104, 1);
    func_801B2C70(g_SaveSummary[port].playSeconds[slot], 248, 104, 1);
    func_801B2BD4(g_SaveSummary[port].gold[slot], 180, 112, 1);
    percentage = g_SaveSummary[port].nRoomsExplored[slot];
    percentage = percentage * 1000 / 942;
    percentageDecimal = percentage % 10;
    func_801B2BD4(percentage / 10, 232, 112, 1);
    func_801B27A8(240, 116, 8, 4, 0xE0, 0x8C, 0x200, 12, 1, 128);
    func_801B2BD4(percentageDecimal, 248, 112, 1);
}

extern s32 g_MenuHeadGfxU[];
extern s32 g_MenuHeadGfxV[];
void func_801AE9A8(void) {
    s32 i;

    MenuHideAllGfx();
    func_801ACBE4(0, 0);

    for (i = 1; i < NUM_MENU_OPTIONS; i++) {
        func_801ACBE4(i + 1, 4);
        func_801B26A0(
            &g_PrimBuf[D_801BAF18[i + 1][0]], (i * 64) - 32, (i * 5) * 8, 127,
            31, g_MenuHeadGfxU[i], g_MenuHeadGfxV[i]);
    }

    DrawNavigationTips(0);
    func_801ACBE4(0x11, 0);
}

void func_801AEA8C(s32 arg0) {
    g_InputCursorPos = 0;
    D_801BC3E0 = 0;
    MenuHideAllGfx();
    func_801ACBE4(7, 0x11);
    func_801ACBE4(8, 0);
    func_801ACBE4(9, 0x11);
    func_801ACBE4(10, 0);

    if (arg0 == 0) {
        func_801ACBE4(1, 0);
        func_801B2670(&g_PrimBuf[D_801BAF20], 24, 24, 127, 31);
    } else {
        func_801ACBE4(3, 0);
        func_801B2670(&g_PrimBuf[D_801BAF30], 24, 24, 127, 31);
    }

    DrawNavigationTips(1);
}

void SelectMainMenuOption(MainMenuCursor cursor) {
    Primitive* prim;
    s32 gfxId;

    g_SaveSummary[0].padding = 0;
    g_SaveSummary[1].padding = 0;
    MenuHideAllGfx();
    func_801ACBE4(GFX_WND_SAVE_SUMMARY, 0x11);
    func_801ACBE4(GFX_WND_CARD_1, 0x11);
    func_801ACBE4(GFX_WND_CARD_2, 0x11);
    func_801ACBE4(15, 0);

    switch (cursor) {
    case MAIN_MENU_CURSOR_FILE_SELECT:
        gfxId = GFX_FILE_SELECT;
        break;
    case MAIN_MENU_CURSOR_NAME_CHANGE:
        gfxId = GFX_NAME_CHANGE;
        break;
    case MAIN_MENU_CURSOR_FILE_COPY:
        gfxId = GFX_FILE_COPY;
        break;
    case MAIN_MENU_CURSOR_FILE_DELETE:
        gfxId = GFX_FILE_DELETE;
        break;
    }
    func_801ACBE4(gfxId, 0);

    // Relocate the graphics at the top-left of the screen
    prim = &g_PrimBuf[D_801BAF18[gfxId][0]];
    func_801B2670(prim, 16, 16, 127, 31);
    prim->clut = 0x200;
}

void func_801AECA0(void) {
    s32 i = 0;
    s32 x;
    s32 y = 256;
    s32 w = 16;
    s32 h = 48;
    s32 xnext = 384;
    u32* pix = g_saveIconTexture;

    for (; i < 16; i++) {
        s32 tmp = 4;
        x = xnext;
        xnext += tmp;
        LoadTPage(*pix++, 0, 0, x, y, w, tmp = 0x30);
        x = xnext;
    }

    g_api.func_800EA5E4(0x8004);
}

void CheckIfMemcardsCanBeUsed(void) {
    s32 isCard0Full;
    s32 isCard1Full;
    s32 i;

    isCard0Full = true;
    isCard1Full = true;
    for (i = 0; i < BLOCK_PER_CARD; i++) {
        if (g_SaveSummary[0].icon[i] != -2) {
            isCard0Full = false;
        }
        if (g_SaveSummary[1].icon[i] != -2) {
            isCard1Full = false;
        }
    }

    D_801BAF10 = 0;
    if ((g_SaveSummary[0].padding < 0 || isCard0Full) &&
        (g_SaveSummary[1].padding < 0 || isCard1Full)) {
        D_801BAF10 = 1;
    }

    D_801BAF14 = 0;
    for (i = 0; i < BLOCK_PER_CARD; i++) {
        if ((g_SaveSummary[0].padding > 0 && g_SaveSummary[0].icon[i] == -3) ||
            (g_SaveSummary[1].padding > 0 && g_SaveSummary[1].icon[i] == -3)) {
            break;
        }
    }
    if (i == BLOCK_PER_CARD) {
        D_801BAF14 = 1;
    }
}

void func_801AEE74(void) {
    s32 i = 0;
    SaveSummary* saveMenuInfo = g_SaveSummary;
    s32* iconsPort1 = saveMenuInfo[1].icon;
    s32* iconsPort0 = saveMenuInfo[0].icon;

    for (; i < BLOCK_PER_CARD; i++) {
        if (*iconsPort0 >= 0 || *iconsPort1 >= 0)
            break;
        iconsPort1++;
        iconsPort0++;
    }

    if (i == BLOCK_PER_CARD) {
        D_801BAF10 = 1;
    }
}
