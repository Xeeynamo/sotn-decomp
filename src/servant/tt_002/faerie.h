// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

typedef struct {
    s16 animIndex;
    s16 zPriorityFlag;
} FaerieAnimIndex;

typedef struct
{
    s32 comparator;
    s16* data;
} RankedLookup_s16;

typedef union 
{
    s32 arr[4];
    RankedLookup_s16 lookup[2];
} FaerieUnkRankedLookup_6504;

