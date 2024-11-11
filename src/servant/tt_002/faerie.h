// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

typedef struct {
    s16 animIndex;
    s16 zPriorityFlag;
} FaerieAnimIndex;

// It looks like most if not all of the ability stats for faerie are
// essentially % chance for abilities to trigger.
typedef struct {
    s16 timer;
    s16 unk1;
    s16 hammerChance;
    s16 uncurseChance;
    s16 antivenomChance;
    s16 unkChance5;
    s16 healChance;
} FaerieAbilityStats;

typedef struct {
    s32 left;
    s32 top;
    FaerieUnkA4* unk8;
} Unk2CB0;
