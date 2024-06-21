#include "dre.h"

extern RoomHeader g_Rooms[];
extern SpriteParts** SpriteBanks[];
extern void* Cluts[];
extern RoomDef g_TileLayers[];
extern GfxBank* g_GfxBanks[];
void UpdateStageEntities();

static Overlay StageOverlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = g_Rooms,
    .spriteBanks = SpriteBanks,
    .cluts = Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = g_TileLayers,
    .gfxBanks = g_GfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2c = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .unk3C = NULL,
};

/*
 * Alternatively, AbbreviatedOverlay can be used
 * which leaves out the last 5 words of Overlay
 */

extern SpriteParts* D_80190168[];

static SpriteParts** SpriteBanks[] = {
    0x00000000,
    D_80190168,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};

extern u16* D_8018AEA8[];
extern u16* D_8018AF48[];
extern u16* D_8018B148[];
extern u16* D_8018B348[];
extern u16* D_8018ABE8[];

static u16** Clut[] = {
    0x00000005,
    0x00002000,
    0x00000050,
    D_8018AEA8,
    0x00002080,
    0x00000080,
    D_8018AF48,
    0x00002100,
    0x00000080,
    D_8018B148,
    0x00002180,
    0x00000080,
    D_8018B348,
    0x00002E00,
    0x00000100,
    D_8018ABE8,
    (u16**)-1,
};

static void* Cluts[] = {
    Clut,
};
