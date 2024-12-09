// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DEMON_H
#define DEMON_H
#include "common.h"
#include <servant.h>

typedef enum {
    DEMON_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    DEMON_MODE_UNK_D2,
    DEMON_MODE_UNK_D3,
    DEMON_MODE_UNK_D4,
    DEMON_MODE_UNK_D5,
    DEMON_MODE_UNK_D6,
    DEMON_SUBENTITY_UNK_D7,
    DEMON_MODE_UNK_D8,
    DEMON_EVENT_SFX_PASSTHROUGH,
    DEMON_EVENT_ATTACK_UPDATE,
    DEMON_MODE_UNK_DB,
    DEMON_MODE_UNK_DC,
    DEMON_MODE_UNK_DD,
    DEMON_MODE_UNK_DE
} EntityIds;

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
