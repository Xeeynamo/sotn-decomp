// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// Each "stream" here represents one of the 4 movie files (.STR files)
// at a specific location on the SOTN disk. Data in the comments are generated
// from an .idx file exported from running "jpsxdec" on the raw .bin or ISO.

// All 4 .STR files share the following properties:
// Video:
// - Type: Video
// - Dimensions: 320x240, Disc Speed: 2, Sectors/Frame: 1001/100
// - 1st frame end sector: 9
//
// Audio:
// - Type:XA
// - File:1, Channel:1, Stereo?:Yes, Sector stride:8

// File: "LOGO15XA.STR" (Konami Logo):
// Sectors:23113-24544, Size:2932736
// - Video: Sectors:23113-24543, Frame Count:143, Sector Frames:23113-24534
// - audio: Sectors:23120-24240
StreamInfo g_StreamInfo0 = {
    .cdOffset = 0x5a49, // = 23113
    .frameCount = 0x8f,
    .isRGB24 = 1,
};

// File: "OPN_WS.STR" (opening cinematic)
// Sectors:13873-23112, Size:18923520
// - Video: Sectors:13873-23102, Frame Count:922, Sector Frames:13873-23093
// - Audio: Sectors:13880-23112
StreamInfo g_StreamInfo1 = {
    .cdOffset = 0x3631, // 13873
    .frameCount = 0x39a,
    .isRGB24 = 1,
};

// File: "TYK_WS.STR" (inverted castle reveal cinematic)
// Sectors:8317-13872, Size:11378688
// - Video: Sectors:8317-13872, Frame Count:555, Sector Frames:8317-13863
// - Audio: Sectors:8324-13788
StreamInfo g_StreamInfo2 = {
    .cdOffset = 0x207d, // 8317
    .frameCount = 0x221,
    .isRGB24 = 1,
};

// File: "END_WS.STR" (ending cinematic)
// Sectors:879-8316, Size:15233024
// - Video: Sectors:879-8316, Frame Count:743, Sector Frames:879-8307
// - Audio: Sectors:886-7910
StreamInfo g_StreamInfo3 = {
    .cdOffset = 0x36f, // 879
    .frameCount = 0x2e4,
    .isRGB24 = 1,
};

// reference all 4 movie files:
StreamInfo* g_Streams[] = {
    &g_StreamInfo0,
    &g_StreamInfo1,
    &g_StreamInfo2,
    &g_StreamInfo3,
};

s32 g_StreamWidth = 0;
s32 g_StreamHeight = 0;
