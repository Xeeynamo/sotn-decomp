// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 layoutId);
extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];
void UpdateStageEntities(void);

AbbreviatedOverlay g_Overlay = {
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
