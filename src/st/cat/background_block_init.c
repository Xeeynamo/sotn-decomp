// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

static AnimateEntityFrame anim_frames[] = {{64, 1}, POSE_END};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 506,
    .facingLeft = 0,
    .unk5A = 0,
    .palette = 0,
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .animFrames = (u8*)anim_frames,
}};
