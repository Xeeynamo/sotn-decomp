/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "sel.h"

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ TestCollisions,
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

void func_801AC048(void) {
    D_801D6B0C = 1;
    D_801D6B08 = 0;
    D_801BC3E0 = 0;
    D_801D6B04 = 0;
    D_801BC3D8 = 0;
    D_801BC3DC = 0;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2C048", func_801AC084);
#else
// Those arrays are weird. They do not store s32 but they are used as such.
extern s32 D_80180068[];
extern s32 D_80180088[];
extern s32 D_801800A8[];
extern s32 D_801800C8[];
extern s32 D_801800E8[];
extern s32 D_80180108[];

void func_801AC084(s32 arg0, s32 ypos) {
    POLY_GT4* poly = &D_80086FEC[D_801BAF18[arg0].unk0];
    s32 i;

    for (i = 0; i < 8; i++) {
        poly->x0 = D_80180068[i] + 0x68;
        poly->y0 = D_80180088[i] + 0x58 + ypos;
        poly->u0 = D_801800A8[i];
        poly->v0 = D_801800C8[i];
        poly->u1 = D_801800E8[i];
        poly->tpage = 0xC;
        poly->clut = 0x200;
        poly->pad2 = 0x11;
        poly->pad3 = 8;
        poly->v1 = D_80180108[i];
        poly = (POLY_GT4*)poly->tag;
    }
}
#endif

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2C048", func_801AC174);

void func_801ACBE4(s32 arg0, u16 arg1) {
    POLY_GT4* poly = &D_80086FEC[D_801BAF18[arg0].unk0];
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
    s16 firstPolygonIndex;
    POLY_GT4* poly;
    s32 i;

    firstPolygonIndex = g_api.AllocPolygons(4, 3);
    poly = &D_80086FEC[firstPolygonIndex];
    D_801BAFC0 = firstPolygonIndex;

    for (i = 0; i < 3; i++) {
        func_801B26A0(poly, i << 7, 0, 128, 240, 0, 0);
        func_801B1D88(poly);
        poly->tpage = i + 137;
        poly->clut = 0x210;
        poly->pad3 = 4;
        poly = (POLY_GT4*)poly->tag;
    }

    firstPolygonIndex = g_api.AllocPolygons(1, 2);
    poly = &D_80086FEC[firstPolygonIndex];
    D_801BAFC4 = firstPolygonIndex;

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
    POLY_GT4* poly = &D_80086FEC[D_801BAFC4];
    s32 var_s1 = poly->r0;

    var_s1 -= 0x10;
    if (var_s1 < 0) {
        var_s1 = 0;
    }

    func_801B1CFC(poly, var_s1);
    func_801B1CFC((POLY_GT4*)poly->tag, var_s1);

    if (!var_s1) {
        do {
            poly = &D_80086FEC[D_801BAFC4];
            poly->pad3 = 8;
        } while (0);
        poly = (POLY_GT4*)poly->tag;
        poly->pad3 = 8;
    } else {
        return 0;
    }
}

s32 func_801ACEC0(void) {
    POLY_GT4* poly = &D_80086FEC[D_801BAFC4];
    s32 var_s0 = poly->r0;

    var_s0 += 0x10;
    poly->pad3 = 0x51;

    if (var_s0 > 255) {
        var_s0 = 255;
    }

    func_801B1CFC(poly, var_s0);
    poly = (POLY_GT4*)poly->tag;
    poly->pad3 = 0x51;
    func_801B1CFC((POLY_GT4*)poly, var_s0);

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2C048", func_801ACFBC);

void PrintFileSelectPlaceName(s32 arg0, s32 arg1, s32 y) {
    const s32 x = 160;
    const s32 row1y = 0;
    const s32 row2y = 8;
    const s32 tge = 1;
    volatile u32 pad; // !FAKE:

    s32* new_var2 = &D_801BC958[arg0 * 0xEA];
    s32 idx = new_var2[arg1] * 2;
    DrawImages8x8(D_80180128[idx], x, y + row1y, tge);
    DrawImages8x8(D_8018012C[idx], x, y + row2y, tge);
}

void func_801AD1D0(void) {
    DrawImages8x8(D_801803BC, 52, 196, 1);
    DrawImages8x8(D_801803C0, 52, 212, 1);
}

void func_801AD218(void) {
    DrawImages8x8(D_801803C0, 52, 196, 1);
    DrawImages8x8(D_801803BC, 52, 212, 1);
}
