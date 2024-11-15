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
    s16 lifeAppleChance;
    s16 hammerChance;
    s16 uncurseChance;
    s16 antivenomChance;
    s16 resistChance;
    s16 healChance;
} FaerieAbilityStats;

typedef struct {
    s32 left;
    s32 top;
    FaerieSfxEventDesc* hint;
} HintTriggerMap;

typedef struct {
    s32 healing;
    s32 potion;
    s32 regeneration;
    s32 noMedicine;
    s32 ohNo;
    s32 areYouOk;
} FaerieSfx;

typedef struct {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 w;
    /* 0x0A */ s16 h;
    /* 0x0C */ s16 r;
    /* 0x0E */ s16 g;
    /* 0x10 */ s16 b;
    /* 0x12 */ u16 priority;
    /* 0x14 */ s16 drawMode;
    /* 0x16 */ s16 : 16;
    /* 0x18 */ u32 flags;
} ItemPrimitiveParams; // size = 0x1C
