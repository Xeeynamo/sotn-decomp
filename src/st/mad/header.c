// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_pStTileset[];
void UpdateStageEntities();
void func_8018E1D4();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = SpriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = g_TileLayers,
    .gfxBanks = g_pStTileset,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = func_8018E1D4,
};

extern SpriteParts* D_8018CAA8[];

static SpriteParts** SpriteBanks[] = {
    NULL, D_8018CAA8, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
};

extern u16* D_80182058[0x10];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80182058),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
