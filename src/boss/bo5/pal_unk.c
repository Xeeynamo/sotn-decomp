// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>

u16 D_us_8018E704[] = {
#include "gen/D_us_8018E704.h"
};
#ifndef VERSION_PSP
// unreferenced
u16 D_us_8018E9C4[] = {
#include "gen/D_us_8018E9C4.h"
};
#endif
u16 D_us_8018EBE4[] = {
#include "gen/D_us_8018EBE4.h"
#ifdef FIX_UB
// fix crash where bo5/gen/palette_def.h copies 0x100 bytes instead of 0x40
#include "gen/D_us_8018EC24.h"
#endif
};
u16 D_us_8018EC24[] = {
#include "gen/D_us_8018EC24.h"
};
u16 D_us_8018EE24[] = {
#include "gen/D_us_8018EE24.h"
};
u16 D_us_8018F024[] = {
#include "gen/D_us_8018F024.h"
};
