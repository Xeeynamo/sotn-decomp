// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"
#include "stprops.h"

extern EntityEntry* g_Stage02EntityUpdates[78];
extern struct SpriteParts** g_Stage02SpriteBanks[];
extern LayoutEntity* g_Stage02LayoutHorizontal[];
extern LayoutEntity* g_Stage02LayoutVertical[];
extern SaturnRoomHeader g_Stage02Rooms[33];
extern SaturnLayerCompressedSizes g_Stage02LayerCompressedSizes[26];
extern SaturnLayerMapOffsets g_Stage02LayerMapOffsets[26];
extern SaturnRoomGraphics g_Stage02RoomGraphics[26];
extern SaturnRoomPriorities g_Stage02RoomPriorities[32];

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
