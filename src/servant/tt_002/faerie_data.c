// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"
#include "sfx.h"

// SFX map
s32 D_us_80172BCC[] = {
    NA_VO_FAERIE_HEALING, NA_VO_FAERIE_POTION, NA_VO_FAERIE_REGENERATION,
    NA_VO_FAERIE_NO_MEDICINE, NA_VO_FAERIE_OH_NO, NA_VO_FAERIE_ARE_YOU_OK,
};

s32 g_SfxRandomizerHammerResist[] = {0x3F, NA_SE_FAERIE_HAI, 0x7F, NA_SE_FAERIE_YEAH,
                       0xBF, NA_SE_FAERIE_HA1, 0xFF, NA_SE_FAERIE_HA2};

s32 g_SfxRandomizerGrunt[] = {0x3F, NA_SE_FAERIE_AH, 0x7F, NA_SE_FAERIE_UHH,
                       0xBF, NA_SE_FAERIE_UHH2, 0xFF, NA_SE_FAERIE_OHH};

static FaerieSfxEventDesc s_IntroEventLifeVO[2] = { { 0, 34, NA_VO_FAERIE_INTRO_LIFE, },{-1, 14, 0}};

static FaerieSfxEventDesc s_IntroEventCommandVO[] = {{0, 34, NA_VO_FAERIE_INTRO_COMMAND,},{-1, 14, 0}};

s32 g_FaerieIntroRandomizer[] = {0x0000007F, s_IntroEventLifeVO, 0x000000FF, s_IntroEventCommandVO};

static FaerieSfxEventDesc D_us_80172C4C[] = {{0, 38, NA_VO_FAERIE_LETS_GO,},{ -1, 14, 0}};

static FaerieSfxEventDesc D_us_80172C58[] = {{0, 38, NA_VO_FAERIE_FOLLOW,},{-1, 14, 0}};

// This is a ranked lookup table.  First column is selected from a rand() %
// 0x100 to select the data at the pointer in column 2
s32 D_us_80172C64[] = {0x0000007F, D_us_80172C4C, 0x000000FF, D_us_80172C58};

// position data with a flag field
// clang-format off
static FaerieSfxEventDesc s_DarknessHint[2] = { { 0, 14, NA_VO_FAERIE_DARKNESS_HINT,} , { -1, 14, 0 } };
static FaerieSfxEventDesc s_MistHint[2] = { { 0, 14, NA_VO_FAERIE_MIST_HINT,} , { -1, 14, 0 } };
static FaerieSfxEventDesc s_WallHint1[2] = { { 0, 37, NA_VO_FAERIE_WALL_HINT,} , { -1, 14, 0 } };
static FaerieSfxEventDesc s_SuspiciousHint[2] = { { 0, 36, NA_VO_FAERIE_SUSPICIOUS_HINT,} , { -1, 14, 0 } };
static FaerieSfxEventDesc s_WallHint2[2] = { { 0, 36, NA_VO_FAERIE_WALL_HINT,} , { -1, 14, 0 } };

HintTriggerMap g_FaerieHints[] = {
    { .left = -1,  .top = -1,  .hint = s_DarknessHint },
    { .left = -1,  .top = -1,  .hint = s_MistHint },
    { .left = 88,  .top = 184, .hint = s_WallHint1 },
    { .left = 32,  .top = 128, .hint = s_SuspiciousHint },
    { .left = 56,  .top = 128, .hint = s_WallHint2 },
    { .left = 128, .top = 208, .hint = s_WallHint1 },
    { .left = 208, .top = 112, .hint = s_WallHint2 },
    { .left = 160, .top = 128, .hint = s_SuspiciousHint },
    { .left = 208, .top = 120, .hint = s_WallHint2 },
    { .left = 48,  .top = 128, .hint = s_SuspiciousHint },
};
// clang-format on

s16 g_FaerieFrameCount1 = 0x1518;
s16 g_FaerieFrameCount2 = 0x0960;
