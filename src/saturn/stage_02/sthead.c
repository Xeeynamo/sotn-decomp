// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"
#include "stprops.h"
#include "stage_02.h"

SaturnStageDataTables g_Stage02Data = {
    g_Stage02EntityUpdates,
    g_Stage02SpriteBanks,
    g_Stage02LayoutHorizontal,
    g_Stage02LayoutVertical,
    g_Stage02Rooms,
    g_Stage02LayerCompressedSizes,
    g_Stage02LayerMapOffsets,
    g_Stage02LayerProperties.rooms,
    g_Stage02RoomGraphics,
    g_Stage02RoomPriorities,
};
