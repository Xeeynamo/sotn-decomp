// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#ifdef VERSION_PSP
    #include "../pfn_entity_update.h"

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
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

void Update();
void HitDetection();
void UpdateRoomPosition();
void InitRoomEntities(s32 objLayoutId);

extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern u_long** gfxBanks[];
extern RoomDef rooms_layers[];
extern RoomHeader rooms[];

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
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
