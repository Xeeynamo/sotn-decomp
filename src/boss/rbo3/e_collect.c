// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

#include "../../st/prize_drop_fall.h"

#include "../../st/prize_drop_fall2.h"

#include "../../st/collect_heart.h"

#include "../../st/collect_gold.h"

extern u16 aluric_subweapons_idx[];
extern u16 aluric_subweapons_id[];
extern s16 D_80180EB8[];

#include "../../st/collect_subweapon.h"

#include "../../st/collect_heart_vessel.h"

#include "../../st/collect_life_vessel.h"

#include "../../st/destroy_current_entity.h"

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F54);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F5C);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F64);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F6C);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F74);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F7C);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F84);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F8C);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F94);

INCLUDE_RODATA("boss/rbo3/nonmatchings/e_collect", D_us_80190F9C);

extern u16 g_EInitObtainable[];
extern u8* g_SubweaponAnimPrizeDrop[];
#include "../../st/entity_prize_drop.h"

#include "../../st/entity_explosion.h"

#include "../../st/blink_item.h"

#include "../../st/entity_equip_item_drop.h"
