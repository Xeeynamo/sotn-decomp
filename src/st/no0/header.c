// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "../pfn_entity_update.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = (SpriteParts**)spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = rooms_layers,
    .gfxBanks = (GfxBank**)gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#ifdef VERSION_US
#include "gen/sprite_banks.h"
#include "gen/palette_def.h"
#include "gen/layers.h"
#include "gen/graphics_banks.h"
#endif
