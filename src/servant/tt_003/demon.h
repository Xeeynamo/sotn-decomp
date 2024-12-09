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

// SFX Ids
#define NA_VO_DEMON_INTRO_COMMAND 0x4E8 // Command me, my lord and master
#define NA_VO_DEMON_INTRO_READY 0x4ED   // I'm ready to serve, master
#define NA_VO_DEMON_SWITCH_1                                                   \
    0x4EE // Hmm, a switch.  Why don't I press it and see?
#define NA_VO_DEMON_SWITCH_2 0x4EF // Hmm, this switch hasn't been pressed yet

#define NA_SE_DEMON_GRUNT_1 0x89E         // he-ya
#define NA_SE_DEMON_GRUNT_2 0x89F         // huh
#define NA_SE_DEMON_GRUNT_3 0x8A0         // hrr
#define NA_VO_DEMON_TAKE_THAT 0x8A1       // "Take that" - possibly unused
#define NA_VO_DEMON_DIE 0x8A2             // "DIE!" - Used for cleave attack
#define NA_VO_DEMON_FIRE_SPEAR 0x8A3      // "Fire Spear"
#define NA_VO_DEMON_ICE_SPEAR 0x8A4       // "Ice Spear"
#define NA_VO_DEMON_THUNDER_SPEAR 0x8A5   // "Thunder Spear"
#define NA_VO_DEMON_LIGHTNING_SPEAR 0x8A6 // "Lightning spear"

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
