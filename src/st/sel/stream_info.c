// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// each "stream" here represents one of the 4 movie files (.STR files) 
// at a specific location on the SOTN disk.
// offsets shown here are from the .idx file exported from running "jpsxdec" on the raw .bin or ISO.

// movie file: LOGO15XA.STR (Konami Logo)
// #:13|ID:LOGO15XA.STR|Sectors:23113-24544|Type:File|Size:2932736|Path:LOGO15XA.STR|Has mode 2 form 2:Yes|Has CD audio:No
// -> #:14|ID:LOGO15XA.STR[0]|Sectors:23113-24543|Type:Video|Dimensions:320x240|Frame Count:143|Sector Frames:23113-24534|Sectors/Frame:1001/100|1st frame end sector:9|Disc Speed:2|Header Frames:1-143
// -> #:15|ID:LOGO15XA.STR[0.0]|Sectors:23120-24240|Type:XA|File:1|Channel:1|Stereo?:Yes|Samples/Sec:37800|Bits/Sample:4|Sector stride:8|Disc speed:2x
StreamInfo g_StreamInfo0 = {
    .cdOffset = 0x5a49, // = 23113
    .frameCount = 0x8f,
    .isRGB24 = 1,
};

// movie file: OPN_WS.STR (opening cinematic)
// #:10|ID:OPN_WS.STR|Sectors:13873-23112|Type:File|Size:18923520|Path:OPN_WS.STR|Has mode 2 form 2:Yes|Has CD audio:No
// -> #:11|ID:OPN_WS.STR[0]|Sectors:13873-23102|Type:Video|Dimensions:320x240|Frame Count:922|Sector Frames:13873-23093|Sectors/Frame:1001/100|1st frame end sector:9|Disc Speed:2|Header Frames:1-922
// -> #:12|ID:OPN_WS.STR[0.0]|Sectors:13880-23112|Type:XA|File:1|Channel:1|Stereo?:Yes|Samples/Sec:37800|Bits/Sample:4|Sector stride:8|Disc speed:2x
StreamInfo g_StreamInfo1 = {
    .cdOffset = 0x3631, // 13873
    .frameCount = 0x39a,
    .isRGB24 = 1,
};

// movie file: TYK_WS.STR (inverted castle reveal cinematic)
// #:7|ID:TYK_WS.STR|Sectors:8317-13872|Type:File|Size:11378688|Path:TYK_WS.STR|Has mode 2 form 2:Yes|Has CD audio:No
// -> #:8|ID:TYK_WS.STR[0]|Sectors:8317-13872|Type:Video|Dimensions:320x240|Frame Count:555|Sector Frames:8317-13863|Sectors/Frame:1001/100|1st frame end sector:9|Disc Speed:2|Header Frames:1-555
// -> #:9|ID:TYK_WS.STR[0.0]|Sectors:8324-13788|Type:XA|File:1|Channel:1|Stereo?:Yes|Samples/Sec:37800|Bits/Sample:4|Sector stride:8|Disc speed:2x
StreamInfo g_StreamInfo2 = {
    .cdOffset = 0x207d, // 8317
    .frameCount = 0x221,
    .isRGB24 = 1,
};

// movie file: END_WS.STR (ending cinematic)
// #:4|ID:END_WS.STR|Sectors:879-8316|Type:File|Size:15233024|Path:END_WS.STR|Has mode 2 form 2:Yes|Has CD audio:No
// -> #:5|ID:END_WS.STR[0]|Sectors:879-8316|Type:Video|Dimensions:320x240|Frame Count:743|Sector Frames:879-8307|Sectors/Frame:1001/100|1st frame end sector:9|Disc Speed:2|Header Frames:1-743
// -> #:6|ID:END_WS.STR[0.0]|Sectors:886-7910|Type:XA|File:1|Channel:1|Stereo?:Yes|Samples/Sec:37800|Bits/Sample:4|Sector stride:8|Disc speed:2x
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
