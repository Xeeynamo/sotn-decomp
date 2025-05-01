// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

s16 mar_80154568[4] = {0, -8, -16, 0};

#if !defined(VERSION_PSP) // falls in BSS on PSP
s32 g_IsPrologueStage = 0;
#endif

#if defined(VERSION_PSP)
u8 font_eu[] = {
#include "gen_font_eu.h"
};
LangImg g_FontImage = {4, 0, {0x100, 0x380, 128, 128}, font_eu, -1, 0};

u8 hud_sp[] = {
#include "gen_hud_sp.h"
};
u8 hud_it[] = {
#include "gen_hud_it.h"
};
u8 hud_ge[] = {
#include "gen_hud_ge.h"
};
u8 hud_fr[] = {
#include "gen_hud_fr.h"
};
LangImg g_HudImage = {4, 0, {0x100, 0x2C0, 128, 128}, hud_sp, -1, 0};
#endif

u16 mar_80154574[] = {
    PAL_UNK_812F, PAL_UNK_812F, PAL_MARIA,    PAL_UNK_812F, PAL_UNK_812F,
    PAL_MARIA,    PAL_UNK_812F, PAL_UNK_812F, PAL_MARIA,    PAL_UNK_812F,
    PAL_UNK_812E, PAL_UNK_812F, PAL_UNK_812E, PAL_UNK_812F, PAL_MARIA};
