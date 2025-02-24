// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_us_801BB8DC);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256018);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092564B8);

// func_us_801BC28C code is shared with PSX and is ready for merge
// Lesser Demon punch attack
void func_us_801BC28C(void) {
    Primitive* prim;
    s32 primIndex;

    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x13;
            prim->clut = 0x24A;
            prim->v0 = 0x70;
            prim->v1 = prim->v0;
            prim->v2 = 0x7F;
            prim->v3 = prim->v2;
            if (g_CurrentEntity->facingLeft) {
                prim->next->x1 = g_CurrentEntity->posX.i.hi + 4;
                prim->next->clut = 2;
                prim->u0 = 0x2F;
                prim->u1 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x2F;
                prim->next->x1 = g_CurrentEntity->posX.i.hi - 4;
                LOH(prim->next->clut) = -2;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->next->y0 = g_CurrentEntity->posY.i.hi + 1;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim->next->b3 = 0x80;
            LOH(prim->next->r2) = 0x28;
            LOH(prim->next->b2) = 0x10;
        } else {
            g_CurrentEntity->ext.lesserDemon.unk84 = 3;
        }
        g_CurrentEntity->ext.lesserDemon.unk84++;
        return;
    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        if (prim->next->r3) {
            prim->clut = 0x252;
        } else {
            prim->clut = 0x24A;
        }

        prim->next->r3 ^= 1;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) -= 1;
        prim->next->b3 -= 4;
        if (LOH(prim->next->r2) > 0x38) {
            g_CurrentEntity->ext.lesserDemon.unk84++;
        }
        break;
    case 2:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    }
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);
