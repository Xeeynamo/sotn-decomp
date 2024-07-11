#ifndef COLLIDER_H
#define COLLIDER_H

#include "types.h"

typedef enum {
    EFFECT_SOLID = 1 << 0,
    EFFECT_UNK_0002 = 1 << 1,
    EFFECT_QUICKSAND = 1 << 2,
    EFFECT_WATER = 1 << 3,
    EFFECT_MIST_ONLY = 1 << 4,
    EFFECT_UNK_0020 = 1 << 5,
    // Used when you jump from below to a platform. You can drop below.
    EFFECT_SOLID_FROM_ABOVE = 1 << 6,
    // Doesn't collide when falling on it but you cannot go back up.
    EFFECT_SOLID_FROM_BELOW = 1 << 7,
    EFFECT_UNK_0100 = 1 << 8,
    EFFECT_UNK_0200 = 1 << 9,
    EFFECT_UNK_0400 = 1 << 10,
    EFFECT_UNK_0800 = 1 << 11,
    EFFECT_UNK_1000 = 1 << 12,
    EFFECT_UNK_2000 = 1 << 13,
    EFFECT_UNK_4000 = 1 << 14,
    EFFECT_UNK_8000 = 1 << 15,

    // Aggregate helpers below:
    EFFECT_NOTHROUGH = EFFECT_SOLID | EFFECT_QUICKSAND,
    EFFECT_NOTHROUGH_PLUS = EFFECT_SOLID | EFFECT_UNK_0002 | EFFECT_QUICKSAND
} ColliderEffectFlags;

typedef struct Collider {
    /* 0x00 */ u32 effects;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} Collider; /* size=0x24 */

#endif // COLLIDER_H
