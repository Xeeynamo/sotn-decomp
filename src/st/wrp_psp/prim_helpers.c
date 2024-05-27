#include "../wrp/wrp.h"

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
    prim->next->drawMode = 0xA;
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
