// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

// This is a #include "../get_lang.h", but that's a static func so need to
// re-split so all of its callers are in this file.
INCLUDE_ASM("dra_psp/psp/dra_psp/199E8", func_psp_090F6368);

INCLUDE_ASM("dra_psp/psp/dra_psp/199E8", SetGameState);

INCLUDE_ASM("dra_psp/psp/dra_psp/199E8", func_800E414C);

INCLUDE_ASM("dra_psp/psp/dra_psp/199E8", ClearBackbuffer);

INCLUDE_ASM("dra_psp/psp/dra_psp/199E8", HandleTitle);
