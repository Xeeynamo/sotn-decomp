// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"
#include "stage_16.h"

SaturnStageDataTables g_Stage16Data = {
    g_Stage16EntityUpdates,
    g_Stage16SpriteBanks,
    g_Stage16LayoutHorizontal,
    g_Stage16LayoutVertical,
    g_Stage16Rooms,
    g_Stage16LayerCompressedSizes,
    g_Stage16LayerMapOffsets,
    g_Stage16LayerSetup,
    g_Stage16RoomGraphics,
    g_Stage16RoomPriorities,
};

u32 g_Stage16HeaderExtension[] = {
    0x66732E61, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
