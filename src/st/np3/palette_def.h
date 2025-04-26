// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* e_explosion_p[0x100];
extern u16* e_skyswirl_p[0x8C0];
extern u16* e_merman_p[0x60];
extern u16* D_80195B74[0x20];
extern u16* D_80195BB4[0x20];
extern u16* D_80195BF4[0x20];
extern u16* D_80195C34[0x20];
extern u16* D_80195C74[0x20];
extern u16* D_80195CB4[0x20];
extern u16* D_80195CF4[0x20];
extern u16* D_80195D34[0x20];
extern u16* D_80195D74[0x20];
extern u16* D_80195DB4[0x20];
extern u16* D_80195DF4[0x20];
extern u16* D_80195E34[0x20];
extern u16* D_80195E74[0x20];
extern u16* D_80195EB4[0x20];
extern u16* D_80195EF4[0x130];
extern u16* e_slinger_p[0x30];
extern u16* e_ghost_bat_p[0x30];
extern u16* e_owlknight_p[0x70];
extern u16* e_zombie_p[0x30];
extern u16* e_bloody_zombie_p[0x30];
extern u16* e_slogra_p[0x90];
extern u16* e_gaibon_p[0x80];
extern u16* e_gurkha_p[0x90];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x0D00, e_explosion_p),
    PAL_BULK(0x2000, e_skyswirl_p),
    PAL_BULK(0x28C0, e_merman_p),
    PAL_BULK(0x2920, D_80195B74),
    PAL_BULK(0x2940, D_80195BB4),
    PAL_BULK(0x2960, D_80195BF4),
    PAL_BULK(0x2980, D_80195C34),
    PAL_BULK(0x29A0, D_80195C74),
    PAL_BULK(0x29C0, D_80195CB4),
    PAL_BULK(0x29E0, D_80195CF4),
    PAL_BULK(0x2A00, D_80195D34),
    PAL_BULK(0x2A20, D_80195D74),
    PAL_BULK(0x2A40, D_80195DB4),
    PAL_BULK(0x2A60, D_80195DF4),
    PAL_BULK(0x2A80, D_80195E34),
    PAL_BULK(0x2AA0, D_80195E74),
    PAL_BULK(0x2AC0, D_80195EB4),
    PAL_BULK(0x2B20, D_80195EF4),
    PAL_BULK(0x2C50, e_slinger_p),
    PAL_BULK(0x2C80, e_ghost_bat_p),
    PAL_BULK(0x2CB0, e_owlknight_p),
    PAL_BULK(0x2D30, e_zombie_p),
    PAL_BULK(0x2D60, e_bloody_zombie_p),
    PAL_BULK(0x2D90, e_slogra_p),
    PAL_BULK(0x2E20, e_gaibon_p),
    PAL_BULK(0x2EA0, e_gurkha_p),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
