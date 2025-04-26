// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* cen_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 e_maria_cen_g0[];
extern u8 e_maria_cen_g1[];
static u_long* cen_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_maria_cen_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_maria_cen_g1),
    GFX_TERMINATE(),
};
extern u8 stage_title_jp[];
extern u8 stage_placeholder[];
static u_long* cen_gfxbank_2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_jp),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};
extern u8 e_elevator_cen_g[];
static u_long* cen_gfxbank_3[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_elevator_cen_g),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    cen_gfxbank_0,
    cen_gfxbank_1,
    cen_gfxbank_3,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_2,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
    cen_gfxbank_0,
};
