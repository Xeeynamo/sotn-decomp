// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "pc.h"

static RoomTeleport s_SaturnDoorTeleports[] = {
    {16, 131, 0x0000, STAGE_NP3, STAGE_ID_SATURN_15},
    {0, 0, 0x0000, STAGE_NP3, STAGE_NP3},
    {0, 0, 0x0000, STAGE_NO0, STAGE_NO0},
    {0, 0, 0x0000, STAGE_NO4, STAGE_NO4},
    {0, 0, 0x0000, STAGE_NO0, STAGE_NO0},
    {0, 0, 0x0000, STAGE_NO4, STAGE_NO4},
    {240, 904, 0x0008, STAGE_ID_SATURN_15, STAGE_NP3},
};

RoomTeleport* PC_GetRoomTeleport(int id) {
    if (id < RETAIL_ROOM_TELEPORT_COUNT) {
        return &D_800A245C[id];
    }
    return &s_SaturnDoorTeleports[id - RETAIL_ROOM_TELEPORT_COUNT];
}
