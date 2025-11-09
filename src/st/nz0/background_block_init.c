// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

static u32 D_80180D54[] = {0x00000B10};
static u32 D_80180D58[] = {0x0D080C08, 0x0F080E08, 0x00001008};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = 0x8001,
        .zPriority = 0x0069,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = D_80180D54,
    },
    {
        .animSet = 0x8001,
        .zPriority = 0x0069,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = D_80180D58,
    }};
