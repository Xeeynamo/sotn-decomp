// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "warp/warp.h"

extern EntityEntry* g_WarpEntityUpdates[];
extern void* g_WarpSpriteBanks[18];
extern LayoutEntity* g_WarpLayoutHorizontal[53];
extern LayoutEntity* g_WarpLayoutVertical[53];
extern WarpRoomTable g_WarpRooms;
extern SaturnLayerCompressedSizes g_WarpLayerCompressedSizes[6];
extern SaturnLayerMapOffsets g_WarpLayerMapOffsets[6];
extern WarpLayerProperties g_WarpLayerProperties;
extern SaturnRoomGraphics g_WarpRoomGraphics[6];
extern SaturnRoomPriorities g_WarpRoomPriorities[32];

typedef struct {
    SaturnStageDataTables tables;
    void* reserved[6];
} SaturnStageDataHeader;

SaturnStageDataHeader g_WarpStageData = {
    {
        g_WarpEntityUpdates,
        g_WarpSpriteBanks,
        g_WarpLayoutHorizontal,
        g_WarpLayoutVertical,
        g_WarpRooms.rooms,
        g_WarpLayerCompressedSizes,
        g_WarpLayerMapOffsets,
        g_WarpLayerProperties.rooms,
        g_WarpRoomGraphics,
        g_WarpRoomPriorities,
    },
    {NULL, NULL, NULL, NULL, NULL, NULL},
};
