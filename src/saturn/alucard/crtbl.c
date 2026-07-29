// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s16 g_AlucardCrashCrossAngles[] = {
    0x3C0,
    0x440,
    0x340,
    0x4C0,
};

s16 g_AlucardCrashCrossVertexOffsets[][2] = {
    {31, 0},   {31, -32}, {0, -32}, {-32, -32}, {-32, 0},
    {-32, 31}, {0, 31},   {31, 31}, {31, 0},
};

u8 g_AlucardCrashCrossPattern[] = {
    0, 1, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0,
};

s16 g_AlucardCrashCrossFadeSteps[] = {
    0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1,
};

s16 g_AlucardCrashCrossScaleSteps[] = {
    0,     0x30,  0x60, 0x90, 0xC0, 0xF0, 0x100, 0x100, 0x100,
    0x100, 0x100, 0xF0, 0xC0, 0x90, 0x60, 0x30,  0,
};
