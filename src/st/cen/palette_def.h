// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* D_8018658C[0x80];
extern u16* D_8018678C[0x80];
extern u16* e_maria_cen_p[0x10];
extern u16* e_elevator_cen_p[0x20];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018658C),
    PAL_BULK(0x2080, D_8018678C),
    PAL_BULK(0x2100, e_maria_cen_p),
    PAL_BULK(0x2230, e_elevator_cen_p),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
