// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* chi_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 bn_gfx_stage_name_en[];
extern u8 bn_gfx_stage_name_jp_lg[];
static u_long* chi_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, bn_gfx_stage_name_en),
    GFX_ENTRY(0x100, 0x060, 128, 128, bn_gfx_stage_name_jp_lg),
    GFX_TERMINATE(),
};
extern u8 bn_gfx_gremlin[];
static u_long* chi_gfxbank_2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, bn_gfx_gremlin),
    GFX_TERMINATE(),
};
extern u8 bn_gfx_gremlin[];
static u_long* chi_gfxbank_3[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, bn_gfx_gremlin),
    GFX_TERMINATE(),
};
extern u8 bn_gfx_salem_witch_1[];
extern u8 bn_gfx_salem_witch_2[];
extern u8 bn_gfx_salem_witch_4[];
extern u8 bn_gfx_salem_witch_5[];
extern u8 bn_gfx_salem_witch_3[];
static u_long* chi_gfxbank_4[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, bn_gfx_salem_witch_1),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, bn_gfx_salem_witch_2),
    GFX_ENTRY(0x180, 0x080, 128, 128, bn_gfx_salem_witch_4),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, bn_gfx_salem_witch_5),
    GFX_ENTRY(0x100, 0x1C0, 128, 128, bn_gfx_salem_witch_3),
    GFX_TERMINATE(),
};
extern u8 bn_gfx_thornweed_corpseweed[];
extern u8 bn_gfx_venus_weed_1[];
extern u8 bn_gfx_venus_weed_2[];
static u_long* chi_gfxbank_5[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x0C0, 128, 128, bn_gfx_thornweed_corpseweed),
    GFX_ENTRY(0x100, 0x100, 128, 128, bn_gfx_venus_weed_1),
    GFX_ENTRY(0x100, 0x120, 128, 128, bn_gfx_venus_weed_2),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    chi_gfxbank_0,
    chi_gfxbank_1,
    chi_gfxbank_2,
    chi_gfxbank_4,
    chi_gfxbank_5,
    chi_gfxbank_3,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
    chi_gfxbank_0,
};
