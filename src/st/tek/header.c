// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 layoutId);
extern RoomHeader D_80182EA4[];
extern SpriteParts* D_8018002C[];
extern u_long* D_801801A8[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef D_8018037C[];
extern GfxBank* D_80180600[];
void UpdateStageEntities(void);

AbbreviatedOverlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = D_80182EA4,
    .spriteBanks = D_8018002C,
    .cluts = D_801801A8,
    .objLayoutHorizontal = entityLayoutHorizontal,
    .tileLayers = D_8018037C,
    .gfxBanks = D_80180600,
    .UpdateStageEntities = UpdateStageEntities,
};
