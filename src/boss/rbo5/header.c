// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long** OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities();

extern u8* g_SpriteSheet[0x34C];
extern u8* g_PlOvlDopBatSpritesheet[6];

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
    .unk2C = g_SpriteSheet,
    .unk30 = g_PlOvlDopBatSpritesheet,
};

extern s16* D_us_801B0B50[];
extern s16* D_us_801B1674[];
extern s16* D_us_801B173C[];
extern s16* D_us_801B2140[];
extern s16* D_us_801B2604[];

s16** OVL_EXPORT(spriteBanks)[] = {
    NULL, D_us_801B0B50, D_us_801B1674, D_us_801B173C, D_us_801B2140, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
    NULL, NULL,          NULL,          D_us_801B2604, NULL,          NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
};

extern s16* D_us_801AC360[0x1F0];

static u_long* D_us_80180094[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_us_801AC360),
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
