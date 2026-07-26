// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* PSP NZ0/NP3 share the 146-instruction spear and 84-instruction projectile,
 * but RCHI's 1084-instruction Slogra and its owned data are a coupled stage
 * variant. Split the helpers only when that data can retain original order. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_slogra", EntitySlogra);

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_slogra", EntitySlograSpear);

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_slogra", EntitySlograSpearProjectile);
