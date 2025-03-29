// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F0E10);

extern RECT D_800A2D90;
extern s32 D_psp_0914A394;
extern s32 D_psp_0914A0D0;
extern s32 D_psp_09149E90;
extern s32 D_psp_0914A248;
extern s32 D_psp_09149FB0;
extern s32 D_psp_0914A388;

void func_800F9E18(s32 arg0) {
    char buffer[38];
    const int ItemsPerRow = 2;
    s32 i = arg0 * 5;
    s32 nHalfScreenSize;
    s32 nItems = i + 5;

    if (arg0 == 0) {
        ClearImage(&D_800A2D90, 0, 0, 0);
        DrawSync(0);
    }

    D_psp_0914A394 = func_psp_090EAF08(0, &D_psp_0914A0D0, &D_psp_09149E90, &D_psp_0914A248,
                          &D_psp_09149FB0);
    if(D_psp_0914A394){
        func_psp_091040A0(&D_psp_0914A388);
    }

    for (nHalfScreenSize = i; i < nItems; i++, nHalfScreenSize++) {
        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 128, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 259, 1);
        }

        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow + 1].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 640, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 771, 1);
        }
    }
}
INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F0FD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F1078);

INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F1418);

INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F1618);

INCLUDE_ASM("dra_psp/psp/dra_psp/14490", func_psp_090F17D8);
