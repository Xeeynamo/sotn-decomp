#include "chi.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern GfxBank gfxBanks[];
void UpdateStageEntities();
void HitDetection();

// D_80180000
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

// D_80180040: spriteBanks
#include "sprite_banks.h"

extern u16* D_8018A300[0x40];
extern u16* D_8018A380[0x20];
extern u16* D_8018A3C0[0x40];
extern u16* D_8018A440[0x290];
extern u16* D_8018A040[0x100];

// D_801800A0
static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018A300),
    PAL_BULK(0x2040, D_8018A380),
    PAL_BULK(0x2060, D_8018A3C0),
    PAL_BULK(0x20A0, D_8018A440),
    PAL_BULK(0x2E00, D_8018A040),
    PAL_TERMINATE(),
};

// D_801800E4
static void* Cluts[] = {
    D_801800A0,
};

// D_801800E8: layers
// D_80180218: rooms_layers
#include "layers.h"