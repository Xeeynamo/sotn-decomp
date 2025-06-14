// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static u8 AnimFrames_80180AC4[] = {0x40, 0x01, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 0x1FA,
    .facingLeft = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .animFrames = AnimFrames_80180AC4,
}};
