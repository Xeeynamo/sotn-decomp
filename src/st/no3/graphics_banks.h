// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* no3_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 stage_title_jp[];
extern u8 stage_placeholder[];
static u_long* no3_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_jp),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};
extern u8 e_death_g0[];
extern u8 e_death_g1[];
extern u8 e_death_g2[];
extern u8 e_skyswirl_g0[];
extern u8 e_skyswirl_g1[];
static u_long* no3_gfxbank_2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, e_death_g0),
    GFX_ENTRY(0x100, 0x060, 128, 128, e_death_g1),
    GFX_ENTRY(0x180, 0x040, 128, 128, e_death_g2),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_skyswirl_g0),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_skyswirl_g1),
    GFX_TERMINATE(),
};
extern u8 e_merman_g0[];
extern u8 e_merman_g1[];
extern u8 e_merman_g2[];
extern u8 e_merman_g3[];
extern u8 e_ghost_bat_g[];
extern u8 e_explosion_g[];
static u_long* no3_gfxbank_3[] = {
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
extern u8 e_explosion_g[];
static u_long* no3_gfxbank_4[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_slinger_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_warg_rider_g0[];
extern u8 e_warg_rider_g1[];
extern u8 e_warg_rider_g2[];
extern u8 e_warg_rider_g3[];
extern u8 e_explosion_g[];
static u_long* no3_gfxbank_5[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_warg_rider_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_warg_rider_g1),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_warg_rider_g2),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_warg_rider_g3),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
extern u8 e_warg_rider_g0[];
extern u8 e_warg_rider_g1[];
extern u8 e_warg_rider_g2[];
extern u8 e_warg_rider_g3[];
extern u8 e_warg_rider_g4[];
extern u8 e_zombie_g[];
extern u8 e_explosion_g[];
static u_long* no3_gfxbank_6[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, e_warg_rider_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_warg_rider_g1),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_warg_rider_g2),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_warg_rider_g3),
    GFX_ENTRY(0x100, 0x0C0, 128, 128, e_warg_rider_g4),
    GFX_ENTRY(0x100, 0x0E0, 128, 128, e_zombie_g),
    GFX_ENTRY(0x180, 0x120, 128, 128, e_explosion_g),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    no3_gfxbank_0,
    no3_gfxbank_2,
    no3_gfxbank_3,
    no3_gfxbank_4,
    no3_gfxbank_5,
    no3_gfxbank_1,
    no3_gfxbank_6,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
    no3_gfxbank_0,
};
