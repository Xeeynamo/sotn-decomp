// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern MyRoomDef OVL_EXPORT(rooms_layers)[];
extern void* OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities();

static Overlay OVL_EXPORT(Overlay) = {
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

extern u16* D_80181D08[0x100];

static u_long* Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2E00, D_80181D08),
    PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    Clut,
};

#include "layers.h"
