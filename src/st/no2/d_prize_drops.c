// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

u16 OVL_EXPORT(PrizeDrops)[] = {
    ITEMDROP_LIFE_VESSEL,
    ITEMDROP_HEART_VESSEL,
    // Pentagram does not appear in NO2, unused?
    ITEMDROP_PENTAGRAM,
    // Goddess Shield does not appear in NO2, unused?
    ITEMDROP_GODDESS_SHIELD,
    ITEMDROP_BROADSWORD,
    ITEMDROP_ONYX,
    ITEMDROP_CHEESE,
    ITEMDROP_MANNA_PRISM,
    ITEMDROP_RESIST_FIRE,
    ITEMDROP_LUCK_POTION,
    ITEMDROP_ESTOC,
    ITEMDROP_IRON_BALL,
#ifndef VERSION_PSP
    // Garnet is replaced with Sword Card on PSP
    ITEMDROP_GARNET,
#endif
};
