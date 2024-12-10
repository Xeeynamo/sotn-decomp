// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra_psp.h"

s32 func_psp_09141860(s32 arg0) { return D_psp_091893B8[arg0]; }

void func_psp_09141878(s32 arg0) {
    func_892A620(0, 0);
    func_psp_09140BF8(0, 0x7F, 0x7F);
    if (arg0 >= 0 && arg0 <= 0x230) {
        func_psp_09141668(arg0);
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/64EE0", func_psp_091418D0);

INCLUDE_ASM("dra_psp/psp/dra_psp/64EE0", func_psp_09141AA0);
