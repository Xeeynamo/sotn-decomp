// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

#include "../../st/create_explosion_puff.h"

static AnimateEntityFrame D_us_80180FE8[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static AnimateEntityFrame D_us_80181004[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static AnimateEntityFrame D_us_80181020[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END};
// unused
static AnimateEntityFrame anim_unused[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE_END};
EntityConfig D_us_8018105C[] = {
    {ANIMSET_DRA(0xE), 0x0079, 0x0000, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80180FE8},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181020},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181004},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181004},
};

INCLUDE_ASM("boss/bo3/nonmatchings/e_explosion_puff_opaque", EntityExplosionPuffOpaque);
