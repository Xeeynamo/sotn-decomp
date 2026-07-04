// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include <cutscene.h>

u8 OVL_EXPORT(cutscene_endings)[] = {
#include "gen/cutscene_endings.h"
};

s8 D_8018BC4A = 0;
static s8 D_8018BC4B = 0;
static s32 D_8018BC4C = 0;
s8 D_8018BC50 = 0;
static s8 D_8018BC51 = 0;
static s16 D_8018BC52 = 0;

u8 OVL_EXPORT(credits)[] = {
#include "gen/credits.h"
};
