// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

#define CORPSEWEED_TPAGE 0x13
#define CORPSEWEED_PAL 0x20B
#define CORPSEWEED_PROJ_PAL 0x20E
#define g_EInitCorpseweedProjectile D_us_80180678

/* The PSP Corpseweed body uses palette 0x20B, but correcting that constant in
 * the shared C still produces 0x1260 bytes instead of the original 0x1240.
 * Its remaining diff is register allocation/expression scheduling rather than
 * mirrored-stage arithmetic, so interleave only that function as assembly. */
#define CORPSEWEED_ATTACK_CHARGE_SCOPE
#define THORNWEED_ONLY
#define SKIP_CORPSEWEED
#include "../en_thornweed_corpseweed.h"
#undef THORNWEED_ONLY
#undef SKIP_CORPSEWEED

INCLUDE_ASM(
    "st/rchi_psp/nonmatchings/rchi_psp/e_thornweed_corpseweed",
    EntityCorpseweed);

#define THORNWEED_DATA_ALREADY_DEFINED
#define CORPSEWEED_PROJECTILE_ONLY
#include "../en_thornweed_corpseweed.h"
