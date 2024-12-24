// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra_psp.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E3170);

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E31F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E4370);

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E4828);

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E4968);

void func_psp_090E4C18(void) {
    if (D_psp_091474B8 < 0) {
        D_psp_091474B8 = 0;
        D_psp_091CDC80 = D_psp_091CF698;
        D_psp_091CDC88 = D_psp_091CF6DC;
    }
}

s32 func_psp_090E4C58(void) { return D_psp_091474B8; }

void func_psp_090E4C68(void) {
    D_psp_091CDC80 = D_psp_091CF698;
    D_psp_091CDC88 = D_psp_091CF6DC;
}

void func_psp_090E4C90(void) {
    if (D_psp_091474B8 < 0) {
        D_psp_091CDC88 = D_psp_091CF6DC;
    } else {
        D_psp_091CDC80 = D_psp_091CF6DC;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/67F0", func_psp_090E4CD0);
