// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

SaturnSpriteImage g_WarpSpriteBank16Images[7] = {
    {4, 4, 0x0000}, {4, 4, 0x0004},   {4, 8, 0x0008}, {8, 8, 0x0010},
    {8, 8, 0x0020}, {40, 40, 0x0030}, {0, 0, 0x01C0},
};

SaturnSpriteFrameHeader g_WarpRoomFrame0 = {
    0x0000,
    0x0000,
};

SaturnSpriteFrame1 g_WarpRoomFrame1 = {
    {0x0100, 0x0000},
    {{0x0000, 0, 0, 0}},
};

SaturnSpriteFrame1 g_WarpRoomFrame2 = {
    {0x0100, 0x0000},
    {{0x0000, 0, 0, 1}},
};

SaturnSpriteFrame1 g_WarpRoomFrame3 = {
    {0x0100, 0x0000},
    {{0x0000, 0, 0, 2}},
};

SaturnSpriteFrame1 g_WarpRoomFrame4 = {
    {0x0100, 0x0000},
    {{0x0000, 0, 0, 3}},
};

SaturnSpriteFrame1 g_WarpRoomFrame5 = {
    {0x0100, 0x0000},
    {{0x0000, 0, 0, 4}},
};

SaturnSpriteFrame1 g_WarpRoomFrame6 = {
    {0x0100, 0x0000},
    {{0x0100, 40, 40, 5}},
};

SaturnSpriteFrameHeader* g_WarpSpriteBank16Frames[7] = {
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame0,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame1,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame2,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame3,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame4,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame5,
    (SaturnSpriteFrameHeader*)&g_WarpRoomFrame6,
};
