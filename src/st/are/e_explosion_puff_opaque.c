// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

#define PUFF_PARAMS_0                                                          \
    {ANIMSET_DRA(0xE), 0x0079, 0x0000, DRAW_TPAGE | DRAW_TPAGE2, puff_anim_one}
#define PUFF_PARAMS_1                                                          \
    {ANIMSET_OVL(0xB), 0x0057, 0x0000, DRAW_DEFAULT, puff_anim_two}
#define PUFF_PARAMS_2                                                          \
    {ANIMSET_OVL(0xB), 0x0057, 0x0003, DRAW_TPAGE | DRAW_TPAGE2, puff_anim_two}
#define PUFF_PARAMS_3                                                          \
    {ANIMSET_DRA(0xE), 0x0079, 0x0004, DRAW_TPAGE | DRAW_TPAGE2, puff_anim_one}

#include "../e_explosion_puff_opaque.h"
