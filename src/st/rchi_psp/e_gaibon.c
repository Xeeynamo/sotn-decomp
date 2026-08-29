// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* PSP RCHI's Gaibon is 1658 instructions versus NZ0's 1756. Only the
 * 90-instruction small projectile is structurally exact; leg and large
 * projectile still differ, and all four functions share stage-owned data. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_gaibon", EntityGaibon);

#include "../rchi/e_rchi_gaibon_leg.h"

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_gaibon", EntitySmallGaibonProjectile);

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_gaibon", EntityLargeGaibonProjectile);
