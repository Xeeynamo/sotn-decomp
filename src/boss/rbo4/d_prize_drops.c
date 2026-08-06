// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#if defined(VERSION_PSP)
u16 PrizeDrops[ZERO_LEN] = {};
#else
u16 PrizeDrops[] = {
    ITEMDROP_SMALL_HEART,
    ITEMDROP_LIFE_VESSEL,
    0x0020,
    ITEMDROP_SMALL_HEART,
    ITEMDROP_SMALL_HEART,
    ITEMDROP_LIFE_VESSEL,
    ITEMDROP_SMALL_HEART,
    ITEMDROP_GOLD_3,
    ITEMDROP_GOLD_7,
    0xFFFC,
    0xFFF0,
    ITEMDROP_SMALL_HEART,
};
#endif
