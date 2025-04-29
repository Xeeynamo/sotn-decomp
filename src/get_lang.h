// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

#pragma optimization_level 0

extern s32 g_UserLanguage;

static void* GetLang(void* en, void* fr, void* sp, void* ge, void* it) {
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        return en;
    case LANG_FR:
        return fr;
    case LANG_SP:
        return sp;
    case LANG_GE:
        return ge;
    case LANG_IT:
        return it;
    }
}

#pragma optimization_level reset