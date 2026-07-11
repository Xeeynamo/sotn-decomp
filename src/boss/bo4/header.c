// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long** OVL_EXPORT(gfxBanks)[];

extern u8* doppleganger_sprites[0x34C];
extern u8* bat_form_sprites[6];

extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];

AbbreviatedOverlay2 OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = OVL_EXPORT(HitDetection),
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal),
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = OVL_EXPORT(UpdateStageEntities),
    .unk2C = doppleganger_sprites,
    .unk30 = bat_form_sprites,
};
