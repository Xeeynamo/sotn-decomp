// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#if !defined(VERSION_HD)

#include "../e_collect.h"

#else

// e_collect

#include "../prize_drop_fall.h"

INCLUDE_ASM("st/cen/nonmatchings/e_collect", func_8018CB34);

// TODO: needs c_HeartPrizes
INCLUDE_ASM("st/cen/nonmatchings/e_collect", CollectHeart);

// TODO: needs c_GoldPrizes, g_goldCollectTexts
INCLUDE_ASM("st/cen/nonmatchings/e_collect", CollectGold);

INCLUDE_ASM("st/cen/nonmatchings/e_collect", CollectSubweapon);

#include "../collect_heart_vessel.h"

INCLUDE_ASM("st/cen/nonmatchings/e_collect", CollectLifeVessel);

INCLUDE_ASM("st/cen/nonmatchings/e_collect", DestroyCurrentEntity);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D4F8);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D500);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D508);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D510);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D518);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D520);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D528);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D530);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D538);

INCLUDE_RODATA("st/cen/nonmatchings/e_collect", D_hd_8018D540);

INCLUDE_ASM("st/cen/nonmatchings/e_collect", EntityPrizeDrop);

// TODO: needs g_ExplosionYVelocities, g_ExplosionAnimations
INCLUDE_ASM("st/cen/nonmatchings/e_collect", EntityExplosion);

#include "../blink_item.h"

INCLUDE_ASM("st/cen/nonmatchings/e_collect", EntityEquipItemDrop);

#endif
