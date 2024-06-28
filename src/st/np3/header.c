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

extern u16* D_801963B4[0x100];
extern u16* D_80194914[0x8C0];
extern u16* D_80195A94[0x60];
extern u16* D_80195B74[0x20];
extern u16* D_80195BB4[0x20];
extern u16* D_80195BF4[0x20];
extern u16* D_80195C34[0x20];
extern u16* D_80195C74[0x20];
extern u16* D_80195CB4[0x20];
extern u16* D_80195CF4[0x20];
extern u16* D_80195D34[0x20];
extern u16* D_80195D74[0x20];
extern u16* D_80195DB4[0x20];
extern u16* D_80195DF4[0x20];
extern u16* D_80195E34[0x20];
extern u16* D_80195E74[0x20];
extern u16* D_80195EB4[0x20];
extern u16* D_80195EF4[0x130];
extern u16* D_80196154[0x30];
extern u16* D_801961B4[0x30];
extern u16* D_801962D4[0x70];
extern u16* D_80196214[0x30];
extern u16* D_80196274[0x30];
extern u16* D_80196674[0x90];
extern u16* D_801966D4[0x80];
extern u16* D_801967D4[0x90];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0xD00, D_801963B4),
    PAL_BULK(0x2000, D_80194914),  PAL_BULK(0x28C0, D_80195A94),
    PAL_BULK(0x2920, D_80195B74),  PAL_BULK(0x2940, D_80195BB4),
    PAL_BULK(0x2960, D_80195BF4),  PAL_BULK(0x2980, D_80195C34),
    PAL_BULK(0x29A0, D_80195C74),  PAL_BULK(0x29C0, D_80195CB4),
    PAL_BULK(0x29E0, D_80195CF4),  PAL_BULK(0x2A00, D_80195D34),
    PAL_BULK(0x2A20, D_80195D74),  PAL_BULK(0x2A40, D_80195DB4),
    PAL_BULK(0x2A60, D_80195DF4),  PAL_BULK(0x2A80, D_80195E34),
    PAL_BULK(0x2AA0, D_80195E74),  PAL_BULK(0x2AC0, D_80195EB4),
    PAL_BULK(0x2B20, D_80195EF4),  PAL_BULK(0x2C50, D_80196154),
    PAL_BULK(0x2C80, D_801961B4),  PAL_BULK(0x2CB0, D_801962D4),
    PAL_BULK(0x2D30, D_80196214),  PAL_BULK(0x2D60, D_80196274),
    PAL_BULK(0x2D90, D_80196674),  PAL_BULK(0x2E20, D_801966D4),
    PAL_BULK(0x2EA0, D_801967D4),  PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
