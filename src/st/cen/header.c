// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

extern RoomHeader OVL_EXPORT(rooms)[];
static signed short* spriteBanks[];
static void* Cluts[];
static MyRoomDef rooms_layers[];
static GfxBank* gfxBanks[];
void UpdateStageEntities();

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
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_8018658C[0x80];
extern u16* D_8018678C[0x80];
extern u16* D_8018698C[0x10];
extern u16* D_801869AC[0x20];

static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x2000, D_8018658C),
    PAL_BULK(0x2080, D_8018678C),  PAL_BULK(0x2100, D_8018698C),
    PAL_BULK(0x2230, D_801869AC),  PAL_TERMINATE(),
};

static void* Cluts[] = {
    D_801800A0,
};

#include "layers.h"

static u32 D_8019C704[24];

static u_long* D_80180134[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0, 0, 0, 0, NULL),
    GFX_TERMINATE(),
};

extern u8 D_80183A40[];
extern u8 D_80184B70[];
static u_long* D_80180148[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80183A40),
    GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, D_80184B70),
    GFX_TERMINATE(),
};

extern u8 D_80181658[];
extern u8 D_8018199C[];
static u_long* D_80180168[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 0x80, 0x80, D_80181658),
    GFX_ENTRY(0x100, 0x60, 0x80, 0x80, D_8018199C),
    GFX_TERMINATE(),
};

extern u8 D_80185830[];
static u_long* D_80180188[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80185830),
    GFX_TERMINATE(),
};

static GfxBank* gfxBanks[] = {
    &D_80180134, &D_80180148, &D_80180188, &D_80180134, &D_80180134,
    &D_80180168, &D_80180134, &D_80180134, &D_80180134, &D_80180134,
    &D_80180134, &D_80180134, &D_80180134, &D_80180134, &D_80180134,
    &D_80180134, &D_80180134, &D_80180134, &D_80180134, &D_80180134,
};
