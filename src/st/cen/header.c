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
    .unk3C = NULL,
};

extern SpriteParts* D_8018C754[];
extern SpriteParts* D_8018C60C[];
extern SpriteParts* D_8018CED8[];

static SpriteParts** SpriteBanks[] = {
    NULL,
    D_8018C754,
    D_8018C60C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    D_8018CED8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

extern u16* D_8018658C[];
extern u16* D_8018678C[];
extern u16* D_8018698C[];
extern u16* D_801869AC[];

static u16** D_801800A0[] = {
    0x00000005,
    0x00002000,
    0x00000080,
    D_8018658C,
    0x00002080,
    0x00000080,
    D_8018678C,
    0x00002100,
    0x00000010,
    D_8018698C,
    0x00002230,
    0x00000020,
    D_801869AC,
    (u16**)-1,
};

static void* Cluts[] = {
    D_801800A0,
};
