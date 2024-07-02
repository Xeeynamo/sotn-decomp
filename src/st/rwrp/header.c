#include "rwrp.h"

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

extern u16* D_80181D08[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2E00, D_80181D08),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};

#include "layers.h"
