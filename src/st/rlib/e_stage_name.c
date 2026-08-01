// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

enum StageNameDissolverSteps {
    STAGE_NAME_DISSOLVER_INIT,
    STAGE_NAME_DISSOLVER_UPPER_HALF = 1,
    STAGE_NAME_DISSOLVER_LOWER_HALF = 2,
};

s32 PrimDecreaseBrightness(Primitive* prim, u8 arg1);

static void StageNamePopupDissolver(Primitive* prim) {
    u8 offsetX;
    s32 i, j;
    switch (prim->p3) {
    case STAGE_NAME_DISSOLVER_INIT:
        if (prim->p1 < 128) {
            if (!--prim->p1) {
                prim->p3 = STAGE_NAME_DISSOLVER_UPPER_HALF;
            }
        } else {
            if (!++prim->p1) {
                prim->p3 = STAGE_NAME_DISSOLVER_LOWER_HALF;
            }
        }
        if (prim->p3) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 80;
                }
                dst += 24;
            }
            prim->p2 = 0;
        }
        break;
    case STAGE_NAME_DISSOLVER_UPPER_HALF:
        if (prim->p2 < 20) {
            prim->p2++;
        }
        offsetX = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + offsetX;
        prim->x1 = prim->x1 + offsetX;
        prim->x3 = prim->x0;
        PrimDecreaseBrightness(prim, 4);
        break;
    case STAGE_NAME_DISSOLVER_LOWER_HALF:
        if (prim->p2 < 20) {
            prim->p2++;
        }
        offsetX = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - offsetX;
        prim->x1 = prim->x1 - offsetX;
        prim->x3 = prim->x0;
        PrimDecreaseBrightness(prim, 4);
        break;
    }
}

INCLUDE_ASM("st/rlib/nonmatchings/e_stage_name", EntityStageNamePopup);
