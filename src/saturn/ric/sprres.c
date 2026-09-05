// SPDX-License-Identifier: AGPL-3.0-or-later
#include "gen/sprres.h"

extern struct SpriteParts* g_EntitySpriteBank15[];

void* g_RichterSpriteBanks[17] = {
    &g_RichterSpriteResources[0],
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    &g_RichterSpriteResources[1],
    &g_RichterSpriteResources[2],
    &g_RichterSpriteResources[3],
    &g_RichterSpriteResources[4],
    &g_RichterSpriteResources[5],
    &g_RichterSpriteResources[6],
    &g_RichterSpriteResources[7],
    &g_RichterSpriteResources[8],
    &g_RichterSpriteResources[9],
    g_EntitySpriteBank15,
    g_EntitySpriteBank15,
    NULL,
};
