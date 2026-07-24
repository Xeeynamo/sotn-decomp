// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>

#define DECLARE_SPRITE_BANK(index)                                             \
    extern struct SpriteParts* g_Stage02SpriteBank##index[]

DECLARE_SPRITE_BANK(28);
DECLARE_SPRITE_BANK(29);
DECLARE_SPRITE_BANK(30);
DECLARE_SPRITE_BANK(31);
DECLARE_SPRITE_BANK(32);
DECLARE_SPRITE_BANK(33);

extern SaturnSpriteResource entityRedEyeBustData;
extern SaturnSpriteResource g_Stage02TableWithGlobeResource;
extern SaturnSpriteResource g_Stage02LifeMaxTankResource;
extern SaturnSpriteResource g_Stage02BlueFlameTableResource;
extern SaturnSpriteResource g_Stage02SubweaponContainerResource;
extern SaturnSpriteResource g_Stage02SubweaponContainerPaletteResource;
extern SaturnSpriteResource g_Stage02ElevatorResource;
extern SaturnSpriteResource g_Stage02ElevatorPaletteResource;
extern SaturnSpriteResource g_Stage02Entity74Resource0;
extern SaturnSpriteResource g_Stage02Entity74Resource1;
extern SaturnSpriteResource g_Stage02MariaNpcResource;
extern SaturnSpriteResource g_Stage02SpriteBank17Resource;
extern struct SpriteParts* g_EntitySpriteBank15[];

void* g_Stage02SpriteBanks[35] = {
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
    &entityRedEyeBustData,
    &g_Stage02SpriteBank17Resource,
    &g_Stage02TableWithGlobeResource,
    &g_Stage02LifeMaxTankResource,
    &g_Stage02BlueFlameTableResource,
    &g_Stage02SubweaponContainerResource,
    &g_Stage02SubweaponContainerPaletteResource,
    &g_Stage02ElevatorResource,
    &g_Stage02ElevatorPaletteResource,
    &g_Stage02Entity74Resource0,
    &g_Stage02Entity74Resource1,
    &g_Stage02MariaNpcResource,
    g_Stage02SpriteBank28,
    g_Stage02SpriteBank29,
    g_Stage02SpriteBank30,
    g_Stage02SpriteBank31,
    g_Stage02SpriteBank32,
    g_Stage02SpriteBank33,
    NULL,
};
