// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

#if defined(VERSION_PSP)
u16 PrizeDrops[ZERO_LEN] = {};
#else
u16 PrizeDrops[] = {ITEMDROP_SMALL_HEART, ITEMDROP_SMALL_HEART};
#endif
