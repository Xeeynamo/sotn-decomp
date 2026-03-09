// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

static u32 D_us_80180B10[] = {0x00FF0140};
static u32 D_us_80180B14[] = {0x26022502, 0x26022702, 0x00000000};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x01FA,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = ENTITY_DEFAULT,
        .blendMode = BLEND_TRANSP,
        .flags = 0,
        .animFrames = D_us_80180B10,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x00C0,
        .unk5A = 0,
        .palette = 0,
        .drawFlags = ENTITY_SCALEY | ENTITY_SCALEX,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .flags = 0,
        .animFrames = D_us_80180B14,
    }};

#define BG_BLOCK_NEEDS_SCALE

#include "../e_room_bg.h"
