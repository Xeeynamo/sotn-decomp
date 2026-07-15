// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

extern RoomHeader g_Rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];
void func_8018E1D4();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = entityLayoutHorizontal,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = func_8018E1D4,
};

extern s16* D_8018CAA8[];
s16** spriteBanks[] = {
    NULL, D_8018CAA8, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
};

extern u16* D_80182058[0x10];
static u_long* Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80182058),
    PAL_TERMINATE(),
};

u_long* cluts[] = {
    Clut,
};
