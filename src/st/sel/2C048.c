/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "sel.h"
#include "memcard.h"
#include "sfx.h"

Overlay g_StageSel = {
    /* 0x00 */ SEL_Update,
    /* 0x04 */ HandleTitleScreen,
    /* 0x08 */ func_801B9C80,
    /* 0x0C */ SEL_Init,
    /* 0x10 */ NULL,
    /* 0x14 */ g_SpriteBanks,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ NULL,
    /* 0x20 */ NULL,
    /* 0x24 */ OVL_EXPORT(g_EntityGfxs),
    /* 0x28 */ func_801B60D4,
    /* 0x2C */ NULL,
    /* 0x30 */ &D_8018C404,
    /* 0x34 */ NULL,
    /* 0x38 */ NULL,
    /* 0x3C */ func_801B17C8,
};

// The five possible header options that are displayed on the top-left for each
// sub-menu in the main menu. The same graphics is also re-used for the main
// menu selectable options.
s32 g_MenuHeadGfxU[NUM_MENU_OPTIONS] = {0, 128, 0, 0, 0};
s32 g_MenuHeadGfxV[NUM_MENU_OPTIONS] = {192, 144, 224, 128, 160};

// Unknown. Named 084 due to the name of the function that uses it.
s32 g_MenuUnk084X[NUM_MENU_UNK_084] = {
    16, 16, 24, 61, 104, 128, 24, 152,
};
s32 g_MenuUnk084Y[NUM_MENU_UNK_084] = {
    8, 24, 56, 56, 56, 56, 64, 64,
};
s32 g_MenuUnk084U0[NUM_MENU_UNK_084] = {
    128, 168, 224, 232, 224, 224, 232, 240,
};
s32 g_MenuUnk084V0[NUM_MENU_UNK_084] = {
    240, 240, 128, 128, 136, 136, 136, 136,
};
s32 g_MenuUnk084U1[NUM_MENU_UNK_084] = {
    40, 40, 8, 24, 8, 8, 8, 8,
};
s32 g_MenuUnk084V1[NUM_MENU_UNK_084] = {
    16, 16, 8, 8, 8, 8, 8, 8,
};

StageName D_80180128[80] = {
    {_S("Marble"), _S("Gallery")},
    {_S("Outer"), _S("Wall")},
    {_S("Long"), _S("Library")},
    {_S("Catacombs"), _S("")},
    {_S("Olrox's"), _S("Quarters")},
    {_S("Abandoned"), _S("Mine")},
    {_S("Royal"), _S("Chapel")},
    {_S("Entrance"), _S("")},
    {_S(""), _S("")},
    {_S("Underground"), _S("Caverns")},
    {_S("Colosseum"), _S("")},
    {_S("Castle"), _S("Keep")},
    {_S("Alchemy"), _S("Laboratory")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S("Black Marble"), _S("Gallery")},
    {_S("Reverse"), _S("Outer Wall")},
    {_S("Forbidden"), _S("Library")},
    {_S("Floating"), _S("Catacombs")},
    {_S("Death Wing's"), _S("Lair")},
    {_S("Cave"), _S("")},
    {_S("Anti-Chapel"), _S("")},
    {_S("Reverse"), _S("Entrance")},
    {_S(""), _S("")},
    {_S("Reverce"), _S("Caverns")},
    {_S("Reverce"), _S("Colosseum")},
    {_S("Reverce"), _S("Keep")},
    {_S("Necromancy"), _S("Laboratory")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S("Entrance"), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
    {_S(""), _S("")},
};

void func_801B18F4(void);
void func_801B19F4(void);
void SetTitleDisplayBuffer256(void);
void func_801B1D88(Primitive* prim);
void func_801B1DA8(void);
void func_801B1F34(void);
void func_801B1F4C(s32 arg0);
void func_801B25D4(const char* str, s32 id);
void func_801B2608(const char* str, s32 id);
void func_801B263C(const char* str, s32 id);
void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut, s32 arg7,
                   s32 tge, s32 c);
void func_801B2BD4(s32 digit, s32 x, s32 y, s32 tge);
void func_801B2C70(s32 digit, s32 x, s32 y, s32 tge);
void func_801B2D1C(void);
void func_801B2D6C(void);
void func_801B3120(void);

void SetupFileChoose(void) {
    g_MainMenuCursor = 1;
    g_InputCursorPos = 0;
    D_801BC3E0 = 0;
    D_801D6B04 = 0;
    g_MemCardSelectorX = 0;
    g_MemCardSelectorY = 0;
}

