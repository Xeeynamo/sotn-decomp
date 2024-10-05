// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern void* OVL_EXPORT(g_EntityGfxs)[];
void UpdateStageEntities();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = spriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = OVL_EXPORT(g_EntityGfxs),
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_80181D08[0x100];

static u16** Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2E00, D_80181D08),
    PAL_TERMINATE(),
};

static void* Cluts[] = {
    Clut,
};

#include "layers.h"
