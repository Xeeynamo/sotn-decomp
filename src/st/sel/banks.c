// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"

extern s16* D_8018DBD4[];
extern s16* D_8018EFB4[];
extern s16* D_8018DC30[];
extern s16* D_8018E3B4[];
s16** g_SpriteBanks[] = {
    NULL, D_8018DBD4, D_8018EFB4, D_8018DC30, D_8018E3B4, NULL, NULL, NULL,
    NULL, NULL,       NULL,       NULL,       NULL,       NULL, NULL, NULL,
    NULL, NULL,       NULL,       NULL,       NULL,       NULL, NULL, NULL,
};

extern u16 D_8018CD54[0x30];
extern u16 D_8018CDB4[0x100];
extern u16 D_8018D5D4[0x300];
extern u16 D_8018CFB4[0x80];
extern u16 D_8018D1B4[0x80];
extern u16 D_8018D3B4[0x80];
extern u16 D_8018D5B4[0x10];
extern u16 D_80180764[0x10];
extern u16 D_80180784[0x10];
extern u16 D_801807A4[0x10];
extern u16 D_801807C4[0x10];
extern u16 D_801807E4[0x10];
extern u16 D_80180804[0x10];
extern u16 D_801808E4[0x100];

static u16 D_801805FC[] = {
#include "gen/D_801805FC.h"
};

static u_long* D_8018061C[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018CD54),
    PAL_BULK(0x2100, D_8018CDB4),
    PAL_TERMINATE(),
};

static u_long* D_8018063C[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x1960, D_801805FC),
    PAL_BULK(0x2100, D_8018D5D4),  PAL_BULK(0x2400, D_8018CFB4),
    PAL_BULK(0x2480, D_8018D1B4),  PAL_BULK(0x2500, D_8018D3B4),
    PAL_BULK(0x2580, D_8018D5B4),  PAL_TERMINATE(),
};

static u_long* D_8018068C[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x1960, D_801805FC),
    PAL_TERMINATE(),
};

static u_long* D_801806A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2030, D_80180764),
    PAL_BULK(0x2040, D_80180804),
    PAL_TERMINATE(),
};

static u_long* D_801806C0[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 2),
    PAL_GLOW_INFO(0x2030, 16),
    PAL_GLOW_DATA(D_80180784),
    PAL_GLOW_DATA(D_80180764),
    PAL_TERMINATE(),
};

static u_long* D_801806D8[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 1),
    PAL_GLOW_INFO(0x2040, 16),
    PAL_GLOW_DATA(D_801807A4),
    PAL_GLOW_DATA(D_801807C4),
    PAL_GLOW_DATA(D_801807E4),
    PAL_GLOW_DATA(D_80180804),
    PAL_TERMINATE(),
};

static u_long* D_801806F8[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2200, D_801808E4),
    PAL_TERMINATE(),
};

u_long* g_Cluts[] = {
    D_8018061C, D_801806A0, D_801806C0, D_801806D8,
    D_801806F8, D_8018063C, D_8018068C,
};

extern u8 D_80192228[];
extern u8 D_80193358[];
extern u8 D_80194018[];
extern u8 D_80195274[];

u_long* D_80180728[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x40, 128, 128, D_80192228),
    GFX_ENTRY(0x180, 0x60, 128, 128, D_80193358),
    GFX_ENTRY(0x100, 0x80, 128, 128, D_80194018),
    GFX_ENTRY(0x100, 0xA0, 128, 128, D_80195274),
    GFX_TERMINATE(),
};

GfxBank* g_EntityGfxs[] = {D_80180728};

static u16 D_80180764[] = {
#include "gen/D_80180764.h"
};

static u16 D_80180784[] = {
#include "gen/D_80180784.h"
};

static u16 D_801807A4[] = {
#include "gen/D_801807A4.h"
};

static u16 D_801807C4[] = {
#include "gen/D_801807C4.h"
};

static u16 D_801807E4[] = {
#include "gen/D_801807E4.h"
};

static u16 D_80180804[] = {
#include "gen/D_80180804.h"
};
