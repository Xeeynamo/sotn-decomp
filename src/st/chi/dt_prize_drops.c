// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_prize_drops.c
 * Overlay: CHI
 * Description: DATA - Prize drops
 */

#include "chi.h"

// D_801809E4
u16 OVL_EXPORT(PrizeDrops)[] = {
    ITEMDROP_POWER_OF_SIRE,
    ITEMDROP_KARMA_COIN,
    // Stone Sword is an enemy drop, not an item drop, likely cut
    ITEMDROP_STONE_SWORD,
    ITEMDROP_TURKEY,
    ITEMDROP_RING_OF_ARES,
    ITEMDROP_COMBAT_KNIFE,
    ITEMDROP_SHIITAKE,
    ITEMDROP_SHIITAKE,
    ITEMDROP_BARLEY_TEA,
    ITEMDROP_PEANUTS,
    ITEMDROP_PEANUTS,
    ITEMDROP_PEANUTS,
    ITEMDROP_PEANUTS,
};
