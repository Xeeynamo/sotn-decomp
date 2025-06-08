// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no4/no4.h"

#include "../blit_char_psp.h"

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", PrizeDropFall);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", PrizeDropFall2);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", CollectHeart);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", CollectGold);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", CollectSubweapon);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", CollectHeartVessel);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", CollectLifeVessel);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", DestroyCurrentEntity);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", EntityPrizeDrop);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", EntityExplosion);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", BlinkItem);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", EntityEquipItemDrop);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/e_collect", EntityRelicOrb);

#define HEART_DROP_CASTLE_FLAG 0x40
#include "../entity_heart_drop.h"

#include "../entity_message_box.h"
