// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long** OVL_EXPORT(gfxBanks)[];

extern u8* doppleganger_sprites[0x34C];
extern u8* bat_form_sprites[6];

AbbreviatedOverlay2 OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal),
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = doppleganger_sprites,
    .unk30 = bat_form_sprites,
};

extern s16* D_us_801B0A78[];
extern s16* D_us_801B159C[];
extern s16* D_us_801B1664[];
extern s16* D_us_801B2068[];
extern s16* D_us_801B252C[];

s16** OVL_EXPORT(spriteBanks)[] = {
    NULL, D_us_801B0A78, D_us_801B159C, D_us_801B1664, D_us_801B2068, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
    NULL, NULL,          NULL,          D_us_801B252C, NULL,          NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
};

extern s16* D_us_801AC288[0x180];

static u_long* D_us_80180094[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_us_801AC288),
    PAL_TERMINATE(),
};

static u_long* D_us_801800A8[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0xA0], 16),
};

static u_long* D_us_801800B8[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0xC0], 16),
    PAL_TERMINATE(),
};

static u_long* D_us_801800CC[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_COPY_DATA_(0x20F0, &g_Clut[2][0], 16),
    PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    D_us_80180094,
    D_us_801800B8,
    D_us_801800CC,
    D_us_801800A8,
};

#include "gen/layers.h"
#include "gen/graphics_banks.h"
