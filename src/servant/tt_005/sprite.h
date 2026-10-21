// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SPRITE_H
#define SPRITE_H
#include "common.h"
#include <servant.h>
#include <sfx.h>

typedef enum {
    SPRITE_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    SPRITE_MODE_USE_LIFE_APPLE,
    SPRITE_MODE_USE_HAMMER,
    SPRITE_MODE_USE_UNCURSE,
    SPRITE_MODE_USE_ANTIVENOM,
    SPRITE_MODE_USE_ELEMENTAL_RESIST,
    SPRITE_MODE_USE_POTION,
    SPRITE_MODE_ADDITIONAL_INIT,
    SPRITE_SUBENTITY_WINGS,
    SPRITE_MODE_SIT_ON_SHOULDER,
    SPRITE_MODE_OFFER_HINT,
    SPRITE_SUBENTITY_LIFE_APPLE = SERVANT_ID(13),
    SPRITE_EVENT_SFX_PASSTHROUGH,
    SPRITE_SUBENTITY_ITEM,
} EntityID;

#define ROOM_STATE_TO_HINT_OFFSET 2
#define ROOM_SPECIAL_STATE_UNK1 1
#define ROOM_SPECIAL_STATE_DARKNESS 2
#define ROOM_SPECIAL_STATE_MIST 3
#define ROOM_SPECIAL_STATE_WALL_HINT1 4
#define ROOM_SPECIAL_STATE_WALL_HINT2 6
#define ROOM_SPECIAL_STATE_WALL_HINT3 7
#define ROOM_SPECIAL_STATE_WALL_HINT4 8
#define ROOM_SPECIAL_STATE_WALL_HINT5 10
#define ROOM_SPECIAL_STATE_SUS_HINT1 5
#define ROOM_SPECIAL_STATE_SUS_HINT2 9
#define ROOM_SPECIAL_STATE_SUS_HINT3 11

typedef struct {
    s16 animIndex;
    s16 wingsInBackZ;
} SpriteWingAnimationParams;

typedef struct {
    s16 timer;
    s16 lifeAppleChance;
    s16 hammerChance;
    s16 uncurseChance;
    s16 antivenomChance;
    s16 resistChance;
    s16 healChance;
} SpriteAbilityStats;

typedef struct {
    s32 healing;
    s32 potion;
    s32 regeneration;
    s32 noMedicine;
    s32 ohNo;
} SpriteSfx;

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
    /* 0x12 */ s16 priority;
    /* 0x14 */ s16 drawMode;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u32 flags;
} ItemPrimitiveParams; // size = 0x1C

extern AnimationFrame* g_SpriteAnimationFrames[];

#endif
