#include "st0.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* OVL_EXPORT(g_EntityGfxs)[];
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
    .gfxBanks = OVL_EXPORT(g_EntityGfxs),
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .unk3C = func_801B0464,
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

extern u16* D_8019A750[];
extern u16* D_8019AD30[];
extern u16* D_8019AC30[];
extern u16* D_8019AD70[];
extern u16* D_8019ADD0[];
extern u16* D_8019AE70[];
extern u16* D_8019AF30[];
extern u16* D_8019A830[];
extern u16* D_8019AA30[];
extern u16* D_8019B010[];

static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    0x2000, 0x70, D_8019A750,
    0x2100, 0x20, D_8019AD30,
    0x2120, 0x80, D_8019AC30,
    0x21A0, 0x30, D_8019AD70,
    0x21D0, 0x50, D_8019ADD0,
    0x2220, 0x60, D_8019AE70,
    0x2280, 0x70, D_8019AF30,
    0x2300, 0x80, D_8019A830,
    0x2480, 0x80, D_8019AA30,
    0x2800, 0x100, D_8019B010,
    PAL_TERMINATE()
};

static void* Cluts[] = {
    D_801800A0,
};
