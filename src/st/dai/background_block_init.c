// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static u8 anim_frames[] = {64, 1, -1, 0};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 506,
    .facingLeft = 0,
    .unk5A = 0,
    .palette = PAL_NONE,
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .animFrames = anim_frames,
}};
