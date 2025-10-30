// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

static u8 AnimFrames_80180994[] = {0x40, 0x01, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x01FA,
     .unk5A = 0x0000,
     .palette = PAL_NONE,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .flags = 0,
     .animFrames = AnimFrames_80180994},
};
