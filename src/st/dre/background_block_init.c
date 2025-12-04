// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

static AnimateEntityFrame AnimFrames_80180518[] = {0x40, 0x01, 0xFF, 0x00};
static AnimateEntityFrame AnimFrames_8018051C[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NULL,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .flags = 0,
        .animFrames = (u8*)AnimFrames_80180518,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NULL,
        .drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY,
        .drawMode = DRAW_TPAGE | DRAW_TPAGE2,
        .flags = 0,
        .animFrames = (u8*)AnimFrames_8018051C,
    }};
