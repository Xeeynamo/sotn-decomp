// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_WARP_H
#define SATURN_WARP_H

#include "stage_data.h"

typedef struct {
    SaturnRoomHeader rooms[18];
    u8 terminator[4];
} WarpRoomTable;

typedef struct {
    SaturnRoomLayerSetup rooms[6];
    u8 padding[2];
} WarpLayerProperties;

#endif
