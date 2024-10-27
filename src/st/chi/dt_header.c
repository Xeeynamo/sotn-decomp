// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_header.c
 * Overlay: CHI
 * Description: DATA - Header
 */

#include "chi.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
static void* Cluts[];
extern MyRoomDef rooms_layers[];
static GfxBank* OVL_EXPORT(g_EntityGfxs)[];
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
    .gfxBanks = OVL_EXPORT(g_EntityGfxs),
    .UpdateStageEntities = UpdateStageEntities,
};

// D_80180040: spriteBanks
#include "sprite_banks.h"

// Palette Data -- These addresses are to the binary data
extern u16* _binary_assets_st_chi_dt_palette_unused0_bin_start[0x30];   // Unused (US)
extern u16* _binary_assets_st_chi_dt_palette_salem_witch_projectiles_bin_start[0x100];
extern u16* _binary_assets_st_chi_dt_palette_unused1_bin_start[0x60];   // Unused (US)
extern u16* _binary_assets_st_chi_dt_palette_gremlin_bin_start[0x40];
extern u16* _binary_assets_st_chi_dt_palette_salem_witch_bin_start[0x20];
extern u16* _binary_assets_st_chi_dt_palette_thornweed_corpseweed_bin_start[0x40];
extern u16* _binary_assets_st_chi_dt_palette_venus_weed_bin_start[0x290];

// D_801800A0
static u16** PaletteCommand0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, _binary_assets_st_chi_dt_palette_gremlin_bin_start),
    PAL_BULK(0x2040, _binary_assets_st_chi_dt_palette_salem_witch_bin_start),
    PAL_BULK(0x2060, _binary_assets_st_chi_dt_palette_thornweed_corpseweed_bin_start),
    PAL_BULK(0x20A0, _binary_assets_st_chi_dt_palette_venus_weed_bin_start),
    PAL_BULK(0x2E00, _binary_assets_st_chi_dt_palette_salem_witch_projectiles_bin_start),
    PAL_TERMINATE(),
};

// D_801800E4
static void* Cluts[] = {
    PaletteCommand0,
};

// D_801800E8: layers
// D_80180218: rooms_layers
#include "layers.h"

// Gfx Bank Data -- These addresses are to the binary data
extern u8 _binary_assets_st_chi_dt_gfx_jp_stage_name_sm_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_jp_stage_name_lg_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_gremlin_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_salem_witch_1_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_salem_witch_2_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_salem_witch_3_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_salem_witch_4_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_salem_witch_5_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_thornweed_corpseweed_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_venus_weed_1_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_venus_weed_2_bin_start[];
extern u8 _binary_assets_st_chi_dt_gfx_en_stage_name_bin_start[];

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
            GFX_ENTRY(0x100, 0x40, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_en_stage_name_bin_start),
            GFX_ENTRY(0x100, 0x60, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_jp_stage_name_lg_bin_start),
        },
};
static u_long GfxBank_StageName_TERM = GFX_TERMINATE();

// D_801802CC
static GfxBank GfxBank_Gremlin1 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_gremlin_bin_start),
        },
};
static u_long GfxBank_Gremlin1_TERM = GFX_TERMINATE();

// D_801802E0
static GfxBank GfxBank_Gremlin2 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_gremlin_bin_start),
        },
};
static u_long GfxBank_Gremlin2_TERM = GFX_TERMINATE();

// D_801802F4
static GfxBank GfxBank_SalemWitch = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_salem_witch_1_bin_start),
            GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_salem_witch_2_bin_start),
            GFX_ENTRY(0x180, 0x80, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_salem_witch_4_bin_start),
            GFX_ENTRY(0x180, 0xA0, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_salem_witch_5_bin_start),
            GFX_ENTRY(0x100, 0x1C0, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_salem_witch_3_bin_start),
        },
};
static u_long GfxBank_SalemWitch_TERM = GFX_TERMINATE();

// D_80180338
static GfxBank GfxBank_AllWeeds = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0xC0, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_thornweed_corpseweed_bin_start),
            GFX_ENTRY(0x100, 0x100, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_venus_weed_1_bin_start),
            GFX_ENTRY(0x100, 0x120, 0x80, 0x80, _binary_assets_st_chi_dt_gfx_venus_weed_2_bin_start),
        },
};
static u_long GfxBank_AllWeeds_TERM = GFX_TERMINATE();

// clang-format off
// D_80180364
static GfxBank* OVL_EXPORT(g_EntityGfxs)[] = {
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
