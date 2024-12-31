// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"

#include "../prize_drop_fall.h"
#include "../prize_drop_fall2.h"

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectHeart);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", func_pspeu_0924BB08);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", func_pspeu_0924BBA0);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectDummy);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", EntityPrizeDrop);

#include "../entity_explosion.h"
#include "../blink_item.h"

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", EntityEquipItemDrop);
