// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"
#ifdef VERSION_PSP
#include "../../st/pfn_entity_update.h"

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);

AbbreviatedOverlay g_BossOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};
#else

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

AbbreviatedOverlay MAR_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = entityLayoutHorizontal,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "gen/sprite_banks.h"
#include "gen/palette_def.h"
#include "gen/layers.h"
#include "gen/graphics_banks.h"
#endif
