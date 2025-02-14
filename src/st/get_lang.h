// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

extern s32 D_8B42058;

u8* GetLang(u8* en, u8* fr, u8* sp, u8* ge, u8* it) {
    switch (D_8B42058) {
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
