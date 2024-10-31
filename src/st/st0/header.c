// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

extern RoomHeader OVL_EXPORT(rooms)[];
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* g_EntityGfxs[];
void UpdateStageEntities();
void PrologueScroll();

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal),
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = g_EntityGfxs,
    .UpdateStageEntities = UpdateStageEntities,
    .StageEndCutScene = PrologueScroll,
};

#include "sprite_banks.h"

extern u16* D_8019A750[0x70];
extern u16* D_8019AD30[0x20];
extern u16* D_8019AC30[0x80];
extern u16* D_8019AD70[0x30];
extern u16* D_8019ADD0[0x50];
extern u16* D_8019AE70[0x60];
extern u16* D_8019AF30[0x70];
extern u16* D_8019A830[0x80];
extern u16* D_8019AA30[0x80];
extern u16* D_8019B010[0x100];

static u_long* Clut[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0), PAL_BULK(0x2000, D_8019A750),
    PAL_BULK(0x2100, D_8019AD30),  PAL_BULK(0x2120, D_8019AC30),
    PAL_BULK(0x21A0, D_8019AD70),  PAL_BULK(0x21D0, D_8019ADD0),
    PAL_BULK(0x2220, D_8019AE70),  PAL_BULK(0x2280, D_8019AF30),
    PAL_BULK(0x2300, D_8019A830),  PAL_BULK(0x2480, D_8019AA30),
    PAL_BULK(0x2800, D_8019B010),  PAL_TERMINATE()};

u_long* OVL_EXPORT(cluts)[] = {
    Clut,
};

#include "layers.h"
