// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

#include "../entity_explosion_variants_spawner.h"

#include "../entity_greypuff_spawner.h"

// NOTE: This entity data is slightly out of order.
// Grey puff data comes before explosion variants data,
// but explosion variant entity comes before grey puff entity.

static s16 greyPuff_rot[] = {
    /* 235C */ 0x0030,
    /* 235E */ 0x0050,
    /* 2360 */ 0x0080,
    /* 2362 */ 0x00B0,
    /* 2364 */ 0x00D0,
    /* 2366 */ 0x0100,
    /* 2368 */ 0x0100,
    /* 236A */ 0x0000,
};

static s32 greyPuff_yVel[] = {
    /* 236C */ FIX(2.0 / 128),
    /* 2370 */ FIX(18.0 / 128),
    /* 2374 */ FIX(30.0 / 128),
    /* 2378 */ FIX(48.0 / 128),
    /* 237C */ FIX(60.0 / 128),
    /* 2380 */ FIX(96.0 / 128),
};

static s32 explode_yVel[] = {
    /* 2384 */ FIX(4.0 / 128),
    /* 2388 */ FIX(20.0 / 128),
    /* 238C */ FIX(36.0 / 128),
    /* 2390 */ FIX(56.0 / 128),
    /* 2394 */ FIX(112.0 / 128),
    /* 2398 */ FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {
    /* 239C */ 1,
    /* 239D */ 9,
    /* 239E */ 21,
    /* 239F */ 43,
};

static u16 explode_lifetime[] = {
    /* 23A0 */ 0x0010,
    /* 23A2 */ 0x0018,
    /* 23A4 */ 0x002A,
    /* 23A6 */ 0x002F,
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
