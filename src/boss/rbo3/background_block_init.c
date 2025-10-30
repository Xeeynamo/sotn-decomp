// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

static u8 anim_frames[] = {0x40, 0x01, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x01FA,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = PAL_NONE,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .flags = 0,
     .animFrames = anim_frames},
};
