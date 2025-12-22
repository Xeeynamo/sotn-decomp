// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"

#define OVL_EXPORT(x) TT_000_##x

typedef struct {
    s32 delayFrames;
    s32 angleStep;
    s32 additionalBatCount;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
} BatAbilityValues;
