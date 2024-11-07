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
    s16 unk0;
    s16 unk1;
    s16 unk2;
    s16 unk3;
    s16 unk4;
    s16 unk5;
    s16 unk6;
} FaerieAbilityStats;
