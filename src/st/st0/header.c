#include "st0.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern GfxBank* g_EntityGfxs[];
void UpdateStageEntities();
void PrologueScroll();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = spriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = rooms_layers,
    .gfxBanks = g_EntityGfxs,
    .UpdateStageEntities = UpdateStageEntities,
    .StageEndCutScene = PrologueScroll,
};

#include "sprite_banks.h"

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

#include "layers.h"
