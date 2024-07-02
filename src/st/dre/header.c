#include "dre.h"

extern RoomHeader g_Rooms[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms[];
extern GfxBank* g_GfxBanks[];
void UpdateStageEntities();

static Overlay StageOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = spriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms,
    .gfxBanks = g_GfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
};

#include "sprite_banks.h"

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

#include "layers.h"
