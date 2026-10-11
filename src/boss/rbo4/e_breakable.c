// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

static u8 anim_1[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_2[] = {4, 7, 4, 8, 4, 9, 0, 0};
static u8 anim_3[] = {4, 29, 4, 30, 4, 31, 0, 0};
static u8 anim_4[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_5[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_6[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_7[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_8[] = {4, 1, 4, 2, 0, 0, 0, 0, 4, 1, 4, 2, 0, 0, 0, 0};
static u8* g_eBreakableAnimations[8] = {
    anim_1, anim_2, anim_3, anim_4, anim_5, anim_6, anim_7, anim_8};
static u8 g_eBreakableHitboxes[8] = {8, 8, 8, 8, 8, 8, 8, 8};
static u8 g_eBreakableExplosionTypes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static u16 g_eBreakableanimSets[8] = {
    ANIMSET_DRA(3), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_DRA(3),
    ANIMSET_DRA(3), ANIMSET_DRA(3), ANIMSET_DRA(3), ANIMSET_DRA(3),
};

static u8 blend_modes[8] = {
    BLEND_TRANSP | BLEND_QUARTER, BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,     BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,     BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,     BLEND_TRANSP | BLEND_ADD,
};

static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};

#include "../../st/e_breakable.h"
