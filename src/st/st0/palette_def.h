// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* e_dracula_p[0x70];
extern u16* stage_title_p[0x20];
extern u16* e_breakables_p[0x80];
extern u16* D_8019AD70[0x30];
extern u16* e_smoke_p[0x50];
extern u16* D_8019AE70[0x60];
extern u16* e_secret_stairs_p[0x70];
extern u16* D_8019A830[0x80];
extern u16* D_8019AA30[0x80];
extern u16* bg_moon_p[0x100];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, e_dracula_p),
    PAL_BULK(0x2100, stage_title_p),
    PAL_BULK(0x2120, e_breakables_p),
    PAL_BULK(0x21A0, D_8019AD70),
    PAL_BULK(0x21D0, e_smoke_p),
    PAL_BULK(0x2220, D_8019AE70),
    PAL_BULK(0x2280, e_secret_stairs_p),
    PAL_BULK(0x2300, D_8019A830),
    PAL_BULK(0x2480, D_8019AA30),
    PAL_BULK(0x2800, bg_moon_p),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
