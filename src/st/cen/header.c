#include "cen.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* D_8018019C[];
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
    .gfxBanks = D_8018019C,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
};

extern SpriteParts* D_8018C754[];
extern SpriteParts* D_8018C60C[];
extern SpriteParts* D_8018CED8[];

static SpriteParts** SpriteBanks[] = {
    NULL, D_8018C754, D_8018C60C, NULL,       NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL,       D_8018CED8, NULL, NULL, NULL, NULL,
    NULL, NULL,       NULL,       NULL,       NULL, NULL, NULL, NULL,
};

extern u16* D_8018658C[0x80];
extern u16* D_8018678C[0x80];
extern u16* D_8018698C[0x10];
extern u16* D_801869AC[0x20];

static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x2000, D_8018658C),
    PAL_BULK(0x2080, D_8018678C),  PAL_BULK(0x2100, D_8018698C),
    PAL_BULK(0x2230, D_801869AC),  PAL_TERMINATE(),
};

static void* Cluts[] = {
    D_801800A0,
};
