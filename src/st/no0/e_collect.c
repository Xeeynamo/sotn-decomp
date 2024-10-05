// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stage.h"

extern s8 c_HeartPrizes[];

#include "../prize_drop_fall.h"

#include "../prize_drop_fall2.h"

#include "../collect_heart.h"

#include "../collect_gold.h"

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectSubweapon);

#include "../collect_heart_vessel.h"

#include "../collect_life_vessel.h"

#include "../destroy_current_entity.h"

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C1394);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C139C);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13A4);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13AC);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13B4);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13BC);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13C4);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13CC);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13D4);

INCLUDE_RODATA("st/no0/nonmatchings/e_collect", D_us_801C13DC);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", EntityPrizeDrop);

#include "../entity_explosion.h"

#include "../blink_item.h"

INCLUDE_ASM("st/no0/nonmatchings/e_collect", EntityEquipItemDrop);
