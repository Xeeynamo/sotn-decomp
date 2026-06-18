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

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 clut;
    /* 0x0A */ s16 tpage;
    /* 0x0C */ s16 texLeft;
    /* 0x0E */ s16 texTop;
    /* 0x10 */ s16 texRight;
    /* 0x12 */ s16 texBottom;
} BatSpriteData; /* size=0x14 */
