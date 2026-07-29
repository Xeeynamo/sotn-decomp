// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"

extern EntityEntry* g_RStage15EntityUpdates[];
extern void* g_RStage15SpriteBanks[];
extern LayoutEntity* g_RStage15LayoutHorizontal[];
extern LayoutEntity* g_RStage15LayoutVertical[];
extern SaturnRoomHeader g_RStage15Rooms[];
extern SaturnLayerCompressedSizes g_RStage15LayerCompressedSizes[];
extern SaturnLayerMapOffsets g_RStage15LayerMapOffsets[];
extern SaturnRoomLayerSetup g_RStage15LayerSetup[];
extern SaturnRoomGraphics g_RStage15RoomGraphics[];
extern SaturnRoomPriorities g_RStage15RoomPriorities[];

SaturnStageDataTables g_RStage15Data = {
    g_RStage15EntityUpdates,
    g_RStage15SpriteBanks,
    g_RStage15LayoutHorizontal,
    g_RStage15LayoutVertical,
    g_RStage15Rooms,
    g_RStage15LayerCompressedSizes,
    g_RStage15LayerMapOffsets,
    g_RStage15LayerSetup,
    g_RStage15RoomGraphics,
    g_RStage15RoomPriorities,
};

u32 g_RStage15HeaderExtension[] = {
    0x544C4100, 0x444C4100, 0x344C4100, 0x244C4100, 0x144C4100, 0x044C4100,
};
