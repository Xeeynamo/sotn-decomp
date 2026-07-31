// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

extern struct SpriteParts* g_EntitySpriteBank15[];
extern u8 g_Stage16SpriteBank16[];
extern u8 g_Stage16SpriteBank17[];
extern u8 g_Stage16SpriteBank18[];
extern u8 g_Stage16SpriteBank19[];
extern u8 g_Stage16SpriteBank20[];
extern u8 g_Stage16SpriteBank21[];
extern u8 g_Stage16SpriteBankSkeletonBeast[];
extern u8 g_Stage16SpriteBankSpecter[];
extern u8 g_Stage16SpriteBankGargoyle[];
extern u8 g_Stage16SpriteBankSkeletonBreeder[];
extern u8 g_Stage16SpriteBankWillOWisp[];

void* g_Stage16SpriteBanks[] = {
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
    g_Stage16SpriteBank16,
    g_Stage16SpriteBank17,
    g_Stage16SpriteBank18,
    g_Stage16SpriteBank19,
    g_Stage16SpriteBank20,
    g_Stage16SpriteBank21,
    g_Stage16SpriteBankSkeletonBeast,
    g_Stage16SpriteBankSpecter,
    g_Stage16SpriteBankGargoyle,
    g_Stage16SpriteBankSkeletonBreeder,
    g_Stage16SpriteBankWillOWisp,
    NULL,
};
