// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

extern u8* doppleganger_sprites[0x34C];
extern u8* bat_form_sprites[6];

extern s16** spriteBanks[];
extern u_long* cluts[];

AbbreviatedOverlay2 OVL_EXPORT(Overlay) = {
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
    .unk2C = doppleganger_sprites,
    .unk30 = bat_form_sprites,
};
