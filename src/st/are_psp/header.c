// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../are/are.h"
#include "../pfn_entity_update.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern SpriteParts* OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities(void);

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
};
