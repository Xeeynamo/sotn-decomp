// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"

extern EntityEntry* g_Stage15EntityUpdates[];
extern void* g_Stage15SpriteBanks[];
extern LayoutEntity* g_Stage15LayoutHorizontal[];
extern LayoutEntity* g_Stage15LayoutVertical[];
extern SaturnRoomHeader g_Stage15Rooms[];
extern SaturnLayerCompressedSizes g_Stage15LayerCompressedSizes[];
extern SaturnLayerMapOffsets g_Stage15LayerMapOffsets[];
extern SaturnRoomLayerSetup g_Stage15LayerSetup[];
extern SaturnRoomGraphics g_Stage15RoomGraphics[];
extern SaturnRoomPriorities g_Stage15RoomPriorities[];

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
