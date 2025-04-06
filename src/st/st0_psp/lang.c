// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

extern s32 g_UserLanguage;
u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* es, u8* de, u8* it) {
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        return en + idx;
    case LANG_FR:
        return fr + idx;
    case LANG_ES:
        return es + idx;
    case LANG_DE:
        return de + idx;
    case LANG_IT:
        return it + idx;
    }
}

#include "../get_lang.h"
