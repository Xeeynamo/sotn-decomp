// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"
#include "stage_14.h"

SaturnStageDataTables g_Stage14Data = {
    g_Stage14EntityUpdates,
    g_Stage14SpriteBanks,
    g_Stage14LayoutHorizontal,
    g_Stage14LayoutVertical,
    g_Stage14Rooms,
    g_Stage14LayerCompressedSizes,
    g_Stage14LayerMapOffsets,
    g_Stage14LayerSetup,
    g_Stage14RoomGraphics,
    g_Stage14RoomPriorities,
};

u32 g_Stage14HeaderExtension[] = {
    0x257B417D, 0x20257B64, 0x7D20257B, 0x652A7D20, 0x257B6D7D, 0x20257B4E,
};
