// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DEMON_H
#define DEMON_H
#include "common.h"
#include <servant.h>

typedef enum {
    DEMON_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    DEMON_MODE_BASIC_ATTACK,
    DEMON_MODE_SPECIAL_ATTACK,
    DEMON_MODE_UNUSED_D4,
    DEMON_MODE_UNUSED_D5,
    DEMON_MODE_PRESS_SWITCH,
    DEMON_SUBENTITY_SWITCH,
    DEMON_MODE_ADDITIONAL_INIT,
    DEMON_EVENT_SFX_PASSTHROUGH,
    DEMON_SPECIAL_ATTACK_UPDATE,
    DEMON_MODE_UNK_DB,
    DEMON_MODE_UNK_DC,
    DEMON_MODE_UNK_DD,
    DEMON_MODE_UNK_DE
} EntityIds;

typedef enum {
    DEMON_INTRO_COMMAND = 0x4E8, // Command me, my lord and master
    DEMON_INTRO_READY = 0x4ED,   // I'm ready to serve, master
    DEMON_SWITCH_1,        // Hmm, a switch.  Why don't I press it and see?
    DEMON_SWITCH_2,        // Hmm, this switch hasn't been pressed yet
    DEMON_GRUNT_1 = 0x89E, // he-ya
    DEMON_GRUNT_2,         // huh
    DEMON_GRUNT_3,         // hrr
    DEMON_TAKE_THAT,       // "Take that" - possibly unused
    DEMON_DIE,             // "DIE!" - Used for cleave attack
    DEMON_FIRE_SPEAR,      // "Fire Spear"
    DEMON_ICE_SPEAR,       // "Ice Spear"
    DEMON_THUNDER_SPEAR,   // "Thunder Spear"
    DEMON_LIGHTNING_SPEAR  // "Lightning spear"
} DemonSfxId;

typedef struct {
    s32 timer;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
    s32 maxEnemyAxisDelta;
} DemonAbilityStats;

typedef struct {
    s32 animationIndex;
    s32 sfxIndex;
    s32 abilityId;
} DemonAttackInfo;

#endif
