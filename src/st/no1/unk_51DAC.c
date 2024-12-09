// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "game.h"

extern MATRIX D_us_80182DF4;
extern SVECTOR D_us_80182E14;
extern SVECTOR D_us_80182E1C;
extern SVECTOR D_us_80182E24;

s32 func_us_801D1DAC(void) {
    long unusedA, unusedB;
    SVECTOR rotA, rotB, rotC;
    VECTOR trans;
    MATRIX m;
    MATRIX lightMatrix;
    CVECTOR color;

    s16 posX, posY;
    Primitive* prim;
    Primitive* prim2;
    s16 z;
    s32 primIndex;
    s32 i;
    u8 temp;
    s32 unused;

    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->ext.et_801D1DAC.unk8D = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xE);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            prim = g_CurrentEntity->ext.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0xFF;
                prim->u1 = 0xD8;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x1A;
            } else {
                prim->u0 = 0xD8;
                prim->u1 = 0xFF;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0xD;
            }
            prim->x1 = prim->x0 + 0x28;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim2 = prim;
            prim = prim->next;
            prim->u0 = prim2->u0;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x0;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x20;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x80;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
            prim->u0 = prim2->u1;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x1;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x20;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = g_CurrentEntity->ext.prim;
            for (i = 0; i < 3; i++) {
                prim->tpage = 0x15;
                prim->clut = 0x160;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = 0x37;
                prim->v3 = prim->v2;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
                prim->y1 = prim->y0;
                prim->y2 = prim->y1 + 0x38;
                prim->y3 = prim->y2;
                prim->priority = g_CurrentEntity->zPriority + 1;
                prim = prim->next;
            }
            g_CurrentEntity->ext.et_801D1DAC.unk90 = prim;
            while (prim != NULL) {
                prim->tpage = 0x14;
                prim->clut = 0x220;
                prim->u0 = 0xE2;
                prim->u1 = 0xEC;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xD0;
                prim->v1 = prim->v0;
                prim->v2 = 0xD0;
                prim->v3 = prim->v2;
                prim->r0 = prim->g0 = prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
        } else {
            return 1;
        }

        g_CurrentEntity->ext.et_801D1DAC.unk86 = 0x20;
        g_CurrentEntity->ext.et_801D1DAC.unk8A = 0;
        g_CurrentEntity->ext.et_801D1DAC.unk88 = 0;
        g_CurrentEntity->ext.et_801D1DAC.unk8C = 0;
        g_CurrentEntity->drawFlags |= FLAG_DRAW_UNK8;
        g_CurrentEntity->unk6C = 0x80;
        g_CurrentEntity->step_s++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.prim;
        prim->r0 += 2;
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        g_CurrentEntity->unk6C += 0xFE;
        if (!g_CurrentEntity->unk6C) {
            g_CurrentEntity->animCurFrame = 0;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            g_CurrentEntity->ext.et_801D1DAC.unk8D += 1;
            PlaySfxPositional(0x660);
            g_CurrentEntity->step_s++;
        }
        break;

    case 2:
        g_CurrentEntity->step_s++;
        break;

    case 3:
        if (g_Timer % 8 == 0) {
            prim = g_CurrentEntity->ext.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1--;
            } else {
                prim->u1++;
            }
            prim->u3 = prim->u1;
            prim->x1++;
            prim->x3 = prim->x1;
            prim->y0 -= 3;
            prim->y2 -= 1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0++;
            } else {
                prim->u0--;
            }
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->y1 -= 3;
            prim->y3 -= 1;
            g_CurrentEntity->ext.et_801D1DAC.unk8C += 1;
            if (g_CurrentEntity->ext.et_801D1DAC.unk8C > 5) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 5:
        if (g_Timer % 4 == 0) {
            prim = g_CurrentEntity->ext.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1--;
            } else {
                prim->u0++;
                prim->u1++;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1++;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
                prim->u0++;
            } else {
                prim->u1--;
                prim->u0--;
            }
            prim->u3 = prim->u1;
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.et_801D1DAC.unk8C++;
            if (g_CurrentEntity->ext.et_801D1DAC.unk8C > 0x14) {
                g_CurrentEntity->ext.et_801D1DAC.unk8D = 2;
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 6:
        if (g_Timer % 2 == 0) {
            prim = g_CurrentEntity->ext.prim;
            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
            } else {
                prim->u0++;
            }
            prim->u2 = prim->u0;
            prim->x0++;
            prim->x2 = prim->x0;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
            } else {
                prim->u1--;
            }
            prim->u3 = prim->u1;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.et_801D1DAC.unk8C++;
            if (g_CurrentEntity->ext.et_801D1DAC.unk8C > 0x18) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 8:
        prim = g_CurrentEntity->ext.prim;
        while (prim != NULL) {
            if (g_Timer % prim->p2 == 0) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.et_801D1DAC.unk8C++ > 0x40) {
            return 1;
        }
        break;
    }

    if (g_CurrentEntity->ext.et_801D1DAC.unk8D) {
        prim = g_CurrentEntity->ext.et_801D1DAC.unk90;
        prim2 = prim;
        unused = g_CurrentEntity->ext.et_801D1DAC.unk8A;
        for (i = 0; i < 8; i++) {
            if (g_CurrentEntity->ext.et_801D1DAC.unk88 < 0x5C) {
                prim->v2++;
                prim->v3 = prim->v2;
            }
            if (g_Timer % 3 == 0) {
                temp = prim->u0;
                prim->u0 = prim->u1;
                prim->u1 = temp;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
            }
            SetGeomScreen(0x400);
            rotC.vx = 0;
            rotC.vy = (i * 512) + g_CurrentEntity->ext.et_801D1DAC.unk8A;
            rotC.vz = 0;
            RotMatrix(&D_us_80182E24, &m);
            RotMatrixY(rotC.vy, &m);
            SetRotMatrix(&m);
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x400;
            TransMatrix(&m, &trans);
            SetTransMatrix(&m);
            SetBackColor(0x20, 0x20, 0x20);
            color.r = 0x80;
            color.g = 0x60;
            color.b = 0x60;
            color.cd = prim->type;
            RotMatrix(&rotC, &lightMatrix);
            SetColorMatrix(&D_us_80182DF4);
            SetLightMatrix(&lightMatrix);
            if (g_CurrentEntity->facingLeft) {
                posX = g_CurrentEntity->posX.i.hi - 5;
            } else {
                posX = g_CurrentEntity->posX.i.hi + 8;
            }
            posY = g_CurrentEntity->posY.i.hi + 0x29;
            SetGeomOffset(posX, posY);
            rotA.vx = 0;
            rotA.vy = 0;
            rotA.vz = -g_CurrentEntity->ext.et_801D1DAC.unk86;
            rotB.vx = 0;
            rotB.vy = -g_CurrentEntity->ext.et_801D1DAC.unk88;
            rotB.vz = -g_CurrentEntity->ext.et_801D1DAC.unk86;
            prim->x0 = prim2->x1;
            prim->y0 = prim2->y1;
            prim->x2 = prim2->x3;
            prim->y2 = prim2->y3;
            prim->r0 = prim2->r1;
            prim->g0 = prim2->g1;
            prim->b0 = prim2->b1;
            prim->r2 = prim2->r3;
            prim->g2 = prim2->g3;
            prim->b2 = prim2->b3;
            z = RotTransPers(&rotA, (long*)(&prim->x3), &unusedA, &unusedB);
            z += RotTransPers(&rotB, (long*)(&prim->x1), &unusedA, &unusedB);
            z /= 2;
            NormalColorCol(&D_us_80182E14, &color, (CVECTOR*)(&prim->r3));
            NormalColorCol(&D_us_80182E1C, &color, (CVECTOR*)(&prim->r1));
            prim->priority = g_CurrentEntity->zPriority + (0x101 - z);
            prim2 = prim;
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.et_801D1DAC.unk90;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim->x2 = prim2->x3;
        prim->y2 = prim2->y3;
        prim->r0 = prim2->r1;
        prim->g0 = prim2->g1;
        prim->b0 = prim2->b1;
        prim->r2 = prim2->r3;
        prim->g2 = prim2->g3;
        prim->b2 = prim2->b3;
        g_CurrentEntity->ext.et_801D1DAC.unk8A += 4;
        if (g_CurrentEntity->ext.et_801D1DAC.unk88 < 0x68) {
            g_CurrentEntity->ext.et_801D1DAC.unk88 += 2;
        } else if (g_Timer % 4 == 0) {
            g_CurrentEntity->ext.et_801D1DAC.unk86 -= 1;
            if (g_CurrentEntity->ext.et_801D1DAC.unk86 == 0x19) {
                g_CurrentEntity->step_s++;
            }
        }
        if (g_CurrentEntity->ext.et_801D1DAC.unk8D == 2) {
            g_CurrentEntity->ext.et_801D1DAC.unk88 += 8;
        }
        if (!g_CurrentEntity->ext.et_801D1DAC.unk86) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x14);
            if (primIndex != -1) {
                g_CurrentEntity->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                g_CurrentEntity->ext.prim = prim;
                while (prim != NULL) {
                    prim->x0 = (posX + (Random() & 3)) - 2;
                    prim->y0 = posY - 0x48 + (Random() & 0x3F);
                    prim->u0 = 1;
                    prim->v0 = 1;
                    prim->r0 = 0xE0;
                    prim->b0 = 0x88;
                    prim->g0 = 0xA0;
                    prim->p2 = (Random() & 7) + 1;
                    prim->priority = g_CurrentEntity->zPriority + 1;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
            }
            g_CurrentEntity->ext.et_801D1DAC.unk8D = 0;
            g_CurrentEntity->ext.et_801D1DAC.unk8C = 0;
            g_CurrentEntity->step_s++;
        }
    }
    return 0;
}

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D2D00);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D348C);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D3700);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D37A4);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D38E4);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D3918);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D3A74);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D42EC);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D4400);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D4558);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D4950);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D49E4);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D4F18);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D5008);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D5040);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D544C);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D563C);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D5808);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D582C);

INCLUDE_ASM("st/no1/nonmatchings/unk_51DAC", func_us_801D5A10);
