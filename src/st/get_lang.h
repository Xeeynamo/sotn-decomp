// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

extern s32 g_UserLanguage;

u8* GetLang(u8* en, u8* fr, u8* es, u8* de, u8* it) {
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        return en;
    case LANG_FR:
        return fr;
    case LANG_ES:
        return es;
    case LANG_DE:
        return de;
    case LANG_IT:
        return it;
    }
}
