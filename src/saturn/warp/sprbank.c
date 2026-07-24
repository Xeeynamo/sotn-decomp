// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>

extern struct SpriteParts* g_EntitySpriteBank15[];
extern struct SpriteParts* g_WarpSpriteBank16[];

void* g_WarpSpriteBanks[18] = {
    &g_SaturnSharedSpriteBank0Resource,
    &g_SaturnSharedSpriteBank1Resource,
    &g_SaturnSharedSpriteBank2Resource,
    &g_SaturnSharedSpriteBank3Resource,
    &g_SaturnSharedSpriteBank4Resource,
    &g_SaturnSharedSpriteBank5Resource,
    &g_SaturnSharedSpriteBank6Resource,
    &g_SaturnSharedSpriteBank7Resource,
    &g_SaturnSharedSpriteBank8Resource,
    &g_SaturnSharedSpriteBank9Resource,
    &g_SaturnSharedSpriteBank10Resource,
    &g_SaturnSharedSpriteBank11Resource,
    &g_SaturnSharedSpriteBank13Resource,
    &g_SaturnSharedSpriteBank12Resource,
    &g_SaturnSharedSpriteBank14Resource,
    g_EntitySpriteBank15,
    g_WarpSpriteBank16,
    NULL,
};
