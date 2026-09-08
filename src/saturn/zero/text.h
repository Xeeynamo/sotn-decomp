// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ZERO_TEXT_H
#define SATURN_ZERO_TEXT_H

#include "sattypes.h"

typedef struct {
    s32 data[16];
    s32 unk40;
    s32 primitiveCount;
} BottomCornerText;

void func_06019560(s8*, s32*, s32*, s32*);
void func_060190D8(s32, s32*, u8);
void func_0600C6E4(s32);
void func_06019A7C(s32*, s32, s32, s32);
void func_0601A020(void);

extern s32 DAT_06057C90;

#endif
