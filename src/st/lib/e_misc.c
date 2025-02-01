// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

#include "../entity_explosion_variants_spawner.h"

#include "../entity_greypuff_spawner.h"

// NOTE: This entity data is slightly out of order.
// Grey puff data comes before explosion variants data,
// but explosion variant entity comes before grey puff entity.

static s16 greyPuff_rot[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

static s32 greyPuff_yVel[] = {
    /* 1008 */ FIX(2.0 / 128),
    /* 100C */ FIX(18.0 / 128),
    /* 1010 */ FIX(30.0 / 128),
    /* 1014 */ FIX(48.0 / 128),
    /* 1018 */ FIX(60.0 / 128),
    /* 101C */ FIX(96.0 / 128),
};

static s32 explode_yVel[] = {
    /* 1020 */ FIX(4.0 / 128),
    /* 1024 */ FIX(20.0 / 128),
    /* 1028 */ FIX(36.0 / 128),
    /* 102C */ FIX(56.0 / 128),
    /* 1030 */ FIX(112.0 / 128),
    /* 1034 */ FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {
    /* 1038 */ 1,
    /* 1039 */ 9,
    /* 103A */ 21,
    /* 103B */ 43,
};

static u16 explode_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

#include "../entity_explosion_variants.h"

#include "../entity_greypuff.h"

#include "../entity_olrox_drool.h"

#include "../unk_collision_func5.h"

#include "../unk_collision_func4.h"

#include "../entity_intense_explosion.h"

#include "../initialize_unk_entity.h"

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

#include "../unk_recursive_primfunc_1.h"

#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"
