// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

static AnimateEntityFrame anim1[] = {{64, 2}, POSE_END};

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
};

#include "../e_room_bg.h"
