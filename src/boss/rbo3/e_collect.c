// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

#include "../../st/prize_drop_fall.h"

#include "../../st/prize_drop_fall2.h"

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", CollectHeart);

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", CollectGold);

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", CollectSubweapon);

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", CollectHeartVessel);

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", CollectLifeVessel);

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", DestroyCurrentEntity);

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

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", EntityPrizeDrop);

#include "../../st/entity_explosion.h"

#include "../../st/blink_item.h"

INCLUDE_ASM("boss/rbo3/nonmatchings/e_collect", EntityEquipItemDrop);
