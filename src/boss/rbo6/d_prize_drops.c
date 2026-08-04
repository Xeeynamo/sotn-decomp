// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

#ifdef VERSION_PSP
u16 PrizeDrops[ZERO_LEN] = {};
#else
u16 PrizeDrops[] = {
    ITEMDROP_STAR_FLAIL,
    0x0203,
    0x0303,
    0x0403,
    0x0503,
    0x0603,
    0x0703,
    0x0803,
    0x0903,
    0x0A03,
    0x0B03,
    0x0C03,
    0x0D03,
    ITEMDROP_GREAT_SWORD,
};
#endif
