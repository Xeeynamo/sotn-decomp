// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void OVL_EXPORT(InitRoomEntities)(s32 objLayoutId);

extern RoomHeader OVL_EXPORT(rooms)[];
extern SpriteParts* OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];

Overlay OVL_EXPORT(Overlay) = {
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
