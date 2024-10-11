// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

static u8 anim_1[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_2[] = {4, 7, 4, 8, 4, 9, 0, 0};
static u8 anim_3[] = {4, 29, 4, 30, 4, 31, 0, 0};
static u8 anim_4[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_5[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_6[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_7[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_8[] = {4, 1, 4, 2, 0, 0, 0, 0, 4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_9[] = {4, 12, 4, 13, 4, 14, 4, 15, 4, 16, 0, 0};
// This has 9 animations? Other stages only seem to have 8.
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, anim_3, anim_4, anim_5, anim_6, anim_7, anim_8, anim_9};
static u8 g_eBreakableHitboxes[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0};

// TODO: Check if PSP is in the BSS section like it is on other stages
static u8 g_eBreakableExplosionTypes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static u16 g_eBreakableanimSets[] = {
    ANIMSET_DRA(3), ANIMSET_OVL(1),
    ANIMSET_OVL(1), ANIMSET_DRA(3),
    ANIMSET_DRA(3), ANIMSET_DRA(3),
    ANIMSET_DRA(3), ANIMSET_DRA(3),
    ANIMSET_OVL(1), 0};
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT};

#include "../e_breakable.h";
