// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* sp, u8* ge, u8* it) {
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        return en + idx;
    case LANG_FR:
        return fr + idx;
    case LANG_SP:
        return sp + idx;
    case LANG_GE:
        return ge + idx;
    case LANG_IT:
        return it + idx;
    }
}
