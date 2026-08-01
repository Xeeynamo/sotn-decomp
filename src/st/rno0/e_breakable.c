// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"
extern EInit g_EInitBreakable;

static u8 anim_1[] = {4, 1, 4, 2, 0, 0};
static u8 anim_2[] = {4, 7, 4, 8, 4, 9, 0, 0};
static u8 anim_3[] = {4, 29, 4, 30, 4, 31, 0, 0};
static u8 anim_4[] = {4, 1, 4, 2, 0, 0};
static u8 anim_5[] = {4, 1, 4, 2, 0, 0};
static u8 anim_6[] = {4, 1, 4, 2, 0, 0};
static u8 anim_7[] = {4, 1, 4, 2, 0, 0};
static u8 anim_8[] = {4, 1, 4, 2, 0, 0};
static u8 anim_9[] = {4, 1, 4, 2, 0, 0};
static u8 anim_10[] = {4, 12, 4, 13, 4, 14, 4, 15, 4, 16, 0, 0};


static u8* g_eBreakableAnimations[9] = {anim_1, anim_2, anim_3, anim_4, anim_5,
                                        anim_6, anim_7, anim_8, anim_10};
static u8 g_eBreakableHitboxes[9] = {8, 8, 8, 8, 8, 8, 8, 8, 8};
static u8 g_eBreakableExplosionTypes[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

static u16 g_eBreakableanimSets[9] = {
    ANIMSET_DRA(3), 
    ANIMSET_OVL(2),
    ANIMSET_OVL(2),
    ANIMSET_DRA(3),
    ANIMSET_DRA(3),
    ANIMSET_DRA(3),
    ANIMSET_DRA(3),
    ANIMSET_DRA(3),
    ANIMSET_OVL(2),
};
static u8 blend_modes[9] = {
    BLEND_TRANSP | BLEND_QUARTER,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
};

// Stripped on PSP
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

#define DO_ROTATION
#define COND_ROTATION
#define SPLIT_SFX

#include "../e_breakable.h"
