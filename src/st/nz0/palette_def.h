// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* e_blood_skeleton_p[0x40];
extern u16* e_slinger_p[0x10];
extern u16* e_axe_knight_p[0x40];
extern u16* e_bloody_zombie_p[0x30];
extern u16* e_skeleton_p[0x10];
extern u16* e_skelerang_p[0x30];
extern u16* e_table_with_alembic_p[0x40];
extern u16* e_table_blue_flame_p[0x40];
extern u16* e_table_with_globe_p[0x40];
extern u16* e_cloche_p[0xA0];
extern u16* e_slogra_p[0x30];
extern u16* e_gaibon_p[0x80];
extern u16* e_sealed_door_p[0x50];
extern u16* e_maria_nz0_p[0x10];
extern u16* D_8019665C[0x80];
extern u16* D_8019685C[0x80];
extern u16* e_explosion_p[0x100];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, e_blood_skeleton_p),
    PAL_BULK(0x2040, e_slinger_p),
    PAL_BULK(0x2050, e_axe_knight_p),
    PAL_BULK(0x2090, e_bloody_zombie_p),
    PAL_BULK(0x20C0, e_skeleton_p),
    PAL_BULK(0x20D0, e_skelerang_p),
    PAL_BULK(0x2110, e_table_with_alembic_p),
    PAL_BULK(0x2150, e_table_blue_flame_p),
    PAL_BULK(0x2190, e_table_with_globe_p),
    PAL_BULK(0x21D0, e_cloche_p),
    PAL_BULK(0x2270, e_slogra_p),
    PAL_BULK(0x22A0, e_gaibon_p),
    PAL_BULK(0x2320, e_sealed_door_p),
    PAL_BULK(0x2370, e_maria_nz0_p),
    PAL_BULK(0x2380, D_8019665C),
    PAL_BULK(0x2400, D_8019685C),
    PAL_BULK(0x2E00, e_explosion_p),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
