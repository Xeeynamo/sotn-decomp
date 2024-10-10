// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern MyRoomDef OVL_EXPORT(rooms_layers)[];
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
    .objLayoutHorizontal = g_pStObjLayoutHorizontal,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
};

#include "sprite_banks.h"

extern u16* D_80198578[0x100];
extern u16* D_801966B8[0x8C0];
extern u16* D_80197838[0x60];
extern u16* D_80197918[0x20];
extern u16* D_80197958[0x20];
extern u16* D_80197998[0x20];
extern u16* D_801979D8[0x20];
extern u16* D_80197A18[0x20];
extern u16* D_80197A58[0x20];
extern u16* D_80197A98[0x20];
extern u16* D_80197AD8[0x20];
extern u16* D_80197B18[0x20];
extern u16* D_80197B58[0x20];
extern u16* D_80197B98[0x20];
extern u16* D_80197BD8[0x20];
extern u16* D_80197C18[0x20];
extern u16* D_80197C58[0x20];
extern u16* D_80197C98[0x130];
extern u16* D_80197EF8[0x30];
extern u16* D_80197F58[0x30];
extern u16* D_80197FB8[0x80];
extern u16* D_801980B8[0x30];
extern u16* D_80198518[0x30];
extern u16* D_80198118[0x80];
extern u16* D_80198318[0x80];

// n.b.! very similar to np3
static u_long* Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0xD00, D_80198578),
    PAL_BULK(0x2000, D_801966B8),
    PAL_BULK(0x28C0, D_80197838),
    PAL_BULK(0x2920, D_80197918),
    PAL_BULK(0x2940, D_80197958),
    PAL_BULK(0x2960, D_80197998),
    PAL_BULK(0x2980, D_801979D8),
    PAL_BULK(0x29A0, D_80197A18),
    PAL_BULK(0x29C0, D_80197A58),
    PAL_BULK(0x29E0, D_80197A98),
    PAL_BULK(0x2A00, D_80197AD8),
    PAL_BULK(0x2A20, D_80197B18),
    PAL_BULK(0x2A40, D_80197B58),
    PAL_BULK(0x2A60, D_80197B98),
    PAL_BULK(0x2A80, D_80197BD8),
    PAL_BULK(0x2AA0, D_80197C18),
    PAL_BULK(0x2AC0, D_80197C58),
    PAL_BULK(0x2B20, D_80197C98),
    PAL_BULK(0x2C50, D_80197EF8),
    PAL_BULK(0x2C80, D_80197F58),
    PAL_BULK(0x2CB0, D_80197FB8),
    PAL_BULK(0x2D30, D_801980B8),
    PAL_BULK(0x2D60, D_80198518),
    PAL_BULK(0x2E00, D_80198118),
    PAL_BULK(0x2E80, D_80198318),
    PAL_TERMINATE(),
};

u_long* OVL_EXPORT(cluts)[] = {
    Clut,
};

#include "layers.h"

static GfxBank D_801805A4 = {
    .kind = GFX_BANK_NONE,
    .entries =
        {
            GFX_ENTRY(0, 0, 0, 0, NULL),
        },
};
static u_long D_801805A4_TERM = GFX_TERMINATE();

extern u_long* D_80184E74;
extern u_long* D_801851B8;

static GfxBank D_801805B8 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x100, 0x40, 0x80, 0x80, &D_80184E74),
            GFX_ENTRY(0x100, 0x60, 0x80, 0x80, &D_801851B8),
        },
};
static u_long D_801805B8_TERM = GFX_TERMINATE();

extern u_long* D_80193688;
extern u_long* D_80194688;
extern u_long* D_801950CC;
extern u_long* D_8018575C;
extern u_long* D_801868C8;

static GfxBank D_801805D8 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x0100, 0x0040, 0x0080, 0x0080, &D_80193688),
            GFX_ENTRY(0x0100, 0x0060, 0x0080, 0x0080, &D_80194688),
            GFX_ENTRY(0x0180, 0x0040, 0x0080, 0x0080, &D_801950CC),
            GFX_ENTRY(0x0180, 0x0080, 0x0080, 0x0080, &D_8018575C),
            GFX_ENTRY(0x0180, 0x00A0, 0x0080, 0x0080, &D_801868C8),
        },
};
static u_long D_801805D8_TERM = GFX_TERMINATE();

