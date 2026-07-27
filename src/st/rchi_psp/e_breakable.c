// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* Codebase-wide PSP comparison found no other e_breakable functions with
 * RCHI's 206/356-instruction sizes. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_breakable", EntityBreakable);

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_breakable", EntityBreakableDebris);
