#include "dre.h"

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

extern SpriteParts* D_80190168[];

static SpriteParts** SpriteBanks[] = {
    NULL, D_80190168, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL, NULL, NULL, NULL, NULL, NULL,
};

extern u16* D_8018AEA8[0x50];
extern u16* D_8018AF48[0x80];
extern u16* D_8018B148[0x80];
extern u16* D_8018B348[0x80];
extern u16* D_8018ABE8[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018AEA8),
    PAL_BULK(0x2080, D_8018AF48),
    PAL_BULK(0x2100, D_8018B148),
    PAL_BULK(0x2180, D_8018B348),
    PAL_BULK(0x2E00, D_8018ABE8),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
