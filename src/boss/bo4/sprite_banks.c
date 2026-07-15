// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern s16* D_us_801B0A78[];
extern s16* D_us_801B159C[];
extern s16* D_us_801B1664[];
extern s16* D_us_801B2068[];
extern s16* D_us_801B252C[];

s16** spriteBanks[] = {
    NULL, D_us_801B0A78, D_us_801B159C, D_us_801B1664, D_us_801B2068, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
    NULL, NULL,          NULL,          D_us_801B252C, NULL,          NULL,
    NULL, NULL,          NULL,          NULL,          NULL,          NULL,
};
