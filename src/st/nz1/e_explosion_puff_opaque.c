// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

// Unused in us and deadstripped in pspeu
INCLUDE_ASM("st/nz1/nonmatchings/e_explosion_puff_opaque", CreateExplosionPuff);
// Used for the explosion when the e_breakable_bridge piece lands
INCLUDE_ASM("st/nz1/nonmatchings/e_explosion_puff_opaque", EntityExplosionPuffOpaque);
