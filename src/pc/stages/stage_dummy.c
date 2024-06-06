#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "stage_loader.h"
#include "sfx.h"

static void Update(void);
static void HitDetection(void);
static void func_8018A7AC(void);
static void InitRoomEntities(s32 objLayoutId);

static u32* empty_entity_gfx[] = {
    (u32*)0xFFFFFFFF,
};
static u_long* empty_clut_load[] = {
    (u_long*)0x00000000,
};

static RoomHeader g_Rooms[1] = {{40, 12, 40, 12, {0, 0, 0, 0}}};
static u_long* g_SpriteBanks[1] = {NULL};
static u16* g_Cluts[] = {empty_clut_load, NULL};
static void* g_EntityGfxs[] = {empty_entity_gfx, NULL};
static void UpdateStageEntities(void);

static Overlay g_StageDesc = {
    Update,
    HitDetection,
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

void InitStageDummy(Overlay* o) {
    g_StageDesc.tileLayers = LoadRooms("assets/st/wrp/rooms.layers.json");
    memcpy(o, &g_StageDesc, sizeof(Overlay));
}

static void Update(void) { NOT_IMPLEMENTED; }

static void HitDetection(void) { NOT_IMPLEMENTED; }

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
    PlaySfx(MU_CRYSTAL_TEARDROPS);
}

static void UpdateStageEntities(void) { NOT_IMPLEMENTED; }
