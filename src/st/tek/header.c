// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

void func_801BF5A4(void);
void func_801BF9B0(void);
void func_801C1950(void);
void func_801C17D8(s32 layoutId);
extern RoomHeader D_80182EA4[];
extern SpriteParts* D_8018002C[];
extern u_long* D_801801A8[];
extern LayoutEntity* D_80180630[];
extern RoomDef D_8018037C[];
extern GfxBank* D_80180600[];
void func_801BF888(void);

AbbreviatedOverlay g_Overlay = {
    .Update = func_801BF5A4,
    .HitDetection = func_801BF9B0,
    .UpdateRoomPosition = func_801C1950,
    .InitRoomEntities = func_801C17D8,
    .rooms = D_80182EA4,
    .spriteBanks = D_8018002C,
    .cluts = D_801801A8,
    .objLayoutHorizontal = D_80180630,
    .tileLayers = D_8018037C,
    .gfxBanks = D_80180600,
    .UpdateStageEntities = func_801BF888,
};
