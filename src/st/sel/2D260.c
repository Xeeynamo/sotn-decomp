#include "sel.h"

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

    for (i = 0; i < 5; i++) {
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

// single instruction reorder, function tested working in-game
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AD66C);
#else
void func_801AD66C(void) {
    s32 spaceCounter;
    s32 counter;
    s32 i;

    /**
     * If the entered name contains 8 spaces, sets the default
     * name to "alucard " which is stored in D_801A7754
     */
    for (spaceCounter = 0, i = 0; i < 8; i++) {
        g_SaveName[i] = g_InputSaveName[i];
        if (g_InputSaveName[i] == ' ') {
            spaceCounter++;
        }
    }

    if (spaceCounter == 8) {
        __builtin_memcpy(g_SaveName, D_801A7754, 9);
    }

    /**
     * Checks byte by byte if the entered name is equal
     * to "richter " and if time attack is unlocked,
     * in which case enables the player to play as Richter
     */
    D_80097B98 = 0;
    D_80097B99 = 0;

    for (counter = 0; counter < 8; counter++) {
        if (g_SaveName[counter] != D_80180468[counter]) {
            break;
        }
    }

    if (g_IsTimeAttackUnlocked != false) {
        g_IsTimeAttackUnlocked = 2;
    }

    if ((counter == 8) && (g_IsTimeAttackUnlocked != false)) {
        g_PlayableCharacter = PLAYER_RICHTER;
    } else {
        g_PlayableCharacter = PLAYER_ALUCARD;
    }
}
#endif

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
    if (g_blinkTimer & 8) {
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
    if (D_801BCC84[0] >= 0 || D_801BD02C >= 0) {
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

        if ((D_801BCC84[0] > 0) && (D_801BD02C > 0) &&
            (g_pads[0].tapped & (PAD_L2 + PAD_R2 + PAD_L1 + PAD_R1))) {
            g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 3) % 6;
        }

        if (D_801BCC84[0] < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }

        if (D_801BD02C < 0) {
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
    func_801B2BD4(g_SaveSummary[port].money[slot], 0xB4, 112, 1);
    percentage = g_SaveSummary[port].percentage[slot];
    percentage = percentage * 1000 / 942;
    percentageDecimal = percentage % 10;
    func_801B2BD4(percentage / 10, 232, 112, 1);
    func_801B27A8(240, 116, 8, 4, 0xE0, 0x8C, 0x200, 12, 1, 128);
    func_801B2BD4(percentageDecimal, 248, 112, 1);
}

void func_801AE9A8(void) {
    s32 i;

    MenuHideAllGfx();
    func_801ACBE4(0, 0);

    for (i = 1; i < 5; i++) {
        func_801ACBE4(i + 1, 4);
        func_801B26A0(&g_PrimBuf[D_801BAF18[i + 1][0]], (i * 64) - 32,
                      (i * 5) * 8, 127, 31, D_80180040[i], D_80180054[i]);
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

    *D_801BCC84 = 0;
    D_801BD02C = 0;
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
    prim = &g_PrimBuf[*D_801BAF18[gfxId]];
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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AED48);

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", Update);

void func_801B17C8(void) {
    switch (D_800978F8) {
    case 0:
        if (D_80097924 == -1 || D_8006C378 == -1) {
            g_GameStep++;
        } else {
            D_800978C4 = 0;
            D_800978F8++;
        }
        break;

    case 1:
        func_801B3A54(D_80097924, D_8006C378);
        D_800978F8++;
        break;

    case 2:
        D_800978C4 = 0;
        if (func_801B3A94(1) != 0) {
            D_800978C4 = 1;
            g_GameStep++;
        }
        break;
    }
}

void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

void func_801B1924(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_801B195C(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 20;
    g_GpuBuffers[0].draw.clip.h = 207;
    if (arg0 == 0) {
        g_GpuBuffers[1].draw.clip.y = 20;
    } else {
        g_GpuBuffers[1].draw.clip.y = 276;
    }
    g_GpuBuffers[1].draw.clip.h = 207;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].draw.dtd = 0;
    g_GpuBuffers[0].draw.dtd = 0;
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B19F4(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B195C(0);
}

void func_801B1A98(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_W, DISP_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_W, DISP_H);
    g_GpuBuffers[1].draw.clip.y = DISP_W / 2;
    g_GpuBuffers[1].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B1B88(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, 384, DISP_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, 384, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, 384, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, 384, DISP_H);
    g_GpuBuffers[1].draw.clip.y = 256;
    g_GpuBuffers[1].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B1C78(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        poly->r0 = poly->g0 = poly->b0 = colorIntensity;
        break;
    case 1:
        poly->r1 = poly->g1 = poly->b1 = colorIntensity;
        break;
    case 2:
        poly->r2 = poly->g2 = poly->b2 = colorIntensity;
        break;
    case 3:
        poly->r3 = poly->g3 = poly->b3 = colorIntensity;
        break;
    }
}

void func_801B1CFC(POLY_GT4* poly, s32 colorIntensity) {
    func_801B1C78(poly, colorIntensity, 0);
    func_801B1C78(poly, colorIntensity, 1);
    func_801B1C78(poly, colorIntensity, 2);
    func_801B1C78(poly, colorIntensity, 3);
}

void func_801B1D68(POLY_GT4* poly) { func_801B1CFC(poly, 0); }

void func_801B1D88(POLY_GT4* arg0) { func_801B1CFC(arg0, 0x80); }

void func_801B1DA8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

void func_801B1ED0(void) {
    s32 var_v1 = 0xF;
    s32* var_v0 = D_801BC3D4;

    do {
        *var_v0-- = 0;
    } while (--var_v1 >= 0);
}

u8 func_801B1EF4(u8 arg0) {
    if (arg0 & 0x80) {
        return func_801B1EF4((arg0 & 0x7F) + 3);
    } else {
        return (arg0 * 0x10) & 0xF0;
    }
}

void func_801B1F34(void) { D_801BAFD0 = g_Pix[1]; }

void func_801B1F4C(s32 arg0) {
    const s32 count = 0x200;
    u8* pix;
    s32 i;

    D_801BC398[arg0] = 0;
    arg0 = func_801B1EF4(arg0);
    pix = D_801BAFD0;
    for (i = 0; i < count * 4; i++) {
        *D_801BAFD0++ = 0;
    }

    LoadTPage(pix, 0, 0, 0x180, arg0, 0x100, 0x10);
}

void func_801B1FD8(u8* arg0, s32 arg1) {
    const int W = 12;
    const int H = 16;
    const int LEN = W * H / 2;
    s32 y;
    s32 i;
    s32 x;
    u8* srcPix;
    s32 param;

    y = func_801B1EF4(arg1);
    x = 0;
    while (*arg0 != 0 && D_801BAFD0 < g_Pix[4]) {
        param = *arg0++ << 8;
        param += *arg0++;
        srcPix = g_api.func_80106A28(param, 3);
        for (i = 0; i < LEN; i++) {
            D_801BAFD0[i] = *srcPix++;
        }
        LoadTPage(D_801BAFD0, 0, 0, D_801BAFD4 + x, D_801BAFD8 + y, W, H);
        D_801BAFD0 += LEN;
        x += 3;
    }
}

void func_801B2108(const char* str, s32 id);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2108);

void func_801B248C(const char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B1FD8(str, id);
    }
}

