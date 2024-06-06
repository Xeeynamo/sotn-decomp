#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "stage_loader.h"
#include "sfx.h"

static void Update(void);
static void TestCollisions(void);
static void func_8018A7AC(void);
static void InitRoomEntities(s32 objLayoutId);

static RoomHeader g_Rooms[1];
static s16** g_SpriteBanks[1];
static u16* g_Cluts[1];
static void* g_EntityGfxs[17];
static void UpdateStageEntities(void);

static Overlay g_StageDesc = {
    Update,
    TestCollisions,
    func_8018A7AC,
    InitRoomEntities,
    g_Rooms,
    g_SpriteBanks,
    g_Cluts,
    NULL,
    NULL,
    g_EntityGfxs,
    UpdateStageEntities,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

static RoomHeader g_Rooms[1] = {0};
static s16** g_SpriteBanks[1] = {0};

static u32* D_801801B8[] = {
    (u32*)0x00000000, (u32*)0x00000000, (u32*)0x00000000,
    (u32*)0x00000000, (u32*)0xFFFFFFFF,
};
static void* g_EntityGfxs[] = {
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, NULL,
};

static u8 D_80181D08[0x2000];
static u32* D_801800A0[] = {
    (u32*)0x00000005, (u32*)0x00002000, (u32*)0x00000010,
    (u32*)D_80181D08, (u32*)0xFFFFFFFF,
};
static u16* g_Cluts[] = {
    D_801800A0,
};

void InitStageDummy(Overlay* o) {
    FILE* f;

    f = fopen("assets/st/wrp/D_80181D08.dec", "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);
        fread(D_80181D08, len, 1, f);
        fclose(f);
    }

    g_StageDesc.tileLayers = LoadRooms("assets/st/wrp/rooms.layers.json");
    memcpy(o, &g_StageDesc, sizeof(Overlay));
}

static void Update(void) { NOT_IMPLEMENTED; }

static void TestCollisions(void) { NOT_IMPLEMENTED; }

static void func_8018A7AC(void) { NOT_IMPLEMENTED; }

void SetGameState(GameState gameState);
void PlaySfx(s32 sfxId);
static void InitRoomEntities(s32 objLayoutId) {
    if (g_StageId == STAGE_SEL) {
        SetGameState(Game_NowLoading);
        g_GameStep = NowLoading_2;
        g_StageId = STAGE_WRP;
        return;
    }

    INFOF("Stage ID: %02X", g_StageId);
    PlaySfx(MU_REQUIEM_FOR_THE_GODS);
}

static void UpdateStageEntities(void) { NOT_IMPLEMENTED; }
