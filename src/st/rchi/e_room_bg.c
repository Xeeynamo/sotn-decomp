// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

static AnimateEntityFrame AnimFrames_80180690[] = {{64, 1}, POSE_END};
static AnimateEntityFrame AnimFrames_80180694[] = {
    {2, 37}, {2, 38}, {2, 39}, {2, 38}, POSE_LOOP(0),
};

ObjInit2 BackgroundBlockInit[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NULL,
        .drawFlags = ENTITY_DEFAULT,
        .blendMode = BLEND_TRANSP,
        .flags = 0,
        .animFrames = (u8*)AnimFrames_80180690,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NULL,
        .drawFlags = ENTITY_SCALEX | ENTITY_SCALEY,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .flags = 0,
        .animFrames = (u8*)AnimFrames_80180694,
    },
};

#define BG_BLOCK_NEEDS_SCALE
#include "../e_room_bg.h"
