// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern MyRoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* g_EntityGfxs[];
void UpdateStageEntities();
void PrologueScroll();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal),
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = g_EntityGfxs,
    .UpdateStageEntities = UpdateStageEntities,
    .StageEndCutScene = PrologueScroll,
};

#include "sprite_banks.h"
#include "palette_def.h"
#include "layers.h"
