// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_GAME_DATA_H
#define SATURN_GAME_DATA_H

#include "../sattypes.h"

typedef struct {
    u16 x;
    u16 y;
    u16 roomId;
    u16 reloadStageId;
    u16 stageId;
} RoomTeleport;

typedef struct {
    s32 x;
    s32 y;
    s32 stageId;
    s32 eventId;
    s32 castleFlag;
} RoomBossTeleport;

typedef struct {
    s32 equipmentId;
    s32 paletteIndex;
} EquipmentPaletteMap;

#endif
