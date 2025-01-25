// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>
#include <sfx.h>

typedef enum {
    FAERIE_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    FAERIE_MODE_USE_LIFE_APPLE,
    FAERIE_MODE_USE_HAMMER,
    FAERIE_MODE_USE_UNCURSE,
    FAERIE_MODE_USE_ANTIVENOM,
    FAERIE_MODE_USE_ELEMENTAL_RESIST,
    FAERIE_MODE_USE_POTION,
    FAERIE_MODE_ADDITIONAL_INIT,

    FAERIE_SUBENTITY_WINGS,
    FAERIE_MODE_SIT_ON_SHOULDER,
    FAERIE_MODE_OFFER_HINT,
    FAERIE_SUBENTITY_LIFE_APPLE = SERVANT_ID(13),
    FAERIE_EVENT_SFX_PASSTHROUGH,
    FAERIE_SUBENTITY_ITEM,
} EntityIDs;

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

// These are all SFX keys that are loaded from TT_002.VB/VH
typedef enum {
    FAERIE_HEALING = 0x885, // "Healing!"
    FAERIE_POTION,          // "Potion"
    FAERIE_REGENERATION,    // "Regeneration"
    FAERIE_NO_MEDICINE,     // "No medicine left"
    FAERIE_HAI,
    FAERIE_YEAH,
    FAERIE_HA1,
    FAERIE_HA2,
    FAERIE_AH,
    FAERIE_UHH,
    FAERIE_UHH2,
    FAERIE_OHH,
    FAERIE_OH_NO,     // "OH NOOO!"
    FAERIE_ARE_YOU_OK // "Are you ok?" possibly unreachable code
} FaerieSfxId;

typedef struct {
    s16 animIndex;
    s16 wingsInBackZ;
} FaerieWingAnimationParams;

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
    ServantSfxEventDesc* hint;
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

extern SpriteParts* g_FaerieSpriteParts[];
extern s32* g_FaerieIntroRandomizer[];
extern s32* g_SfxEventRandomizer[];
