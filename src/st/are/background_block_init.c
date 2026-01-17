// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

static AnimateEntityFrame anim_one[] = {{16, 0xB}, POSE_LOOP(0)};
static AnimateEntityFrame anim_two[] = {
    {8, 0x0C}, {8, 0x0D}, {8, 0x0E}, {8, 0x0F}, {8, 0x10}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_three[] = {{16, 0x13}, POSE_END};
static AnimateEntityFrame anim_four[] = {{16, 0xD}, POSE_END};
static AnimateEntityFrame anim_five[] = {{16, 0xE}, POSE_END};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 105,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .animFrames = (u8*)anim_one,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 105,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE | DRAW_TPAGE2,
        .animFrames = (u8*)anim_two,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 108,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .animFrames = (u8*)anim_three,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 108,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .animFrames = (u8*)anim_four,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 108,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .animFrames = (u8*)anim_five,
    },
};
