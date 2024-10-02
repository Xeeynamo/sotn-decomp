// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stage.h"

#include "../prize_drop_fall.h"

#include "../prize_drop_fall2.h"

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectHeart);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectGold);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectSubweapon);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectHeartVessel);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", CollectLifeVessel);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", DestroyCurrentEntity);

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

INCLUDE_ASM("st/no0/nonmatchings/e_collect", EntityExplosion);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", BlinkItem);

INCLUDE_ASM("st/no0/nonmatchings/e_collect", EntityEquipItemDrop);
