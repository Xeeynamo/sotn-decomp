// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

static u8 anim_1[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_2[] = {4, 0, 4, 0, 0, 0, 0, 0};
static u8 anim_3[] = {4, 12, 4, 13, 4, 14, 4, 15, 4, 16, 0, 0};
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, anim_3, NULL, NULL, NULL, NULL, NULL};
static u8 g_eBreakableHitboxes[] = {8, 8, 8, 0, 0, 0, 0, 0};

#ifndef VERSION_PSP // on PSP this is in the BSS section, not data
static u8 g_eBreakableExplosionTypes[] = {0, 0, 0, 0, 0, 0, 0, 0};
#else
extern u8 g_eBreakableExplosionTypes[];
#endif

static u16 g_eBreakableanimSets[] = {
    ANIMSET_DRA(3), ANIMSET_DRA(3), ANIMSET_OVL(1), 0, 0, 0, 0, 0};
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT};

#ifndef VERSION_PSP
// on PSP this might be either optimised out to BSS or completely removed
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};
#endif

#define SFX_BREAKABLE_HIT SFX_CANDLE_HIT_WHOOSH_A
#include "../../st/e_breakable.h"
