// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_header.c
 * Overlay: CHI
 * Description: DATA - Header
 */

#include "chi.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

// D_80180000
Overlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

// D_80180040: spriteBanks
#include <gen/sprite_banks.h>

// Palette Data -- These addresses are to the binary data
extern u16* bn_pal_unused_0[0x30]; // Unused (US)
extern u16* bn_pal_salem_witch_projectiles[0x100];
extern u16* bn_pal_unused_1[0x60]; // Unused (US)
extern u16* bn_pal_gremlin[0x40];
extern u16* bn_pal_salem_witch[0x20];
extern u16* bn_pal_thornweed_corpseweed[0x40];
extern u16* bn_pal_venus_weed[0x290];

// D_801800A0
static u16** PaletteCommand0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, bn_pal_gremlin),
    PAL_BULK(0x2040, bn_pal_salem_witch),
    PAL_BULK(0x2060, bn_pal_thornweed_corpseweed),
    PAL_BULK(0x20A0, bn_pal_venus_weed),
    PAL_BULK(0x2E00, bn_pal_salem_witch_projectiles),
    PAL_TERMINATE(),
};

// D_801800E4
u_long* cluts[] = {
    PaletteCommand0,
};

// D_801800E8: layers
// D_80180218: rooms_layers
#include <gen/layers.h>

// Gfx Bank Data -- These addresses are to the binary data
extern u8 bn_gfx_stage_name_jp_sm[];
extern u8 bn_gfx_stage_name_jp_lg[];
extern u8 bn_gfx_gremlin[];
extern u8 bn_gfx_salem_witch_1[];
extern u8 bn_gfx_salem_witch_2[];
extern u8 bn_gfx_salem_witch_3[];
extern u8 bn_gfx_salem_witch_4[];
extern u8 bn_gfx_salem_witch_5[];
extern u8 bn_gfx_thornweed_corpseweed[];
extern u8 bn_gfx_venus_weed_1[];
extern u8 bn_gfx_venus_weed_2[];
extern u8 bn_gfx_stage_name_en[];

#include <gen/graphics_banks.h>
