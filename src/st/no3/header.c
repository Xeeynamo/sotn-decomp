#include "no3.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_GfxBanks[];
void UpdateStageEntities();

static AbbreviatedOverlay StageOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = SpriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = g_TileLayers,
    .gfxBanks = g_GfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

extern SpriteParts* D_801AEA68[];
extern SpriteParts* D_801B009C[];
extern SpriteParts* D_801AF754[];
extern SpriteParts* D_801AFB3C[];
extern SpriteParts* D_801B077C[];
extern SpriteParts* D_801B0B80[];
extern SpriteParts* D_801B57C0[];
extern SpriteParts* D_801B5904[];
extern SpriteParts* D_801B721C[];

static SpriteParts** SpriteBanks[] = {
    0x00000000,
    D_801AEA68,
    D_801B009C,
    D_801AF754,
    D_801AFB3C,
    D_801B077C,
    D_801B0B80,
    D_801B57C0,
    D_801B5904,
    D_801B721C,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};

extern u16* table[];

extern u16* D_80198578[];
extern u16* D_801966B8[];
extern u16* D_80197838[];
extern u16* D_80197918[];
extern u16* D_80197958[];
extern u16* D_80197998[];
extern u16* D_801979D8[];
extern u16* D_80197A18[];
extern u16* D_80197A58[];
extern u16* D_80197A98[];
extern u16* D_80197AD8[];
extern u16* D_80197B18[];
extern u16* D_80197B58[];
extern u16* D_80197B98[];
extern u16* D_80197BD8[];
extern u16* D_80197C18[];
extern u16* D_80197C58[];
extern u16* D_80197C98[];
extern u16* D_80197EF8[];
extern u16* D_80197F58[];
extern u16* D_80197FB8[];
extern u16* D_801980B8[];
extern u16* D_80198518[];
extern u16* D_80198118[];
extern u16* D_80198318[];


static u16** Clut[] = {
    0x00000005,
    0x00000D00,
    0x00000100,
    D_80198578,
    0x00002000,
    0x000008C0,
    D_801966B8,
    0x000028C0,
    0x00000060,
    D_80197838,
    0x00002920,
    0x00000020,
    D_80197918,
    0x00002940,
    0x00000020,
    D_80197958,
    0x00002960,
    0x00000020,
    D_80197998,
    0x00002980,
    0x00000020,
    D_801979D8,
    0x000029A0,
    0x00000020,
    D_80197A18,
    0x000029C0,
    0x00000020,
    D_80197A58,
    0x000029E0,
    0x00000020,
    D_80197A98,
    0x00002A00,
    0x00000020,
    D_80197AD8,
    0x00002A20,
    0x00000020,
    D_80197B18,
    0x00002A40,
    0x00000020,
    D_80197B58,
    0x00002A60,
    0x00000020,
    D_80197B98,
    0x00002A80,
    0x00000020,
    D_80197BD8,
    0x00002AA0,
    0x00000020,
    D_80197C18,
    0x00002AC0,
    0x00000020,
    D_80197C58,
    0x00002B20,
    0x00000130,
    D_80197C98,
    0x00002C50,
    0x00000030,
    D_80197EF8,
    0x00002C80,
    0x00000030,
    D_80197F58,
    0x00002CB0,
    0x00000080,
    D_80197FB8,
    0x00002D30,
    0x00000030,
    D_801980B8,
    0x00002D60,
    0x00000030,
    D_80198518,
    0x00002E00,
    0x00000080,
    D_80198118,
    0x00002E80,
    0x00000080,
    D_80198318,
    (u16**)-1,
};

static void* Cluts[] = {
    Clut,
};
