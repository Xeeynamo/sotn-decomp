// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_header.c
 * Overlay: CHI
 * Description: DATA - Header
 */

#include "chi.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];

void UpdateStageEntities();
void HitDetection();

// D_80180000
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

// D_80180040: spriteBanks
#include "sprite_banks.h"

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
static u_long* OVL_EXPORT(cluts)[] = {
    PaletteCommand0,
};

// D_801800E8: layers
// D_80180218: rooms_layers
#include "layers.h"

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

// D_80180298
static GfxBank GfxBank_Null = {
    .kind = GFX_BANK_NONE,
    .entries =
        {
            GFX_ENTRY(0, 0, 0, 0, NULL),
        },
};
static u_long GfxBank_Null_TERM = GFX_TERMINATE();

// D_801802AC
static GfxBank GfxBank_StageName = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x40, 0x80, 0x80, bn_gfx_stage_name_en),
            GFX_ENTRY(0x100, 0x60, 0x80, 0x80, bn_gfx_stage_name_jp_lg),
        },
};
static u_long GfxBank_StageName_TERM = GFX_TERMINATE();

// D_801802CC
static GfxBank GfxBank_Gremlin1 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, bn_gfx_gremlin),
        },
};
static u_long GfxBank_Gremlin1_TERM = GFX_TERMINATE();

// D_801802E0
static GfxBank GfxBank_Gremlin2 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, bn_gfx_gremlin),
        },
};
static u_long GfxBank_Gremlin2_TERM = GFX_TERMINATE();

// D_801802F4
static GfxBank GfxBank_SalemWitch = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, bn_gfx_salem_witch_1),
            GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, bn_gfx_salem_witch_2),
            GFX_ENTRY(0x180, 0x80, 0x80, 0x80, bn_gfx_salem_witch_4),
            GFX_ENTRY(0x180, 0xA0, 0x80, 0x80, bn_gfx_salem_witch_5),
            GFX_ENTRY(0x100, 0x1C0, 0x80, 0x80, bn_gfx_salem_witch_3),
        },
};
static u_long GfxBank_SalemWitch_TERM = GFX_TERMINATE();

// D_80180338
static GfxBank GfxBank_AllWeeds = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0xC0, 0x80, 0x80, bn_gfx_thornweed_corpseweed),
            GFX_ENTRY(0x100, 0x100, 0x80, 0x80, bn_gfx_venus_weed_1),
            GFX_ENTRY(0x100, 0x120, 0x80, 0x80, bn_gfx_venus_weed_2),
        },
};
static u_long GfxBank_AllWeeds_TERM = GFX_TERMINATE();

// clang-format off
// D_80180364
static GfxBank* OVL_EXPORT(gfxBanks)[] = {
    &GfxBank_Null,
    &GfxBank_StageName,
    &GfxBank_Gremlin1,
    &GfxBank_SalemWitch,
    &GfxBank_AllWeeds,
    &GfxBank_Gremlin2,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
    &GfxBank_Null,
};
// clang-format on
