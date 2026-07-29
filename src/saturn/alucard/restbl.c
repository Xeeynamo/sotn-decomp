// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource AlucardSpriteResources[];
extern u16 g_EntitySpriteBank15[];

SaturnSpriteResource* AlucardSpriteResourceTable[13] = {
    &AlucardSpriteResources[0],  &AlucardSpriteResources[1],
    &AlucardSpriteResources[3],  &AlucardSpriteResources[2],
    &AlucardSpriteResources[4],  &AlucardSpriteResources[5],
    &AlucardSpriteResources[6],  &AlucardSpriteResources[7],
    &AlucardSpriteResources[8],  &AlucardSpriteResources[9],
    &AlucardSpriteResources[10], &AlucardSpriteResources[11],
    &AlucardSpriteResources[12],
};

u16* AlucardExternalSpriteBanks[3] = {
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
};

u32 AlucardPlayerGraphicsPadding = 0;
