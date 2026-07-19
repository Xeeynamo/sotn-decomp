// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

AnimationFrame g_MariaUnusedHolyWaterGlassAnim[] = {
    POSE(128, 0, 0),
    POSE_LOOP(0),
};

s16 g_MariaHolyWaterGlassShardVertices[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3},
};

s16 g_MariaUnusedHolyWaterGlassParams[9][4] = {
    {16, 0, -1, 0},
    {0, 28, 0, 0},
    {0, 28, 0, 16},
    {0, 28, 0, 32},
    {0, 28, 0, 48},
    {0, 60, 0, 0},
    {0, 60, 0, 16},
    {0, 60, 0, 32},
    {0, 60, 0, 48},
};

SaturnEntityCombatConfig g_MariaEntity060B9404CombatConfig = {
    15, 16, 8, 0, 0, 0x20, 2, 16, 4, 0x81, 0x20,
};

s8 g_MariaEntity060B9404Offsets[8][2] = {
    {30, -11}, {30, 7}, {34, -16}, {38, 3},
    {16, -11}, {16, 7}, {16, -16}, {16, -8},
};

AnimationFrame g_MariaEntity060B9404Anim0[] = {
    POSE(4, 1, 0),
    POSE(4, 2, 0),
    POSE(4, 3, 0),
    POSE(4, 4, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060B9404Anim1[] = {
    POSE(4, 5, 0),
    POSE(4, 6, 0),
    POSE(4, 7, 0),
    POSE(4, 8, 0),
    POSE_LOOP(0),
};

SaturnEntityCombatConfig g_MariaEntity060B99A8CombatConfig = {
    30, 4, 8, 0, 0, 0x8000, 2, 16, 4, 0x81, 0x20,
};

SaturnEntityCombatConfig g_MariaEntity060B9D88CombatConfig = {
    40, 9, 9, 0, 0, 0x20, 2, 16, 4, 0x181, 8,
};

SaturnEntityCombatConfig g_MariaEntity060B96C0CombatConfig = {
    45, 16, 8, 0, 0, 0x20, 2, 16, 4, 0x81, 0x20,
};

AnimationFrame g_MariaEntity060B9D88Anim[] = {
    POSE(2, 9, 0),
    POSE(1, 16, 0),
    POSE(2, 10, 0),
    POSE(1, 16, 0),
    POSE(2, 11, 0),
    POSE(1, 16, 0),
    POSE(2, 12, 0),
    POSE_LOOP(0),
};

u16 g_MariaEntityEffectTimings[6] = {40, 80, 100, 120, 60, 150};

u8 g_MariaEntityEffectPattern0[44] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 1, 2, 3, 4, 1, 2, 3,
    4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0, 0,
};

SaturnEntityCombatConfig g_MariaEntity060BAFE4CombatConfig = {
    50, 32, 16, 32, -8, 0x1000, 2, 16, 4, 1, 0x30,
};

u8 g_MariaEntityEffectPattern1[32] = {
    19, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 1, 2,
    3, 4, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0,
};

AnimationFrame g_MariaEntity060BB334Anim[] = {
    POSE(2, 1, 0),
    POSE(2, 2, 0),
    POSE(2, 3, 0),
    POSE(2, 4, 0),
    POSE(2, 5, 0),
    POSE(2, 6, 0),
    POSE(2, 7, 0),
    POSE_END,
};

SaturnEntityCombatConfig g_MariaEntity060BB334CombatConfig = {
    20, 16, 16, 0, 0, 0x9000, 2, 16, 4, 1, 8,
};

u8 g_MariaEntity060BB710Pattern[44] = {
    8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1,
    8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1,
    9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
};

u16 g_MariaEntity060BB860Params[52] = {
    0x0D0E, 0x0F10, 0x1112, 0x0019, 0x1010, 0x0000, 0x1000, 0x0002,
    0x1004, 0x0001, 0x0018, 0x0009, 0x0001, 0x0002, 0x0003, 0x0004,
    0x0005, 0x0002, 0x0003, 0x0004, 0x0005, 0x0002, 0x0003, 0x0004,
    0x0005, 0x0002, 0x0003, 0x0004, 0x0005, 0x0002, 0x0003, 0x0004,
    0x0005, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0002,
    0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009,
    0x0000, 0x0000, 0x0000, 0x0000,
};

AnimationFrame g_MariaEntity060BC320Anim0[] = {
    POSE(8, 4, 0),
    POSE(8, 5, 0),
    POSE(8, 6, 0),
    POSE(8, 7, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BC320Anim1[] = {
    POSE(8, 8, 0),
    POSE(8, 9, 0),
    POSE(8, 10, 0),
    POSE(8, 11, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BC320Anim2[] = {
    POSE(5, 4, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BC320Anim3[] = {
    POSE(5, 8, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BC320Anim4[] = {
    POSE(5, 9, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BC320Anim5[] = {
    POSE(4, 4, 0),
    POSE(4, 5, 0),
    POSE(4, 6, 0),
    POSE(4, 7, 0),
    POSE(4, 4, 0),
    POSE(4, 5, 0),
    POSE(4, 6, 0),
    POSE(4, 7, 0),
    POSE(5, 4, 0),
    POSE(5, 5, 0),
    POSE(5, 6, 0),
    POSE(5, 7, 0),
    POSE(6, 4, 0),
    POSE(6, 5, 0),
    POSE(7, 6, 0),
    POSE(8, 7, 0),
    POSE(10, 1, 0),
    POSE(8, 2, 0),
    POSE(8, 3, 0),
    POSE(8, 2, 0),
    POSE_LOOP(16),
};
