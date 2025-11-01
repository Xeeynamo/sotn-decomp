// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

static u8 D_801804D0[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_801804D4[] = {0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = 0x0006,
        .zPriority = 0x01FA,
        .unk5A = 0x0000,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .flags = 0,
        .animFrames = D_801804D0,
    },
    {
        .animSet = 0x8001,
        .zPriority = 0x00C0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = D_801804D4,
    }};
