// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

static u8 AnimFrames_80180464[] = {0x10, 0x0B, 0x00, 0x00};
static u8 AnimFrames_80180468[] = {
    0x08, 0x0C, 0x08, 0x0D, 0x08, 0x0E, 0x08, 0x0F, 0x08, 0x10, 0x00, 0x00,
};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x69,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_80180464,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x69,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE | DRAW_TPAGE2,
        .flags = 0,
        .animFrames = AnimFrames_80180468,
    }};