void func_801B24F8(const char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B2108(str, id);
    }
}

void func_801B2564(const char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B248C(str, id);
}

void func_801B259C(const char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B24F8(str, id);
}

void func_801B25D4(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B248C(str, id);
}

void func_801B2608(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B24F8(str, id);
}

void func_801B263C(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B1FD8(str, id);
}

void func_801B2670(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void func_801B26A0(
    POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + height;
    poly->x3 = x + width;
    poly->y3 = y + height;
    poly->v0 = v;
    poly->v1 = v;
    poly->u0 = u;
    poly->u1 = u + width;
    poly->u2 = u;
    poly->v2 = v + height;
    poly->u3 = u + width;
    poly->v3 = v + height;
}

void func_801B2700(s32 tpage, s32 otIdx) {
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    u_long* ot = g_CurrentBuffer->ot;

    SetDrawMode(drawMode, 0, 0, tpage, &D_80182584);
    AddPrim(&ot[otIdx], drawMode);
    g_GpuUsage.drawModes++;
}

void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut, s32 arg7,
                   s32 tge, s32 c) {
    SPRT* sprite = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    GpuBuffer* temp_s4 = g_CurrentBuffer;

    SetSemiTrans(sprite, 0);
    SetShadeTex(sprite, tge);
    sprite->x0 = x;
    sprite->y0 = y;
    sprite->w = w;
    sprite->h = h;
    sprite->u0 = u;
    sprite->v0 = v;
    sprite->r0 = c;
    sprite->g0 = c;
    sprite->b0 = c;
    sprite->clut = D_8003C104[clut];
    AddPrim(&temp_s4->ot[0x20], sprite);
    g_GpuUsage.sp++;
    func_801B2700(arg7, 0x20);
}

