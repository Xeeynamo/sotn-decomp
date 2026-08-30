// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"
#include <cutscene.h>

s32 metLibrarian = 0;
s32 D_us_80183F64 = 0;

u8 cutscene_data[] = {
#include <gen/cutscene_data.h>
#include <gen/cutscene_events.h>
};
