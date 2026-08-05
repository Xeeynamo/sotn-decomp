// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

#include "../../st/pfn_entity_update.h"

extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];

extern u8* g_SpriteSheet[];
extern u8* g_PlOvlDopBatSpritesheet[];

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
    .unk2C = g_SpriteSheet,
    .unk30 = g_PlOvlDopBatSpritesheet,
};
