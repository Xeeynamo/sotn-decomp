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
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    0xD00,  0x100, D_80198578,
    0x2000, 0x8C0, D_801966B8,
    0x28C0, 0x60,  D_80197838,
    0x2920, 0x20,  D_80197918,
    0x2940, 0x20,  D_80197958,
    0x2960, 0x20,  D_80197998,
    0x2980, 0x20,  D_801979D8,
    0x29A0, 0x20,  D_80197A18,
    0x29C0, 0x20,  D_80197A58,
    0x29E0, 0x20,  D_80197A98,
    0x2A00, 0x20,  D_80197AD8,
    0x2A20, 0x20,  D_80197B18,
    0x2A40, 0x20,  D_80197B58,
    0x2A60, 0x20,  D_80197B98,
    0x2A80, 0x20,  D_80197BD8,
    0x2AA0, 0x20,  D_80197C18,
    0x2AC0, 0x20,  D_80197C58,
    0x2B20, 0x130, D_80197C98,
    0x2C50, 0x30,  D_80197EF8,
    0x2C80, 0x30,  D_80197F58,
    0x2CB0, 0x80,  D_80197FB8,
    0x2D30, 0x30,  D_801980B8,
    0x2D60, 0x30,  D_80198518,
    0x2E00, 0x80,  D_80198118,
    0x2E80, 0x80,  D_80198318,
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};
