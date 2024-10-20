/*
 * File: dt_header.c
 * Overlay: CHI
 * Description: DATA - Header
 */

#include "chi.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern signed short* spriteBanks[];
extern void* Cluts[];
extern MyRoomDef rooms_layers[];
extern GfxBank* OVL_EXPORT(g_EntityGfxs)[];
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

extern u16* D_80189FE0[0x30];   // Unused
extern u16* D_8018A040[0x100];
extern u16* D_8018A240[0x60];   // Unused
extern u16* D_8018A300[0x40];
extern u16* D_8018A380[0x20];
extern u16* D_8018A3C0[0x40];
extern u16* D_8018A440[0x290];

// D_801800A0
static u16** D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_8018A300),
    PAL_BULK(0x2040, D_8018A380),
    PAL_BULK(0x2060, D_8018A3C0),
    PAL_BULK(0x20A0, D_8018A440),
    PAL_BULK(0x2E00, D_8018A040),
    PAL_TERMINATE(),
};

// D_801800E4
static void* Cluts[] = {
    D_801800A0,
};

// D_801800E8: layers
// D_80180218: rooms_layers
#include "layers.h"

// D_80180298
static u_long* GfxBank_Null[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0, 0, 0, 0, NULL),
    GFX_TERMINATE(),
};

extern u8 D_80189B38[];
extern u8 D_80182508[];

// D_801802AC
static u_long* GfxBank_StageName[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 0x80, 0x80, D_80189B38), // EN Stage Name
    GFX_ENTRY(0x100, 0x60, 0x80, 0x80, D_80182508), // JP Stage Name (Large)
    GFX_TERMINATE(),
};

extern u8 D_80182A60[];

// D_801802CC
static u_long* GfxBank_Gremlin1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60), // Gremlin
    GFX_TERMINATE(),
};

// D_801802E0
static u_long* GfxBank_Gremlin2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60), // Gremlin
    GFX_TERMINATE(),
};

extern u8 D_80183480[];
extern u8 D_801841F8[];
extern u8 D_80185BA0[];
extern u8 D_80186B1C[];
extern u8 D_80184DBC[];

// D_801802F4
static u_long* GfxBank_SalemWitch[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80183480),     // Body/Arm
    GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, D_801841F8),     // Shine/Curse/Body
    GFX_ENTRY(0x180, 0x80, 0x80, 0x80, D_80185BA0),     // Explosion
    GFX_ENTRY(0x180, 0xA0, 0x80, 0x80, D_80186B1C),     // Shine
    GFX_ENTRY(0x100, 0x1C0, 0x80, 0x80, D_80184DBC),    // Fire
    GFX_TERMINATE(),
};

extern u8 D_801870F8[];
extern u8 D_80187E84[];
extern u8 D_80188A10[];

// D_80180338
static u_long* GfxBank_AllWeeds[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0xC0, 0x80, 0x80, D_801870F8),     // Thornweed/Corpseweed
    GFX_ENTRY(0x100, 0x100, 0x80, 0x80, D_80187E84),    // Venus Weed Flower/Stem/Woman/Projectiles
    GFX_ENTRY(0x100, 0x120, 0x80, 0x80, D_80188A10),    // Venus Weed Woman
    GFX_TERMINATE(),
};

// D_80180364
static GfxBank* OVL_EXPORT(g_EntityGfxs)[] = {
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_StageName,
    (GfxBank*)GfxBank_Gremlin1,
    (GfxBank*)GfxBank_SalemWitch,
    (GfxBank*)GfxBank_AllWeeds,
    (GfxBank*)GfxBank_Gremlin2,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
};