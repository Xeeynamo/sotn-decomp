// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "stage_data.h"

extern EntityEntry* g_Stage16EntityUpdates[];
extern void* g_Stage16SpriteBanks[];
extern LayoutEntity* g_Stage16LayoutHorizontal[];
extern LayoutEntity* g_Stage16LayoutVertical[];
extern SaturnRoomHeader g_Stage16Rooms[];
extern SaturnLayerCompressedSizes g_Stage16LayerCompressedSizes[];
extern SaturnLayerMapOffsets g_Stage16LayerMapOffsets[];
extern SaturnRoomLayerSetup g_Stage16LayerSetup[];
extern SaturnRoomGraphics g_Stage16RoomGraphics[];
extern SaturnRoomPriorities g_Stage16RoomPriorities[];

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
