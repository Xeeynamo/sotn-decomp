// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

extern struct SpriteParts* g_EntitySpriteBank15[];
extern u8 g_RStage15SpriteBank16[];
extern u8 g_RStage15SpriteBank17[];
extern u8 g_RStage15SpriteBank18[];
extern u8 g_RStage15SpriteBank19[];
extern u8 g_RStage15SpriteBank20[];
extern u8 g_RStage15SpriteBank21[];
extern u8 g_RStage15SpriteBank22[];
extern u8 g_RStage15SpriteBank23[];
extern u8 g_RStage15SpriteBankEfreet[];
extern u8 g_RStage15SpriteBank25[];
extern u8 g_RStage15SpriteBank26[];
extern u8 g_RStage15SpriteBankCopperArmor[];
extern u8 g_RStage15SpriteBankSkeletonGuardian[];

void* g_RStage15SpriteBanks[] = {
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
    g_RStage15SpriteBank16,
    g_RStage15SpriteBank17,
    g_RStage15SpriteBank18,
    g_RStage15SpriteBank19,
    g_RStage15SpriteBank20,
    g_RStage15SpriteBank21,
    g_RStage15SpriteBank22,
    g_RStage15SpriteBank23,
    g_RStage15SpriteBankEfreet,
    g_RStage15SpriteBank25,
    g_RStage15SpriteBank26,
    g_RStage15SpriteBankCopperArmor,
    g_RStage15SpriteBankSkeletonGuardian,
    NULL,
};
