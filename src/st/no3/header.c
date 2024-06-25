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
    NULL,       D_801AEA68, D_801B009C, D_801AF754, D_801AFB3C, D_801B077C,
    D_801B0B80, D_801B57C0, D_801B5904, D_801B721C, NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
};

extern u16* table[];

extern u16* D_80198578[0x100];
extern u16* D_801966B8[0x8C0];
extern u16* D_80197838[0x60];
extern u16* D_80197918[0x20];
extern u16* D_80197958[0x20];
extern u16* D_80197998[0x20];
extern u16* D_801979D8[0x20];
extern u16* D_80197A18[0x20];
extern u16* D_80197A58[0x20];
extern u16* D_80197A98[0x20];
extern u16* D_80197AD8[0x20];
extern u16* D_80197B18[0x20];
extern u16* D_80197B58[0x20];
extern u16* D_80197B98[0x20];
extern u16* D_80197BD8[0x20];
extern u16* D_80197C18[0x20];
extern u16* D_80197C58[0x20];
extern u16* D_80197C98[0x130];
extern u16* D_80197EF8[0x30];
extern u16* D_80197F58[0x30];
extern u16* D_80197FB8[0x80];
extern u16* D_801980B8[0x30];
extern u16* D_80198518[0x30];
extern u16* D_80198118[0x80];
extern u16* D_80198318[0x80];

// n.b.! very similar to np3
static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0xD00, D_80198578),
    PAL_BULK(0x2000, D_801966B8),
    PAL_BULK(0x28C0, D_80197838),
    PAL_BULK(0x2920, D_80197918),
    PAL_BULK(0x2940, D_80197958),
    PAL_BULK(0x2960, D_80197998),
    PAL_BULK(0x2980, D_801979D8),
    PAL_BULK(0x29A0, D_80197A18),
    PAL_BULK(0x29C0, D_80197A58),
    PAL_BULK(0x29E0, D_80197A98),
    PAL_BULK(0x2A00, D_80197AD8),
    PAL_BULK(0x2A20, D_80197B18),
    PAL_BULK(0x2A40, D_80197B58),
    PAL_BULK(0x2A60, D_80197B98),
    PAL_BULK(0x2A80, D_80197BD8),
    PAL_BULK(0x2AA0, D_80197C18),
    PAL_BULK(0x2AC0, D_80197C58),
    PAL_BULK(0x2B20, D_80197C98),
    PAL_BULK(0x2C50, D_80197EF8),
    PAL_BULK(0x2C80, D_80197F58),
    PAL_BULK(0x2CB0, D_80197FB8),
    PAL_BULK(0x2D30, D_801980B8),
    PAL_BULK(0x2D60, D_80198518),
    PAL_BULK(0x2E00, D_80198118),
    PAL_BULK(0x2E80, D_80198318),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