extern u_long* D_80187BD0;
extern u_long* D_80188870;
extern u_long* D_801894AC;
extern u_long* D_8018A4BC;
extern u_long* D_8018B99C;
extern u_long* D_8019573C;

static GfxBank D_8018061C = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x0100, 0x0080, 0x0080, 0x0080, &D_80187BD0),
            GFX_ENTRY(0x0100, 0x00A0, 0x0080, 0x0080, &D_80188870),
            GFX_ENTRY(0x0180, 0x0080, 0x0080, 0x0080, &D_801894AC),
            GFX_ENTRY(0x0180, 0x00A0, 0x0080, 0x0080, &D_8018A4BC),
            GFX_ENTRY(0x0100, 0x00C0, 0x0080, 0x0080, &D_8018B99C),
            GFX_ENTRY(0x0180, 0x0120, 0x0080, 0x0080, &D_8019573C),
        },
};
static u_long D_8018061C_TERM = GFX_TERMINATE();

extern u_long* D_8018ADC0;
extern u_long* D_8019573C;

static GfxBank D_8018066C = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x0100, 0x0080, 0x0080, 0x0080, &D_8018ADC0),
            GFX_ENTRY(0x0180, 0x0120, 0x0080, 0x0080, &D_8019573C),
        },
};
static u_long D_8018066C_TERM = GFX_TERMINATE();

extern u_long* D_8018C460;
extern u_long* D_8018D5EC;
extern u_long* D_8018E6CC;
extern u_long* D_8018F870;
extern u_long* D_8019573C;

static GfxBank D_8018068C = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x0100, 0x0080, 0x0080, 0x0080, &D_8018C460),
            GFX_ENTRY(0x0100, 0x00A0, 0x0080, 0x0080, &D_8018D5EC),
            GFX_ENTRY(0x0180, 0x0080, 0x0080, 0x0080, &D_8018E6CC),
            GFX_ENTRY(0x0180, 0x00A0, 0x0080, 0x0080, &D_8018F870),
            GFX_ENTRY(0x0180, 0x0120, 0x0080, 0x0080, &D_8019573C),
        },
};
static u_long D_8018068C_TERM = GFX_TERMINATE();

extern u_long* D_8018C460;
extern u_long* D_8018D5EC;
extern u_long* D_8018E6CC;
extern u_long* D_8018F870;
extern u_long* D_80190958;
extern u_long* D_801914B8;
extern u_long* D_8019573C;

static GfxBank D_801806D0 = {
    .kind = GFX_BANK_COMPRESSED,
    .entries =
        {
            GFX_ENTRY(0x0100, 0x0080, 0x0080, 0x0080, &D_8018C460),
            GFX_ENTRY(0x0100, 0x00A0, 0x0080, 0x0080, &D_8018D5EC),
            GFX_ENTRY(0x0180, 0x0080, 0x0080, 0x0080, &D_8018E6CC),
            GFX_ENTRY(0x0180, 0x00A0, 0x0080, 0x0080, &D_8018F870),
            GFX_ENTRY(0x0100, 0x00C0, 0x0080, 0x0080, &D_80190958),
            GFX_ENTRY(0x0100, 0x00E0, 0x0080, 0x0080, &D_801914B8),
            GFX_ENTRY(0x0180, 0x0120, 0x0080, 0x0080, &D_8019573C),
        },
};
static u_long D_801806D0_TERM = GFX_TERMINATE();

u_long* OVL_EXPORT(gfxBanks)[] = {
    &D_801805A4, &D_801805D8, &D_8018061C, &D_8018066C, &D_8018068C,
    &D_801805B8, &D_801806D0, &D_801805A4, &D_801805A4, &D_801805A4,
    &D_801805A4, &D_801805A4, &D_801805A4, &D_801805A4, &D_801805A4,
    &D_801805A4, &D_801805A4, &D_801805A4, &D_801805A4, &D_801805A4,
};
