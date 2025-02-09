// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

static u_long* wrp_gfxbank_0[] = {
    (u_long*)GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 stage_title_jp[];
extern u8 stage_placeholder[];
static u_long* wrp_gfxbank_1[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_jp),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};

void* OVL_EXPORT(gfxBanks)[] = {
    /* 0x1EC */ wrp_gfxbank_0,
    /* 0x1F0 */ wrp_gfxbank_0,
    /* 0x1F4 */ wrp_gfxbank_0,
    /* 0x1F8 */ wrp_gfxbank_0,
    /* 0x1FC */ wrp_gfxbank_0,
    /* 0x200 */ wrp_gfxbank_1,
    /* 0x204 */ wrp_gfxbank_0,
    /* 0x208 */ wrp_gfxbank_0,
    /* 0x20C */ wrp_gfxbank_0,
    /* 0x210 */ wrp_gfxbank_0,
    /* 0x214 */ wrp_gfxbank_0,
    /* 0x218 */ wrp_gfxbank_0,
    /* 0x21C */ wrp_gfxbank_0,
    /* 0x220 */ wrp_gfxbank_0,
    /* 0x224 */ wrp_gfxbank_0,
    /* 0x228 */ wrp_gfxbank_0,
    /* 0x22C */ wrp_gfxbank_0,
    /* 0x230 */ wrp_gfxbank_0,
    /* 0x234 */ wrp_gfxbank_0,
    /* 0x238 */ wrp_gfxbank_0,
};
