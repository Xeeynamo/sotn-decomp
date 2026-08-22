// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

static AnimateEntityFrame anim_background_flame[] = {
    {3, 3}, {3, 4}, {3, 5}, {3, 6}, POSE_LOOP(0)};
static AnimateEntityFrame anim_wall_sconce[] = {
    {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, POSE_LOOP(0)};
static AnimateEntityFrame* g_eBreakableAnimations[8] = {
    anim_background_flame, anim_wall_sconce};
static u8 g_eBreakableHitboxes[8] = {8, 8};

#ifndef VERSION_PSP // on PSP this is in the BSS section, not data
static u8 g_eBreakableExplosionTypes[8] = {EXPLOSION_SMALL, EXPLOSION_SMALL};
#else
extern u8 g_eBreakableExplosionTypes[];
#endif

static u16 g_eBreakableanimSets[8] = {ANIMSET_OVL(1), ANIMSET_OVL(1)};

static u8 blend_modes[8] = {
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
};

#ifndef VERSION_PSP
static u8 unused[8] = {0};
#endif

#include "../../st/e_breakable.h"
