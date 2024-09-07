// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

StreamInfo g_StreamInfo0 = {
    .cdOffset = 0x5a49,
    .frameCount = 0x8f,
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo1 = {
    .cdOffset = 0x3631,
    .frameCount = 0x39a,
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo2 = {
    .cdOffset = 0x207d,
    .frameCount = 0x221,
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo3 = {
    .cdOffset = 0x36f,
    .frameCount = 0x2e4,
    .isRGB24 = 1,
};

StreamInfo* g_Streams[] = {
    &g_StreamInfo0,
    &g_StreamInfo1,
    &g_StreamInfo2,
    &g_StreamInfo3,
};

s32 g_StreamWidth = 0;
s32 g_StreamHeight = 0;
