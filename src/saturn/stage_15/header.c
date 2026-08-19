// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"
#include "stage_15.h"

SaturnStageDataTables g_Stage15Data = {
    g_Stage15EntityUpdates,
    g_Stage15SpriteBanks,
    g_Stage15LayoutHorizontal,
    g_Stage15LayoutVertical,
    g_Stage15Rooms,
    g_Stage15LayerCompressedSizes,
    g_Stage15LayerMapOffsets,
    g_Stage15LayerSetup,
    g_Stage15RoomGraphics,
    g_Stage15RoomPriorities,
};

u32 g_Stage15HeaderExtension[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