void func_801B28D4(u8* str, s32 x, s32 y, s32 tge) {
    const int w = 12;
    const int h = 16;
    u8 ch;

loop_1:
    ch = *str++;
    if (ch != 0xFF) {
        s32 u = (ch & 0xF) * w;
        s32 v = ch & 0xF0;
        func_801B27A8(x, y, w, h, u, v, 0x1A1, 6, tge, 0x40);
        x += w;
        goto loop_1;
    }
}

s32 func_801B2984(u8 ch) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        if (D_8018046C[i * 3] == ch)
            return i;
    }
    return 0x20;
}

void DrawString16x16(const char* str, s32 x, s32 y, s32 tga) {
    const int W = 16;
    const int H = 16;
    char ch;
    s32 uvIndex;

    while (true) {
        ch = *str++;
        if (ch == 0) {
            break;
        }

        uvIndex = func_801B2984(ch);
        func_801B27A8(x, y, W, H, D_8018046C[uvIndex * 3 + 1],
                      D_8018046C[uvIndex * 3 + 2], 0x200, 12, tga, 0x40);
        x += W;
    }
}

void func_801B2A9C(s32 img, s32 x, s32 y, s32 tge) {
    func_801B27A8(
        x, y, 8, 8, (img & 0xF) * 8, (img & 0xF0) / 2, 0x196, 0x1E, tge, 0x80);
}

void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge) {
    while (true) {
        if (*imgs == 0xFF)
            break;
        func_801B2A9C(*imgs, x, y, tge);
        x += 8;
        imgs++;
    }
}

void func_801B2B78(s32 icon, s32 x, s32 y, s32 tge) {
    func_801B27A8(x, y, 8, 8, icon * 8 + 176, 120, 0x200, 0xC, tge, 0x40);
}

void func_801B2BD4(s32 digit, s32 x, s32 y, s32 tge) {
    do {
        func_801B2B78(digit % 10, x, y, tge);
        digit /= 10;
        x -= 8;
    } while (digit != 0);
}

void func_801B2C70(s32 digit, s32 x, s32 y, s32 tge) {
    func_801B2B78(digit % 10, x, y, tge);
    func_801B2B78(digit / 10, x - 8, y, tge);
}

void func_801B2CF8(POLY_GT4* poly) {
    u32* data = poly;
    s32 n = sizeof(POLY_GT4) / sizeof(*data);
    s32 i;

    for (i = 0; i < n; i++) {
        *data++ = 0;
    }
}

