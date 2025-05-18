// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

static u8 D_801804D0[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_801804D4[] = {0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = 0x0006,
        .zPriority = 0x01FA,
        .unk5A = 0x0000,
        .palette = PAL_DRA(0),
        .drawFlags = 0x00,
        .drawMode = 0x10,
        .flags = 0x00000000,
        .animFrames = D_801804D0,
    },
    {
        .animSet = 0x8001,
        .zPriority = 0x00C0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = 0x03,
        .drawMode = 0x30,
        .flags = 0x00000000,
        .animFrames = D_801804D4,
    }};