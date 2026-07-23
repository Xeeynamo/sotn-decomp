// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

u16 OVL_EXPORT(PrizeDrops)[] = {
    ITEMDROP_HEART_VESSEL,
    ITEMDROP_SHIELD_ROD,
    // Moon Rod does not appear in ARE, unused?
    ITEMDROP_MOON_ROD,
    ITEMDROP_BLOOD_CLOAK,
    ITEMDROP_KNIGHT_SHIELD,
    ITEMDROP_LIBRARY_CARD,
    ITEMDROP_GREEN_TEA,
#ifdef VERSION_US
    // Holy Sword is replaced with N Demon Familiar on PSP and HD
    ITEMDROP_HOLY_SWORD,
#endif
};
