// SPDX-License-Identifier: AGPL-3.0-or-later
#include "warp.h"

extern u32 CheckAndDoLevelUp(void);

struct SpawnPoint {
    s16 stageId;
    u8 roomIndex;
    s16 x;
    s16 y;
};

static const struct SpawnPoint s_SpawnPoints[PC_SPAWN_COUNT] = {
    [PC_SPAWN_NP3_STAGE15] = {STAGE_NP3, 1, 192, 870},
    [PC_SPAWN_RNO3_RSTAGE15] = {STAGE_RNO3, 1, 96, 104},
    [PC_SPAWN_NO0_STAGE16] = {STAGE_NO0, 0, 1440, 688},
    [PC_SPAWN_NO4_STAGE16] = {STAGE_NO4, 5, 176, 396},
    [PC_SPAWN_RNO0_RSTAGE16] = {STAGE_RNO0, 0, 64, 132},
    [PC_SPAWN_RNO4_RSTAGE16] = {STAGE_RNO4, 5, 208, 132},
};

enum WarpStep {
    Warp_Off,
    Warp_PickRoom,
    Warp_PlacePlayer,
};

static enum WarpStep s_Step = Warp_Off;
static const struct SpawnPoint* s_Spawn = NULL;
static void (*s_InitRoomEntities)(s32 layoutId) = NULL;

int Warp_StageForSpawnPoint(int spawnPoint) {
    if (spawnPoint <= PC_SPAWN_DEFAULT || spawnPoint >= PC_SPAWN_COUNT) {
        return -1;
    }
    return s_SpawnPoints[spawnPoint].stageId;
}

void Warp_Init(const struct InitGameParams* params) {
    s_Step = Warp_Off;
    s_Spawn = NULL;
    if (params->spawnPoint <= PC_SPAWN_DEFAULT ||
        params->spawnPoint >= PC_SPAWN_COUNT) {
        return;
    }
    s_Spawn = &s_SpawnPoints[params->spawnPoint];
    s_Step = Warp_PickRoom;
}

void Warp_OnFrame(void) {
    const RoomHeader* room;

    if (s_Step != Warp_PickRoom) {
        return;
    }
    if (g_GameState != Game_Play || g_GameStep < Play_Init) {
        return;
    }
    if (g_StageId != s_Spawn->stageId || g_api.o.rooms == NULL) {
        ERRORF("spawn point does not match the loaded stage %02X", g_StageId);
        s_Step = Warp_Off;
        return;
    }
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        CheckAndDoLevelUp();
    }
    room = &g_api.o.rooms[s_Spawn->roomIndex];
    g_Tilemap.left = room->left;
    g_Tilemap.top = room->top;
    D_8003C730 = 1;
    s_Step = Warp_PlacePlayer;
}

static void Warp_PlacePlayerNow(void) {
    s32 x, y;

    if (s_Step != Warp_PlacePlayer) {
        return;
    }
    s_Step = Warp_Off;

    x = s_Spawn->x;
    y = s_Spawn->y;

    g_PlayerX = x;
    g_PlayerY = y;
    PLAYER.posX.i.hi = (u8)x;
    PLAYER.posY.i.hi = (u8)y;
    PLAYER.facingLeft = PLAYER.posX.i.hi >= 0x80;

    D_8009791C.x = g_Tilemap.left + (g_PlayerX >> 8);
    D_8009791C.y = g_Tilemap.top + (g_PlayerY >> 8);
    g_Tilemap.scrollX.i.hi = (D_8009791C.x - g_Tilemap.left) << 8;
    g_Tilemap.scrollY.i.hi = (D_8009791C.y - g_Tilemap.top) << 8;
    g_PrevScrollX = g_Tilemap.scrollX.i.hi;
    g_PrevScrollY = g_Tilemap.scrollY.i.hi;
}

static void Warp_InitRoomEntities(s32 layoutId) {
    Warp_PlacePlayerNow();
    s_InitRoomEntities(layoutId);
}

void Warp_HookOverlay(Overlay* o) {
    if (s_Step == Warp_Off || o->InitRoomEntities == NULL) {
        return;
    }
    s_InitRoomEntities = o->InitRoomEntities;
    o->InitRoomEntities = Warp_InitRoomEntities;
}
