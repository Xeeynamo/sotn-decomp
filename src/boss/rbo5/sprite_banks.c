// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

// This cannot currently be generated: sprite data ranges overlap.
extern s16* D_us_801B0B50[];
extern s16* D_us_801B1674[];
extern s16* D_us_801B173C[];
extern s16* D_us_801B2140[];
extern s16* D_us_801B2604[];

s16** spriteBanks[] = {
    NULL, D_us_801B0B50, D_us_801B1674, D_us_801B173C, D_us_801B2140, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
    NULL, NULL,          NULL,          D_us_801B2604, NULL,          NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
};
