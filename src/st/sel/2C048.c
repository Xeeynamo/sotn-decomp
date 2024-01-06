/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "sel.h"
#include "memcard.h"

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ HandleMainMenu,
    /* 0x08 */ func_801B9C80,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ NULL,
    /* 0x14 */ g_SpriteBanks,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ 0x00000000,
    /* 0x20 */ 0x00000000,
    /* 0x24 */ g_EntityGfxs,
    /* 0x28 */ func_801B60D4,
    /* 0x2C */ 0x00000000,
    /* 0x30 */ &D_8018C404,
    /* 0x34 */ 0x00000000,
    /* 0x38 */ 0x00000000,
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

typedef struct {
    const char* line1;
    const char* line2;
} StageName;

StageName D_80180128[] = {
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

void SetupFileChoose(void) {
    D_801D6B0C = 1;
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
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
    }
}

void InitMainMenuGraphics(void) {
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
    prim->blendMode = 0;

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
            prim->blendMode = BLEND_VISIBLE;
        } else {
            prim->blendMode = 4;
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
    prim->blendMode = 0;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x70);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = 0;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x60);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = 0;

    prim = prim->next;
    SetTexturedPrimRect(prim, 32, 176, 16, 16, 0xA0, 0x80);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = 0;

    D_801BAF18[7][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[7][0]];
    SetTexturedPrimRect(prim, 112, 48, 160, 48, 0, 0x50);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;

    D_801BAF18[8][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[8][0]];
    SetTexturedPrimRect(prim, 128, 72, 15, 15, 0xF0, 0xF0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x30;
    prim->blendMode = BLEND_VISIBLE;

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
        prim->blendMode = 8;
        prim = prim->next;
    }

    D_801BAF18[10][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[10][0]];
    SetTexturedPrimRect(prim, 64, 104, 32, 32, 0, 0x48);
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x204;
    prim->priority = 0x30;
    prim->blendMode = BLEND_VISIBLE;

    D_801BAF18[GFX_WND_SAVE_SUMMARY][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[11][0]];
    SetTexturedPrimRect(prim, 104, 88, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = 0;

    D_801BAF18[18][0] = g_api.AllocPrimitives(PRIM_GT4, 2);
    prim = &g_PrimBuf[D_801BAF18[18][0]];
    SetTexturedPrimRect(prim, 104, 48, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;
    prim = prim->next;
    SetTexturedPrimRect(prim, 168, 128, 48, 16, 0xB0, 0x80);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;

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
    prim->blendMode = BLEND_VISIBLE;
}

void func_801ACBE4(s32 gfxId, u16 blendMode) {
    Primitive* prim = &g_PrimBuf[D_801BAF18[gfxId][0]];
    while (prim != NULL) {
        prim->blendMode = blendMode;
        prim = prim->next;
    }
}

void MenuHideAllGfx(void) {
    s32 i;
    for (i = GFX_UNK_0; i < NUM_GFX; i++) {
        func_801ACBE4(i, 8);
    }
}

void func_801ACC7C(void) {
    s16 primIndex;
    POLY_GT4* poly;
    s32 i;

    primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
    poly = &g_PrimBuf[primIndex];
    D_801BAFC0 = primIndex;

    for (i = 0; i < 3; i++) {
        SetTexturedPrimRect(poly, i << 7, 0, 128, 240, 0, 0);
        func_801B1D88(poly);
        poly->tpage = i + 137;
        poly->clut = 0x210;
        poly->pad3 = 4;
        poly = (POLY_GT4*)poly->tag;
    }

    primIndex = g_api.AllocPrimitives(PRIM_TILE, 2);
    poly = &g_PrimBuf[primIndex];
    D_801BAFC4 = primIndex;

    for (i = 0; poly != NULL; i++) {
        poly->x0 = (i & 1) * 192;
        poly->u0 = 192;
        poly->v0 = 240;
        func_801B1CFC(poly, 255);
        poly->pad2 = 0x1FD;
        poly->pad3 = 0x51;
        poly = (POLY_GT4*)poly->tag;
    }
}

s32 func_801ACDFC(void) {
    POLY_GT4* poly = &g_PrimBuf[D_801BAFC4];
    s32 var_s1 = poly->r0;

    var_s1 -= 16;
    if (var_s1 < 0) {
        var_s1 = 0;
    }

    func_801B1CFC(poly, var_s1);
    func_801B1CFC(poly->tag, var_s1);

    if (var_s1 == 0) {
        do {
            poly = &g_PrimBuf[D_801BAFC4];
            poly->pad3 = 8;
        } while (0);
        poly = (POLY_GT4*)poly->tag;
        poly->pad3 = 8;
    } else {
        return 0;
    }
}

s32 func_801ACEC0(void) {
    POLY_GT4* poly = &g_PrimBuf[D_801BAFC4];
    s32 var_s0 = poly->r0;

    var_s0 += 0x10;
    poly->pad3 = 0x51;

    if (var_s0 > 255) {
        var_s0 = 255;
    }

    func_801B1CFC(poly, var_s0);
    poly = (POLY_GT4*)poly->tag;
    poly->pad3 = 0x51;
    func_801B1CFC(poly, var_s0);

    if (g_api.func_80131F68()) {
        return 0;
    } else {
        return var_s0 == 255;
    }
}

void func_801ACF7C(void) {
    func_801B1ED0();
    func_801B25D4(D_801A75A0, 0);
    func_801B25D4(D_801A75C0, 1);
}

extern const char D_801A7620[]; // ""
extern const char D_801A76A4[]; // "Richter"
extern const char D_801A76AC[]; // "Clear"
extern const char D_801A76B4[]; // "Replay"
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
        func_801B25D4(D_801A7620, textId + 1);
    } while (0);
    if (g_SaveSummary[port].character[slot]) {
        strSaveKind = D_801A76A4;
    } else if (g_SaveSummary[port].kind[slot] & SAVE_FLAG_CLEAR) {
        strSaveKind = D_801A76AC;
    } else if (g_SaveSummary[port].kind[slot] & SAVE_FLAG_REPLAY) {
        strSaveKind = D_801A76B4;
    } else {
        strSaveKind = D_801A7620;
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
