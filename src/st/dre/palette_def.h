// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* e_succubus_p[0x50];
extern u16* D_8018AF48[0x80];
extern u16* D_8018B148[0x80];
extern u16* D_8018B348[0x80];
extern u16* D_8018ABE8[0x100];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, e_succubus_p),
    PAL_BULK(0x2080, D_8018AF48),
    PAL_BULK(0x2100, D_8018B148),
    PAL_BULK(0x2180, D_8018B348),
    PAL_BULK(0x2E00, D_8018ABE8),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
