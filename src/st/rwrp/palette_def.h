// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* D_80181D08[0x100];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2E00, D_80181D08),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
