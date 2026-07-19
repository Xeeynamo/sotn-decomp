// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_MariaSpriteResources[13];
extern struct SpriteParts* g_EntitySpriteBank15[];

void* g_MariaSpriteBanks[18] = {
    &g_MariaSpriteResources[0],
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    &g_MariaSpriteResources[1],
    &g_MariaSpriteResources[2],
    &g_MariaSpriteResources[3],
    &g_MariaSpriteResources[8],
    &g_MariaSpriteResources[4],
    &g_MariaSpriteResources[6],
    &g_MariaSpriteResources[5],
    &g_MariaSpriteResources[7],
    &g_MariaSpriteResources[9],
    &g_MariaSpriteResources[10],
    &g_MariaSpriteResources[11],
    &g_MariaSpriteResources[12],
    NULL,
};
