// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

void func_psp_0913D610(void) {}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MemcardInit);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", func_psp_0913D628);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MemcardParse);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", GetMemcardFreeBlockCount);
