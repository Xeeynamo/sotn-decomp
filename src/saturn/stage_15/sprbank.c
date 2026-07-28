// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

extern struct SpriteParts* g_EntitySpriteBank15[];
extern u8 g_Stage15SpriteBank16[];
extern u8 g_Stage15SpriteBank17[];
extern u8 g_Stage15SpriteBank18[];
extern u8 g_Stage15SpriteBank19[];
extern u8 g_Stage15SpriteBank20[];
extern u8 g_Stage15SpriteBank21[];
extern u8 g_Stage15SpriteBank22[];
extern u8 g_Stage15SpriteBankSkeletonBeast[];
extern u8 g_Stage15SpriteBankRedGargoyle[];
extern u8 g_Stage15SpriteBankSkeletonBreeder[];
extern u8 g_Stage15SpriteBankHumanFaceTree[];
extern u8 g_Stage15SpriteBankWaterLeaper[];
extern u8 g_Stage15SpriteBankVenusManTrap[];
extern u8 g_Stage15SpriteBank29[];
extern u8 g_Stage15SpriteBankGardener[];
extern u8 g_Stage15SpriteBankSkeletonLeader[];
extern u8 g_Stage15SpriteBank32[];

void* g_Stage15SpriteBanks[] = {
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
    g_Stage15SpriteBank16,
    g_Stage15SpriteBank17,
    g_Stage15SpriteBank18,
    g_Stage15SpriteBank19,
    g_Stage15SpriteBank20,
    g_Stage15SpriteBank21,
    g_Stage15SpriteBank22,
    g_Stage15SpriteBankSkeletonBeast,
    g_Stage15SpriteBankRedGargoyle,
    g_Stage15SpriteBankSkeletonBreeder,
    g_Stage15SpriteBankHumanFaceTree,
    g_Stage15SpriteBankWaterLeaper,
    g_Stage15SpriteBankVenusManTrap,
    g_Stage15SpriteBank29,
    g_Stage15SpriteBankGardener,
    g_Stage15SpriteBankSkeletonLeader,
    g_Stage15SpriteBank32,
    NULL,
};
