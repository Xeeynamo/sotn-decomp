// SPDX-License-Identifier: AGPL-3.0-only
#include "dre.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern GfxBank* g_GfxBanks[];
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
    .gfxBanks = g_GfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_8018AEA8[0x50];
extern u16* D_8018AF48[0x80];
extern u16* D_8018B148[0x80];
extern u16* D_8018B348[0x80];
extern u16* D_8018ABE8[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018AEA8),
    PAL_BULK(0x2080, D_8018AF48),
    PAL_BULK(0x2100, D_8018B148),
    PAL_BULK(0x2180, D_8018B348),
    PAL_BULK(0x2E00, D_8018ABE8),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};

#include "layers.h"
