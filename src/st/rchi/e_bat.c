// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

/*
 * The RCHI bat is substantially different from the shared PSX implementation
 * (198 instructions versus 147, below the tools/dups similarity threshold).
 */
INCLUDE_ASM("st/rchi/nonmatchings/e_bat", EntityBat);
