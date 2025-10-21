// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

#define HAS_ORIENTATIONS
#define SPIKES_PARTS_FRAME 18
#define SPIKES_TILE_WIDTH 48
#define DAMAGE_ENT_ON_HIT
#define DAMAGE_ENT_START g_CurrentEntity[1]
#define DAMAGE_ENT_END g_CurrentEntity[4]
#define SPIKES_ELEMENT ELEMENT_CUT | ELEMENT_UNK_10 | ELEMENT_UNK_2

#include "../e_spikes.h"
