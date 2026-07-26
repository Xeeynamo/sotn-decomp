// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/*
 * PSP RCHI's functions match other PSP overlays, but its collect data order
 * differs: Alucard/Maria tables precede the animation blocks instead of using
 * the current shared-header declaration order.
 */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", BlitChar);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", PrizeDropFall);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", PrizeDropFall2);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectHeart);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectGold);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectSubweapon);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectHeartVessel);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectLifeVessel);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", CollectDummy);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityPrizeDrop);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityExplosion);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", BlinkItem);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityEquipItemDrop);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityRelicOrb);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityHeartDrop);
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_collect", EntityMessageBox);
