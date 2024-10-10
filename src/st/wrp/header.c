// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 objLayoutId);
void UpdateStageEntities(void);

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
static u_long* cluts[];
extern MyRoomDef OVL_EXPORT(rooms_layers)[];
extern u_long* OVL_EXPORT(gfxBanks)[];

Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16 D_80181D08[16];
u_long* D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80181D08),
    PAL_TERMINATE(),
};
static u_long* cluts[] = {D_801800A0};

#include "layers.h"

static u_long* D_801801B8[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0, 0, 0, 0, NULL),
    GFX_TERMINATE(),
};

extern u8 D_80181420[];
extern u8 D_80181764[];
static u_long* D_801801CC[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 0x80, 0x80, D_80181420),
    GFX_ENTRY(0x100, 0x60, 0x80, 0x80, D_80181764),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801CC, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8};
