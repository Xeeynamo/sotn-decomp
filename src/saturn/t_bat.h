// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_T_BAT_H
#define SATURN_T_BAT_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"
#include "sattypes.h"
#include "inc_asm.h"
#include <saturn_sprite.h>

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 clut;
    s16 tpage;
    s16 texLeft;
    s16 texTop;
    s16 texRight;
    s16 texBottom;
} BatSpriteData;

typedef struct {
    s32 delayFrames;
    s32 angleStep;
    s32 additionalBatCount;
    s32 minimumEnemyHp;
    s32 makeBadAttacks;
} BatAbilityValues;

/* Declarations moved here by tools/saturn/move_declarations.py */
void DestroyServantEntity(Entity* self);
void func_060D0A64(Entity* self);
void UpdateBatAttackMode(Entity* self);
void UpdateServantDefault(Entity* self);
void ServantInit(s32 mode);
void PlaySfx(s32 sfxId);
/* End moved declarations */

#endif
