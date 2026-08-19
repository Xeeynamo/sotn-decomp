// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "warp.h"

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
