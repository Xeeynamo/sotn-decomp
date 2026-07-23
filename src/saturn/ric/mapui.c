// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u8 g_RichterMapRevealPattern[11] = {
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
};
u8 g_RichterMapRevealPatternPadding = 0;

s32 g_RichterSavedMapVramBase = 0;
s32 g_RichterSavedMapPlaneConfig = 0;

u8 g_RichterMapIconIndices[8] = {
    0x21, 0x22, 0x23, 0x38, 0x39, 0x3A, 0x32, 0x2C,
};

s16 g_RichterMapUiPositionsA[12][2] = {
    {64, 126}, {68, 126}, {92, 126}, {64, 138}, {68, 138}, {92, 138},
    {64, 150}, {68, 150}, {92, 150}, {64, 162}, {68, 162}, {92, 162},
};

s16 g_RichterMapUiPositionsB[5][2] = {
    {260, 81}, {300, 81}, {260, 92}, {300, 92}, {300, 110},
};

s16 g_RichterMapUiPositionsC[21][2] = {
    {152, 42},  {200, 42},  {152, 54},  {200, 54},  {152, 66},  {200, 66},
    {116, 182}, {116, 194}, {116, 205}, {290, 30},  {248, 58},  {288, 158},
    {288, 174}, {244, 194}, {248, 194}, {264, 194}, {272, 194}, {276, 194},
    {292, 194}, {300, 194}, {312, 192},
};

s16 g_RichterMapRevealRowIndices[7] = {8, 8, 14, 13, 20, 18, 23};

s16 g_RichterMapUiPositionsD[14][2] = {
    {144, 63},  {144, 79},  {304, 63},  {304, 79},  {144, 111},
    {144, 127}, {304, 103}, {304, 119}, {144, 159}, {144, 175},
    {304, 143}, {304, 159}, {304, 183}, {304, 199},
};

s16 g_RichterMapUiPositionsE[16][2] = {
    {10, 72},  {56, 72},  {57, 72},  {80, 72},  {10, 84}, {56, 84},
    {57, 84},  {80, 84},  {10, 96},  {56, 96},  {57, 96}, {80, 96},
    {10, 108}, {56, 108}, {57, 108}, {80, 108},
};

s16 g_RichterMapUiPositionsF[11][2] = {
    {252, 81}, {280, 81}, {252, 90}, {280, 90},  {280, 106}, {282, 81},
    {310, 81}, {282, 90}, {310, 90}, {282, 106}, {310, 106},
};
s16 g_RichterMapUiPositionsFTerminator = 0;

u8 g_RichterMapComparisonGlyphs[4] = {0xE3, 0xE5, 0xE4, 0x00};
u8 g_RichterMapAttributeGlyphs[4] = {0x32, 0x27, 0x22, 0x00};
u8 g_RichterMapPromptGlyphs[8] = {
    0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0xFF,
};

u32 g_RichterMapPromptState = 0;
u32 g_RichterMapTransitionState = 0;
