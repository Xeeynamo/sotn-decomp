// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

static AnimateEntityFrame anim_frames_0[] = {POSE(16, 0x0B, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_frames_1[] = {
    POSE(8, 0x0C, 0), POSE(8, 0x0D, 0), POSE(8, 0x0E, 0),
    POSE(8, 0x0F, 0), POSE(8, 0x10, 0), POSE_LOOP(0)};

ObjInit2 BackgroundBlockInit[] = {
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 105,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = 0,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_NO,
     .flags = 0,
     .animFrames = (u8*)anim_frames_0},
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 105,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = 0,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_TRANSP | BLEND_ADD,
     .flags = 0,
     .animFrames = (u8*)anim_frames_1},
};
