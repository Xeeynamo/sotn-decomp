// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

void func_us_801C4B2C() {
    s32 i;
    s32 xVar2;
    s32 yVar2;
    s32 xVar1;
    s32 yVar1;
    Primitive* prim2;
    Primitive* prim;

    prim = g_CurrentEntity->ext.prim;
    for(i = 0; i < 7; i++) {
        prim2 = prim->next;
        xVar1 = prim2->x2 + prim->x0;
        xVar1 /= 2;
        yVar1 = prim2->y2 + prim->y0;
        yVar1 /= 2;
        xVar2 = prim->x2 - xVar1;
        yVar2 = prim->y2 - yVar1;
        
        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x0 = prim->x2 = xVar2;
        prim2->y0 = prim->y2 = yVar2;
        
        xVar1 = prim2->x3 + prim->x1;
        xVar1 /= 2;
        yVar1 = prim2->y3 + prim->y1;
        yVar1 /= 2;
        xVar2 = prim->x3 - xVar1;
        yVar2 = prim->y3 - yVar1;
        
        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x1 = prim->x3 = xVar2;
        prim2->y1 = prim->y3 = yVar2;
        prim = prim2;
    }
}

void func_us_801C4C4C(void) {
    Primitive* prim2;
    Primitive* prim;
    s32 primIndex;
    s32 var_s1;

    switch (g_CurrentEntity->step_s) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        g_CurrentEntity->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= 0x800000;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
        } else {
            DestroyEntity(g_CurrentEntity);
            return;
        }
        for(var_s1 = 0; var_s1 < 8; var_s1++) {
            prim->tpage = 0x12;
            prim->clut = 0x164;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0x40;
                prim->u1 = 0;
                prim->u2 = 0x40;
                prim->u3 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x40;
                prim->u2 = 0;
                prim->u3 = 0x40;
            }
            prim->v0 = ((var_s1 * 2) + 0xB5);
            prim->v1 = ((var_s1 * 2) + 0xB5);
            prim->v2 = ((var_s1 * 2) + 0xB8);
            prim->v3 = ((var_s1 * 2) + 0xB8);            
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->r1 = prim->g1 = prim->b1 = 0x80;
            prim->r2 = prim->g2 = prim->b2 = 0x80;
            prim->r3 = prim->g3 = prim->b3 = 0x80;
            if (g_CurrentEntity->facingLeft) {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
            } else {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
            }
            prim->x1 = prim->x0 + 0x40;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = g_CurrentEntity->posY.i.hi - 0xA + (var_s1 * 2);
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 4;
            prim->y3 = prim->y2;
            prim->priority = ((g_CurrentEntity->zPriority) + 2);
            prim->drawMode = 2;
            prim2 = prim;
            prim = prim->next;
        }
        g_CurrentEntity->ext.ILLEGAL.u32[1] = (u32) prim2;
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = 0;
        prim->u3 = 0x40;
        prim->v0 = 0xEE;
        prim->v1 = 0xEE;
        prim->v2 = 0xEF;
        prim->v3 = 0xEF;            
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->r1 = prim->g1 = prim->b1 = 0x80;
        prim->r2 = prim->g2 = prim->b2 = 0x80;
        prim->r3 = prim->g3 = prim->b3 = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 0x40;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0;
        prim->y3 = prim->y2;
        prim->priority = ((g_CurrentEntity->zPriority) + 3);
        prim->drawMode = 0xA;
        g_CurrentEntity->ext.ILLEGAL.u32[3] = (u32) prim;
        prim = prim->next;
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 0x40;
        prim->u1 = 0x7F;
        prim->u2 = 0x40;
        prim->u3 = 0x7F;
        prim->v0 = 0xC8;
        prim->v1 = 0xC8;
        prim->v2 = 0xC9;
        prim->v3 = 0xC9;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->r1 = prim->g1 = prim->b1 = 0x80;
        prim->r2 = prim->g2 = prim->b2 = 0x80;
        prim->r3 = prim->g3 = prim->b3 = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 0x40;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0;
        prim->y3 = prim->y2;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = 0xA;
        g_CurrentEntity->ext.ILLEGAL.u32[4] = (u32) prim;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 0x5C;
        prim->u1 = 0x64;
        prim->u2 = 0x5C;
        prim->u3 = 0x64;
        prim->v0 = 0xC0;
        prim->v1 = 0xC0;
        prim->v2 = 0xC8;
        prim->v3 = 0xC8;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x12;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x12;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi - 0x28;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 8;
        LOH(prim->next->b2) = 8;
        prim->next->b3 = 0x80;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = 0xA;
        g_CurrentEntity->ext.ILLEGAL.u32[5] = (u32) prim;
        prim = prim->next;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x164;
        if (g_CurrentEntity->facingLeft) {
            prim->u0 = 0x3C;
            prim->u1 = 0;
            prim->u2 = 0x3C;
            prim->u3 = 0;
        } else {
            prim->u0 = 0;
            prim->u1 = 0x3C;
            prim->u2 = 0;
            prim->u3 = 0x3C;
        }
        prim->v0 = 0xD0;
        prim->v1 = 0xD0;
        prim->v2 = 0xDD;
        prim->v3 = 0xDD;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x12;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x12;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi + 2;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 2;
        LOH(prim->next->b2) = 1;
        prim->next->b3 = 0x80;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = 0xA;
        g_CurrentEntity->ext.ILLEGAL.u32[8] = (u32) prim;
        PlaySfxPositional(0x672);
        g_CurrentEntity->step_s++;
        g_CurrentEntity->ext.ILLEGAL.s16[4] = 0x10;
        g_CurrentEntity->animCurFrame = 0;
        break;
    case 1:                                         /* switch 1 */
        if (!--g_CurrentEntity->ext.ILLEGAL.s16[4]) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x18] = 0;
            g_CurrentEntity->ext.ILLEGAL.u8[0x19] = 0;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1A] = 0;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1B] = 0;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1C] = 0;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1D] = 0x24;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1E] = 0x30;
            g_CurrentEntity->ext.ILLEGAL.u8[0x1F] = 0;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:                                         /* switch 1 */
        g_CurrentEntity->ext.ILLEGAL.s16[4]++;
        switch (g_CurrentEntity->ext.ILLEGAL.u8[0x18]) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.prim;
            prim->y0 -= 3;
            prim->y1 -= 3;
            if ((g_CurrentEntity->ext.ILLEGAL.s16[4] % 2) != 0) {
                prim->x0 ++;
                prim->x1 --;
            }
            if ((prim->x1 - prim->x0) < 0x20) {
                g_CurrentEntity->ext.ILLEGAL.s16[4] = 0xC;
                g_CurrentEntity->ext.ILLEGAL.u8[0x18]++;
            }
            prim = prim->next;
            for(var_s1 = 0; var_s1 < 6; var_s1++) {
                prim->x2 += 2;
                prim->x3 -= 2;
                prim = prim->next;
            }
            break;
        case 1:                                     /* switch 2 */
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.prim;
            prim->y0 += 6;
            prim->y1 += 6;
            prim = prim->next;
            for(var_s1 = 0; var_s1 < 6; var_s1++) {
                prim->x2++;
                prim->x3 -= 1;
                prim = prim->next;
            }
            if (g_CurrentEntity->ext.ILLEGAL.s16[4] % 2) {
                prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[1];
                prim->x2++;
                prim->x3-= 2;
            }
            prim = g_CurrentEntity->ext.prim;
            if (prim->y0 > (g_CurrentEntity->posY.i.hi + 8)) {
                for(var_s1 = 0; var_s1 < 8; var_s1++) {
                    prim->drawMode |= 8;
                    prim = prim->next;
                }
            }
            break;
        }
        switch (g_CurrentEntity->ext.ILLEGAL.u8[0x19]) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            if (!--g_CurrentEntity->ext.ILLEGAL.u8[0x1D]) {
                prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[3];
                prim->drawMode &= 0xFFF7;
                g_CurrentEntity->ext.ILLEGAL.u8[0x1D] = 0xF;
                g_CurrentEntity->ext.ILLEGAL.u8[0x19]++;
            }
            break;
        case 1:                                     /* switch 3 */
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[3];
            prim->v2++;
            prim->v3 = prim->v2;
            prim->y0 -= 2;
            prim->y1 = prim->y0;
            if (g_CurrentEntity->ext.ILLEGAL.s16[4] % 4 == 0) {
                prim->x0--;
                prim->x1++;
            }
            if (!--g_CurrentEntity->ext.ILLEGAL.u8[0x1D]) {
                g_CurrentEntity->ext.ILLEGAL.u8[0x19]++;
            }
            break;
        case 2:                                     /* switch 3 */
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[3];
            if ((g_CurrentEntity->ext.ILLEGAL.s16[4] % 3) == 0) {
                prim->v2--;
                prim->v3 = prim->v2;
            }
            prim->y0++;
            prim->y1 = prim->y0;
            if (prim->y0 > prim->y2) {
                prim->drawMode |= 8;
                g_CurrentEntity->ext.ILLEGAL.u8[0x19] = 8;
            }
            break;
        }
        switch (g_CurrentEntity->ext.ILLEGAL.u8[0x1A]) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            if (!--g_CurrentEntity->ext.ILLEGAL.u8[0x1E]) {
                prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[4];
                prim->drawMode &= 0xFFF7;
                g_CurrentEntity->ext.ILLEGAL.u8[0x1A]++;
                return;
            }
            break;
        case 1:                                     /* switch 4 */
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[4];
            prim->v2 += 4;
            prim->v3 = prim->v2;
            prim->y0 -= 4;
            prim->y1 = prim->y0;
            if (prim->v2 > 0xF8) {
                prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[5];
                prim->drawMode &= 0xFFF7;
                LOW(prim->next->r1) = 0xFFFF0000;
                prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[8];
                prim->drawMode &= 0xFFF7;
                g_CurrentEntity->ext.ILLEGAL.u8[0x1A]++;
                return;
            }
            break;
        case 2:                                     /* switch 4 */
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[4];
            prim->y0++;
            prim->y1 = prim->y0;
            if (prim->y0 == prim->y3) {
                g_CurrentEntity->ext.ILLEGAL.s16[4] = 1;
                g_CurrentEntity->ext.ILLEGAL.u8[0x1F] = 0;
                prim->drawMode |= 8;
                g_CurrentEntity->step_s++;
            }
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[5];
            UnkPrimHelper(prim);
            LOW(prim->next->r1) += 0x1000;
            prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[8];
            UnkPrimHelper(prim);
            if (LOH((prim->next)->b2) < 0xD) {
                LOH((prim->next)->b2)++;
            }
            if (LOH((prim->next)->r2) < 0x3C) {
                LOH((prim->next)->r2) += 2;
            }
            break;
        }
        break;
    case 3:                                         /* switch 1 */
        g_CurrentEntity->ext.ILLEGAL.s16[4]++;
        prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[8];
        UnkPrimHelper(prim);
        if (g_CurrentEntity->ext.ILLEGAL.s16[4] % 4 == 0) {
            g_CurrentEntity->ext.ILLEGAL.u8[0x1F] ^= 1;
        }
        if (LOH((prim->next)->b2) < 0xD) {
                LOH((prim->next)->b2)++;
        }
        if (LOH((prim->next)->r2) < 0x3C) {
            LOH((prim->next)->r2)++;
        }
        prim = (Primitive*)g_CurrentEntity->ext.ILLEGAL.u32[5];
        UnkPrimHelper(prim);
        LOW(prim->next->r1) += 0x1000;
        if (prim->next->y0 > (g_CurrentEntity->posY.i.hi + 6)) {
            prim->drawMode |= 8;
            g_CurrentEntity->step_s++;
        }
        break;
    case 4:
        break;
    }
}

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_black_panther", func_us_801C5AA0);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_black_panther", EntityBlackPanther);