void func_801AC084(s32 arg0, s32 ypos) {
    Primitive* prim = &g_PrimBuf[D_801BAF18[arg0][0]];
    s32 i;

    for (i = 0; i < NUM_MENU_UNK_084; i++) {
        prim->x0 = g_MenuUnk084X[i] + 104;
        prim->y0 = g_MenuUnk084Y[i] + 88 + ypos;
        prim->u0 = g_MenuUnk084U0[i];
        prim->v0 = g_MenuUnk084V0[i];
        prim->u1 = g_MenuUnk084U1[i];
        prim->v1 = g_MenuUnk084V1[i];
        prim->tpage = 0xC;
        prim->clut = 0x200;
        prim->priority = 0x11;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// Creates the buttons, displays, etc on main menu
static void InitMainMenuUI(void) {
    Primitive* prim;
    s32 i;
    s32 y;
    s32 x;

    // Decoration at the top left for "Select Your Destiny"
    D_801BAF18[GFX_UNK_0][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    i = 0;
    y = 0;
    x = -0x20;
    prim = &g_PrimBuf[D_801BAF18[GFX_UNK_0][0]];
    SetTexturedPrimRect(prim, 216, 16, 144, 72, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x201;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    for (; i < NUM_MENU_OPTIONS; i++) {
        D_801BAF18[i + 1][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
        prim = &g_PrimBuf[D_801BAF18[i + 1][0]];
        SetTexturedPrimRect(
            prim, x, y, 127, 31, g_MenuHeadGfxU[i], g_MenuHeadGfxV[i]);
        func_801B1D88(prim);
        prim->tpage = 0xC;
        prim->clut = 0x200;
        prim->priority = 0x10;
        if (i == 0) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_COLORS;
        }
        y += 40;
        x += 64;
    }

    D_801BAF18[6][0] = g_api.AllocPrimitives(PRIM_GT4, 4);
    prim = &g_PrimBuf[D_801BAF18[6][0]];
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x50);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x70);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x60);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x80);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    D_801BAF18[7][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[7][0]];
    SetTexturedPrimRect(prim, 112, 48, 160, 48, 0, 0x50);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[8][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[8][0]];
    SetTexturedPrimRect(prim, 128, 72, 15, 15, 0xF0, 0xF0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x30;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[9][0] = g_api.AllocPrimitives(PRIM_SPRT, 3);
    prim = &g_PrimBuf[D_801BAF18[9][0]];
    for (i = 0; i < 3; i++) {
        prim->x0 = 48 + i * 128;
        prim->y0 = 96;
        prim->u0 = i * 128;
        prim->v0 = 0x78;
        prim->u1 = 0x80;
        prim->v1 = 0x78;
        if (i == 2) {
            prim->u0 = 0xE0;
            prim->v0 = 0;
            prim->u1 = 0x20;
        }
        prim->tpage = 0xD;
        prim->clut = 0x202;
        prim->priority = 0x10;
        prim->drawMode = 8;
        prim = prim->next;
    }

    D_801BAF18[10][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[10][0]];
    SetTexturedPrimRect(prim, 64, 104, 32, 32, 0, 0x48);
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x204;
    prim->priority = 0x30;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[GFX_WND_SAVE_SUMMARY][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[11][0]];
    SetTexturedPrimRect(prim, 104, 88, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[GFX_UNK_12][0] = g_api.AllocPrimitives(PRIM_SPRT, 8);
    func_801AC084(0xC, 0);

    D_801BAF18[GFX_WND_CARD_1][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[13][0]];
    prim->x0 = 24;
    prim->y0 = 56;
    prim->u0 = 0xB0;
    prim->v0 = 0;
    prim->u1 = 0x50;
    prim->v1 = 0x78;
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[GFX_WND_CARD_2][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[14][0]];
    prim->x0 = 280;
    prim->y0 = 56;
    prim->u0 = 0x90;
    prim->v0 = 0;
    prim->u1 = 0x50;
    prim->v1 = 0x78;
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[15][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[15][0]];
    prim->x0 = 148;
    prim->y0 = 16;
    prim->u0 = 0;
    prim->v0 = 0x40;
    prim->u1 = 0xD0;
    prim->v1 = 0x20;
    func_801B1D88(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[16][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[16][0]];
    prim->x0 = 160;
    prim->y0 = 96;
    prim->u0 = 0;
    prim->v0 = 0x60;
    prim->u1 = 0x70;
    prim->v1 = 0x30;
    func_801B1D88(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[17][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[17][0]];
    prim->y0 = 192;
    prim->x0 = 96;
    prim->u0 = 0;
    prim->v0 = 0x90;
    prim->u1 = 1;
    prim->v1 = 0x10;
    func_801B1D88(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_DEFAULT;

    D_801BAF18[18][0] = g_api.AllocPrimitives(PRIM_GT4, 2);
    prim = &g_PrimBuf[D_801BAF18[18][0]];
    SetTexturedPrimRect(prim, 104, 48, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;
    prim = prim->next;
    SetTexturedPrimRect(prim, 168, 128, 48, 16, 0xB0, 0x80);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_801BAF18[19][0] = g_api.AllocPrimitives(PRIM_SPRT, 8);
    func_801AC084(0x13, -0x28);

    D_801BAF18[20][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_801BAF18[20][0]];
    prim->x0 = 160;
    prim->y0 = 56;
    prim->u0 = 0;
    prim->v0 = 0xA0;
    prim->u1 = 0x70;
    prim->v1 = 0x30;
    func_801B1D88(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_HIDE;
}

void func_801ACBE4(s32 gfxId, u16 drawMode) {
    Primitive* prim = &g_PrimBuf[D_801BAF18[gfxId][0]];
    while (prim != NULL) {
        prim->drawMode = drawMode;
        prim = prim->next;
    }
}

void MenuHideAllGfx(void) {
    s32 i;
    for (i = GFX_UNK_0; i < NUM_GFX; i++) {
        func_801ACBE4(i, 8);
    }
}

static void InitMainMenuBackgroundAndFadeMask(void) {
    s16 primIndex;
    Primitive* prim;
    s32 i;

    // Seems to be the background on the main menu (dark blue/grey door thing?)
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
    prim = &g_PrimBuf[primIndex];
    D_801BAFC0 = primIndex;
    for (i = 0; i < 3; i++) {
        SetTexturedPrimRect(prim, i << 7, 0, 128, 240, 0, 0);
        func_801B1D88(prim);
        prim->tpage = i + 137;
        prim->clut = 0x210;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
    }

    // When the main menu is loaded in, it is covered by a black mask that fades
    // away. This part creates the initial mask, then MainMenuFadeIn deals
    // with fading it out.
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 2);
    prim = &g_PrimBuf[primIndex];
    MainMenuMaskPrimIndex = primIndex;
    for (i = 0; prim != NULL; i++) {
        prim->x0 = (i & 1) * 192;
        prim->u0 = 192;
        prim->v0 = 240;
        SetPrimGrey(prim, 255);
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;
    }
}

// On title screen, you press START. Then the screen goes black,
// and fades in gradually. This function handles that fade. Returns false
// as long as the fade-in is ongoing.
// Odd that this function can return false but not true. Perhaps there is a
// default-true behavior when a bool function exits without an explicit value?
// PSP version returns true at the end. True means the fade is complete.
static bool MainMenuFadeIn(void) {
    Primitive* prim = &g_PrimBuf[MainMenuMaskPrimIndex];
    s32 greyLevel = prim->r0;

    greyLevel -= 16;
    if (greyLevel < 0) {
        greyLevel = 0;
    }

    SetPrimGrey(prim, greyLevel);
    prim = prim->next;
    SetPrimGrey(prim, greyLevel);

    if (greyLevel != 0) {
        return false;
    } else {
        // Once the greyLevel is exhaused, we hide them.
        prim = &g_PrimBuf[MainMenuMaskPrimIndex];
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
    }
}

s32 func_801ACEC0(void) {
    Primitive* prim = &g_PrimBuf[MainMenuMaskPrimIndex];
    s32 var_s0 = prim->r0;

    var_s0 += 0x10;
    prim->drawMode = 0x51;

    if (var_s0 > 255) {
        var_s0 = 255;
    }

    SetPrimGrey(prim, var_s0);
    prim = prim->next;
    prim->drawMode = 0x51;
    SetPrimGrey(prim, var_s0);

    if (g_api.func_80131F68()) {
        return 0;
    } else {
        return var_s0 == 255;
    }
}

void func_801ACF7C(void) {
    func_801B1ED0();
    func_801B25D4("…選択決定取消入力未初期化確認", 0);
    func_801B25D4("はいえ不良", 1);
}

const char* D_801803A8[10] = {
    _S("Select"), _S("Decide"), _S("Cancel"),  _S("Input"), _S("Not for-"),
    _S("Yes"),    _S("No"),     _S("Confirm"), _S("Error"), _S("matted"),
};

const char* D_801803D0[] = {
    "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ", "Ｋ",
    "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ", "Ｕ", "Ｖ",
    "Ｗ", "Ｘ", "Ｙ", "Ｚ", "＆", "！", "−",  "．", "’",  "？", "　",
};

s32 func_801B2984(char ch);
void func_801ACFBC(s32 port, s32 slot, s32 textId) {
    char playerName[0x20];
    const char* strSaveKind;
    s32 i;
    char ch;

    playerName[0] = '\0';
    for (i = 0; i < 8; i++) {
        ch = g_SaveSummary[port].name[slot][i];
        strcat(playerName, D_801803D0[func_801B2984(ch)]);
    }

    do {
        func_801B263C(playerName, textId);
        func_801B25D4("　", textId + 1);
    } while (0);
    if (g_SaveSummary[port].character[slot]) {
        strSaveKind = "Richter";
    } else if (g_SaveSummary[port].kind[slot] & SAVE_FLAG_CLEAR) {
        strSaveKind = "Clear";
    } else if (g_SaveSummary[port].kind[slot] & SAVE_FLAG_REPLAY) {
        strSaveKind = "Replay";
    } else {
        strSaveKind = "　";
    }
    func_801B2608(strSaveKind, textId + 2);
}

void PrintFileSelectPlaceName(s32 port, s32 slot, s32 y) {
    const s32 x = 160;
    const s32 row1y = 0;
    const s32 row2y = 8;
    const s32 tge = 1;
    volatile u32 pad; // !FAKE:

    s32 stage = g_SaveSummary[port].stage[slot];
    DrawImages8x8(D_80180128[stage].line1, x, y + row1y, tge);
    DrawImages8x8(D_80180128[stage].line2, x, y + row2y, tge);
}

#define STR_SELECT D_801803A8[0]
#define STR_DECIDE D_801803A8[1]
#define STR_CANCEL D_801803A8[2]
#define STR_INPUT D_801803A8[3]
#define STR_NOTFOR D_801803A8[4]
#define STR_YES D_801803A8[5]
#define STR_NO D_801803A8[6]
#define STR_CONFIRM D_801803A8[7]
#define STR_ERROR D_801803A8[8]
#define STR_MATTED D_801803A8[9]

typedef enum {
    Tips_Generic,
    Tips_Input,
    Tips_YesNo,
    Tips_Confirm,
    Tips_MenuNavigation,
    Tips_NoYes,
} NavigationTips;

extern char g_AsciiSet[];

void func_801AD1D0(void) {
    DrawImages8x8(STR_YES, 52, 196, 1);
    DrawImages8x8(STR_NO, 52, 212, 1);
}

void func_801AD218(void) {
    DrawImages8x8(STR_NO, 52, 196, 1);
    DrawImages8x8(STR_YES, 52, 212, 1);
}

void DrawNavigationTips(NavigationTips mode) {
    Primitive* prim;

    func_801ACBE4(6, 8);
    prim = &g_PrimBuf[D_801BAF18[GFX_UNK_6][0]];

    switch (mode) {
    case Tips_Generic:
        SetPrimRect(prim, 32, 176, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 32, 192, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 32, 208, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        break;

    case Tips_Input:
        SetPrimRect(prim, 288, 32, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 288, 48, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 288, 64, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 288, 80, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        break;

    case Tips_YesNo:
    case Tips_NoYes:
        prim = prim->next;
        SetPrimRect(prim, 32, 192, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 32, 208, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        if (mode == Tips_YesNo) {
            func_801AD1D0();
        } else {
            func_801AD218();
        }
        break;

    case Tips_Confirm:
        prim = prim->next;
        SetPrimRect(prim, 32, 192, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        DrawImages8x8(STR_CONFIRM, 52, 196, 1);
        break;

    case Tips_MenuNavigation:
        SetPrimRect(prim, 32, 184, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        SetPrimRect(prim, 32, 200, 16, 16);
        prim->drawMode = DRAW_DEFAULT;
        break;
    }
}

void func_801AD490(void) {
    s32 i;

    DrawNavigationTips(Tips_MenuNavigation);
    DrawImages8x8(STR_SELECT /* "select" */, 52, 188, 1);
    DrawImages8x8(STR_DECIDE /* "start" */, 52, 204, 1);
    DrawString16x16("select", 240, 32, 1);
    DrawString16x16("your", 256, 48, 1);
    DrawString16x16("destiny", 232, 64, 1);

    for (i = 0; i < NUM_MENU_OPTIONS; i++) {
        Primitive* prim = &g_PrimBuf[D_801BAF18[i + 1][0]];
        if (i == g_MainMenuCursor) {
            prim->clut = 0x203;
        } else {
            prim->clut = 0x200;
        }
    }
}

const char* D_80180454[] = {
    "−＊＊＊＊＊−",  "− New Game −",   "− Change Name −",
    "− Copy File −", "− Erase File −",
};
void func_801AD590(void) {
    if (g_pads[0].tapped & (PAD_RIGHT + PAD_DOWN)) {
        g_api.PlaySfx(SFX_UI_MP_FULL); // MP sfx also used for Main Menu Select
        if (++g_MainMenuCursor == 5) {
            g_MainMenuCursor = 1;
        }
    }
    if (g_pads[0].tapped & (PAD_LEFT + PAD_UP)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        if (--g_MainMenuCursor == 0) {
            g_MainMenuCursor = 4;
        }
    }
    func_801B2608(D_80180454[g_MainMenuCursor], 9);
}

const char* D_80180468[] = {
    "richter ",
};
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
        STRCPY(g_SaveName, "alucard ");
    }

    D_80097B98 = 0;
    D_80097B99 = 0;

    // check if the name is Richter
    for (strRichter = D_80180468[0], i = 0; i < 8; i++) {
        if (g_SaveName[i] != *strRichter++) {
            break;
        }
    }

    if (g_IsTimeAttackUnlocked != SAVE_FLAG_NORMAL) {
        g_IsTimeAttackUnlocked = SAVE_FLAG_REPLAY;
    }

    // play as Richter only if the game was previously cleared
    if (i == 8 && g_IsTimeAttackUnlocked != SAVE_FLAG_NORMAL) {
        g_PlayableCharacter = PLAYER_RICHTER;
    } else {
        g_PlayableCharacter = PLAYER_ALUCARD;
    }
}

void func_801AD78C(void) {
    DrawImages8x8(STR_SELECT, 0x134, 0x24, 1);
    DrawImages8x8(STR_INPUT, 0x134, 0x34, 1);
    DrawImages8x8(STR_CANCEL, 0x134, 0x44, 1);
    DrawImages8x8(STR_DECIDE, 0x134, 0x54, 1);
    DrawString16x16("a b c d e f g h", 0x48, 0x70, 1);
    DrawString16x16("i j k l m n o p", 0x48, 0x88, 1);
    DrawString16x16("q r s t u v w x", 0x48, 0xA0, 1);
    DrawString16x16("y z & ! - . '  ", 0x48, 0xB8, 1);
    SetTexturedPrimRect(
        &g_PrimBuf[D_801BAF18[GFX_UNK_8][0]], (g_InputCursorPos * 0x10) + 0x80,
        0x48, 0x0F, 0x0F, 0xF0, 0xF0);
    SetTexturedPrimRect(
        &g_PrimBuf[D_801BAF18[GFX_UNK_10][0]], ((D_801BC3E0 & 7) << 5) + 0x40,
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
        g_api.PlaySfx(SFX_UI_MOVE);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 + 1) & 7);
    }

    if (g_pads[0].repeat & PAD_DOWN) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_801BC3E0 = ((D_801BC3E0 + 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].repeat & PAD_LEFT) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 - 1) & 7);
    }

    if (g_pads[0].repeat & PAD_UP) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_801BC3E0 = ((D_801BC3E0 - 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].tapped & (PAD_R1 + PAD_R2)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        if (++g_InputCursorPos == 8) {
            g_InputCursorPos = 0;
        }
    }

    if (g_pads[0].tapped & (PAD_L1 + PAD_L2)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
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
            g_api.PlaySfx(SFX_UI_MOVE);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 1) % 6;
        }

        if (g_pads[0].repeat & PAD_DOWN) { // move selector down
            g_api.PlaySfx(SFX_UI_MOVE);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 4) % 5;
        }

        if (g_pads[0].repeat & PAD_LEFT) { // move selector to the left
            g_api.PlaySfx(SFX_UI_MOVE);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 5) % 6;
        }

        if (g_pads[0].repeat & PAD_UP) { // move selector up
            g_api.PlaySfx(SFX_UI_MOVE);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 1) % 5;
        }

        if (g_SaveSummary[0].padding > 0 && g_SaveSummary[1].padding > 0 &&
            (g_pads[0].tapped & (PAD_L2 + PAD_R2 + PAD_L1 + PAD_R1))) {
            g_api.PlaySfx(SFX_UI_MP_FULL);
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

void func_801ADF94(s32 flags, bool yOffset) {
    s32 saveDescriptorString = flags & 0x7F;
    bool hideButtons = flags & 0x80;
    s32 port = D_801D6B04 / 15;
    s32 slot = D_801D6B04 % 15;
    s32 y = yOffset * 56;
    s32 icon;
    Primitive* p = g_PrimBuf + D_801BAF18[11][0];

    SetTexturedPrimRect(p, 104, 88 + y, 176, 80, 0, 0);

    if (saveDescriptorString > 0) {
        if (g_SaveSummary[port].padding == -3 || saveDescriptorString == 3) {
            func_801ACBE4(12, 8);
            func_801ACBE4(16, 8);
            DrawString16x16("new game", 128, 120 + y, 1);
        } else {
            icon = g_SaveSummary[port].icon[slot];
            if (icon >= 0) {
                s32 percLo;
                s32 percHi;
                func_801AC084(12, y);
                func_801ACBE4(12, 0);
                func_801ACBE4(16, 0);
                p = g_PrimBuf + D_801BAF18[16][0];
                p->y0 = 96 + y;
                func_801ACFBC(port, slot, 6);
                PrintFileSelectPlaceName(port, slot, 112 + y);
                func_801B2BD4(g_SaveSummary[port].level[slot], 148, 144 + y, 1);
                func_801B2BD4(
                    g_SaveSummary[port].playHours[slot], 200, 144 + y, 1);
                func_801B2C70(
                    g_SaveSummary[port].playMinutes[slot], 224, 144 + y, 1);
                func_801B2C70(
                    g_SaveSummary[port].playSeconds[slot], 248, 144 + y, 1);
                func_801B2BD4(g_SaveSummary[port].gold[slot], 180, 152 + y, 1);
                percHi = g_SaveSummary[port].nRoomsExplored[slot];
                percHi = (percHi * 1000) / 942;
                percLo = percHi % 10;
                percHi = percHi / 10;
                func_801B2BD4(percHi, 232, 152 + y, 1);
                func_801B27A8(
                    240, 156 + y, 8, 4, 0xE0, 0x8C, 0x200, 0xC, 1, 0x80);
                func_801B2BD4(percLo, 248, 152 + y, 1);
            } else {
                func_801ACBE4(12, 8);
                func_801ACBE4(16, 8);
                if (icon == -2) {
                    DrawString16x16("used", 160, 120 + y, 1);
                } else if (saveDescriptorString == 2) {
                    DrawString16x16("no data", 136, 120 + y, 1);
                } else {
                    DrawString16x16("new game", 128, 120 + y, 1);
                }
            }
        }
    }

    if (!hideButtons) {
        DrawImages8x8(STR_SELECT, 52, 180, 1);
        DrawImages8x8(STR_DECIDE, 52, 196, 1);
        DrawImages8x8(STR_CANCEL, 52, 212, 1);
    }

    for (port = 0; port < PORT_COUNT; ++port) {
        switch (g_SaveSummary[port].padding) {
        case -1:
            DrawString16x16("no", 48 + port * 256, 88, 1);
            DrawString16x16("card", 32 + port * 256, 104, 1);
            break;
        case -2:
            DrawImages8x8(STR_NOTFOR, 30 + port * 256, 108, 1);
            DrawImages8x8(STR_MATTED, 30 + port * 256, 116, 1);
            break;
        case -3:
            DrawImages8x8(STR_ERROR, 54 + port * 256, 108, 1);
            break;
        default: {
            s32 slot;
            for (slot = 0; slot < BLOCK_PER_CARD; ++slot) {
                s32 x;
                s32 color;
                s32 tge;
                s32 nRow;
                s32 nCol;
                icon = g_SaveSummary[port].icon[slot];
                nRow = slot / 3;
                nCol = slot % 3;
                x = nCol * 24 + 32 + port * 256;
                y = 0x90 - nRow * 16;

                if (nCol + port * 3 == g_MemCardSelectorX &&
                    saveDescriptorString != 3 && nRow == g_MemCardSelectorY &&
                    saveDescriptorString > 0 && D_801BAF10 == 0) {
                    tge = 0;
                    color = 0x40;

                    if (g_Timer & 0x10) {
                        color = g_Timer & 0xF;
                    } else {
                        color = 0xF - (g_Timer & 0xF);
                    }
                    color = color * 8 + 0x80;

                } else {
                    tge = 0;
                    color = 0x40;
                }
                if (icon == -2) {
                    func_801B27A8(
                        x, y, 16, 16, 0x90, 0x80, 0x200, 0xC, tge, color);
                }
                if (icon == -3) {
                    func_801B27A8(
                        x, y, 16, 16, 0x80, 0x80, 0x200, 0xC, tge, color);
                }
                if (icon >= 0) {
                    func_801B27A8(
                        x, y, 16, 16, icon * 0x10, (D_801BAF08 % 3) * 0x10,
                        icon + 0x220, 0x16, tge, color);
                }
            }
            break;
        }
        }
    }
}

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
    SetTexturedPrimRect(prim, 168, (D_801BAF08 % 3) + 127, 48, 16, 0xB0, 0x80);
    prim->drawMode = DRAW_DEFAULT;
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
        SetTexturedPrimRect(
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
        SetPrimRect(&g_PrimBuf[D_801BAF18[GFX_UNK_1][0]], 24, 24, 127, 31);
    } else {
        func_801ACBE4(3, 0);
        SetPrimRect(
            &g_PrimBuf[D_801BAF18[GFX_FILE_DELETE][0]], 24, 24, 127, 31);
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
    SetPrimRect(prim, 16, 16, 127, 31);
    prim->clut = 0x200;
}

void func_801AECA0(void) {
    s32 i = 0;
    s32 x;
    s32 y = 256;
    s32 w = 16;
    s32 h = 48;
    s32 xnext = 384;
    u_long** pix = g_saveIconTexture;

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

extern s32 D_801BAF0C;
extern s32 g_SelNextCrossPressEngStep;
extern s32 g_SelEng220NextStep;

// SEL seems to use these differently
typedef enum {
    Upd_Eng_Init,
    Upd_Eng_MenuInit = -1,
    Upd_Eng_MenuFadeIn = 1,
    Upd_Eng_MainMenuIdle,
    Upd_Eng_3,
    Upd_Eng_0x10 = 0x10,
    Upd_Eng_17,
    Upd_Eng_18,
    Upd_Eng_FileSelect = 0x30,
    Upd_Eng_49,
    Upd_Eng_50,
    Upd_Eng_51,
    Upd_Eng_64 = 0x40,
    Upd_Eng_65,
    Upd_Eng_FileCopy = 0x50,
    Upd_Eng_81,
    Upd_Eng_82,
    Upd_Eng_83,
    Upd_Eng_84,
    Upd_Eng_85,
    Upd_Eng_86,
    Upd_Eng_87,
    Upd_Eng_88,
    Upd_Eng_89,
    Upd_Eng_0x60 = 0x60,
    Upd_Eng_FileDelete = 0x70,
    Upd_Eng_113,
    Upd_Eng_114,
    Upd_Eng_115,
    Upd_Eng_116,
    Upd_Eng_117,
    Upd_Eng_118,
    Upd_Eng_119,
    Upd_Eng_120,
    Upd_Eng_0x80 = 0x80,
    Upd_Eng_NameChange = 0x90,
    Upd_Eng_145,
    Upd_Eng_146,
    Upd_Eng_147,
    Upd_Eng_148,
    Upd_Eng_149,
    Upd_Eng_150,
    Upd_Eng_151,
    Upd_Eng_152,
    Upd_Eng_153,
    Upd_Eng_0xA0 = 0xA0,
    Upd_Eng_0x100 = 0x100,
    Upd_Eng_257,
    Upd_Eng_258,
    Upd_Eng_259,
    Upd_Eng_260,
    Upd_Eng_0x200 = 0x200,
    Upd_Eng_513,
    Upd_Eng_514,
    Upd_Eng_515,
    Upd_Eng_516,
    Upd_Eng_0x210 = 0x210,
    Upd_Eng_529,
    Upd_Eng_530,
    Upd_Eng_531,
    Upd_Eng_532,
    Upd_Eng_0x220 = 0x220,

} SelGameEngineStep;

void SEL_Update(void) {
    s32 temp_v0;
    s32 var_a0_2;
    s32 i;
    s32 port;
    s32 slot;
    s32 icon;

    func_801B1F34();
    switch (g_GameEngineStep) {
    case Upd_Eng_Init:
        func_801B18F4();
        SetTitleDisplayBuffer256();
        g_GameEngineStep--;
        break;
    case Upd_Eng_MenuInit:
        g_api.PlaySfx(MU_PRAYER);
        g_GameTimer = 0;
        D_801BAF08 = 0;
        func_801B2D6C();
        g_api.func_800EA5E4(0);
        g_api.func_800EA5E4(0x8000);
        g_api.func_800EA5E4(0x8001);
        g_api.func_800EA5E4(0x8002);
        g_api.func_800EA5E4(0x8003);
        g_api.func_800EA5E4(0x8006);
        SetupFileChoose();
        InitMainMenuBackgroundAndFadeMask();
        InitMainMenuUI();
        func_801ACF7C();
        func_801AECA0();
        func_801B1F4C(9);
        func_801AD490();
        g_GameEngineStep += 2;
        break;
    case Upd_Eng_MenuFadeIn:
        func_801AD590();
        func_801AD490();
        if (MainMenuFadeIn() != 0) {
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_MainMenuIdle:
        func_801AD590();
        func_801AD490();
        if (g_pads[0].tapped & PAD_CROSS) {
            switch (g_MainMenuCursor) {
            case 0:
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_0x10;
                break;
            case 1:
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_FileSelect;
                break;
            case 2:
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_NameChange;
                break;
            case 3:
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_FileCopy;
                break;
            case 4:
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_FileDelete;
                break;
            default:
                g_api.PlaySfx(SE_UI_ERROR);
                break;
            }
        }
        break;
    case Upd_Eng_3:
        func_801AD590();
        func_801AD490();
        if (func_801ACEC0()) {
            SetGameState(Game_Title);
        }
        break;
    case Upd_Eng_0x10:
        STRCPY(g_InputSaveName, "        ");
        func_801AEA8C(0);
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_17:
        for (i = 0; i < 8; i++) {
            if (g_InputSaveName[i] != ' ') {
                break;
            }
        }
        if (!(g_pads[0].tapped & PAD_SELECT) &&
            (!(g_pads[0].tapped & PAD_TRIANGLE) || i != 8 ||
             g_InputCursorPos != 0)) {
            UpdateNameEntry();
            func_801AD78C();
            if (g_pads[0].tapped & PAD_START) {
                g_api.PlaySfx(SFX_UI_CONFIRM);
                func_801AD66C();
                if (g_PlayableCharacter == 0) {
                    g_StageId = STAGE_ST0;
                } else {
                    g_StageId = STAGE_NO3;
                }
                D_8003C730 = 0;
                D_8006C378 = -1;
                if (D_801BAF10) {
                    D_80097924 = -1;
                } else {
                    D_80097924 = D_801D6B04 / 15;
                }
                g_api.PlaySfx(0x80);
                g_GameEngineStep++;
            }
        } else {
            g_GameEngineStep = Upd_Eng_FileSelect;
        }
        break;
    case Upd_Eng_18:
        func_801AD78C();
        if (func_801ACEC0()) {
            func_801B18F4();
            func_801B19F4();
            func_801B1DA8();
            func_801B2D1C();
            g_api.func_800EA538(0);
            if (g_PlayableCharacter == 0) {
                SetGameState(Game_VideoPlayback);
            } else {
                g_GameStep++;
            }
        }
        break;
    case Upd_Eng_FileSelect:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_SELECT);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_49:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            g_GameEngineStep++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                g_SelNextCrossPressEngStep = Upd_Eng_FileSelect;
                g_SelEng220NextStep = Upd_Eng_FileSelect + 2;
                g_GameEngineStep = Upd_Eng_0x200;
            }
        }
        break;
    case Upd_Eng_50:
        if (g_IsTimeAttackUnlocked == 0) {
            D_801BAF0C = 0xFF;
        } else {
            D_801BAF0C = 0x2FF;
        }
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        if (D_801BAF10) {
            func_801B2608("You won’t be able to save", 4);
            func_801B2608("your game． Is that OK？", 5);
            func_801ADF94(0x83, 0);
            DrawNavigationTips(Tips_YesNo);
            g_GameEngineStep = Upd_Eng_64;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(1, 0);
            func_801B25D4("　", 4);
            func_801B25D4("　", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_64:
        func_801ADF94(0x81, 0);
        DrawNavigationTips(Tips_YesNo);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = Upd_Eng_0x10;
        }
        break;
    case Upd_Eng_65:
        func_801ADF94(0x83, 0);
        DrawNavigationTips(Tips_YesNo);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            D_801BAF0C = 0xFF;
            DrawNavigationTips(Tips_Generic);
            func_801B2608("Select file to be loaded．", 4);
            func_801B2608("", 5);
            g_GameEngineStep = Upd_Eng_51;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = Upd_Eng_0x10;
        }
        break;
    case Upd_Eng_51:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
            break;
        }

        UpdateFileSelect();
        func_801ADF94(1, 0);
        if (++D_801BAF0C == 0x100) {
            func_801B2608("Select file to be loaded．", 4);
            func_801B2608("", 5);
        }
        if (D_801BAF0C == 0x200) {
            if (D_801BAF14 != 0) {
                func_801B2608("Press Start button", 4);
                func_801B2608("to begin new game．", 5);
            } else {
                func_801B2608("Select New Game", 4);
                func_801B2608("to start from beginning．", 5);
            }
            if (g_IsTimeAttackUnlocked == 0) {
                D_801BAF0C = 0;
            }
        }
        if (D_801BAF0C == 0x300) {
            func_801B2608("Input ””RICHTER”” to play", 4);
            func_801B2608("as Richter Belmont．", 5);
            D_801BAF0C = 0;
        }
        if ((g_pads[0].tapped & PAD_START) && D_801BAF14 != 0) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801B2608("You won’t be able to save", 4);
            func_801B2608("your game． Is that OK？", 5);
            func_801ADF94(0x81, 0);
            DrawNavigationTips(Tips_YesNo);
            g_GameEngineStep = Upd_Eng_65;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            port = D_801D6B04 / 15;
            slot = D_801D6B04 % 15;
            icon = g_SaveSummary[port].icon[slot];
            if (icon >= 0) {
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_0x100;
            } else if (icon == -3) {
                g_api.PlaySfx(SFX_UI_CONFIRM);
                g_GameEngineStep = Upd_Eng_0x10;
            } else {
                g_api.PlaySfx(0x686);
            }
        }
        break;
    case Upd_Eng_NameChange:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
        func_801ACBE4(GFX_UNK_15, 0);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_145:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            g_GameEngineStep++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                g_SelNextCrossPressEngStep = Upd_Eng_NameChange;
                g_SelEng220NextStep = Upd_Eng_NameChange + 2;
                g_GameEngineStep = Upd_Eng_0x200;
            }
        }
        break;
    case Upd_Eng_146:
        func_801ACBE4(GFX_UNK_15, 0);
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            g_GameEngineStep = Upd_Eng_0xA0;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select the file", 4);
            func_801B2608("you wish to rename．", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_0xA0:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        }
        break;
    case Upd_Eng_147:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    g_api.PlaySfx(SFX_UI_CONFIRM);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case Upd_Eng_148:
        STRCPY(g_InputSaveName, "        ");
        func_801AEA8C(1);
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_149:
        for (i = 0; i < 8; i++) {
            if (g_InputSaveName[i] != ' ') {
                break;
            }
        }
        if (g_pads[0].tapped & PAD_SELECT ||
            (g_pads[0].tapped & PAD_TRIANGLE && i == 8 &&
             g_InputCursorPos == 0)) {
            SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
            g_GameEngineStep = Upd_Eng_146;
        } else {
            UpdateNameEntry();
            func_801AD78C();
            if (g_pads[0].tapped & PAD_START) {
                SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
                var_a0_2 = 0;
                for (i = 0; i < 8; i++) {
                    if (g_InputSaveName[i] == ' ') {
                        var_a0_2++;
                    }
                }
                if (var_a0_2 == 8) {
                    g_GameEngineStep = Upd_Eng_146;
                } else {
                    func_801ACBE4(GFX_UNK_15, 0);
                    func_801B2608("Changing Name．", 4);
                    func_801B2608("Do not remove Memory Card．", 5);
                    g_api.PlaySfx(SFX_UI_CONFIRM);
                    g_GameEngineStep++;
                }
            }
        }
        break;
    case Upd_Eng_150:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 0);
        func_801B38B4(D_801D6B04, D_801D6B04);
        g_GameEngineStep++;
        break;
    case Upd_Eng_151:
        func_801ADF94(0x82, 0);
        D_800978C4 = 0;
        temp_v0 = func_801B3A94(g_InputSaveName);
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Name changed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        if (temp_v0 == -3) {
            func_801B1F4C(5);
            func_801B2608("Save error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_152:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = Upd_Eng_NameChange;
        }
        break;
    case Upd_Eng_153:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = Upd_Eng_146;
        }
        break;
    case Upd_Eng_FileCopy:
        SelectMainMenuOption(MAIN_MENU_CURSOR_NAME_CHANGE);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_81:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            g_GameEngineStep++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                g_SelNextCrossPressEngStep = Upd_Eng_FileCopy;
                g_SelEng220NextStep = Upd_Eng_FileCopy + 2;
                g_GameEngineStep = Upd_Eng_0x200;
            }
        }
        break;
    case Upd_Eng_82:
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            g_GameEngineStep = Upd_Eng_0x60;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select file", 4);
            func_801B2608("to be copied．", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_0x60:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        }
        break;
    case Upd_Eng_83:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_801B2608("Where do you want", 4);
                    func_801B2608("to copy to？", 5);
                    D_801BC3EC = D_801D6B04;
                    g_api.PlaySfx(SFX_UI_CONFIRM);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case Upd_Eng_84:
        UpdateFileSelect();
        func_801ADF94(2, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801ACBE4(GFX_UNK_18, 8);
            func_801ACBE4(GFX_UNK_19, 8);
            func_801ACBE4(GFX_UNK_20, 8);
            func_801B2608("Select file", 4);
            func_801B2608("to be copied．", 5);
            g_GameEngineStep--;
        } else {
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (D_801BC3EC != D_801D6B04) {
                    icon = g_SaveSummary[port].icon[slot];
                    if (icon >= 0) {
                        func_801B1F4C(5);
                        func_801B2608("OK to overwrite data？", 4);
                        g_api.PlaySfx(SFX_UI_CONFIRM);
                        g_GameEngineStep = Upd_Eng_89;
                    } else if (icon != -2) {
                        func_801B2608("Copying data．", 4);
                        func_801B2608("Do not remove Memory Card．", 5);
                        g_api.PlaySfx(SFX_UI_CONFIRM);
                        g_GameEngineStep++;
                    }
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case Upd_Eng_85:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        func_801B38B4(D_801BC3EC, D_801D6B04);
        g_GameEngineStep++;
        break;
    case Upd_Eng_86:
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        D_800978C4 = 0;
        temp_v0 = func_801B3A94(0);
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("File copied．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        if (temp_v0 == -3) {
            func_801B1F4C(5);
            func_801B2608("Save error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_87:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = Upd_Eng_FileCopy;
        }
        break;
    case Upd_Eng_88:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_18, 8);
            func_801ACBE4(GFX_UNK_19, 8);
            func_801ACBE4(GFX_UNK_20, 8);
            g_GameEngineStep = Upd_Eng_82;
        }
        break;
    case Upd_Eng_89:
        DrawNavigationTips(Tips_YesNo);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801B2608("Copying data．", 4);
            func_801B2608("Do not remove Memory Card．", 5);
            g_GameEngineStep = Upd_Eng_85;
        } else {
            if (g_pads[0].tapped & PAD_TRIANGLE) {
                func_801B1F4C(5);
                func_801B25D4("どこにコピーしますか？", 4);
                DrawNavigationTips(Tips_Generic);
                g_GameEngineStep = Upd_Eng_84;
            }
            func_801AD1D0();
        }
        break;
    case Upd_Eng_FileDelete:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_COPY);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        g_GameEngineStep++;
        // fallthrough
    case Upd_Eng_113:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            g_GameEngineStep++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                g_SelNextCrossPressEngStep = Upd_Eng_FileDelete;
                g_SelEng220NextStep = Upd_Eng_FileDelete + 2;
                g_GameEngineStep = Upd_Eng_0x200;
            }
        }
        break;
    case Upd_Eng_114:
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            g_GameEngineStep = Upd_Eng_0x80;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select file", 4);
            func_801B2608("to be erased．", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_0x80:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        }
        break;
    case Upd_Eng_115:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            g_GameEngineStep = Upd_Eng_MainMenuIdle;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            DrawNavigationTips(Tips_Generic);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_801B1F4C(5);
                    func_801B2608("Is it OK to erase file？", 4);
                    g_api.PlaySfx(SFX_UI_CONFIRM);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case Upd_Eng_116:
        DrawNavigationTips(Tips_YesNo);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801B2608("Select file", 4);
            func_801B2608("to be erased．", 5);
            g_GameEngineStep--;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            func_801ACBE4(GFX_UNK_15, 8);
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_117:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 0);
        func_801B3E14(D_801D6B04);
        g_GameEngineStep++;
        break;
    case Upd_Eng_118:
        func_801ADF94(0x82, 0);
        D_800978C4 = 0;
        temp_v0 = func_801B3E2C();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("File erased．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Delete error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_119:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = Upd_Eng_FileDelete;
        }
        break;
    case Upd_Eng_120:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = Upd_Eng_114;
        }
        break;
    case Upd_Eng_0x100:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x81, 0);
        func_801B2608("Loading Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801ACBE4(GFX_UNK_15, 0);
        func_801B367C(D_801D6B04);
        g_GameEngineStep++;
        break;
    case Upd_Eng_257:
        func_801ADF94(0x81, 0);
        D_800978C4 = 0;
        temp_v0 = TryLoadSaveData();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            D_8003C730 = 1;
            D_80097924 = D_801D6B04 / 15;
            D_8006C378 = g_SaveSummary[D_80097924].slot[D_801D6B04 % 15];
            g_api.PlaySfx(0x80);
            g_GameEngineStep = Upd_Eng_260;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        if (temp_v0 == -2) {
            func_801B1F4C(5);
            func_801B2608("Version error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_258:
        func_801ADF94(0x81, 0);
        if (g_pads[0].tapped) {
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = Upd_Eng_FileSelect;
        }
        break;
    case Upd_Eng_260:
        func_801ADF94(0x81, 0);
        if (func_801ACEC0()) {
            g_GameStep++;
        }
        break;
    case Upd_Eng_0x200:
        DrawNavigationTips(Tips_NoYes);
        func_801ADF94(0x80, 0);
        if (g_SaveSummary[0].padding != -2) {
            g_GameEngineStep = Upd_Eng_0x210;
        } else {
            func_801B2608("Format Memory Card", 4);
            func_801B2608("in slot １？", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_513:
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_6, 8);
            MemCardSetPort(0);
            g_GameEngineStep++;
        } else {
            if (g_pads[0].tapped & PAD_CROSS) {
                g_GameEngineStep = Upd_Eng_0x210;
            }
            func_801AD218();
        }
        break;
    case Upd_Eng_514:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        temp_v0 = MemCardInitAndFormat();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Formatting completed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Formatting error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_515:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = g_SelNextCrossPressEngStep;
        }
        break;
    case Upd_Eng_516:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = g_SelNextCrossPressEngStep;
        }
        break;
    case Upd_Eng_0x210:
        func_801ADF94(0x80, 0);
        func_801AD218();
        if (g_SaveSummary[1].padding != -2) {
            g_GameEngineStep = Upd_Eng_0x220;
        } else {
            func_801B2608("Format Memory Card", 4);
            func_801B2608("in slot １？", 5);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_529:
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_6, 8);
            MemCardSetPort(1);
            g_GameEngineStep++;
        } else {
            if (g_pads[0].tapped & 0x40) {
                g_GameEngineStep = Upd_Eng_0x220;
            }
            func_801AD218();
        }
        break;
    case Upd_Eng_530:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        temp_v0 = MemCardInitAndFormat();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Formatting completed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Formatting error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            g_GameEngineStep++;
        }
        break;
    case Upd_Eng_531:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            func_801ACBE4(GFX_UNK_15, 8);
            g_GameEngineStep = g_SelNextCrossPressEngStep;
        }
        break;
    case Upd_Eng_532:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            g_GameEngineStep = g_SelNextCrossPressEngStep;
        }
        break;
    case Upd_Eng_0x220:
        func_801ADF94(0x80, 0);
        if (D_801BAF10) {
            DrawNavigationTips(Tips_YesNo);
        }
        g_GameEngineStep = g_SelEng220NextStep;
        break;
    }
    if (++g_GameTimer == 10) {
        g_GameTimer = 0;
        D_801BAF08 = (D_801BAF08 + 1) % 3;
    }
}

