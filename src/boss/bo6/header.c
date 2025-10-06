// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long** OVL_EXPORT(gfxBanks)[];
extern u8 richter_sprites[];

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
    .unk2C = richter_sprites,
    .unk30 = richter_sprites,
};

extern s16* D_us_801A39B0[];
extern s16* D_us_801A4628[];
extern s16* D_us_801A43A4[];
extern s16* D_us_801A4AAC[];

s16** OVL_EXPORT(spriteBanks)[] = {
NULL,
D_us_801A39B0,
NULL,
D_us_801A4628,
D_us_801A43A4,
D_us_801A4AAC,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
};


extern s16* D_us_8019E9A0[0x300];
extern s16* D_us_8019EFA0[0x100];
extern s16* D_us_8019F3A0[0x80];
extern s16* D_us_8019F1A0[0x80];
extern s16* D_us_8019F5A0[0x80];

static u_long* D_us_80180094[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2200, D_us_8019E9A0),
    PAL_BULK(0x2500, D_us_8019EFA0),
    PAL_BULK(0x2600, D_us_8019F3A0),
    PAL_BULK(0x2680, D_us_8019F1A0),
    PAL_BULK(0x2700, D_us_8019F5A0),
    PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    D_us_80180094,
};

#include "gen/layers.h"
#include "gen/graphics_banks.h"
