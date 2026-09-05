// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "overlay.h"
#include "../../st/mad/mad.h"

extern Overlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern RoomDef rooms_layers[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

#define TILES_PER_ROOM (16 * 16)
#define MERGED_ROOM_COUNT 8

// func_8018E1D4 randomizes this stage's rooms by merging rooms 1..16 into eight
// two-room-wide ones: every odd room is widened by one room and the even room
// that follows it is zeroed out. The widened room's tile layout is then read
// and written as 32x16 tiles, so it covers its own tilemap plus the next one.
// On PSX that is fine, as the tilemaps are 0x200 bytes apart in the overlay's
// .data, but here each mad_tilemap_* is a separate global. Give every merged
// pair a single contiguous buffer and point both layers into it, reproducing
// the original layout without relying on how the linker orders the tilemaps.
static u16 mergedTilemaps[MERGED_ROOM_COUNT][TILES_PER_ROOM * 2];

static void MergeRoomTilemaps(void) {
    s32 i;

    for (i = 0; i < MERGED_ROOM_COUNT; i++) {
        LayerDef* left = rooms_layers[1 + i * 2].fg;
        LayerDef* right = rooms_layers[2 + i * 2].fg;
        u16* merged = mergedTilemaps[i];

        if (left->layout == merged) {
            // already merged: the overlay was not reloaded since the last call
            continue;
        }
        memcpy(merged, left->layout, TILES_PER_ROOM * sizeof(u16));
        memcpy(merged + TILES_PER_ROOM, right->layout,
               TILES_PER_ROOM * sizeof(u16));
        left->layout = merged;
        right->layout = merged + TILES_PER_ROOM;
    }
}

// func_8018E1D4 builds this stage's rooms out of rand() calls, but
// the game only ever seeds rand() in demo mode, so entering the stage from the
// same point always generates the same layout. This picks a time-based seed to
// randomise the layout
static void SeedDebugRooms(void) {
    unsigned int seed;

    seed = (unsigned int)time(NULL);
    INFOF("seeding rand() with %u for randomized debug rooms", seed);
    srand(seed);
}

OVL_API void InitStage(Overlay* o) {
    memcpy(o, &g_Overlay, sizeof(Overlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    MergeRoomTilemaps();
    SeedDebugRooms();
}
