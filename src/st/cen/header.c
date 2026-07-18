// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 objLayoutId);
void UpdateStageEntities(void);

extern RoomHeader rooms[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];

#ifdef VERSION_PSP
extern SpriteParts* spriteBanks[];
extern GfxBank* gfxBanks[];
#else
extern s16** spriteBanks[];
extern u_long** gfxBanks[];
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
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
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
