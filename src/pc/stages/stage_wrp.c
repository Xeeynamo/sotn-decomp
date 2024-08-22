// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "sfx.h"
#include "../../st/wrp/wrp.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void UpdateStageEntities(void);
static void MyInitRoomEntities(s32 objLayoutId);

u32 D_80181420[2048];
u32 D_80181764[2048];

static u16 D_80181D08[16];
static void* D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80181D08),
    PAL_TERMINATE(),
};

static void* clut_anims[] = {
    /* 0x0B4 */ D_801800A0,
};

extern void* WRP_g_EntityGfxs[];
extern RoomHeader OVL_EXPORT(rooms)[];
#include "../../st/wrp/sprite_banks.h" // TODO OVL_EXPORT
#include "../../st/wrp/layers.h"       // TODO OVL_EXPORT
static Overlay g_StageDesc = {
    Update,
    HitDetection,
    UpdateRoomPosition,
    MyInitRoomEntities,
    OVL_EXPORT(rooms),
    spriteBanks,
    clut_anims,
    NULL,
    rooms_layers,
    WRP_g_EntityGfxs,
    UpdateStageEntities,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

void InitStageWrp(Overlay* o) {
    LoadReset();

    FileReadToBuf(
        "assets/st/wrp/D_80181D08.dec", D_80181D08, 0, sizeof(D_80181D08));
    FileReadToBuf(
        "assets/st/wrp/D_80181420.dec", D_80181420, 0, sizeof(D_80181420));
    FileReadToBuf(
        "assets/st/wrp/D_80181764.dec", D_80181764, 0, sizeof(D_80181764));

    memcpy(o, &g_StageDesc, sizeof(Overlay));
}

void SetGameState(GameState gameState);
void PlaySfx(s32 sfxId);
void InitRoomEntities(s32 objLayoutId);

static void MyInitRoomEntities(s32 objLayoutId) {
    INFOF("Stage: %02X, objLayoutId: %i", g_StageId, objLayoutId);
    InitRoomEntities(objLayoutId);
}
