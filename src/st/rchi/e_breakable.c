// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

/*
 * RCHI's breakable entity is stage-specific and roughly twice the size of the
 * shared candle implementation (0x270 versus 0x134 bytes).
 */
INCLUDE_ASM("st/rchi/nonmatchings/e_breakable", EntityBreakable);

INCLUDE_ASM("st/rchi/nonmatchings/e_breakable", EntityBreakableDebris);
