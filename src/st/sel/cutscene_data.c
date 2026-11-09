// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include <cutscene.h>

u8 cutscene_endings[] = {
#include GEN_VERSION(cutscene_endings.h)
};

#if REGION == REGION_EU
static s8 D_eu_8018BC4F = 0;
#endif

s8 D_8018BC4A = 0;
static s8 D_8018BC4B = 0;

#if REGION == REGION_EU || REGION == REGION_JP
static s16 D_8018BC4C = 0;
#else
static s32 D_8018BC4C = 0;
#endif

s8 D_8018BC50 = 0;
static s8 D_8018BC51 = 0;
static s16 D_8018BC52 = 0;

u8 cutscene_credits[] = {
#include GEN_VERSION(credits.h)
};
