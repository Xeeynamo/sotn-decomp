// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"
#include "../pfn_entity_update.h"

extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
#if defined(VERSION_PSP) || defined(VERSION_PC)
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
#else
    .objLayoutHorizontal = entityLayoutHorizontal,
#endif
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};
