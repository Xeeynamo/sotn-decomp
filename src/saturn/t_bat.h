// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_T_BAT_H
#define SATURN_T_BAT_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"
#include "sattypes.h"
#include "inc_asm.h"
#include <saturn_sprite.h>

/* Declarations moved here by tools/saturn/move_declarations.py */
void DestroyServantEntity(Entity* self);
void func_060D0A64(Entity* self);
void UpdateBatAttackMode(Entity* self);
void UpdateServantDefault(Entity* self);
void ServantInit(s32 mode);
extern struct SpriteParts* g_ServantSpriteParts[]; // 0x060D19FC
extern SaturnSpriteResource g_BatTextureResource;
extern SaturnSpriteImage g_BatTextureSlices[25];
/* End moved declarations */

#endif
