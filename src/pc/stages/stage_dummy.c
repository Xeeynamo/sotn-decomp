// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "stage_loader.h"
#include "sfx.h"
#include "../../st/wrp/wrp.h"

static void MyInitRoomEntities(s32 objLayoutId);

static u32* empty_entity_gfx[] = {
    (u32*)0xFFFFFFFF,
};
static u_long* empty_clut_load[] = {
    (u_long*)0x00000000,
};

static RoomHeader rooms[] = {
    {40, 12, 40, 12, {0, 0, 0, 1}},
    {0x40},
};

static u_long* sprite_banks[1] = {NULL};
static u16* clut_anims[] = {empty_clut_load, NULL};
static void* entity_gfxs[] = {empty_entity_gfx, NULL};
static void UpdateStageEntities(void);
extern s16** WRP_spriteBanks[];
extern RoomDef WRP_rooms_layers[];

static Overlay g_StageDesc = {
    Update,
    HitDetection,
    UpdateRoomPosition,
    MyInitRoomEntities,
    rooms,
    WRP_spriteBanks,
    clut_anims,
    NULL,
    WRP_rooms_layers,
    entity_gfxs,
    UpdateStageEntities,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

void InitStageDummy(Overlay* o) {
    LoadReset();

    memcpy(o, &g_StageDesc, sizeof(Overlay));
}

void SetGameState(GameState gameState);
void PlaySfx(s32 sfxId);
static void MyInitRoomEntities(s32 objLayoutId) {
    switch (g_StageId) {
    case STAGE_SEL: // skip Title screen
    case STAGE_ST0: // hack to force NG to jump straight to a valid map
        SetGameState(Game_NowLoading);
        g_GameStep = NowLoading_2;
        g_StageId = STAGE_NZ0;
        break;
    }

    INFOF("Stage ID: %02X", g_StageId);
    PlaySfx(MU_CRYSTAL_TEARDROPS);
}

static void UpdateStageEntities(void) { NOT_IMPLEMENTED; }
