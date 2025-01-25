// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/60F10", func_psp_0913D890);

s32 func_psp_0913D930(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 != 0) {
        return -1;
    }
    if (arg1 != 0) {
        return -1;
    }
    return func_89192EC(arg2, arg3);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60F10", func_psp_0913D998);
