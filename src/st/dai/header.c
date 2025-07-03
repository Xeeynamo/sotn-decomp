// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// This is a near copy of the relevant pieces of pfn_update_entity.h
// Currently that file uses a pointer for g_pStObjLayoutHorizontal, but it needs
// to be a constant for pspeu.  The logic needs to be coalesced if possible so
// this can be changed to a simple #include
#if defined(VERSION_PSP) || defined(VERSION_PC)
extern LayoutEntity* g_pStObjLayoutHorizontal[];
#define OBJ_LAYOUT_HORIZONTAL g_pStObjLayoutHorizontal
#else
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
#define OBJ_LAYOUT_HORIZONTAL OVL_EXPORT(pStObjLayoutHorizontal)
#endif

extern RoomHeader OVL_EXPORT(rooms)[];
extern SpriteParts* OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
};

// #include "gen/sprite_banks.h"
// #include "gen/palette_def.h"
// #include "gen/layers.h"
// #include "gen/graphics_banks.h"
