// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal),
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "gen/sprite_banks.h"
// #include "gen/palette_def.h"
// #include "gen/layers.h"
// #include "gen/graphics_banks.h"
