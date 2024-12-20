// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"

#if STAGE != STAGE_ST0
#include "entity_heart_drop.h"

#if !defined(VERSION_BETA)
#include "entity_message_box.h"
#endif

#endif

#include "../check_coll_offsets.h"
#include "../entity_message_box.h"
#include "../entity_unkId13.h"
#include "../entity_explosion_variants_spawner.h"
#include "../entity_greypuff_spawner.h"
#include "../entity_explosion_variants.h"
#include "../entity_greypuff.h"
NOP; // not sure if the other entities come before or after this NOP
#include "../entity_intense_explosion.h"
#include "../clut_lerp.h"
#include "../play_sfx_positional.h"
