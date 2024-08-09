#include "cen.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern GfxBank gfxBanks[];
void UpdateStageEntities();

Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = spriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_8018658C[0x80];
extern u16* D_8018678C[0x80];
extern u16* D_8018698C[0x10];
extern u16* D_801869AC[0x20];

static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x2000, D_8018658C),
    PAL_BULK(0x2080, D_8018678C),  PAL_BULK(0x2100, D_8018698C),
    PAL_BULK(0x2230, D_801869AC),  PAL_TERMINATE(),
};

static void* Cluts[] = {
    D_801800A0,
};

#include "layers.h"


static u32 D_8019C704[24];
