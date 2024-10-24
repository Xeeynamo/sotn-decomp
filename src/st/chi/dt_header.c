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

// Palettes -- These addresses are to the binary data
extern u16* Palette_80189FE0[0x30]; // Unused (US)
extern u16* Palette_8018A040[0x100];
extern u16* Palette_8018A240[0x60]; // Unused (US)
extern u16* Palette_8018A300[0x40];
extern u16* Palette_8018A380[0x20];
extern u16* Palette_8018A3C0[0x40];
extern u16* Palette_8018A440[0x290];

// D_801800A0
static u16** PaletteCommand0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, Palette_8018A300),
    PAL_BULK(0x2040, Palette_8018A380),
    PAL_BULK(0x2060, Palette_8018A3C0),
    PAL_BULK(0x20A0, Palette_8018A440),
    PAL_BULK(0x2E00, Palette_8018A040),
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
// These symbols cannot be renamed due to limitations in our current toolchain
extern u8 D_801820D8[]; // JP Stage Name (Small) -- Unused (US)
extern u8 D_80182508[]; // JP Stage Name (Large)
extern u8 D_80182A60[]; // Gremlin
extern u8 D_80183480[]; // Salem Witch (Body/Arm)
extern u8 D_801841F8[]; // Salem Witch (Shine/Curse/Body)
extern u8 D_80184DBC[]; // Salem Witch (Fire)
extern u8 D_80185BA0[]; // Salem Witch (Explosion)
extern u8 D_80186B1C[]; // Salem Witch (Shine)
extern u8 D_801870F8[]; // Thornweed/Corpseweed
extern u8 D_80187E84[]; // Venus Weed (Flower/Stem/Woman/Projectiles)
extern u8 D_80188A10[]; // Venus Weed (Woman)
extern u8 D_80189B38[]; // EN Stage Name

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
            GFX_ENTRY(0x100, 0x40, 0x80, 0x80, D_80189B38),
            GFX_ENTRY(0x100, 0x60, 0x80, 0x80, D_80182508),
        },
};
static u_long GfxBank_StageName_TERM = GFX_TERMINATE();

// D_801802CC
static GfxBank GfxBank_Gremlin1 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60),
        },
};
static u_long GfxBank_Gremlin1_TERM = GFX_TERMINATE();

// D_801802E0
static GfxBank GfxBank_Gremlin2 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60),
        },
};
static u_long GfxBank_Gremlin2_TERM = GFX_TERMINATE();

// D_801802F4
static GfxBank GfxBank_SalemWitch = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80183480),
            GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, D_801841F8),
            GFX_ENTRY(0x180, 0x80, 0x80, 0x80, D_80185BA0),
            GFX_ENTRY(0x180, 0xA0, 0x80, 0x80, D_80186B1C),
            GFX_ENTRY(0x100, 0x1C0, 0x80, 0x80, D_80184DBC),
        },
};
static u_long GfxBank_SalemWitch_TERM = GFX_TERMINATE();

// D_80180338
static GfxBank GfxBank_AllWeeds = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0xC0, 0x80, 0x80, D_801870F8),
            GFX_ENTRY(0x100, 0x100, 0x80, 0x80, D_80187E84),
            GFX_ENTRY(0x100, 0x120, 0x80, 0x80, D_80188A10),
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
