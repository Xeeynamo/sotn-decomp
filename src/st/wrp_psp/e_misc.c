// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

#define HEART_DROP_CASTLE_FLAG 0x118
#include "../entity_heart_drop.h"

#include "../entity_message_box.h"

#include "../entity_unkId13.h"

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

#include "../entity_explosion_variants.h"

#include "../entity_greypuff.h"

#include "../entity_intense_explosion.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"
