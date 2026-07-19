// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s16 g_Stage02Entity38FrameHeader[2] = {0, 0};

s16 g_Stage02Entity38ShortFrames[11][6] = {
    {0x100, 0, 0, 8, 1, 0}, {0x100, 0, 0, 4, 0, 1},
    {0x100, 0, 0, 3, 0, 2}, {0x100, 0, 0, 3, 0, 3},
    {0x100, 0, 0, 5, 1, 4}, {0x100, 0, 0, 3, 0, 5},
    {0x100, 0, 0, 4, 0, 6}, {0x100, 0, 0, 4, 1, 7},
    {0x100, 0, 0, 8, 3, 8}, {0x100, 0, 0, 7, 8, 9},
    {0x100, 0, 0, 6, 0xB, 0xA},
};

s16 g_Stage02Entity38LongFrames[9][10] = {
    {0x200, 0, 0, 6, 0x11, 0xB, 0, -5, 0xE, 0xC},
    {0x200, 0, 0, 6, 0x14, 0xD, 0x30, -9, 0xB, 0xE},
    {0x200, 0, 0, 6, 0x11, 0xB, 0, -6, 8, 0xC},
    {0x200, 0, 0, 6, 0x14, 0xD, 0, -3, 0xB, 0xE},
    {0x200, 0, 0, 6, 0x14, 0xD, 0x30, -8, 0x10, 0xC},
    {0x200, 0, 0, 6, 0x14, 0xD, 0x30, -0xD, 0xE, 0xE},
    {0x200, 0, 0, 6, 0x14, 0xD, 0, -0xB, 0x13, 0xC},
    {0x200, 0, 0, 6, 0x14, 0xD, 0, -8, 0x14, 0xE},
    {0x200, 0, 0, 6, 0x14, 0xD, 0, -9, 0x14, 0xF},
};

s16* g_Stage02Entity38Frames[21] = {
    g_Stage02Entity38FrameHeader,
    g_Stage02Entity38ShortFrames[0],
    g_Stage02Entity38ShortFrames[1],
    g_Stage02Entity38ShortFrames[2],
    g_Stage02Entity38ShortFrames[3],
    g_Stage02Entity38ShortFrames[4],
    g_Stage02Entity38ShortFrames[5],
    g_Stage02Entity38ShortFrames[6],
    g_Stage02Entity38ShortFrames[7],
    g_Stage02Entity38ShortFrames[8],
    g_Stage02Entity38ShortFrames[9],
    g_Stage02Entity38ShortFrames[10],
    g_Stage02Entity38LongFrames[0],
    g_Stage02Entity38LongFrames[1],
    g_Stage02Entity38LongFrames[2],
    g_Stage02Entity38LongFrames[3],
    g_Stage02Entity38LongFrames[4],
    g_Stage02Entity38LongFrames[5],
    g_Stage02Entity38LongFrames[6],
    g_Stage02Entity38LongFrames[7],
    g_Stage02Entity38LongFrames[8],
};
