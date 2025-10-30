// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

static u8 AnimFrames_801809F8[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_801809FC[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_80180A00[] = {0x40, 0x19, 0xFF, 0x00};
static u8 AnimFrames_80180A04[] = {
    0x04, 0x1A, 0x04, 0x1B, 0x04, 0x1C, 0x04, 0x1D, 0x04, 0x1E, 0x00, 0x00,
};
static u8 AnimFrames_80180A10[] = {
    0x03, 0x1F, 0x03, 0x20, 0x03, 0x21, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00,
};
static u8 AnimFrames_80180A1C[] = {0x40, 0x22, 0xFF, 0x00};
static u8 AnimFrames_80180A20[] = {0x40, 0x13, 0xFF, 0x00};
static u8 AnimFrames_80180A24[] = {0x40, 0x14, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NONE,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_801809F8,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_UNK_210,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_801809FC,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_UNK_210,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_80180A00,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_UNK_210,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_80180A04,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_UNK_210,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_80180A10,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x80,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_UNK_210,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_80180A1C,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x6C,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NONE,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_80180A20,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x6C,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_NONE,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_80180A24,
    }};
