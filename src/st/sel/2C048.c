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

void SetupFileChoose(void) {
    D_801D6B0C = 1;
    g_InputCursorPos = 0;
    D_801BC3E0 = 0;
    D_801D6B04 = 0;
    g_MemCardSelectorX = 0;
    g_MemCardSelectorY = 0;
}

// These arrays are weird. They do not store s32 but they are used as such.
extern s32 D_80180068[];
extern s32 D_80180088[];
extern s32 D_801800A8[];
extern s32 D_801800C8[];
extern s32 D_801800E8[];
extern s32 D_80180108[];

void func_801AC084(s32 arg0, s32 ypos) {
    Primitive* prim = &g_PrimBuf[D_801BAF18[arg0][0]];
    s32 i;
    for (i = 0; i < 8; i++) {
        prim->x0 = D_80180068[i] + 0x68;
        prim->y0 = D_80180088[i] + 0x58 + ypos;
        prim->u0 = D_801800A8[i];
        prim->v0 = D_801800C8[i];
        prim->u1 = D_801800E8[i];
        prim->v1 = D_80180108[i];
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
    D_801BAF18[0][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    i = 0;
    y = 0;
    x = -0x20;
    prim = &g_PrimBuf[D_801BAF18[0][0]];
    func_801B26A0(prim, 216, 16, 144, 72, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x201;
    prim->priority = 0x10;
    prim->blendMode = 0;

    for (; i < 5; i++) {
        D_801BAF18[i + 1][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
        prim = &g_PrimBuf[D_801BAF18[i + 1][0]];
        func_801B26A0(prim, x, y, 0x7F, 0x1F, D_80180040[i], D_80180054[i]);
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
    func_801B26A0(prim, 32, 176, 16, 16, 0xA0, 0x50);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = 0;

    prim = prim->next;
    func_801B26A0(prim, 32, 176, 16, 16, 0xA0, 0x70);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = 0;

    prim = prim->next;
    func_801B26A0(prim, 32, 176, 16, 16, 0xA0, 0x60);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = 0;

    prim = prim->next;
    func_801B26A0(prim, 32, 176, 16, 16, 0xA0, 0x80);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->blendMode = 0;

    D_801BAF18[7][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[7][0]];
    func_801B26A0(prim, 112, 48, 160, 48, 0, 0x50);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;

    D_801BAF18[8][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[8][0]];
    func_801B26A0(prim, 128, 72, 15, 15, 0xF0, 0xF0);
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
    func_801B26A0(prim, 64, 104, 32, 32, 0, 0x48);
    func_801B1D88(prim);
    prim->tpage = 0xD;
    prim->clut = 0x204;
    prim->priority = 0x30;
    prim->blendMode = BLEND_VISIBLE;

    D_801BAF18[11][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801BAF18[11][0]];
    func_801B26A0(prim, 104, 88, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;

    D_801BAF18[12][0] = g_api.AllocPrimitives(PRIM_SPRT, 8);
    func_801AC084(0xC, 0);

    D_801BAF18[13][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
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

    D_801BAF18[14][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
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
    func_801B26A0(prim, 104, 48, 176, 80, 0, 0);
    func_801B1D88(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->blendMode = BLEND_VISIBLE;
    prim = prim->next;
    func_801B26A0(prim, 168, 128, 48, 16, 0xB0, 0x80);
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

void func_801ACBE4(s32 arg0, u16 arg1) {
    POLY_GT4* poly = &g_PrimBuf[D_801BAF18[arg0][0]];
    while (poly != NULL) {
        poly->pad3 = arg1;
        poly = (POLY_GT4*)poly->tag;
    }
}

void func_801ACC3C(void) {
    s32 i;
    for (i = 0; i < 21; i++) {
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
        func_801B26A0(poly, i << 7, 0, 128, 240, 0, 0);
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
    if (g_SaveSummary[port].isRichter[slot]) {
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

    s32 placeId = g_SaveSummary[port].place[slot] * 2;
    DrawImages8x8(D_80180128[placeId], x, y + row1y, tge);
    DrawImages8x8(D_8018012C[placeId], x, y + row2y, tge);
}

void func_801AD1D0(void) {
    DrawImages8x8(D_801803BC, 52, 196, 1);
    DrawImages8x8(D_801803C0, 52, 212, 1);
}

void func_801AD218(void) {
    DrawImages8x8(D_801803C0, 52, 196, 1);
    DrawImages8x8(D_801803BC, 52, 212, 1);
}
