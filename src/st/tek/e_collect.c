// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

extern EInit g_EInitBreakable;

#define HEART_DROP_CASTLE_FLAG 0
#include "../e_collect.h"

u16 PrizeDrops[] = {ITEMDROP_HEART_VESSEL, ITEMDROP_LIFE_VESSEL,
                    ITEMDROP_CUTLASS, 0};
