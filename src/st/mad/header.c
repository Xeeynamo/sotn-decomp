#include "mad.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_pStTileset[];
void UpdateStageEntities();
void func_8018E1D4();

static Overlay StageOverlay = {
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
    .unk3C = func_8018E1D4,
};

extern SpriteParts* D_8018CAA8[];

static SpriteParts** SpriteBanks[] = {
    NULL, D_8018CAA8, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
};

extern u16* D_80182058[];

static u16** Clut[] = {
    0x5, 0x2000, 0x10, D_80182058, (u16**)-1,
};

static void* Cluts[] = {
    Clut,
};
