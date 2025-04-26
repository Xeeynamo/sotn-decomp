// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16* bn_pal_gremlin[0x40];
extern u16* bn_pal_salem_witch[0x20];
extern u16* bn_pal_thornweed_corpseweed[0x40];
extern u16* bn_pal_venus_weed[0x290];
extern u16* bn_pal_salem_witch_projectiles[0x100];
static u_long* pal_def[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, bn_pal_gremlin),
    PAL_BULK(0x2040, bn_pal_salem_witch),
    PAL_BULK(0x2060, bn_pal_thornweed_corpseweed),
    PAL_BULK(0x20A0, bn_pal_venus_weed),
    PAL_BULK(0x2E00, bn_pal_salem_witch_projectiles),
    PAL_TERMINATE(),
};
u_long* OVL_EXPORT(cluts)[] = {pal_def};
