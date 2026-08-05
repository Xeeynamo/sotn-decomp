// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"
#ifdef VERSION_PSP
#include "../../st/pfn_entity_update.h"

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);
// overlay
u8* D_pspeu_09263440[];
// overlay
u8* D_pspeu_09263438[];

AbbreviatedOverlay2 g_BossOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = D_pspeu_09263438,
    .unk30 = D_pspeu_09263440,
};
#else

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];

extern u8* doppleganger_sprites[0x34C];
extern u8* bat_form_sprites[6];

extern s16** spriteBanks[];
extern u_long* cluts[];

AbbreviatedOverlay2 BO4_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = rooms,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = entityLayoutHorizontal,
    .tileLayers = rooms_layers,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = doppleganger_sprites,
    .unk30 = bat_form_sprites,
};
#endif
