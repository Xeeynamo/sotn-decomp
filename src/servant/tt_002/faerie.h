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
    /* 0x885 */ SFX_FAERIE_HEALING = 0x885, // "Healing!"
    /* 0x886 */ SFX_FAERIE_POTION,          // "Potion"
    /* 0x887 */ SFX_FAERIE_REGENERATION,    // "Regeneration"
    /* 0x888 */ SFX_FAERIE_NO_MEDICINE,     // "No medicine left"
    /* 0x889 */ SFX_FAERIE_HAMMER_A, // when using hammer on stoned Alucard
    /* 0x88A */ SFX_FAERIE_HAMMER_B,
    /* 0x88B */ SFX_FAERIE_HAMMER_C,
    /* 0x88C */ SFX_FAERIE_HAMMER_D,
    /* 0x88D */ SFX_FAERIE_FALL_OFF_A, // falling off Alucard's shoulder
    /* 0x88E */ SFX_FAERIE_FALL_OFF_B,
    /* 0x88F */ SFX_FAERIE_FALL_OFF_C,
    /* 0x890 */ SFX_FAERIE_FALL_OFF_D,
    /* 0x891 */ SFX_FAERIE_OH_NO,      // "OH NOOO!" (death reaction)
    /* 0x892 */ SFX_FAERIE_ARE_YOU_OK, // "Are you ok?" (possibly unused?)
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

extern SpriteParts* g_FaerieSpriteParts[];
extern s32* g_FaerieIntroRandomizer[];
extern s32* g_SfxEventRandomizer[];
