// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"

extern u8* g_SubweaponAnimPrizeDrop[];
extern u8* g_MariaSubweaponAnimPrizeDrop[];
extern u16 aluric_subweapons_id[];
extern u16 aluric_subweapons_idx[];
extern u16 maria_subweapons_id[];
extern s16 D_80180EB8[];
extern s8 c_HeartPrizes[2];

#include "../prize_drop_fall.h"
#include "../prize_drop_fall2.h"

void CollectHeart(u16 goldSize);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectHeart);

#include "../collect_gold.h"
#include "../collect_subweapon.h"
NOP;
#include "../destroy_current_entity.h"
#include "../entity_prize_drop.h"
#include "../entity_explosion.h"
#include "../blink_item.h"

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", EntityEquipItemDrop);
