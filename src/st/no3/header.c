// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

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
#include "palette_def.h"
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
