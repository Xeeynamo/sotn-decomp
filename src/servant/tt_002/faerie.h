// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

typedef struct {
    s16 animIndex;
    s16 zPriorityFlag;
} FaerieAnimIndex;

// Ranked Lookup Table Macros
#define RANKED_LOOKUP_TABLE(name) s32 name[]
#define RANKED_LOOKUP_COMPARATOR(array, index) array[index * 2]
#define RANKED_LOOKUP_S16_DATA(array, index) (s16*)array[index * 2 + 1]
#define RANKED_LOOKUP_VALUE(array, index) array[index * 2 + 1]
