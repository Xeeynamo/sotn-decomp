// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include "lba.h"

StreamInfo g_StreamInfo0 = {
    .cdOffset = OFF_LOGO15XA_STR,
#if IS_VER_INTL
    .frameCount = 0x8f,
#else
    .frameCount = 0x9e,
#endif
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo1 = {
    .cdOffset = OFF_OPN_WS_STR,
    .frameCount = 0x39a,
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo2 = {
    .cdOffset = OFF_TYK_WS_STR,
    .frameCount = 0x221,
    .isRGB24 = 1,
};

StreamInfo g_StreamInfo3 = {
    .cdOffset = OFF_END_WS_STR,
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
