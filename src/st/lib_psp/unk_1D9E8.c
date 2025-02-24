// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_us_801BB8DC);

// func_us_801BBAB4 code is shared with PSX and is ready for merge
/// Seems to be the windup just before the spit attack
u8 func_us_801BBAB4(void) {
    Primitive* prim;
    Pos tempPrim;
    s32 primIndex;
    s32 unkVar;
    u8 randomVal;
    u8 ret;
#ifdef VERSION_US
    s32 dummy[2];
#endif

    ret = false;
    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x18);
        if (primIndex != -1) {
            g_CurrentEntity->primIndex = primIndex;
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            for (; prim != NULL; prim = prim->next) {
                PGREY_ALT(prim, 0, 0)
                prim->u0 = 2;
                prim->v0 = 2;
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                randomVal = Random() & 0x7F;
                if (g_CurrentEntity->facingLeft) {
                    // These look like they could be -= and += respectively,
                    // but that oddly does not match
                    randomVal = randomVal - 0x40;
                } else {
                    randomVal = randomVal + 0x40;
                }
                prim->x0 = (g_CurrentEntity->posX.i.hi +
                            ((rcos((randomVal) * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->y0 = (g_CurrentEntity->posY.i.hi +
                            ((rsin((randomVal) * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->x1 = 0;
                prim->y1 = 0;
                if (g_CurrentEntity->facingLeft) {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi + 0xA) << 0x10;
                } else {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi - 0xA) << 0x10;
                }
                LOW(prim->x2) = -unkVar / 48;
                unkVar =
                    (prim->y0 - (g_CurrentEntity->posY.i.hi - 0xB) << 0x10);
                LOW(prim->x3) = -unkVar / 48;
            }
        } else {
            ret = true;
            g_CurrentEntity->ext.lesserDemon.unk84 = 2;
        }
        g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.prim;
        for (; prim != NULL; prim = prim->next) {
            tempPrim.x.i.hi = prim->x0;
            tempPrim.x.i.lo = prim->x1;
            tempPrim.y.i.hi = prim->y0;
            tempPrim.y.i.lo = prim->y1;
            tempPrim.x.val += LOWU(prim->x2);
            tempPrim.y.val += LOWU(prim->x3);
#ifdef VERSION_PSP
            prim->x0 = LOH(tempPrim.x.i.hi);
            prim->x1 = LOH(tempPrim.x.i.lo);
            prim->y0 = LOH(tempPrim.y.i.hi);
            prim->y1 = LOH(tempPrim.y.i.lo);
#else
            prim->x0 = tempPrim.x.i.hi;
            prim->x1 = tempPrim.x.i.lo;
            prim->y0 = tempPrim.y.i.hi;
            prim->y1 = tempPrim.y.i.lo;
#endif
            prim->r0 += 3;
        }
        prim = g_CurrentEntity->ext.prim;
        PrimToggleVisibility(prim, 0x18);
        if (g_CurrentEntity->ext.lesserDemon.unk80++ > 0x30) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
            g_CurrentEntity->ext.lesserDemon.unk84++;
            g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        }
        break;
    case 2:
        ret = true;
    }
    return ret;
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092564B8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256AC0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);
