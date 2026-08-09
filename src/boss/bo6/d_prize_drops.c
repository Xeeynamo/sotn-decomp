// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

#ifdef VERSION_PSP
u16 PrizeDrops[ZERO_LEN] = {};
#else
u16 PrizeDrops[] = {
    0x4000,
    ITEMDROP_SMALL_HEART,
};
#endif
