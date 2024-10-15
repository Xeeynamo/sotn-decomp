#include "chi.h"

/*
 * File: 2B7CC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

// func_801AD0EC: StageNamePopupHelper
// func_801AD2BC: EntityStageNamePopup
#include "../e_stage_name.h"


    }
    }
    }
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/2D0EC", PrimDecreaseBrightness);    // PrimDecreaseBrightness()
//INCLUDE_ASM("st/chi/nonmatchings/2D0EC", func_801AE70C);    // PrimDecreaseBrightness()
// #if !defined(VERSION_BETA)
// struct SubPrim {
//     u8 col[3];
//     u8 type;
//     s16 x0;
//     s16 y0;
//     u8 u0;
//     u8 v0;
//     u16 clut;
// };

// typedef struct Primitive2 {
//     struct Primitive2* next;
// #if defined(VERSION_PSP)
//     u32 dummy;
// #endif
//     struct SubPrim prim[4];
// } Primitive2;

// s32 PrimDecreaseBrightness(Primitive2* prim, u8 amount) {
//     s32 isEnd;
//     s32 i;
//     s32 j;
//     struct SubPrim* subprim;
//     u8* pColor;
//     s32 col;

//     isEnd = 0;
//     subprim = &prim->prim[0];
//     for (i = 0; i < 4; i++) {
//         j = 0;
//         for (; j < 3; j++) {
//             pColor = &subprim->col[j];
//             col = *pColor;
//             col = col - amount;
//             if (col < 0) {
//                 col = 0;
//             } else {
//                 isEnd |= 1;
//             }
//             *pColor = col;
//         }
//         subprim++;
//     }
//     return isEnd;
// }
// #else
// s32 PrimDecreaseBrightness(Primitive* prim, u8 amount) {
//     u8 isEnd;
//     s32 i;
//     s32 j;
//     u8* pColor;

//     isEnd = 0;
//     pColor = &prim->r0;
//     for (i = 0; i < 4; i++, pColor += OFF(Primitive, r1) - OFF(Primitive, r0)) {
//         for (j = 0; j < 3; j++) {
//             pColor[j] -= amount;

//             if (pColor[j] > 248) {
//                 pColor[j] = 0;
//             } else {
//                 isEnd |= 1;
//             }
//         }
//     }
//     return isEnd;
// }
// #endif
// func_801ADF40: UnkPrimHelper
// func_801AE328: UpdateAnimation
// func_801AE478: FindFirstUnkPrim
// func_801AE4A8: FindFirstUnkPrim2
// func_801AE524: PrimToggleVisibility
// func_801AE5AC: PrimResetNext
// func_801AE68C: UnkPolyFunc2
// func_801AE6E0: UnkPolyFunc0
// func_801AE70C: PrimDecreaseBrightness
//#include "../prim_helpers.h"