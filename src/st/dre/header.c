// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long* OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities();

Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = NULL,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_8018AEA8[0x50];
extern u16* D_8018AF48[0x80];
extern u16* D_8018B148[0x80];
extern u16* D_8018B348[0x80];
extern u16* D_8018ABE8[0x100];

static u_long* Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018AEA8),
    PAL_BULK(0x2080, D_8018AF48),
    PAL_BULK(0x2100, D_8018B148),
    PAL_BULK(0x2180, D_8018B348),
    PAL_BULK(0x2E00, D_8018ABE8),
    PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    Clut,
};

#include "layers.h"
