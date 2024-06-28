#include "rwrp.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_GfxBanks[];
void UpdateStageEntities();

static Overlay StageOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = SpriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = g_TileLayers,
    .gfxBanks = g_GfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
};

extern SpriteParts* D_80186FE8[];
extern SpriteParts* D_80187090[];

static SpriteParts** SpriteBanks[] = {
    NULL, D_80186FE8, D_80187090, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL,       NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL,       NULL, NULL, NULL, NULL, NULL,

};

extern u16* D_80181D08[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2E00, D_80181D08),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
