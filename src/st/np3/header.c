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
    NULL,       D_801AA124, D_801AB758, D_801AAE10, D_801AB1F8, D_801ABE38,
    D_801AED34, D_801AC23C, D_801AD278, D_801AC380, D_801AEEF8, D_801B08B0,
    D_801B1B30, NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
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
    0x5,        0xD00,     0x100, D_801963B4, 0x2000, 0x8C0,
    D_80194914, 0x28C0,    0x60,  D_80195A94, 0x2920, 0x20,
    D_80195B74, 0x2940,    0x20,  D_80195BB4, 0x2960, 0x20,
    D_80195BF4, 0x2980,    0x20,  D_80195C34, 0x29A0, 0x20,
    D_80195C74, 0x29C0,    0x20,  D_80195CB4, 0x29E0, 0x20,
    D_80195CF4, 0x2A00,    0x20,  D_80195D34, 0x2A20, 0x20,
    D_80195D74, 0x2A40,    0x20,  D_80195DB4, 0x2A60, 0x20,
    D_80195DF4, 0x2A80,    0x20,  D_80195E34, 0x2AA0, 0x20,
    D_80195E74, 0x2AC0,    0x20,  D_80195EB4, 0x2B20, 0x130,
    D_80195EF4, 0x2C50,    0x30,  D_80196154, 0x2C80, 0x30,
    D_801961B4, 0x2CB0,    0x70,  D_801962D4, 0x2D30, 0x30,
    D_80196214, 0x2D60,    0x30,  D_80196274, 0x2D90, 0x90,
    D_80196674, 0x2E20,    0x80,  D_801966D4, 0x2EA0, 0x90,
    D_801967D4, (u16**)-1,
};

static void* Cluts[] = {
    Clut,
};
