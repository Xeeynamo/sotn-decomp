// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_STAGE_02_PROPERTIES_H
#define SATURN_STAGE_02_PROPERTIES_H

#include "stage_data.h"

typedef struct {
    SaturnRoomLayerSetup rooms[26];
    u8 padding[2];
} Stage02LayerProperties;

extern Stage02LayerProperties g_Stage02LayerProperties;

#endif
