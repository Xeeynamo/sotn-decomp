// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

SaturnEntityCombatConfig g_MariaEntity060BC320CombatConfig = {
    30, 0, 0, 0, 0, 0x1000, 2, 16, 4, 1, 0x18,
};

u16 g_MariaEntity060BC320SpawnCounter = 0;

SaturnEntityCombatConfig g_MariaEntity060BCFF4CombatConfig = {
    20, 8, 8, 0, 0, 0x1000, 2, 20, 20, 1, 0,
};

u16 g_MariaEntity060BD0D0Padding = 0;

AnimationFrame g_MariaEntity060BD0D0Anim0[] = {
    POSE(7, 1, 0),
    POSE(7, 3, 0),
    POSE(7, 2, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BD0D0Anim1[] = {
    POSE(7, 4, 0),
    POSE(7, 5, 0),
    POSE(7, 6, 0),
    POSE_LOOP(0),
};

AnimationFrame g_MariaEntity060BD0D0Anim2[] = {
    POSE(7, 7, 0),
    POSE(7, 8, 0),
    POSE(7, 9, 0),
    POSE_LOOP(0),
};

SaturnEntityCombatConfig g_MariaEntity060BD150CombatConfig = {
    255, 8, 16, 22, -4, 0, 4, 6, 0, 1, 1,
};

u16 g_MariaEntity060BD474ResultParams[4] = {2, 0, 8, 5};
