// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

static u8 anim_frames[] = {0x40, 0x01, 0xFF, 0x00};

ObjInit2 BackgroundBlockInit[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 0x01FA,
    .unk5A = 0x0000,
    .palette = 0,
    .drawFlags = ENTITY_DEFAULT,
    .blendMode = BLEND_TRANSP,
    .flags = 0,
    .animFrames = anim_frames,
}};

#include "../../st/e_room_bg.h"
