// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"

#define OVL_EXPORT(x) TT_001_##x

typedef struct {
    s32 delayFrames;
    s32 spellId;
    s32 makeBadAttacks;
} GhostAbilityValues;
