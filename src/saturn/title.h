// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef TITLE_H
#define TITLE_H

#include "sattypes.h"
#include <saturn_sprite.h>

typedef struct {
    s32 index;
    s16 x;
    s16 y;
} TitleTextSlot;

typedef struct {
    s16 width;
    s16 height;
    s32 slot;
    s32 bufferOffset;
    const char* text;
} TitleText;

#endif
