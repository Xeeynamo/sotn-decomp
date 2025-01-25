// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

// SFX map
FaerieSfx g_FaerieSfx = {FAERIE_HEALING,     FAERIE_POTION, FAERIE_REGENERATION,
                         FAERIE_NO_MEDICINE, FAERIE_OH_NO,  FAERIE_ARE_YOU_OK};

s32 g_SfxRandomizerHammerResist[] = {
    0x3F, FAERIE_HAI, 0x7F, FAERIE_YEAH, 0xBF, FAERIE_HA1, 0xFF, FAERIE_HA2};

s32 g_SfxRandomizerGrunt[] = {
    0x3F, FAERIE_AH, 0x7F, FAERIE_UHH, 0xBF, FAERIE_UHH2, 0xFF, FAERIE_OHH};

// clang-format off
static ServantSfxEventDesc s_IntroEventLifeVO[] = {
    { 0, 34, FAERIE_INTRO_LIFE },
    {-1, 14, 0}};
static ServantSfxEventDesc s_IntroEventCommandVO[] = {
    { 0, 34, FAERIE_INTRO_COMMAND },
    {-1, 14, 0}};

s32* g_FaerieIntroRandomizer[] = {
    0x0000007F, s_IntroEventLifeVO, 0x000000FF, s_IntroEventCommandVO};

static ServantSfxEventDesc s_SfxEventLetsGo[] = {
    { 0, 38, FAERIE_LETS_GO },
    {-1, 14, 0}};
static ServantSfxEventDesc s_SfxEventFollow[] = {
    { 0, 38, FAERIE_FOLLOW },
    {-1, 14, 0}};

s32* g_SfxEventRandomizer[] = {
    0x0000007F, s_SfxEventLetsGo, 0x000000FF, s_SfxEventFollow};

// position data with a flag field
static ServantSfxEventDesc s_DarknessHint[] =   { { 0, 14, FAERIE_DARKNESS_HINT  ,}, { -1, 14, 0 } };
static ServantSfxEventDesc s_MistHint[] =       { { 0, 14, FAERIE_MIST_HINT      ,}, { -1, 14, 0 } };
static ServantSfxEventDesc s_WallHint1[] =      { { 0, 37, FAERIE_WALL_HINT      ,}, { -1, 14, 0 } };
static ServantSfxEventDesc s_SuspiciousHint[] = { { 0, 36, FAERIE_SUSPICIOUS_HINT,}, { -1, 14, 0 } };
static ServantSfxEventDesc s_WallHint2[] =      { { 0, 36, FAERIE_WALL_HINT      ,}, { -1, 14, 0 } };

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
