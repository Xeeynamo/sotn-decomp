// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

static u8 D_80180634[] = {0x40, 0x01, 0xFF, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x01FA,
     .unk5A = 0x0000,
     .palette = PAL_UNK_000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .flags = 0,
     .animFrames = D_80180634},
};
