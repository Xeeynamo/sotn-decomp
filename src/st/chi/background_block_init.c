// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: e_room_bg.c
 * Overlay: CHI
 * Description: STAGE - Background Block
 */

#include "chi.h"

// D_80180730
static u8 AnimFrames_80180730[] = {0x40, 0x01, 0xFF, 0x00};

// D_80180734
static u8 AnimFrames_80180734[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00,
};

// Background Block
// D_80180740
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .unk5A = 0,
        .palette = PAL_UNK_000,
        .drawFlags = DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .animFrames = AnimFrames_80180730,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .unk5A = 0,
        .palette = PAL_UNK_000,
        .drawFlags = DRAW_TRANSP | DRAW_UNK02,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_80180734,
    }};
