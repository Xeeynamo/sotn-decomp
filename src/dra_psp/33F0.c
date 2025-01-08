// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

s32 func_800EA5E4(u32 arg0) {
    u16 temp_v0;
    s32 i;
    s32 j;
    u32 start;
    u32 count;
    u_long* clut;
    Unkstruct_8006C3C4* clutAnim;

    temp_v0 = arg0 & ~0xFF; // & 0xFF00 would be more descriptive.
    arg0 = arg0 & 0xFF;

    if (temp_v0 & 0x8000) {
        clut = g_api.o.cluts[arg0];
    } else {
        clut = D_800A3BB8[arg0];
    }

    if (clut[0] == 0) {
        return 1;
    }
    if (clut[0] == -1) {
        return 1;
    }

    for (j = 0, clutAnim = &D_8006C3C4[0]; j < LEN(D_8006C3C4); j++, clutAnim++) {
        if (clutAnim->unk8 != 0) {
            continue;
        }
        clutAnim->desc = clut;
        clutAnim->data = clut + 3;
        clutAnim->unk8 = (GET_PAL_OP_KIND(clut[0]) | temp_v0);
        clutAnim->index = 0;
        clutAnim->unkC = 0;

        // Set unkStruct's array to all zeros, except within this range
        start = clut[1];
        count = clut[2] + start - 1;
        start >>= 8;
        count >>= 8;
        for (i = 0; i < LEN(clutAnim->unkArray); i++) {
            clutAnim->unkArray[i] = 0;
        }
        for (i = start; count >= i; i++) {
            clutAnim->unkArray[i] = 1;
        }

        switch((u8)clutAnim->unk8){
            case 2:
            case 16:
            clutAnim->unkE = 0x1F;
        }
        return 0;
    }
    return -1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090DFED8);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090DFFD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090E0870);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090E08D8);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090E0C30);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090E0C68);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090E0CA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_800EDB08);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_800EDB58);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", AllocPrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_800EDD9C);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", FreePrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", RenderPrimitives);