void func_801B17C8(void) {
    switch (g_MenuStep) {
    case 0:
        if (D_80097924 == -1 || D_8006C378 == -1) {
            g_GameStep++;
        } else {
            D_800978C4 = 0;
            g_MenuStep++;
        }
        break;

    case 1:
        func_801B3A54(D_80097924, D_8006C378);
        g_MenuStep++;
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

#ifndef HARD_LINK
void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}
#endif

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

void SetDisplayBufferColorsToBlack(void) {
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
    SetDisplayBufferColorsToBlack();
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

void SetTitleDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    g_GpuBuffers[1].draw.clip.y = DISP_TITLE_W / 2;
    g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

// same as SetTitleDisplayBuffer, but clips at 256 vertical height
void SetTitleDisplayBuffer256(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    g_GpuBuffers[1].draw.clip.y = 256;
    g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

// For the given prim, sets one of the vertices (0-3) to r,g,b values of
// the given colorIntensity. All of r,g,b are set, so limited to grey shades.
void SetPrimVertexGrey(Primitive* prim, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        prim->r0 = prim->g0 = prim->b0 = colorIntensity;
        break;
    case 1:
        prim->r1 = prim->g1 = prim->b1 = colorIntensity;
        break;
    case 2:
        prim->r2 = prim->g2 = prim->b2 = colorIntensity;
        break;
    case 3:
        prim->r3 = prim->g3 = prim->b3 = colorIntensity;
        break;
    }
}

// Sets each of the 4 vertices of a prim to the specified grey level, thus
// making the whole primitive that level.
void SetPrimGrey(Primitive* prim, s32 colorIntensity) {
    SetPrimVertexGrey(prim, colorIntensity, 0);
    SetPrimVertexGrey(prim, colorIntensity, 1);
    SetPrimVertexGrey(prim, colorIntensity, 2);
    SetPrimVertexGrey(prim, colorIntensity, 3);
}

void func_801B1D68(Primitive* prim) { SetPrimGrey(prim, 0); }

void func_801B1D88(Primitive* prim) { SetPrimGrey(prim, 0x80); }

void func_801B1DA8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }
}

