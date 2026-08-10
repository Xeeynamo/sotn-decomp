// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

// Armor Lord fire wave helper
static void func_us_801D1184_from_are(Primitive* prim) {
switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x1A;
        prim->clut = PAL_CC_FIRE_EFFECT;
        prim->u0 = 0xF0;
        prim->u1 = 0xFF;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        if (prim->next->r3) {
            prim->v0 = 0;
            prim->v1 = prim->v0;
            prim->v2 = 0xF;
            prim->v3 = prim->v2;
        } else {
            prim->v0 = 0x28;
            prim->v1 = prim->v0;
            prim->v2 = 0x37;
            prim->v3 = prim->v2;
        }
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->x0 -= 8;
        prim->x1 = prim->x0 + 16;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 -= 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0 + 0x10;
        prim->y3 = prim->y2;
        PGREY(prim, 0) = 0xA0;
        PGREY(prim, 1) = 0xA0;
        PGREY(prim, 2) = 0xA0;
        PGREY(prim, 3) = 0xA0;
        prim->next->u2++;
        break;

    case 1:
        if (g_Timer % 4 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 0x10;
            prim->y3 = prim->y2;
        }
        prim->r0 -= 2;
        prim->g0 = prim->b0 = prim->r0;
        prim->r1 = prim->g1 = prim->b1 = prim->r0;
        prim->r2 = prim->g2 = prim->b2 = prim->r0;
        prim->r3 = prim->g3 = prim->b3 = prim->r0;
        if (prim->r0 < 0x10) {
            UnkPolyFunc0(prim);
            prim->next->u2 = 0;
        }
        break;
    }
}

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D1388_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", EntityGuardianFireWave);

void Unused801C2C50(void) {}

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D1A9C_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D1DAC_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", EntityGuardian);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D348C_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D3700_from_are);
