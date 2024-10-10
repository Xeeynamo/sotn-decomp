// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"
#include "../st_private.h"

extern u32 D_80181420[];
extern u32 D_80181764[];
static void* D_801801B8[] = {
    /* 0x1B8 */ (void*)0x00000000,
    /* 0x1BC */ (void*)0x00000000,
    /* 0x1C0 */ (void*)0x00000000,
    /* 0x1C4 */ (void*)0x00000000,
    /* 0x1C8 */ (void*)0xFFFFFFFF,
};
static void* D_801801CC[] = {
    /* 0x1CC */ (void*)0x00000004,
    /* 0x1D0 */ (void*)0x00400100,
    /* 0x1D4 */ (void*)0x00800080,
    /* 0x1D8 */ (void*)D_80181420,
    /* 0x1DC */ (void*)0x00600100,
    /* 0x1E0 */ (void*)0x00800080,
    /* 0x1E4 */ (void*)D_80181764,
    /* 0x1E8 */ (void*)0xFFFFFFFF,
};
void* OVL_EXPORT(gfxBanks)[] = {
    /* 0x1EC */ D_801801B8,
    /* 0x1F0 */ D_801801B8,
    /* 0x1F4 */ D_801801B8,
    /* 0x1F8 */ D_801801B8,
    /* 0x1FC */ D_801801B8,
    /* 0x200 */ D_801801CC,
    /* 0x204 */ D_801801B8,
    /* 0x208 */ D_801801B8,
    /* 0x20C */ D_801801B8,
    /* 0x210 */ D_801801B8,
    /* 0x214 */ D_801801B8,
    /* 0x218 */ D_801801B8,
    /* 0x21C */ D_801801B8,
    /* 0x220 */ D_801801B8,
    /* 0x224 */ D_801801B8,
    /* 0x228 */ D_801801B8,
    /* 0x22C */ D_801801B8,
    /* 0x230 */ D_801801B8,
    /* 0x234 */ D_801801B8,
    /* 0x238 */ D_801801B8,
};
