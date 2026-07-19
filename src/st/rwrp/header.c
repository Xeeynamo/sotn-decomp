// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"
#ifdef VERSION_PSP

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);

Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
};
#else

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "gen/sprite_banks.h"
#include "gen/palette_def.h"
#include "gen/layers.h"
#include "gen/graphics_banks.h"
#endif
