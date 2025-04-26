// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* np3_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 stage_title_jp[];
extern u8 stage_placeholder[];
static u_long* np3_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_jp),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};
extern u8 e_slogra_g0[];
extern u8 e_slogra_g1[];
extern u8 e_slogra_g2[];
extern u8 e_gaibon_g0[];
extern u8 e_gaibon_g1[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_slogra_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_slogra_g1),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_slogra_g2),
    GFX_ENTRY(0x100, 0x0C0, 128, 128, e_gaibon_g0),
    GFX_ENTRY(0x100, 0x0E0, 128, 128, e_gaibon_g1),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_merman_g0[];
extern u8 e_merman_g1[];
extern u8 e_merman_g2[];
extern u8 e_merman_g3[];
extern u8 e_ghost_bat_g[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_3[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_merman_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_merman_g1),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_merman_g2),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_merman_g3),
    GFX_ENTRY(0x100, 0x0C0, 128, 128, e_ghost_bat_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_slinger_g[];
extern u8 e_bloody_zombie_g[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_4[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_slinger_g),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_bloody_zombie_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_owlknight_g0[];
extern u8 e_owlknight_g1[];
extern u8 e_owlknight_g2[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_5[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_owlknight_g0),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_owlknight_g1),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_owlknight_g2),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_bloody_zombie_g[];
extern u8 e_zombie_g[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_6[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x080, 128, 128, e_bloody_zombie_g),
    GFX_ENTRY(0x100, 0x0E0, 128, 128, e_zombie_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_gurkha_g[];
extern u8 e_explosion_g[];
static u_long* np3_gfxbank_7[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x0C0, 128, 128, e_gurkha_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    np3_gfxbank_0,
    np3_gfxbank_2,
    np3_gfxbank_3,
    np3_gfxbank_4,
    np3_gfxbank_5,
    np3_gfxbank_1,
    np3_gfxbank_6,
    np3_gfxbank_7,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
    np3_gfxbank_0,
};
