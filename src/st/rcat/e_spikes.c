// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

// Use assembly-provided data (12D4.data.s) instead of static copies
extern AnimateEntityFrame D_us_80181364[];
extern u8 D_us_80181374[][3];
#define anim_dust D_us_80181364
#define parts_params D_us_80181374
#define SPIKES_EXTERN_DATA

#define HAS_ORIENTATIONS
#define SPIKES_PARTS_FRAME 18
#define SPIKES_TILE_WIDTH 48
#define DAMAGE_ENT_ON_HIT
#define DAMAGE_ENT_START g_CurrentEntity[1]
#define DAMAGE_ENT_END g_CurrentEntity[4]
#define SPIKES_ELEMENT ELEMENT_CUT | ELEMENT_UNK_10 | ELEMENT_UNK_1

#include "../e_spikes.h"
