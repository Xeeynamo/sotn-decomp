// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* RCHI's PSP wall functions are 244/556 instructions; TOP's only comparable
 * PSP wall implementation is 246 instructions and is not a duplicate. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_breakable_wall", EntityBreakableWallDebris);

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_breakable_wall", EntityBreakableWall);
