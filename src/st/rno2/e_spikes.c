// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

#define SPIKES_TILE_WIDTH 96
#define SPIKES_PARTS_INITIAL_VELOCITY_Y FIX(-2.5)
#define DAMAGE_ENT_ON_HIT
#define DAMAGE_ENT_START g_Entities[160]
#define DAMAGE_ENT_END g_Entities[192]

#include "../e_spikes.h"

#ifndef VERSION_PSP
const RECT g_Rno2DrawEnvClip = {0, 0x100, 0x50, 0xC0};
#endif