void func_801B1ED0(void) {
    s32 i;

    for (i = 0; i < LEN(D_801BC398); i++) {
        D_801BC398[i] = 0;
    }
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

#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif
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

// Variant of func_800F99B8, with the third argument stripped
void func_801B2108(const char* str, s32 arg1) {
    // See src/st/blit_char.h
    const u16 MINSCODE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s0;
    u8* var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 i;
    s32 j;
    u8* dest_addr;

    var_s1 = str;
    var_s5 = arg1;
    var_s4 = 0x90;
    for (i = 0; i < var_s4 * FontHeight; i++) {
        D_801BAFD0[i] = 0;
    }
    var_s6 = ((u32)var_s5 >> 2) & 0x40;
    var_s3 = 0;
    if (var_s5 & 0x200) {
        var_s6 += 0x20;
        var_s5 &= ~0x200;
    }
#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif
    var_s5 = func_801B1EF4(var_s5 & 0xFF) & 0xFF;
    while (*var_s1 != 0) {
        var_s2 = 0;
        var_s0 = *var_s1++;
        if ('a' <= var_s0 && var_s0 <= 'z') {
            var_a0 = var_s0 + 0x8220;
        } else if ('A' <= var_s0 && var_s0 <= 'Z') {
            var_a0 = var_s0 + 0x821F;
        } else if (var_s0 == ' ') {
            var_a0 = MINSCODE;
            var_s2 = 2;
        } else {
            // load var_a0 as a big-endian value corresponding with shift-jis
            var_a0 = (var_s0 << 8);
            var_a0 += *var_s1++;
            if (var_a0 == RIGHT_DOUBLE_QUOTATION_MARK) {
                var_s1 += 2;
            }
            if (var_a0 == MINSCODE) {
                var_s0 = ' ';
                var_s2 = 2;
            }
        }
        var_a2 = g_api.func_80106A28(var_a0, 3);
        while (1) {
            if (var_s0 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontStride] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontStride];
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
            for (j = 0; j < FontStride; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontStride + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (var_a2[i * FontStride + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontStride) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_801BAFD0[var_s3 + var_s4 * i];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s3 += var_a3 + var_s2;
        if (var_s3 >= var_s4) {
            break;
        }
    }

    LoadTPage(D_801BAFD0, 0, 0, var_s6 + D_801BAFD4, var_s5 + D_801BAFD8,
              var_s4 * 2, 0x10);
    D_801BAFD0 += var_s4 * 0x10;
}

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

#ifndef HARD_LINK
#include "../../set_prim_rect.h"
#endif

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
    sprite->clut = g_ClutIds[clut];
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

u8 D_8018046C[] = {
    'a', 0x80, 0xB0, 'b',  0x90, 0xB0, 'c',  0xA0, 0xB0, 'd', 0xB0, 0xB0,
    'e', 0xC0, 0xB0, 'f',  0xD0, 0xB0, 'g',  0xE0, 0xB0, 'h', 0xF0, 0xB0,
    'i', 0x80, 0xC0, 'j',  0x90, 0xC0, 'k',  0xA0, 0xC0, 'l', 0xB0, 0xC0,
    'm', 0xC0, 0xC0, 'n',  0xD0, 0xC0, 'o',  0xE0, 0xC0, 'p', 0xF0, 0xC0,
    'q', 0x80, 0xD0, 'r',  0x90, 0xD0, 's',  0xA0, 0xD0, 't', 0xB0, 0xD0,
    'u', 0xC0, 0xD0, 'v',  0xD0, 0xD0, 'w',  0xE0, 0xD0, 'x', 0xF0, 0xD0,
    'y', 0x80, 0xE0, 'z',  0x90, 0xE0, '&',  0xA0, 0xE0, '!', 0xB0, 0xE0,
    '-', 0xC0, 0xE0, '.',  0xD0, 0xE0, '\'', 0xE0, 0xE0, '?', 0xF0, 0xE0,
    ' ', 0xE0, 0xF0, 0x00,
};

s32 func_801B2984(char ch) {
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

s32 func_801B2E5C(s32 port) {
    char cardName[32];
    struct DIRENTRY* dirent;
    s32 i;
    s32 j;
    s32 totalSize;
    s32 nBlockUsed;

    STRCPY(cardName, "BASLUS-00067DRAX00");
    totalSize = 0;
    nBlockUsed = g_MemcardInfo[port].nBlockUsed;
    dirent = &g_MemcardInfo[port].entries;
    for (i = 0; i < nBlockUsed; i++) {
        for (j = 0; j < 16; j++) {
            if (cardName[j] != dirent[i].name[j]) {
                break;
            }
        }
        if (j != 16) {
            totalSize += dirent[i].size;
        }
    }

    totalSize /= CARD_BLOCK_SIZE;
    return totalSize;
}

void HydrateSaveSummaryEntry(s32 port, s32 slot, s32 slotValue) {
    SaveData* save = (SaveData*)g_Pix;
    g_SaveSummary[port].slot[slot] = slotValue;
    g_SaveSummary[port].icon[slot] = save->info.cardIcon;
    g_SaveSummary[port].stage[slot] = save->info.stage;
    g_SaveSummary[port].roomX[slot] = save->info.roomX;
    g_SaveSummary[port].roomY[slot] = save->info.roomY;
    g_SaveSummary[port].nRoomsExplored[slot] = save->info.nRoomsExplored;
    g_SaveSummary[port].level[slot] = save->info.level;
    g_SaveSummary[port].gold[slot] = save->info.gold;
    g_SaveSummary[port].playHours[slot] = save->info.playHours;
    g_SaveSummary[port].playSeconds[slot] = save->info.playSeconds;
    g_SaveSummary[port].playMinutes[slot] = save->info.playMinutes;
    if (save->info.saveSize != sizeof(SaveData)) {
        save->info.endGameFlags = 0;
    }
    g_SaveSummary[port].kind[slot] = save->info.endGameFlags;
    g_SaveSummary[port].character[slot] = save->info.character;
    strcpy(g_SaveSummary[port].name[slot], save->info.name);
    g_IsTimeAttackUnlocked |= save->info.endGameFlags;
}

void func_801B3120(void) {
    s32* var_a0;
    s32* var_v0;
    s32* var_v1;
    s32 i;
    s32 n;

    g_MemCardRStep = 0;
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

const char D_801A7AF8[] = "\nrstep:%d,%d\n";
const char D_801A7B08[] = "retry:%d\n";
