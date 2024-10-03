// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#if !defined(VERSION_HD)

#include "../e_collect.h"

#else

// e_collect

#include "../prize_drop_fall.h"

#include "../prize_drop_fall2.h"

#include "../collect_heart.h"

#include "../collect_gold.h"

extern u16 aluric_subweapons_idx[];
extern u16 aluric_subweapons_id[];

#include "../collect_subweapon.h"

#include "../collect_heart_vessel.h"

#include "../collect_life_vessel.h"

#include "../destroy_current_entity.h"

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

extern s16 D_80180EB8[];
extern u8* g_SubweaponAnimPrizeDrop[];
#include "../entity_prize_drop.h"

// TODO: needs g_ExplosionYVelocities, g_ExplosionAnimations
INCLUDE_ASM("st/cen/nonmatchings/e_collect", EntityExplosion);

#include "../blink_item.h"

INCLUDE_ASM("st/cen/nonmatchings/e_collect", EntityEquipItemDrop);

#endif