void func_801B2D1C(void) {
    s32 i;
    Primitive* prim;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        func_801B2CF8((s32*)prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

void func_801B2D6C(void) {
    MemcardInit();
    D_801BAFDC = 0;
    D_801BAFE0 = 0;
    D_801BAFE4 = 0;
    D_801BAFE8 = 0;
}

s32 func_801B2DAC(void) { return D_801BAFE4 < 2 || D_801BAFE4 == 2; }

void func_801B2DDC(void) {}

void func_801B2DE4(void) {}

void func_801B2DEC(void) {}

void func_801B2DF4(void) {
    if (func_801B2DAC() != 0) {
        D_801BAFDC = func_800E9880(D_801BAFE8, 0);
        if (D_801BAFDC != 0) {
            D_801BAFE0 = D_801BAFDC;
        }
    }

    func_801B2DDC();
    func_801B2DE4();
    func_801B2DEC();
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2E5C);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2F50);

void func_801B3120(void) {
    s32* var_a0;
    s32* var_v0;
    s32* var_v1;
    s32 i;
    s32 n;

    g_memCardRStep = 0;
    i = 0;
    n = -1;
    var_v0 = g_SaveSummary;
    var_a0 = var_v0 + 0xEA;
    var_v1 = var_v0;
    for (; i < 0xF; i++) {
        *var_v1 = n;
        *var_a0 = n;
        var_a0++;
        var_v1++;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3164);

void func_801B367C(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

s32 TryLoadSaveData(void) {
    char saveFile[32];
    s32 nPort;
    s32 nSlot;
    s32 temp_v0;
    s32 blockId;

    FntPrint(D_801A7AF8, g_memCardRStep, g_memCardRStepSub);
    FntPrint(D_801A7B08, g_memCardRetryCount);

    nPort = g_memCardRStepSub / 15;
    nSlot = g_memCardRStepSub % 15;
    blockId = g_SaveSummary[nPort].slot[nSlot];
    switch (g_memCardRStep) {
    case 0:
        MemcardInit();
        g_memCardRetryCount = 10;
        g_memCardRStep = 3;
        break;
    case 3:
        MakeMemcardPath(saveFile, blockId);
        if (MemcardReadFile(nPort, 0, saveFile, g_Pix[0], 1) != 0) {
            g_memCardRetryCount--;
            if (g_memCardRetryCount != -1) {
                return 0;
            }
            temp_v0 = -1;
            return temp_v0;
        }
        g_memCardRStep++;
        break;
    case 4:
        temp_v0 = MemcardClose(nPort);
        if (temp_v0 != 0) {
            if (temp_v0 == -3) {
                g_memCardRetryCount--;
                if (g_memCardRetryCount == -1) {
                    return -1;
                } else {
                    g_memCardRStep--;
                    do {
                        return 0;
                    } while (0); // FAKE!
                }
            }
            if (LoadSaveData(g_Pix[0]) < 0) {
                return -2;
            } else {
                return 1;
            }
        }
        break;
    }

    return 0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B38B4);

void func_801B3A54(s32 arg0, s32 arg1) {
    char pad[0x20];

    g_memCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3A94);

void func_801B3E14(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

s32 func_801B3E2C(void) {
    char path[32];
    s32 slot;
    s32 blockId;
    s32 port;

    port = g_memCardRStepSub / 15;
    slot = g_memCardRStepSub % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (g_memCardRStep) {
    case 0:
        MemcardInit(slot, blockId);
        g_memCardRetryCount = 10;
        g_memCardRStep++;
        break;
    case 1:
        MakeMemcardPath(path, blockId);
        if (MemcardEraseFile(port, 0, path)) {
            if (--g_memCardRetryCount == -1) {
                return -1;
            }
        } else {
            g_SaveSummary[port].icon[slot] = -3;
            return 1;
        }
        break;
    }
    return 0;
}

void func_801B3F7C(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3F94);

void InitRoomEntities(s32 objLayoutId) {
    switch (D_8003C9A4) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = true;
        D_8003C728 = 1;
        D_8003C100 = 0;
        D_8003C9A4 = 1;
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728) {
            break;
        }
        g_IsTimeAttackUnlocked = false;
        D_8003C100 = 0;
        func_801B18F4();
        g_GameState = Game_Title;
        D_8003C9A4 = 0;
        break;
    }
}
