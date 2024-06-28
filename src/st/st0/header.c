#include "st0.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_EntityGfxs[];
void UpdateStageEntities();
void func_801B0464();

static Overlay StageOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = SpriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = g_TileLayers,
    .gfxBanks = g_EntityGfxs,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = func_801B0464,
};

extern SpriteParts* D_801A26E0[];
extern SpriteParts* D_801A4298[];
extern SpriteParts* D_801A6A68[];
extern SpriteParts* D_801A6F90[];
extern SpriteParts* D_801A7430[];
extern SpriteParts* D_801A7728[];
extern SpriteParts* D_801A77CC[];

static SpriteParts** SpriteBanks[] = {
    NULL,       D_801A26E0, D_801A4298, D_801A6A68, D_801A6F90, D_801A7430,
    D_801A7728, D_801A77CC, NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
};

extern u16* D_8019A750[0x70];
extern u16* D_8019AD30[0x20];
extern u16* D_8019AC30[0x80];
extern u16* D_8019AD70[0x30];
extern u16* D_8019ADD0[0x50];
extern u16* D_8019AE70[0x60];
extern u16* D_8019AF30[0x70];
extern u16* D_8019A830[0x80];
extern u16* D_8019AA30[0x80];
extern u16* D_8019B010[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x2000, D_8019A750),
    PAL_BULK(0x2100, D_8019AD30),  PAL_BULK(0x2120, D_8019AC30),
    PAL_BULK(0x21A0, D_8019AD70),  PAL_BULK(0x21D0, D_8019ADD0),
    PAL_BULK(0x2220, D_8019AE70),  PAL_BULK(0x2280, D_8019AF30),
    PAL_BULK(0x2300, D_8019A830),  PAL_BULK(0x2480, D_8019AA30),
    PAL_BULK(0x2800, D_8019B010),  PAL_TERMINATE()};

static void* Cluts[] = {
    Clut,
};
