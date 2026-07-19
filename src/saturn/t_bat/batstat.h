#ifndef SATURN_T_BAT_STAT_H
#define SATURN_T_BAT_STAT_H

#include "sattypes.h"

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 clut;
    s16 tpage;
    s16 texLeft;
    s16 texTop;
    s16 texRight;
    s16 texBottom;
} BatSpriteData;

typedef struct {
    s32 delayFrames;
    s32 angleStep;
    s32 additionalBatCount;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
} BatAbilityValues;

extern BatSpriteData g_BatSpriteData[4];
extern BatAbilityValues g_BatAbilityStats[10];

#endif
