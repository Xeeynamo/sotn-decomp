// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef NOSEDEVIL_H
#define NOSEDEVIL_H
#include "common.h"
#include <servant.h>
#include <sfx.h>

typedef enum {
    NOSEDEVIL_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    NOSEDEVIL_MODE_BASIC_ATTACK,
    NOSEDEVIL_MODE_SPECIAL_ATTACK,
    NOSEDEVIL_MODE_UNUSED_D4,
    NOSEDEVIL_MODE_UNUSED_D5,
    NOSEDEVIL_MODE_PRESS_SWITCH,
    NOSEDEVIL_SUBENTITY_SWITCH,
    NOSEDEVIL_MODE_ADDITIONAL_INIT,
    NOSEDEVIL_EVENT_SFX_PASSTHROUGH,
    NOSEDEVIL_SPECIAL_ATTACK_UPDATE,
    NOSEDEVIL_MODE_UNK_DB,
    NOSEDEVIL_MODE_UNK_DC,
    NOSEDEVIL_MODE_UNK_DD,
    NOSEDEVIL_MODE_UNK_DE
} EntityIds;

typedef struct {
    s32 timer;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
    s32 maxEnemyAxisDelta;
} NosedevilAbilityStats;

typedef struct {
    s32 animationIndex;
    s32 sfxIndex;
    s32 abilityId;
} NosedevilAttackInfo;

extern s32 g_PlaySfxStep;
extern SpriteParts* g_NosedevilSpriteParts[];

extern AnimationFrame* g_NosedevilAnimationFrames[];

#endif
