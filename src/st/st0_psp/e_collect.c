// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"

extern u8* g_SubweaponAnimPrizeDrop[];
extern u8* g_MariaSubweaponAnimPrizeDrop[];
extern u16 aluric_subweapons_id[];
extern u16 maria_subweapons_id[];
extern s16 D_80180EB8[];

#include "../prize_drop_fall.h"
#include "../prize_drop_fall2.h"

void CollectHeart(u16 arg0);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectHeart);

void CollectGold(u16 goldSize);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectGold);

void CollectSubweapon(u16 subWeaponIdx);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectSubweapon);

void CollectDummy(u16);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", CollectDummy);

#include "../entity_prize_drop.h"
#include "../entity_explosion.h"
#include "../blink_item.h"

INCLUDE_ASM("st/st0_psp/psp/st0_psp/e_collect", EntityEquipItemDrop);
