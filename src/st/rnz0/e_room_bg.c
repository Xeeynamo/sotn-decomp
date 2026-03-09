// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

static u8 anim1[] = {64, 1, 255, 0};
static u8 anim2[] = {2, 37, 2, 38, 2, 39, 2, 38, 0};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x01FA,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = ENTITY_DEFAULT,
        .blendMode = BLEND_TRANSP,
        .flags = 0,
        .animFrames = anim1,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x00C0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = ENTITY_SCALEY | ENTITY_SCALEX,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .flags = 0,
        .animFrames = anim2,
    }};

#define BG_BLOCK_NEEDS_SCALE

#include "../e_room_bg.h"
