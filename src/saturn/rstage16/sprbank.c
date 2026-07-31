// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

extern struct SpriteParts* g_EntitySpriteBank15[];
extern u8 g_RStage16SpriteBank16[];
extern u8 g_RStage16SpriteBank17[];
extern u8 g_RStage16SpriteBank18[];
extern u8 g_RStage16SpriteBankWraith[];
extern u8 g_RStage16SpriteBankWight[];
extern u8 g_RStage16SpriteBankGargoyle[];
extern u8 g_RStage16SpriteBank22[];
extern u8 g_RStage16SpriteBank23[];

void* g_RStage16SpriteBanks[] = {
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
    g_RStage16SpriteBank16,
    g_RStage16SpriteBank17,
    g_RStage16SpriteBank18,
    g_RStage16SpriteBankWraith,
    g_RStage16SpriteBankWight,
    g_RStage16SpriteBankGargoyle,
    g_RStage16SpriteBank22,
    g_RStage16SpriteBank23,
    NULL,
};
