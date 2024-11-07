// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

s16 D_us_80172C24[] = {0x0000, 0x0022, 0x0472, 0xFFFF, 0x000E, 0x0000};

s16 D_us_80172C30[] = {0x0000, 0x0022, 0x0473, 0xFFFF, 0x000E, 0x0000};

// This is a ranked lookup table.  First column is selected from a rand() %
// 0x100 to select the data at the pointer in column 2
RANKED_LOOKUP_TABLE(D_us_80172C3C) = {0x0000007F, D_us_80172C24, 0x000000FF, D_us_80172C30};

s16 D_us_80172C4C[] = {0x0000, 0x0026, 0x0476, 0xFFFF, 0x000E, 0x0000};

s16 D_us_80172C58[] = {0x0000, 0x0026, 0x0479, 0xFFFF, 0x000E, 0x0000};

// This is a ranked lookup table.  First column is selected from a rand() %
// 0x100 to select the data at the pointer in column 2
RANKED_LOOKUP_TABLE(D_us_80172C64) = {0x0000007F, D_us_80172C4C, 0x000000FF, D_us_80172C58};
