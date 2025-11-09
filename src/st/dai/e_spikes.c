// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#define HAS_ORIENTATIONS
#define SPIKES_PARTS_FRAME 15
#define SPIKES_TILE_WIDTH 80
#define DAMAGE_ENT_ON_SPAWN
#define SPIKES_ELEMENT ELEMENT_CUT | ELEMENT_UNK_10 | ELEMENT_UNK_1

// This should be removed when the e_spikes.h PAL has been reconciled across the
// overlays.
#define PAL_SPIKES_DUST PAL_CC_STONE_EFFECT

#include "../e_spikes.h"
