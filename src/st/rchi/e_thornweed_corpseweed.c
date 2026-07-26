// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

#define CORPSEWEED_TPAGE 0x13
#define CORPSEWEED_PAL 0x206
#define CORPSEWEED_PROJ_PAL 0x20E
#define g_EInitCorpseweedProjectile D_us_80180678
/* Corpseweed differs on both platforms while Thornweed and its projectile
 * match. Keep only the platform-specific middle function in assembly. */
#define CORPSEWEED_ASM
#define AnimFrames_CorpseweedAttackCharge D_us_801817C0
#include "../en_thornweed_corpseweed.h"
