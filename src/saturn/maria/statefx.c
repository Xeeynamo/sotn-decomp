// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u32 g_MariaSubwpnCrashTimer = 0;

s16 g_MariaDeathPrologueState[4] = {0};

u8 g_MariaInitialAfterimageTimers[] = {5, 10, 30, 60, 60, 60, 60, 60};

u8 g_MariaAfterimageTimers[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0xFF, 0xFF, 0, 0,
};

u8 g_MariaAfterimageFadeSteps[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16,
};

u8 g_MariaAfterimageFadeThresholds[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
};
