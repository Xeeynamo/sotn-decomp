// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

#include "../../st/pfn_entity_update.h"

extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];

extern u8* doppleganger_sprites[];
extern u8* bat_form_sprites[];

AbbreviatedOverlay2 g_BossOverlay = {
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
    .unk2C = doppleganger_sprites,
    .unk30 = bat_form_sprites,
};
