// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

static AnimateEntityFrame anim1[] = {{64, 1}, POSE_END};
static AnimateEntityFrame anim2[] = {
    {2, 37}, {2, 38}, {2, 39}, {2, 38}, POSE_LOOP(0),
};

ObjInit2 BackgroundBlockInit[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = ENTITY_DEFAULT,
        .blendMode = BLEND_TRANSP,
        .flags = 0,
        .animFrames = (u8*)anim1,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .unk5A = 0x0000,
        .palette = 0,
        .drawFlags = ENTITY_SCALEX | ENTITY_SCALEY,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .flags = 0,
        .animFrames = (u8*)anim2,
    },
};

#define BG_BLOCK_NEEDS_SCALE
#include "../e_room_bg.h"
