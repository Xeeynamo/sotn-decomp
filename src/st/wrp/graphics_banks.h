// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* wrp_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 stage_title_jp[];
extern u8 stage_placeholder[];
static u_long* wrp_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_jp),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_1,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
    wrp_gfxbank_0,
};
