// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* D_80184EE0[0x80];
extern u16* D_801850E0[0x80];
extern u16* D_801852E0[0x10];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80184EE0),
    PAL_BULK(0x2080, D_801850E0),
    PAL_BULK(0x2100, D_801852E0),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
