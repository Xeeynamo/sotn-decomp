// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra_psp.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/60D80", func_psp_0913D700);

s32 func_psp_0913D798(s32 arg0, s32 arg1) {
    return (&D_psp_09236780[arg0][arg1])[0x10];
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60D80", func_psp_0913D7D8);
