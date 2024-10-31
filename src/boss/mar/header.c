// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern u_long* OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities();

AbbreviatedOverlay OVL_EXPORT(Overlay) = {
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
};

#include "sprite_banks.h"

extern u16* D_us_80184EE0[];
extern u16* D_us_801850E0[];
extern u16* D_us_801852E0[];
static u16** D_us_8018008C[] = {
    0x00000005, 0x00002000,    0x00000080,      D_us_80184EE0,
    0x00002080, 0x00000080,    D_us_801850E0,   0x00002100,
    0x00000010, D_us_801852E0, PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    D_us_8018008C,
};

#include "layers.h"

static u_long* D_us_801800F4_TERM = GFX_TERMINATE();

extern u_long* D_us_801830F0;
extern u_long* D_us_80184220;
static u_long* D_us_801800F8[] = {
    // TODO GfxBank
    0x00000004, 0x00800100, 0x00800080,     &D_us_801830F0,
    0x00A00100, 0x00800080, &D_us_80184220, 0xFFFFFFFF,
};

u_long* OVL_EXPORT(gfxBanks)[] = {
    &D_us_801800F4_TERM, &D_us_801800F8,      &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM, &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM, &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM, &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM, &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM, &D_us_801800F4_TERM,
    &D_us_801800F4_TERM, &D_us_801800F4_TERM};
