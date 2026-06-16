// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 objLayoutId);
void UpdateStageEntities(void);

extern RoomHeader OVL_EXPORT(rooms)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];

#ifdef VERSION_PSP
extern SpriteParts* OVL_EXPORT(spriteBanks)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];
#else
extern s16** OVL_EXPORT(spriteBanks)[];
extern u_long** OVL_EXPORT(gfxBanks)[];
#endif

#ifdef VERSION_PSP
// overlay
u8* D_pspeu_09293958[];
#endif

Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = OVL_EXPORT(spriteBanks),
    .cluts = OVL_EXPORT(cluts),
    .objLayoutHorizontal = NULL,
    .tileLayers = OVL_EXPORT(rooms_layers),
    .gfxBanks = OVL_EXPORT(gfxBanks),
    .UpdateStageEntities = UpdateStageEntities,
#ifdef VERSION_PSP
    .unk2C = NULL,
    .unk30 = D_pspeu_09293958,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
#endif
};

#ifndef VERSION_PSP
#include "gen/sprite_banks.h"
#include "gen/palette_def.h"
#include "gen/layers.h"
#include "gen/graphics_banks.h"
STATIC_PAD_BSS(96);
#endif
