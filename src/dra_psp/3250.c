// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFBD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFC68);

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFC80);

void func_800EA538(s32 arg0) {
    u16 v1;
    s32 i, j;
    u16 unk8;

    v1 = (0x8000 >> (arg0 - 1));
    if (arg0) {
        for (i = 0; i < LEN(D_8006C3C4); i++) {
            unk8 = D_8006C3C4[i].unk8;
            if (unk8 & v1) {
                D_8006C3C4[i].unk8 = 0;
            }
        }
    } else {
        D_8003C0EC[3] = 0;
        for (j = 0; j < LEN(D_8006C3C4); j++) {
            D_8006C3C4[j].unk8 = 0;
        }
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}
