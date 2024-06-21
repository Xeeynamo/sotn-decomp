#include "np3.h"

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

extern SpriteParts* D_801AA124[];
extern SpriteParts* D_801AB758[];
extern SpriteParts* D_801AAE10[];
extern SpriteParts* D_801AB1F8[];
extern SpriteParts* D_801ABE38[];
extern SpriteParts* D_801AED34[];
extern SpriteParts* D_801AC23C[];
extern SpriteParts* D_801AD278[];
extern SpriteParts* D_801AC380[];
extern SpriteParts* D_801AEEF8[];
extern SpriteParts* D_801B08B0[];
extern SpriteParts* D_801B1B30[];


static SpriteParts** SpriteBanks[] = {
    0x00000000,
    D_801AA124,
    D_801AB758,
    D_801AAE10,
    D_801AB1F8,
    D_801ABE38,
    D_801AED34,
    D_801AC23C,
    D_801AD278,
    D_801AC380,
    D_801AEEF8,
    D_801B08B0,
    D_801B1B30,
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

extern u16* D_801963B4[];
extern u16* D_80194914[];
extern u16* D_80195A94[];
extern u16* D_80195B74[];
extern u16* D_80195BB4[];
extern u16* D_80195BF4[];
extern u16* D_80195C34[];
extern u16* D_80195C74[];
extern u16* D_80195CB4[];
extern u16* D_80195CF4[];
extern u16* D_80195D34[];
extern u16* D_80195D74[];
extern u16* D_80195DB4[];
extern u16* D_80195DF4[];
extern u16* D_80195E34[];
extern u16* D_80195E74[];
extern u16* D_80195EB4[];
extern u16* D_80195EF4[];
extern u16* D_80196154[];
extern u16* D_801961B4[];
extern u16* D_801962D4[];
extern u16* D_80196214[];
extern u16* D_80196274[];
extern u16* D_80196674[];
extern u16* D_801966D4[];
extern u16* D_801967D4[];

static u16** Clut[] = {
    0x00000005,
    0x00000D00,
    0x00000100,
    D_801963B4,
    0x00002000,
    0x000008C0,
    D_80194914,
    0x000028C0,
    0x00000060,
    D_80195A94,
    0x00002920,
    0x00000020,
    D_80195B74,
    0x00002940,
    0x00000020,
    D_80195BB4,
    0x00002960,
    0x00000020,
    D_80195BF4,
    0x00002980,
    0x00000020,
    D_80195C34,
    0x000029A0,
    0x00000020,
    D_80195C74,
    0x000029C0,
    0x00000020,
    D_80195CB4,
    0x000029E0,
    0x00000020,
    D_80195CF4,
    0x00002A00,
    0x00000020,
    D_80195D34,
    0x00002A20,
    0x00000020,
    D_80195D74,
    0x00002A40,
    0x00000020,
    D_80195DB4,
    0x00002A60,
    0x00000020,
    D_80195DF4,
    0x00002A80,
    0x00000020,
    D_80195E34,
    0x00002AA0,
    0x00000020,
    D_80195E74,
    0x00002AC0,
    0x00000020,
    D_80195EB4,
    0x00002B20,
    0x00000130,
    D_80195EF4,
    0x00002C50,
    0x00000030,
    D_80196154,
    0x00002C80,
    0x00000030,
    D_801961B4,
    0x00002CB0,
    0x00000070,
    D_801962D4,
    0x00002D30,
    0x00000030,
    D_80196214,
    0x00002D60,
    0x00000030,
    D_80196274,
    0x00002D90,
    0x00000090,
    D_80196674,
    0x00002E20,
    0x00000080,
    D_801966D4,
    0x00002EA0,
    0x00000090,
    D_801967D4,
    (u16**)-1,
};

static void* Cluts[] = {
    Clut,
};
