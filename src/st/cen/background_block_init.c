// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

static u8 D_80180488[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_8018048C[] = {0x40, 0x07, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_OVL(2),
     .zPriority = 129,
     .unk5A = 0,
     .palette = 0,
     .drawFlags = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_8018048C},
};
