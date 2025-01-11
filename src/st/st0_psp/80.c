// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

extern s32 D_8B42058;
u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* sp, u8* ge, u8* it) {
    switch (D_8B42058) {
    default:
    case 1:
        return en + idx;
    case 2:
        return fr + idx;
    case 3:
        return sp + idx;
    case 4:
        return ge + idx;
    case 5:
        return it + idx;
    }
}

u8* GetLang(u8* en, u8* fr, u8* sp, u8* ge, u8* it) {
    switch (D_8B42058) {
    default:
    case 1:
        return en;
    case 2:
        return fr;
    case 3:
        return sp;
    case 4:
        return ge;
    case 5:
        return it;
    }
}
