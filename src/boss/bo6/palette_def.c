// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

// This table is not currently represented by the asset config.
extern s16* D_us_8019E9A0[0x300];
extern s16* D_us_8019EFA0[0x100];
extern s16* D_us_8019F3A0[0x80];
extern s16* D_us_8019F1A0[0x80];
extern s16* D_us_8019F5A0[0x80];

static u_long* D_us_80180094[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2200, D_us_8019E9A0),
    PAL_BULK(0x2500, D_us_8019EFA0),
    PAL_BULK(0x2600, D_us_8019F3A0),
    PAL_BULK(0x2680, D_us_8019F1A0),
    PAL_BULK(0x2700, D_us_8019F5A0),
    PAL_TERMINATE(),
};

u_long* cluts[] = {
    D_us_80180094,
};
