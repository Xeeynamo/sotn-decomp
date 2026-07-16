// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern s16* D_us_801AC288[0x180];

static u_long* D_us_80180094[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_us_801AC288),
    PAL_TERMINATE(),
};

static u_long* D_us_801800A8[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0xA0], 16),
};

static u_long* D_us_801800B8[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0xC0], 16),
    PAL_TERMINATE(),
};

static u_long* D_us_801800CC[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0], 16),
    PAL_TERMINATE(),
};

u_long* cluts[] = {
    D_us_80180094,
    D_us_801800B8,
    D_us_801800CC,
    D_us_801800A8,
};
