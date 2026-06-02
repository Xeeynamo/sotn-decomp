// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

static AnimateEntityFrame anim_frames[] = {{64, 2}, POSE_END};
static AnimateEntityFrame anim_frames_2[] = {{64, 2}, POSE_END};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 506,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = DRAW_DEFAULT,
        .blendMode = BLEND_TRANSP,
        .animFrames = (u8*)anim_frames,
    },
    {
        .animSet = ANIMSET_OVL(8),
        .zPriority = 170,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = DRAW_DEFAULT,
        .blendMode = BLEND_NO,
        .animFrames = (u8*)anim_frames_2,
    }};
