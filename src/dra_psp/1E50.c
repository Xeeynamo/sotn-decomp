// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern SVECTOR* D_800A34C0[][3];

extern SVECTOR D_801379C8;
extern VECTOR D_801379D0;
extern MATRIX D_80137E00;
extern s32 D_80137E44;

void func_80105078(s32 arg0, s32 arg1) {
    s32 interp;
    s32 otz;
    s32 unused_flag;
    VECTOR vec;
    SVECTOR rotVecs[3];
    SVECTOR unkSvectors[3];
    s32 i;
    s32 j;
    Primitive* prim;
    s32 nclip_result;

    RotMatrix(&D_801379C8, &D_80137E00);
    
    for (i = 0, prim = &g_PrimBuf[D_80137E44]; i < 18; i++, prim = prim->next) {
        if (arg0 == 0) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0);
        SetRotMatrix(&D_80137E00);
        SetTransMatrix(&D_80137E00);
        otz = 0;
        for (j = 0; j < 3; j++) {
            vec.vx = rotVecs[j].vx = (D_800A34C0[i][j]->vx * arg0) >> 8;
            vec.vy = rotVecs[j].vy = (D_800A34C0[i][j]->vy * arg0) >> 8;
            vec.vz = rotVecs[j].vz = (D_800A34C0[i][j]->vz * arg0) >> 8;
            func_80017008(&vec, &unkSvectors[j]);
        }
        nclip_result = RotAverageNclip3(
            &rotVecs[0], &rotVecs[1], &rotVecs[2], (s32*)&prim->x0, (s32*)&prim->x1,
            (s32*)&prim->x2, &interp, &otz, &unused_flag);
        if (nclip_result < 0) {
            RotAverage3(&rotVecs[0], &rotVecs[2], &rotVecs[1], (s32*)&prim->x0,
                        (s32*)&prim->x2, (s32*)&prim->x1, &interp, &unused_flag);
        }
        prim->type = PRIM_LINE_G2;
        if (otz < 0xF0) {
            if (nclip_result >= 0) {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter + 3;
            } else {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 3;
            }
            if (arg1 != 0) {
                if (arg1 & 0x80) {
                    PGREY(prim,0) = PGREY(prim,1) = arg1 & 0x7F;
                } else if (arg1 < 0x11) {
                    PGREY(prim,0) = (u16)((0x10 - arg1) * 8);
                } else if (arg1 < 0x21) {
                    PGREY(prim,1) = (u16)((0x20 - arg1) * 8);
                } else {
                    prim->drawMode = DRAW_HIDE;
                    continue;
                }
            }
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
    }
}

void func_80105408(void) {
    g_Player.padSim = PAD_UP;
    g_Player.D_80072EFC = 1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_80105428);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFBD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC68);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC80);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_800EA538);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_800EA5AC);
