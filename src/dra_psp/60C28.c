// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C28", func_psp_0913D5D8);
