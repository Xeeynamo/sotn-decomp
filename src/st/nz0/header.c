// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

extern s16** spriteBanks[];
extern void* g_Cluts[];
extern void* g_EntityGfxs[];
extern MyRoomDef rooms_layers[];
extern RoomHeader OVL_EXPORT(rooms)[];

void Update();
void HitDetection();
void UpdateRoomPosition();
void InitRoomEntities();
void UpdateStageEntities();

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = spriteBanks,
    .cluts = g_Cluts,
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = rooms_layers,
    .gfxBanks = g_EntityGfxs,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u_long* D_80195C3C;
extern u_long* D_80195CDC;
extern u_long* D_80195D3C;
extern u_long* D_80195DBC;
extern u_long* D_80195E1C;
extern u_long* D_80195E3C;
extern u_long* D_80195E9C;
extern u_long* D_80195F1C;
extern u_long* D_80195F9C;
extern u_long* D_8019601C;
extern u_long* D_801962DC;
extern u_long* D_8019641C;
extern u_long* D_8019647C;
extern u_long* D_8019657C;
extern u_long* D_8019663C;
extern u_long* D_8019665C;
extern u_long* D_8019685C;
static u_long* D_8018008C[] = {
    0x00000005,  0x00002000, 0x00000040, &D_80195C3C, 0x00002040, 0x00000010,
    &D_80195CDC, 0x00002050, 0x00000040, &D_80195D3C, 0x00002090, 0x00000030,
    &D_80195DBC, 0x000020C0, 0x00000010, &D_80195E1C, 0x000020D0, 0x00000030,
    &D_80195E3C, 0x00002110, 0x00000040, &D_80195F1C, 0x00002150, 0x00000040,
    &D_80195F9C, 0x00002190, 0x00000040, &D_80195E9C, 0x000021D0, 0x000000A0,
    &D_801962DC, 0x00002270, 0x00000030, &D_8019641C, 0x000022A0, 0x00000080,
    &D_8019647C, 0x00002320, 0x00000050, &D_8019657C, 0x00002370, 0x00000010,
    &D_8019663C, 0x00002380, 0x00000080, &D_8019665C, 0x00002400, 0x00000080,
    &D_8019685C, 0x00002E00, 0x00000100, &D_8019601C, 0xFFFFFFFF,
};

static void* g_Cluts[] = {
    &D_8018008C,
};

#include "layers.h"
