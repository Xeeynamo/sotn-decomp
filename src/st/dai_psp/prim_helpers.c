// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dai/dai.h"

void UnkPrimHelper(Primitive* prim) {
    SVECTOR sp10; // FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR trans1;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX m;
    SVECTOR rot = {0, 0, 0};
    u8 temp_v1_2;
    u16 temp;

    if (prim->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = prim->next->x1;
        sp10.vx = prim->next->y1;
        LOW(sp10.vx) += LOWU(prim->next->u0);
        prim->next->x1 = sp10.vy;
        prim->next->y1 = sp10.vx;
        LOW(prim->next->x0) += LOW(prim->next->r1);
    }
    temp_v1_2 = prim->next->b3;
    temp = (temp_v1_2 + (temp_v1_2 << 8));
    LOH(prim->r0) = LOH(prim->r1) = LOH(prim->r2) = LOH(prim->r3) = temp;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = temp_v1_2;
    trans1.vx = 0;
    trans1.vy = 0;
    trans1.vz = 0x400 - LOH(prim->next->u1);
    RotMatrix(&rot, &m);
    if (prim->p3 & 0x20) {
        sp20.vx = prim->next->x3;
        sp20.vy = prim->next->y3;
        RotMatrixX(sp20.vx, &m);
        RotMatrixY(sp20.vy, &m);
    }
    sp20.vz = LOH(prim->next->tpage);
    RotMatrixZ(sp20.vz, &m);
    TransMatrix(&m, &trans1);
    if (prim->p3 & 0x10) {
        trans1.vx = prim->next->x2;
        trans1.vy = prim->next->y2;
        trans1.vz = 0x1000;
        ScaleMatrix(&m, &trans1);
    }
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    SetGeomScreen(0x400);
    SetGeomOffset(prim->next->x1, prim->next->y0);
    sp38.vx = -LOH(prim->next->r2) / 2;
    sp38.vy = -LOH(prim->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(prim->next->r2) / 2;
    sp40.vy = -LOH(prim->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(prim->next->r2) / 2;
    sp48.vy = LOH(prim->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(prim->next->r2) / 2;
    sp50.vy = LOH(prim->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy((long*)&prim->x0);
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy((long*)&prim->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy((long*)&prim->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy((long*)&prim->x3);
}

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

void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = DRAW_HIDE | DRAW_UNK02;
}

void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}

struct SubPrim {
    u8 col[3];
    u8 type;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
};

typedef struct Primitive2 {
    struct Primitive2* next;
    u32 dummy;
    struct SubPrim prim[4];
} Primitive2;

s32 PrimDecreaseBrightness(Primitive2* prim, u8 amount) {
    s32 isEnd;
    s32 i;
    s32 j;
    struct SubPrim* subprim;
    u8* pColor;
    s32 col;

    isEnd = 0;
    subprim = &prim->prim[0];
    for (i = 0; i < 4; i++) {
        j = 0;
        for (; j < 3; j++) {
            pColor = &subprim->col[j];
            col = *pColor;
            col = col - amount;
            if (col < 0) {
                col = 0;
            } else {
                isEnd |= 1;
            }
            *pColor = col;
        }
        subprim++;
    }
    return isEnd;
}
