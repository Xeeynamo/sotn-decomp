// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

// This table is not currently represented by the asset config.
extern s16* D_us_801A39B0[];
extern s16* D_us_801A4628[];
extern s16* D_us_801A43A4[];
extern s16* D_us_801A4AAC[];

s16** spriteBanks[] = {
    NULL, D_us_801A39B0, NULL, D_us_801A4628, D_us_801A43A4, D_us_801A4AAC,
    NULL, NULL,          NULL, NULL,          NULL,          NULL,
    NULL, NULL,          NULL, NULL,          NULL,          NULL,
    NULL, NULL,          NULL, NULL,          NULL,          NULL,
};
