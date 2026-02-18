// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

static u8 anim_1[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_2[] = {4, 0, 4, 0, 0, 0, 0, 0};
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, NULL, NULL, NULL, NULL, NULL, NULL};
static u8 g_eBreakableHitboxes[] = {8, 8, 0, 0, 0, 0, 0, 0};

#ifndef VERSION_PSP // on PSP this is in the BSS section, not data
static u8 g_eBreakableExplosionTypes[] = {0, 0, 0, 0, 0, 0, 0, 0};
#else
extern u8 g_eBreakableExplosionTypes[];
#endif

static u16 g_eBreakableanimSets[] = {
    ANIMSET_DRA(3), ANIMSET_DRA(3), 0, 0, 0, 0, 0, 0};
static u8 blend_modes[] = {
    BLEND_TRANSP | BLEND_QUARTER,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO};

static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};

#include "../e_breakable.h"
