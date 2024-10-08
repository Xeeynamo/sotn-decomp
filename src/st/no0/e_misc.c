// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#define HEART_DROP_CASTLE_FLAG 0 // This should be fixed

// Obtained
INCLUDE_RODATA("st/no0/nonmatchings/e_misc", D_us_801C141C);

INCLUDE_ASM("st/no0/nonmatchings/e_misc", EntityRelicOrb);

#include "../entity_heart_drop.h"

#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

INCLUDE_ASM("st/no0/nonmatchings/e_misc", EntityExplosionVariantsSpawner);

#include "../entity_greypuff_spawner.h"

INCLUDE_ASM("st/no0/nonmatchings/e_misc", EntityExplosionVariants);

#include "../entity_greypuff.h"

#include "../entity_olrox_drool.h"

#include "../unk_collision_func5.h"

#include "../entity_intense_explosion.h"

#include "../initialize_unk_entity.h"

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"
