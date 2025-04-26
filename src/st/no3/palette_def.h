// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* e_explosion_p[0x100];
extern u16* e_skyswirl_p[0x8C0];
extern u16* e_merman_p[0x60];
extern u16* D_80197918[0x20];
extern u16* D_80197958[0x20];
extern u16* D_80197998[0x20];
extern u16* D_801979D8[0x20];
extern u16* D_80197A18[0x20];
extern u16* D_80197A58[0x20];
extern u16* D_80197A98[0x20];
extern u16* D_80197AD8[0x20];
extern u16* D_80197B18[0x20];
extern u16* D_80197B58[0x20];
extern u16* D_80197B98[0x20];
extern u16* D_80197BD8[0x20];
extern u16* D_80197C18[0x20];
extern u16* D_80197C58[0x20];
extern u16* D_80197C98[0x130];
extern u16* e_slinger_p[0x30];
extern u16* e_ghost_bat_p[0x30];
extern u16* e_warg_rider_p[0x80];
extern u16* e_zombie_p[0x30];
extern u16* e_death_p[0x30];
extern u16* D_80198118[0x80];
extern u16* D_80198318[0x80];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x0D00, e_explosion_p),
    PAL_BULK(0x2000, e_skyswirl_p),
    PAL_BULK(0x28C0, e_merman_p),
    PAL_BULK(0x2920, D_80197918),
    PAL_BULK(0x2940, D_80197958),
    PAL_BULK(0x2960, D_80197998),
    PAL_BULK(0x2980, D_801979D8),
    PAL_BULK(0x29A0, D_80197A18),
    PAL_BULK(0x29C0, D_80197A58),
    PAL_BULK(0x29E0, D_80197A98),
    PAL_BULK(0x2A00, D_80197AD8),
    PAL_BULK(0x2A20, D_80197B18),
    PAL_BULK(0x2A40, D_80197B58),
    PAL_BULK(0x2A60, D_80197B98),
    PAL_BULK(0x2A80, D_80197BD8),
    PAL_BULK(0x2AA0, D_80197C18),
    PAL_BULK(0x2AC0, D_80197C58),
    PAL_BULK(0x2B20, D_80197C98),
    PAL_BULK(0x2C50, e_slinger_p),
    PAL_BULK(0x2C80, e_ghost_bat_p),
    PAL_BULK(0x2CB0, e_warg_rider_p),
    PAL_BULK(0x2D30, e_zombie_p),
    PAL_BULK(0x2D60, e_death_p),
    PAL_BULK(0x2E00, D_80198118),
    PAL_BULK(0x2E80, D_80198318),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
