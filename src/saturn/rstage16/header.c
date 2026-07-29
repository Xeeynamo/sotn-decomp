// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"

extern EntityEntry* g_RStage16EntityUpdates[];
extern void* g_RStage16SpriteBanks[];
extern LayoutEntity* g_RStage16LayoutHorizontal[];
extern LayoutEntity* g_RStage16LayoutVertical[];
extern SaturnRoomHeader g_RStage16Rooms[];
extern SaturnLayerCompressedSizes g_RStage16LayerCompressedSizes[];
extern SaturnLayerMapOffsets g_RStage16LayerMapOffsets[];
extern SaturnRoomLayerSetup g_RStage16LayerSetup[];
extern SaturnRoomGraphics g_RStage16RoomGraphics[];
extern SaturnRoomPriorities g_RStage16RoomPriorities[];

SaturnStageDataTables g_RStage16Data = {
    g_RStage16EntityUpdates,
    g_RStage16SpriteBanks,
    g_RStage16LayoutHorizontal,
    g_RStage16LayoutVertical,
    g_RStage16Rooms,
    g_RStage16LayerCompressedSizes,
    g_RStage16LayerMapOffsets,
    g_RStage16LayerSetup,
    g_RStage16RoomGraphics,
    g_RStage16RoomPriorities,
};

u32 g_RStage16HeaderExtension[] = {
    0x257B417D, 0x20257B64, 0x7D20257B, 0x652A7D20, 0x257B6D7D, 0x20257B4E,
};
