// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

extern u8 g_eBreakableAnimations[];
extern u8 g_eBreakableExplosionTypes[];
extern u8 g_eBreakableDrawModes[];
extern u8 g_eBreakableHitboxes[];
extern u16 g_eBreakableanimSets[];

INCLUDE_ASM("st/top/nonmatchings/e_breakable", EntityBreakable);
