// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include <cutscene.h>

u8 OVL_EXPORT(cutscene_data)[] = {
#include "gen/cutscene_data.h"
};

static u8 unused[] = {32, 88, 8,  128, 8, 128, 0,   0,   0,
                      33, 90, 10, 160, 7, 120, 255, 255, 0};
