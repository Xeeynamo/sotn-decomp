// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

u8 D_us_80180B60[] = {0x40, 0x01, 0xFF, 0x00};
u8 D_us_80180B64[] = {0x40, 0x3B, 0xFF, 0x00};
u8 D_us_80180B68[] = {0x40, 0x3C, 0xFF, 0x00};
u8 D_us_80180B6C[] = {0x01, 0x48, 0xFF, 0x00};
u8 D_us_80180B70[] = {0x08, 0x44, 0x08, 0x45, 0x08, 0x46, 0x00, 0x00};
u8 D_us_80180B78[] = {0x40, 0x57, 0xFF, 0x00};
u8 D_us_80180B7C[] = {0x40, 0x71, 0xFF, 0x00};
u8 D_us_80180B80[] = {0x40, 0x51, 0xFF, 0x00};
u8 D_us_80180B84[] = {0x40, 0x49, 0xFF, 0x00};
u8 D_us_80180B88[] = {0x40, 0x58, 0xFF, 0x00};
u8 D_us_80180B8C[] = {0x40, 0x59, 0xFF, 0x00};
u8 D_us_80180B90[] = {0x04, 0x1E, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    // Life/heart max up text
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x1FA,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .flags = 0,
     .animFrames = D_us_80180B60},

    // The hanging skeleton with the rope
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x07F,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B64},

    // The little piece of rope around the column that the skeleton is tied to
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x07F,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B68},

    // Tile where the elevator cable goes into the stone
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x070,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B6C},

    // The gears to the right of the elevator
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x080,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B70},

    // A medium sized stone tile
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x08A,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B78},

    // The very dark bricks in the background creating the illusion of depth
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x056,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B7C},

    // A large stone tile with "seam" in it
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x070,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B80},

    // A small stone tile
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x070,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B84},

    // long instance of rain against wall
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x07F,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B88},

    // short instance of rain against wall
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x07F,
     .unk5A = 0x00,
     .palette = 0x000,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B8C},

    // mist door
    {.animSet = ANIMSET_OVL(4),
     .zPriority = 0x064,
     .facingLeft = 0x4A,
     .unk5A = 0,
     .palette = 0x207,
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_us_80180B90},
};
