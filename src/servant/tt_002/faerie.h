// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

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

// SFX ids
#define NA_VO_FAERIE_INTRO_LIFE 0x472    // "Thank you for giving me life"
#define NA_VO_FAERIE_INTRO_COMMAND 0x473 // "Your word is my command"
#define NA_VO_FAERIE_LETS_GO 0x476       // "Let's go!"
#define NA_VO_FAERIE_FOLLOW 0x479        // "I'll follow you anywhere"
// "There is something funny about this wall"
#define NA_VO_FAERIE_WALL_HINT 0x47A
// "This is really suspicious looking"
#define NA_VO_FAERIE_SUSPICIOUS_HINT 0x48A
#define NA_VO_FAERIE_MIST_HINT 0x48E // "If only you could transform into mist"
// "Some animals can live in complete darkness"
#define NA_VO_FAERIE_DARKNESS_HINT 0x492
#define NA_VO_FAERIE_HEALING 0x885      // "Healing!"
#define NA_VO_FAERIE_POTION 0x886       // "Potion"
#define NA_VO_FAERIE_REGENERATION 0x887 // "Regeneration"
#define NA_VO_FAERIE_NO_MEDICINE 0x888  // "No medicine left"
#define NA_SE_FAERIE_HAI 0x889
#define NA_SE_FAERIE_YEAH 0x88A
#define NA_SE_FAERIE_HA1 0x88B
#define NA_SE_FAERIE_HA2 0x88C
#define NA_SE_FAERIE_AH 0x88D
#define NA_SE_FAERIE_UHH 0x88E
#define NA_SE_FAERIE_UHH2 0x88F
#define NA_SE_FAERIE_OHH 0x890
#define NA_VO_FAERIE_OH_NO 0x891      // "OH NOOO!"
#define NA_VO_FAERIE_ARE_YOU_OK 0x892 // "Are you ok?" possibly unreachable code

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
