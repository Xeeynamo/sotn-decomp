// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long** OVL_EXPORT(gfxBanks)[];

static Overlay OVL_EXPORT(Overlay) = {
    .Update = OVL_EXPORT(Update),
    .HitDetection = OVL_EXPORT(HitDetection),
    .UpdateRoomPosition = OVL_EXPORT(UpdateRoomPosition),
    .InitRoomEntities = OVL_EXPORT(InitRoomEntities),
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = NULL,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = OVL_EXPORT(UpdateStageEntities),
};

#include "gen/sprite_banks.h"
#include "gen/palette_def.h"
#include "gen/layers.h"
#include "gen/graphics_banks.h"
